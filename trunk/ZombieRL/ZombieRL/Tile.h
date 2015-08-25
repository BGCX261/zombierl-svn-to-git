#pragma once
#include <list>
#include <map>
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "Object.h"
#include "Actor.h"
#include "Types.h"
#include "Sound.h"
#include "Smell.h"

class Tile
{
public:
	Tile(void);
	Tile(int tx,int ty):x(tx),y(ty),type(GRASS){}
	~Tile(void);
	TileType getType(){
		return type;
	}
	void takeObject(boost::shared_ptr<Object> obj){
		objects[obj->getId()] = obj;
	}	
	void relinquishObject(boost::shared_ptr<Object> obj){
		objects.erase(obj->getId());
	}
	void relinquishObject(unsigned int objId){
		objects.erase(objId);
	}
	unsigned int objSize() { return objects.size();}
	void manageSensoryInput();
	bool isPassable(int dexterity);
	bool isSeeThrough();
	bool objectsExist(){
		return !objects.empty();
	}
	bool smellsExist(){
		return !smells.empty();
	}
	bool soundsExist(){
		return !sounds.empty();
	}

	std::list<boost::shared_ptr<Object> > getObjects(){
		std::map<unsigned int, boost::shared_ptr<Object> >::iterator objIter;
		std::list<boost::shared_ptr<Object> > objList;
		for (objIter = objects.begin();
			objIter != objects.end();
			++objIter){
				objList.push_back(objIter->second);
		}
		return objList;
	}
	std::list<boost::shared_ptr<Sound> > getSounds(){
		return sounds;
	}
	std::list<boost::shared_ptr<Smell> > getSmells(){
		return smells;
	}
private:
	std::map<unsigned int, boost::shared_ptr<Object> > objects;
	TileType type;
	int x,y;
	std::list<boost::shared_ptr<Sound> >  sounds;
	std::list<boost::shared_ptr<Smell> >  smells;
};
