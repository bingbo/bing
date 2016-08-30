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
#include "bing_service.h"

zend_class_entry *bing_service_ce, *i_bing_service_ce;

//bing_service_interface接口函数
zend_function_entry i_bing_service_functions[] = {
    PHP_ABSTRACT_ME(i_bing_service, execute, NULL)
    PHP_FE_END
};

//定义实现getDoc方法，这里也可以用ZEND_METHOD
PHP_METHOD(bing_service, getDoc)
{
    php_printf("这是getDoc方法!!\n");
}
//定义构造函数
PHP_METHOD(bing_service, __construct)
{
    php_printf("这是bing_service的构造函数!!\n");
}
//实现接口的函数
PHP_METHOD(bing_service, execute){
    php_printf("这是实现接口的execute函数");
}

//bing_service的所有方法
zend_function_entry bing_service_functions[] = {
    PHP_ME(bing_service, getDoc, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(bing_service, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(bing_service, execute, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END	/* Must be the last line in bing_functions[] */
};

/* 这里在模块初始化时注册类
 */
PHP_MINIT_FUNCTION(bing_service)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
    zend_class_entry ce, i_ce;
    INIT_CLASS_ENTRY(i_ce, "bing_service_interface", i_bing_service_functions);
    i_bing_service_ce = zend_register_internal_interface(&i_ce TSRMLS_CC);

    INIT_CLASS_ENTRY(ce, "bing_service", bing_service_functions);
    bing_service_ce = zend_register_internal_class(&ce TSRMLS_CC);
    zend_class_implements(bing_service_ce TSRMLS_CC, 1, i_bing_service_ce);

    //定义属性
    //zend_declare_property_null(bing_service_ce, "doc", strlen("doc"), ZEND_ACC_PUBLIC TSRMLS_CC);
	return SUCCESS;
}
/*
 * ZEND_ACC_PUBLIC
 * ZEND_ACC_PRIVATE
 * ZEND_ACC_PROTECTED
 */
/* }}} */

