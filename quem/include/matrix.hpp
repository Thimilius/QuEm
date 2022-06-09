#pragma once

#include <cassert>
#include <iostream>

#include "qubit.hpp"
#include "types.hpp"

namespace QuEm {

  template<typename T>
  class MatrixT {
  public:
    MatrixT(size_t rows, size_t columns) : m_rows(rows), m_columns(columns) {
      m_elements = new T[rows * columns];
    }
    
    MatrixT(size_t rows, size_t columns, std::initializer_list<T> elements) : m_rows(rows), m_columns(columns) {
      assert(elements.size() == rows * columns);

      m_elements = new T[rows * columns];
      size_t i = 0;
      for (auto element : elements) {
        m_elements[i] = element;
        i++;
      }
    }

    MatrixT(const MatrixT &other) : m_rows(other.m_rows), m_columns(other.m_columns) {
      m_elements = new T[m_rows * m_columns];
      for (size_t i = 0; i < m_rows * m_columns; i++) {
        m_elements[i] = other.m_elements[i];
      }
    }
    
    ~MatrixT() {
      delete[] m_elements;
    }
  public:
    MatrixT &operator=(const MatrixT &other) {
      if (this == &other) {
        return *this;
      }
      
      delete[] m_elements;
      m_elements = new T[m_rows * m_columns];
      for (size_t i = 0; i < m_rows * m_columns; i++) {
        m_elements[i] = other.m_elements[i];
      }
      
      return *this;
    }

    T &operator()(size_t row, size_t column) {
      return m_elements[column + row * m_columns];
    }

    const T &operator()(size_t row, size_t column) const {
      return m_elements[column + row * m_columns];
    }
    
    Qubit operator*(Qubit &qubit) const {
      assert(m_rows == m_columns && m_rows == qubit.GetSize());

      size_t size = m_rows;

      std::vector<Complex> new_data;
      new_data.resize(qubit.GetSize());
      
      std::vector<Complex> &data = qubit.GetData();
      for (size_t y = 0; y < size; y++) {
          Complex sum = static_cast<FloatType>(0.0);
          for (size_t e = 0; e < size; e++) {
            sum += m_elements[e + y * size] * data[e];
          }
          new_data[y] = sum;
      }
      
      return Qubit(new_data);
    }

    void Print() {
      for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_columns; j++) {
          std::cout << (*this)(i, j) << " "; 
        }
        std::cout << std::endl;
      }
    }
  public:
    static MatrixT Tensor(const MatrixT &a, const MatrixT &b) {
      size_t rows_b = b.m_rows;
      size_t columns_b = b.m_columns;
      size_t rows = a.m_rows * rows_b;
      size_t columns = a.m_columns * columns_b;

      MatrixT result = MatrixT(rows, columns);
      for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
          result(i, j) = a(i / rows_b , j / columns_b) * b(i % rows_b , j % columns_b);
        } 
      }
      
      return result;
    }
  private:
    T *m_elements = nullptr;
    size_t m_rows;
    size_t m_columns;
  };

  using Matrix = MatrixT<Complex>;
  
}
