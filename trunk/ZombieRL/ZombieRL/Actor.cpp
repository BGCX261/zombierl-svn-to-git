#include "StdAfx.h"
#include "Actor.h"
#include "Map.h"
#include <map>
Actor::Actor(void)
{
}

Actor::~Actor(void)
{
}


int ScentWeight(int x, int y,PassedValue p){
	int returnVal;
	TileType type =  Map::Instance()->getTile(x,y)->getType();
	switch(type) {
		case GRASS:
		case ROAD:
		case SIDEWALK:
		case DIRT:
		case CONCRETE:
		case LINOLEUM:
		case OPENDOOR:		
		case WATER:
		case DEBRIS:
		case CONCRETEBARRIER:
		case CHAINLINKFENCE:
		case WOODFENCE:
		case TREE:
			returnVal =  1;
			break;
		case GLASS:		
		case STEEL:
		case WOOD:
		case CLOSEDDOOR:
		default:
			returnVal =   999;
			break;
	}
	return returnVal;
}
int SoundWeight(int x, int y,PassedValue p){
	int returnVal;
	TileType type =  Map::Instance()->getTile(x,y)->getType();
	switch(type) {
		case CONCRETE:
		case LINOLEUM:
		case OPENDOOR:
		case WATER:
		case ROAD:
		case SIDEWALK:
		case DIRT:
		case CHAINLINKFENCE:
			returnVal = 1;
		case GRASS:
		case DEBRIS:
		case TREE:
			returnVal = 2;
		case GLASS:
		case CONCRETEBARRIER:
		case WOODFENCE:
			returnVal =  4;
			break;		
		case STEEL:
		case WOOD:
		case CLOSEDDOOR:
		default:
			returnVal =   6;
			break;
	}
	return returnVal;
}
int movementWeight(int x, int y, PassedValue p){
	boost::shared_ptr<Tile> thisTile = Map::Instance()->getTile(x,y);
	int dexterity = p.iValue1;
	return 0;
}
SensoryInput Actor::observe(){
	/*
	 * Create a list of all spaces within the given range
	 */
	std::list<std::pair<int,int> > potentialSightSquares;
	potentialSightSquares.push_back(std::pair<int,int>(0,0));

	std::list<std::pair<int,int> > potentialSoundSquares;
	potentialSoundSquares.push_back(std::pair<int,int>(0,0));

	std::list<std::pair<int,int> > potentialSmellSquares;
	potentialSmellSquares.push_back(std::pair<int,int>(0,0));

	int maxRange = sightRange;
	maxRange = maxRange > soundRange ? maxRange : soundRange;
	maxRange = maxRange > smellRange ? maxRange : smellRange;
	for (int i = 1; i <= maxRange; i++){
		if (i <= sightRange){
			potentialSightSquares.push_back(std::pair<int,int>(i,0));
			potentialSightSquares.push_back(std::pair<int,int>(0,i));	
			potentialSightSquares.push_back(std::pair<int,int>(-i,0));
			potentialSightSquares.push_back(std::pair<int,int>(0,-i));	
		}
		if (i <= soundRange){
			potentialSoundSquares.push_back(std::pair<int,int>(i,0));
			potentialSoundSquares.push_back(std::pair<int,int>(0,i));	
			potentialSoundSquares.push_back(std::pair<int,int>(-i,0));
			potentialSoundSquares.push_back(std::pair<int,int>(0,-i));	
		}
		if (i <= smellRange){
			potentialSmellSquares.push_back(std::pair<int,int>(i,0));
			potentialSmellSquares.push_back(std::pair<int,int>(0,i));	
			potentialSmellSquares.push_back(std::pair<int,int>(-i,0));
			potentialSmellSquares.push_back(std::pair<int,int>(0,-i));	
		}
	}
	for (int i = 1; i < maxRange; i++){		
		for (int j = 1; j < maxRange; j++){
			if ((i*i+j*j) <= sightRangeSq){
				potentialSightSquares.push_back(std::pair<int,int>(i,j));
				potentialSightSquares.push_back(std::pair<int,int>(i,-j));	
				potentialSightSquares.push_back(std::pair<int,int>(-i,j));
				potentialSightSquares.push_back(std::pair<int,int>(-i,-j));	
			}
			if ((i*i+j*j) <= soundRangeSq){
				potentialSoundSquares.push_back(std::pair<int,int>(i,j));
				potentialSoundSquares.push_back(std::pair<int,int>(i,-j));	
				potentialSoundSquares.push_back(std::pair<int,int>(-i,j));
				potentialSoundSquares.push_back(std::pair<int,int>(-i,-j));
			}
			if ((i*i+j*j) <= smellRangeSq){
				potentialSmellSquares.push_back(std::pair<int,int>(i,j));
				potentialSmellSquares.push_back(std::pair<int,int>(i,-j));	
				potentialSmellSquares.push_back(std::pair<int,int>(-i,j));
				potentialSmellSquares.push_back(std::pair<int,int>(-i,-j));	
			}
		}
	}

	std::list<std::pair<int,int> >::iterator squareIter;
	/***************************************************
	* For sight
	****************************************************/
	std::list<boost::shared_ptr<Object> > objectList;
	
	for (squareIter = potentialSightSquares.begin();
		 squareIter != potentialSightSquares.end();
		 ++squareIter){
		int x,y;
		x = myX + squareIter->first;
		y = myY + squareIter->second;

		/*
		 * Now see if a LoS exists between this location and all of the tiles
		 */
		if (Map::Instance()->getTile(x,y)->objectsExist()){
			if (Map::Instance()->lineOfSightExists(myX,myY,x,y)){
				std::list<boost::shared_ptr<Object> > objList = Map::Instance()->getTile(x,y)->getObjects();
				objectList.insert(objectList.begin(),objList.begin(),objList.end());
			}	
		}
	}
	
	/*****************************************************
	* For smells
	******************************************************/
	
	std::list<boost::shared_ptr<Smell> > smellList;
	PassedValue p;
	p.mode = true;
	p.iValue1 = smellRange; 
	for (squareIter = potentialSmellSquares.begin();
		 squareIter != potentialSmellSquares.end();
		 ++squareIter){
		int x,y;
		x = myX + squareIter->first;
		y = myY + squareIter->second;

		if (Map::Instance()->getTile(x,y)->smellsExist()){
			if (Map::Instance()->PathExists(myX,myY,x,y,ScentWeight,p).empty()){
				std::list<boost::shared_ptr<Smell> > sList = Map::Instance()->getTile(x,y)->getSmells();
				smellList.insert(smellList.begin(),sList.begin(),sList.end());
			}	
		}
	}

	/*****************************************************
	* For sounds
	******************************************************/
	std::list<boost::shared_ptr<Sound> > soundList;
	p.mode = true;
	p.iValue1 = soundRange; 	
	for (squareIter = potentialSoundSquares.begin();
		 squareIter != potentialSoundSquares.end();
		 ++squareIter){
		int x,y;
		x = myX + squareIter->first;
		y = myY + squareIter->second;
		if (Map::Instance()->getTile(x,y)->soundsExist()){
			if (Map::Instance()->PathExists(myX,myY,x,y,SoundWeight,p).empty()){
				std::list<boost::shared_ptr<Sound> > sList = Map::Instance()->getTile(x,y)->getSounds();
				soundList.insert(soundList.begin(),sList.begin(),sList.end());				
			}	
		}		
	}	
	SensoryInput sensoryOutput;
	sensoryOutput.objectsSeen = objectList;
	sensoryOutput.soundsHeard = soundList;
	sensoryOutput.smellsSmelled = smellList;
	return sensoryOutput;
}
