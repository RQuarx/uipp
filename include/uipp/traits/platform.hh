#pragma once
#include "uipp/math/vector.hh"
#include "uipp/window.hh"


namespace uipp::traits
{
    template <typename T>
    concept platform = requires(T &platform, const char *title, math::ivec2 size) {
        { T::create() } noexcept -> std::same_as<result<T>>;
        { platform.create_window(title, size) } noexcept -> std::same_as<result<window>>;
    };
}
