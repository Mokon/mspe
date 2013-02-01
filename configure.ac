# (C) 2010-2013 David Bond, All Rights Reserved

AC_INIT([mspe],[DEV-VERSION],[mokon@mokon.net],
  [mspe],[http://mokon.net])

AC_COPYRIGHT([(C) 2010-2013 David Bond])
AC_REVISION([$Revision: 0.0 $])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])

AC_ARG_ENABLE([debug],
  [  --enable-debug    Turn on debugging],
  [case "${enableval}" in
    yes) debug=true  ; release=false ;;
    no)  debug=false ; release=true  ;;
    *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
   esac],[debug=false ; release=true])
AM_CONDITIONAL([DEBUG],[test x$debug = xtrue])
AM_CONDITIONAL([RELEASE],[test x$release = xtrue])

if test x$debug = xtrue] ; then
AC_DEFINE([DEBUG], [1], [Debug Build])
else if test x$release = xtrue ; then
AC_DEFINE([RELEASE], [1], [Release Build])
AC_DEFINE([GOOGLE_STRIP_LOG], [1], [Strip Logging Messages from Release.])
fi fi

AC_LANG([C++])
AC_PROG_CXX

AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_USE_SYSTEM_EXTENSIONS
AC_PROG_LIBTOOL

AC_CHECK_LIB([gflags],[main])
AC_CHECK_LIB([glog],[main])

AC_CONFIG_FILES([
  Makefile
  obj/Makefile
])

AC_OUTPUT

