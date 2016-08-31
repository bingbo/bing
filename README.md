# bing
this is a demo about php extension development

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
