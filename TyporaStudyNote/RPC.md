# RPC

## 1.关于`RPC`

`RPC`是**远程过程调用**的简称，是分布式系统中不同节点间流行的通信方式。那什么是**远程过程调用**呢？

**简单的来说，就是两台服务器A和B，一个应用部署在A服务器上，但是却想调用B服务器上应用提供的方法。**不在一个内存空间，不能直接调用，需要**通过网络来表达调用的语义和传达调用的数据**

```
//举个栗子
我们定义了这么一个方法
func getUserByName(fullname string ){

}
```

- **首先需要解决的问题是——通讯问题**，通过在客户端和服务端建立TCP连接，需要的数据都在这个连接里面传输。这种连接可以是按照我们的需求进行的连接，当我们需要时，就连接，我们不需要时，就断开连接。也可以是长连接，多个远程的调用共享一个连接。
- **其次需要解决的是——寻址的问题**， 也就是A服务器上的应用怎么告诉底层的`RPC`框架，如何连接到B服务器（主机或IP地址）以及特定的端口，还有调用的方法名是什么？这样才能完成调用。
- **将参数系列化**，A服务器上的应用发起远程过程调用时，方法需要的参数需要通过底层的网络协议如TCP传到B服务器。网络协议是基于二进制的，所以要把参数的值序列化为二进制的形式。通过寻址和传输发送给B服务器。

- **将参数反序列化** ，B服务器收到请求时将参数反序列化，恢复为内存中的表达方式，然后找到对应的方法，进行本地调用。

## 2.为什么要RPC呢？

因为无法在同一个进程中，就是在一台计算机内部通过本地调用的方式完成的需求，比如不同系统间的通讯。需要在多台计算机上部署应用。

*有个问题？那么RPC和Api调用又有什么区别呢？*

> 从使用上来看，HTTP 接口只关注服务提供方，对于客户端怎么调用并不关心。接口只要保证有客户端调用时，返回对应的数据就行了。而RPC则要求客户端接口保持和服务端的一致。
>
> API ——客户端并不知道具体方法。客户端只想获取资源，所以发起HTTP请求，而服务端接收到请求后根据URI经过一系列的路由才定位到方法上面去
>
> RPC是服务端提供好方法给客户端调用，客户端需要知道服务端的具体类，具体方法，然后像调用本地方法一样直接调用它。
> REST 是 基于 HTTP 协议
>
>  RPC 可以基于 TCP/UDP，也可以基于 HTTP 协议进行传输的。
>
> RPC 和 REST 两者的定位不同，REST 面向资源，更注重接口的规范，因为要保证通用性更强，所以对外最好通过 REST。而 RPC 面向方法，主要用于函数方法的调用，可以适合更复杂通信需求的场景。RESTful API客户端与服务端之间采用的是同步机制，当发送HTTP请求时，客户端需要等待服务端的响应。当然对于这一点是可以通过一些技术来实现异步的机制的。采用RESTful API，客户端与服务端之间虽然可以独立开发，但还是存在耦合。比如，客户端在发送请求的时，必须知道服务器的地址，且必须保证服务器正常工作。而 rpc + ralbbimq中间件（RabbitMQ是一个开源的消息代理和队列服务器）可以实现低耦合的分布式集群架构。
>
> https://segmentfault.com/a/1190000021036376
>
> 如果感兴趣可以看看上面这个文章

![attachments-2021-02-o0G9ZrBM601e36a0dfecc.jpg](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/140ce4ae3c6747a5938992bc38f00dae~tplv-k3u1fbpfcp-zoom-in-crop-mark:1304:0:0:0.awebp)

一个最简单的 `RPC` 服务，只需要 Client、Server 和 Network，利用消息中间件 `RabbitMQ` 作为 Network 载体传输信息，实现简单的 `RPC` 服务。简单原理可如下图所示：

![attachments-2021-02-rvci9qL6601e36a7da0e5.jpg](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/705bed66febf4ec39a409355c7da697e~tplv-k3u1fbpfcp-zoom-in-crop-mark:1304:0:0:0.awebp)



## 3.RPC版"Hello, World"的实现

```
type HelloService struct {}

func (p *HelloService) Hello(request string, reply *string) error {
    *reply = "hello:" + request
    return nil
}
```

- **这个Hello方法必须满足go语言 的两个RPC规则：**
  - **方法必须只有两个*可序列化的参数*** 
  - **第二个参数必须是指针**
  - **必须返回error类型**
  - **必须是公开的方法**

```
func main(){
	rpc.RegisterName("HelloService",new(HelloService))
	listener,err := net.Listen("tcp",":1234")
	if err != nil{
		log.Fatal("ListenTCP error:",err)
	}
	conn,err := listener.Accept()
	if err != nil{
		log.Fatal("Accept error:",err)
	}
	rpc.ServeConn(conn)
	
}
```

- **其中`rpc.Register`函数调用会将对象类型中所有满足`RPC`规则的对象方法注册为`RPC`函数**

  将`HelloService`类型下符合`RPC`规则的方法注册为`RPC`函数。

- **然后建立唯一的`RPC`连接**

  ```
  listener,err := net.Listen("tcp",":1234")
  conn,err := listener.Accept()
  ```

- **然后通过`rpc.ServeConn(conn)`**函数在该连接上为对方提供`RPC`服务

  所以上面这个代码就是服务端提供服务的代码

- **客户端请求**`HelloService`服务的代码

  ```
  package main
  
  import (
  	"fmt"
  	"log"
  	"net/rpc"
  )
  func main(){
  	client ,err := rpc.Dial("tcp","localhost:1234")
  	if err != nil {
  		log.Fatal("dialing",err)
  	}
  	var reply string
  	client.Call("HelloService.Hello","hello",&reply)
  	if err != nil {
  		log.Fatal(err)
  	}
  	fmt.Println(reply)
  
  }
  ```

  - 通过`rpc.Dial`拨号`RPC`服务
  - 通过`client.Call("HelloService.Hello","hello",&reply)`调用具体的`RPC`方法
  - 在调用`client.Call`时，第一个参数是用点号链接的`RPC`服务名字和方法名字，第二和第三个参数分别我们定义`RPC`方法的两个参数。

作为开发人员一般至少有三种角色：

1. 首先是服务端实现RPC方法的开发人员
2. 其次是客户端调用RPC方法的人员
3. 最后也是最重要的是制定服务端和客户端RPC接口规范的设计人员。
4. 虽然看似实现简单，但是不利于后期的维护和工作的切割。

如果要重构`HelloService`服务，第一步需要明确服务的名字和接口：

```
const HelloServiceName = "path/to/pkg.HelloServiceName"
// 我们在RPC服务的名字中增加了包路径前缀（这个是RPC服务抽象的包路径，并非完全等价Go语言的包路径
type HelloServiceInterface = interface {
	Hello(request string,peply *string) error
}

func RegisterHelloService( svc HelloServiceInterface) error {
	return rpc.RegisterName(HelloServiceName,svc)
}
```

- **定义接口的名字，或者说是某一大类功能总（服务）的名字。**

- **然后是服务要实现的详细的方法列表。**

- **最后是*<u>注册</u>*该服务**

  `RegisterHelloService`注册服务时，编译器会要求传入的对象满足`HelloServiceInterface`接口。

