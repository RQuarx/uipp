#pragma once
#include <cstdint>
#include <memory>

#include "uipp/color.hh"
#include "uipp/draw_list.hh"


namespace uipp
{
    using texture_id = std::uint32_t;


    class surface
    {
    public:
        struct backend
        {
            virtual ~backend() = default;

            virtual void begin_frame(color clear_color) noexcept = 0;
            virtual void submit(const draw_list &list)           = 0;
            virtual void end_frame() noexcept                    = 0;

            virtual auto resize(math::ivec2 new_size) noexcept -> result<void> = 0;

            [[nodiscard]] virtual auto create_texture(std::span<const std::uint8_t> rgba8,
                                                      math::ivec2 size) -> result<texture_id> = 0;
            virtual void               destroy_texture(texture_id id) noexcept                = 0;
        };


        explicit surface(std::unique_ptr<backend> &&backend) noexcept;

        void begin_frame(color clear_color) noexcept;
        void submit(const draw_list &list);
        void end_frame() noexcept;

        auto resize(math::ivec2 new_size) noexcept -> result<void>;

        [[nodiscard]] auto create_texture(std::span<const std::uint8_t> rgba8, math::ivec2 size)
            -> result<texture_id>;
        void destroy_texture(texture_id id) noexcept;

    private:
        std::unique_ptr<backend> m_backend;
    };
}
