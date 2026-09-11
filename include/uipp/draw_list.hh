#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

#include "uipp/color.hh"
#include "uipp/math/rect.hh"
#include "uipp/math/vector.hh"


namespace uipp
{
    using font_id    = std::uint32_t;
    using texture_id = std::uint32_t;


    struct [[uipp_public]] cmd_rect
    {
        math::rect bounds;
        color      fill;
        float      corner_radius = 0.0F;
    };


    struct [[uipp_public]] cmd_text
    {
        math::vec2  pos;
        font_id     font;
        float       size;
        color       fill;
        std::string text;
    };


    struct [[uipp_public]] cmd_texture
    {
        math::rect dst;
        math::rect src_uv; /* 0...1 normalized */
        texture_id texture;
        color      tint { 255, 255, 255, 255 };
    };


    struct [[uipp_public]] cmd_push_clip
    {
        math::rect bounds;
    };


    struct [[uipp_public]] cmd_pop_clip
    {
    };


    using draw_command = std::variant<cmd_rect, cmd_text, cmd_texture, cmd_push_clip, cmd_pop_clip>;


    class [[uipp_public]] draw_list
    {
    public:
        void clear() noexcept;

        void rect(math::rect bounds, color fill, float corner_radius = 0.0F);
        void text(math::vec2 pos, font_id font, float size, color fill, std::string_view s);
        void texture(math::rect dst,
                     math::rect src_uv,
                     texture_id tex,
                     color      tint = { 255, 255, 255, 255 });

        void push_clip(math::rect bounds);
        void pop_clip();

        [[nodiscard]] auto commands() const noexcept -> const std::vector<draw_command> &;

    private:
        std::vector<draw_command> m_commands;
    };
}
