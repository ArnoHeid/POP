// regression.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//


#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

double max(std::vector<double> values) {
	double max = 0;

	for (size_t i = 0; i < values.size(); i++)
	{
		if (values[i] > max) {
			max = values[i];
		}
	}
	return max;
}

double min(std::vector<double> values) {
	double min = std::numeric_limits<double>::max();

	for (size_t i = 0; i < values.size(); i++)
	{
		if (values[i] < min) {
			min = values[i];
		}
	}
	return min;
}

double mean(std::vector<double> values) {
	double sum = 0;
	for (size_t i = 0; i < values.size(); i++)
	{
		sum += values[i];
	}
	return sum / values.size();
}

class mess {
	std::vector<double> xValues;
	std::vector<double> yValues;


public:
	void addElement(double x, double y) {
		xValues.push_back(x);
		yValues.push_back(y);

	}

	void calcStatisics() {
		cout << fixed << "Min X =" << min(xValues) << endl;
		cout << fixed << "Min Y =" << min(yValues) << endl;
		cout << fixed << "Max X =" << max(xValues) << endl;
		cout << fixed << "Max Y =" << max(yValues) << endl;
		cout << fixed << "Mittel X =" << mean(xValues) << endl;
		cout << fixed << "Mittel Y =" << mean(yValues) << endl;
	}

};



int main(int argc, char *argv[])
{
	ifstream   infile;
	ofstream  outfile;
	double       x, y;
	const int  bufflen = 1024;
	char          buffer[bufflen + 1];
	mess messwerte;

	infile.open("messreihe01.dat");
	if (!infile) {
		cout << "File open error."; return(-1);
	}
	outfile.open("out.dat");
	if (!outfile) {
		cout << "File open error."; return(-2);
	}


	while (infile.getline(buffer, bufflen, '\n'))
	{
		if (buffer[0] == '#') {
			outfile << buffer << "\n";
		}
		else {
			if (sscanf(buffer, "%lf %lf", &x, &y) == 2)
			{

				messwerte.addElement(x, y);

				cout << fixed << "x= " << x << " y= " << y << "\n";
				outfile << fixed << setw(9) << setprecision(3) << y;
				outfile << setw(1) << " ";
				outfile << fixed << setw(9) << setprecision(3) << x;
				outfile << setw(1) << "\n";
			}
		}
	}

	messwerte.calcStatisics();
	
	system("pause");
	
	infile.close();
	outfile.close();



}
