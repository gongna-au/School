# `Dubbo-go`源码分析

### 关键源码[ ](https://dubbo.apache.org/zh/blog/2021/01/14/dubbo-go-源码笔记一server-端开启服务过程/#2关键源码)

源码放置在 `app/` 文件夹下，主要包含 `server.go` 和 `user.go` 两个文件，顾名思义，`server.go` 用于使用框架开启服务以及注册传输协议；`user.go` 则定义了 `rpc-service` 结构体，以及传输协议的结构

```
func init() {
    config.SetProviderService(new(UserProvider))
    // ------for hessian2------
    hessian.RegisterPOJO(&User{})
}
type User struct {
    Id   string
    Name string
    Age  int32
    Time time.Time
}
type UserProvider struct {
}
func (u *UserProvider) GetUser(ctx context.Context, req []interface{}) (*User, error) {
```

可以看到，`user.go` 中存在`init`函数，是服务端代码中最先被执行的部分。`User` 为用户自定义的传输结构体，`UserProvider` 为用户自定义的 `rpc_service`

包含一个 `rpc` 函数，`GetUser`。当然，用户可以自定义其他的 `rpc` 功能函数。在 `init` 函数中，调用 `config` 的 `SetProviderService` 函数，将当前 `rpc_service` 注册在框架 `config` 上

**可以查看 `dubbo` 官方文档提供的设计图：**

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p2.png)

`rpc-service` 注册完毕之后，调用 `hessian` 接口注册传输结构体 User。

至此，`init` 函数执行完毕。

- `server.go`

  ```
  // they are necessary:
  //      export CONF_PROVIDER_FILE_PATH="xxx"
  //      export APP_LOG_CONF_FILE="xxx"
  func main() {
      hessian.RegisterPOJO(&User{})
      config.Load()
      initSignal()
  }
  func initSignal() {
      signals := make(chan os.Signal, 1)
      ...
  ```

  之后执行 main 函数。

  main 函数中只进行了两个操作，首先使用 `hessian` 注册组件将 User 结构体注册（与之前略有重复），从而可以在接下来使用 `getty` 打解包。

之后调用 `config.Load` 函数，该函数位于框架 `config/config_loader.go` 内，这个函数是整个框架服务的启动点，**下面会详细讲这个函数内重要的配置处理过程**。执行完 Load() 函数之后，配置文件会读入框架，之后根据配置文件的内容，将注册的 service 实现到配置结构里,再调用 Export 暴露给特定的 registry，进而开启特定的 service 进行对应端口的 `tcp` 监听，成功启动并且暴露服务。

最终开启信号监听 `initSignal()` 优雅地结束一个服务的启动过程。

###  客户端源码[ ](https://dubbo.apache.org/zh/blog/2021/01/14/dubbo-go-源码笔记一server-端开启服务过程/#4-客户端源码)

客户端包含 `client.go` 和 `user.go` (定义了传输协议的结构{`server.go`使用框架开启服务，并且注册传输协议。})两个文件，其中 `user.go` 与服务端完全一致，不再赘述。

```
func main() {
    hessian.RegisterPOJO(&User{})
    config.Load()
    time.Sleep(3e9)
    println("\n\n\nstart to test dubbo")
    user := &User{}
    err := userProvider.GetUser(context.TODO(), []interface{}{"A001"}, user)
    if err != nil {
  panic(err)
    }
    println("response result: %v\n", user)
    initSignal()
}
```

main 函数和服务端也类似，首先将传输结构注册到 `hessian 上`，再调用 `config.Load()` 函数。在下文会介绍，客户端和服务端会根据配置类型执行 `config.Load()` 中特定的函数 `loadConsumerConfig()` 和 `loadProviderConfig()`，从而达到“开启服务”、“调用服务”的目的。

- 客户端和服务端都通过1.先把传输的结构体注册在`hessian` ，通过调用 `config.Load()` 函数，`config.Load()` 函数通过配置类型分别去执行`config.Load()` 中特定的函数，实现开启了服务，调用服务的目的。
- 那加载完配置后是怎么做的？还是通过实现服务，增加增加函数 proxy、申请 registry 和 `reloadInvoker` 指向服务端 `ip` 等操作，重写了客户端实例 `userProvider` 的对应函数，在通过调用`GetUser` 函数，可以直接通过 invoker，调用到已经开启的服务端，实现 `rpc` 过程。

### **server 端角度--服务启动、registry 注册和调用过程：**



### 自定义配置文件（非环境变量）方法[ ](https://dubbo.apache.org/zh/blog/2021/01/14/dubbo-go-源码笔记一server-端开启服务过程/#5-自定义配置文件非环境变量方法)

