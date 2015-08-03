cmake_minimum_required(VERSION 3.0.0)
project(CC3K)

# Enable Cotire
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cotire/CMake")
include(cotire)

# Here we guarantee that Boost is in place along with
# Boost.ProgramOptions
set(LOCAL_BOOST "${CMAKE_SOURCE_DIR}/boost/boost/../")
find_package(Boost COMPONENTS program_options)
if(NOT Boost_FOUND)
  set(Boost_FOUND YES)
  set(Boost_INCLUDE_DIR ${LOCAL_BOOST})
endif()
if(NOT Boost_PROGRAM_OPTIONS_FOUND)
  set(Boost_PROGRAM_OPTIONS_FOUND YES)
  file(GLOB BOOST_PROGRAM_OPTIONS_SOURCES
    "${LOCAL_BOOST}/libs/program_options/src/*")
  add_library(boost_program_options ${BOOST_PROGRAM_OPTIONS_SOURCES})
  target_include_directories(boost_program_options PUBLIC ${LOCAL_BOOST})
  set(Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG boost_program_options)
  set(Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE boost_program_options)
endif()

# Try finding curses if we can, but if we can't then it's no big deal.
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

cotire(cc3k)

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
  $<$<CONFIG:Debug>:${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG}>
  $<$<NOT:$<CONFIG:Debug>>:${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}>
  ${CURSES_LIBRARIES}
  )

configure_file(config.in.hh config.hh)
