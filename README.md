# bing
this is a demo about php extension development

## 编译安装

```bash
phpize
./configure
make
##配置php.ini加入
[bing]
extension = "xxx/xxx/bing.so"
```

## 该扩展DEMO实现了以下php代码的功能

```php
/**
 * 定义了bing_version()方法获取bing.so的版本号
 */
function bing_version(){
    return BING_VERSION;
}

/**
 * 定义了Bing_Service_Interface接口
 */
interface Bing_Service_Interface{
    public function execute();
}

/**
 * 定义了抽象类Bing_Service_Abstract,
 * 且实现了接口Bing_Service_Interface的execute方法
 */
abstract class Bing_Service_Abstract implements Bing_Service_Interface{

    /**
     * 定义了构造函数
     */
    public function __construct(){
        echo "这是Bing_Service_Abstract的构造函数方法!!\n";
    }
    
    /**
     * 定义抽象方法，让子类实现
     */
    public abstract function process();

    /**
     * 实现接口的方法,并调用自身的process方法
     */
    public function execute(){
        echo "这是Bing_Service_Abstract的execute方法!!\n";
        $this->process();
    }
}

/**
 * 定义子类继承Bing_Service_Abstract父类
 */
final class Bing_Service extends Bing_Service_Abstract{
    /**
     * 实现父类的process方法
     */
    public function process(){
        echo "这是Bing_Service的process方法!!\n";
    }
}
```

运行测试代码：

```php
dl('bing.so');

echo bing_version() . "\n";

$obj = new Bing_Service();
$obj->getDoc();
$obj->execute();
```

结果如下：

```
0.1.0
这是bing_service_parent的构造函数!!
这是service's getDoc方法!!
这是实现接口的execute函数!!
这是service's process方法!!
```

## PHP中的宏定义

> 扩展开发的API基本上在Zend/zend_API.h里有定义

### 方法或类修饰符

```c
/**在Zend/zend_compile.h中**/
/* method flags (types) 方法修饰符类型*/
#define ZEND_ACC_STATIC			0x01
#define ZEND_ACC_ABSTRACT		0x02
#define ZEND_ACC_FINAL			0x04
#define ZEND_ACC_IMPLEMENTED_ABSTRACT		0x08

/* class flags (types) 类修饰符类型*/
/* ZEND_ACC_IMPLICIT_ABSTRACT_CLASS is used for abstract classes (since it is set by any abstract method even interfaces MAY have it set, too). */
/* ZEND_ACC_EXPLICIT_ABSTRACT_CLASS denotes that a class was explicitly defined as abstract by using the keyword. */
#define ZEND_ACC_IMPLICIT_ABSTRACT_CLASS	0x10
#define ZEND_ACC_EXPLICIT_ABSTRACT_CLASS	0x20
#define ZEND_ACC_INTERFACE		            0x40
#define ZEND_ACC_TRAIT						0x80
#define ZEND_ACC_ANON_CLASS                 0x100
#define ZEND_ACC_ANON_BOUND                 0x200

/* method flags (visibility)类方法修饰符类型 */
/* The order of those must be kept - public < protected < private */
#define ZEND_ACC_PUBLIC		0x100
#define ZEND_ACC_PROTECTED	0x200
#define ZEND_ACC_PRIVATE	0x400
#define ZEND_ACC_PPP_MASK  (ZEND_ACC_PUBLIC | ZEND_ACC_PROTECTED | ZEND_ACC_PRIVATE)

#define ZEND_ACC_CHANGED	0x800
#define ZEND_ACC_IMPLICIT_PUBLIC	0x1000

/* method flags (special method detection) */
#define ZEND_ACC_CTOR		0x2000
#define ZEND_ACC_DTOR		0x4000
#define ZEND_ACC_CLONE		0x8000

/* method flag used by Closure::__invoke() */
#define ZEND_ACC_USER_ARG_INFO 0x80

/* method flag (bc only), any method that has this flag can be used statically and non statically. */
#define ZEND_ACC_ALLOW_STATIC	0x10000

/* shadow of parent's private method/property */
#define ZEND_ACC_SHADOW 0x20000

/* deprecation flag */
#define ZEND_ACC_DEPRECATED 0x40000

/* class implement interface(s) flag */
#define ZEND_ACC_IMPLEMENT_INTERFACES 0x80000
#define ZEND_ACC_IMPLEMENT_TRAITS	  0x400000

/* class constants updated */
#define ZEND_ACC_CONSTANTS_UPDATED	  0x100000

/* user class has methods with static variables */
#define ZEND_HAS_STATIC_IN_METHODS    0x800000


#define ZEND_ACC_CLOSURE              0x100000
#define ZEND_ACC_GENERATOR            0x800000

#define ZEND_ACC_NO_RT_ARENA          0x80000

/* call through user function trampoline. e.g. __call, __callstatic */
#define ZEND_ACC_CALL_VIA_TRAMPOLINE  0x200000

/* call through internal function handler. e.g. Closure::invoke() */
#define ZEND_ACC_CALL_VIA_HANDLER     ZEND_ACC_CALL_VIA_TRAMPOLINE

/* disable inline caching */
#define ZEND_ACC_NEVER_CACHE          0x400000

#define ZEND_ACC_VARIADIC				0x1000000

#define ZEND_ACC_RETURN_REFERENCE		0x4000000
#define ZEND_ACC_DONE_PASS_TWO			0x8000000

/* class has magic methods __get/__set/__unset/__isset that use guards */
#define ZEND_ACC_USE_GUARDS				0x1000000

/* function has typed arguments */
#define ZEND_ACC_HAS_TYPE_HINTS			0x10000000

/* op_array has finally blocks */
#define ZEND_ACC_HAS_FINALLY_BLOCK		0x20000000

/* internal function is allocated at arena */
#define ZEND_ACC_ARENA_ALLOCATED		0x20000000

/* Function has a return type (or class has such non-private function) */
#define ZEND_ACC_HAS_RETURN_TYPE		0x40000000

/* op_array uses strict mode types */
#define ZEND_ACC_STRICT_TYPES			0x80000000
```

