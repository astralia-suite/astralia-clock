project('astralia-clock', 'cpp', default_options: [
    'cpp_std=c++23', 'warning_level=3',
    'buildtype=minsize', 'strip=true', 'cpp_eh=none', 'cpp_rtti=false',
])

# Size: drop unused sections and unreferenced libs (`libstdc++`).
add_project_arguments('-ffunction-sections', '-fdata-sections', '-fno-asynchronous-unwind-tables', language: 'cpp')
add_project_link_arguments('-Wl,--gc-sections,--as-needed', language: 'cpp')

inc = include_directories('src')

ncurses = dependency('ncursesw')

executable('astralia-clock', 'src/main.cpp', include_directories: inc, dependencies: ncurses, install: true)

test('clock', executable('test_clock', 'tests/test_clock.cpp', include_directories: inc))
