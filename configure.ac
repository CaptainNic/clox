AC_PREREQ([2.68])
AC_INIT([clox], [0.1], [nicolasbreidinger@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdint.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_REALLOC

# Makefiles
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

# Features
AC_ARG_ENABLE(
    [dbg-trace],
    AS_HELP_STRING([--enable-dbg-trace], [Enables debug tracing]),
    [dbg_trace=yes]
)

AS_IF([test "x$dbg_trace" == "xyes"], [
    AC_DEFINE([DBG_TRACE_EXECUTION], [1], [Debug tracing for bytecode execution])
])

AC_OUTPUT