#### 1）服务端自定义配置文件

- var `providerConfigStr` = `xxxxx`// 配置文件内容，可以参考 log 和 client。在这里你可以定义配置文件的获取方式，比如配置中心，本地文件读取。

- 在 `config.Load()` 之前设置配置，例如：

- ```
  func main() {
      hessian.RegisterPOJO(&User{})
      providerConfig := config.ProviderConfig{}
      yaml.Unmarshal([]byte(providerConfigStr), &providerConfig)
      config.SetProviderConfig(providerConfig)
      defaultServerConfig := dubbo.GetDefaultServerConfig()
      dubbo.SetServerConfig(defaultServerConfig)
      logger.SetLoggerLevel("warn") // info,warn
      config.Load()
      select {
      }
  }
  ```

  

#### 2）客户端自定义配置文件

- var consumerConfigStr = `xxxxx`// 配置文件内容，可以参考 log 和 clien。在这里你可以定义配置文件的获取方式，比如配置中心，本地文件读取。

- 在 `config.Load()` 之前设置配置，例如：

- ```
  func main() {
       p := config.ConsumerConfig{}
       yaml.Unmarshal([]byte(consumerConfigStr), &p)
       config.SetConsumerConfig(p)
       defaultClientConfig := dubbo.GetDefaultClientConfig()
       dubbo.SetClientConf(defaultClientConfig)
       logger.SetLoggerLevel("warn") // info,warn
       config.Load()
  
       user := &User{}
       err := userProvider.GetUser(context.TODO(), []interface{}{"A001"}, user)
       if err != nil {
           log.Print(err)
           return
       }
    log.Print(user)
  }
  ```

  

## Server 端[ ](https://dubbo.apache.org/zh/blog/2021/01/14/dubbo-go-源码笔记一server-端开启服务过程/#server-端)

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p3.png)

> 服务暴露过程涉及到多次原始 `rpcService` 的封装、暴露，网上其他文章的图感觉太过笼统，在此，简要地绘制了一个用户定义服务的数据流图

### 1. 加载配置[ ](https://dubbo.apache.org/zh/blog/2021/01/14/dubbo-go-源码笔记一server-端开启服务过程/#1-加载配置)

#### 1）框架初始化

> 在加载配置之前，框架提供了很多已定义好的协议、工厂等组件，都会在对应模块 `init` 函数内注册到 extension 模块上，以供接下来配置文件中进行选用。

其中重要的有：

- **默认函数代理工厂**：`common/proxy/proxy_factory/default.go`

```
func init() {
    extension.SetProxyFactory("default", NewDefaultProxyFactory)
}
```

它的作用是将原始 `rpc-service` 进行封装，形成 `proxy_invoker`，更易于实现远程 call 调用，详情可见其 invoke 函数。

- **注册中心注册协议**： `registry/protocol/protocol.go`

```
func init() {
    extension.SetProtocol("registry", GetProtocol)
}
```

它负责将 invoker 暴露给对应注册中心，比如 `zk` 注册中心。

- **`zookeeper` 注册协议**：`registry/zookeeper/zookeeper.go`

```
func init() {
    extension.SetRegistry("zookeeper", newZkRegistry)
}
```

它合并了 base_`resiger`，负责在服务暴露过程中，将服务注册在 `zookeeper` 注册器上，从而为调用者提供调用方法。

-  **`dubbo` 传输协议**：`protocol/dubbo/dubbo.go`

```
func init() {
    extension.SetProtocol(DUBBO, GetProtocol)
}
```

它负责监听对应端口，将具体的服务暴露，并启动对应的事件 handler，将远程调用的 event 事件传递到 invoker 内部，调用本地 invoker 并获得执行结果返回。

- **filter 包装调用链协议**：`protocol/protocolwrapper/protocol_filter_wrapper.go`

```
func init() {
    extension.SetProtocol(FILTER, GetProtocol)
}
```

它负责在服务暴露过程中，将代理 invoker 打包，通过配置好的 filter 形成调用链，并交付给 `dubbo` 协议进行暴露。

上述提前注册好的框架已实现的组件，在整个服务暴露调用链中都会用到，会根据配置取其所需。

#### 2）配置文件[ ](https://dubbo.apache.org/zh/blog/2021/01/14/dubbo-go-源码笔记一server-端开启服务过程/#2配置文件)

服务端需要的重要配置有三个字段：services、protocols、registries。

`profiles/dev/server.yml:`

