cmake_minimum_required(VERSION 3.7.2)
project(cellar)

find_package(PythonInterp)

include_directories(include)

set(coggedfiles)

file(GLOB cogfiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cog")

foreach(cogfile ${cogfiles})
        string(REGEX REPLACE ".in\$" "" outfile "${cogfile}")
        set(thisfile "${CMAKE_CURRENT_SOURCE_DIR}/${outfile}")

        add_custom_command(OUTPUT "${outfile}"
                COMMAND ${PYTHON_EXECUTABLE} -m cogapp -d -o "${outfile}" "${cogfile}"
                DEPENDS ${cogfile}
                COMMENT "Greasing the cog for ${outfile}")

        set(coggedfiles ${coggedfiles} ${thisfile})
endforeach(cogfile)

add_custom_target(cog ALL DEPENDS ${cogfiles})

add_executable(cellar src/cellar.cpp src/commands.cpp src/fs.cpp
        src/bottles.cpp src/version.cpp)
add_dependencies(cellar cog)
