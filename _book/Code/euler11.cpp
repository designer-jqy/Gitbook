/*--------------------------------------------------------
* Author             :Jiaq.yang
* Email              :thinklook1@outlook.com
* Create time        :2020-11-12 14:49
* Last modified      :2020-11-12 14:49
* Filename           :euler11.cpp
* Description        :
----------------------------------------------------------*/
#include <iostream>
using namespace std;

int dir_x[4] = {0,1,1,1};
int dir_y[4] = {1,1,0,-1};

int arr[30][30];

int main() {
	long ans = 0;
	for (int i = 5; i <25; i++) {
		for (int j = 5; j < 25; j++) {
			cin>>arr[i][j];
		}
	}
	for (int i = 5; i < 25; i++) {
		for (int j = 5; j < 25; j++) {
			for (int k = 0; k < 4; k++) {
				long temp = arr[i][j];
				for (int r = 1; r < 4; r++) {
					int x = i + dir_x[k] * r;
					int y = j + dir_y[k] * r;
					temp *= arr[x][y];
				}
				ans = max(ans, temp);
			}
		}
	}
	cout << ans << endl;



	return 0;
}
