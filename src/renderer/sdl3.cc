#include <variant>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "uipp/renderer/sdl3.hh"

using uipp::renderer::sdl3;


auto sdl3::create_surface(window &target) noexcept -> result<surface> /* NOLINT */
{
    auto *sdl_window = static_cast<SDL_Window *>(target.get_native_handle());

    if (auto *r = SDL_CreateRenderer(sdl_window, nullptr); r == nullptr)
        return error { "failed to create renderer: {}", SDL_GetError() }.unexpected();
    else /* NOLINT */
        return surface { std::make_unique<sdl3_surface>(r) };
}


using uipp::renderer::sdl3_surface;


sdl3_surface::~sdl3_surface()
{
    if (m_renderer != nullptr) SDL_DestroyRenderer(static_cast<SDL_Renderer *>(m_renderer));
}


void sdl3_surface::begin_frame(color clear_color) noexcept
{
    auto *r = static_cast<SDL_Renderer *>(m_renderer);
    SDL_SetRenderDrawColor(r, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    SDL_RenderClear(r);
}


void sdl3_surface::submit(const draw_list &list)
{
    auto *r = static_cast<SDL_Renderer *>(m_renderer);

    for (const draw_command &cmd : list.commands())
    {
        std::visit(
            [r, this](auto &&c)
            {
                using T = std::decay_t<decltype(c)>;

                if constexpr (std::is_same_v<T, cmd_rect>)
                {
                    SDL_SetRenderDrawColor(r, c.fill.r, c.fill.g, c.fill.b, c.fill.a);
                    SDL_FRect fr { c.bounds.position.x, c.bounds.position.y, c.bounds.size.x,
                                   c.bounds.size.y };
                    SDL_RenderFillRect(r, &fr);
                }
                else if constexpr (std::is_same_v<T, cmd_texture>)
                {
                    if (auto it = m_textures.find(c.texture); it != m_textures.end())
                    {
                        SDL_FRect dst { c.dst.position.x, c.dst.position.y, c.dst.size.x,
                                        c.dst.size.y };
                        SDL_RenderTexture(r, static_cast<SDL_Texture *>(it->second), nullptr, &dst);
                    }
                }
                else if constexpr (std::is_same_v<T, cmd_push_clip>)
                {
                    SDL_Rect clip {
                        static_cast<int>(c.bounds.position.x),
                        static_cast<int>(c.bounds.position.y),
                        static_cast<int>(c.bounds.size.x),
                        static_cast<int>(c.bounds.size.y),
                    };
                    SDL_SetRenderClipRect(r, &clip);
                }
                else if constexpr (std::is_same_v<T, cmd_pop_clip>)
                {
                    SDL_SetRenderClipRect(r, nullptr);
                }
                else if constexpr (std::is_same_v<T, cmd_text>) { /* font shit, revisit later */ }
            },
            cmd);
    }
}


void sdl3_surface::end_frame() noexcept
{ SDL_RenderPresent(static_cast<SDL_Renderer *>(m_renderer)); }


auto sdl3_surface::resize(math::ivec2 /* new_size */) noexcept -> result<void> { return {}; }


auto sdl3_surface::create_texture(std::span<const std::uint8_t> rgba8, math::ivec2 size)
    -> result<texture_id>
{
    auto        *r = static_cast<SDL_Renderer *>(m_renderer);
    SDL_Texture *tex
        = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, size.w, size.h);
    if (tex == nullptr)
        return error { "failed to create texture: {}", SDL_GetError() }.unexpected();

    SDL_UpdateTexture(tex, nullptr, rgba8.data(), size.w * 4);

    const texture_id id = m_next_texture_id++;
    m_textures[id]      = tex;
    return id;
}


void sdl3_surface::destroy_texture(texture_id id) noexcept
{
    if (auto it = m_textures.find(id); it != m_textures.end())
    {
        SDL_DestroyTexture(static_cast<SDL_Texture *>(it->second));
        m_textures.erase(it);
    }
}
