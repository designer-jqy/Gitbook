/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-12 10:50
* Last modified      :2020-11-12 10:50
* Filename           :euler8.cpp
* Description        :
----------------------------------------------------------*/
#include <iostream>
using namespace std;

char num[1005];
long long ans, now = 1;

int main() {
	int zero_cnt = 0;
	cin >> num;
	for (int i = 0; i < 1000; i++) {
		if (i < 13) {
			now *= num[i] - '0';
		} else {
			if (num[i] == '0') {
				zero_cnt++;
			} else {
				now *= num[i] - '0';
			}
			if (num[i-13] == '0') {
				zero_cnt--;
			} else {
				now /= num[i-13] - '0';
			}
		}
		if (!zero_cnt) {
			ans = max(ans, now);
		}
	}

	cout << ans << endl;

	return 0;
}
