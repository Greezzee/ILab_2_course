#include "Vector.h"
#include <cmath>
namespace matrix {
    template <typename T>
    class Matrix final
    {
    public:
        Matrix() {} //Пустая матрица
        Matrix(size_t n, size_t m, T elem = T{}) : //Матрица n на m, заполненный elem (по умолчанию стандартное значение типа)
            data_(Vector<Vector<T>>(n, Vector<T>(m, elem))) {}
        Matrix(size_t n, size_t m, const T* data) : //Матрица n на m, заполненная из двумерного массива
            data_(Vector<Vector<T>>(n, Vector<T>(m))) {
                for (size_t i = 0; i < n; i++)
                    for (size_t j = 0; j < m; j++)
                        data_[i][j] = data[i * m + j];
        }
        Matrix(const std::vector<std::vector<T>>& base) : //Матрица, заполненная согласно данному вектору. Вектор должен быть прямоугольным
            data_(Vector<Vector<T>>(base.size(), Vector<T>(base.size() == 0 ? 0 : base[0].size()))) {
            for (size_t i = 0; i < base.size(); i++)
                data_[i] = base[i];
        }
        Matrix(const Matrix<T>& that) : //Конструктор копирования
            data_(that.data_) {}
        Matrix(const Vector<Vector<T>>& that) : // Матрица, заполненная из данного столбца столбцов (внешний столбец отвечает за строки, внутренний за столбцыы)
            data_(that) {}

        ~Matrix() {};

        size_t GetRowCount() const {
            return GetColCount() == 0 ? 0 : data_[0].GetLen();
        }

        size_t GetColCount() const {
            return data_.GetLen();
        }

        void PushCol(Vector<T> col) {
            assert(GetRowCount() == 0 || col.GetLen() == GetRowCount());
            data_.Push(col);
        }
        Vector<T> PopCol() {
            return data_.Pop();
        }
        void SwapCol(size_t fcol, size_t scol) {
            data_.Swap(fcol, scol);
        }

        void PushRow(Vector<T> row) {
            assert(GetColCount() == 0 || row.GetLen() == GetColCount());
            if (GetColCount() == 0) {
                for (size_t i = 0; i < row.GetLen(); i++)
                    data_.Push(Vector<T>(1, row[i]));
            }
            else {
                for (size_t i = 0; i < GetColCount(); i++)
                    data_[i].Push(row[i]);
            }
        }

        Vector<T> PopRow() {
            Vector<T> out{};
            for (size_t i = 0; i < GetColCount(); i++)
                out.Push(data_[i].Pop());
            return out;
        }

        void SwapRow(size_t frow, size_t srow) {
            assert (frow < GetRowCount() && srow < GetRowCount());
            for (size_t i = 0; i < GetColCount(); i++) {
                T buf = data_[i][frow];
                data_[i][frow] = data_[i][srow];
                data_[i][srow] = buf;
            }
        }

        Matrix<T> Slice(size_t begin_col, size_t end_col, size_t begin_row, size_t end_row) const {
            Matrix<T> out (end_col - begin_col, end_row - begin_row);
            for (size_t i = begin_col; i < end_col; i++)
                out[i - begin_col] = data_[i].Slice(begin_row, end_row);
            return out;
        }

        void ConnectRight(const Matrix<T>& that) {
            assert(GetRowCount() == that.GetRowCount());
            data_.Connect(that.data_);
        }
        void ConnectDown(const Matrix<T>& that) {
            assert(GetColCount() == that.GetColCount());
            for (size_t i = 0; i < GetColCount(); i++)
                data_[i].Connect(that[i]);
        }

        Matrix<T> Transpose() const {
            Matrix<T> out{GetRowCount(), GetColCount()};
            for (size_t i = 0; i < GetColCount(); i++)
                for (size_t j = 0; j < GetRowCount(); j++)
                    out[j][i] = data_[i][j];
            return out;
        }

        long double Determinant() const {
            assert(GetColCount() == GetRowCount());

            Matrix<long double>* temp = new Matrix<long double>{GetColCount(), GetRowCount()};
            for (size_t i = 0; i < GetColCount(); i++)
                for (size_t j = 0; j < GetRowCount(); j++)
                    (*temp)[i][j] = static_cast<long double>(data_[i][j]);
            long double out = 1;
            long double EPS = 1e-6;

            for (size_t k = 0; k < GetColCount(); k++) {
                int sign = 1;
                for (size_t i = k; i < GetColCount(); i++) {
                    if (std::abs((*temp)[i][k]) > EPS) {
                        temp->SwapCol(k, i);
                        if (k != i)
                            sign *= -1;
                        break;
                    }
                }
                if (std::abs((*temp)[k][k]) < EPS) {
                    return 0;
                }

                for (size_t i = k + 1; i < GetColCount(); i++)
                    (*temp)[i] -= (*temp)[k] * ((*temp)[i][k] / (*temp)[k][k]);
                out *= (*temp)[k][k] * sign;
            }

            delete temp;
            //printf("OK\n");
            long double sign = 1;
            if (out < 0)
                sign *= -1;
            return static_cast<T>(sign * (std::abs(out) + EPS));
        }

        Matrix& operator=(const Matrix<T>& that) {
            data_ = that.data_;
            return *this;
        }

        const Vector<T>& operator[](size_t i) const {
            assert(i < GetColCount());
            return data_[i];
        }
        Vector<T>& operator[](size_t i) {
            assert(i < GetColCount());
            return data_[i];
        }

        Matrix operator-() const {
            return Matrix<T>(-data_);
        }

        Matrix& operator+=(const Matrix<T>& that) {
            assert(GetColCount() == that.GetColCount());
            assert(GetRowCount() == that.GetRowCount());
            data_ += that.data_;
            return *this;
        }
        Matrix& operator-=(const Matrix<T>& that) {
            *this += (-that);
            return *this;
        }

        Matrix& operator*=(const T& that) {
            for (size_t i = 0; i < GetColCount(); i++)
                data_[i] *= that;
            return *this;
        }

        Matrix& operator/=(const T& that) {
            for (size_t i = 0; i < GetColCount(); i++)
                data_[i] /= that;
            return *this;
        }


    private:
        Vector<Vector<T>> data_;
    };


    template <typename T> Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        Matrix<T> out = lhs;
        out += rhs;
        return out;
    }
    template <typename T> Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        return lhs + (-rhs);
    }

    template <typename T> Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs) {
        Matrix<T> out = lhs;
        out *= rhs;
        return out;
    }
    template <typename T> Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs) {
        return rhs * lhs;
    }
    template <typename T> Matrix<T> operator/(const Matrix<T>& lhs, const T& rhs) {
        Matrix<T> out = lhs;
        out /= rhs;
        return out;
    }
    template <typename T> Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        assert(lhs.GetColCount() == rhs.GetRowCount());
        Matrix<T> lhs_transposed = lhs.Transpose();
        Matrix<T> out{rhs.GetColCount(), lhs.GetRowCount()};
        for (size_t i = 0; i < lhs_transposed.GetColCount(); i++)
            for(size_t j = 0; j < rhs.GetColCount(); j++)
                out[j][i] = matrix::DotProduct(lhs_transposed[i], rhs[j]);
        return out;
    }
    template <typename T> bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        if (lhs.GetColCount() != rhs.GetColCount())
            return false;
        for (size_t i = 0; i < lhs.GetColCount(); i++)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }
    template <typename T> bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        return !(lhs == rhs);
    }
}