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

#include "D3D11Buffer.hpp"
#include "D3D11Exception.hpp"
#include "D3D11Context.hpp"

Destiny::D3D11VertexBuffer::D3D11VertexBuffer(float *vertices, size_t size,
                                              GraphicsContext *context,
                                              BufferLayout layout)
    : m_Layout(std::move(layout)),
      m_Context(reinterpret_cast<D3D11Context *>(context)) {
  D3D11_BUFFER_DESC bd = {0};
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.CPUAccessFlags = 0;
  bd.MiscFlags = 0;
  bd.ByteWidth = sizeof(float) * size;
  bd.StructureByteStride = m_Layout.getStride();

  D3D11_SUBRESOURCE_DATA sd = {nullptr};
  sd.pSysMem = vertices;

  DT_D3D11_THROW_FAILED(m_Context->getD3D11Device()->CreateBuffer(
      &bd, &sd, m_Buffer.ReleaseAndGetAddressOf()));
}

Destiny::D3D11VertexBuffer::~D3D11VertexBuffer() {}

void Destiny::D3D11VertexBuffer::bind() const {
  const UINT stride = m_Layout.getStride();
  const UINT offset = 0;
  m_Context->getD3D11Context()->IASetVertexBuffers(
      0, 1, m_Buffer.GetAddressOf(), &stride, &offset);
}

void Destiny::D3D11VertexBuffer::unbind() const {
  m_Context->getD3D11Context()->IASetVertexBuffers(0, 0, nullptr, nullptr,
                                                   nullptr);
}

const Destiny::BufferLayout &Destiny::D3D11VertexBuffer::getLayout() const {
  return m_Layout;
}

Destiny::D3D11IndexBuffer::D3D11IndexBuffer(uint32_t *indices, size_t size,
                                            GraphicsContext *context)
    : m_Context(reinterpret_cast<D3D11Context *>(context)) {
  D3D11_BUFFER_DESC ibd = {0};
  ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  ibd.Usage = D3D11_USAGE_DEFAULT;
  ibd.CPUAccessFlags = 0;
  ibd.MiscFlags = 0;
  ibd.ByteWidth = sizeof(uint32_t) * size;
  ibd.StructureByteStride = sizeof(uint32_t);

  D3D11_SUBRESOURCE_DATA isd = {nullptr};
  isd.pSysMem = indices;
  DT_D3D11_THROW_FAILED(m_Context->getD3D11Device()->CreateBuffer(
      &ibd, &isd, m_Buffer.ReleaseAndGetAddressOf()));
}

Destiny::D3D11IndexBuffer::~D3D11IndexBuffer() {}

void Destiny::D3D11IndexBuffer::bind() const {
  m_Context->getD3D11Context()->IASetIndexBuffer(m_Buffer.Get(),
                                                 DXGI_FORMAT_R32_UINT, 0);
}

void Destiny::D3D11IndexBuffer::unbind() const {
  m_Context->getD3D11Context()->IASetIndexBuffer(nullptr, (DXGI_FORMAT)0, 0);
}
