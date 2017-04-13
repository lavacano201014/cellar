#ifndef __OUTPUT_HPP
#define __OUTPUT_HPP

#include <string>

namespace cellar {
    namespace output {
        extern void statement(std::string);
        extern void warning(std::string);
        extern void error(std::string);

        extern void statement(std::string parm, bool);
        extern void warning(std::string, bool);
        extern void error(std::string, bool);

        extern void blank_line(bool verbose = false);
        
        extern bool colors;
        extern void detect_colors();
    }
}

#endif // __OUTPUT_HPP
