#pragma once
#include <cmath>
#include <concepts>
#include <cstdint>
#include <format>
#include <ostream>
#include <sstream>

#include "uipp/result.hh"


namespace uipp::math
{
    template <typename T>
    concept arithmetic_type = std::is_arithmetic_v<T>;

    template <typename T>
    concept vector_like = requires {
        typename T::value_type;
        typename T::size_type;
        { T::size() } -> std::convertible_to<typename T::size_type>;
    } and std::is_arithmetic_v<typename T::value_type>;

    template <typename T>
    concept float_vector_Like = vector_like<T> and std::floating_point<typename T::value_type>;


    template <arithmetic_type T>
    struct tvec2
    {
        using size_type  = std::size_t;
        using value_type = T;


        union
        {
            T x, r, s;
        };
        union
        {
            T y, g, t;
        };


        constexpr tvec2() noexcept : x { 0 }, y { 0 } {}
        constexpr tvec2(T x, T y) noexcept : x { x }, y { y } {}
        explicit constexpr tvec2(T scalar) noexcept : x { scalar }, y { scalar } {}

        [[nodiscard]]
        constexpr auto at(size_type i) -> T &
        {
            if (i > 2) throw error { "attempted to access out-of-range value ({} >= 2)", i };
            return reinterpret_cast<T *>(this)->at(i);
        }

        [[nodiscard]]
        constexpr auto at(size_type i) const -> const T &
        {
            if (i > 2) throw error { "attempted to access out-of-range value ({} >= 2)", i };
            return reinterpret_cast<const T *>(this)->at(i);
        }

        [[nodiscard]] static constexpr auto size() noexcept -> size_type { return 2; }
    };


    template <arithmetic_type T>
    struct tvec3
    {
        union
        {
            T x, r, s;
        };
        union
        {
            T y, g, t;
        };
        union
        {
            T z, b, p;
        };


        constexpr tvec3() noexcept : x { 0 }, y { 0 }, z { 0 } {}
        constexpr tvec3(T x, T y, T z) noexcept : x { x }, y { y }, z { z } {}
        explicit constexpr tvec3(T scalar) noexcept : x { scalar }, y { scalar }, z { scalar } {}

        [[nodiscard]]
        constexpr auto at(std::size_t i) -> T &
        {
            if (i > 3) throw error { "attempted to access out-of-range value ({} >= 3)", i };
            return reinterpret_cast<T *>(this)->at(i);
        }

        [[nodiscard]]
        constexpr auto at(std::size_t i) const -> const T &
        {
            if (i > 3) throw error { "attempted to access out-of-range value ({} >= 3)", i };
            return reinterpret_cast<const T *>(this)->at(i);
        }

        [[nodiscard]] static constexpr auto size() noexcept -> std::size_t { return 3; }
        [[nodiscard]] constexpr auto        xy() const noexcept -> tvec2<T> { return { x, y }; }
        [[nodiscard]] constexpr auto        yz() const noexcept -> tvec2<T> { return { y, z }; }
    };


    template <arithmetic_type T>
    struct tvec4
    {
        union
        {
            T x, r, s;
        };
        union
        {
            T y, g, t;
        };
        union
        {
            T z, b, p;
        };
        union
        {
            T w, a, q;
        };


        constexpr tvec4() noexcept : x { 0 }, y { 0 }, z { 0 }, w { 0 } {}
        constexpr tvec4(T x, T y, T z, T w) noexcept : x { x }, y { y }, z { z }, w { w } {}
        explicit constexpr tvec4(T scalar) noexcept
            : x { scalar }, y { scalar }, z { scalar }, w { scalar }
        {
        }

        [[nodiscard]]
        constexpr auto at(std::size_t i) -> T &
        {
            if (i > 4) throw error { "attempted to access out-of-range value ({} >= 4)", i };
            return reinterpret_cast<T *>(this)->at(i);
        }

        [[nodiscard]]
        constexpr auto at(std::size_t i) const -> const T &
        {
            if (i > 4) throw error { "attempted to access out-of-range value ({} >= 4)", i };
            return reinterpret_cast<const T *>(this)->at(i);
        }

        [[nodiscard]] static constexpr auto size() noexcept -> std::size_t { return 4; }
        [[nodiscard]] constexpr auto        xyz() const noexcept -> tvec3<T> { return { x, y, z }; }
        [[nodiscard]] constexpr auto        xy() const noexcept -> tvec2<T> { return { x, y }; }
    };


    using vec2  = tvec2<float>;
    using dvec2 = tvec2<double>;
    using ivec2 = tvec2<std::int32_t>;
    using uvec2 = tvec2<std::uint32_t>;
    using vec3  = tvec3<float>;
    using dvec3 = tvec3<double>;
    using ivec3 = tvec3<std::int32_t>;
    using uvec3 = tvec3<std::uint32_t>;
    using vec4  = tvec4<float>;
    using dvec4 = tvec4<double>;
    using ivec4 = tvec4<std::int32_t>;
    using uvec4 = tvec4<std::uint32_t>;


    template <vector_like T>
    auto operator+=(T &a, const T &b) -> T &
    {
        for (typename T::size_type i = 0; i < T::length(); i++) a.at(i) += b.at(i);
        return a;
    }

    template <vector_like T>
    auto operator-=(T &a, const T &b) -> T &
    {
        for (typename T::size_type i = 0; i < T::length(); i++) a.at(i) -= b.at(i);
        return a;
    }

    template <vector_like T>
    auto operator*=(T &a, typename T::value_type s) -> T &
    {
        for (typename T::size_type i = 0; i < T::length(); i++) a.at(i) *= s;
        return a;
    }

