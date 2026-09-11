#include <print>

#include <uipp.hh>
#include <uipp/platform/sdl3.hh>
#include <uipp/renderer/sdl3.hh>


auto
main() -> int
{
    auto app = uipp::application::create<uipp::platform::sdl3, uipp::renderer::sdl3>();

    if (app.has_value())
        return app.run(
            [](uipp::context &ctx) -> uipp::result<void>
            { uipp::widget::button(ctx, "click me!", [] { std::println("clicked"); }); });
    else /* NOLINT */
        std::println("error: {}", app.error());
}
