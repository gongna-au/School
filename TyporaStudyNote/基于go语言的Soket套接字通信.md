# 基于go语言的Soket套接字通信

## 网络应用的--设计模式

#### 1) C/S模式

传统的网络应用设计模式，客户机（Client）/服务器（Server）模式，需要在通讯两端各自部署客户机和服务器来完成数据通信。

#### 2) B/S模式

浏览器（Browser）/服务器（Server）模式，只需在一端部署服务器，而另外一端使用每台 PC 都默认配置的浏览器即可完成数据的传输。

Go语言的 net 包中有一个 TCPConn 类型，可以用来建立 TCP 客户端和 TCP 服务器端间的通信通道，TCPConn 类型里有两个主要的函数：

```
func (c *TCPConn) Write(b []byte) (n int, err os.Error)
func (c *TCPConn) Read(b []byte) (n int, err os.Error)
```

- TCPConn 可以用在客户端和服务器端来读写数据。

-  TCPAddr 类型，它表示一个 TCP 的地址信息，其定义如下：

  ```
  type TCPAddr struct {
      IP IP
      Port int
  }
  ```

- Go语言中通过 ResolveTCPAddr 可以获取一个 TCPAddr 类型

  ```
  func ResolveTCPAddr(net, addr string) (*TCPAddr, os.Error)
  ```

参数说明

- net 参数是 "tcp4"、"tcp6"、"tcp" 中的任意一个，分别表示 TCP(IPv4-only)，TCP(IPv6-only) 或者 TCP(IPv4,IPv6) 中的任意一个；

- addr 表示域名或者 IP 地址，例如 "c.biancheng.net:80" 或者 "127.0.0.1:22"

  ## 

## WebSocket 网络通信

> WebSocket 是一种网络传输协议，可以在单个 TCP 连接上进行全双工通信，位于 OSI 模型的应用层。WebScoket 在 2011 年由 IETF 标准化为 RFC 6455，后由 RFC 7936 补充规范。Web IDL 中的 WebSocket API 是由 W3C 标准化的。
>
> WebSocket 使得客户端和服务器之间的数据交换变得更加简单，允许服务端主动向客户端推送数据。在 WebSocket API 中，浏览器和服务器只需完成**一次握手，两者之间就可以建立持久性的连接**，并进行双向数据传输。
>
> WebSocket 是一种与 HTTP 不同的协议。两者都位于 OSI 模型的应用层，并且都依赖于传输层的 TCP。虽然它们不同，但 RFC 6455 规定: "WebSocket 设计为通过 80 和 443 端口工作，并支持 HTTP 代理和中介"，从而使其与 HTTP 兼容。
>
> 为了实现兼容性，WebSocket 在握手时使用 HTTP Upgrade 头把 HTTP 更改为 WebSocket
>
> WebSocket 支持 Web 浏览器(或其他客户端应用程序)与 Web 服务器之间的交互，具有较低的开销，以便实现客户端与服务器的实时数据传输。
> 服务器可以通过标准化的方式来实现，无须客户端先请求内容，并允许消息在保持连接打开的同时进行来回传递。
> 通过这种方式，我们可以在客户端和服务器之间进行双向持续对话。通信通过 TCP 的 80 或 443 端口完成，这在防火墙阻止非 Web 网络连接的环境下是有益的。另外，Comet 之类的技术会以非标准化的方式实现类似的双向通信
>
> 大多数浏览器都支持该协议，如 Chrome、Firefox、Safari、Microsoft Edge、Internet Explorer 和 Opera 等
>
> 与 HTTP 不同，WebScoket 提供全双工通信。此外，WebScoket 还可以在 TCP 之上启用信息流。TCP 单独处理字节流，没有固定的消息概念。在 WebSocket 之前，使用 Comet 可以实现全双工通信，但是 Comet 存在 TCP 握手和 HTTP 头的开销，因此对于小消息来说效率极低。WebSocket 旨在解决这些问题WebSocket 协议规范将 ws(WebSocket)和 wss(WebSocket Secure)定义为两个新的统一资源标识符(URI)方案，分别对应明文和加密连接。
> 除方案名称和片段 ID(不支持`#`)外，其余的 URI 组件都被定义为词 URI 的通用语法
>
> 通过使用浏览器开发人员工具，开发人员可以检查 WebSocket 握手和 WebSocket 框架





```
//客户端的
//client.go
package main

import (
	"io"
	"net"
	"os"

	"log"
)

func main() {
	conn, err := net.Dial("tcp", ":2020")
	if err != nil {
		panic(err)
	}

	done := make(chan struct{})
	go func() {
		io.Copy(os.Stdout, conn)
		// NOTE: ignoring errors
		log.Println("done")
		// signal the main goroutine
		done <- struct{}{}
	}()

	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done
}

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}

```

