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
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */
#include "bing_service.h"

zend_class_entry *bing_service_ce, *bing_service_parent_ce, *bing_service_interface_ce;

/********************service interface接口定义*******************************/
//bing_service_interface接口函数
zend_function_entry bing_service_interface_functions[] = {
    PHP_ABSTRACT_ME(bing_service_interface, execute, NULL)
    PHP_FE_END
};

/********************service interface接口定义*******************************/

/********************service abstract抽象类定义*******************************/
//定义实现getDoc方法，这里也可以用ZEND_METHOD
PHP_METHOD(bing_service_parent, getDoc)
{
    php_printf("这是service's getDoc方法!!\n");
}
//定义构造函数
PHP_METHOD(bing_service_parent, __construct)
{
    php_printf("这是bing_service_parent的构造函数!!\n");
}
//实现接口的函数
PHP_METHOD(bing_service_parent, execute){
    php_printf("这是实现接口的execute函数!!\n");
    zval *this_zval;
    this_zval = getThis();
    zend_call_method_with_0_params(this_zval,bing_service_ce,NULL,"process",NULL);
}

//bing_service的所有方法
zend_function_entry bing_service_parent_functions[] = {
    PHP_ME(bing_service_parent, getDoc, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(bing_service_parent, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(bing_service_parent, execute, NULL, ZEND_ACC_PUBLIC)
    PHP_ABSTRACT_ME(bing_service_parent, process, NULL)
	PHP_FE_END	/* Must be the last line in bing_functions[] */
};
/********************service abstract抽象类定义*******************************/

/********************service 子类定义*******************************/
//实现process方法，这里也可以用ZEND_METHOD
PHP_METHOD(bing_service, process)
{
    php_printf("这是service's process方法!!\n");
}

//bing_service的所有方法
zend_function_entry bing_service_functions[] = {
    PHP_ME(bing_service, process, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END	/* Must be the last line in bing_functions[] */
};
/********************service 子类定义*******************************/



/* 这里在模块初始化时注册类
 */
PHP_MINIT_FUNCTION(bing_service)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
    zend_class_entry ce, i_ce,p_ce;
    /***********************注册Bing_Service_Interface接口**********************/
    INIT_CLASS_ENTRY(i_ce, "Bing_Service_Interface", bing_service_interface_functions);
    //注册接口
    bing_service_interface_ce = zend_register_internal_interface(&i_ce TSRMLS_CC);
    /***********************注册Bing_Service_Interface接口**********************/

    /***********************注册Bing_Service_Abstract抽象类**********************/
    INIT_CLASS_ENTRY(p_ce, "Bing_Service_Abstract", bing_service_parent_functions);
    bing_service_parent_ce = zend_register_internal_class(&p_ce TSRMLS_CC);
    //实现接口
    zend_class_implements(bing_service_parent_ce TSRMLS_CC, 1, bing_service_interface_ce);
    //用abstract显式声明为抽象类
    bing_service_parent_ce->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;
    /***********************注册Bing_Service_Abstract抽象类**********************/

    /***********************注册Bing_Service类**********************/
    INIT_CLASS_ENTRY(ce, "Bing_Service", bing_service_functions);
    //注册子类并继承父类
    bing_service_ce = zend_register_internal_class_ex(&ce,bing_service_parent_ce);
    //bing_service_ce->ce_flags |= ZEND_ACC_FINAL_CLASS；
    /***********************注册Bing_Service类**********************/

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

