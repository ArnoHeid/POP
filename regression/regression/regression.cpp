#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

double max(vector<double> values)
{
	double max = 0;

	for (size_t i = 0; i < values.size(); i++)
	{
		if (values[i] > max)
		{
			max = values[i];
		}
	}
	return max;
}

double min(vector<double> values)
{
	double min = numeric_limits<double>::max();

	for (size_t i = 0; i < values.size(); i++)
	{
		if (values[i] < min)
		{
			min = values[i];
		}
	}
	return min;
}

double mean(vector<double> values)
{
	double sum = 0;
	for (size_t i = 0; i < values.size(); i++)
	{
		sum += values[i];
	}
	return sum / static_cast<double>(values.size());
}

double median(vector<double> values)
{
	double median;
	size_t size = values.size();
	sort(values.begin(), values.end());
	if (size % 2 == 0)
	{
		median = (values[size / 2 - 1] + values[size / 2]) / 2;
	}
	else
	{
		median = values[size / 2];
	}
	return median;
}

double varianz(vector<double> values)
{
	double mean_value = mean(values);
	double sum = 0;
	for (size_t i = 0; i < values.size(); i++)
	{
		sum += pow(values[i] - mean_value, 2);
	}
	return sum / static_cast<double>(values.size() - 1);
}

double stabwa(vector<double> values)
{
	return sqrt(varianz(values));
}

double sch_and_kur(vector<double> values, int power)
{
	double mean_value = mean(values);
	double stabwa_values = stabwa(values);
	double sum = 0;
	for (size_t i = 0; i < values.size(); i++)
	{
		sum += pow((values[i] - mean_value) / stabwa_values, power);
	}
	return sum / static_cast<double>(values.size() - 1);
}

double kovar(vector<double> values_x, vector<double> values_y)
{
	double mean_x = mean(values_x);
	double mean_y = mean(values_y);
	double sum = 0;
	for (size_t i = 0; i < values_x.size(); i++)
	{
		sum += (values_x[i] - mean_x) * (values_y[i] - mean_y);
	}
	return sum / static_cast<double>(values_x.size() - 1);
}

vector<double> res(vector<double> values_x, vector<double> values_y)
{
	double b = kovar(values_x, values_y) / varianz(values_x);
	double a = mean(values_y) - b * mean(values_x);
	vector<double> residuum;
	for (size_t i = 0; i < values_x.size(); i++)
	{
		residuum.push_back(a + b * values_x[i] - values_y[i]);
	}
	return residuum;
}

double rest(vector<double> residuum)
{
	double sum = 0;
	for (size_t i = 0; i < residuum.size(); i++)
	{
		sum += residuum[i] * residuum[i];
	}
	return sqrt(sum / static_cast<double>(residuum.size() - 2));
}

vector<double> stabwa_reg(vector<double> values_x, vector<double> values_y)
{
	double stabwa_values_x = stabwa(values_x);
	double stabwa_values_y = stabwa(values_y);
	double kovarianz = kovar(values_x, values_y);
	vector<double> stabwa;
	for (size_t i = 0; i < values_x.size(); i++)
	{
		stabwa.push_back(stabwa_values_x * stabwa_values_x + stabwa_values_y * stabwa_values_y * values_x[i] * values_x[i] + 2 * values_x[i] * kovarianz);
	}
	return stabwa;
}


class mess
{
	vector<double> xValues;
	vector<double> yValues;
	vector<double> residuum;
	vector<double> stabwa_y;

private:


public:
	void addElement(double x, double y)
	{
		xValues.push_back(x);
		yValues.push_back(y);
	}

	void calcStatisics()
	{
		ofstream outfile("residuum.csv");
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
		double stabwaX = stabwa(xValues);
		double stabwaY = stabwa(yValues);
		cout << fixed << "Stabwa X =" << stabwaX << endl;
		cout << fixed << "Stabwa Y =" << stabwaY << endl;
		cout << fixed << "Schiefe X =" << sch_and_kur(xValues, 3) << endl;
		cout << fixed << "Schiefe Y =" << sch_and_kur(yValues, 3) << endl;
		cout << fixed << "Kurtosis X =" << sch_and_kur(xValues, 4) << endl;
		cout << fixed << "Kurtosis Y =" << sch_and_kur(yValues, 4) << endl;
		double koVarianz = kovar(xValues, yValues);
		cout << fixed << "Kovarianz =" << koVarianz << endl;
		double korKof = koVarianz / (stabwaX * stabwaY);
		cout << fixed << "Korrel Kof. =" << korKof << endl;
		cout << fixed << "Bestimmtheitsmaß =" << pow(korKof, 2) << endl;
		vector<double> residuum = res(xValues, yValues);
		double b = kovar(xValues, yValues) / varianz(xValues);
		double a = mean(yValues) - b * mean(xValues);
		cout << "Y-Achsenabschnitt: " << a << endl;
		cout << "Steigung: " << b << endl;
		cout << "Residuuen: " << endl;
		for each (auto var in residuum)
		{
			outfile << var << endl;
			cout << var << endl;
		}
		cout << fixed << "Reststreuung =" << rest(residuum) << endl;
		cout << "Stabwa y:" << endl;
		vector<double> stabwaresY = stabwa_reg(xValues, yValues);
		for each (auto var in stabwaresY)
		{
			cout << var << endl;
		}
		outfile.close();
	}
};


int main(int argc, char* argv[])
{
	ifstream infile;
	ofstream outfile;
	double x, y;
	const int bufflen = 1024;
	char buffer[bufflen + 1];
	mess messwerte;
	string inputfile;
	if(argc==2)
	{
		inputfile = argv[1];
	}
	else
	{
		inputfile = "messreihe01.dat";
	}

	infile.open(inputfile);
	if (!infile)
	{
		cout << "File open error.";
		return (-1);
	}
	outfile.open("out.dat");
	if (!outfile)
	{
		cout << "File open error.";
		return (-2);
	}


	while (infile.getline(buffer, bufflen, '\n'))
	{
		if (buffer[0] == '#')
		{
			outfile << buffer << "\n";
		}
		else
		{
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

	infile.close();
	outfile.close();
	system("pause");
}