```
registries :
  "demoZk":
    protocol: "zookeeper"
    timeout    : "3s"
    address: "127.0.0.1:2181"
services:
  "UserProvider":
    # 可以指定多个registry，使用逗号隔开;不指定默认向所有注册中心注册
    registry: "demoZk"
    protocol : "dubbo"
    # 相当于dubbo.xml中的interface
    interface : "com.ikurento.user.UserProvider"
    loadbalance: "random"
    warmup: "100"
    cluster: "failover"
    methods:
    - name: "GetUser"
      retries: 1
      loadbalance: "random"
protocols:
  "dubbo":
    name: "dubbo"
    port: 20000
```



其中 service 指定了要暴露的 `rpc-service` 名（`“UserProvider`）*传输数据时的结构体的名字*、暴露的协议名（“`dubbo`”）*（服务端传输数据需要遵守的规则的名字）*、`注册的协议名(“demoZk”)`、 *（向注册中心注册的协议的名字=与注册中心达成的规则的名字）* 暴露的服务所处的 interface、负载均衡策略、集群失败策略及调用的方法等等。

其中，服务的协议名需要和 registries 下的 `mapkey` 对应，（服务遵守的协议的名字和与注册中心达成的规则名相同，就是注册中心的`mapkey` ==服务与注册中心达成的规则，使所以你服务应该遵守，服务的`registry: "demoZk"`与注册中心的`"demoZk":`一致。）暴露的协议名需要和 protocols 下的 `mapkey` 对应。（也就是服务本身遵守的协议[就是服务暴露的协议/或者说是与客户端达成的规则]与规则，要和协议的的`mapkey` 对应。）

```
protocols:
  "dubbo":
    name: "dubbo"
    port: 20000
```

可以看到上述例子中，使用了 `dubbo` 作为暴露协议，使用了 `zookeeper` 作为中间注册协议，并且给定了端口。如果 `zk` 需要设置用户名和密码，也可以在配置中写好。

#### 3）配置文件的读入和检查

> `config/config_loader.go:: Load()`

```
在上述 example 的 main 函数中，有 config.Load() 函数的直接调用，该函数执行细节如下：

// Load Dubbo Init
func Load() {
    // init router
    initRouter()
    // init the global event dispatcher
    extension.SetAndInitGlobalDispatcher(GetBaseConfig().EventDispatcherType)
    // start the metadata report if config set
    if err := startMetadataReport(GetApplicationConfig().MetadataType, GetBaseConfig().MetadataReportConfig); err != nil {
  logger.Errorf("Provider starts metadata report error, and the error is {%#v}", err)
  return
    }
    // reference config
    loadConsumerConfig()
    // service config
    loadProviderConfig()
    // init the shutdown callback
    GracefulShutdownInit()
}
```

我们重点关心 `loadConsumerConfig() 和` （加载客户端配置的函数）`loadProviderConfig()`（加载服务端配置的函数）两个函数。

对于 provider 端，可以看到 `loadProviderConfig()` 函数代码如下：



![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p4.png)

前半部分是配置的读入和检查，进入 for 循环后，是单个 service 的暴露起始点。

前面提到，在配置文件中已经写好了要暴露的 service 的种种信息，比如服务名、interface 名、method 名等等。在图中 for 循环内，会将所有 service 的服务依次实现。

for 循环的第一行，根据 key 调用 `GetProviderService` 函数，拿到注册的 `rpcService` 实例，这里对应上述提到的 `init` 函数中，用户手动注册的自己实现的 `rpc-service` 实例：![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p5.png)

这个对象也就成为了 for 循环中的 `rpcService` 变量，将这个对象注册通过 Implement 函数写到 sys（`ServiceConfig` 类型）上，设置好 sys 的 key 和协议组，最终调用了 sys 的 Export 方法。![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p6.png)

至此，框架配置结构体已经拿到了所有 service 有关的配置，以及用户定义好的 `rpc-service` 实例，它触发了 Export 方法，旨在将自己的实例暴露出去。这是 Export 调用链的起始点。

### 2. 原始 service 封装入 proxy_invoker

> `config/service_config.go :: Export()`

**接下来进入 `ServiceConfig.Export()` 函数.**

这个函数进行了一些细碎的操作，比如为不同的协议分配随机端口，如果指定了多个中心注册协议，则会将服务通过多个中心注册协议的 `registryProtocol` 暴露出去，我们只关心对于一个注册协议是如何操作的。还有一些操作比如生成调用 `url` 和注册 `url`，用于为暴露做准备。（简言之就是如何把服务的URL（包含参数等等一系列数据）传递给注册中心，以及自己怎么生成URL。）

#### 1）首先通过配置生成对应 `registryUrl` 和 `serviceUrl`![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p7.png)

