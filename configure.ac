#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ATLAS IPC Library], [1.0], [ravitillo@lbl.gov])
AC_CONFIG_SRCDIR([include/PipeSocketFactory.h])
AC_CONFIG_HEADERS([config/config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gettimeofday mkfifo strcasecmp strdup])

AC_CONFIG_FILES([Makefile])
#AC_CONFIG_SUBDIRS([zeromq])
AC_OUTPUT