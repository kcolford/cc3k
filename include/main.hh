#ifndef MAIN_HH
#define MAIN_HH

#include "property_type.hh"
#include <map>
#include <string>

extern std::map<std::string, property_type> config;

int run_game(int argc, char *argv[]);

#endif
