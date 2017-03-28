#ifndef __CELLAR_HPP
#define __CELLAR_HPP
#pragma once
#include <string>
#include <vector>

#include "bottles.hpp"

using namespace std;

namespace cellar {
    extern void print_header();

    extern bool dryrun;
    extern bool verbose;
}

#endif // __CELLAR_HPP
