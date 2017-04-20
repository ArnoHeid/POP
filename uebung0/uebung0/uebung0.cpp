// uebung0.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>


void main()
{
	std::ifstream filestream("output.geom");
	std::ofstream outfile("out.dat");
	std::string line;
	int i = 1; //counter
	while (std::getline(filestream,line))
	{
		std::istringstream iss(line);
		std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
		outfile << "v " << tokens[1] <<" "<< tokens[2] << " " << tokens[3] << "\nv " << tokens[4] << " " << tokens[5] << " " << tokens[6] << "\nv " << tokens[7] << " " << tokens[8] << " " << tokens[9] << "\nf " << i << " " << i+1 << " " << i+2<< "\n";
		i = i + 3;
	}
	filestream.close();
	outfile.close();
}