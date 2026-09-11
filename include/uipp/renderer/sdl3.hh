#pragma once
#include <unordered_map>

#include "uipp/result.hh"
#include "uipp/surface.hh"
#include "uipp/traits/renderer.hh"
#include "uipp/window.hh"


namespace uipp::renderer
{
    /* an SDL3 renderer must be paired with an SDL3 platform */
    class [[uipp_public]] sdl3
    {
    public:
        [[nodiscard]] auto create_surface(window &target) noexcept -> result<surface>;

    private:
    };


    /* a renderer, not SDL_Surface */
    class [[uipp_public]] sdl3_surface final : public surface::backend
    {
    public:
        constexpr sdl3_surface(void *renderer) noexcept : m_renderer { renderer } {}
        ~sdl3_surface() override;

        void begin_frame(color clear_color) noexcept override;
        void submit(const draw_list &list) override;
        void end_frame() noexcept override;

        auto resize(math::ivec2 new_size) noexcept -> result<void> override;

        [[nodiscard]]
        auto create_texture(std::span<const std::uint8_t> rgba8, math::ivec2 size)
            -> result<texture_id> override;

        void destroy_texture(texture_id id) noexcept override;

    private:
        void *m_renderer;

        /* id -> SDL_Textures */
        std::unordered_map<texture_id, void *> m_textures;
        texture_id                             m_next_texture_id = 1;
    };


    static_assert(traits::renderer<sdl3>);
}
