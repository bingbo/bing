dnl $Id$
dnl config.m4 for extension bing

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(bing, for bing support,
dnl Make sure that the comment is aligned:
dnl [  --with-bing             Include bing support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(bing, whether to enable bing support,
dnl Make sure that the comment is aligned:
dnl [  --enable-bing           Enable bing support])

if test "$PHP_BING" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-bing -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/bing.h"  # you most likely want to change this
  dnl if test -r $PHP_BING/$SEARCH_FOR; then # path given as parameter
  dnl   BING_DIR=$PHP_BING
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for bing files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       BING_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$BING_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the bing distribution])
  dnl fi

  dnl # --with-bing -> add include path
  dnl PHP_ADD_INCLUDE($BING_DIR/include)

  dnl # --with-bing -> check for lib and symbol presence
  dnl LIBNAME=bing # you may want to change this
  dnl LIBSYMBOL=bing # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BING_DIR/$PHP_LIBDIR, BING_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_BINGLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong bing lib version or lib not found])
  dnl ],[
  dnl   -L$BING_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(BING_SHARED_LIBADD)

  PHP_NEW_EXTENSION(bing, bing.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi