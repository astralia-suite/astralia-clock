#include <curses.h>
#include <time.h>

#include <clocale>

#include "clock.h"

namespace {

constexpr struct {
    int r, g, b;
} accent{0x9B, 0x57, 0xF4};

// Inits curses; restores the terminal on scope exit.
struct Curses {
    Curses() {
        setlocale(LC_ALL, "");  // UTF-8 glyphs
        initscr();
        raw();  // Ctrl-C arrives as key 3, so exit runs the destructor
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);  // enables KEY_RESIZE
        init_accent();
    }
    ~Curses() { endwin(); }

    // Pair 1 = `accent`: exact if colors are redefinable, else nearest 256-color.
    static void init_accent() {
        if (!has_colors()) return;
        start_color();             // sets `COLORS`
        if (COLORS < 256) return;  // keep default color
        use_default_colors();
        constexpr short id = 16;
        constexpr auto c = accent;
        auto scaled = [](int v, int max) { return static_cast<short>((v * max + 127) / 255); };  // 0..255 -> 0..max
        short fg = id;
        if (can_change_color())
            init_color(id, scaled(c.r, 1000), scaled(c.g, 1000), scaled(c.b, 1000));
        else
            fg = static_cast<short>(16 + 36 * scaled(c.r, 5) + 6 * scaled(c.g, 5) + scaled(c.b, 5));
        init_pair(1, fg, -1);
        accent_ready = true;
    }

    static inline bool accent_ready = false;
};

void draw(time_t t) {
    const Banner b = render(format_time(t).data());
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
        // One clock read: `time()` is tick-coarse and lags the second boundary.
        timespec now;
        clock_gettime(CLOCK_REALTIME, &now);
        draw(now.tv_sec);
        timeout(static_cast<int>(1000 - now.tv_nsec / 1000000));  // wake at next second
        const int ch = getch();                                   // ERR on timeout
        if (ch == 'q' || ch == 3) break;                          // 3 = Ctrl-C
    }
}
