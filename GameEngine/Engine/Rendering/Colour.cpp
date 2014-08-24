#include "Colour.h"

Colour::Colour()
	: Vector4(0, 0, 0, 1)
{
}

Colour::Colour(float r, float g, float b, float a)
	: Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f)
{
}

Colour::Colour(int hex)
{
	Colour c = hexToRGBA(hex);
	x = c.getR();
	y = c.getG();
	z = c.getB();
	w = c.getA();
}

Colour Colour::hexToRGBA(int hex)
{
	int r = (hex >> 24) & 0xFF;
	int g = (hex >> 16) & 0xFF;
	int b = (hex >> 8) & 0xFF;
	int a = (hex >> 0) & 0xFF;

	return Colour(r, g, b, a);
}

int Colour::RGBAtoHex(float r, float g, float b, float a)
{
	return ((int)x << 24) + ((int)y << 16) + ((int)z << 8) + (int)w;
}

Vector3 Colour::getRGB() const
{
	return Vector3(x, y, z) * w;
}

float Colour::getR() const
{
	return x;
}

float Colour::getG() const
{
	return y;
}

float Colour::getB() const
{
	return z;
}

float Colour::getA() const
{
	return w;
}

void Colour::setR(float r)
{
	this->x = r;
}

void Colour::setG(float g)
{
	this->y = g;
}

void Colour::setB(float b)
{
	this->z = b;
}

void Colour::setA(float a)
{
	this->w = a;
}