`registryUrl` 是用来向中心注册组件发起注册请求的，对于 `zookeeper` 的话，会传入其 `ip` 和端口号，以及附加的用户名密码等信息。

这个 `regUrl` 目前只存有注册（`zk`）相关信息，后续会补写入 `ServiceIvk，`即服务调用相关信息，里面包含了方法名，参数等…

#### 2）对于一个注册协议，将传入的 `rpc-service` 实例注册在 `common.ServiceMap![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p8.png)`

这个 Register 函数将服务实例注册了两次，一次是以 Interface 为 key 写入接口服务组内，一次是以 interface 和 `proto` 为 key 写入特定的一个唯一的服务。

后续会从 `common.Map` 里面取出来这个实例。

#### 3）获取默认代理工厂，将实例封装入代理 invoker[ ](https://dubbo.apache.org/zh/blog/2021/01/14/dubbo-go-源码笔记一server-端开启服务过程/#3获取默认代理工厂将实例封装入代理-invoker)

```
// 拿到一个proxyInvoker，这个invoker的url是传入的regUrl，这个地方将上面注册的service实例封装成了invoker
// 这个GetProxyFactory返回的默认是common/proxy/proxy_factory/default.go
// 这个默认工厂调用GetInvoker获得默认的proxyInvoker，保存了当前注册url
invoker := extension.GetProxyFactory(providerConfig.ProxyFactory).GetInvoker(*regUrl)
// 暴露出来 生成exporter,开启tcp监听
// 这里就该跳到registry/protocol/protocol.go registryProtocol 调用的Export，将当前proxyInvoker导出
exporter = c.cacheProtocol.Export(invoker)

```

这一步的 `GetProxyFactory`(“default”) 方法获取默认代理工厂，通过传入上述构造的 `regUrl，`将 `url` 封装入代理 invoker。

可以进入 到这里，上面 GetInvoker(*regUrl) 返回的 invoker 即为 proxy_invoker，它封装好了用户定义的 rpc_service，并将具体的调用逻辑封装入了 Invoke 函数内。`common/proxy/proxy_factory/default.go::ProxyInvoker.Invoke()` 函数里，看到对于 `common.Map` 取用为 `svc` 的部分，以及关于 `svc` 对应 Method 的实际调用 Call 的函数如下：![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p9.png)

到这里，上面 `GetInvoker(*regUrl)` 返回的 invoker 即为 proxy_invoker，它封装好了用户定义的 `rpc_service`，并将具体的调用逻辑封装入了 Invoke 函数内。

为什么使用 Proxy_invoker 来调用？

通过这个 proxy_invoke 调用用户的功能函数，调用方式将更加抽象化，可以在代码中看到，通过 ins 和 outs 来定义入参和出参，将整个调用逻辑抽象化为 invocation 结构体，而将具体的函数名的选择、参数向下传递和 reflect 反射过程封装在 invoke 函数内，这样的设计更有利于之后远程调用。个人认为这是 `dubbo Invoke` 调用链的设计思想。

至此，实现了图中对应的部分：

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p10.png)

### 3. registry 协议在 `zkRegistry` 上暴露上面的 proxy_invoker

上面，我们执行到了 exporter = `c.cacheProtocol.Export`(invoker)。

这里的 `cacheProtocol` 为一层缓存设计，对应到原始的 demo 上，这里是默认实现好的 `registryProtocol。`

> `registry/protocol/protocol.go:: Export()`

这个函数内构造了多个 `EventListener`，非常有 `java` 的设计感。

我们只关心服务暴露的过程，先忽略这些监听器。

#### 1）获取注册 `url` 和服务 `url`![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p11.png)![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p12.png)

一层缓存操作，如果 cache 没有需要从 common 里面重新拿 `zkRegistry。`

#### 3）`zkRegistry` 调用 Registry 方法，在 `zookeeper` 上注册 `dubboPath`

该结构体组合了 registry.BaseRegistry 结构，base 结构定义了注册器基础的功能函数，比如 Registry、Subscribe 等，但在这些默认定义的函数内部，还是会调用 facade 层（zkRegistry 层）的具体实现函数，这一设计模型能在保证已有功能函数不需要重复定义的同时，引入外层函数的实现，类似于结构体继承却又复用了代码。这一设计模式值得学习。

我们查看上述 `registry/protocol/protocol.go:: Export()` 函数，直接调用了:

```
// 1. 通过zk注册器，调用Register()函数，将已有@root@rawurl注册到zk上
    err := reg.Register(*registeredProviderUrl)
```

将已有 RegistryUrl 注册到了 zkRegistry 上。

这一步调用了 baseRegistry 的 Register 函数，进而调用 zkRegister 的 DoRegister 函数，进而调用：

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p14.png)

