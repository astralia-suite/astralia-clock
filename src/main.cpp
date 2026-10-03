#include <curses.h>
#include <time.h>

#include <clocale>

#include "clock.h"
#include "palette.h"  // from astralia-shell-hl

namespace {

// Starts curses on construction and restores the terminal on scope exit.
struct Curses {
    Curses() {
        setlocale(LC_ALL, "");  // needed for the box-drawing glyphs to render as UTF-8
        initscr();
        raw();  // Ctrl-C arrives as a key (3) so we always exit through the destructor
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);  // delivers KEY_RESIZE on terminal resize
        init_accent();
    }
    ~Curses() { endwin(); }

    // Color pair 1 = `palette::accent`: exact if the terminal can redefine colors, else nearest of the 256-color cube.
    static void init_accent() {
        if (!has_colors()) return;
        start_color();             // sets `COLORS`
        if (COLORS < 256) return;  // 8/16-color terminals keep the default color
        use_default_colors();
        constexpr short id = 16;
        constexpr Color c = palette::accent;
        auto scaled = [](float v, float max) { return static_cast<int>(v * max + 0.5f); };
        short fg = id;
        if (can_change_color())
            init_color(id, static_cast<short>(scaled(c.r, 1000)), static_cast<short>(scaled(c.g, 1000)),
                       static_cast<short>(scaled(c.b, 1000)));
        else
            fg = static_cast<short>(16 + 36 * scaled(c.r, 5) + 6 * scaled(c.g, 5) + scaled(c.b, 5));
        init_pair(1, fg, -1);
        accent_ready = true;
    }

    static inline bool accent_ready = false;
};

void draw() {
    const Banner b = render(format_time(time(nullptr)).data());
    const Pos p = center(getmaxy(stdscr), getmaxx(stdscr), b.cols, glyph_rows);
    erase();
    if (Curses::accent_ready) attron(COLOR_PAIR(1));
    for (int r = 0; r < glyph_rows; ++r) mvaddnstr(p.row - 1 + r, p.col - 1, b.rows[r].data(), b.bytes[r]);
    refresh();
}

}  // namespace

int main() {
    Curses curses;
    for (;;) {
        draw();
        timespec now;
        clock_gettime(CLOCK_REALTIME, &now);
        timeout(static_cast<int>(1000 - now.tv_nsec / 1000000));  // wake at the next second boundary
        const int ch = getch();                                   // ERR on timeout, KEY_RESIZE on resize
        if (ch == 'q' || ch == 3) break;                          // 3 = Ctrl-C
    }
}
