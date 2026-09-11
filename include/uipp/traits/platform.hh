#pragma once
#include "uipp/event.hh"
#include "uipp/math/vector.hh"
#include "uipp/window.hh"


namespace uipp::traits
{
    template <typename T, typename F>
    concept platform = requires(
        T &platform, const char *title, math::ivec2 size, F &&callback, const event &ev) {
        { platform.create_window(title, size) } noexcept -> std::same_as<result<window>>;
        { platform.poll_events(callback) } noexcept -> std::same_as<result<bool>>;
        { callback(ev) } noexcept -> std::same_as<result<bool>>;
    };
}
