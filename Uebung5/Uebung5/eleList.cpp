#include "stdafx.h"
#include "eleList.h"


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

void eleList::addFront(element* newElement)
{
	if (last == nullptr)
	{
		first = last = newElement;
	}
	else
	{
		newElement->next = first;
		first->prev = newElement;
		first = newElement;
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
			element *newElement = new element();
			newElement->islast = akut->islast;
			newElement->angle = akut->angle;
			newElement->dist = akut->dist;
			newElement->stand = akut->stand;
			newElement->befor = akut->befor;
			newElement->after = akut->after;
			newElement->next = nullptr;
			newElement->prev = nullptr;
			return newElement;
		}
			
		akut = akut->next;
	}

	element *newElement = new element();
	newElement->islast = false;
	newElement->angle = NULL;
	newElement->dist = NULL;
	newElement->next = nullptr;
	newElement->prev = nullptr;
	newElement->stand = standpunkt;
	return newElement;
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
