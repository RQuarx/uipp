#pragma once
#include <memory>

#include "uipp/math/vector.hh"
#include "uipp/export.hh"


namespace uipp
{
    using window_id = std::uint32_t;


    class [[uipp_public]] window
    {
    public:
        struct [[uipp_public]] backend
        {
            virtual ~backend() = default;


            [[nodiscard]] virtual auto get_native_handle() noexcept -> void * = 0;

            [[nodiscard]] virtual auto get_id() const -> window_id           = 0;
            [[nodiscard]] virtual auto get_size() const -> math::ivec2       = 0;
            [[nodiscard]] virtual auto get_title() const -> std::string_view = 0;

            virtual auto set_size(math::ivec2 new_size) noexcept -> result<void>   = 0;
            virtual auto set_title(const char *new_title) noexcept -> result<void> = 0;
        };


        explicit window(std::unique_ptr<backend> &&backend) noexcept;

        [[nodiscard]] auto get_native_handle() noexcept -> void *;
        [[nodiscard]] auto get_window_id() const -> std::uint32_t;
        [[nodiscard]] auto get_size() const -> math::ivec2;
        [[nodiscard]] auto get_title() const -> std::string_view;

        auto set_size(math::ivec2 new_size) noexcept -> result<void>;
        auto set_title(const char *new_title) noexcept -> result<void>;

    private:
        std::unique_ptr<backend> m_backend;
    };
}
