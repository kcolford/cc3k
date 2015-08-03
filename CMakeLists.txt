cmake_minimum_required(VERSION 3.0.0)
project(CC3K)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(Curses)

add_executable(cc3k
  src/cc3k.cc
  src/Character.cc
  src/Character.hh
  src/CollectComponent.hh
  src/CollectGold.hh
  src/collision_masks.hh
  src/Controller.hh
  src/DragonAI.hh
  src/Enemy.cc
  src/Enemy.hh
  src/fix_dragons.cc
  src/fix_dragons.hh
  src/Floor.cc
  src/FloorFiller.cc
  src/Floor.hh
  src/Game.cc
  src/Game.hh
  src/GameObject.cc
  src/GameObject.hh
  src/GameObjectPtr.hh
  src/Gold.cc
  src/Gold.hh
  src/main.cc
  src/main.hh
  src/make_view.cc
  src/make_view.hh
  src/Player.cc
  src/Player.hh
  src/PlayerStats.cc
  src/PlayerStats.hh
  src/Potion.cc
  src/Potion.hh
  src/SceneGraph.cc
  src/SceneGraph.hh
  src/shared_ptr.hh
  src/Stairs.cc
  src/TextView.cc
  src/TextView.hh
  src/View.cc
  src/View.hh
  src/within_one_block.hh
  )

target_sources(cc3k PUBLIC
  $<$<BOOL:CURSES_FOUND>:src/CursesView.cc src/CursesView.hh>
  )  
target_include_directories(cc3k PUBLIC
  ${Boost_INCLUDE_DIRS}
  ${CURSES_INCLUDE_DIRS}
  )
target_link_libraries(cc3k
  ${Boost_LIBRARIES}
  ${CURSES_LIBRARIES}
  )

configure_file(config.in.h config.h)
