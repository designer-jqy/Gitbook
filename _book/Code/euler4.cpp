/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-11 21:28
* Last modified      :2020-11-11 21:28
* Filename           :euler4.cpp
* Description        :
----------------------------------------------------------*/
#include <iostream>
using namespace std;

int func(int x) {
	int t = 0, raw = x;
	while(x) {
		t = t * 10 + x % 10;
		x /= 10;
	}
	return t == raw;
}// 判断回文数

int main() {
	int ans = 0;
	for (int i = 100; i < 1000; ++i) {
		for (int j = i; j < 1000; ++j) {
			int temp = i*j;
			if(func(temp)) {
				ans = max(ans, temp);
			}
		}
	}
	cout << ans << endl;

	return 0;
}
