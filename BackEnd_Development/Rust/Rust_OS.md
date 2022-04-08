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

| 类型 | 名称                    | 描述                   |
| :--: | ----------------------- | ---------------------- |
| u16  | Function Pointer[0:15]  | 指向处理函数的低位指针 |
| u16  | GDT  selector           |                        |
| u16  | Options                 |                        |
| u16  | Function Pointer[16:31] |                        |
| u32  | Function Pointer[32:63] |                        |
| u32  | Reserved                |                        |



## IDT类型

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
## 中断调用协议

### 保留和暂存寄存器

### 保留所有寄存器

### 中断栈帧

### 幕后的操作

## 实现

### 载入IDT

### 运行它

### 增加Test

## Too much Magic