以上就是我们定义好了RPC接口服务的规范。客户端就可以根据规范编写`RPC`调用的代码了：

```
func main() {
    client, err := rpc.Dial("tcp", "localhost:1234")
    if err != nil {
        log.Fatal("dialing:", err)
    }

    var reply string
    err = client.Call(HelloServiceName+".Hello", "hello", &reply)
    if err != nil {
        log.Fatal(err)
    }
}
```

- **但是！！！`client.Call`函数调用`RPC`方法依然比较繁琐，同时参数的类型依然无法得到编译器提供的安全保障。**

  ```
  //为了简化客户端用户调用RPC函数，我们在可以在接口规范部分增加对客户端的简单包装
  // client.go
  package main
  
  import (
  	"fmt"
  	"log"
  	"net/rpc"
  )
  
  type Client struct {
  	*rpc.Client
  }
  
  func Dial(network string, address string) *Client {
  	client, err := rpc.Dial(network, address)
  	if err != nil {
  		log.Fatal(err)
  	}
  	return &Client{
  		client,
  	}
  }
  func (c *Client) ClientCall(serviceMethod string, args string, reply *string) error {
  
  	err := c.Call(serviceMethod+".Service", args, reply)
  	if err != nil {
  		log.Fatal(err)
  		return err
  
  	}
  	return nil
  
  }
  func main() {
  	client := Dial("tcp", "localhost:1234")
  	var reply string
  	err := client.ClientCall("User", "user request", &reply)
  	if err != nil {
  		log.Fatal(err)
  	}
  	fmt.Println(reply)
  
  }
  //go语言里我们每一个具体的类型，基于它们相同的行为我们可以把这些相同的行为表示成一个接口类型。
  //不像基于类的语言，类实现的接口集合需要进行显式的定义。显示的说明是指：类必须声明实现了某接口，从哪个接口继承。哪怕是两个一模一样的接口但只有名字不一样，也只能根据类所声明的实现接口是否包括该接口来决定该类是否实现该接口，叫做“侵入式”的接口。
  //在Go语言中我们可以在需要的时候定义一个新的抽象或者特定特点的组，而不需要修改具体类型的定义。
  //接口类型封装和隐藏具体类型和它的值。即使具体类型有其它的方法，也只有接口类型暴露出来的方法会被调用到
  
  ```

  ```
  //对服务端进行包装
  //server.go
  package main
  
  import (
  	"log"
  	"net"
  	"net/rpc"
  )
  
  type ServerServiceInterface = interface {
  	Service(request string, reply *string) error
  }
  
  func RegisterService(name string, svc ServerServiceInterface) error {
  	return rpc.RegisterName(name, svc)
  
  }
  
  type User struct {
  }
  
  func (u *User) Service(request string, reply *string) error {
  
  	*reply = request + " " + "Success!"
  	return nil
  }
  
  func ListenService(network string, address string) {
  	listener, err := net.Listen(network, address)
  	if err != nil {
  		log.Fatal("ListenTCP error:", err)
  	}
  	conn, err := listener.Accept()
  	if err != nil {
  		log.Fatal("Accept error:", err)
  	}
  
  	rpc.ServeConn(conn)
  
  }
  
  func main() {
  	RegisterService("User", new(User))
  	ListenService("tcp", ":1234")
  
  }
  
  ```

  ```
  //测试结果
  user request Success!
  ```

- **在新的`RPC`服务端实现中，我们用`RegisterService`函数来注册函数，这样不仅可以避免命名服务名称的工作，同时也保证了传入的服务对象满足了`RPC`接口的定义。最后我们新的服务改为支持多个`TCP`链接，然后为每个TCP链接提供`RPC`服务。**

## 4.使用`json`的`RPC`

> 标准库的RPC默认采用Go语言特有的gob编码，因此从其它语言调用Go语言实现的RPC服务将比较困难。在互联网的微服务时代，每个RPC以及服务的使用者都可能采用不同的编程语言，因此跨语言是互联网时代RPC的一个首要条件。

> Go语言特有的gob编码
>
> 为了让某个数据结构能够在网络上传输或能够保存至文件，它必须被编码然后再解码。当然已经有许多可用的编码方式了，比如 JSON,XML,Google 的 protocol buffers 等等。而现在又多了一种，由Go语言 encoding/gob 包提供的方式。
>
> Gob 是Go语言自己以二进制形式序列化和反序列化程序数据的格式，可以在 encoding 包中找到。这种格式的数据简称为 Gob（即 Go binary 的缩写）Gob 由发送端使用 Encoder 对数据结构进行编码。在接收端收到消息之后，接收端使用 Decoder 将序列化的数据变化成本地变量。Go语言可以通过 JSON 或 Gob 来序列化 struct 对象，虽然 JSON 的序列化更加为通用，那么我们为什么不用json呢？因为 Gob 编码可以实现 JSON 所不能支持的 struct 的**方法序列化**，利用 Gob 包序列化 struct 保存到本地也十分简单。Gob 使用通用的 io.Writer 接口，通过 NewEncoder() 函数创建 Encoder 对象并调用 Encode()，相反的过程使用通用的 io.Reader 接口，通过 NewDecoder() 函数创建 Decoder 对象并调用 Decode

Go语言的RPC框架有两个比较有特色的设计：

- 一个是RPC数据打包时可以通过插件实现自定义的编码和解码；
- 另一个是RPC建立在抽象的io.ReadWriteCloser接口之上的，我们可以将RPC架设在不同的通讯协议之上。
- 这里我们将尝试通过官方自带的net/rpc/jsonrpc扩展实现一个跨语言的RPC。

```
//server.go
package main

import (
	"log"
	"net"
	"net/rpc"
	"net/rpc/jsonrpc"
)

type ServerServiceInterface = interface {
	Service(request string, reply *string) error
}

func RegisterService(name string, svc ServerServiceInterface) error {
	return rpc.RegisterName(name, svc)

}

type User struct {
}

func (u *User) Service(request string, reply *string) error {

	*reply = request + " " + "Success!"
	return nil
}

func ListenService(network string, address string) {
	listener, err := net.Listen(network, address)
	if err != nil {
		log.Fatal("ListenTCP error:", err)
	}
	conn, err := listener.Accept()
	if err != nil {
		log.Fatal("Accept error:", err)
	}

	rpc.ServeCodec(jsonrpc.NewServerCodec(conn))
	//用rpc.ServeCodec函数替代了rpc.ServeConn函数，传入的参数是针对服务端的json编解码器。

}

func main() {
	RegisterService("User", new(User))
	ListenService("tcp", ":1234")

}

```

```
//client.go
package main

import (
	"fmt"
	"log"
	"net"
	"net/rpc"
	"net/rpc/jsonrpc"
)

type Client struct {
	*rpc.Client
}

func Dial(network string, address string) *Client {
	//先手工调用net.Dial函数建立TCP链接
	conn, err := net.Dial(network, address)
	//基于该链接建立针对客户端的json编解码器。
	client := rpc.NewClientWithCodec(jsonrpc.NewClientCodec(conn))
	if err != nil {
		log.Fatal(err)
	}
	return &Client{
		client,
	}
}
func (c *Client) ClientCall(serviceMethod string, args string, reply *string) error {

	err := c.Call(serviceMethod+".Service", args, reply)
	if err != nil {
		log.Fatal(err)
		return err

	}
	return nil

}
func main() {
	client := Dial("tcp", "localhost:1234")
	var reply string
	err := client.ClientCall("User", "user request", &reply)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(reply)

}

```