在这个函数里，将对应 root 创造一个新的节点。

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p15.png)

并且写入具体 node 信息，node 为 url 经过 encode 的结果，**包含了服务端的调用方式。**

这部分的代码较为复杂，具体可以看 baseRegistry 的 `processURL()` 函数：http://t.tb.cn/6Xje4bijnsIDNaSmyPc4Ot。

至此，将服务端调用 `url` 注册到了 `zookeeper` 上，而客户端如果想获取到这个 `url`，只需要传入特定的 `dubboPath`，向 `zk` 请求即可。目前 client 是可以获取到访问方式了，但服务端的特定服务还没有启动，还没有开启特定协议端口的监听，这也是 `registry/protocol/protocol.go:: Export()` 函数接下来要做的事情。

#### 4）proxy_invoker 封装入 wrapped_invoker，得到 filter 调用链

```
    // invoker封装入warppedInvoker
    wrappedInvoker := newWrappedInvoker(invoker, providerUrl)
    // 经过为invoker增加filter调用链，再使用dubbo协议Export，开启service并且返回了Exporter 。
    // export_1
    cachedExporter = extension.GetProtocol(protocolwrapper.FILTER).Export(wrappedInvoker)
```



**新建一个 `WrappedInvoker`，用于之后链式调用。**

拿到提前实现并注册好的 `ProtocolFilterWrapper`，调用 Export 方法，进一步暴露。

> `protocol/protocolwrapped/protocol_filter_wrapper.go:Export()`

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p16.png)

> `protocol/protocolwrapped/protocol_filter_wrapper.go:buildInvokerChain`

<img src="https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p17.png" alt="img" style="zoom:200%;" />

可见，根据配置的内容，通过链式调用的构造，将 proxy_invoker 层层包裹在调用链的最底部，最终返回一个调用链 invoker。

对应图中部分：

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p18.png)

至此，我们已经拿到 filter 调用链，期待将这个 chain 暴露到特定端口，用于相应请求事件。

#### 5）通过 dubbo 协议暴露 wrapped_invoker

> protocol/protocolwrapped/protocol_filter_wrapper.go:Export()

```go
// 通过dubbo协议Export  dubbo_protocol调用的 export_2
    return pfw.protocol.Export(invoker)
```

回到上述 Export 函数的最后一行，调用了 dubboProtocol 的 Export 方法，将上述 chain 真正暴露。

该 Export 方法的具体实现在：protocol/dubbo/dubbo_protocol.go: Export()。

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p19.png)

这一函数做了两个事情：构造触发器、启动服务。

- 将传入的 Invoker 调用 chain 进一步封装，封装成一个 exporter，再将这个 export 放入 map 保存。**注意！这里把 exporter 放入了 SetExporterMap中，在下面服务启动的时候，会以注册事件监听器的形式将这个 exporter 取出！**
- 调用 dubboProtocol 的 openServer 方法，开启一个针对特定端口的监听。

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p20.png)

如上图所示，一个 Session 被传入，开启对应端口的事件监听。

至此构造出了 exporter，完成图中部分：

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p21.png)

### 4. 注册触发动作[ ](https://dubbo.apache.org/zh/blog/2021/01/14/dubbo-go-源码笔记一server-端开启服务过程/#4-注册触发动作)

上述只是启动了服务，但还没有看到触发事件的细节，点进上面的 s.newSession 可以看到，dubbo 协议为一个 getty 的 session 默认使用了如下配置：

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p22.png)

其中很重要的一个配置是 EventListener，传入的是 dubboServer 的默认 rpcHandler。

> protocol/dubbo/listener.go:OnMessage()

`rpcHandler 有一个实现好的 OnMessage 函数，根据 getty 的 API，当 client 调用该端口时，会触发 OnMessage。`

```go
// OnMessage notified when RPC server session got any message in connection
func (h *RpcServerHandler) OnMessage(session getty.Session, pkg interface{}) {
```

这一函数实现了在 `getty session` 接收到 `rpc` 调用后的一系列处理：

- 传入包的解析

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p23.png)

- 根据请求包构造请求 url

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p24.png)

- 拿到对应请求 key，找到要被调用的 exporter

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p25.png)

- 拿到对应的 Invoker

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p26.png)

- 构造 invocation

- 构造 invocation

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p27.png)

- 调用

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p28.png)

- 返回

![img](https://dubbo.apache.org/imgs/blog/dubbo-go/code1/p29.png)

整个被调过程一气呵成。实现了从 getty.Session 的调用事件，到经过层层封装的 invoker 的调用。

至此，一次 `rpc` 调用得以正确返回。