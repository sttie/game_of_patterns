#pragma once

#include <vector>

#include "../lib/my_container.hpp"


void TestContainer() {
    Lib::Container<int> cont = {2, 1, 5, 10, 11111, 42, 5};
    std::vector<int> vec = {2, 1, 5, 10, 11111, 42, 5};
    ASSERT(cont.size() == 7);

    // Проверяем, правильно ли записались числа
    for (int i = 0; i < vec.size(); ++i)
        ASSERT(cont[i] == vec[i]);

    for (int i = 0; i < 5; ++i) {
        cont.PushBack(i + 10);
        vec.push_back(i + 10);
    }
    ASSERT(cont.size() == 12);

    // Проверяем, правильно ли записались числа
    for (int i = 0; i < vec.size(); ++i)
        ASSERT(cont[i] == vec[i]);

    int old_size = cont.size(), old_capacity = cont.capacity();
    Lib::Container<int> moved_cont = std::move(cont);
    ASSERT(moved_cont.size() == old_size && moved_cont.capacity() == old_capacity);
    for (int i = 0; i < vec.size(); ++i)
        ASSERT(moved_cont[i] == vec[i]);
}