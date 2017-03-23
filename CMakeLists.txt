cmake_minimum_required(VERSION 3.7.2)
project(cellar CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PythonInterp)
find_package(Boost 1.63 REQUIRED COMPONENTS filesystem)

include_directories(include)
set(src "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(coggedfiles)

file(GLOB_RECURSE cogfiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cog")

foreach(cogfile ${cogfiles})
        string(REGEX REPLACE ".cog\$" "" outfile "${cogfile}")
        set(thisfile "${CMAKE_CURRENT_SOURCE_DIR}/${outfile}")

        add_custom_command(OUTPUT "${thisfile}"
                COMMAND ${PYTHON_EXECUTABLE} -m cogapp -d -o "${outfile}" "${cogfile}"
                DEPENDS ${cogfile}
                COMMENT "Greasing the cog for ${thisfile}")

        set(coggedfiles ${coggedfiles} "${thisfile}")
endforeach(cogfile)

add_custom_target(cog ALL DEPENDS ${coggedfiles})

add_executable(cellar ${src}/cellar.cpp ${src}/commands.cpp ${src}/fs.cpp
        ${src}/bottles.cpp ${src}/version.cpp)
add_dependencies(cellar cog)
target_link_libraries(cellar ${Boost_LIBRARIES})
