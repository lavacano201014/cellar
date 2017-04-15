#ifndef __CONFIG_HPP
#define __CONFIG_HPP
#pragma once

#include "json.hpp"

using nlohmann::json;

namespace cellar {
    namespace config {
        json get_default_config();
    }
}

#endif // __CONFIG_HPP
