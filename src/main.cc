// The cc3k game.

#include <config.hh>
#include "main.hh"
#include "Game.hh"
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void parse_opts(int argc, char *argv[])
{
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "print this help message")
    ("load-file", po::value<std::string>(), "load floors from this file")
    ("seed", po::value<int>(), "initalize with a random seed")
#if CURSES_FOUND
# ifndef ENABLE_DEFAULT_ADVANCED_GAME
    ("with-curses", "use curses display")
# else
    ("without-curses", "don't use curses display")
# endif
#endif
    ;
  po::positional_options_description p;
  p.add("load-file", 1);
  p.add("seed", 1);
  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
            .options(desc).positional(p).run(), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    exit(0);
  }

#define _ARG(ID, TGT, DATA)                                             \
  do { if (vm.count(ID)) config[ID] = config[TGT] = DATA; } while (0)
#define CHECK_ARG(ID, TGT, DATA) _ARG(#ID, #TGT, DATA)
#define ADD_ARG(ID) _ARG(#ID, #ID, vm[#ID].as<std::string>())
  ADD_ARG(load-file);
  ADD_ARG(seed);
  CHECK_ARG(with-curses, use_curses, true);
  CHECK_ARG(without-curses, use_curses, false);
#undef ADD_ARG
#undef CHECK_ARG
#undef _ARG
}  

std::map<std::string, property_type> config;  

int run_game(int argc, char *argv[])
{

#ifdef ENABLE_DEFAULT_ADVANCED_GAME
  config["use_curses"] = true;
#endif

  config["seed"] = time(NULL);

  parse_opts(argc, argv);

  std::ifstream file;
  if (config.count("load-file")) {
    file.open(config["load-file"].as<std::string>().c_str());
    game.setIn(file);
  }

  srand(config["seed"]);

  config["advanced_game"] = config["use_curses"];

  game.run();
  return 0;
}
