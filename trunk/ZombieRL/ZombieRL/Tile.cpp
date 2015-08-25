#include "StdAfx.h"
#include "Tile.h"
#include <iostream>

Tile::Tile(void)
:type(GRASS)
{

}

Tile::~Tile(void)
{
}

bool isSoundOld (const boost::shared_ptr<Sound>& sound) { return (sound->freshness-GameInfo::currentTime) < 4; }
bool isSmellOld (const boost::shared_ptr<Smell>& smell) { return (smell->freshness-GameInfo::currentTime) < 400; }

void Tile::manageSensoryInput(){
	bool (*soundCheck)(const boost::shared_ptr<Sound>& sound);
	soundCheck = isSoundOld;  	
	sounds.remove_if(soundCheck);
	bool (*smellCheck)(const boost::shared_ptr<Smell>& smell);
	smellCheck = isSmellOld;  	
	smells.remove_if(smellCheck);
}

bool Tile::isPassable(int dexterity){
	bool returnVal;
	switch(type){
		case GRASS:
		case ROAD:
		case SIDEWALK:
		case DIRT:
		case CONCRETE:
		case LINOLEUM:
		case OPENDOOR:
			returnVal = true;
			break;
		case DEBRIS:
		case CONCRETEBARRIER:
		case CHAINLINKFENCE:
		case WOODFENCE:
			if (dexterity > 5){
				returnVal =  true;
			}
			else{
				returnVal =  false;
			}
			break;
		case GLASS:
		case STEEL:
		case WOOD:
		case TREE:
		case WATER:
		case CLOSEDDOOR:
		default:
			returnVal =  false;
			break;
	}
	return returnVal;

}

bool Tile::isSeeThrough(){
	bool returnVal;
	switch(type) {
		case GRASS:
		case ROAD:
		case SIDEWALK:
		case DIRT:
		case CONCRETE:
		case LINOLEUM:
		case OPENDOOR:
		case GLASS:
		case WATER:
		case DEBRIS:
		case CONCRETEBARRIER:
		case CHAINLINKFENCE:
			returnVal =   true;
			break;
		case WOODFENCE:
		case STEEL:
		case WOOD:
		case TREE:
		case CLOSEDDOOR:
		default:
			returnVal =   false;
			break;
	}
	return returnVal;
}

