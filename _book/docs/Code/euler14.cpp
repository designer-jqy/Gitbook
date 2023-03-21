/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-12 15:16
* Last modified      :2020-11-12 15:16
* Filename           :euler14.cpp
* Description        :
----------------------------------------------------------*/
// 递归+记忆化 约等于 递推
#include <iostream>
using namespace std;

#define num 3000002
int mem[num]; 

int func(long long n) {
	if (n == 1) return 1;
	if (n < num && mem[n]) return mem[n];
	int temp = 0;
	if (n % 2 == 0) {
		temp = func(n/2) + 1;
	} else {
		temp = func(3*n+1) + 1;
	}
	if (n < num) {
		mem[n] = temp;
	}
	return temp;
}

int main() {
	int ans = 1;
	for (int i = 2; i <= 1000000; i++) {
		if (func(ans) < func(i)) {
			ans = i;
		}
	}
	cout << ans << endl;
	return 0;
}
