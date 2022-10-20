<center><h1 style="font-size: 40px;">项目申请书</h></center>

<center><p style="font-size: 20px;">项目名称 : Pixiu 流量分发模式</p></center>

<center><p style="font-size: 15px;">标签：Distributed System,Cloud Native,Micro Service</p></center>

<center><p style="font-size: 15px;">产出要求：提供浏览分发的 Filter对接 pixiu admin，动态根据不同比率进行流量分发
支持多协议超时返回机制</p></center>

<center><p style="font-size: 15px;">项目主导师：王虓雄</p></center>

<center><p style="font-size: 15px;">申请人：龚娜</p></center>

<center><p style="font-size: 15px;">github: https://github.com/gongna-au</p></center>

****

## 1.项目背景

Pixiu 是一款开源的 Dubbo 生态的 API 网关和 接入 dubbo 集群的语言解决方案。作为 API 网关形态， Pixiu 能接收外界的网络请求，将其转换为 dubbo 等协议请求，转发给背后集群；作为 Sidecar，Pixiu 期望可以代替代理服务注册到 Dubbo 集群，让多语言服务接入 Dubbo 集群提供更快捷的解决方案。Pixiu 网关多一个主要能力是提供流量管理能力，本题目需要学生继续完善流量管理能力，支持多协议超时设置，超时优雅返回能力，提供流量分发的能力，尝试基于此来构建金丝雀测试、蓝绿发布、故障注入等服务运维能力。

## 2.项目基本需求

- 提供浏览分发的 Filter

- 对接 pixiu admin，动态根据不同比率进行流量分发
- 支持多协议超时返回机制



## 3.需求实现

### 1.提供浏览分发的 Filter对接 pixiu admin

##### Go实现filter的基本思路：

**就是把功能性（业务代码）与非功能性（非业务代码）分离，保证对业务代码无侵入，同时提高代码复用性。**

<img src="/home/gongna/桌面/D1.png" style="zoom:150%;" />

通过go代码可以实现以下功能来实现负载均衡的同时对接对接 pixiu admin。



###### 步骤1：自定义Context

重新定义一个Context的结构体，其中组合了标准库中的Context，具备标准库Context的能力，Context是作为数据载体在各个过滤器之间传递，没有用标准库的Context，采用自定义的Context主要是为了可以根据需要扩展Context，通过扩展Context添加任何我们需要的参数，同时可以把过滤器处理的结果存入这个Context中，再传递到下一个过滤器。



###### 步骤2： FilterFuncChain

过滤函数都有相同入参和返回值，定义为一个变量FilterFunc ，抽象过滤函数为为`FilterFunc`，编写方法注册更多的filter到`FilterFuncChain []FilterFunc`。

```
type CombinedFunc struct {
	CF    FilterFuncChain
	MyCtx *MyContext
}
```

也可以通过迭代实现：将本层`filter`包裹后重新传递到下一层，这样就可以将之前包裹后`filter`沿用到下一轮迭代，基于上一轮`filter`继续包裹剩余的`filter`在最里层放我们的业务逻辑.



###### 步骤3：CombinedFunc

```
type CombinedFunc struct {
	CF    FilterFuncChain
	MyCtx *MyContext
}
```

**通过以上步骤可以结合Pixiu特性实现基于 pixiu特性的浏览分发Filter**，并根据Pixiu特性进行以下功能的扩展。

- 灰度发布 (项目发布后的流量接入控制)
- 流量控制 (按照规则设置不同服务不同流量分发)
- 摘机操作 (服务器迁移，故障转移等将相应服务器剔除，不接受流量)
- 黑白名单 (按照规则限制ip访问或允许ip访问，提高服务安全性)



### 2.流量管理及分发

##### 流量控制和分发的逻辑：

业务把多个后端模块提供的 API 暴露供客户端调用，通过配置网关路由规则，实现将**相应的请求路径流量** 路由至 **相应的服务**。

###### 步骤1：设计了流量管理 API

设计流量管理 API，主要通过 Gateway，VirtualService，DestinationRule 这几个实现。

- **Gateway**：配置**监听规则**。包括端口、协议、host、SSL 等。
- **VirtualService**：配置**路由规则**。包括匹配条件、流量行为、路由目的服务/版本等。
- **DestinationRule**：配置**服务版本**及**负载均衡**、**连接池**、**健康检查策略**。

<img src="/home/gongna/桌面/d3.jpeg" style="zoom:150%;" />

###### 步骤2：提供API暴露供客户端调用

###### 步骤3：负载均衡策略

同一后端服务一般由多个实例（Pod）承载，通常需要将入口流量在多个后端实例负载均衡，实现负载均衡最小连接数等负载均衡算法，保持多个后端实例均衡处理流量。在一些特定情况下，需要将来自同一用户的请求路由到相同后端实例，保证某些需要会话保持的服务能够正常工作。

1. 基于 IP 的简单会话保持：来自同一 IP 地址的请求判定为同一用户，路由至相同后端服务实例。实现简单、方便，但无法支撑多个客户端使用代理访问后端服务的场景，此时同一 IP 地址不代表同一用户。
2. 基于 cookie（或其他 7 层信息）的会话保持：用户第一次请求时，边缘网关为其插入 cookie 并返回，后续客户端使用此 cookie 访问，边缘网关根据 cookie 将流量负载至后端服务实例。

