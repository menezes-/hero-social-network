#pragma once

#include <memory>
#include <random>

template<typename T, typename... Args>
inline std::unique_ptr<T> make_unique(Args &&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


inline std::mt19937 radomNumberGenerator() {
    std::random_device rd;
    std::mt19937 result(rd());
    return result;
}

template<class T>
inline const T &max(const T &a, const T &b) {
    return (a < b) ? b : a;
}

template<class T>
inline const T &min(const T &a, const T &b) {
    return (b < a) ? b : a;
}