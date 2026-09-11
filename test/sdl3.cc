#include <uipp/platform/sdl3.hh>

#include <print>

#include <uipp/context.hh>
#include <uipp/renderer/sdl3.hh>


auto main() -> int
{
    auto platform = uipp::platform::sdl3 {};
    auto renderer = uipp::renderer::sdl3 {};
    auto context  = uipp::context {};

    std::optional<uipp::window> window;

    if (auto res = platform.create_window("test-sdl3", { 800, 300 }); res.has_value())
        window = std::move(*res);
    else
        std::println("{}", res.error().what());

    auto surface      = renderer.create_surface(*window);
    bool should_close = false;

    while (!should_close)
    {
        if (!platform.poll_events(
                [&](const uipp::event &ev) -> uipp::result<bool>
                {
                    context.handle_event(ev);

                    std::visit(
                        [&](const auto &event)
                        {
                            using T = std::remove_cvref_t<decltype(event)>;
                            using namespace uipp;

                            if constexpr (std::is_same_v<T, close_event>)
                            {
                                should_close = true;
                                std::println("close event");
                            }
                            else if constexpr (std::is_same_v<T, resize_event>)
                            {
                                auto _ = surface->resize(event.size);
                                std::println("resize event");
                            }
                            else if constexpr (std::is_same_v<T, key_event>)
                                std::println("key event");
                            else if constexpr (std::is_same_v<T, mouse_move_event>)
                                std::println("mouse move event");
                            else if constexpr (std::is_same_v<T, mouse_button_event>)
                                std::println("mouse button event");
                            else if constexpr (std::is_same_v<T, mouse_scroll_event>)
                                std::println("mouse scroll event");
                        },
                        ev);

                    return true;
                }))
            should_close = true;

        context.begin_frame({ 0, 0 });
        context.end_frame();

        surface->begin_frame({ 20, 20, 24, 255 });
        surface->submit(context.draw_list());
        surface->end_frame();
    }
}
