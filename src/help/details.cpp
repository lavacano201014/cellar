#include <map>
#include <string>

#include "help.hpp"

map<string,string> details_map;

void cellar::help::set_details(string command, string details) {
    if (details.empty()) {
        if (details_map.find(command) == details_map.end()) { // not found
            return; // no details no cry
        } else {
            details_map.erase(command);
        }
    } else { // setting details
        details_map[command] = details;
    }
}

string cellar::help::get_details(string command) {
    if (details_map.find(command) == details_map.end()) { // not found
        return "";
    } else {
        return details_map.at(command);
    }
}
