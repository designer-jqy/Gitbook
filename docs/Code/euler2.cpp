/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-11 21:11
* Last modified      :2020-11-11 21:11
* Filename           :euler2.cpp
* Description        :
----------------------------------------------------------*/
#include <iostream>
using namespace std;

int main() {
	int a = 1, b = 1, c = 2, ans = 0;
	while (c < 4000000) {
		if (!(c % 2)) ans += c;
		c = b + c;
		a = b;
		b = c - b;
	}

	cout << ans << endl;
	return 0;
}
