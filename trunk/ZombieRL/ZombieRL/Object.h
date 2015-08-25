#pragma once
#include <string>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
class ParmStruct;

class Object
{
public:
	virtual ~Object(void);	
	unsigned int getId();
	virtual boost::weak_ptr<Object> returnMe() =0;
	static boost::shared_ptr<Object> create(std::string parmFile);
	static boost::shared_ptr<Object> create(ParmStruct);
	
protected:
	unsigned int id;
	unsigned int myX;
	unsigned int myY;
	Object();

};
