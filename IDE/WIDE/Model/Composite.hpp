#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <vector>

template <typename T>
struct Composite
{
    T value;
    std::vector<Composite<T>> children;

    Composite(T v) : value(v), children()
    {}
};

#endif // COMPOSITE_HPP
