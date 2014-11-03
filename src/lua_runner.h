#ifndef LUA_RUNNER_H
#define LUA_RUNNER_H

#include <tuple>
#include <string>

std::tuple<std::string, int> run(std::string const &script);

#endif
