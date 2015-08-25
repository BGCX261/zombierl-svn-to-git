#pragma once
#include "Types.h"

class Smell{
public:
	Smell(ScentSource s,float f,unsigned int id):freshness(f),source(s),sourceId(id){}
	~Smell(){};
	float freshness;
	unsigned int sourceId;
	ScentSource source;

};
