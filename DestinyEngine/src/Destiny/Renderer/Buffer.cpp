#include "Buffer.hpp"
#include "Destiny/Platform/D3D11/D3D11Buffer.hpp"

Destiny::VertexBuffer* Destiny::VertexBuffer::create(float* vertices, size_t size, GraphicsContext* context, BufferLayout layout)
{
	return new Destiny::D3D11VertexBuffer(vertices, size, context, layout);
}

Destiny::IndexBuffer* Destiny::IndexBuffer::create(uint32_t* indices, size_t size, GraphicsContext* context)
{
	return new Destiny::D3D11IndexBuffer(indices, size, context);
}

