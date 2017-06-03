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

	infile.open("beispiel02.txt");
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


	eleList::element *akt = liste.findLast();
	
	eleList sortedList;
	//

	sortedList.addFront(liste.findOrCreateElement(akt->after));

	//Standpunkte Schreiben
	while (akt!=nullptr)
	{
		sortedList.addFront(akt);
		akt = liste.findOrCreateElement(akt->befor);
	}

	sortedList.addFront(liste.findOrCreateElement(sortedList.first->befor));

	akt = sortedList.first;

	while (akt!=nullptr)
	{
		std::cout << akt->stand;
		if(akt->angle!=NULL)
		{
			std::cout << ' ' <<akt->angle << ' ' << akt->dist;
		}
		std::cout<< std::endl;
		akt = akt->next;
	}

	system("pause");
	return 0;
}

