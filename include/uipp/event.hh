#pragma once
#include <cstdint>
#include <variant>

#include "uipp/export.hh"
#include "uipp/math/vector.hh"


namespace uipp
{
    using window_id = std::uint32_t;

    enum class [[uipp_public]] mouse_button : std::uint8_t
    {
        left,
        right,
        middle,
        side_rear,
        side_front,
        other,
    };

    enum class [[uipp_public]] scancode : std::uint16_t
    {
        unknown              = 0,
        a                    = 4,
        b                    = 5,
        c                    = 6,
        d                    = 7,
        e                    = 8,
        f                    = 9,
        g                    = 10,
        h                    = 11,
        i                    = 12,
        j                    = 13,
        k                    = 14,
        l                    = 15,
        m                    = 16,
        n                    = 17,
        o                    = 18,
        p                    = 19,
        q                    = 20,
        r                    = 21,
        s                    = 22,
        t                    = 23,
        u                    = 24,
        v                    = 25,
        w                    = 26,
        x                    = 27,
        y                    = 28,
        z                    = 29,
        num_1                = 30,
        num_2                = 31,
        num_3                = 32,
        num_4                = 33,
        num_5                = 34,
        num_6                = 35,
        num_7                = 36,
        num_8                = 37,
        num_9                = 38,
        num_0                = 39,
        kb_return            = 40,
        escape               = 41,
        backspace            = 42,
        tab                  = 43,
        space                = 44,
        minus                = 45,
        equals               = 46,
        left_bracket         = 47,
        right_bracket        = 48,
        backslash            = 49,
        non_us_hash          = 50,
        semicolon            = 51,
        apostrophe           = 52,
        grave                = 53,
        comma                = 54,
        period               = 55,
        slash                = 56,
        caps_lock            = 57,
        f1                   = 58,
        f2                   = 59,
        f3                   = 60,
        f4                   = 61,
        f5                   = 62,
        f6                   = 63,
        f7                   = 64,
        f8                   = 65,
        f9                   = 66,
        f10                  = 67,
        f11                  = 68,
        f12                  = 69,
        print_screen         = 70,
        scroll_lock          = 71,
        pause                = 72,
        insert               = 73,
        home                 = 74,
        page_up              = 75,
        kb_delete            = 76,
        end                  = 77,
        page_down            = 78,
        right                = 79,
        left                 = 80,
        down                 = 81,
        up                   = 82,
        num_lock_clear       = 83,
        kp_divide            = 84,
        kp_multiply          = 85,
        kp_minus             = 86,
        kp_plus              = 87,
        kp_enter             = 88,
        kp_1                 = 89,
        kp_2                 = 90,
        kp_3                 = 91,
        kp_4                 = 92,
        kp_5                 = 93,
        kp_6                 = 94,
        kp_7                 = 95,
        kp_8                 = 96,
        kp_9                 = 97,
        kp_0                 = 98,
        kp_period            = 99,
        non_us_backslash     = 100,
        application          = 101,
        power                = 102,
        kp_equals            = 103,
        f13                  = 104,
        f14                  = 105,
        f15                  = 106,
        f16                  = 107,
        f17                  = 108,
        f18                  = 109,
        f19                  = 110,
        f20                  = 111,
        f21                  = 112,
        f22                  = 113,
        f23                  = 114,
        f24                  = 115,
        execute              = 116,
        help                 = 117,
        menu                 = 118,
        select               = 119,
        stop                 = 120,
        again                = 121,
        undo                 = 122,
        cut                  = 123,
        copy                 = 124,
        paste                = 125,
        find                 = 126,
        mute                 = 127,
        volume_up            = 128,
        volume_down          = 129,
        kp_comma             = 133,
        kp_equals_as400      = 134,
        international_1      = 135,
        international_2      = 136,
        international_3      = 137,
        international_4      = 138,
        international_5      = 139,
        international_6      = 140,
        international_7      = 141,
        international_8      = 142,
        international_9      = 143,
        lang_1               = 144,
        lang_2               = 145,
        lang_3               = 146,
        lang_4               = 147,
        lang_5               = 148,
        lang_6               = 149,
        lang_7               = 150,
        lang_8               = 151,
        lang_9               = 152,
        alter_ase            = 153,
        sys_req              = 154,
        cancel               = 155,
        clear                = 156,
        prior                = 157,
        return_2             = 158,
        separator            = 159,
        out                  = 160,
        oper                 = 161,
        clear_again          = 162,
        cr_sel               = 163,
        ex_sel               = 164,
        kp_00                = 176,
        kp_000               = 177,
        thousands_separator  = 178,
        decimal_separator    = 179,
        currency_unit        = 180,
        currency_subunit     = 181,
        kp_left_paren        = 182,
        kp_right_paren       = 183,
        kp_left_brace        = 184,
        kp_right_brace       = 185,
        kp_tab               = 186,
        kp_backspace         = 187,
        kp_a                 = 188,
        kp_b                 = 189,
        kp_c                 = 190,
        kp_d                 = 191,
        kp_e                 = 192,
        kp_f                 = 193,
        kp_xor               = 194,
        kp_power             = 195,
        kp_percent           = 196,
        kp_less              = 197,
        kp_greater           = 198,
        kp_ampersand         = 199,
        kp_dbl_ampersand     = 200,
        kp_vertical_bar      = 201,
        kp_dbl_vertical_bar  = 202,
        kp_colon             = 203,
        kp_hash              = 204,
        kp_space             = 205,
        kp_at                = 206,
        kp_exclam            = 207,
        kp_memstore          = 208,
        kp_memrecall         = 209,
        kp_memclear          = 210,
        kp_memadd            = 211,
        kp_memsubtract       = 212,
        kp_memmultiply       = 213,
        kp_memdivide         = 214,
        kp_plus_minus        = 215,
        kp_clear             = 216,
        kp_clear_entry       = 217,
        kp_binary            = 218,
        kp_octal             = 219,
        kp_decimal           = 220,
        kp_hexadecimal       = 221,
        l_ctrl               = 224,
        l_shift              = 225,
        l_alt                = 226,
        l_gui                = 227,
        r_ctrl               = 228,
        r_shift              = 229,
        r_alt                = 230,
        r_gui                = 231,
        mode                 = 257,
        sleep                = 258,
        wake                 = 259,
        channel_increment    = 260,
        channel_decrement    = 261,
        media_play           = 262,
        media_pause          = 263,
        media_record         = 264,
        media_fast_forward   = 265,
        media_rewind         = 266,
        media_next_track     = 267,
        media_previous_track = 268,
        media_stop           = 269,
        media_eject          = 270,
        media_play_pause     = 271,
        media_select         = 272,
        ac_new               = 273,
        ac_open              = 274,
        ac_close             = 275,
        ac_exit              = 276,
        ac_save              = 277,
        ac_print             = 278,
        ac_properties        = 279,
        ac_search            = 280,
        ac_home              = 281,
        ac_back              = 282,
        ac_forward           = 283,
        ac_stop              = 284,
        ac_refresh           = 285,
        ac_bookmarks         = 286,
        soft_left            = 287,
        soft_right           = 288,
        call                 = 289,
        end_call             = 290,
        reserved             = 400,
        count                = 512,
    };


