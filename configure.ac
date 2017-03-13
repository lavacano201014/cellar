AC_INIT([cellar], [0])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11

AX_BOOST_BASE([1.63], , [AC_MSG_ERROR([boost 1.63 required])])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT
