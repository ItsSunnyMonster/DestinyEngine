#include "Buffer.hpp"
#include "Destiny/Platform/D3D11/D3D11Buffer.hpp"

Destiny::Ref<Destiny::VertexBuffer> Destiny::VertexBuffer::create(float* vertices, size_t size, GraphicsContext* context, BufferLayout layout)
{
	return makeRef<D3D11VertexBuffer>(vertices, size, context, layout);
}

Destiny::Ref<Destiny::IndexBuffer> Destiny::IndexBuffer::create(uint32_t* indices, size_t size, GraphicsContext* context)
{
	return makeRef<D3D11IndexBuffer>(indices, size, context);
}

