# Rust
Statics are initialized at compile time, in contrast to normal variables that are initialized at run time.
The 'static lifetime specifies that the reference is valid for the whole program run time.

## raw pointer
Rust’s ownership rules don’t allow a mutable reference at the same time as any immutable references. With raw pointers, we can create a mutable pointer and an immutable pointer to the same location and change data through the mutable pointer, potentially creating a data race. Be careful!


# Rust OS

## CPU Exceptions

在各种各样错误的情况下，都可能发生CPU异常；例如，访问无效的内存地址或者除零的时候。为了处理这些异常，
我们需要设置一个中断描述符表，其中的描述符指向了对应的处理函数。在这篇文章的最后，我们的内核将能够捕获
断点异常，并在之后恢复正常执行。

### 概述

一个异常标识着当前指令的某些错误。例如，如果当前的指令尝试除0，那么CPU将产生一个异常。
当一个异常发生的时候，CPU中断它当前的工作并根据异常类型调用特定的异常处理函数。
在x86架构上，大约有20种不同的CPU异常类型。最重要的几个是:
* **Page Fault**

* **Invalid Opcode**

* **General Protection Fault**

* **Double Fault**

* **Triple Fault**

