#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const void* indices, unsigned int size);
	~IndexBuffer();

	void BindIndexBuffer() const;

	void UnbindIndexBuffer() const;

	inline unsigned int GetCount() const { return m_Count; }
};