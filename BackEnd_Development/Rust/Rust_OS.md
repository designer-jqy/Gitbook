# Rust
Statics are initialized at compile time, in contrast to normal variables that are initialized at run time.
The 'static lifetime specifies that the reference is valid for the whole program run time.

## raw pointer
Rust’s ownership rules don’t allow a mutable reference at the same time as any immutable references. With raw pointers, we can create a mutable pointer and an immutable pointer to the same location and change data through the mutable pointer, potentially creating a data race. Be careful!


# CPU Exceptions

在各种各样错误的情况下，都可能发生CPU异常；例如，访问无效的内存地址或者除零的时候。为了处理这些异常，
我们需要设置一个中断描述符表，其中的描述符指向了对应的处理函数。在这篇文章的最后，我们的内核将能够捕获
断点异常，并在之后恢复正常执行。

## 概述

一个异常标识着当前指令的某些错误。例如，如果当前的指令尝试除0，那么CPU将产生一个异常。
当一个异常发生的时候，CPU中断它当前的工作并根据异常类型调用特定的异常处理函数。
在x86架构上，大约有20种不同的CPU异常类型。最重要的几个是:
* **Page Fault**
    Page Fault发生在访问非法内存的时候，例如，如果当前的指令尝试读一个没有映射的页或者写一个只读的页。
* **Invalid Opcode**
    该异常发生在当前指令无效的时候，例如，当我们尝试使用新的SSE指令在旧的不支持该指令的CPU上时。
* **General Protection Fault**
    这个异常具有广泛的诱因，它发生在各种各样的违规访问上，例如在用户代码中执行特权指令或者在配置寄存器中覆盖保留字段。
* **Double Fault**
    Double Fault: 当一个异常发生的时候，CPU尝试调用相应的处理函数，但是在调用处理函数的过程中，发生了另外一个异常。
    这个异常还发生在没有对相应的异常注册处理函数。
