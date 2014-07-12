#include "../Core/CoreEngine.h"
#include "../Rendering/RenderingEngine.h"
#include "../Rendering/Shader.h"
#include "Lighting.h"

#define COLOUR_DEPTH 256

Light::Light(const Vector3& colour, float intensity)
{
	m_colour = colour;
	m_intensity = intensity;
	m_shader = 0;
}

Light::~Light()
{
	if(m_shader)
	{
		delete m_shader;
	}
}

void Light::addToCoreEngine(CoreEngine* coreEngine)
{
	coreEngine->getRenderingEngine()->addLight(this);
}

Shader* Light::getShader()
{
	return m_shader;
}

Vector3 Light::getColour() const
{
	return m_colour;
}

float Light::getIntensity() const
{
	return m_intensity;
}

void Light::setShader(Shader* shader)
{
	if(m_shader)
	{
		delete m_shader;
	}

	this->m_shader = shader;
}

void Light::setColour(const Vector3& colour)
{
	m_colour = colour;
}

void Light::setIntensity(float intensity)
{
	m_intensity = intensity;
}

Attenuation::Attenuation(float constant, float linear, float exponent)
{
	m_constant = constant;
	m_linear = linear;
	m_exponent = exponent;
}

float Attenuation::getConstant() const
{
	return m_constant;
}

float Attenuation::getLinear() const
{
	return m_linear;
}

float Attenuation::getExponent() const
{
	return m_exponent;
}

void Attenuation::setConstant(float constant)
{
	m_constant = constant;
}

void Attenuation::setLinear(float linear)
{
	m_linear = linear;
}

void Attenuation::setExponent(float exponent)
{
	m_exponent = exponent;
}

DirectionalLight::DirectionalLight(const Vector3& colour, float intensity)
	: Light(colour, intensity)
{
	setShader(new Shader("forward-directional"));
}

PointLight::PointLight(const Vector3& colour, float intensity, const Attenuation& attenuation)
	: Light(colour, intensity)
{
	float a = attenuation.getExponent();
	float b = attenuation.getLinear();
	float c = attenuation.getConstant() - COLOUR_DEPTH * intensity * colour.max();

	m_range = (-b + sqrtf(b * b - 4 * a * c)) / ( 2 * a);

	setShader(new Shader("forward-point"));
}

Attenuation PointLight::getAttenuation() const
{
	return m_attenuation;
}

float PointLight::getRange() const
{
	return m_range;
}

void PointLight::setAttenuation(Attenuation attenuation)
{
	m_attenuation = attenuation;
}

void PointLight::setRange(float range)
{
	m_range = range;
}

SpotLight::SpotLight(const Vector3& colour, float intensity, const Attenuation& attenuation, float cutoff)
	: PointLight(colour, intensity, attenuation)
{
	m_cutoff = cutoff;

	setShader(new Shader("forward-spot"));
}

float SpotLight::getCutoff() const
{
	return m_cutoff;
}

void SpotLight::setCutoff(float cutoff)
{
	m_cutoff = cutoff;
}