#pragma once

#include <memory>


template<typename T>
struct is_vector {
    static constexpr bool value = false;
};

template<typename T>
struct is_vector<std::vector<T>> {
    static constexpr bool value = true;
};

template<typename T>
struct is_vector<Lib::Container<T>> {
    static constexpr bool value = true;
};


template <typename T>
struct is_smart_pointer {
    static constexpr bool value = false;
};

template <typename T>
struct is_smart_pointer<std::shared_ptr<T>> {
    static constexpr bool value = true;
};

template <typename T>
struct is_smart_pointer<std::unique_ptr<T>> {
    static constexpr bool value = true;
};