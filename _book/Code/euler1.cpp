/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-11 20:45
* Last modified      :2020-11-11 20:45
* Filename           :euler.cpp
* Description        :
----------------------------------------------------------*/
#include <iostream>
using namespace std;

int main() {
	int t3 = (3 + 999) * 999 / 3 / 2;
	int t5 = (5 + 995) * 995 / 5 / 2;
	int t15 = (15 + 990) * 990 / 15 / 2;
	cout << t3 + t5 - t15 << endl; 

	return 0;
}