- 通过nc命令`nc -l 1234`在同样的端口启动一个TCP服务。然后再次执行一次RPC调用将会发现nc输出了以下的信息：

```
{"method":"User.Service","params":["user request"],"id":0}
```

- 这是一个json编码的数据
- 其中method部分对应要调用的rpc服务和方法组合成的名字
- params部分的第一个元素为参数
- id是由调用端维护的一个唯一的调用编号。

请求的json数据对象在内部对应两个结构体：

客户端是clientRequest，服务端是serverRequest。clientRequest和serverRequest结构体的内容基本是一致的：

```
type clientRequest struct {
    Method string         `json:"method"`
    Params [1]interface{} `json:"params"`
    Id     uint64         `json:"id"`
}

type serverRequest struct {
    Method string           `json:"method"`
    Params *json.RawMessage `json:"params"`
    Id     *json.RawMessage `json:"id"`
}
```

通过直接向架设了RPC服务的TCP服务器发送json数据模拟RPC方法调用：

```
 echo -e '{"method":"User.Service","params":["user request"],"id":0}' | nc localhost 1234
```

```
//返回结果
{"id":0,"result":"user request Success!","error":null}
```

其中id对应输入的id参数，result为返回的结果，error部分在出问题时表示错误信息。对于顺序调用来说，id不是必须的。但是Go语言的RPC框架支持异步调用，当返回结果的顺序和调用的顺序不一致时，可以通过id来识别对应的调用。

```
返回的json数据也是对应内部的两个结构体：客户端是clientResponse，服务端是serverResponse。两个结构体的内容同样也是类似的：

type clientResponse struct {
    Id     uint64           `json:"id"`
    Result *json.RawMessage `json:"result"`
    Error  interface{}      `json:"error"`
}

type serverResponse struct {
    Id     *json.RawMessage `json:"id"`
    Result interface{}      `json:"result"`
    Error  interface{}      `json:"error"`
}
```

只要遵循同样的json结构，以同样的流程就可以和Go语言编写的RPC服务进行通信。这样我们就实现了跨语言的RPC。

## 5.Http上的RPC

现在我们尝试在http协议上提供jsonrpc服务。新的RPC服务其实是一个类似REST规范的接口，接收请求并采用相应处理流程：

```
//server.go
package main

import (
	"io"

	"net/http"
	"net/rpc"
	"net/rpc/jsonrpc"
)

type ServerServiceInterface = interface {
	Service(request string, reply *string) error
}

func RegisterService(name string, svc ServerServiceInterface) error {
	return rpc.RegisterName(name, svc)

}

type User struct {
}

func (u *User) Service(request string, reply *string) error {

	*reply = request + " " + "Success!"
	return nil
}

func HttpServiceListen(address string) {
	http.HandleFunc("/jsonrpc", func(w http.ResponseWriter, r *http.Request) {
		var conn io.ReadWriteCloser = struct {
			io.Writer
			io.ReadCloser
		}{
			Writer:     w,
			ReadCloser: r.Body,
		}
		rpc.ServeRequest(jsonrpc.NewServerCodec(conn))

	})
	http.ListenAndServe(address, nil)

}

func main() {
	RegisterService("User", new(User))
	HttpServiceListen(":1234")

}

```

```
//测试
$ curl localhost:1234/jsonrpc -X POST \
    --data '{"method":"User.Service","params":["user request"],"id":0}'

//测试结果
{"id":0,"result":"user request Success!","error":null}

```

- **模拟一次RPC调用的过程就是向该链接发送一个json字符串：**
- 返回的结果依然是json字符串
- **这样就可以很方便地从不同语言中访问RPC服务了。**

## 6.Protobuf和RPC

> Protobuf是Protocol Buffers的简称，它是Google公司开发的一种数据描述语言，并于2008年对外开源。Protobuf刚开源时的定位类似于XML、JSON等数据描述语言通过附带工具生成代码并实现将结构化数据序列化的功能。但是我们更关注的是Protobuf作为接口规范的描述语言，可以作为设计安全的跨语言PRC接口的基础工具。

Protobuf中最基本的数据单元是message，是类似Go语言中结构体的存在。在message中可以嵌套message或其它的基础数据类型的成员。

```
syntax = "proto3";

option go_package="./;new";
package new;

message String {
    string value =1;
    
}
//option go_package = "path;name";
//path 表示生成的go文件的存放地址，会自动生成目录的。
//name 表示生成的go文件所属的包名
```

```
// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.26.0
// 	protoc        v3.20.0
// source: user.proto

package new

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type String struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Value string `protobuf:"bytes,1,opt,name=value,proto3" json:"value,omitempty"`
}

func (x *String) Reset() {
	*x = String{}
	if protoimpl.UnsafeEnabled {
		mi := &file_user_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *String) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*String) ProtoMessage() {}

func (x *String) ProtoReflect() protoreflect.Message {
	mi := &file_user_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use String.ProtoReflect.Descriptor instead.
func (*String) Descriptor() ([]byte, []int) {
	return file_user_proto_rawDescGZIP(), []int{0}
}

func (x *String) GetValue() string {
	if x != nil {
		return x.Value
	}
	return ""
}

var File_user_proto protoreflect.FileDescriptor

var file_user_proto_rawDesc = []byte{
	0x0a, 0x0a, 0x75, 0x73, 0x65, 0x72, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x03, 0x6e, 0x65,
	0x77, 0x22, 0x1e, 0x0a, 0x06, 0x53, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x12, 0x14, 0x0a, 0x05, 0x76,
	0x61, 0x6c, 0x75, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x05, 0x76, 0x61, 0x6c, 0x75,
	0x65, 0x42, 0x08, 0x5a, 0x06, 0x2e, 0x2f, 0x3b, 0x6e, 0x65, 0x77, 0x62, 0x06, 0x70, 0x72, 0x6f,
	0x74, 0x6f, 0x33,
}

var (
	file_user_proto_rawDescOnce sync.Once
	file_user_proto_rawDescData = file_user_proto_rawDesc
)

func file_user_proto_rawDescGZIP() []byte {
	file_user_proto_rawDescOnce.Do(func() {
		file_user_proto_rawDescData = protoimpl.X.CompressGZIP(file_user_proto_rawDescData)
	})
	return file_user_proto_rawDescData
}

var file_user_proto_msgTypes = make([]protoimpl.MessageInfo, 1)
var file_user_proto_goTypes = []interface{}{
	(*String)(nil), // 0: new.String
}
var file_user_proto_depIdxs = []int32{
	0, // [0:0] is the sub-list for method output_type
	0, // [0:0] is the sub-list for method input_type
	0, // [0:0] is the sub-list for extension type_name
	0, // [0:0] is the sub-list for extension extendee
	0, // [0:0] is the sub-list for field type_name
}

func init() { file_user_proto_init() }
func file_user_proto_init() {
	if File_user_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_user_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*String); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_user_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   1,
			NumExtensions: 0,
			NumServices:   0,
		},
		GoTypes:           file_user_proto_goTypes,
		DependencyIndexes: file_user_proto_depIdxs,
		MessageInfos:      file_user_proto_msgTypes,
	}.Build()
	File_user_proto = out.File
	file_user_proto_rawDesc = nil
	file_user_proto_goTypes = nil
	file_user_proto_depIdxs = nil
}

//生成的user.pb.go文件
```



