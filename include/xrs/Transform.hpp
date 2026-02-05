#pragma once

#ifndef _XRS_TRANSFORM_HPP_
#define _XRS_TRANSFORM_HPP_

#include "Vector.hpp"
#include "Matrix.hpp"

namespace xrs
{

  class Transform
  {
  public:
    Transform() = default;
    Transform(const Vector3f &position, const Vector3f &rotation = {0}, const Vector3f &scale = {1});
    inline Vector3f GetPosition() const { return m_Position; }
    inline void SetPosition(const Vector3f &position) { m_Position = position; }
    inline Vector3f GetRotationDeg() const { return m_Rotation; }
    inline void SetRotation(const Vector3f &rotation) { m_Rotation = rotation; }
    inline Vector3f GetScale() const { return m_Scale; }
    inline void SetScale(const Vector3f &scale) { m_Scale = scale; }
    const Matrix GetModelMatrix() const;
  private:
    Vector3f m_Position;
    Vector3f m_Rotation;
    Vector3f m_Scale{1};
  };

}

#endif // _XRS_TRANSFORM_HPP_