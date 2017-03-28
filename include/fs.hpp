#ifndef __FS_HPP
#define __FS_HPP
#pragma once

#include <string>
#include <vector>

using namespace std;

namespace cellar {
	namespace fs {
        typedef void (*CopyCallbackFunc)(string,string); 
        typedef void (*RemoveCallbackFunc)(string); 
		extern vector<string> listdir(string path);
        
        extern bool recursive_copy(string, string);
        extern bool recursive_remove(string);
        extern bool recursive_copy(string, string, CopyCallbackFunc);
        extern bool recursive_remove(string, RemoveCallbackFunc);
	}
}

#endif // __FS_HPP
