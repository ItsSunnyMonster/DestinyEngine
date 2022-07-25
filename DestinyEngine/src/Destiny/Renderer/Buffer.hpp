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

#include "GraphicsContext.hpp"

namespace Destiny {
enum class ShaderDataType {
  None = 0,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool
};

static size_t shaderDataTypeSize(ShaderDataType type) {
  switch (type) {
  case Destiny::ShaderDataType::Float:
    return sizeof(float);
  case Destiny::ShaderDataType::Float2:
    return sizeof(float) * 2;
  case Destiny::ShaderDataType::Float3:
    return sizeof(float) * 3;
  case Destiny::ShaderDataType::Float4:
    return sizeof(float) * 4;
  case Destiny::ShaderDataType::Mat3:
    return sizeof(float) * 3 * 3;
  case Destiny::ShaderDataType::Mat4:
    return sizeof(float) * 4 * 4;
  case Destiny::ShaderDataType::Int:
    return sizeof(int32_t);
  case Destiny::ShaderDataType::Int2:
    return sizeof(int32_t) * 2;
  case Destiny::ShaderDataType::Int3:
    return sizeof(int32_t) * 3;
  case Destiny::ShaderDataType::Int4:
    return sizeof(int32_t) * 4;
  case Destiny::ShaderDataType::Bool:
    return sizeof(bool);
  }
  DT_ASSERT_MSG(false, "Unknown shader data type");
}

struct BufferElement {
  std::string Name;
  ShaderDataType Type;
  uint32_t Size;
  uint32_t Offset;

  BufferElement(ShaderDataType type, std::string name)
      : Type(type), Name(std::move(name)),
        Size((uint32_t)shaderDataTypeSize(type)), Offset(0) {}
};

class BufferLayout {
public:
  BufferLayout(std::initializer_list<BufferElement> elements)
      : m_Elements(std::move(elements)) {
    calculateOffsetsAndStride();
  }

  inline const std::vector<BufferElement> &getElements() const {
    return m_Elements;
  }
  inline uint32_t getStride() const { return m_Stride; }

private:
  void calculateOffsetsAndStride() {
    uint32_t offset = 0;
    m_Stride = 0;
    for (auto &element : m_Elements) {
      element.Offset = offset;
      offset += element.Size;
      m_Stride += element.Size;
    }
  }

private:
  std::vector<BufferElement> m_Elements;
  uint32_t m_Stride;
};

class VertexBuffer {
public:
  virtual ~VertexBuffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual const BufferLayout &getLayout() const = 0;

  static Ref<VertexBuffer> create(float *vertices, size_t size,
                                  GraphicsContext *context,
                                  BufferLayout layout);
};

class IndexBuffer {
public:
  virtual ~IndexBuffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  static Ref<IndexBuffer> create(uint32_t *indices, size_t size,
                                 GraphicsContext *context);
};
} // namespace Destiny
