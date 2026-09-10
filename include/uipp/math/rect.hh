#pragma once
#include "uipp/math/vector.hh"


namespace uipp::math
{
    template <arithmetic_type T>
    struct trect
    {
        tvec2<T> position;
        tvec2<T> size;
    };


    using rect  = trect<float>;
    using drect = trect<double>;
    using irect = trect<std::int32_t>;
    using urect = trect<std::uint32_t>;
}
