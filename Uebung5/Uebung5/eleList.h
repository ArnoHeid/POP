#pragma once
class eleList
{
public:
struct element
{
	struct  element *prev;
	struct element *next;
	double angle;
	double dist;
	char stand;
	char befor;
	char after;
	bool islast;
};

//Pointer

element *first;
element *last;
//Functions	
void addTail(element *newElement);
void addFront(element* newElement, eleList otherList, bool soloElement);
void debug();
eleList::element* findElement(char standpunkt);
eleList::element* findOrCreateElement(char standpunkt);
eleList::element* findLast();
//Construktor/Dekonstruktor
	eleList();
	~eleList();
};

