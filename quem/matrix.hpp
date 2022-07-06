#pragma once

#include <cassert>
#include <iostream>

#include "register.hpp"
#include "types.hpp"

namespace QuEm {

  class Matrix {
  public:
    Matrix(uint64_t rows, uint64_t columns) : m_rows(rows), m_columns(columns) {
      m_elements.resize(rows * columns);
    }
    
    Matrix(uint64_t rows, uint64_t columns, const std::vector<Complex> &elements) : m_rows(rows), m_columns(columns), m_elements(elements) {
      assert(elements.size() == rows * columns);
    }
  public:
    Complex &operator()(uint64_t row, uint64_t column) {
      return m_elements[column + row * m_columns];
    }

    const Complex &operator()(uint64_t row, uint64_t column) const {
      return m_elements[column + row * m_columns];
    }
    
    Register operator*(Register &reg) const {
      assert(m_rows == m_columns && m_rows == reg.GetSize());

      uint64_t size = m_rows;

      std::vector<Complex> new_data;
      new_data.resize(reg.GetSize());
      
      std::vector<Complex> &data = reg.GetAmplitudes();
      for (uint64_t y = 0; y < size; y++) {
          Complex sum = static_cast<FloatType>(0.0);
          for (uint64_t e = 0; e < size; e++) {
            sum += m_elements[e + y * size] * data[e];
          }
          new_data[y] = sum;
      }
      
      return Register(new_data);
    }

    void Print() const {
      for (uint64_t i = 0; i < m_rows; i++) {
        for (uint64_t j = 0; j < m_columns; j++) {
          std::cout << (*this)(i, j) << " "; 
        }
        std::cout << std::endl;
      }
    }
  public:
    static Matrix Tensor(const Matrix &a, const Matrix &b) {
      uint64_t rows_b = b.m_rows;
      uint64_t columns_b = b.m_columns;
      uint64_t rows = a.m_rows * rows_b;
      uint64_t columns = a.m_columns * columns_b;

      Matrix result = Matrix(rows, columns);
      for (uint64_t i = 0; i < rows; i++) {
        for (uint64_t j = 0; j < columns; j++) {
          result(i, j) = a(i / rows_b , j / columns_b) * b(i % rows_b , j % columns_b);
        } 
      }
      
      return result;
    }
  private:
    uint64_t m_rows;
    uint64_t m_columns;
    std::vector<Complex> m_elements;
  };

}