- 创建user.proto文件

- syntax语句表示采用proto3的语法,第三版的Protobuf对语言进行了提炼简化，所有成员均采用类似Go语言中的零值初始化（不再支持自定义默认值），因此消息成员也不再需要支持required特性。

- 然后package指令指明当前是new包

- message关键字定义一个新的String类型，在最终生成的Go语言代码中对应一个String结构体。

- **生成的结构体中还会包含一些以`XXX_`为名字前缀的成员**

  ```
  //去掉这些以`XXX_`为名字前缀的成员得到
  type String struct {
  	state         protoimpl.MessageState
  	sizeCache     protoimpl.SizeCache
  	unknownFields protoimpl.UnknownFields
  
  	Value string `protobuf:"bytes,1,opt,name=value,proto3" json:"value,omitempty"`
  }
  
  func (x *String) Reset() {
  	*x = String{}
  	if protoimpl.UnsafeEnabled {
  		mi := &file_user_proto_msgTypes[0]
  		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
  		ms.StoreMessageInfo(mi)
  	}
  }
  
  func (x *String) String() string {
  	return protoimpl.X.MessageStringOf(x)
  }
  
  func (*String) ProtoMessage() {}
  
  func (x *String) ProtoReflect() protoreflect.Message {
  	mi := &file_user_proto_msgTypes[0]
  	if protoimpl.UnsafeEnabled && x != nil {
  		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
  		if ms.LoadMessageInfo() == nil {
  			ms.StoreMessageInfo(mi)
  		}
  		return ms
  	}
  	return mi.MessageOf(x)
  }
  
  // Deprecated: Use String.ProtoReflect.Descriptor instead.
  func (*String) Descriptor() ([]byte, []int) {
  	return file_user_proto_rawDescGZIP(), []int{0}
  }
  
  func (x *String) GetValue() string {
  	if x != nil {
  		return x.Value
  	}
  	return ""
  }
  
  ```

  

- String类型中只有一个字符串类型的value成员，该成员编码时用1编号代替名字。

- 在XML或JSON等数据描述语言中，一般通过成员的名字来绑定对应的数据。**但是Protobuf编码却是通过成员的唯一编号来绑定对应的数据**

- 最终生成的Go结构体可以自由采用JSON或gob等编码格式，因此大家可以暂时忽略Protobuf的成员编码部分。

- ```
  // Code generated by protoc-gen-go. DO NOT EDIT.
  // versions:
  // 	protoc-gen-go v1.26.0
  // 	protoc        v3.20.0
  // source: user.proto
  
  // 更新user.proto文件，通过Protobuf来定义ServerServiceInterface服务：
  
  service ServerServiceInterface {
      rpc Service (String) returns (String);
  }
  但是重新生成的Go代码并没有发生变化。这是因为世界上的RPC实现有千万种，protoc编译器并不知道该如何为ServerServiceInterface服务生成代码。
  
  package new
  
  import (
  	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
  	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
  	reflect "reflect"
  	sync "sync"
  )
  
  const (
  	// Verify that this generated code is sufficiently up-to-date.
  	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
  	// Verify that runtime/protoimpl is sufficiently up-to-date.
  	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
  )
  
  type String struct {
  	state         protoimpl.MessageState
  	sizeCache     protoimpl.SizeCache
  	unknownFields protoimpl.UnknownFields
  
  	Value string `protobuf:"bytes,1,opt,name=value,proto3" json:"value,omitempty"`
  }
  
  func (x *String) Reset() {
  	*x = String{}
  	if protoimpl.UnsafeEnabled {
  		mi := &file_user_proto_msgTypes[0]
  		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
  		ms.StoreMessageInfo(mi)
  	}
  }
  
  func (x *String) String() string {
  	return protoimpl.X.MessageStringOf(x)
  }
  
  func (*String) ProtoMessage() {}
  
  func (x *String) ProtoReflect() protoreflect.Message {
  	mi := &file_user_proto_msgTypes[0]
  	if protoimpl.UnsafeEnabled && x != nil {
  		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
  		if ms.LoadMessageInfo() == nil {
  			ms.StoreMessageInfo(mi)
  		}
  		return ms
  	}
  	return mi.MessageOf(x)
  }
  
  // Deprecated: Use String.ProtoReflect.Descriptor instead.
  func (*String) Descriptor() ([]byte, []int) {
  	return file_user_proto_rawDescGZIP(), []int{0}
  }
  
  func (x *String) GetValue() string {
  	if x != nil {
  		return x.Value
  	}
  	return ""
  }
  
  var File_user_proto protoreflect.FileDescriptor
  
  var file_user_proto_rawDesc = []byte{
  	0x0a, 0x0a, 0x75, 0x73, 0x65, 0x72, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x03, 0x6e, 0x65,
  	0x77, 0x22, 0x1e, 0x0a, 0x06, 0x53, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x12, 0x14, 0x0a, 0x05, 0x76,
  	0x61, 0x6c, 0x75, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x05, 0x76, 0x61, 0x6c, 0x75,
  	0x65, 0x32, 0x3d, 0x0a, 0x16, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x53, 0x65, 0x72, 0x76, 0x69,
  	0x63, 0x65, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x12, 0x23, 0x0a, 0x07, 0x53,
  	0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x12, 0x0b, 0x2e, 0x6e, 0x65, 0x77, 0x2e, 0x53, 0x74, 0x72,
  	0x69, 0x6e, 0x67, 0x1a, 0x0b, 0x2e, 0x6e, 0x65, 0x77, 0x2e, 0x53, 0x74, 0x72, 0x69, 0x6e, 0x67,
  	0x42, 0x08, 0x5a, 0x06, 0x2e, 0x2f, 0x3b, 0x6e, 0x65, 0x77, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74,
  	0x6f, 0x33,
  }
  
  var (
  	file_user_proto_rawDescOnce sync.Once
  	file_user_proto_rawDescData = file_user_proto_rawDesc
  )
  
  func file_user_proto_rawDescGZIP() []byte {
  	file_user_proto_rawDescOnce.Do(func() {
  		file_user_proto_rawDescData = protoimpl.X.CompressGZIP(file_user_proto_rawDescData)
  	})
  	return file_user_proto_rawDescData
  }
  
  var file_user_proto_msgTypes = make([]protoimpl.MessageInfo, 1)
  var file_user_proto_goTypes = []interface{}{
  	(*String)(nil), // 0: new.String
  }
  var file_user_proto_depIdxs = []int32{
  	0, // 0: new.ServerServiceInterface.Service:input_type -> new.String
  	0, // 1: new.ServerServiceInterface.Service:output_type -> new.String
  	1, // [1:2] is the sub-list for method output_type
  	0, // [0:1] is the sub-list for method input_type
  	0, // [0:0] is the sub-list for extension type_name
  	0, // [0:0] is the sub-list for extension extendee
  	0, // [0:0] is the sub-list for field type_name
  }
  
  func init() { file_user_proto_init() }
  func file_user_proto_init() {
  	if File_user_proto != nil {
  		return
  	}
  	if !protoimpl.UnsafeEnabled {
  		file_user_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
  			switch v := v.(*String); i {
  			case 0:
  				return &v.state
  			case 1:
  				return &v.sizeCache
  			case 2:
  				return &v.unknownFields
  			default:
  				return nil
  			}
  		}
  	}
  	type x struct{}
  	out := protoimpl.TypeBuilder{
  		File: protoimpl.DescBuilder{
  			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
  			RawDescriptor: file_user_proto_rawDesc,
  			NumEnums:      0,
  			NumMessages:   1,
  			NumExtensions: 0,
  			NumServices:   1,
  		},
  		GoTypes:           file_user_proto_goTypes,
  		DependencyIndexes: file_user_proto_depIdxs,
  		MessageInfos:      file_user_proto_msgTypes,
  	}.Build()
  	File_user_proto = out.File
  	file_user_proto_rawDesc = nil
  	file_user_proto_goTypes = nil
  	file_user_proto_depIdxs = nil
  }
  
  //生成的Go代码并没有发生变化 ,protoc编译器并不知道该如何为HelloService服务生成代码
  ```