实现基于 IP、cookie、HTTP header 的会话保持服务。

###### 步骤4：容错

连接池是保持服务化应用稳定的重要配置。当系统中其中一个服务因请求数暴增而有故障风险时，快速返回失败信息尽快将压力施加给下游服务能有效避免整个系统发生雪崩。我们可通过连接池为有需要的服务配置 TCP/HTTP 的连接数/请求数阈值，达到阈值后拒绝处理新增流量返回错误信息，能有效保护服务运行的稳定性。

###### 步骤5：健康检查

当服务实例（Pod）在处理流量过程中发生故障时（连续返回错误，成功率降低到阈值之下等） Gateway 可以配置将故障的 endpoints 从健康负载均衡池中剔除的策略，保证客户端调用可以由状态正常的后端服务实例处理。当流量出现了类似连续 5xx 错误（HTTP）、连接超时/失败（TCP）等行为时，将其识别为离群值从负载均衡池中剔除一段时间。

###### 步骤6：重定向

当应用被迁移到新的 URI，同时又需要保持原有链接可用，配置 HTTP 重定向。

###### 步骤7：高可用调度

策略一实现：当健康度高于阈值时，流量 100% 在本地路由，低于阈值时，视健康度自动 failover 一定比例流量至其他可用区/地域，直至 endpoint 全部不健康时 100% 流量自动 failover 至其他可用区/地域。

策略二实现：不按照地域与错误信息自动 failover 流量，自定义配置跨可用区/地域多集群流量分发策略。

### 3.多协议超时返回

`timeout`都是代码层面对各个函数设置的处理时间。比如，读取客户端读取请求头、读取响应体的时间，本质上都是响应函数的超时时间。

###### SetDeadline实现

根据查阅资料，了解到Go暴露出来的，用于实现`timeout`的方法有Deadline 。`timeout`本身通过 net.Conn包中的`Set[Read|Write]Deadline(time.Time)`方法来控制。`Deadline`是一个绝对的时间点，当连接的I/O操作超过这个时间点而没有完成时，便会因为超时失败。`Deadlines`不同于`timeout`的是：对一个连接而言，设置Deadline之后，除非重新调SetDeadline，否则这个Deadline不会变化。Deadline是一个绝对的时间点。因此，如果要通SetDeadline来实现timeout，就得通过每次执Read/Write前重新调用它来实现。

###### Server Timeouts

在创建`http.Server`的时候，可以通过`ReadTimeout`和`WriteTimeout`来设置超时。如果是`HTTPS`的话，`SetWriteDeadline`方法在`Accept`后就被调用，所以`TLS handshake`也是`WriteTimeout`的一部分。同时，这也意味着（仅仅`HTTPS`）`WriteTimeout`包括了读`header`头以及握手的时间。为了避免不信任的`client`端或者网络连接的影响，同时设置这两个值，来保证连接不被`client`长时间占用。

###### Client Timeouts

- 可以通过使用`http.Client`指定`timeout`
  - `net.Dialer.Timeout`用于限制建立`TCP`连接的时间，包括域名解析的时间在内（如果需要创建的话）
  - `http.Transport.TLSHandshakeTimeout`用于限制`TLS`握手的时间
  - `http.Transport.ResponseHeaderTimeout`用于限制读取响应头的时间（不包括读取`response body`的时间）
  - `http.Transport.ExpectContinueTimeout`

###### Cancel and Context

`net/http` 提供了两种取消客户端请求的方法：

-  通过`Request.Cancel`实现

  `Request.Cancel`是一个可选的`channel`，如果设置了它，便可以通过关闭该`channel`来终止请求,就跟请求超时了一样。也可以可结合`Request.Cancel`和`time.Timer`对`timeout`进行更细的控制。比如，在我们每次从`response body`中读取数据后，延长`timeout`的时间。或者通过

- 通过在`1.7`版本中引入的`Context`实现

  使用`context`来取消一个请求，获取一个`Context`类型，以及调用`context.WithCancel`返回的`cancel()`方法，并通过`Request.WithContext`将`context`绑定到一个请求上。当我们想取消这个请求时，只需要调用`cancel()`方法(代替上述关闭`channel`的做法)。

  

## 4.项目研发流程

#### 第一阶段：（07 月 01 日 - 08 月 15 日） ：

- **阅读Pixiu 源码，分析Pixiu 特性，完成大致的项目框架构建。**
- **与导师沟通主要完成**：
  - **提供浏览分发的 Filter对接 pixiu admin模块。**
  - **流量管理及分发模块的大致逻辑框架模块的构建。**

#### 第二阶段：（08 月 16 日 - 09 月 30 日） ：

- **完善浏览分发的 Filter和流量管理模块。**
- **完成多协议超时返回功能模块。**
- **最终代码测试以及优化。**

## 5.期望

**自2021-Summer参加了Apache Dubbo-go社区的Dubbo-go 增加命令行生成 Demo 的工具项目，不仅在社区学到了很多东西，同时也对Pixiu 产生了极大的兴趣，真的非常非常渴望加入Pixiu ，学习相关领域的信息，并为社区作出一份贡献。**







