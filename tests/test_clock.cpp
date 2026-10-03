#include <cassert>
#include <string_view>

#include "clock.h"

int main() {
    const std::time_t t = 1791000306;  // 2026-10-03 04:05:06 UTC
    assert(std::string_view(format_time(t, true).data()) == "04:05:06");

    const Banner b = render("12:34:56");
    assert(b.cols == 58);
    for (int r = 0; r < glyph_rows; ++r) assert(b.bytes[r] > 0 && b.rows[r][b.bytes[r]] == '\0');
    const std::string_view row2(b.rows[2].data(), b.bytes[2]);
    assert(row2.starts_with(digits[1][2]));
    assert(row2.ends_with(digits[6][2]));

    auto p = center(24, 80, 60, 6);
    assert(p.row == 10 && p.col == 11);
    p = center(25, 81, 60, 6);  // odd sizes round down
    assert(p.row == 10 && p.col == 11);
    p = center(3, 40, 60, 6);  // smaller than the banner: clamp to the corner
    assert(p.row == 1 && p.col == 1);
}
