#pragma once
#include "Types.h"
#include "boost/shared_ptr.hpp"
#include "GameInfo.h"

class Sound
{
public:
	Sound(float f,unsigned int id, unsigned int sVal,SoundSource s):
	  freshness(f),sourceId(id),soundVal(sVal),source(s){}
	~Sound(){};
	float freshness;
	unsigned int sourceId;
	unsigned int soundVal;
	SoundSource source;

};