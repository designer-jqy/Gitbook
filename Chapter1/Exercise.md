# Chapter1：Exercise
## 位运算
### 计算整数二进制中1的个数（以int类型为例，32个bit）
#### 方法1：移动

1. 通过移动数字计算

   ```c++
   /*把要求的数字不停的往右移，然后再和1进行与运算*/
   void bitcount(int n){
       int count = 0;
       for(int i = 0; i < 32; i++){
           if(((n>>i) & 1) == 1){
               count++;
           }
       }
   
       cout << count << endl;
   }
   ```
   
2. 通过移动1来计算

   ```C++
   /*保持要求的数字不变，把1不停的往左移，然后再和移动后的1进行与运算*/
   void bitcount(int n){
       int count = 0;
       for(int i = 0; i < 32; i++){
           if(((1<<i) & n) != 0){
               count++;
           }
       }
   
       cout << count << endl;
   }
   ```

#### 方法2：不通过移动

1. 消1

   ```c++
   void bitcount(int n){
       /*n&(n-1)可以把n最右边的1给消除掉*/
       int count = 0;
       while( n!= 0 ){
           n &= n-1;
           count++;
       }
   
       cout << count << endl;
   }
   ```

   ```c++
   /*递归方法*/
   int bitcount(int n){
       return n == 0 ? 0 : 1+bitcount(n&(n-1));
   }
   ```

2. 查表

   ```c++
   /*先把0-15转化为2进制，记录下每个数字包含1的个数，再构成一张表，然后再把数字n每4位进行一次计算*/
   void bitcount(int n){
       //table是0-15转化为二进制时1的个数
       int table[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
       int count = 0;
       while(n != 0){
           count += table[n & 0xf];
           n >>= 4;
       }
   
       cout << count << endl;
   }
   ```

   