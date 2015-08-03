cmake_minimum_required(VERSION 3.0.0)
project(CC3K)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(Curses)

add_executable(cc3k
  src/add_to_floor.cc
  src/cc3k.cc
  src/Character.cc
  src/Enemy.cc
  src/fix_dragons.cc
  src/Floor.cc
  src/FloorFiller.cc
  src/Game.cc
  src/GameObject.cc
  src/Gold.cc
  src/main.cc
  src/make_view.cc
  src/Player.cc
  src/PlayerInputController.cc
  src/PlayerStats.cc
  src/Potion.cc
  src/random.cc
  src/SceneGraph.cc
  src/Stairs.cc
  src/TextView.cc
  src/View.cc
  )

target_sources(cc3k PUBLIC
  $<$<BOOL:CURSES_FOUND>:src/CursesView.cc>
  )
target_include_directories(cc3k PUBLIC
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIRS}
  ${CURSES_INCLUDE_DIRS}
  )
target_link_libraries(cc3k
  ${Boost_LIBRARIES}
  ${CURSES_LIBRARIES}
  )

configure_file(config.in.h config.h)
