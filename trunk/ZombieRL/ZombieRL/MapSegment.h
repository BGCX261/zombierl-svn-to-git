#pragma once
#include "Tile.h"
#include "boost/multi_array.hpp"
#include "boost/shared_ptr.hpp"

typedef boost::multi_array<boost::shared_ptr<Tile>, 2> array_type;
typedef array_type::index index;
class MapSegment
{
public:
	MapSegment();
	~MapSegment(void);
	void print();
	boost::shared_ptr<Tile> getTile(int x, int y){
		return tileMap[x][y];
	}
private:
	array_type tileMap;
	int xMax;
	int yMax;
};
