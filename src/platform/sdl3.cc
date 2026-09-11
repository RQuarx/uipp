#include <SDL3/SDL.h>

#include "uipp/platform/sdl3.hh"

using uipp::platform::sdl3;

namespace
{
    [[nodiscard]]
    constexpr auto translate_modifiers(SDL_Keymod mod) noexcept -> uipp::modifiers
    {
        using uipp::modifiers;

        auto mods = modifiers::none;
        if ((mod & SDL_KMOD_SHIFT) != 0U) mods = mods | modifiers::shift;
        if ((mod & SDL_KMOD_CTRL) != 0U) mods = mods | modifiers::ctrl;
        if ((mod & SDL_KMOD_ALT) != 0U) mods = mods | modifiers::alt;
        if ((mod & SDL_KMOD_GUI) != 0U) mods = mods | modifiers::super;
        return mods;
    }
}


sdl3::sdl3()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        throw error { "failed to initialize SDL3: {}", SDL_GetError() }.unexpected();
}


sdl3::~sdl3() { SDL_Quit(); }


auto sdl3::create_window(const char *title, math::ivec2 size) noexcept /* NOLINT */
    -> result<window>
{
    if (auto *w = SDL_CreateWindow(title, size.w, size.h,
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
        w == nullptr)
        return error { "failed to create window: {}", SDL_GetError() }.unexpected();
    else /* NOLINT */
        return window { std::make_unique<sdl3_window>(w) };
}


auto sdl3::mf_poll_events(void *ctx, auto (*invoke)(void *, const event &)->result<bool>) noexcept
    -> result<bool>
{
    SDL_Event ev;

    while (SDL_PollEvent(&ev))
    {
        uipp::event event;

        switch (ev.type)
        {
        case SDL_EVENT_QUIT: event = quit_event {}; break;

        case SDL_EVENT_MOUSE_MOTION:
            event = mouse_move_event {
                .window = ev.motion.windowID, .position = { ev.motion.x, ev.motion.y }
            };
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                mouse_button_event mbe {
                    .window   = ev.button.windowID,
                    .position = { ev.button.x, ev.button.y },
                    .down     = ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN,
                }; /* NOLINT */

                switch (ev.button.button)
                {
                case 1:  mbe.button = mouse_button::left; break;
                case 2:  mbe.button = mouse_button::middle; break;
                case 3:  mbe.button = mouse_button::right; break;
                case 4:  mbe.button = mouse_button::side_rear; break;
                case 5:  mbe.button = mouse_button::side_front; break;
                default: mbe.button = mouse_button::other; break;
                }

                event = mbe;
                break;
            }

        case SDL_EVENT_MOUSE_WHEEL:
            event = mouse_scroll_event {
                .window = ev.wheel.windowID, .delta = { ev.wheel.x, ev.wheel.y }
            };
            break;

        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            event = key_event {
                ev.key.windowID,
                scancode(ev.key.scancode),
                translate_modifiers(ev.key.mod),
                ev.type == SDL_EVENT_KEY_DOWN,
                int(ev.key.repeat) != 0,
            };
            break;

        case SDL_EVENT_TEXT_INPUT:
            event = text_input_event { ev.text.windowID, ev.text.text };
            break;

        case SDL_EVENT_WINDOW_RESIZED:
            event = resize_event {
                ev.window.windowID, { ev.window.data1, ev.window.data2 }
            };
            break;

        case SDL_EVENT_WINDOW_CLOSE_REQUESTED: event = close_event { ev.window.windowID }; break;
        default:                               break;
        };

        if (auto res = invoke(ctx, event); res.has_value() and !*res)
            return false;
        else /* NOLINT */
        {
            if (std::holds_alternative<quit_event>(event)) return false;
            return *res;
        }
    }

    return true;
}


using uipp::platform::sdl3_window;


sdl3_window::~sdl3_window()
{
    if (m_window != nullptr) SDL_DestroyWindow(static_cast<SDL_Window *>(m_window));
}


auto sdl3_window::get_native_handle() noexcept -> void * { return m_window; }
auto sdl3_window::get_id() const -> window_id
{ return SDL_GetWindowID(static_cast<SDL_Window *>(m_window)); }

auto sdl3_window::get_size() const -> math::ivec2
{
    math::ivec2 size;
    SDL_GetWindowSize(static_cast<SDL_Window *>(m_window), &size.w, &size.h);
    return size;
}


auto sdl3_window::get_title() const -> std::string_view
{ return SDL_GetWindowTitle(static_cast<SDL_Window *>(m_window)); }

auto sdl3_window::set_size(math::ivec2 new_size) noexcept -> result<void>
{
    if (!SDL_SetWindowSize(static_cast<SDL_Window *>(m_window), new_size.w, new_size.h))
        return error { "failed to set window size: {}", SDL_GetError() }.unexpected();
    return {};
}


auto sdl3_window::set_title(const char *new_title) noexcept -> result<void>
{
    if (!SDL_SetWindowTitle(static_cast<SDL_Window *>(m_window), new_title))
        return error { "failed to set window title: {}", SDL_GetError() }.unexpected();
    return {};
}
