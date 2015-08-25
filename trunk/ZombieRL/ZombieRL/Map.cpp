#include "StdAfx.h"
#include "Map.h"
#include <map>

Map::Map(void)
{
}

Map::~Map(void)
{
}

bool Map::lineOfSightExists(int sX,int sY,int eX,int eY){
	int dx = abs(eX - sX);
    int dy = abs(eY - sY);
    int x = sX;
    int y = sY;
    int n = 1 + dx + dy;
    int x_inc = (eX > sX) ? 1 : -1;
    int y_inc = (eY > sY) ? 1 : -1;
    int error = dx - dy;
    dx *= 2;
    dy *= 2;

    for (; n > 0; --n)
    {
		if (!getTile(x, y)->isSeeThrough()){
			return false;
		}

        if (error > 0)
        {
            x += x_inc;
            error -= dy;
        }
        else
        {
            y += y_inc;
            error += dx;
        }
    }
	return true;
}
boost::shared_ptr<Tile> Map::getTile(unsigned int x,unsigned int y){
	std::list<SegmentStructure>::iterator segmentIter;
	boost::shared_ptr<Tile> returnTile;
	for (segmentIter = segments.begin();
		 segmentIter != segments.end();
		 ++segmentIter){
		if ( (segmentIter->xMin <= x) &&
			 (segmentIter->xMax >= x) &&
			 (segmentIter->yMin <= y) &&
			 (segmentIter->yMax >= y)){
				 returnTile = segmentIter->segment->getTile(x-segmentIter->xMin,y-segmentIter->yMin);
				 break;
		}
	}
	return returnTile;
}
int h(int x,int y, int eX, int eY){
	return abs(x-eX) + abs(y-eY);
}
std::list<std::pair<int,int> > Map::PathExists(int sX,int sY,int eX,int eY,int (*weightFunction)(int x, int y,PassedValue p),PassedValue p){
	
	
	int nodeId = 0;
	
	int radius = p.iValue1;
	std::map<std::pair<int,int>,int > openList;
	std::multimap<int,std::pair<int,int> > openListScoreMap;
	std::map<std::pair<int,int>,int > closedList;
	std::map<std::pair<int,int>,int> distanceFromStart;
	std::map<std::pair<int,int>,int> tentativeScore;
	std::map<std::pair<int,int>,std::pair<int,int> > cameFrom;
	openList[(std::pair<int,int>(sX,sY))] = 0;
	distanceFromStart[(std::pair<int,int>(sX,sY))] = 0;	
	int score = h(sX,sY,eX,eY);
	openListScoreMap.insert(std::pair<int,std::pair<int,int> >(score,(std::pair<int,int>(sX,sY))));
	tentativeScore[(std::pair<int,int>(sX,sY))] = score;
	
	/*
	* Setup nodes to traverse and their expected distance to the end node
	*/
	/*
	* A* algorithm
	*/
	std::list<std::pair<int,int> > neighbors;
	neighbors.push_back(std::pair<int,int>(1,0));
	neighbors.push_back(std::pair<int,int>(-1,0));
	neighbors.push_back(std::pair<int,int>(0,1));
	neighbors.push_back(std::pair<int,int>(0,-1));
	std::list<std::pair<int,int> >::iterator neighborIter;
	bool foundPath = false;
	while (!openList.empty()){
		
		std::pair<int,int> nodePos = openListScoreMap.begin()->second;
		if (nodePos.first == eX && nodePos.second == eY){
			foundPath = true;
			break;
		}
		openListScoreMap.erase(openListScoreMap.begin());
		openList.erase(nodePos);
		closedList[nodePos] = 0;
		for (neighborIter = neighbors.begin();
			 neighborIter != neighbors.end();
			 ++neighborIter){
			 std::pair<int,int> neighbor(nodePos.first+neighborIter->first,nodePos.second+neighborIter->second);
			 if (closedList.find(neighbor) != closedList.end()){
				continue;
			 }
             int tentative_g_score = distanceFromStart[nodePos] + weightFunction(neighbor.first,neighbor.second, p);
             bool tentative_is_better = false;
			 if (openList.find(neighbor) == openList.end()){
                openList[neighbor] = 0;
                tentative_is_better = true;
			 }
			 else if (tentative_g_score < distanceFromStart[neighbor]){
                tentative_is_better = true;
			 }
			 if (tentative_is_better = true){
				cameFrom[neighbor] = nodePos;
                distanceFromStart[neighbor] = tentative_g_score;
                int score = tentative_g_score + h(neighbor.first,neighbor.second,eX,eY);
				openListScoreMap.insert(std::pair<int,std::pair<int,int> >(score,neighbor));
			 }
		}
	}
	std::list<std::pair<int,int> > path;
	if (foundPath){
		std::pair<int,int> endNode(eX,eY);
		path.push_front(endNode);
		std::pair<int,int> nextNode = cameFrom[endNode];
		path.push_front(nextNode);
		while (! ( (nextNode.first == sX) && (nextNode.second == sY))){
			std::pair<int,int> nextNode = cameFrom[endNode];
			path.push_front(nextNode);			
		}
	}
	return path;

}