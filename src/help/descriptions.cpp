#include <map>
#include <string>

#include "help.hpp"

map<string,string> description_map;

void cellar::help::set_description(string command, string description) {
    if (description.empty()) {
        if (description_map.find(command) == description_map.end()) { // not found
            return; // no description no cry
        } else {
            description_map.erase(command);
        }
    } else { // setting description
        description_map[command] = description;
    }
}

string cellar::help::get_description(string command) {
    if (description_map.find(command) == description_map.end()) { // not found
        return "";
    } else {
        return description_map.at(command);
    }
}