### 返回值宏定义

```c
/**在Zend/zend_API.h中**/
#define RETVAL_BOOL(b)					ZVAL_BOOL(return_value, b)
#define RETVAL_NULL() 					ZVAL_NULL(return_value)
#define RETVAL_LONG(l) 					ZVAL_LONG(return_value, l)
#define RETVAL_DOUBLE(d) 				ZVAL_DOUBLE(return_value, d)
#define RETVAL_STR(s)			 		ZVAL_STR(return_value, s)
#define RETVAL_INTERNED_STR(s)	 		ZVAL_INTERNED_STR(return_value, s)
#define RETVAL_NEW_STR(s)		 		ZVAL_NEW_STR(return_value, s)
#define RETVAL_STR_COPY(s)		 		ZVAL_STR_COPY(return_value, s)
#define RETVAL_STRING(s)		 		ZVAL_STRING(return_value, s)
#define RETVAL_STRINGL(s, l)		 	ZVAL_STRINGL(return_value, s, l)
#define RETVAL_EMPTY_STRING() 			ZVAL_EMPTY_STRING(return_value)
#define RETVAL_RES(r)			 		ZVAL_RES(return_value, r)
#define RETVAL_ARR(r)			 		ZVAL_ARR(return_value, r)
#define RETVAL_OBJ(r)			 		ZVAL_OBJ(return_value, r)
#define RETVAL_ZVAL(zv, copy, dtor)		ZVAL_ZVAL(return_value, zv, copy, dtor)
#define RETVAL_FALSE  					ZVAL_FALSE(return_value)
#define RETVAL_TRUE   					ZVAL_TRUE(return_value)

#define RETURN_BOOL(b) 					{ RETVAL_BOOL(b); return; }
#define RETURN_NULL() 					{ RETVAL_NULL(); return;}
#define RETURN_LONG(l) 					{ RETVAL_LONG(l); return; }
#define RETURN_DOUBLE(d) 				{ RETVAL_DOUBLE(d); return; }
#define RETURN_STR(s) 					{ RETVAL_STR(s); return; }
#define RETURN_INTERNED_STR(s)			{ RETVAL_INTERNED_STR(s); return; }
#define RETURN_NEW_STR(s)				{ RETVAL_NEW_STR(s); return; }
#define RETURN_STR_COPY(s)				{ RETVAL_STR_COPY(s); return; }
#define RETURN_STRING(s) 				{ RETVAL_STRING(s); return; }
#define RETURN_STRINGL(s, l) 			{ RETVAL_STRINGL(s, l); return; }
#define RETURN_EMPTY_STRING() 			{ RETVAL_EMPTY_STRING(); return; }
#define RETURN_RES(r) 					{ RETVAL_RES(r); return; }
#define RETURN_ARR(r) 					{ RETVAL_ARR(r); return; }
#define RETURN_OBJ(r) 					{ RETVAL_OBJ(r); return; }
#define RETURN_ZVAL(zv, copy, dtor)		{ RETVAL_ZVAL(zv, copy, dtor); return; }
#define RETURN_FALSE  					{ RETVAL_FALSE; return; }
#define RETURN_TRUE   					{ RETVAL_TRUE; return; }
```

### 函数宏定义

