find_program(RONN ronn)
find_program(GZIP gzip)

if(NOT RONN OR NOT GZIP)
	message(WARNING "Not generating manpages")
	if(NOT RONN)
		message(WARNING "    ronn not installed")
	endif(NOT RONN)
	if (NOT GZIP)
		message(WARNING "    gzip (somehow) not installed")
	endif(NOT GZIP)
	macro(generate_manpage)  # Empty, won't do anything
	endmacro(generate_manpage)
    macro(add_manpage_target) # ditto
    endmacro(add_manpage_target)
else(NOT RONN OR NOT GZIP)
    set(manpages)
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/man")
    macro(generate_manpage TARGET SECTION)
		set(ronnfile "${CMAKE_SOURCE_DIR}/doc/${TARGET}.${SECTION}.ronn")
        set(outfile "${CMAKE_CURRENT_BINARY_DIR}/man/${TARGET}.${SECTION}")
        add_custom_command(OUTPUT "${outfile}"
                DEPENDS "${ronnfile}"
                COMMAND ${RONN}
                # BULLSHIT: ronn doesn't let you specify your own output filenames,
                #           have to hack it with shell redirecting
                ARGS    -r --pipe "${ronnfile}" > "${outfile}"
        )
        add_custom_command(OUTPUT "${outfile}.gz"
                DEPENDS "${outfile}"
                COMMAND "${GZIP}"
                ARGS    -fk "${outfile}"
        )
        set(manpages ${manpages} "${outfile}.gz")
    endmacro(generate_manpage)

    macro(add_manpage_target) # this is a macro so we can call it after we've generated all our manpages
        add_custom_target(man ALL DEPENDS ${manpages})
        foreach(SECTION RANGE 1 9)
            file(GLOB sectionpages RELATIVE "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/man/*.${SECTION}.gz")
            install(FILES ${sectionpages} DESTINATION "${MAN_INSTALL_DIR}/man${SECTION}" OPTIONAL)
        endforeach(SECTION RANGE 1 9)
    endmacro(add_manpage_target)
endif(NOT RONN OR NOT GZIP)