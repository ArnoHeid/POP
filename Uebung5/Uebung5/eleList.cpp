#include "stdafx.h"
#include "eleList.h"
#include <iostream>


void eleList::addTail(element* newElement)
{
	if(last==nullptr)
	{
		first = last = newElement;
	}
	else
	{
		newElement->prev = last;
		last->next = newElement;
		last = newElement;
		
	}
}

void eleList::addFront(element* newElement, eleList otherList,bool soloElement)
{
	if (last == nullptr)
	{
		first = last = newElement;
	}
	else
	{
		if(!soloElement)
		{
		if(newElement->prev != nullptr && newElement->next !=nullptr)
		{
			newElement->next->prev = newElement->prev;
		}

		if(newElement->next !=nullptr && newElement->prev != nullptr)
		{
			newElement->prev->next = newElement->next;
		}
		if(newElement->next == nullptr)
		{
			newElement->prev->next = nullptr;
		}
		if (newElement->prev == nullptr)
		{
			newElement->next->prev = nullptr;
			otherList.first = newElement->next;
		}			
		}

		newElement->next = first;
		first->prev = newElement;
		first = newElement;
		newElement->prev = nullptr;
	}
}

void eleList::debug()
{
	element*akt = first;

	while (akt != nullptr)
	{
		std::cout << akt->stand;
		if (akt->angle != NULL)
		{
			std::cout << ' ' << akt->angle << ' ' << akt->dist;
		}
		std::cout << std::endl;
		akt = akt->next;
	}
}


eleList::element* eleList::findElement(char standpunkt)
{
	element *akut = first;

	while (akut!=nullptr)
	{
		if (akut->stand == standpunkt)
		{
			akut->prev = akut->next;
			akut->next = akut->prev;
			return akut;			
		}

		akut = akut->next;
	}
	return nullptr;
}

eleList::element* eleList::findOrCreateElement(char standpunkt)
{
	element *akut = first;

	while (akut != nullptr)
	{
		if (akut->stand == standpunkt)
		{
			if(first==akut)
			{
				first = akut->next;
			}
			return akut;
		}
			
		akut = akut->next;
	}

	akut = first;

	while (akut != nullptr)
	{
		if (akut->after == standpunkt || akut->befor == standpunkt)
		{
			element *newElement = new element();
			newElement->islast = false;
			newElement->angle = NULL;
			newElement->dist = NULL;
			newElement->next = nullptr;
			newElement->prev = nullptr;
			newElement->stand = standpunkt;
			return newElement;
		}

		akut = akut->next;
	}

	return nullptr;
}


eleList::element* eleList::findLast()
{
	element *akut = first;

	while (akut != nullptr)
	{
		if (akut->islast == true)
			return akut;
		akut = akut->next;
	}
	return nullptr;
}


eleList::eleList()
{
	first = nullptr;
	last = nullptr;
}


eleList::~eleList()
{
}