- ```
  // protoc-gen-go内部已经集成了一个名字为grpc的插件，可以针对gRPC生成代码：
  protoc --go_out=plugins=grpc:. user.proto
  ```

- ```
  // Code generated by protoc-gen-go. DO NOT EDIT.
  // versions:
  // 	protoc-gen-go v1.26.0
  // 	protoc        v3.20.0
  // source: user.proto
  
  package new
  
  import (
  	context "context"
  	grpc "google.golang.org/grpc"
  	codes "google.golang.org/grpc/codes"
  	status "google.golang.org/grpc/status"
  	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
  	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
  	reflect "reflect"
  	sync "sync"
  )
  
  const (
  	// Verify that this generated code is sufficiently up-to-date.
  	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
  	// Verify that runtime/protoimpl is sufficiently up-to-date.
  	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
  )
  
  type String struct {
  	state         protoimpl.MessageState
  	sizeCache     protoimpl.SizeCache
  	unknownFields protoimpl.UnknownFields
  
  	Value string `protobuf:"bytes,1,opt,name=value,proto3" json:"value,omitempty"`
  }
  
  func (x *String) Reset() {
  	*x = String{}
  	if protoimpl.UnsafeEnabled {
  		mi := &file_user_proto_msgTypes[0]
  		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
  		ms.StoreMessageInfo(mi)
  	}
  }
  
  func (x *String) String() string {
  	return protoimpl.X.MessageStringOf(x)
  }
  
  func (*String) ProtoMessage() {}
  
  func (x *String) ProtoReflect() protoreflect.Message {
  	mi := &file_user_proto_msgTypes[0]
  	if protoimpl.UnsafeEnabled && x != nil {
  		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
  		if ms.LoadMessageInfo() == nil {
  			ms.StoreMessageInfo(mi)
  		}
  		return ms
  	}
  	return mi.MessageOf(x)
  }
  
  // Deprecated: Use String.ProtoReflect.Descriptor instead.
  func (*String) Descriptor() ([]byte, []int) {
  	return file_user_proto_rawDescGZIP(), []int{0}
  }
  
  func (x *String) GetValue() string {
  	if x != nil {
  		return x.Value
  	}
  	return ""
  }
  
  var File_user_proto protoreflect.FileDescriptor
  
  var file_user_proto_rawDesc = []byte{
  	0x0a, 0x0a, 0x75, 0x73, 0x65, 0x72, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x03, 0x6e, 0x65,
  	0x77, 0x22, 0x1e, 0x0a, 0x06, 0x53, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x12, 0x14, 0x0a, 0x05, 0x76,
  	0x61, 0x6c, 0x75, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x05, 0x76, 0x61, 0x6c, 0x75,
  	0x65, 0x32, 0x3d, 0x0a, 0x16, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x53, 0x65, 0x72, 0x76, 0x69,
  	0x63, 0x65, 0x49, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x12, 0x23, 0x0a, 0x07, 0x53,
  	0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x12, 0x0b, 0x2e, 0x6e, 0x65, 0x77, 0x2e, 0x53, 0x74, 0x72,
  	0x69, 0x6e, 0x67, 0x1a, 0x0b, 0x2e, 0x6e, 0x65, 0x77, 0x2e, 0x53, 0x74, 0x72, 0x69, 0x6e, 0x67,
  	0x42, 0x08, 0x5a, 0x06, 0x2e, 0x2f, 0x3b, 0x6e, 0x65, 0x77, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74,
  	0x6f, 0x33,
  }
  
  var (
  	file_user_proto_rawDescOnce sync.Once
  	file_user_proto_rawDescData = file_user_proto_rawDesc
  )
  
  func file_user_proto_rawDescGZIP() []byte {
  	file_user_proto_rawDescOnce.Do(func() {
  		file_user_proto_rawDescData = protoimpl.X.CompressGZIP(file_user_proto_rawDescData)
  	})
  	return file_user_proto_rawDescData
  }
  
  var file_user_proto_msgTypes = make([]protoimpl.MessageInfo, 1)
  var file_user_proto_goTypes = []interface{}{
  	(*String)(nil), // 0: new.String
  }
  var file_user_proto_depIdxs = []int32{
  	0, // 0: new.ServerServiceInterface.Service:input_type -> new.String
  	0, // 1: new.ServerServiceInterface.Service:output_type -> new.String
  	1, // [1:2] is the sub-list for method output_type
  	0, // [0:1] is the sub-list for method input_type
  	0, // [0:0] is the sub-list for extension type_name
  	0, // [0:0] is the sub-list for extension extendee
  	0, // [0:0] is the sub-list for field type_name
  }
  
  func init() { file_user_proto_init() }
  func file_user_proto_init() {
  	if File_user_proto != nil {
  		return
  	}
  	if !protoimpl.UnsafeEnabled {
  		file_user_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
  			switch v := v.(*String); i {
  			case 0:
  				return &v.state
  			case 1:
  				return &v.sizeCache
  			case 2:
  				return &v.unknownFields
  			default:
  				return nil
  			}
  		}
  	}
  	type x struct{}
  	out := protoimpl.TypeBuilder{
  		File: protoimpl.DescBuilder{
  			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
  			RawDescriptor: file_user_proto_rawDesc,
  			NumEnums:      0,
  			NumMessages:   1,
  			NumExtensions: 0,
  			NumServices:   1,
  		},
  		GoTypes:           file_user_proto_goTypes,
  		DependencyIndexes: file_user_proto_depIdxs,
  		MessageInfos:      file_user_proto_msgTypes,
  	}.Build()
  	File_user_proto = out.File
  	file_user_proto_rawDesc = nil
  	file_user_proto_goTypes = nil
  	file_user_proto_depIdxs = nil
  }
  
  // Reference imports to suppress errors if they are not otherwise used.
  var _ context.Context
  var _ grpc.ClientConnInterface
  
  // This is a compile-time assertion to ensure that this generated file
  // is compatible with the grpc package it is being compiled against.
  const _ = grpc.SupportPackageIsVersion6
  
  // ServerServiceInterfaceClient is the client API for ServerServiceInterface service.
  //
  // For semantics around ctx use and closing/ending streaming RPCs, please refer to https://godoc.org/google.golang.org/grpc#ClientConn.NewStream.
  type ServerServiceInterfaceClient interface {
  	Service(ctx context.Context, in *String, opts ...grpc.CallOption) (*String, error)
  }
  
  type serverServiceInterfaceClient struct {
  	cc grpc.ClientConnInterface
  }
  
  func NewServerServiceInterfaceClient(cc grpc.ClientConnInterface) ServerServiceInterfaceClient {
  	return &serverServiceInterfaceClient{cc}
  }
  
  func (c *serverServiceInterfaceClient) Service(ctx context.Context, in *String, opts ...grpc.CallOption) (*String, error) {
  	out := new(String)
  	err := c.cc.Invoke(ctx, "/new.ServerServiceInterface/Service", in, out, opts...)
  	if err != nil {
  		return nil, err
  	}
  	return out, nil
  }
  
  // ServerServiceInterfaceServer is the server API for ServerServiceInterface service.
  type ServerServiceInterfaceServer interface {
  	Service(context.Context, *String) (*String, error)
  }
  
  // UnimplementedServerServiceInterfaceServer can be embedded to have forward compatible implementations.
  type UnimplementedServerServiceInterfaceServer struct {
  }
  
  func (*UnimplementedServerServiceInterfaceServer) Service(context.Context, *String) (*String, error) {
  	return nil, status.Errorf(codes.Unimplemented, "method Service not implemented")
  }
  
  func RegisterServerServiceInterfaceServer(s *grpc.Server, srv ServerServiceInterfaceServer) {
  	s.RegisterService(&_ServerServiceInterface_serviceDesc, srv)
  }
  
  func _ServerServiceInterface_Service_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
  	in := new(String)
  	if err := dec(in); err != nil {
  		return nil, err
  	}
  	if interceptor == nil {
  		return srv.(ServerServiceInterfaceServer).Service(ctx, in)
  	}
  	info := &grpc.UnaryServerInfo{
  		Server:     srv,
  		FullMethod: "/new.ServerServiceInterface/Service",
  	}
  	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
  		return srv.(ServerServiceInterfaceServer).Service(ctx, req.(*String))
  	}
  	return interceptor(ctx, in, info, handler)
  }
  
  var _ServerServiceInterface_serviceDesc = grpc.ServiceDesc{
  	ServiceName: "new.ServerServiceInterface",
  	HandlerType: (*ServerServiceInterfaceServer)(nil),
  	Methods: []grpc.MethodDesc{
  		{
  			MethodName: "Service",
  			Handler:    _ServerServiceInterface_Service_Handler,
  		},
  	},
  	Streams:  []grpc.StreamDesc{},
  	Metadata: "user.proto",
  }
  
  // 在生成的代码中多了一些类似HelloServiceServer、HelloServiceClient的新类型。这些类型是为gRPC服务的，并不符合我们的RPC要求。
  ```

  

