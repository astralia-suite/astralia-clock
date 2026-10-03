project('astralia-clock', 'cpp', default_options: [
    'cpp_std=c++23', 'warning_level=3',
    'buildtype=minsize', 'strip=true', 'cpp_eh=none', 'cpp_rtti=false',
])

# Footprint: drop unused code/data and any shared library nothing references (`libstdc++`).
add_project_arguments('-ffunction-sections', '-fdata-sections', '-fno-asynchronous-unwind-tables', language: 'cpp')
add_project_link_arguments('-Wl,--gc-sections,--as-needed', language: 'cpp')

inc = include_directories('src')

ncurses = dependency('ncursesw')

# `palette.h` is shared with astralia-shell-hl so the accent color has a single source.
palette_inc = include_directories('../astralia-shell-hl/src/render')

executable('astralia-clock', 'src/main.cpp', include_directories: [inc, palette_inc], dependencies: ncurses, install: true)

test('clock', executable('test_clock', 'tests/test_clock.cpp', include_directories: inc))
