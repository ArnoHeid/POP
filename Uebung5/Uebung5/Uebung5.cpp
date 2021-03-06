// Uebung5.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
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

	sortedList.addFront(liste.findOrCreateElement(akt->after),liste,false);

	//Standpunkte Schreiben
	while (akt != nullptr)
	{
		sortedList.addFront(akt,liste,false);
		akt = liste.findOrCreateElement(akt->befor);
		//std::cout << "Liste:"<<std::endl;
		//liste.debug();
		//std::cout << "Sorted List"<<std::endl;
		//sortedList.debug();
	}

	eleList::element *newElement = new eleList::element();
	newElement->islast = false;
	newElement->angle = NULL;
	newElement->dist = NULL;
	newElement->next = nullptr;
	newElement->prev = nullptr;
	newElement->stand = sortedList.first->befor;

	sortedList.addFront(newElement,liste,true);

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

