#include "uipp/draw_list.hh"

using uipp::draw_list;


void draw_list::clear() noexcept { m_commands.clear(); }

void draw_list::rect(math::rect bounds, color fill, float corner_radius)
{ m_commands.emplace_back(cmd_rect { bounds, fill, corner_radius }); }

void draw_list::text(math::vec2 pos, font_id font, float size, color fill, std::string_view s)
{ m_commands.emplace_back(cmd_text { pos, font, size, fill, std::string { s } }); }

void draw_list::texture(math::rect dst, math::rect src_uv, texture_id tex, color tint)
{ m_commands.emplace_back(cmd_texture { dst, src_uv, tex, tint }); }

void draw_list::push_clip(math::rect bounds) { m_commands.emplace_back(cmd_push_clip { bounds }); }

void draw_list::pop_clip() { m_commands.emplace_back(cmd_pop_clip {}); }

auto draw_list::commands() const noexcept -> const std::vector<draw_command> &
{ return m_commands; }
