AC_COPYRIGHT([[Copyright 2023 Jeff Greer. All rights reserved. Restrictions apply, see COPYRIGHT and LICENSE files.]])
AC_INIT([tendril], [0.1.0])
AC_ARG_WITH(librdkafka,       [--with-librdkafka=DIR   path to librdkafka installation filesystem i.e. /usr/local])
AC_LANG_PUSH([C++])
if[ "$with_librdkafka" == "" ]; then
	AC_MSG_ERROR([could not locate librdkafka installation file system, use --with-librdkafka=DIR])
else
	CPPFLAGS="-I$with_librdkafka/include $CPPFLAGS"
	LDFLAGS="-L$with_librdkafka/lib $LDFLAGS"
	librdkafka="$with_librdkafka/lib/librdkafka++.a"
fi
PKG_PROG_PKG_CONFIG
AC_CHECK_HEADERS([librdkafka/rdkafkacpp.h], [],[AC_MSG_ERROR([could not locate librdkafka installation file system, use --with-librdkafka=DIR])])
AC_CHECK_FILE([$librdkafka], [], [AC_MSG_ERROR([could not locate librdkafka installation file system, use --with-librdkafka=DIR])])
cwd=`pwd`
CPPFLAGS="-I$cwd/include $CPPFLAGS"
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AM_INIT_AUTOMAKE
AC_PROG_CXX
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
LT_INIT
AC_OUTPUT