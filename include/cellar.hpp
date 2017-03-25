#ifndef __CELLAR_HPP
#define __CELLAR_HPP
#pragma once
#include <string>
#include <vector>

#include "bottles.hpp"

using namespace std;

namespace cellar {
    extern void print_header();
    extern void print_version(int,vector<string>);

    extern bottles::Bottle active_bottle;
    
    extern bool verbose;
}

#endif // __CELLAR_HPP