    enum class [[uipp_public]] modifiers : std::uint8_t
    {
        none  = 0,
        shift = 1 << 0,
        ctrl  = 1 << 1,
        alt   = 1 << 2,
        super = 1 << 3,
    };

    [[nodiscard, uipp_public]]
    constexpr auto operator|(modifiers a, modifiers b) noexcept -> modifiers
    { return static_cast<modifiers>(static_cast<std::uint8_t>(a) | static_cast<std::uint8_t>(b)); }

    [[nodiscard, uipp_public]]
    constexpr auto operator&(modifiers a, modifiers b) noexcept -> bool
    { return (static_cast<std::uint8_t>(a) & static_cast<std::uint8_t>(b)) != 0; }


    struct [[uipp_public]] mouse_move_event
    {
        window_id  window;
        math::vec2 position;
    };

    struct [[uipp_public]] mouse_button_event
    {
        window_id    window;
        math::vec2   position;
        mouse_button button;
        bool         down;
    };

    struct [[uipp_public]] mouse_scroll_event
    {
        window_id  window;
        math::vec2 delta;
    };

    struct [[uipp_public]] key_event
    {
        window_id window;
        scancode  code;
        modifiers mod;
        bool      down;
        bool      repeat;
    };

    struct [[uipp_public]] text_input_event
    {
        window_id        window;
        std::string_view text;
    };

    struct [[uipp_public]] resize_event
    {
        window_id   window;
        math::ivec2 size;
    };

    struct [[uipp_public]] close_event
    {
        window_id window;
    };

    struct [[uipp_public]] quit_event
    {
    };

    using event = std::variant<mouse_move_event,
                               mouse_button_event,
                               mouse_scroll_event,
                               key_event,
                               text_input_event,
                               resize_event,
                               close_event,
                               quit_event>;
}