* **Triple Fault**
    如果CPU在尝试调用Double Fault异常处理函数的时候，发生了一个异常，将会产生Triple Fault。我们无法捕捉和处理Triple Fault，
    大多数处理器痛殴复位和重启操作系统来处理该异常。
    有关异常的完成列表请参见[OSDev wiki.](https://wiki.osdev.org/Exceptions)
### 中断描述符表
为了捕捉和处理异常，我们必须建立一个所谓的中断描述符表(IDT)。在这个表中，我们可以给每个CPU异常指定一个处理函数。由于硬件直接
使用该表，所以我们必须遵守相应的预定义格式。每个条目必须具备以下的16字节结构：

| 类型 | 名称                    | 描述                     |
| :--: | ----------------------- | ------------------------ |
| u16  | Function Pointer[0:15]  | 指向处理函数的指针的低位 |
| u16  | GDT  selector           | 全局描述符中的代码段选择器  |
| u16  | Options                 | (见下表)                 |
| u16  | Function Pointer[16:31] | 指向处理函数的指针的中位 |
| u32  | Function Pointer[32:63] | 指向处理函数的指针的剩余位  |
| u32  | Reserved                |                          |

```rust
pub struct Entry<F> {
    pointer_low: u16,
    gdt_selector: u16,
    options: EntryOptions,
    pointer_middle: u16,
    pointer_high: u32,
    reserved: u32,
    phantom: PhantomData<F>,
}
```

Options的格式如下:

| 位    | 名称                             | 描述 |
| ----- | -------------------------------- | ---- |
| 0-2   | Interrupt Stack Table Index      | 0:不切换栈 1-7:调用此处理程序时，切换到中断栈表中的第n个栈 |
| 3-7   | Reserved                         |      |
| 8     | 0: Interrupt Gate, 1: Trap Gate  | 如果此位为0，调用此处理程序时，禁止中断 |
| 9-11  | must be one                      |      |
| 12    | must be zero                     |      |
| 13-14 | Descriptor Privilege Level (DPL) | 调用此处理程序所必须的最低权限等级 |
| 15    | Present                          |      |

每个异常都有一个预定义的IDT索引，例如无效操作码和页面错误异常的表索引分别为6和14。因此，硬件可针对每个异常自动的加载
相应的IDT条目，OSDev wiki异常表中的"Vector nr."列展示了所有异常的IDT索引。

当发生一个异常时，CPU大致做了如下的事情:
1. 把一些寄存器压入栈中，包括instruction pointer和RFLAGS寄存器(在后续的文章中，我们将会使用这些值)。
2. 从中断描述符表(IDT)中读取相应的条目；例如，当发生页面错误异常时，CPU读取对应的第14个条目。
3. 检查该条目是否存在，不存在情况下，触发double fault。
4. 如果这个条目是Interrupt Gate(条目的第40位未设置)，则禁止硬件中断。
5. 加载特定的GDT选择器到CS段。
6. 跳到对应的处理函数。
目前不必担心步骤4和5，我们将在后续的文章中学习全局描述符表(global descriptor table)和硬件中断。

## IDT类型

我们将使用`x86_64`包中的`InterruptDescriptorTable`结构体作为IDT类型，而不是自建IDT，对应的结构体如下:
```rust
#[repr(C)]
pub struct InterruptDescriptorTable {
    pub divide_by_zero: Entry<HandlerFunc>,
    pub debug: Entry<HandlerFunc>,
    pub non_maskable_interrupt: Entry<HandlerFunc>,
    pub breakpoint: Entry<HandlerFunc>,
    pub overflow: Entry<HandlerFunc>,
    pub bound_range_exceeded: Entry<HandlerFunc>,
    pub invalid_opcode: Entry<HandlerFunc>,
    pub device_not_available: Entry<HandlerFunc>,
    pub double_fault: Entry<HandlerFuncWithErrCode>,
    pub invalid_tss: Entry<HandlerFuncWithErrCode>,
    pub segment_not_present: Entry<HandlerFuncWithErrCode>,
    pub stack_segment_fault: Entry<HandlerFuncWithErrCode>,
    pub general_protection_fault: Entry<HandlerFuncWithErrCode>,
    pub page_fault: Entry<PageFaultHandlerFunc>,
    pub x87_floating_point: Entry<HandlerFunc>,
    pub alignment_check: Entry<HandlerFuncWithErrCode>,
    pub machine_check: Entry<HandlerFunc>,
    pub simd_floating_point: Entry<HandlerFunc>,
    pub virtualization: Entry<HandlerFunc>,
    pub security_exception: Entry<HandlerFuncWithErrCode>,
    // some fields omitted
}
```
这些字段的类型为`idt::Entry<F>`，它是一个表示IDT条目字段的结构体。类型参数`F`定义了期望的处理函数类型。
我们可以看到有些条目要求`HandlerFunc`类型有些要求`HandlerFuncWithErrCode`，页面错误甚至有自己特殊的类型`PageFaultHandlerFunc`。
首先看下`HandlerFunc`类型:
```rust
type HandlerFunc = extern "x86-interrupt" fn(_: InterruptStackFrame);
```
它是`extern "x86-interrupt" fn`类型的一个类型别名，`extern`关键字定义了具有外部调用协议的函数，并经常用来与C代码通信(extern "C" fn)。
但是`x86-interrupt`的调用协议是怎样的呢？

## 中断调用协议

异常和函数调用非常类似: CPU跳转到被调用函数的第一个指令处，并执行它；之后，CPU跳到返回地址并继续执行调用函数剩余的部分。
但是，在异常和函数调用之间有一个很大的不同:函数调用是通过编译器插入`call`指令自愿调用的，但是异常却可能发生在任何指令处。
为了理解这种不同所带来的后果，需要更详细的窥探函数调用。

调用协议指定了函数调用的细节。例如，它们指定了函数参数放在哪里(e.g.在寄存器或者栈中)和结果如何被返回。在x86_64的Linux系统中，
C函数遵循以下规则(在System V ABI中指定的):
* 头六个整数参数通过`rdi`、`rsi`、`rdx`、`rcx`、`r8`和`r9`进行传递
* 附加的参数通过栈进行传递
* 结果通过`rax`进行返回

注意Rust不遵循C ABI(事实上，目前甚至还没有Rust ABI)，所以这些规则仅适用声明为`extern "C" fn`类型的函数。

### preserved和Scratch寄存器

调用协议把寄存器分为了两类: preserved 和 scratch 寄存器
preserved寄存器中的值在经过函数调用后必须保持不变，所以被调用的函数("callee")仅在返回时能够恢复这些寄存器中的值时，才被允许覆盖这些寄存器，所以这些寄存器被称为"callee-saved"。一个常见的模式是在函数开始时，将这些寄存器中的值保存到栈上，仅在函数返回时恢复它们。

与之相对应，被调用的函数可以无限制的覆盖scratch寄存器。如果调用方希望在经过函数调用后，保留scratch寄存器中的值，那么调用方必须在函数调用前和调用后分别备份和恢复它(e.g. 把需要保留的值压在栈中)；所以，scratchi寄存器被称为"caller-saver"。

在X86_64中，C 的调用协议指定了如下的preserved和scratch寄存器:

| preserved                                           | scratch                                                     |
| --------------------------------------------------- | ----------------------------------------------------------- |
| `rbp`, ` rbx`, `rsp`,  `r12`,  `r13`,  `r14`, `r15` | `rax`, `rcx`, `rdx`, `rsi`, `rdi`, `r8`, `r9`, `r10`, `r11` |
| callee-saved                                        | caller-saved                                                |

编译器根据这些规则生成相应的代码。例如，大部分被调用函数将通过`push rbp`指令将`rbp`中的值备份到栈中，作为函数的开始。

### 保留所有寄存器

相比函数调用，异常可能发生在任何指令处，在大部分情况下，如果生成的代码将产生异常，我们甚至在编译的时候都不知道。
例如，如果一个指令产生了栈溢出或者页面异常，编译器无法感知。

因为无法得知异常何时发生，所以在异常发生之前，无法备份任何寄存器的值。这意味着，针对异常处理函数，不能使用依赖 caller-save 寄存器的调用协议。因此，需要一个保留所有寄存器的调用协议。x86-interrupt调用协议就是这样一个协议，它保证了函数返回时，所有寄存器的值恢复到它们原来的大小。
注意这并不意味着所有寄存器中的值都被保存到了函数条目的栈中，实际情况是编译器只备份了那些被函数覆盖的寄存器。
通过这种方法，可以为仅使用了少量寄存器的短函数生成非常高效的代码。

### 中断栈帧

在正常的函数调用中(使用`call`指令)，CPU在跳转到目标函数之前压入返回地址，在函数返回时(使用`ret`指令)，CPU弹出该返回地址，并跳到该地址处。所以，正常函数调用的栈帧看起来像下面的样子:

![](https://os.phil-opp.com/cpu-exceptions/function-stack-frame.svg)

但是，对于异常和中断处理函数，压入返回地址是不够的，因为中断处理函数经常运行在不同的上下文中(例如: stack pointer, CPU flags)，因此，当一个中断发生时，CPU执行如下的步骤:
1. 对齐栈指针: 因为中断会发生在任何指令处，所以栈指针也会拥有各种各样的值；但是，一些CPU指令要求栈指针对齐到16字节的边界(e.g. 一些SSE指令)，因此，CPU在中断后，立即执行这种对齐。
2. 切换栈(在某些情况下): 当CPU特权级别发生变更时，会导致栈切换，例如在用户模式程序中发生CPU异常时。此外，也可以通过中断栈表(Interrupt Stack Table: 后续的文章将会描述)对特定的中断配置栈切换。 
3. 压入旧的栈指针: 当发生中断时，CPU把栈指针(rsp)和栈段(ss)寄存器中的值压入栈中(在对齐栈指针之前)。这使得中断处理函数返回后，能够恢复原始的栈指针。
4. 压入并更新`RFLAGS`寄存器: `RFLAGS`寄存器包含了各种控制和状态位，在进入中断时，CPU 会更改其中的一些值，并压入旧的值。
5. 压入指令指针: 在跳转到中断处理函数之前，CPU 对指令指针(rip)和代码段(cs)进行了入栈。这相当于普通函数调用的中的返回地址入栈。
6. 压入错误码(针对某些异常): 对于一些特定的异常，例如页面错误，CPU 会压入错误成因的错误码。
7. 调用中断处理程序: CPU 从 IDT 对应的字段中读取中断处理函数的地址和段描述符。

所以，中断栈帧形成了如下的样子:

![](https://os.phil-opp.com/cpu-exceptions/exception-stack-frame.svg)

在`x86_64`的包中，`InterruptStackFrame`结构体表示了中断栈帧，它以`&mut`的形式被传递给了中断处理函数，可用于检索异常成因的其他信息。因为只有部分异常压入错误码，所以该结构体没有包含错误码字段。
针对需要错误码的异常，可使用`HandlerFuncWithErrCode`类型的函数，该类函数附有`error_code`参数。

```rust
pub struct InterruptStackFrameValue {
    /// This value points to the instruction that should be executed when the interrupt
    /// handler returns. For most interrupts, this value points to the instruction immediately
    /// following the last executed instruction. However, for some exceptions (e.g., page faults),
    /// this value points to the faulting instruction, so that the instruction is restarted on
    /// return. See the documentation of the [`InterruptDescriptorTable`] fields for more details.
    pub instruction_pointer: VirtAddr,
    /// The code segment selector, padded with zeros.
    pub code_segment: u64,
    /// The flags register before the interrupt handler was invoked.
    pub cpu_flags: u64,
    /// The stack pointer at the time of the interrupt.
    pub stack_pointer: VirtAddr,
    /// The stack segment descriptor at the time of the interrupt (often zero in 64-bit mode).
    pub stack_segment: u64,
}
```

### 幕后的操作

`x86-interrupt`调用协议高度抽象，以至于隐藏了异常处理过程中复杂的细节，但是，这某些情况下，了解这些细节又十分有用，因此，下面对`x86-interrupt`调用协议中，重点的几个功能进行简单的概述:
* 检索参数: 大多数的调用协议希望参数通过寄存器传递，但这对异常处理函数来说是不可能的，因为在覆盖寄存器中的值之前，必须先将其备份到栈上。
而在`x86-interrupt`调用协议中，约定参数位于栈中的特定偏移处。
* 返回使用`iretq`: 因为中断栈帧完全不同于正常函数调用的栈帧，无法使用常规的`ret`指令从处理函数中返回，因为，必须使用`iretq`指令。
* 处理错误码: 由于部分异常压栈错误码，从而使得部分事情复杂起来。错误码改变了栈的对齐方式并在程序返回之前需要出栈，虽然`x84-interrupt`调用协议处理了所有的复杂操作，但是，它不知道哪个处理函数用于哪个异常，所以它需要从函数参数的数量中推导出该信息，这意味着程序员必须给每个异常使用正确的函数类型。幸运的是，`x86_64`包中定义的`InterruptDescriptor`类型确保了函数类型使用的正确性。
* 栈对齐: 有些指令(尤其是SSE指令)要求16字节的栈对齐，每当异常发生的时候，CPU都会保证这种对齐方式。但是，针对入栈错误码的异常，会在栈对齐后，破坏这种对齐方式，在这种情况下，`x86-interrupt`调用协议通过重新对齐栈来解决这个问题。

如果你对其中的更多细节感兴趣: 我们还有一系列的文章，解释了如果使用裸函数处理异常。

## 实现

现在，已经理解理论，是时候在内核中处理 CPU 异常了。首先，创建新的中断模块`src/interrupts.rs`，其次，在该模块的`init_idt`函数内创建新建`InterruptDescriptorTable`:

```rust
// in src/lib.rs

pub mod interrupts;

// in src/interrupts;

use x86_64::structures::idt::InterruptDescriptorTable;

pub fn init_idt() {
   let mut idt = InterruptDescriptorTable::new();
}
```

现在，

### 载入IDT



### 运行它



### 增加Test



## Too much Magic
