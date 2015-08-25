#pragma once
#include <list>
#include "Object.h"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "Types.h"
#include "Sound.h"
#include "Smell.h" 

struct SensoryInput{
	std::list<boost::shared_ptr<Object> > objectsSeen;
	std::list<boost::shared_ptr<Sound> > soundsHeard;
	std::list<boost::shared_ptr<Smell> > smellsSmelled;
};

class Actor : public Object
{
public:
	virtual ~Actor(void);	
	void act();
	virtual boost::weak_ptr<Object> returnMe()=0;
	static boost::shared_ptr<Actor> create(std::string parmFile);
	static boost::shared_ptr<Actor> create(ParmStruct);
	virtual void takeDamage(unsigned int sourceId,std::list<DamageSource>,unsigned int damage)=0;
	void skipNextTurn();
	int getPriority();
private:
	Actor();
	SensoryInput observe();
	int sightRange;
	int smellRange;
	int soundRange;
	int sightRangeSq;
	int smellRangeSq;
	int soundRangeSq;
	int perception;
	int intelligence;
	int dexterity;
	int strength;
	int endurance;
};
