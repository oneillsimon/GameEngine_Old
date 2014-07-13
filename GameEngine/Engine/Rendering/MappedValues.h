#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include <string>
#include <map>
#include "../Core/Math3D.h"

class MappedValues
{
private:
	std::map<std::string, Vector3> vector3Map;
	std::map<std::string, Vector4> vector4Map;
	std::map<std::string, float> floatMap;

public:
	void addVector3(std::string name, Vector3 v);
	void addVector4(std::string name, Vector4 v);
	void addFloat(std::string name, float f);

	Vector3 getVector3(std::string name);
	Vector4 getVector4(std::string name);
	float getFloat(std::string name);
};

#endif