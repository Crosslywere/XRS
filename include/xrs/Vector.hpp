#pragma once

#ifndef _XRS_VECTOR_HPP_
#define _XRS_VECTOR_HPP_

namespace xrs
{

  template<typename T>
  struct Vector2
  {
    T x{}, y{};
    Vector2() = default;
    Vector2(T s) : x{s}, y{s} {}
    Vector2(T _x, T _y) : x{_x}, y{_y} {}
  };

  template<typename T>
  struct Vector3
  {
    T x{}, y{}, z{};
    Vector3() = default;
    Vector3(T s) : x{s}, y{s}, z{s} {}
    Vector3(T _x, T _y, T _z) : x{_x}, y{_y}, z{_z} {}
    Vector3(const Vector2<T> &v2, T _z) : x{v2.x}, y{v2.y}, z{_z} {}
    Vector3(T _x, const Vector2<T> &v2) : x{_x}, y{v2.x}, z{v2.y} {}
  };

  template<typename T>
  struct Vector4
  {
    T x{}, y{}, z{}, w{};
    Vector4() = default;
    Vector4(T s) : x{s}, y{s}, z{s}, w{s} {}
    Vector4(T _x, T _y, T _z, T _w) : x{_x}, y{_y}, z{_z}, w{_w} {}
    Vector4(const Vector2<T> &v2, T _z, T _w) : x{v2.x}, y{v2.y}, z{_z}, w{_w} {}
    Vector4(T _x, const Vector2<T> &v2, T _w) : x{_x}, y{v2.x}, z{v2.y}, w{_w} {}
    Vector4(T _x, T _y, const Vector2<T> &v2) : x{_x}, y{_y}, z{v2.x}, w{v2.y} {}
    Vector4(const Vector2<T> &v21, const Vector2<T> &v22) : x{v21.x}, y{v21.y}, z{v22.x}, w{v22.y} {}
    Vector4(const Vector3<T> &v3, T _w) : x{v3.x}, y{v3.y}, z{v3.z}, w{_w} {}
    Vector4(T _x, const Vector3<T> &v3) : x{_x}, y{v3.x}, z{v3.y}, w{v3.z} {}
    Vector4(const Vector3<T> &v3) : x{v3.x}, y{v3.y}, z{v3.z}, w{1} {}
  };

  typedef Vector2<float> Vector2f;
  typedef Vector2<int> Vector2i;
  typedef Vector3<float> Vector3f;
  typedef Vector3<int> Vector3i;
  typedef Vector4<float> Vector4f;
  typedef Vector4<int> Vector4i;

}

#endif // _XRS_VECTOR_HPP_