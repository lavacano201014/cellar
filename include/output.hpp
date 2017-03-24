#ifndef __OUTPUT_HPP
#define __OUTPUT_HPP

#include <string>

namespace cellar {
    namespace output {
        extern void statement(std::string parm);
        extern void warning(std::string parm);
        extern void error(std::string);
    }
}

#endif // __OUTPUT_HPP
