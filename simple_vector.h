#ifndef EXPRESSES_SIMPLE_VECTOR_H
#define EXPRESSES_SIMPLE_VECTOR_H

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector()
            : data_begin(nullptr),
              data_end(nullptr),
              capacity(0),
              size_(0) {}

    explicit SimpleVector(size_t size) : capacity(size), size_(size) {
        data_begin = new T[size];
        data_end = data_begin + size;
    }
    ~SimpleVector() {
        delete[] data_begin;
    }

    T& operator[](size_t index) {
        return data_begin[index];
    }

    T* begin() {
        return data_begin;
    }
    T* end() {
        return data_end;
    }

    [[nodiscard]] size_t Size() const {
        return size_;
    }
    [[nodiscard]] size_t Capacity() const {
        return capacity;
    }
    void PushBack(const T& value) {
        if (capacity == 0) {
            data_begin = new T[1];
            *data_begin = value;
            data_end = data_begin + 1;
            ++capacity;
            size_ = 1;
        } else {
            if (capacity == size_) {
                capacity *= 2;
                T* new_data = new T[capacity];
                std::copy(data_begin, data_end, new_data);
                delete [] data_begin;
                data_begin = new_data;
            }
            data_begin[size_] = value;
            ++size_;
            data_end = data_begin + size_;
        }
    }

private:
    T* data_begin;
    T* data_end;
    size_t capacity;
    size_t size_;
};

#endif //EXPRESSES_SIMPLE_VECTOR_H
