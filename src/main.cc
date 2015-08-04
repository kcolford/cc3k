// The cc3k game.

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

std::map<std::string, int> config;

int run_game(int argc, char *argv[])
{
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "print this help message")
    ("load-file", po::value<std::string>(),
     "load floors from this file")
    ("seed", po::value<int>(&config["random_seed"])->implicit_value(0)->default_value(time(NULL)),
     "initalize with a random seed")
    ("curses",po::bool_switch((bool *) &config["use_curses"]),
     "use curses display")
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
    return 0;
  }

  std::ifstream file;
  if (vm.count("load-file")) {
    file.open(vm["load-file"].as<std::string>().c_str());
    game.setIn(file);
  }

  srand(config["random_seed"]);

  config["advanced_game"] = config["use_curses"];

  game.run();
  return 0;
}
