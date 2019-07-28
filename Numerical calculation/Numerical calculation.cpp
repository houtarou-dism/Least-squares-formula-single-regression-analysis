#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>


using namespace std;

void deviation(double* a, double* b, double* x, double* y) {     //&x[i], &y[i], &x_average, &y_average, &Element_count

	*a -= *x;
	*b -= *y;
}


int main(void) {

	const int max = 1000;

	double a = 0;
	double b = 0;
	int Element_count = 0;
	int number = 1;
	double* x;     //数値x
	double* y;     //数値y
	double* x_Covariance;     //数値x　偏差
	double* y_Covariance;     //数値y　偏差
	double* Covariance_product;     //偏差の積
	double Covariance_total = 0;     //偏差の合計
	double Covariance = 0;     //偏差
	double x_total = 0;     //xの合計
	double y_total = 0;     //yの合計
	double x_average = 0;     //xの平均
	double y_average = 0;     //yの平均
	double x_Total_deviation = 0;
	double y_Total_deviation = 0;
	double x_dispersion = 0;
	double y_dispersion = 0;
	double x_standard_deviation = 0;
	double y_standard_deviation = 0;

	while (1) {

		cout << "Please enter the number of data to enter ： " << flush;
		cin >> Element_count;

		if(!(Element_count)) {

			cout << "Invalid input(Non-numeric or 0 input)" << endl;
			cin.clear();   //エラー状態をクリア
			cin.ignore(1024, '\n');   //内部バッファのデータを破棄
			continue;   //繰り返し
		}
		else if (Element_count < 0) {
		
			cout << "Invalid input(Negative input)" << endl;
			cin.clear();   //エラー状態をクリア
			cin.ignore(1024, '\n');   //内部バッファのデータを破棄
			continue;
		}

		cin.ignore(1024, '\n');
		break;
	}
	
	x = new double[Element_count];
	y = new double[Element_count];
	x_Covariance = new double[Element_count];
	y_Covariance = new double[Element_count];
	Covariance_product = new double[Element_count];

	cout << "Please enter two values" << endl;

	for (int i = 0; i < Element_count; i++) {
		
		while (1) {

			cout << number << " point  x：";
			number++;

			if (!(cin >> x[i])) {
				cout << "Input more than significant digits or non-numeric input" << endl;
				cin.clear();   //エラー状態をクリア
				cin.ignore(1024, '\n');   //内部バッファのデータを破棄
				continue;   //繰り返し
			}
			cin.ignore(1024, '\n');
			break;
		}
		while (1) {

			cout << "         y：";

			if (!(cin >> y[i])) {
				cout << "Input more than significant digits or non-numeric input" << endl;
				cin.clear();   //エラー状態をクリア
				cin.ignore(1024, '\n');   //内部バッファのデータを破棄
				continue;   //繰り返し
			}
			cin.ignore(1024, '\n');
			break;
		}

		x_Covariance[i] = x[i];
		y_Covariance[i] = y[i];

		x_total += x[i];     //xの合計
		y_total += y[i];     //yの合計

	}

	x_average = x_total / Element_count;     //x, yの平均
	y_average = y_total / Element_count;

	for (int i = 0; i < Element_count; i++) {

		deviation(&x_Covariance[i], &y_Covariance[i], &x_average, &y_average);     //x, y 偏差

		x_Total_deviation += pow(x_Covariance[i], 2.0);     //x, y 偏差二乗合計
		y_Total_deviation += pow(y[i], 2.0);

	}

	x_dispersion = (x_Total_deviation / Element_count);     //x, y 分散
	y_dispersion = (y_Total_deviation / Element_count);

	x_standard_deviation = sqrt(x_dispersion);     //x, y 標準偏差
	y_standard_deviation = sqrt(y_dispersion);

	for (int i = 0; i < Element_count; i++) {

		Covariance_product[i] = x_Covariance[i] * y_Covariance[i];
		Covariance_total += Covariance_product[i];
	}

	Covariance = Covariance_total / Element_count;     //共分散

	a = Covariance / x_dispersion;     //傾き

	b = y_average - a * x_average;     //切片

	ofstream date_file("Least-squares-method.csv");     //ファイル書き込み

	if (b < 0) {

		date_file << "y = " << a << " x - " << b * (-1) << endl;
	}
	else {

		date_file << "y = " << a << " x + " << b << endl;
	}
	
	date_file << endl;
	date_file << endl;
	date_file << endl;
	date_file << "x" << "," << "y" << endl;

	for (int i = 0; i < Element_count; i++) {

		date_file << x[i] << "," << y[i] << endl;
		
	}
	date_file.close();

	cout << endl;

	if (b < 0) {

		printf("Regression line ： y = %.2f x - %.2f\n", a, b * (-1));
	}
	else {

		printf("Regression line ： y = %.2f x + %.2f\n", a, b);
	}

	delete[] x;
	delete[] y;
	delete[] x_Covariance;
	delete[] y_Covariance;
	delete[] Covariance_product;

	return 0;
}