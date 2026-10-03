#pragma once

#include <algorithm>
#include <array>
#include <cstring>
#include <ctime>
#include <string_view>

#include "numbers.h"

// `hh:mm:ss` in local time (or UTC), NUL-terminated.
inline std::array<char, 9> format_time(std::time_t t, bool utc = false) {
    std::tm tm{};
    utc ? gmtime_r(&t, &tm) : localtime_r(&t, &tm);
    std::array<char, 9> out{};
    strftime(out.data(), out.size(), "%H:%M:%S", &tm);
    return out;
}

// Fixed buffers: no `std::string`, so no `libstdc++`.
inline constexpr int max_row_bytes = 256;

struct Banner {
    std::array<std::array<char, max_row_bytes>, glyph_rows> rows{};  // NUL-terminated
    std::array<int, glyph_rows> bytes{};
    int cols = 0;
};

// Big-glyph `hh:mm:ss`; skips anything but digits and `:`.
inline Banner render(std::string_view text) {
    Banner b;
    for (char ch : text) {
        const bool is_colon = ch == ':';
        if (!is_colon && (ch < '0' || ch > '9')) continue;
        const Glyph& g = is_colon ? colon : digits[ch - '0'];
        if (b.bytes[0] + static_cast<int>(g[0].size()) >= max_row_bytes) break;
        for (int r = 0; r < glyph_rows; ++r) {
            std::memcpy(b.rows[r].data() + b.bytes[r], g[r].data(), g[r].size());
            b.bytes[r] += static_cast<int>(g[r].size());
        }
        b.cols += is_colon ? colon_cols : digit_cols;
    }
    return b;
}

struct Pos {
    int row;
    int col;
};

// 1-based position centering a `w`x`h` block; clamps to the top-left.
inline Pos center(int rows, int cols, int w, int h) {
    return {std::max(1, (rows - h) / 2 + 1), std::max(1, (cols - w) / 2 + 1)};
}
