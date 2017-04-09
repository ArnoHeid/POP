// regression.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//


#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

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

double median(std::vector<double> values) {
	double median;
	size_t size = values.size();
	sort(values.begin(), values.end());
	if (size % 2 == 0) {
		median = (values[size / 2 - 1] + values[size / 2]) / 2;
	}
	else {
		median = values[size / 2];
	}
	return median;
}

double varianz(std::vector<double> values) {
	double mean_value = mean(values);
	double sum = 0;
	for (size_t i = 0; i < values.size(); i++)
	{
		sum += pow(values[i] - mean_value, 2);
	}
	return sum / (values.size() - 1);
}

double stabwa(std::vector<double> values) {
	return sqrt(varianz(values));
}

double sch_and_kur(std::vector<double> values, int power) {
	double mean_value = mean(values);
	double stabwa_values = stabwa(values);
	double sum = 0;
	for (size_t i = 0; i < values.size(); i++)
	{
		sum += pow((values[i] - mean_value) / stabwa_values, power);
	}
	return sum / (values.size() - 1);
}

double kovar(std::vector<double> values_x, std::vector<double> values_y) {
	double mean_x = mean(values_x);
	double mean_y = mean(values_y);
	double sum;
	for (size_t i = 0; i < values_x.size(); i++)
	{
		sum += (values_x[i] - mean_x) * (values_y[i] - mean_y);
	}
	return sum / (values_x.size() - 1);
}

std::vector<double> res(std::vector<double> values_x, std::vector<double> values_y) {
	double b = kovar(values_x, values_y) / pow(varianz(values_x), 2);
	double a = mean(values_y) - b*mean(values_x);
	std::vector<double> residuum;
	for (size_t i = 0; i < values_x.size(); i++)
	{
		residuum.push_back(a + b*values_x[i] - values_y[i]);
	}
	return residuum;
}

double rest(std::vector<double> residuum) {
	double sum = 0;
	for (size_t i = 0; i < residuum.size(); i++)
	{
		sum += residuum[i] * residuum[i];
	}
	return sum / (residuum.size() - 2);
}

std::vector<double> stabwa_reg(std::vector<double> values_x, std::vector<double> values_y) {
	double stabwa_values_x = stabwa(values_x);
	double stabwa_values_y = stabwa(values_y);
	double kovarianz = kovar(values_x, values_y);
	std::vector<double> stabwa;
	for (size_t i = 0; i < values_x.size(); i++)
	{
		stabwa.push_back(stabwa_values_x*stabwa_values_x + stabwa_values_y*stabwa_values_y*values_x[i] * values_x[i] + 2 * values_x[i] * kovarianz);
	}
	return stabwa;
}



class mess {
	std::vector<double> xValues;
	std::vector<double> yValues;
	std::vector<double> residuum;
	std::vector<double> stabwa_y;

private:



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
		cout << fixed << "Median X =" << median(xValues) << endl;
		cout << fixed << "Median Y =" << median(yValues) << endl;
		cout << fixed << "Varianz X =" << varianz(xValues) << endl;
		cout << fixed << "Varianz Y =" << varianz(yValues) << endl;
		cout << fixed << "Schiefe X =" << sch_and_kur(xValues, 3) << endl;
		cout << fixed << "Schiefe Y =" << sch_and_kur(yValues, 3) << endl;
		cout << fixed << "Kurtosis X =" << sch_and_kur(xValues, 4) << endl;
		cout << fixed << "Kurtosis Y =" << sch_and_kur(yValues, 4) << endl;
		cout << fixed << "Kovarianz =" << kovar(xValues,yValues) << endl;


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
