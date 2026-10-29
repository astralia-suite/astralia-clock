project(
  'astralia-clock',
  'cpp',
  default_options: [
    'prefix=/usr',
    'cpp_std=c++23',
    'warning_level=3',
    'buildtype=minsize',
    'strip=true',
    'cpp_eh=none',
    'cpp_rtti=false',
  ],
)

# Size: drop unused sections and unreferenced libs (`libstdc++`).
add_project_arguments('-ffunction-sections', '-fdata-sections', '-fno-asynchronous-unwind-tables', language: 'cpp')
add_project_link_arguments('-Wl,--gc-sections,--as-needed', language: 'cpp')

inc = include_directories('src')

ncurses_dep = dependency('ncursesw')

executable(
  'astralia-clock',
  'src/main.cpp',
  include_directories: inc,
  dependencies: ncurses_dep,
  install: true,
)

clock_test = executable(
  'test_clock',
  'tests/test_clock.cpp',
  include_directories: inc,
)

test('clock', clock_test)
