/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-12 20:42
* Last modified      :2020-11-12 20:42
* Filename           :euler13.cpp
* Description        :大整数加法，将数字倒序存入数组，方便加减和进位
----------------------------------------------------------*/
#include <iostream>
#include <cstring>
using namespace std;

int num1[105], num2[105], sum[105];
char s1[105], s2[105];               // 输入是字符型的

int main() {
	cin >> s1 >> s2;
	num1[0] = strlen(s1);
	num2[0] = strlen(s2);
	for (int i = 0, j = num1[0]; i < num1[0]; ++i, --j) {
		num1[j] = s1[i] - '0';
	}                
    // 输入123,存入num中为3321，第一个3为123的位数
	for (int i = 0, j = num2[0]; i < num2[0]; ++i, --j) {
		num2[j] = s2[i] - '0';
	}
	sum[0] = max(num1[0], num2[0]);  // 确定两数和的位数
	for (int i = 1; i <= sum[0]; i++) {
		sum[i] = num1[i] + num2[i];  // 两数相加
	}
	for (int i = 1; i <= sum[0]; i++) { 
		if (sum[i] > 9) {            // 处理进位
			sum[i+1] += sum[i] / 10;
			sum[i] %= 10;
			if (i == sum[0]) {           // 最高位发生进位
				sum[0]++;
			}
		}
	}
	for (int i = sum[0]; i > 0; --i) {
		cout << sum[i];
	}
	cout << endl;

	return 0;
}

