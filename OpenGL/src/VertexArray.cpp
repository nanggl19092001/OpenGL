#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererId));
	GLCall(glBindVertexArray(m_RendererId));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();

	const std::vector<VertexBufferElement>& elements = layout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) {
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, elements.at(i).count, elements.at(i).type, 
			elements.at(i).normalized, layout.getStride(), (const void*)offset));
		offset += elements.at(i).count + sizeof(elements.at(i).type);
	}
	
}

void VertexArray::Bind()
{
	GLCall(glBindVertexArray(m_RendererId));
}

void VertexArray::Unbind()
{
	GLCall(glBindVertexArray(0));
}
