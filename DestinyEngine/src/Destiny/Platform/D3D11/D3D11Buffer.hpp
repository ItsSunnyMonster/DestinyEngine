#pragma once

#include "Destiny/Renderer/Buffer.hpp"
#include "Destiny/Renderer/GraphicsContext.hpp"
#include "D3D11Context.hpp"

namespace Destiny
{
	class D3D11VertexBuffer : public VertexBuffer
	{
	public:
		D3D11VertexBuffer(float* vertices, size_t size, GraphicsContext* context, BufferLayout layout);
		~D3D11VertexBuffer() override;

		void bind() const override;
		void unbind() const override;

		const BufferLayout& getLayout() const override;

	private:
		ID3D11Buffer* m_Buffer;
		BufferLayout m_Layout;
		D3D11Context* m_Context;
	};

	class D3D11IndexBuffer : public IndexBuffer
	{
	public:
		D3D11IndexBuffer(uint32_t* indices, size_t size, GraphicsContext* context);
		~D3D11IndexBuffer() override;
		void bind() const override;
		void unbind() const override;
	private:
		ID3D11Buffer* m_Buffer;
		D3D11Context* m_Context;
	};
}