    template <vector_like T>
    auto operator/=(T &a, typename T::value_type s) -> T &
    {
        for (typename T::size_type i = 0; i < T::length(); i++) a.at(i) /= s;
        return a;
    }

    template <vector_like T>
    auto operator+(T a, const T &b) -> T
    {
        a += b;
        return a;
    }

    template <vector_like T>
    auto operator-(T a, const T &b) -> T
    {
        a -= b;
        return a;
    }

    template <vector_like T>
    auto operator*(T a, typename T::value_type s) -> T
    {
        a *= s;
        return a;
    }

    template <vector_like T>
    auto operator*(typename T::value_type s, T a) -> T
    {
        a *= s;
        return a;
    }

    template <vector_like T>
    auto operator/(T a, typename T::value_type s) -> T
    {
        a /= s;
        return a;
    }

    template <vector_like T>
    auto operator-(const T &v) -> T
    {
        T out;
        for (typename T::size_type i = 0; i < T::length(); i++) out.at(i) = -v.at(i);
        return out;
    }

    template <vector_like T>
    auto operator==(const T &a, const T &b) -> bool
    {
        for (typename T::size_type i = 0; i < T::length(); i++)
            if (a.at(i) != b.at(i)) return false;
        return true;
    }

    template <vector_like T>
    auto operator!=(const T &a, const T &b) -> bool
    { return !(a == b); }

    template <vector_like T>
    auto operator<<(std::ostream &os, const T &v) -> std::ostream &
    {
        os << "vec" << T::length() << "(";

        for (typename T::size_type i = 0; i < T::length(); i++)
        {
            os << v.at(i);
            if (i + 1 < T::length()) os << ", ";
        }

        return os << ")";
    }

    template <vector_like T>
    auto dot(const T &a, const T &b) -> typename T::value_type
    {
        typename T::value_type r {};
        for (typename T::size_type i = 0; i < T::length(); i++) r += a.at(i) * b.at(i);
        return r;
    }

    template <arithmetic_type T>
    auto cross(const tvec3<T> &a, const tvec3<T> &b) -> tvec3<T>
    { return tvec3<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

    template <float_vector_Like T>
    auto length2(const T &v) -> typename T::value_type
    { return dot(v, v); }

    template <float_vector_Like T>
    auto length(const T &v) -> typename T::value_type
    { return std::sqrt(length2(v)); }

    template <float_vector_Like T>
    auto distance(const T &a, const T &b) -> typename T::value_type
    { return length(a - b); }

    template <float_vector_Like T>
    auto normalize(const T &v) -> T
    {
        auto l = length(v);
        return l > typename T::value_type { 0 } ? v * (typename T::value_type { 1 } / l) : v;
    }

    template <float_vector_Like T>
    auto reflect(const T &I, const T &N) -> T
    { return I - N * (typename T::value_type { 2 } * dot(N, I)); }

    template <vector_like T>
    auto mix(const T &a, const T &b, typename T::value_type t) -> T
    {
        T out;
        for (typename T::size_type i = 0; i < T::length(); i++)
            out.at(i) = a.at(i) + t * (b.at(i) - a.at(i));
        return out;
    }

    template <vector_like T>
    auto clamp(const T &v, typename T::value_type lo, typename T::value_type hi) -> T
    {
        T out;
        for (typename T::size_type i = 0; i < T::length(); i++)
            out.at(i) = std::max(lo, std::min(v.at(i), hi));
        return out;
    }

    template <vector_like T>
    auto min(const T &a, const T &b) -> T
    {
        T out;
        for (typename T::size_type i = 0; i < T::length(); i++)
            out.at(i) = std::min(a.at(i), b.at(i));
        return out;
    }
    template <vector_like T>
    auto max(const T &a, const T &b) -> T
    {
        T out;
        for (typename T::size_type i = 0; i < T::length(); i++)
            out.at(i) = std::max(a.at(i), b.at(i));
        return out;
    }
    template <vector_like T>
    auto abs(const T &v) -> T
    {
        T out;
        for (typename T::size_type i = 0; i < T::length(); i++)
            out.at(i) = v.at(i) < typename T::value_type { 0 } ? -v.at(i) : v.at(i);
        return out;
    }

    template <arithmetic_type T>
    constexpr auto mix(T a, T b, T t) -> T
    { return a + t * (b - a); }

    template <arithmetic_type T>
    constexpr auto clamp(T x, T lo, T hi) -> T
    { return std::max(lo, std::min(x, hi)); }

}


template <uipp::math::vector_like T>
struct std::formatter<T>
{
    char bracket = U'<';


    template <typename ParseContext>
    constexpr auto parse(ParseContext &ctx) -> ParseContext::iterator
    {
        auto it = ctx.begin();

        if (it == ctx.end()) return it;

        bracket = *it;
        ++it;

        if (it != ctx.end() and *it != '}')
            throw std::format_error { std::format("Invalid format args for uipp::math::vec{}",
                                                  T::size()) };
        return it;
    }


    template <typename FmtContext>
    auto format(const T &vec, FmtContext &ctx) const -> FmtContext::iterator
    {
        std::ostringstream oss;

        oss << "vec" << T::length() << bracket;

        for (typename T::size_type i = 0; i < T::length(); i++)
        {
            oss << vec.at(i);
            if (i + 1 < T::length()) oss << ", ";
        }

        oss << bracket;

        return std::ranges::copy(std::move(oss).str(), ctx.out()).out;
    }
};
