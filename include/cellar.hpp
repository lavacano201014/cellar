#ifndef __CELLAR_HPP
#define __CELLAR_HPP
#pragma once
#include <string>
#include <vector>

using namespace std;

namespace cellar {
    extern void print_header();
    extern void print_version(int,vector<string>);

    extern bool verbose;
}

#endif // __CELLAR_HPP
