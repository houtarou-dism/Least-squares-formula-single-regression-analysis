#include <cstdio>
#include <iostream>
#include <math.h>

using namespace std;

void deviation(double* a, double* b, double* x, double* y) {     //&x[i], &y[i], &x_average, &y_average, &Element_count

	*a -= *x;
	*b -= *y;
}


int main(void) {

	int Element_count = 0;
	double x[100] = { 0 };     //���lx
	double y[100] = { 0 };    //���ly
	double x_Covariance[100] = { 0 };     //���lx�@�΍�
	double y_Covariance[100] = { 0 };     //���ly�@�΍�
	double Covariance_product[100] = { 0 };     //�΍��̐�
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

		cout << "Please enter the number of data less than 100�F " << flush;

		if (!(cin >> Element_count)) {

			cout << "Input more than significant digits or non-numeric input" << endl;
			cin.clear();   //�G���[��Ԃ��N���A
			cin.ignore(1024, '\n');   //�����o�b�t�@�̃f�[�^��j��
			continue;   //�J��Ԃ�
		}

		if (Element_count > 100) {

			cout << "A number greater than 100 has been entered" << endl;
		}
		cin.ignore(1024, '\n');
		break;
	}


	cout << "Please enter two values" << endl;

	for (int i = 1; i <= Element_count; i++) {

		while (1) {

			cout << i << " point  x�F";

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


	for (int i = 1; i <= Element_count; i++) {

		deviation(&x_Covariance[i], &y_Covariance[i], &x_average, &y_average);     //x, y �΍�

		x_Total_deviation += pow(x[i], 2.0);     //x, y �΍���捇�v
		y_Total_deviation += pow(y[i], 2.0);

	}

	x_dispersion = (x_Total_deviation / Element_count);     //x, y ���U
	y_dispersion = (y_Total_deviation / Element_count);

	x_standard_deviation = sqrt(x_dispersion);     //x, y �W���΍�
	y_standard_deviation = sqrt(y_dispersion);

	for (int i = 1; i <= Element_count; i++) {

		Covariance_product[i] = x_Covariance[i] * y_Covariance[i];
		Covariance_total += Covariance_product[i];
	}

	Covariance = Covariance_total / Element_count;

	for (int i = 1; i <= Element_count; i++) {

		printf("%lf", x[i]);
		printf("\n");
		printf("%lf", y[i]);
		printf("\n");

	}




	return 0;
}