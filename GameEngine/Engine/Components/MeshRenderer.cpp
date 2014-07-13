#include "MeshRenderer.h"
#include "../Rendering/Shader.h"

MeshRenderer::MeshRenderer()
{
	m_mesh = 0;
	m_material = 0;
	m_colour = 0;
}

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material)
{
	m_mesh = mesh;
	m_material = material;
	m_colour = new Colour(1, 1, 1);
}

MeshRenderer::MeshRenderer(Mesh* mesh, Colour* colour)
{
	m_mesh = mesh;
	m_material = new Material(new Texture("test.png"), 1, 8);
	m_colour = colour;
}

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material, Colour* colour)
{
	m_mesh = mesh;
	m_material = material;
	m_colour = colour;
}

MeshRenderer::~MeshRenderer()
{
	if(m_mesh)
	{
		delete m_mesh;
	}

	if(m_material)
	{
		delete m_material;
	}

	if(m_colour)
	{
		delete m_colour;
	}
}

void MeshRenderer::render(Shader* shader, RenderingEngine* renderingEngine)
{
	shader->bind();
	shader->updateUniforms(getTransform(), *m_material, *m_colour, renderingEngine);
	m_mesh->draw();
}