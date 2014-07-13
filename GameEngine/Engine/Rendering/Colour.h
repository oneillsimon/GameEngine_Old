#ifndef COLOUR_H
#define COLOUR_H

#include "../Core/Math3D.h"

class Colour : public Vector4
{
private:
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);

public:
	Colour();
	Colour(float r, float g, float b);
	Colour(float r, float g, float b, float a);

	Vector3 getRGB() const;

	float getR() const;
	float getG() const;
	float getB() const;
	float getA() const;

	void setR(float x);
	void setG(float y);
	void setB(float z);
	void setA(float w);
};

#endif