// meridianbogen.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "cmath"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>



using namespace std;

double B_super(double phi, double a, double b) {
	double n = (a - b) / (a + b);

	double n2 = n*n;
	double n3 = n2*n;
	double n4 = n3*n;
	double n5 = n4*n;

	return ((a + b) / 2.0 * (1.0 + 1.0 / 4.0 * n2 + 1.0 / 64.0 * n4)) * (phi + (-3.0 / 2.0 * n + 9.0 / 16.0 * n3 - 3.0 / 32.0 * n5)*sin(2.0 * phi) + (15.0 / 16.0 * n2 - 15.0 / 32.0 * n4)*sin(4.0 * phi) + (-35.0 / 48.0 * n3 + 105.0 / 256.0 * n5)*sin(6.0 * phi) + (315.0 / 512.0 * n4)*sin(8.0 * phi));
}


double B(double phi, double a, double b) {
	double n = (a - b) / (a + b);

	double n2 = n*n;
	double n3 = n2*n;
	double n4 = n3*n;
	double n5 = n4*n;

	double alpha = (a + b) / 2.0 * (1.0 + 1.0 / 4.0 * n2 + 1.0 / 64.0 * n4);
	double beta = -3.0 / 2.0 * n + 9.0 / 16.0 * n3 - 3.0 / 32.0 * n5;
	double gamma = 15.0 / 16.0 * n2 - 15.0 / 32.0 * n4;
	double delta = -35.0 / 48.0 * n3 + 105.0 / 256.0 * n5;
	double eps = 315.0 / 512.0 * n4;

	return alpha * (phi + beta*sin(2.0 * phi) + gamma*sin(4.0 * phi) + delta*sin(6.0 * phi) + eps*sin(8.0 * phi));
}


double B_alt(double phi, double a, double b) {
	double n = (a - b) / (a + b);

	double alpha = (a + b) / 2.0 * (1.0 + 1.0 / 4.0 * pow(n,2) + 1.0 / 64.0 * pow(n,4));
	double beta = -3.0 / 2.0 * n + 9.0 / 16.0 * pow(n,3) - 3.0 / 32.0 * pow(n,5);
	double gamma = 15.0 / 16.0 * pow(n,2) - 15.0 / 32.0 * pow(n,4);
	double delta = -35.0 / 48.0 * pow(n,3) + 105.0 / 256.0 * pow(n,5);
	double eps = 315.0 / 512.0 * pow(n,4);



	return alpha * (phi + beta*sin(2.0 * phi) + gamma*sin(4.0 * phi) + delta*sin(6.0 * phi) + eps*sin(8.0 * phi));
}


int main()
{
	double pi = 4.0*atan2(1.0, 1.0);
	double a = 6377397.15508;
	double b = 6356078.96290;
	double phi = 0.822390395076852;
	double grad;
	double min;
	double sec;

	//typedef std::chrono::high_resolution_clock Time;
	//typedef std::

	time_t start, end;

	cout << "Grad Eingeben" << endl;
	cin >> grad;
	cout << "Minuten Eingeben" << endl;
	cin >> min;
	cout << "Sekunden Eingeben" << endl;
	cin >> sec;
	phi = (grad + (min + sec / 60.0) / 60.0)*pi/180.0;

	auto start_time = chrono::high_resolution_clock::now();
	double bout;

	for (size_t i = 0; i < 10000000; i++)
	{
		bout = B_alt(phi,a,b);

	}

	auto end_time = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << ":\n";
	system("pause");
	start_time = chrono::high_resolution_clock::now();

	for (size_t i = 0; i < 10000000; i++)
	{
		bout = B(phi, a, b);

	}

	end_time = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << ":\n";

	system("pause");
	start_time = chrono::high_resolution_clock::now();

	for (size_t i = 0; i < 10000000; i++)
	{
		bout = B_super(phi, a, b);

	}

	end_time = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << ":\n";


	printf("B = %12.6f\n", bout);
	system("pause");
	return 0;
}

