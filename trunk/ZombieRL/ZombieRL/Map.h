#pragma once
#include "Tile.h"
#include <list>
#include <vector>
#include "MapSegment.h"
#include "boost/shared_ptr.hpp"
struct SegmentStructure{
	unsigned int xMin;
	unsigned int yMin;
	unsigned int xMax;
	unsigned int yMax;
	boost::shared_ptr<MapSegment> segment;
};

class Map
{
public:
	Map(void);
	~Map(void);
	boost::shared_ptr<Tile> getTile(unsigned int x,unsigned int y);
	static Map* Instance(){
		static Map instance;
		return &instance;
	}
	bool lineOfSightExists(int sX,int sY,int eX,int eY);
	std::list<std::pair<int,int> > PathExists(int sX,int sY,int eX,int eY,int (*weightFunction)(int x, int y,PassedValue p),PassedValue p);
private:
	std::list<SegmentStructure> segments;
	
};
