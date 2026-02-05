#pragma once

#ifndef _XRS_MATRIX_HPP_
#define _XRS_MATRIX_HPP_

namespace xrs
{

struct Matrix
{
  union
  {
    struct Mat
    {
      float
      m00{1}, m01{}, m02{}, m03{},
      m10{}, m11{1}, m12{}, m13{},
      m20{}, m21{}, m22{1}, m23{},
      m30{}, m31{}, m32{}, m33{1};
    };
    float mem[16];
  } data;

  Matrix() = default;
  Matrix(const float *const _data, int rows, int cols)
  {
    for (int x = 0; x < cols; x++)
      for (int y = 0; y < rows; y++)
        data.mem[x + y] = _data[x + y];
  }
};

}

#endif // _XRS_MATRIX_HPP_