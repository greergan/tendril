AC_COPYRIGHT([[Copyright 2023 Jeff Greer. All rights reserved. Restrictions apply, see COPYRIGHT and LICENSE files.]])
AC_INIT([tendril], [0.1.0])
AC_ARG_WITH(librdkafka,       [--with-librdkafka=DIR   path to librdkafka installation filesystem i.e. /usr/local])
AC_ARG_WITH(libprometheus-cpp,       [--with-libprometheus-cpp=DIR   path to librdkafka installation filesystem i.e. /usr/local])
AC_LANG_PUSH([C++])
if[ "$with_librdkafka" == "" ]; then
	AC_MSG_ERROR([could not locate librdkafka installation file system, use --with-librdkafka=DIR])
else
	CPPFLAGS="-I$with_librdkafka/include $CPPFLAGS"
	LDFLAGS="-L$with_librdkafka/lib $LDFLAGS"
	librdkafka="$with_librdkafka/lib/librdkafka.a"
	librdkafkapp="$with_librdkafka/lib/librdkafka++.a"
	KAFKALIB_PATH="$with_librdkafka/lib"
fi
if[ "$with_libprometheus_cpp" == "" ]; then
	AC_MSG_ERROR([could not locate libprometheus installation file system, use --with-libprometheus-cpp=DIR])
else
	CPPFLAGS="-I$with_libprometheus_cpp/include $CPPFLAGS"
	LDFLAGS="-L$with_libprometheus_cpp/lib $LDFLAGS"
	libprometheus_cpp_core="$with_libprometheus_cpp/lib/libprometheus-cpp-core.so"
	libprometheus_cpp_pull="$with_libprometheus_cpp/lib/libprometheus-cpp-pull.so"
	PROMETHEUS_CPP_PATH="$with_libprometheus_cpp/lib"
fi
PKG_PROG_PKG_CONFIG
AC_CHECK_HEADERS([librdkafka/rdkafkacpp.h], [],[AC_MSG_ERROR([could not locate librdkafka installation file system, use --with-librdkafka=DIR])])
AC_CHECK_FILE([$librdkafka], [], [AC_MSG_ERROR([could not locate librdkafka installation file system, use --with-librdkafka=DIR])])
AC_CHECK_FILE([$librdkafkapp], [], [AC_MSG_ERROR([could not locate librdkafka installation file system, use --with-librdkafka=DIR])])
AC_CHECK_HEADERS([prometheus/counter.h], [], [AC_MSG_ERROR([could not locate libprometheus installation file system, use --with-libprometheus-cpp=DIR])])
AC_CHECK_HEADERS([prometheus/exposer.h], [], [AC_MSG_ERROR([could not locate libprometheus installation file system, use --with-libprometheus-cpp=DIR])])
AC_CHECK_HEADERS([prometheus/registry.h],[], [AC_MSG_ERROR([could not locate libprometheus installation file system, use --with-libprometheus-cpp=DIR])])
AC_CHECK_FILE([$libprometheus_cpp_core], [], [AC_MSG_ERROR([could not locate libprometheus installation file system, use --with-libprometheus-cpp=DIR])])
AC_CHECK_FILE([$libprometheus_cpp_pull], [], [AC_MSG_ERROR([could not locate libprometheus installation file system, use --with-libprometheus-cpp=DIR])])
cwd=`pwd`
CPPFLAGS="-I$cwd/include $CPPFLAGS"
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST([KAFKALIB_PATH])
AC_SUBST([PROMETHEUS_CPP_PATH])
AM_INIT_AUTOMAKE
AC_PROG_CXX
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
LT_INIT
AC_OUTPUT