#pragma once

#include <memory>
#include <random>
#include <iterator>

template<typename T, typename... Args>
inline std::unique_ptr<T> make_unique(Args &&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


inline std::mt19937 radomNumberGenerator() {
    std::random_device rd;
    std::mt19937 result(rd());
    return result;
}


template<class T, std::size_t N>
std::ostream &operator<<(std::ostream &o, const std::array<T, N> &arr) {
    std::copy(arr.cbegin(), arr.cend(), std::ostream_iterator<T>(o, " "));
    return o;
}