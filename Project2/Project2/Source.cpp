#include <iostream>
#include <math.h>

using namespace std;

double f1(double x, double y)
{
	return tan(x * y + 0.4) - x * x;
}
double f2(double x, double y)
{
	return 0.8 * x * x + 2 * y * y - 1;
}
// Матрица Якоби(не обратная)
double W11(double x, double y)
{
	return -2 * x + y * (tan(pow(x * y + 0.4, 2)) + 1);
}
double W21(double x, double y)
{
	return x * tan(pow(x * y + 0.4, 2)) + 1;
}
double W12(double x, double y)
{
	return 1.2 * x;
}
double W22(double x, double y)
{
	return 4 * y;
}
// Обратная матрица
void W(double a[2][2])
{
	double det, aa;
	det = a[0][0] * a[1][1] - a[0][1] * a[1][0];
	aa = a[0][0];
	a[0][0] = a[1][1] / det;
	a[1][1] = aa / det;
	aa = a[0][1];
	a[0][1] = -a[1][0] / det;
	a[1][0] = -aa / det;
}

void MN(double x, double y, double eps)
{
	int i = 1;
	double a[2][2], dx, dy, b[2], norm;
	do
	{
		a[0][0] = W11(x, y);
		a[0][1] = W12(x, y);
		a[1][0] = W21(x, y);
		a[1][1] = W22(x, y);
		W(a);
		dx = -a[0][0] * f1(x, y) + -a[0][1] * f2(x, y);
		dy = -a[1][0] * f1(x, y) + -a[1][1] * f2(x, y);
		x = x + dx;
		y = y + dy;
		b[0] = f1(x, y);
		b[1] = f2(x, y);
		norm = sqrt(b[0] * b[0] + b[1] * b[1]);
		i++;
		cout << "х[" << i - 1 << "] = " << x << endl << "y[" << i - 1 << "] = " << y << endl << endl;
	} while (norm >= eps);
	cout << "Количество итераций = " << i - 1 << endl;
}
void main()
{
	setlocale(LC_CTYPE, "Rus");
	double x, y, eps;
	cout << "x = "; cin >> x;
	cout << "y = "; cin >> y;
	cout << "eps = "; cin >> eps;
	MN(x, y, eps); cout << endl;
	system("PAUSE");
}