- **Protobuf核心的工具集是C++语言开发的，在官方的protoc编译器中并不支持Go语言。要想基于上面的hello.proto文件生成相应的Go代码，需要安装相应的插件。首先是安装官方的protoc工具，可以从 https://github.com/google/protobuf/releases 下载。然后是安装针对Go语言的代码生成插件，可以通过`go get github.com/golang/protobuf/protoc-gen-go`命令安装**

  - **protoc是用于将proto文件编程成各种语言源码文件的工具**
  - 例如此处我们可以将`proto`文件通过`protoc`工具，编译生成适用于GO语言开发的源码文件`xxx.pb.go`
  - 一般会和`GRPC`进行配套使用

- **`go_out`参数告知protoc编译器去加载对应的protoc-gen-go工具，然后通过该工具生成代码，生成代码放到当前目录。最后是一系列要处理的protobuf文件的列表。**

```
//ubuntu安装protoc全过程

git clone https://github.com/protocolbuffers/protobuf.git
sudo apt-get install autoconf automake libtool curl make g++ unzip
cd protobuf/
git submodule update --init --recursive
sudo ./autogen.sh   #生成配置脚本
sudo ./configure    #生成Makefile文件，为下一步的编译做准备，可以加上安装路径：--prefix=path ，默认路径为/usr/local/
sudo make           #从Makefile读取指令，然后编译
sudo make check     #可能会报错，但是不影响,对于安装流程没有实质性用处，可以跳过该步
sudo make install 
sudo ldconfig       #更新共享库缓存
which protoc        #查看软件的安装位置
protoc --version    #检查是否安装成功

//吐槽！！！真的超级慢！！！
//但是很管用.....
```



## 7.设计netrpcPlugin插件

> 用于为标准库的RPC框架生成代码

- Protobuf的protoc编译器是通过**插件机制实现对不同语言的支持**。比如protoc命令出现`--xxx_out`格式的参数，那么protoc将首先查询是否有内置的xxx插件，如果没有内置的xxx插件那么将继续查询当前系统中是否存在protoc-gen-xxx命名的可执行程序，最终通过查询到的插件生成代码。对于Go语言的protoc-gen-go插件来说，里面又实现了一层静态插件系统。比如protoc-gen-go内置了一个gRPC插件，用户可以通过`--go_out=plugins=grpc`参数来生成gRPC相关代码，否则只会针对message生成相关代码

- **参考`gRPC`插件的代码，可以发现`generator.RegisterPlugin`函数可以用来注册插件。插件是一个`generator.Plugin`接口：**

- ```
  // A Plugin provides functionality to add to the output during
  // Go code generation, such as to produce RPC stubs.
  type Plugin interface {
      //Name方法返回插件的名字，这是Go语言的Protobuf实现的插件体系
      Name() string
      // Init函数是通过g参数对插件进行初始化 g参数中包含Proto文件的所有信息.
      Init(g *Generator)
      // Generate和GenerateImports方法用于生成主体代码和对应的导入包代码。
      
      Generate(file *FileDescriptor)
  
      GenerateImports(file *FileDescriptor)
  }
  ```

  所以我们可以设计一个`netrpcPlugin插件`，用于为标准库的`RPC`框架生成代码：

  ```
  import (
      "github.com/golang/protobuf/protoc-gen-go/generator"
  )
  
  type netrpcPlugin struct{ *generator.Generator }
  
  func (p *netrpcPlugin) Name() string                { return "netrpc" }
  func (p *netrpcPlugin) Init(g *generator.Generator) { p.Generator = g }
  
  func (p *netrpcPlugin) GenerateImports(file *generator.FileDescriptor) {
      if len(file.Service) > 0 {
      //GenerateImports方法调用自定义的genImportCode函数生成导入代码。
          p.genImportCode(file)
      }
  }
  
  func (p *netrpcPlugin) Generate(file *generator.FileDescriptor) {
      for _, svc := range file.Service {
      //Generate方法调用自定义的genServiceCode方法生成每个服务的代码。
          p.genServiceCode(svc)
      }
  }
  ```

  ```
  //自定义的genImportCode和genServiceCode方法只是输出一行简单的注释：
  func (p *netrpcPlugin) genImportCode(file *generator.FileDescriptor) {
      p.P("// TODO: import code")
  }
  
  func (p *netrpcPlugin) genServiceCode(svc *descriptor.ServiceDescriptorProto) {
      p.P("// TODO: service code, Name = " + svc.GetName())
  }
  
  ```

