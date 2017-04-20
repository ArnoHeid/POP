// Cluster.cpp

#include "stdafx.h"
#include "Cluster.h"
#include <vector>

//private Vatriablen

int numberOfPeoles;
int numberOfDocs;
int maxPePerDoc;

struct clusterCenter
{
	int x;
	int y;
	int xNew;
	int yNew;
	int sum;
};

std::vector<clusterCenter> clusters;
std::vector<coordinats> zensusData;






//Construktor using random positions for clusters
void Cluster::calucalteSum()
{
	numberOfPeoles = 0;
	for (int i = 0; i < zensusData.size(); ++i)
	{
		numberOfPeoles += zensusData[i].anz;
	}
	//Calculate Maximal Number of Docs
	numberOfDocs = round(static_cast<double>(numberOfPeoles)/static_cast<double>(maxPePerDoc)+0.5);
}

void generateClusterRandom()
{
	for (int i = 0; i < numberOfDocs; ++i)
	{
		rand
	}
}




Cluster::Cluster()
{
}


Cluster::~Cluster()
{
}
