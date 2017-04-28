// Uebung5.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "eleList.h"


int main()
{
	//Read in stuff;
	std::ifstream infile;
	std::ofstream outfile;
	double rueck, vor, strecke;
	char pre, at, next;
	const int bufflen = 1024;
	char buffer[bufflen + 1];

	//Zeiger 
	eleList liste;

	infile.open("beispiel01.txt");
	if (!infile)
	{
		std::cout << "File open error.";
		return (-1);
	}


	while (infile.getline(buffer, bufflen, '\n'))
	{
		if (buffer[0] == '#')
		{
			outfile << buffer << "\n";
		}
		else
		{
			int number = sscanf(buffer, "%c %c %c %lf %lf %lf", &at, &pre, &next, &rueck, &vor, &strecke);

			eleList::element *newelement;
			newelement = static_cast<eleList::element *>(calloc(1, sizeof(eleList::element)));
			if (number == 6)
			{
				newelement->dist = strecke;
				newelement->islast = false;
			}
			else if (number == 5)
			{
				newelement->dist = 0;
				newelement->islast = true;
			}
			newelement->stand = at;
			newelement->befor = pre;
			newelement->after = next;
			newelement->angle = vor - rueck;
			liste.addTail(newelement);

		}
	}



	return 0;
}

