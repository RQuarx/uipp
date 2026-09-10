#pragma once
#include <expected>
#include <format>
#include <source_location>
#include <stdexcept>


namespace uipp
{
    namespace _impl
    {
        template <typename... Args>
        struct format_string_source
        {
            std::source_location        source;
            std::format_string<Args...> format;


            template <typename T>
            constexpr format_string_source(const T                   &format,
                                           const std::source_location source
                                           = std::source_location::current()) noexcept
                requires std::constructible_from<std::format_string<Args...>, T>
                : source { source }, format { format }
            {
            }
        };
    }


    class error final : public std::runtime_error
    {
    public:
        template <typename... Args>
        error(std::type_identity_t<_impl::format_string_source<Args...>> fmt, Args &&...args)
            : std::runtime_error { std::format(fmt.format, std::forward<Args>(args)...) },
              m_source { fmt.source }
        {
        }


        [[nodiscard]]
        constexpr auto what() const noexcept -> const char * override
        { return std::runtime_error::what(); }

        [[nodiscard]]
        constexpr auto where() const noexcept -> std::source_location
        { return m_source; }

    private:
        std::source_location m_source;
    };


    template <typename T>
    using result = std::expected<T, error>;
}
