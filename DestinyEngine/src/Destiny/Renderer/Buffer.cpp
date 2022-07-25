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

#include "Buffer.hpp"
#include "Destiny/Platform/D3D11/D3D11Buffer.hpp"

Destiny::Ref<Destiny::VertexBuffer>
Destiny::VertexBuffer::create(float *vertices, size_t size,
                              GraphicsContext *context, BufferLayout layout) {
  return makeRef<D3D11VertexBuffer>(vertices, size, context, layout);
}

Destiny::Ref<Destiny::IndexBuffer>
Destiny::IndexBuffer::create(uint32_t *indices, size_t size,
                             GraphicsContext *context) {
  return makeRef<D3D11IndexBuffer>(indices, size, context);
}
