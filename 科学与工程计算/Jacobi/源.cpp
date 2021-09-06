#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int sum1(int a[], double b[], int i) {
	int sum = 0;
	for (int j = 0; i < i - 1; j++)
		sum += a[j] * b[j];
	return sum;
}
int sum2(int a[], double b[], int i) {
	int sum = 0;
	for (int j = i; j < 3; j++)
		sum += a[j] * b[j];
	return sum;
}
bool compare(double x[], double y[]) {
	double x1, x2, x3, max;
	x1 = fabs(y[0] - x[0]);
	x2 = fabs(y[1] - x[1]);
	x3 = fabs(y[2] - x[2]);
	max = x1 > x2 ? x1 : x2;
	max = max > x3 ? max: x3;
	if (max >= 0.0001) return 1;
	else return 0;
}
int main() {
	int a[3][3] = { 0 }, b[3] = {0};
	a[0][0] = 5;	a[0][1] = 2;	a[0][2] = 1;	b[0] = -12;
	a[1][0] = -1;	a[1][1] = 4;	a[1][2] = 2;	b[1] = 20;
	a[2][0] = 2;	a[2][1] = -3;	a[2][2] = 10;	b[2] = 3;
	double x[3] = { 1 };
	double y[3] = { 2 };
	int n = 0;
	while (compare(x,y)) {
		for (int i = 0; i < 3; i++)
			y[i] = x[i];
		for (int i = 0; i < 3; i++)
			x[i] = 1.0 * (b[i] - sum1(a[i], y, i) - sum2(a[i], y, i)) / a[i][i];
		n++;
		cout << "µü´ú´ÎÊý£º" << n << endl;
		cout << "x1: " << x[0] << endl
			 << "x2: " << x[1] << endl
			 << "x3: " << x[2] << endl
			 << endl;
	}
	return 0;
}