```
//服务器端的
//server.go
package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"strconv"
	"time"
)

var num int

var (
	// 新用户到来，通过该 channel 进行登记
	userEnterChannel = make(chan *User)
	// 用户离开，通过哎 channel 进行登记
	userLeavingChannel = make(chan *User)
	// 广播专用的用户普通信息 channel，缓冲是尽可能避免出现异常情况堵塞，这里简单给了 8，
	// 具体值根据情况调整
	messageChannel = make(chan string, 8)
)

type User struct {
	//每个用户的唯一标识
	ID int
	//每个用户的ip地址和端口
	Addr string
	//每个用户进入聊天室的时间
	EnterTime time.Time
	//每个用户有一个专属于自己接受信息的通道
	//当需要给某个用户发送消息时，只需在该用户的 MessageChannel 中写入消息即可。
	MessageChannel chan string
}

//四种 goroutine: main goroutine
//广播消息 goroutine
//每一个客户端链接都会有一个读和写的 goroutine
func main() {
	//在 listen 时没有指定 IP 地址，所以表示绑定到当前机器的 IP 地址上
	listener, err := net.Listen("tcp", ":2020")
	if err != nil {
		panic(err)
	}
	go broadCaseter()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Println(err)
			continue
		} else {
			go handleConn(conn)

		}

	}

}

// broadcaster 用于记录聊天室用户，并进行消息广播
// 1. 新用户进来 2. 用户普通消息 3. 用户离开
func broadCaseter() {
	//用户所有的用户是一个map
	users := make(map[*User]struct{})
	//在登记/注销用户时，是通过 map 存储在线用户的
	//在用户登记、注销时应使用专门的 channel。
	//在注销时，除从 map 中删除用户外，还会关闭 user 的 MessageChannel，避免出现 goroutine 泄漏问题
	//全局的 messageChannle 一般用来给聊天室中的所有用户广播消息
	//broadcaster 函数的关键在于对 goroutine 和 channel 的运用。
	//它很好地践行了 Go 的概念，即通过通信来共享内存。它里面的三个 channel 的定义如下:
	for {
		select {
		case user := <-userEnterChannel:
			// 新用户进入
			users[user] = struct{}{}
		case user := <-userLeavingChannel:
			// 用户离开
			delete(users, user)
			//避免 goroutine 泄漏
			close(user.MessageChannel)
		case msg := <-messageChannel:
			for user := range users {
				user.MessageChannel <- msg
			}
		}
	}

}
func GetUserId() int {
	num = num + 1
	return num

}

func handleConn(conn net.Conn) {
	//1.处理完毕后关闭连接
	defer conn.Close()
	//2.每个连接进入到这个函数里面就保存我们需要的数据
	user := &User{
		GetUserId(),
		conn.RemoteAddr().String(),
		time.Now(),
		make(chan string, 8),
	}
	//go sendMessage(conn, user.MessageChannel)
	//也就是在往user.MessageChannel这个里面写的时候就是用户可以接收到外界的信息
	//那么还需要实现用户可以往外发送信息
	go sendMessageOut(conn, user.MessageChannel)

	//3.给当前用户发送欢迎信息 往每个进入聊天室的用户的Channel里面写
	//给当前用户发送欢迎信息，同时给聊天室所有用户发送有新用户到来的提醒
	//注意顺序一定是先欢迎用户，然后才把用户添加到全局聊天室的用户列表当中
	//否则会收到自己到来的消息提示
	//当然，也可以做消息过滤处理
	user.MessageChannel <- "Welcome " + strconv.Itoa(user.ID)
	//4. 需要一个公共的messageChannel让所有的用户知道这个用户来了
	messageChannel <- "User:" + strconv.Itoa(user.ID) + "has enter"
	//5. 把每个进入的用户的指针添加到全局的变量中
	//将该用户写入全局用户列表，即聊天室用户列表
	userEnterChannel <- user
	//6 .循环的读取每个用户的输入
	input := bufio.NewScanner(conn)
	for input.Scan() {
		messageChannel <- strconv.Itoa(user.ID) + ":" + input.Text()
	}
	if err := input.Err(); err != nil {
		log.Println("从用户读取数据错误！", err)
	}
	//6.用户离开
	userLeavingChannel <- user
	messageChannel <- "User:" + strconv.Itoa(user.ID) + "has left"

}

/*
需要注意的是，因为 sendMessage 在一个新的 goroutine 中，所以如果函数里的 ch 不关闭
则该 goroutine 是不会退出的，因此需要注意不关闭 ch 导致的 goroutine 泄漏的问题这里有一个语法
ch <-chan string
channel 实际上有三种类型，大部分时候，我们只用了其中一种，即正常的既能发送也能接收的 channel。
除此之外，还有单向的 channel： 只能接收和只能发送。它们无法直接被创建，而是通过正常(双向) channel 转换而来(会自动隐式转换)。
比如在上面代码中的 ch <-chan string 就是为了限制在 sendMessage 函数只从 channel 中读取数据，不允许往里写数据 */
func sendMessageOut(conn net.Conn, ch <-chan string) {
	//向外界发送信息已经存储在自己的chan string里面
	//现在可以直接读取出来
	for msg := range ch {
		//把读到的数据又写入到了连接conn
		fmt.Fprintln(conn, msg)
	}
}

```

## 测试

![](/home/gongna/桌面/2022-05-20_11-14.png)

如图，是两个同时运行了client.go代码

前提是先运行server.go代码

