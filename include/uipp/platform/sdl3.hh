#pragma once
#include "uipp/traits/platform.hh"


namespace uipp::platform
{
    class [[uipp_public]] sdl3
    {
    public:
        sdl3();
        ~sdl3();


        [[nodiscard]]
        auto create_window(const char *title, math::ivec2 size) noexcept -> result<window>;

        template <typename F>
        [[nodiscard]]
        auto poll_events(F &&callback) noexcept -> result<bool>
        {
            return mf_poll_events(
                &callback, [](void *ctx, const event &ev) noexcept -> result<bool>
                { return (*static_cast<std::remove_reference_t<F> *>(ctx))(ev); });
        }

    private:
        [[nodiscard]]
        auto mf_poll_events(void *ctx, auto (*invoke)(void *, const event &)->result<bool>) noexcept
            -> result<bool>;
    };


    class [[uipp_public]] sdl3_window final : public window::backend
    {
    public:
        constexpr sdl3_window(void *window) noexcept : m_window { window } {}
        ~sdl3_window() override;


        [[nodiscard]] auto get_native_handle() noexcept -> void * override;
        [[nodiscard]] auto get_id() const -> window_id override;
        [[nodiscard]] auto get_size() const -> math::ivec2 override;
        [[nodiscard]] auto get_title() const -> std::string_view override;

        auto set_size(math::ivec2 new_size) noexcept -> result<void> override;
        auto set_title(const char *new_title) noexcept -> result<void> override;

    private:
        void *m_window = nullptr;
    };


    static_assert(
        traits::platform<sdl3,
                         decltype([](const event &) noexcept -> result<bool> { return true; })>);
}
