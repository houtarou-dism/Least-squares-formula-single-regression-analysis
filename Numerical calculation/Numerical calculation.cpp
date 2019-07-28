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
	double* x;     //���lx
	double* y;     //���ly
	double* x_Covariance;     //���lx�@�΍�
	double* y_Covariance;     //���ly�@�΍�
	double* Covariance_product;     //�΍��̐�
	double Covariance_total = 0;     //�΍��̍��v
	double Covariance = 0;     //�΍�
	double x_total = 0;     //x�̍��v
	double y_total = 0;     //y�̍��v
	double x_average = 0;     //x�̕���
	double y_average = 0;     //y�̕���
	double x_Total_deviation = 0;
	double y_Total_deviation = 0;
	double x_dispersion = 0;
	double y_dispersion = 0;
	double x_standard_deviation = 0;
	double y_standard_deviation = 0;

	while (1) {

		cout << "Please enter the number of data to enter �F " << flush;
		cin >> Element_count;

		if(!(Element_count)) {

			cout << "Invalid input(Non-numeric or 0 input)" << endl;
			cin.clear();   //�G���[��Ԃ��N���A
			cin.ignore(1024, '\n');   //�����o�b�t�@�̃f�[�^��j��
			continue;   //�J��Ԃ�
		}
		else if (Element_count < 0) {
		
			cout << "Invalid input(Negative input)" << endl;
			cin.clear();   //�G���[��Ԃ��N���A
			cin.ignore(1024, '\n');   //�����o�b�t�@�̃f�[�^��j��
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

			cout << number << " point  x�F";
			number++;

			if (!(cin >> x[i])) {
				cout << "Input more than significant digits or non-numeric input" << endl;
				cin.clear();   //�G���[��Ԃ��N���A
				cin.ignore(1024, '\n');   //�����o�b�t�@�̃f�[�^��j��
				continue;   //�J��Ԃ�
			}
			cin.ignore(1024, '\n');
			break;
		}
		while (1) {

			cout << "         y�F";

			if (!(cin >> y[i])) {
				cout << "Input more than significant digits or non-numeric input" << endl;
				cin.clear();   //�G���[��Ԃ��N���A
				cin.ignore(1024, '\n');   //�����o�b�t�@�̃f�[�^��j��
				continue;   //�J��Ԃ�
			}
			cin.ignore(1024, '\n');
			break;
		}

		x_Covariance[i] = x[i];
		y_Covariance[i] = y[i];

		x_total += x[i];     //x�̍��v
		y_total += y[i];     //y�̍��v

	}

	x_average = x_total / Element_count;     //x, y�̕���
	y_average = y_total / Element_count;

	for (int i = 0; i < Element_count; i++) {

		deviation(&x_Covariance[i], &y_Covariance[i], &x_average, &y_average);     //x, y �΍�

		x_Total_deviation += pow(x_Covariance[i], 2.0);     //x, y �΍���捇�v
		y_Total_deviation += pow(y[i], 2.0);

	}

	x_dispersion = (x_Total_deviation / Element_count);     //x, y ���U
	y_dispersion = (y_Total_deviation / Element_count);

	x_standard_deviation = sqrt(x_dispersion);     //x, y �W���΍�
	y_standard_deviation = sqrt(y_dispersion);

	for (int i = 0; i < Element_count; i++) {

		Covariance_product[i] = x_Covariance[i] * y_Covariance[i];
		Covariance_total += Covariance_product[i];
	}

	Covariance = Covariance_total / Element_count;     //�����U

	a = Covariance / x_dispersion;     //�X��

	b = y_average - a * x_average;     //�ؕ�

	ofstream date_file("Least-squares-method.csv");     //�t�@�C����������

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

		printf("Regression line �F y = %.2f x - %.2f\n", a, b * (-1));
	}
	else {

		printf("Regression line �F y = %.2f x + %.2f\n", a, b);
	}

	delete[] x;
	delete[] y;
	delete[] x_Covariance;
	delete[] y_Covariance;
	delete[] Covariance_product;

	return 0;
}