#ifndef __CELLAR_HPP
#define __CELLAR_HPP
#pragma once
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "bottles.hpp"

using namespace std;
using nlohmann::json;

namespace cellar {
    extern void print_header();

    extern bool dryrun;
    extern bool verbose;

    extern json global_config;
}

#endif // __CELLAR_HPP
