#pragma once
#include <bitset>
#include <cstddef>
#include <unordered_map>

#include "uipp/color.hh"
#include "uipp/draw_list.hh"
#include "uipp/event.hh"
#include "uipp/math/rect.hh"


namespace uipp
{
    enum class [[uipp_public]] widget_id : std::size_t
    {
    };
}

template <>
struct std::hash<uipp::widget_id>
{
    [[nodiscard]]
    auto operator()(uipp::widget_id id) const noexcept -> std::size_t
    { return std::size_t(id); }
};

namespace uipp
{
    struct [[uipp_public]] widget_state
    {
        std::bitset<2> state;


        constexpr void set_hovered(bool hovered) noexcept { state.set(0, hovered); }
        constexpr void set_active(bool active) noexcept { state.set(1, active); }

        [[nodiscard]] constexpr auto hovered() const noexcept -> bool { return state.test(0); }
        [[nodiscard]] constexpr auto active() const noexcept -> bool { return state.test(1); }
    };


    struct [[uipp_public]] style_sheet
    {
        color bg { 45, 45, 48, 255 };
        color bg_hover { 60, 60, 64, 255 };
        color bg_active { 30, 30, 32, 255 };
        color text { 235, 235, 235, 255 };

        float corner_radius = 4.0F;
        float padding       = 8.0F;
        float spacing       = 6.0F;


        [[nodiscard]]
        static auto default_dark() noexcept -> style_sheet
        {
            return {
                { 45,  45,  48,  255 },
                { 60,  60,  64,  255 },
                { 30,  30,  32,  255 },
                { 235, 235, 235, 255 },
                4.0F,
                8.0F,
                6.0F,
            };
        }
    };


    class [[uipp_public]] context
    {
    public:
        auto begin_frame(math::ivec2 viewport_size) noexcept -> void;
        auto end_frame() noexcept -> void;

        auto handle_event(const event &ev) noexcept -> void;

        auto push_column(math::vec2 origin) noexcept -> void;
        auto push_row(math::vec2 origin) noexcept -> void;
        auto pop_layout() noexcept -> void;

        [[nodiscard]] auto next_widget_rect(math::vec2 size) noexcept -> math::rect;

        [[nodiscard]] auto make_id(std::string_view label) const noexcept -> widget_id;
        [[nodiscard]] auto state_for(widget_id id) noexcept -> widget_state &;

        [[nodiscard]] auto draw_list() noexcept -> draw_list &;

        [[nodiscard]] auto style() const noexcept -> const style_sheet &;
        [[nodiscard]] auto style() noexcept -> style_sheet &;

        [[nodiscard]] auto mouse_pos() const noexcept -> math::vec2;
        [[nodiscard]] auto mouse_down() const noexcept -> bool;
        [[nodiscard]] auto mouse_pressed() const noexcept -> bool;
        [[nodiscard]] auto mouse_released() const noexcept -> bool;

    private:
        struct layout_frame
        {
            math::vec2 cursor;
            math::vec2 origin;
            bool       horizontal;
        };

        uipp::draw_list m_draw_list;
        style_sheet     m_style;

        std::unordered_map<widget_id, widget_state> m_widget_states;
        std::vector<layout_frame>                   m_layout_stack;

        math::vec2  m_mouse_pos;
        bool        m_mouse_down      = false;
        bool        m_prev_mouse_down = false;
        math::ivec2 m_viewport_size;
    };
}

