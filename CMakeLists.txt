cmake_minimum_required(VERSION 3.7.2)
project(cellar CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# local cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

# for installation rules, from CMake wiki
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/cellar")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(PythonInterp)
find_package(PythonModule)
find_python_module(cogapp REQUIRED)

find_package(Boost 1.63 REQUIRED COMPONENTS filesystem)

find_package(PkgConfig)
pkg_check_modules(TCLAP "tclap >= 1.2.1")
if(NOT TCLAP_FOUND)
MESSAGE(WARNING "TCLAP is required by this project, but was not found by CMake.
Continuing on the assumption that you've downloaded it from
http://tclap.sourceforge.net and put the headers in ./include
(wink, nudge)")
endif(NOT TCLAP_FOUND)

include_directories(include)
set(src "${CMAKE_SOURCE_DIR}/src")

set(coggedfiles)

file(GLOB_RECURSE cogfiles RELATIVE "${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/*.cog")

foreach(cogfile ${cogfiles})
        string(REGEX REPLACE ".cog\$" "" outfile "${cogfile}")
        set(thisfile "${CMAKE_SOURCE_DIR}/${outfile}")

        add_custom_command(OUTPUT "${thisfile}" PRE_BUILD
                COMMAND ${PYTHON_EXECUTABLE} -m cogapp -d -o "${outfile}" "${cogfile}"
                DEPENDS ${cogfile}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Greasing the cog for ${outfile}")

        set(coggedfiles ${coggedfiles} "${thisfile}")
endforeach(cogfile)

add_custom_target(cog ALL DEPENDS ${coggedfiles})

set(cellar_LIBRARIES)
function(cellar_library target)
        file(GLOB_RECURSE targetsources RELATIVE "${CMAKE_SOURCE_DIR}"
                "${CMAKE_SOURCE_DIR}/src/${target}/*.cpp")
        file(GLOB_RECURSE targetcoggedsources RELATIVE "${CMAKE_SOURCE_DIR}"
                "${CMAKE_SOURCE_DIR}/src/${target}/*.cpp.cog")
        foreach(targetcog ${targetcoggedsources})
                string(REGEX REPLACE ".cog\$" "" this "${targetcog}")
                set(targetsources ${targetsources} ${this})
        endforeach(targetcog)

        add_library(${target} SHARED ${targetsources})
        add_dependencies(${target} cog)

        set(cellar_LIBRARIES ${cellar_LIBRARIES} ${target} PARENT_SCOPE)
endfunction(cellar_library)

cellar_library(bottles)
cellar_library(launch)

add_executable(cellar ${src}/cellar.cpp ${src}/commands.cpp ${src}/fs.cpp
        ${src}/version.cpp ${src}/output.cpp ${src}/help/help.cpp)
target_link_libraries(cellar ${cellar_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(cellar cog) # effectively redundant but a couple of the bin's
                             # files are cogged, so this is mostly for people
                             # looking at CMakeLists.txt for hints

install(TARGETS cellar ${cellar_LIBRARIES}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib/cellar
        ARCHIVE DESTINATION share/cellar)