- **要使用我们定义好的插件，需要通过`generator.RegisterPlugin`函数注册插件**

  ```
  func init() {
      generator.RegisterPlugin(new(netrpcPlugin))
  }
  ```

- **Go语言的包只能静态导入，我们无法向已经安装的`protoc-gen-go`添加我们新编写的插件。我们将重新克隆`protoc-gen-go`对应的main函数**

  ```
  package main
  
  import (
  	"io/ioutil"
  	"os"
  
  	"github.com/golang/protobuf/proto"
  	"github.com/golang/protobuf/protoc-gen-go/generator"
  )
  
  func main() {
  	g := generator.New()
  
  	data, err := ioutil.ReadAll(os.Stdin)
  	if err != nil {
  		g.Error(err, "reading input")
  	}
  
  	if err := proto.Unmarshal(data, g.Request); err != nil {
  		g.Error(err, "parsing input proto")
  	}
  
  	if len(g.Request.FileToGenerate) == 0 {
  		g.Fail("no files to generate")
  	}
  
  	g.CommandLineParameters(g.Request.GetParameter())
  
  	// Create a wrapped version of the Descriptors and EnumDescriptors that
  	// point to the file that defines them.
  	g.WrapTypes()
  
  	g.SetPackageNames()
  	g.BuildTypeNameMap()
  
  	g.GenerateAllFiles()
  
  	// Send back the results.
  	data, err = proto.Marshal(g.Response)
  	if err != nil {
  		g.Error(err, "failed to marshal output proto")
  	}
  	_, err = os.Stdout.Write(data)
  	if err != nil {
  		g.Error(err, "failed to write output proto")
  	}
  }
  
  ```

  

- **为了避免对`protoc-gen-go`插件造成干扰，我们将我们的可执行程序命名为`protoc-gen-go-netrpc`，表示包含了`netrpc`插件。然后用以下命令重新编译`user.proto`文件**

  - **值得注意的是在刚开始的时候如果没有go mod /go mod tidy 就会出现**

    ```
    go build protoc-gen-go-netrpc.go 
    package command-line-arguments
            imports google.golang.org/protobuf: build constraints exclude all Go files in /home/gongna/go/pkg/mod/google.golang.org/protobuf@v1.28.0
    gongna@gongna-Ubuntu:~/go/src/githu
    报错的问题
    //这里涉及到go 语言交叉编译与条件编译的知识
    //经过排错，我发现不过报错的原因不是交叉编译与条件编译引起的，只是因为依赖不够
    
    // 解决的办法就是go mod 与go tidy
    
    ```

  - ```
    protoc --go-netrpc_out=plugins=netrpc:. user.
    ```

  - ```
     cp ./protoc-gen-go-netrpc /usr/local/go/bin
     //这一步是把我们编译好的文件放在/usr/local/go/bin下
    //专门存放可执行的命令
     
    ```

    

  - ```go
    //执行后生成的代码
    // Code generated by protoc-gen-go. DO NOT EDIT.
    // source: user.proto
    
    package new
    
    import (
    	fmt "fmt"
    	proto "github.com/golang/protobuf/proto"
    	math "math"
    )
    
    // Reference imports to suppress errors if they are not otherwise used.
    var _ = proto.Marshal
    var _ = fmt.Errorf
    var _ = math.Inf
    
    // This is a compile-time assertion to ensure that this generated file
    // is compatible with the proto package it is being compiled against.
    // A compilation error at this line likely means your copy of the
    // proto package needs to be updated.
    const _ = proto.ProtoPackageIsVersion3 // please upgrade the proto package
    
    type String struct {
    	Value                string   `protobuf:"bytes,1,opt,name=value,proto3" json:"value,omitempty"`
    	XXX_NoUnkeyedLiteral struct{} `json:"-"`
    	XXX_unrecognized     []byte   `json:"-"`
    	XXX_sizecache        int32    `json:"-"`
    }
    
    func (m *String) Reset()         { *m = String{} }
    func (m *String) String() string { return proto.CompactTextString(m) }
    func (*String) ProtoMessage()    {}
    func (*String) Descriptor() ([]byte, []int) {
    	return fileDescriptor_116e343673f7ffaf, []int{0}
    }
    
    func (m *String) XXX_Unmarshal(b []byte) error {
    	return xxx_messageInfo_String.Unmarshal(m, b)
    }
    func (m *String) XXX_Marshal(b []byte, deterministic bool) ([]byte, error) {
    	return xxx_messageInfo_String.Marshal(b, m, deterministic)
    }
    func (m *String) XXX_Merge(src proto.Message) {
    	xxx_messageInfo_String.Merge(m, src)
    }
    func (m *String) XXX_Size() int {
    	return xxx_messageInfo_String.Size(m)
    }
    func (m *String) XXX_DiscardUnknown() {
    	xxx_messageInfo_String.DiscardUnknown(m)
    }
    
    var xxx_messageInfo_String proto.InternalMessageInfo
    
    func (m *String) GetValue() string {
    	if m != nil {
    		return m.Value
    	}
    	return ""
    }
    
    func init() {
    	proto.RegisterType((*String)(nil), "new.String")
    }
    
    func init() { proto.RegisterFile("user.proto", fileDescriptor_116e343673f7ffaf) }
    
    var fileDescriptor_116e343673f7ffaf = []byte{
    	// 125 bytes of a gzipped FileDescriptorProto
    	0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0xe2, 0xe2, 0x2a, 0x2d, 0x4e, 0x2d,
    	0xd2, 0x2b, 0x28, 0xca, 0x2f, 0xc9, 0x17, 0x62, 0xce, 0x4b, 0x2d, 0x57, 0x92, 0xe3, 0x62, 0x0b,
    	0x2e, 0x29, 0xca, 0xcc, 0x4b, 0x17, 0x12, 0xe1, 0x62, 0x2d, 0x4b, 0xcc, 0x29, 0x4d, 0x95, 0x60,
    	0x54, 0x60, 0xd4, 0xe0, 0x0c, 0x82, 0x70, 0x8c, 0x6c, 0xb9, 0xc4, 0x82, 0x53, 0x8b, 0xca, 0x52,
    	0x8b, 0x40, 0x64, 0x66, 0x72, 0xaa, 0x67, 0x5e, 0x49, 0x6a, 0x51, 0x5a, 0x62, 0x72, 0xaa, 0x90,
    	0x32, 0x17, 0x3b, 0x54, 0x4c, 0x88, 0x5b, 0x2f, 0x2f, 0xb5, 0x5c, 0x0f, 0x62, 0x8e, 0x14, 0x32,
    	0xc7, 0x89, 0x23, 0x8a, 0x4d, 0x4f, 0xdf, 0x3a, 0x2f, 0xb5, 0x3c, 0x89, 0x0d, 0x6c, 0xa9, 0x31,
    	0x20, 0x00, 0x00, 0xff, 0xff, 0x34, 0x53, 0xb5, 0x73, 0x82, 0x00, 0x00, 0x00,
    }
    
    ```

**我们已经构建了最小化的netrpcPlugin插件，并且通过克隆protoc-gen-go的主程序创建了新的protoc-gen-go-netrpc的插件程序。现在开始继续完善netrpcPlugin插件，最终目标是生成RPC安全接口。**

## 8.自动生成完整的RPC代码

