#include <stdio.h>
#include <stdlib.h>
int isAsciiDigit(int x) {
  int temp = temp ^ 0x30;
  int result = temp & (temp ^ 1) & (temp >> 1 ^ 1) & (temp >> 2 ^ 1) & (temp >> 3 ^ 1);
  return !result;
}

char *GetMemory(void) {
    char p[] = "hello world!";
    return p;
}

int Test(void) {
    double a = 2.55;
    return a;
}



int main() {
    // printf("%d\n", isAsciiDigit(0x05));
    // printf("%d\n", Test());
    printf("%lu\n", sizeof(long));

    return 0;
}
/*------------------------------
int a = -3;
    a += 1;
    printf("%d\n", a>>1);
    return 0;
1101           -3
加偏移1
再进行右移一位   -1
*-------------------------------*/