```c
/**在Zend/zend_API.h中**/
#define ZEND_FN(name) zif_##name
#define ZEND_MN(name) zim_##name
#define ZEND_NAMED_FUNCTION(name)		void name(INTERNAL_FUNCTION_PARAMETERS)
#define ZEND_FUNCTION(name)				ZEND_NAMED_FUNCTION(ZEND_FN(name))
#define ZEND_METHOD(classname, name)	ZEND_NAMED_FUNCTION(ZEND_MN(classname##_##name))

#define ZEND_FENTRY(zend_name, name, arg_info, flags)	{ #zend_name, name, arg_info, (uint32_t) (sizeof(arg_info)/sizeof(struct _zend_internal_arg_info)-1), flags },

#define ZEND_RAW_FENTRY(zend_name, name, arg_info, flags)   { zend_name, name, arg_info, (uint32_t) (sizeof(arg_info)/sizeof(struct _zend_internal_arg_info)-1), flags },
#define ZEND_RAW_NAMED_FE(zend_name, name, arg_info) ZEND_RAW_FENTRY(#zend_name, name, arg_info, 0)

#define ZEND_NAMED_FE(zend_name, name, arg_info)	ZEND_FENTRY(zend_name, name, arg_info, 0)
#define ZEND_FE(name, arg_info)						ZEND_FENTRY(name, ZEND_FN(name), arg_info, 0)
#define ZEND_DEP_FE(name, arg_info)                 ZEND_FENTRY(name, ZEND_FN(name), arg_info, ZEND_ACC_DEPRECATED)
#define ZEND_FALIAS(name, alias, arg_info)			ZEND_FENTRY(name, ZEND_FN(alias), arg_info, 0)
#define ZEND_DEP_FALIAS(name, alias, arg_info)		ZEND_FENTRY(name, ZEND_FN(alias), arg_info, ZEND_ACC_DEPRECATED)
#define ZEND_NAMED_ME(zend_name, name, arg_info, flags)	ZEND_FENTRY(zend_name, name, arg_info, flags)
#define ZEND_ME(classname, name, arg_info, flags)	ZEND_FENTRY(name, ZEND_MN(classname##_##name), arg_info, flags)
#define ZEND_ABSTRACT_ME(classname, name, arg_info)	ZEND_FENTRY(name, NULL, arg_info, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
#define ZEND_MALIAS(classname, name, alias, arg_info, flags) \
                                                    ZEND_FENTRY(name, ZEND_MN(classname##_##alias), arg_info, flags)
#define ZEND_ME_MAPPING(name, func_name, arg_types, flags) ZEND_NAMED_ME(name, ZEND_FN(func_name), arg_types, flags)

#define ZEND_NS_FENTRY(ns, zend_name, name, arg_info, flags)		ZEND_RAW_FENTRY(ZEND_NS_NAME(ns, #zend_name), name, arg_info, flags)

#define ZEND_NS_RAW_FENTRY(ns, zend_name, name, arg_info, flags)	ZEND_RAW_FENTRY(ZEND_NS_NAME(ns, zend_name), name, arg_info, flags)
#define ZEND_NS_RAW_NAMED_FE(ns, zend_name, name, arg_info)			ZEND_NS_RAW_FENTRY(ns, #zend_name, name, arg_info, 0)

#define ZEND_NS_NAMED_FE(ns, zend_name, name, arg_info)	ZEND_NS_FENTRY(ns, zend_name, name, arg_info, 0)
#define ZEND_NS_FE(ns, name, arg_info)					ZEND_NS_FENTRY(ns, name, ZEND_FN(name), arg_info, 0)
#define ZEND_NS_DEP_FE(ns, name, arg_info)				ZEND_NS_FENTRY(ns, name, ZEND_FN(name), arg_info, ZEND_ACC_DEPRECATED)
#define ZEND_NS_FALIAS(ns, name, alias, arg_info)		ZEND_NS_FENTRY(ns, name, ZEND_FN(alias), arg_info, 0)
#define ZEND_NS_DEP_FALIAS(ns, name, alias, arg_info)	ZEND_NS_FENTRY(ns, name, ZEND_FN(alias), arg_info, ZEND_ACC_DEPRECATED)

#define ZEND_FE_END            { NULL, NULL, NULL, 0, 0 }

#define ZEND_ARG_INFO(pass_by_ref, name)                             { #name, NULL, 0, pass_by_ref, 0, 0 },
#define ZEND_ARG_PASS_INFO(pass_by_ref)                              { NULL,  NULL, 0, pass_by_ref, 0, 0 },
#define ZEND_ARG_OBJ_INFO(pass_by_ref, name, classname, allow_null)  { #name, #classname, IS_OBJECT, pass_by_ref, allow_null, 0 },
#define ZEND_ARG_ARRAY_INFO(pass_by_ref, name, allow_null)           { #name, NULL, IS_ARRAY, pass_by_ref, allow_null, 0 },
#define ZEND_ARG_CALLABLE_INFO(pass_by_ref, name, allow_null)        { #name, NULL, IS_CALLABLE, pass_by_ref, allow_null, 0 },
#define ZEND_ARG_TYPE_INFO(pass_by_ref, name, type_hint, allow_null) { #name, NULL, type_hint, pass_by_ref, allow_null, 0 },
#define ZEND_ARG_VARIADIC_INFO(pass_by_ref, name)                    { #name, NULL, 0, pass_by_ref, 0, 1 },
```

