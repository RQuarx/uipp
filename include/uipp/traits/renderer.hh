#pragma once
#include <concepts>

#include "uipp/surface.hh"
#include "uipp/result.hh"
#include "uipp/window.hh"


namespace uipp::traits
{
    template <typename T>
    concept renderer = requires(T &renderer, window &target) {
        { renderer.create_surface(target) } noexcept -> std::same_as<result<surface>>;
    };
}
