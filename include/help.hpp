#ifndef __HELP_HPP
#define __HELP_HPP
#pragma once

#include <string>

using namespace std;

namespace cellar {
    namespace help {
        extern void set_description(string,string);
        extern string get_description(string);
    }
}

#endif // __HELP_HPP
