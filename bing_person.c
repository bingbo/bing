//加载config.h,如果配置了的话
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//加载php头文件
#include "php.h"
#include "Zend/zend_interfaces.h" /* for zend_call_method_with_* */
#include "bing_person.h"

//声明类指针
zend_class_entry *person_ce;

//定义构造函数参数
ZEND_BEGIN_ARG_INFO_EX(config_arginfo, 0, 0, 1)
    ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()


//定义构造函数
ZEND_METHOD(person, __construct){
    zval *array_config;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"a", &array_config) == FAILURE){
        RETURN_NULL();
    }
    php_var_dump(&array_config,1 TSRMLS_CC);
    //接收参数并更新参数
    zend_update_property(person_ce,getThis(),"config",sizeof("config")-1,array_config TSRMLS_CC);
}

//定义析构函数
ZEND_METHOD(person,__destruct){
    zend_printf("destruct\n");
}

//定义doing函数
ZEND_METHOD(person,doing){
    zval *array_config;
    zval rv;
    //获取参数并输出
    array_config = zend_read_property(person_ce,getThis(),"config",sizeof("config")-1,0,&rv TSRMLS_CC);
    if(Z_TYPE_P(array_config) == IS_NULL || Z_TYPE_P(array_config) != IS_ARRAY){
        RETURN_FALSE;
    }
    RETURN_ZVAL(array_config,1,0);
}
//定义saying函数
ZEND_METHOD(person,saying){
    //该函数不能有参数传入
    if(zend_parse_parameters_none() == FAILURE){
        RETURN_FALSE;
    }
    array_init(return_value);
}

//声明所有的函数
const zend_function_entry person_functions[] = {
    //这里构造函数绑定参数
    ZEND_ME(person, __construct, config_arginfo, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    ZEND_ME(person,doing,NULL,ZEND_ACC_PUBLIC)
    ZEND_ME(person,saying,NULL,ZEND_ACC_PUBLIC)
    ZEND_ME(person,__destruct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
    PHP_FE_END
};

//类及属性注册
PHP_MINIT_FUNCTION(bing_person){
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Person", person_functions);
    person_ce = zend_register_internal_class(&ce TSRMLS_CC);

    zend_declare_property_null(person_ce,"saying",strlen("saying"),ZEND_ACC_PUBLIC);
    zend_declare_property_null(person_ce,"doing",strlen("doing"),ZEND_ACC_PUBLIC);

    return SUCCESS;
}


