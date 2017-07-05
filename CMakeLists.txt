cmake_minimum_required(VERSION 3.7.2)
project(cellar CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-pipe")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_RELWITHDBGINFO "${CMAKE_CXX_FLAGS_RELEASE} -g")

if(NOT CMAKE_BUILD_TYPE)
        message(STATUS "Assuming this is a release build. -DCMAKE_BUILD_TYPE=Debug otherwise.")
        set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

# local cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

# for installation rules, from CMake wiki
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/cellar")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include(Git)
git_init()

include(Ronn)

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

include_directories("${CMAKE_SOURCE_DIR}/include")
configure_file("${CMAKE_SOURCE_DIR}/include/cmake.hpp.in"
                "${CMAKE_CURRENT_BINARY_DIR}/include/cmake.hpp")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
set(src "${CMAKE_SOURCE_DIR}/src")

set(coggedfiles)

file(GLOB_RECURSE cogfiles RELATIVE "${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/*.cog")

foreach(cogfile ${cogfiles})
        # thisfile = absolute path to output file
        # outfile = relative path
        # TODO: fix that
        string(REGEX REPLACE ".cog\$" "" outfile "${cogfile}")
        set(thisfile "${CMAKE_CURRENT_BINARY_DIR}/${outfile}")

        add_custom_command(OUTPUT "${thisfile}" PRE_BUILD
                COMMAND ${PYTHON_EXECUTABLE} -m cogapp -d -o "${thisfile}" "${cogfile}"
                DEPENDS ${cogfile}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Greasing the cog for ${outfile}")

        set(coggedfiles ${coggedfiles} "${thisfile}")
endforeach(cogfile)

add_custom_target(cog ALL DEPENDS ${coggedfiles})

function(get_sources globtarget output)
        file(GLOB_RECURSE targetsources RELATIVE "${CMAKE_SOURCE_DIR}"
                "${CMAKE_SOURCE_DIR}/${globtarget}")
        file(GLOB_RECURSE targetcoggedsources RELATIVE "${CMAKE_SOURCE_DIR}"
                "${CMAKE_SOURCE_DIR}/${globtarget}.cog")
        foreach(targetcog ${targetcoggedsources})
                string(REGEX REPLACE ".cog\$" "" this "${targetcog}")
                set(targetsources ${targetsources} ${this})
        endforeach(targetcog)

        set(${output} ${targetsources} PARENT_SCOPE)
endfunction(get_sources)

set(cellar_LIBRARIES)
function(cellar_library)
        set(multiValueArgs SUBDIRS)
        set(oneValueArgs TARGET)
        cmake_parse_arguments(cellar_library "" "${oneValueArgs}"
                "${multiValueArgs}" ${ARGN})

        set(target ${cellar_library_TARGET})

        set(targetsources)
        foreach(subdir ${cellar_library_SUBDIRS})
                get_sources("src/${subdir}/*.cpp" subdirsources)

                foreach(source ${subdirsources})
                        set(targetsources ${targetsources} ${source})
                endforeach(source)
        endforeach(subdir)

        add_library(${target} SHARED ${targetsources})
        add_dependencies(${target} cog)

        set(cellar_LIBRARIES ${cellar_LIBRARIES} ${target} PARENT_SCOPE)
endfunction(cellar_library)

cellar_library(TARGET cellarlib SUBDIRS bottles launch config)

file(GLOB coresources RELATIVE "${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB corecoggedsources RELATIVE "${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/src/*.cpp.cog")
foreach(corecog ${corecoggedsources})
        string(REGEX REPLACE ".cog\$" "" this "${corecog}")
        set(coresources ${coresources} ${this})
endforeach(corecog)

get_sources("src/help/*.cpp" helpsources)

add_executable(cellar ${coresources} ${helpsources})
target_link_libraries(cellar ${cellar_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(cellar cog) # effectively redundant but a couple of the bin's
                             # files are cogged, so this is mostly for people
                             # looking at CMakeLists.txt for hints

generate_manpage(cellar 1)
add_manpage_target()

install(TARGETS cellar ${cellar_LIBRARIES}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib/cellar
        ARCHIVE DESTINATION share/cellar)
