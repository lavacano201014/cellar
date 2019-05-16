#pragma once

#include <string>

namespace cellar {
    namespace paths {
        extern std::string translate(std::string in_path, bool lazy = false);
        extern std::string resolve_drive_letter(std::string in_path);
    }
}
