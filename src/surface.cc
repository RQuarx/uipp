#include "uipp/surface.hh"

using uipp::surface;


surface::surface(std::unique_ptr<backend> &&backend) noexcept : m_backend { std::move(backend) } {}

void surface::begin_frame(color clear_color) noexcept { m_backend->begin_frame(clear_color); }
void surface::submit(const draw_list &list) { m_backend->submit(list); }
void surface::end_frame() noexcept { m_backend->end_frame(); }

auto surface::resize(math::ivec2 new_size) noexcept -> result<void>
{ return m_backend->resize(new_size); }

auto surface::create_texture(std::span<const std::uint8_t> rgba8, math::ivec2 size)
    -> result<texture_id>
{ return m_backend->create_texture(rgba8, size); }

void surface::destroy_texture(texture_id id) noexcept { m_backend->destroy_texture(id); }
