#pragma once


class VertexBuffer {
private:
	unsigned int m_id;
public:
	VertexBuffer(float vertices[] , unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};