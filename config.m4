dnl $Id$
dnl config.m4 for extension bing

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(bing, for bing support,
dnl Make sure that the comment is aligned:
dnl [  --with-bing             Include bing support])

dnl Otherwise use enable:以--enable-bing的形式添加扩展

PHP_ARG_ENABLE(bing, whether to enable bing support,
Make sure that the comment is aligned:
[  --enable-bing           Enable bing support])

dnl 如果以./configure --enable-bing的形式编译添加扩展，则$PHP_BING变量会自动为yes
if test "$PHP_BING" != "no"; then
  PHP_SUBST(BING_SHARED_LIBADD)

  PHP_NEW_EXTENSION(bing, bing.c bing_service.c,$ext_shared, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
