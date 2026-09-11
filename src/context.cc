#include "uipp/context.hh"

using uipp::context;


namespace
{
    constexpr auto fnv1a(std::string_view s, std::uint64_t seed = 1469598103934665603ULL) noexcept
        -> std::size_t
    {
        std::size_t hash = seed;

        for (unsigned char c : s)
        {
            hash ^= c;
            hash *= 1099511628211ULL;
        }

        return hash;
    }
}


auto context::begin_frame(math::ivec2 viewport_size) noexcept -> void
{
    m_draw_list.clear();
    m_layout_stack.clear();

    m_prev_mouse_down = m_mouse_down;
    m_viewport_size   = viewport_size;
}


auto context::end_frame() noexcept -> void
{
    /* placeholder: destroy widget_states not touched this frame,
                    once make_id/state_for track "last seen frame" per id */
}


auto context::handle_event(const event &ev) noexcept -> void
{
    std::visit(
        [this](auto &&e)
        {
            using T = std::decay_t<decltype(e)>;

            if constexpr (std::is_same_v<T, mouse_move_event>)
                m_mouse_pos = e.position;
            else if constexpr (std::is_same_v<T, mouse_button_event>)
                if (e.button == mouse_button::left) m_mouse_down = e.down;
        },
        ev);
}


auto context::push_column(math::vec2 origin) noexcept -> void
{ m_layout_stack.push_back(layout_frame { origin, origin, false }); }


auto context::push_row(math::vec2 origin) noexcept -> void
{ m_layout_stack.push_back(layout_frame { origin, origin, true }); }


auto context::pop_layout() noexcept -> void
{
    if (!m_layout_stack.empty()) m_layout_stack.pop_back();
}


auto context::next_widget_rect(math::vec2 size) noexcept -> math::rect
{
    if (m_layout_stack.empty())
        return math::rect {
            { 0, 0 },
            size
        };

    auto      &frame = m_layout_stack.back();
    math::rect r { frame.cursor, size };

    if (frame.horizontal)
        frame.cursor.x += size.x + m_style.spacing;
    else
        frame.cursor.y += size.y + m_style.spacing;

    return r;
}


auto context::make_id(std::string_view label) const noexcept -> widget_id
{
    return widget_id(fnv1a(label));
}


auto context::state_for(widget_id id) noexcept -> widget_state &
{ return m_widget_states[id]; }


auto context::draw_list() noexcept -> uipp::draw_list & { return m_draw_list; }
auto context::style() const noexcept -> const style_sheet & { return m_style; }
auto context::style() noexcept -> style_sheet & { return m_style; }
auto context::mouse_pos() const noexcept -> math::vec2 { return m_mouse_pos; }
auto context::mouse_down() const noexcept -> bool { return m_mouse_down; }
auto context::mouse_pressed() const noexcept -> bool { return m_mouse_down && !m_prev_mouse_down; }
auto context::mouse_released() const noexcept -> bool { return !m_mouse_down && m_prev_mouse_down; }
