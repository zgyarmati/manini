#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(manini, 0.1.0~, mr.zoltan.gyarmati@gmail.com)
AM_INIT_AUTOMAKE
AC_PROG_RANLIB
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strchr])


#check for doc generating tools
AC_CHECK_PROGS([A2X], [a2x])
if test -z "$A2X";
   then AC_MSG_WARN([asciidoc a2x not found - continuing without building man pages])
fi
AM_CONDITIONAL([HAVE_A2X], [test -n "$A2X"])

AC_CONFIG_FILES([Makefile
                 man/Makefile
                 src/Makefile
                 src/minIni/Makefile
                 src/minIni/dev/Makefile])
AC_OUTPUT
