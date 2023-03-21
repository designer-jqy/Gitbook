#include<iostream>
#include<cstdio>
#include<stdlib.h>
using namespace std;

int main()
{
    int i1=30;
    int i2=40;
    int * const pi=&i1;//这里的pi指针式常量。
    // pi=&i2;     //注意这里，pi不能再这样重新赋值了，即不能再指向另一个新地址。所以我已经注释了它。
    printf("%d\n", *pi ) ;   //输出是30
    i1=80;     //5.想想看：这里能用*pi=80;来代替吗？可以，这里可以通过*pi修改i1的值。
    printf("%d\n", *pi ) ;   //输出是80
    return 0;
}