#include "StdAfx.h"
#include "MapSegment.h"
#include <iostream>
MapSegment::MapSegment(void)
{ 
	xMax = 32;
	yMax = 32;
	tileMap.resize(boost::extents[xMax][yMax]);
	for (int i = 0; i < xMax; i++){
		for (int j = 0; j < yMax; j++){
			tileMap[i][j].reset(new Tile(i,j));
		}
	}
}

MapSegment::~MapSegment(void)
{
}

void MapSegment::print(){
	for (int j = 0; j < yMax; j++){
		for (int i = 0; i < xMax; i++){
			std::cout << tileMap[i][j]->getType() << tileMap[i][j]->objSize() << " ";
		}
		std::cout << "\n";
	}
}
