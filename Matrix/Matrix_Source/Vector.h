#include <vector>
#include <cassert>
#include <cstdio>

namespace matrix {

template <typename T>
class Vector final
{
public:
    Vector() {} //Пустой столбец
    Vector(size_t n, T elem = T{}) : //Столбец длины n, заполненный elem (по умолчанию стандартное значение типа)
        data_(std::vector<T>(n, elem)) {}
    Vector(size_t n, const T* data) : //Столбец длины n, заполненная из массива
        data_(std::vector<T>(n)) {
            for (size_t i = 0; i < n; i++)
                data_[i] = data[i];
        }
    Vector(const std::vector<T>& base) : //Столбец, заполненный согласно данному вектору
        data_(base) {}
    Vector(const Vector<T>& that) : //Конструктор копирования
        data_(that.data_) {}

    ~Vector() {};

    size_t GetLen() const { return data_.size(); }

    void Resize(size_t new_size) { data_.resize(new_size); }

    Vector<T> Slice(size_t begin, size_t end) const {
        assert(end >= begin && end < GetLen() && begin < GetLen());
        Vector<T> out(end - begin);
        for (size_t i = begin; i < end; i++)
            out[i - begin] = data_[i];
        return out;
    }

    void Push(T elem) { data_.push_back(elem); }
    T Pop() {
        assert(GetLen() > 0);
        T buf = data_.back();
        data_.pop_back();
        return buf;
    }
    void Swap(size_t fn, size_t sn) {
        assert(fn < GetLen());
        assert(sn < GetLen());
        T buf = data_[fn];
        data_[fn] = data_[sn];
        data_[sn] = buf;
    }

    void Connect(const Vector<T>& that) {
        data_.insert(data_.end(), that.data_.begin(), that.data_.end());
    }

    Vector& operator=(const Vector<T>& that) {
        data_ = that.data_;
        return *this;
    }

    const T& operator[](size_t i) const {
        assert(i < GetLen());
        return data_[i];
    }
    T& operator[](size_t i) {
        assert(i < GetLen());
        return data_[i];
    }

    Vector operator-() const {
        Vector<T> out{*this};
        for (size_t i = 0; i < GetLen(); i++)
            out[i] = -data_[i];
        return out;
    }

    Vector& operator+=(const Vector<T>& that) {
        assert(GetLen() == that.GetLen());
        for (size_t i = 0; i < GetLen(); i++)
            data_[i] += that[i];
        return *this;
    }
    Vector& operator-=(const Vector<T>& that) {
        *this += (-that);
        return *this;
    }

    Vector& operator*=(const T& that) {
        for (size_t i = 0; i < GetLen(); i++)
            data_[i] *= that;
        return *this;
    }
    Vector& operator/=(const T& that) {
        for (size_t i = 0; i < GetLen(); i++)
            data_[i] /= that;
        return *this;
    }

private:
    std::vector<T> data_;
};

template <typename T> T DotProduct(const Vector<T>& lhs, const Vector<T>& rhs) {
    assert(lhs.GetLen() == rhs.GetLen());
    T out = T{};
    for (size_t i = 0; i < lhs.GetLen(); i++)
        out += lhs[i] * rhs[i];
    return out;
}

template <typename T> Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
    Vector<T> out = lhs;
    out += rhs;
    return out;
}
template <typename T> Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs) {
    return lhs + (-rhs);
}

template <typename T> Vector<T> operator*(const Vector<T>& lhs, const T& rhs) {
    Vector<T> out = lhs;
    out *= rhs;
    return out;
}
template <typename T> Vector<T> operator*(const T& lhs, const Vector<T>& rhs) {
    return rhs * lhs;
}
template <typename T> Vector<T> operator/(const Vector<T>& lhs, const T& rhs) {
    Vector<T> out = lhs;
    out /= rhs;
    return out;
}

template <typename T> bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.GetLen() != rhs.GetLen())
        return false;
    for (size_t i = 0; i < lhs.GetLen(); i++)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}
template <typename T> bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

}