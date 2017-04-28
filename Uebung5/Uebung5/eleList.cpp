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

eleList::element* eleList::findElement(char standpunkt)
{
	element *akut = first;

	while (akut!=nullptr)
	{
		if (akut->stand == standpunkt)
			return akut;
		akut = akut->next;
	}
	return nullptr;
}

eleList::element* eleList::findOrCreateElement(char standpunkt)
{

}


eleList::eleList()
{
	first = nullptr;
	last = nullptr;
}


eleList::~eleList()
{
}
