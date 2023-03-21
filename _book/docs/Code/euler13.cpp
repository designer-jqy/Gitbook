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

int num1[155], num2[155], sum[155];

int main() {
	string s1;                           // 输入是字符型的
	for (int m = 0; m < 100; m++) {
		s1 = "";
		cin >> s1;
		num1[0] = s1.size();
		for (int i = 0, j = num1[0]; i < num1[0]; ++i, --j) {
			num1[j] = s1[i] - '0';
		}                
		// 输入123,存入num中为3321，第一个3为123的位数
		sum[0] = max(num1[0], num2[0]);  // 确定两数和的位数
		for (int i = 1; i <= sum[0]; i++) {
			sum[i] = num1[i] + num2[i];  // 两数相加
		}
		for (int i = 1; i <= sum[0]; i++) { 
			if (sum[i] > 9) {            // 处理进位
				sum[i+1] += sum[i] / 10;
				sum[i] %= 10;
				if (i == sum[0]) {       // 最高位发生进位
					sum[0]++;
				}
			}
		}
		for (int i = 0; i <= sum[0]; ++i) {
			num2[i] = sum[i];
		}
		memset(num1, 0, sizeof(num1));
	}
	for (int i = num2[0]; i > num2[0] - 10; --i) {
		cout << num2[i];
	}
	cout << endl;

	return 0;
}

