/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-12 11:01
* Last modified      :2020-11-12 11:01
* Filename           :euler11.cpp
* Description        :
----------------------------------------------------------*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define max_h 2000000

long long arr[max_h + 5] = {0};

int main() {
	long long ans = 0;
	long long i = 0, j = 0;
	for (i = 2; i <= max_h; i++) {
		if (arr[i]) continue;
		//arr[++arr[0]] = i;
		ans += i;
		for (j = i*2; j <= max_h && i <= 1000000; j+=i) {
			arr[j] = 1;
		}
	}
	cout << ans << endl;
	//printf("%I64d\n", ans);

	return 0;
}
