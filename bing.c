/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:ibingbo                                                       |
  +----------------------------------------------------------------------+
*/

/* $Id$ */
//加载config.h,如果配置了的话
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//加载php头文件
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bing.h"
#include "main/SAPI.h"
#include "Zend/zend_alloc.h"
#include "ext/standard/php_string.h"

/* If you declare any globals in php_bing.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(bing)
*/

/* True global resources - no need for thread safety here */
static int le_bing;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("bing.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_bing_globals, bing_globals)
    STD_PHP_INI_ENTRY("bing.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_bing_globals, bing_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_bing_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(bing_version)
{
    /*
    zend_string *str;
    str = PHP_BING_VERSION;
    */
	RETURN_STRING(PHP_BING_VERSION);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_bing_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_bing_init_globals(zend_bing_globals *bing_globals)
{
	bing_globals->global_value = 0;
	bing_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(bing)
{
//	REGISTER_INI_ENTRIES();
    ZEND_MODULE_STARTUP_N(bing_service)(INIT_FUNC_ARGS_PASSTHRU);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(bing)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(bing)
{
#if defined(COMPILE_DL_BING) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(bing)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(bing)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "bing support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ bing_functions[]
 *
 * Every user visible function must have an entry in bing_functions[].
 */
const zend_function_entry bing_functions[] = {
	PHP_FE(bing_version,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in bing_functions[] */
};
/* }}} */

/* {{{ bing_module_entry
 */
zend_module_entry bing_module_entry = {
	STANDARD_MODULE_HEADER,
	"bing",
	bing_functions,
	PHP_MINIT(bing),
	PHP_MSHUTDOWN(bing),
	PHP_RINIT(bing),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(bing),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(bing),
	PHP_BING_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BING
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(bing)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
