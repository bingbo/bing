#ifndef BING_SERVICE_H
#define BING_SERVICE_H

#define BING_SERVICE_PROPERTY_NAME_PARAMS "_params"
#define BING_SERVICE_PROPERTY_NAME_RESULT "_result"


//声明全局变量的引用
extern zend_class_entry *bing_service_ce,*bing_service_parent_ce,*bing_service_interface_ce;

PHP_MINIT_FUNCTION(bing_service);
#endif
