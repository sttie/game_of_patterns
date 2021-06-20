#pragma once

#include <cstdint>
#include <utility>
#include <stdexcept>

namespace Lib {

    template<typename T>
    class Container {
    public:
        typedef T value_type;

        Container() {
            data = nullptr;
            _size = 0;
            _capacity = 0;
        }

        Container(std::size_t size_)
                : _size(size_), _capacity(size_) {
            data = new T[_size];
        }

        Container(std::initializer_list<T> values)
                : _size(values.size()), _capacity(values.size()) {
            data = new T[_size];

            int i = 0;
            for (auto &value : values) {
                data[i++] = std::move(value);
            }
        }

        Container(const Container& other_container) {
            _size = other_container._size;
            _capacity = other_container._capacity;

            data = new T[_capacity];

            for (std::size_t i = 0; i < _size; i++) {
                data[i] = other_container[i];
            }
        }

        Container(Container&& other_container) {
            _size = other_container._size;
            _capacity = other_container._capacity;
            data = other_container.data;
            other_container.data = nullptr;
        }

        Container& operator=(const Container& other_container) {
            _size = other_container._size;
            std::size_t old_capacity = _capacity;
            _capacity = other_container._capacity;

            if (_capacity != old_capacity) {
                delete[] data;
                data = new T[_capacity]();
            }

            for (std::size_t i = 0; i < _size; i++) {
                data[i] = other_container[i];
            }

            return *this;
        }

        Container& operator=(Container&& other_container) {
            _size = other_container._size;
            std::size_t old_capacity = _capacity;
            _capacity = other_container._capacity;

            if (_capacity != old_capacity) {
                delete[] data;
                data = new T[_capacity];
            }

            for (std::size_t i = 0; i < _size; i++) {
                data[i] = std::move(other_container[i]);
            }

            delete[] other_container.data;
            other_container.data = nullptr;

            return *this;
        }

        void Reserve(std::size_t size_, T default_value = T()) {
            delete[] data;

            _size = size_;
            _capacity = _size;
            data = new T[_size];
            for (std::size_t i = 0; i < _size; i++) {
                data[i] = default_value;
            }
        }

        void PushBack(T value) {
            if (_size >= _capacity) {
                _capacity = _capacity == 0 ? 1 : _capacity * 2;
                T *new_data = new T[_capacity];

                for (int i = 0; i < _size; i++) {
                    new_data[i] = std::move(data[i]);
                }

                delete[] data;
                data = new_data;
            }

            data[_size] = std::move(value);
            _size++;
        }

        T& operator[](std::size_t index) {
            if (index >= _size)
                throw std::runtime_error("Index is out of bounds");

            return data[index];
        }

        const T& operator[](std::size_t index) const {
            if (index >= _size)
                throw std::runtime_error("Index is out of bounds");

            return data[index];
        }

        std::size_t size() const { return _size; }
        std::size_t capacity() const { return _capacity; }

        T* begin() { return data; }

        T* end() { return data + _size; }

        const T* begin() const { return data; }

        const T* end() const { return data + _size; }

    private:
        T* data;
        std::size_t _size;
        std::size_t _capacity;
    };

}