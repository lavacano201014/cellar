#ifndef __FS_HPP
#define __FS_HPP
#pragma once

#include <string>
#include <vector>

using namespace std;

namespace cellar {
	namespace fs {
		extern vector<string> listdir(string path);
        extern bool recursive_copy(string, string);
	}
}

#endif // __FS_HPP
