#include "uipp/window.hh"

using uipp::window;


window::window(std::unique_ptr<backend> &&backend) noexcept : m_backend { std::move(backend) } {}

auto window::get_native_handle() noexcept -> void * { return m_backend->get_native_handle(); }
auto window::get_window_id() const -> std::uint32_t { return m_backend->get_id(); }
auto window::get_size() const -> math::ivec2 { return m_backend->get_size(); }
auto window::get_title() const -> std::string_view { return m_backend->get_title(); }

auto window::set_size(math::ivec2 new_size) noexcept -> result<void>
{ return m_backend->set_size(new_size); }

auto window::set_title(const char *new_title) noexcept -> result<void>
{ return m_backend->set_title(new_title); }

