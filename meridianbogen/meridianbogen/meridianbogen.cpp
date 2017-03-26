// meridianbogen.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "cmath"
#include <iostream>
#include <stdio.h>

using namespace std;


double B(double phi, double a, double b) {
	double n = (a - b) / (a + b);

	double alpha = (a + b) / 2.0 * (1.0 + 1.0 / 4.0 * n*n + 1.0 / 64.0 * pow(n, 4));
	double beta = -3.0 / 2.0 * n + 9.0 / 16.0 * n*n*n - 3.0 / 32.0 * pow(n, 5);
	double gamma = 15.0 / 16.0 * n*n - 15.0 / 32.0 * pow(n, 4);
	double delta = -35.0 / 48.0 * pow(n, 3) + 105.0 / 256.0 * pow(n, 5);
	double eps = 315.0 / 512.0 * pow(n, 4);

	double bbb = alpha * (phi + beta*sin(2.0 * phi) + gamma*sin(4.0 * phi) + delta*sin(6.0 * phi) + eps*sin(8.0 * phi));

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
	cout << "Grad Eingeben" << endl;
	cin >> grad;
	cout << "Minuten Eingeben" << endl;
	cin >> min;
	cout << "Sekunden Eingeben" << endl;
	cin >> sec;
	phi = (grad + (min + sec / 60.0) / 60.0)*pi/180.0;
	double bout = B(phi,a,b);
	printf("B = %12.6fl\n", bout);
	system("pause");
	return 0;
}

