#pragma once
#include <memory>

#include "uipp/math/vector.hh"


namespace uipp
{
    class window
    {
    public:
        struct backend
        {
            virtual ~backend() = default;


            [[nodiscard]] virtual auto get_native_handle() noexcept -> void *;
            [[nodiscard]] virtual auto get_size() const -> math::ivec2       = 0;
            [[nodiscard]] virtual auto get_title() const -> std::string_view = 0;

            virtual auto set_size(math::ivec2 new_size) noexcept -> result<void>   = 0;
            virtual auto set_title(const char *new_title) noexcept -> result<void> = 0;
        };


        explicit window(std::unique_ptr<backend> &&backend) noexcept;

        [[nodiscard]] auto get_native_handle() noexcept -> void *;
        [[nodiscard]] auto get_size() const -> math::ivec2;
        [[nodiscard]] auto get_title() const -> std::string_view;

        auto set_size(math::ivec2 new_size) noexcept -> result<void>;
        auto set_title(const char *new_title) noexcept -> result<void>;

    private:
        std::unique_ptr<backend> m_backend;
    };
}
