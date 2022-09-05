/*
 *   Copyright (c) 2022 ItsSunnyMonster

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "D3D11Context.hpp"
#include "Destiny/Renderer/Buffer.hpp"
#include "Destiny/Renderer/GraphicsContext.hpp"

namespace Destiny {
class D3D11VertexBuffer : public VertexBuffer {
public:
  D3D11VertexBuffer(float *vertices, size_t size, GraphicsContext *context,
                    BufferLayout layout);
  ~D3D11VertexBuffer() override;

  void bind() const override;
  void unbind() const override;

  const BufferLayout &getLayout() const override;

private:
  ComRef<ID3D11Buffer> m_Buffer;
  BufferLayout m_Layout;
  D3D11Context *m_Context;
};

class D3D11IndexBuffer : public IndexBuffer {
public:
  D3D11IndexBuffer(uint32_t *indices, size_t size, GraphicsContext *context);
  ~D3D11IndexBuffer() override;
  void bind() const override;
  void unbind() const override;

private:
  ComRef<ID3D11Buffer> m_Buffer;
  D3D11Context *m_Context;
};
} // namespace Destiny