- ```
   protoc --go-netrpc_out=plugins=netrpc:. hello.proto
   //对应的文件
   syntax = "proto3";
  //
  package new;
  
  message String {
      string value =1;
      
  }
  service ServerServiceInterface {
      rpc Service (String) returns (String);
  }
  
  ```

  ```
  //本来是下面这些代码，但是报错，原因是.protoGo 导入路径是通过声明go_package带有 Go 包的完整导入路径的选项在文件中本地指定的。示例用法：option go_package = "example.com/project/protos/fizz";对于go_package选项和M标志，该值可能包括一个显式的包名称，该名称与导入路径之间用分号分隔。如："example.com/protos/foo;package_name"。不鼓励这种用法，因为默认情况下，包名称将以合理的方式从导入路径派生。
  
  
  option go_package = "example.com/project/protos/fizz";
  syntax = "proto3";
  option go_package="./;new";
  
  package new;
  message String {
      string value =1;
      
  }
  service ServerServiceInterface {
      rpc Service (String) returns (String);
  }
  
  
  ```

  

- **其中`--go-netrpc_out`参数告知protoc编译器加载名为protoc-gen-go-netrpc的插件，插件中的`plugins=netrpc`指示启用内部唯一的名为netrpc的netrpcPlugin插件。在新生成的user.pb.go文件中将包含增加的注释代码。**
- **自动生成完整的RPC代码**

****

```
//继续完善netrpcPlugin插件，最终目标是生成RPC安全接口。
package netrpc

import (
	"bytes"
	"log"
	"text/template"

	"github.com/golang/protobuf/protoc-gen-go/descriptor"
	"github.com/golang/protobuf/protoc-gen-go/generator"
)

func init() {
	generator.RegisterPlugin(new(netrpcPlugin))
}

type netrpcPlugin struct{ *generator.Generator }

func (p *netrpcPlugin) Name() string                { return "netrpc" }
func (p *netrpcPlugin) Init(g *generator.Generator) { p.Generator = g }

func (p *netrpcPlugin) GenerateImports(file *generator.FileDescriptor) {
	if len(file.Service) > 0 {
		p.genImportCode(file)
	}
}

func (p *netrpcPlugin) Generate(file *generator.FileDescriptor) {
	for _, svc := range file.Service {
		p.genServiceCode(svc)
	}
}
//2.然后要在自定义的genServiceCode方法中为每个服务生成相关的代码。分析可以发现每个服务最重要的是服务的名字，然后每个服务有一组方法。而对于服务定义的方法，最重要的是方法的名字，还有输入参数和输出参数类型的名字。
type ServiceSpec struct {
	ServiceName string
	MethodList  []ServiceMethodSpec
}

type ServiceMethodSpec struct {
	MethodName     string
	InputTypeName  string
	OutputTypeName string
}

//1.首先是自定义的genImportCode方法中生成导入包的代码：
func (p *netrpcPlugin) genImportCode(file *generator.FileDescriptor) {
	p.P(`import "net/rpc"`)
}

//4.然后我们就可以基于buildServiceSpec方法构造的服务的元信息生成服务的代码：
func (p *netrpcPlugin) genServiceCode(svc *descriptor.ServiceDescriptorProto) {
	spec := p.buildServiceSpec(svc)
	var buf bytes.Buffer
	t := template.Must(template.New("").Parse(tmplService))
	err := t.Execute(&buf, spec)
	if err != nil {
		log.Fatal(err)
	}

	p.P(buf.String())
}

//3.然后我们新建一个buildServiceSpec方法用来解析每个服务的ServiceSpec元信息：


func (p *netrpcPlugin) buildServiceSpec(svc *descriptor.ServiceDescriptorProto) *ServiceSpec {
	spec := &ServiceSpec{
		ServiceName: generator.CamelCase(svc.GetName()),
	}

	for _, m := range svc.Method {
		spec.MethodList = append(spec.MethodList, ServiceMethodSpec{
			MethodName:     generator.CamelCase(m.GetName()),
			InputTypeName:  p.TypeName(p.ObjectNamed(m.GetInputType())),
			OutputTypeName: p.TypeName(p.ObjectNamed(m.GetOutputType())),
		})
	}

	return spec
}
//其中输入参数是*descriptor.ServiceDescriptorProto类型，完整描述了一个服务的所有信息。然后通过svc.GetName()就可以获取Protobuf文件中定义的服务的名字。Protobuf文件中的名字转为Go语言的名字后，需要通过generator.CamelCase函数进行一次转换。类似的，在for循环中我们通过m.GetName()获取方法的名字，然后再转为Go语言中对应的名字。比较复杂的是对输入和输出参数名字的解析：首先需要通过m.GetInputType()获取输入参数的类型，然后通过p.ObjectNamed获取类型对应的类对象信息，最后获取类对象的名字。

//6.最终要生成的代码可以构建如下模板：
const tmplService = `
{
   {$root := .}}

type {
   {.ServiceName}}Interface interface {
	{
   {- range $_, $m := .MethodList}}
		{
   {$m.MethodName}}(in *{
   {$m.InputTypeName}}, out *{
   {$m.OutputTypeName}}) error
	{
   {- end}}
}

func Register{
   {.ServiceName}}(srv *rpc.Server, x {
   {.ServiceName}}Interface) error {
	if err := srv.RegisterName("{
   {.ServiceName}}", x); err != nil {
		return err
	}
	return nil
}

type {
   {.ServiceName}}Client struct {
	*rpc.Client
}

var _ {
   {.ServiceName}}Interface = (*{
   {.ServiceName}}Client)(nil)

func Dial{
   {.ServiceName}}(network, address string) (*{
   {.ServiceName}}Client, error) {
	c, err := rpc.Dial(network, address)
	if err != nil {
		return nil, err
	}
	return &{
   {.ServiceName}}Client{Client: c}, nil
}
{
	{range $_, $m := .MethodList}}
 func (p *{
	{$root.ServiceName}}Client) {
	{$m.MethodName}}(in *{
	{$m.InputTypeName}}, out *{
	{$m.OutputTypeName}}) error {
	 return p.Client.Call("{
	{$root.ServiceName}}.{
	{$m.MethodName}}", in, out)
 }
 {
	{end}}
 `

```

```
//5.为了便于维护，我们基于Go语言的模板来生成服务代码，其中tmplService是服务的模板。在编写模板之前，我们先查看下我们期望生成的最终代码大概是什么样子：
type HelloServiceInterface interface {
    Hello(in String, out *String) error
}

func RegisterHelloService(srv *rpc.Server, x HelloService) error {
    if err := srv.RegisterName("HelloService", x); err != nil {
        return err
    }
    return nil
}

type HelloServiceClient struct {
    *rpc.Client
}

var _ HelloServiceInterface = (*HelloServiceClient)(nil)

func DialHelloService(network, address string) (*HelloServiceClient, error) {
    c, err := rpc.Dial(network, address)
    if err != nil {
        return nil, err
    }
    return &HelloServiceClient{Client: c}, nil
}

func (p *HelloServiceClient) Hello(in String, out *String) error {
    return p.Client.Call("HelloService.Hello", in, out)
}
```

**当Protobuf的插件定制工作完成后，每次uesr.proto文件中RPC服务的变化都可以自动生成代码。也可以通过更新插件的模板，调整或增加生成代码的内容。在掌握了定制Protobuf插件技术后，你将彻底拥有这个技术。**`