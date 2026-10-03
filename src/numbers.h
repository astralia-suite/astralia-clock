#pragma once

#include <array>
#include <string_view>

// "ANSI Shadow" glyphs (the style used by nvim dashboards). Every digit sits in an 8-column, 6-row box, flush right.
using Glyph = std::array<std::string_view, 6>;

inline constexpr int glyph_rows = 6;
inline constexpr int digit_cols = 8;
inline constexpr int colon_cols = 5;

inline constexpr std::array<Glyph, 10> digits = {{
    {" █████╗ ",
     "██╔══██╗",
     "██║  ██║",
     "██║  ██║",
     "╚█████╔╝",
     " ╚════╝ "},
    {"     ██╗",
     "    ███║",
     "    ╚██║",
     "     ██║",
     "     ██║",
     "     ╚═╝"},
    {"██████╗ ",
     "╚════██╗",
     " █████╔╝",
     "██╔═══╝ ",
     "███████╗",
     "╚══════╝"},
    {"██████╗ ",
     "╚════██╗",
     " █████╔╝",
     " ╚═══██╗",
     "██████╔╝",
     "╚═════╝ "},
    {"██╗  ██╗",
     "██║  ██║",
     "███████║",
     "╚════██║",
     "     ██║",
     "     ╚═╝"},
    {"███████╗",
     "██╔════╝",
     "███████╗",
     "╚════██║",
     "███████║",
     "╚══════╝"},
    {" █████╗ ",
     "██╔═══╝ ",
     "██████╗ ",
     "██╔══██╗",
     "╚█████╔╝",
     " ╚════╝ "},
    {"███████╗",
     "╚════██║",
     "    ██╔╝",
     "   ██╔╝ ",
     "   ██║  ",
     "   ╚═╝  "},
    {" █████╗ ",
     "██╔══██╗",
     "╚█████╔╝",
     "██╔══██╗",
     "╚█████╔╝",
     " ╚════╝ "},
    {" █████╗ ",
     "██╔══██╗",
     "╚██████║",
     " ╚═══██║",
     " █████╔╝",
     " ╚════╝ "},
}};

// One blank column on each side of the dots.
inline constexpr Glyph colon = {"     ",
                                " ██╗ ",
                                " ╚═╝ ",
                                " ██╗ ",
                                " ╚═╝ ",
                                "     "};
