/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-12 21:50
* Last modified      :2020-11-12 21:50
* Filename           :euler25.cpp
* Description        :
----------------------------------------------------------*/
#include <iostream>
using namespace std;

int a[1001];
int b[1001];
int sum[1005];

int main() {
	a[0] = 1;
	a[1] = 1;
	b[0] = 1;
	b[1] = 1;
	int num = 2;
	while (sum[0] < 1000) {
		num++;
		sum[0] = max(a[0], b[0]);
		for (int i = 1; i <= sum[0]; ++i) {
			sum[i] = a[i] + b[i];
		}
		for (int i = 1; i <= sum[0]; ++i) {
			if (sum[i] > 9) {
				sum[i+1] += sum[i] / 10;
				sum[i] %= 10;
				if (i == sum[0]) {
					sum[0]++;
				}
			}
		}
		for (int i = 0; i <= b[0]; i++) {
			a[i] = b[i];
		}
		for (int i = 0; i <= sum[0]; i++) {
			b[i] = sum[i];
		}

	}
	cout << num << endl;

	return 0;
}
