# 1.AOP 面对切面编程思想

AOP(Aspect Oriented Programming, 面向切面编程)，如果要长篇大论地介绍最早是怎么来地，是通过多少复杂的机制实现的，那将是晦涩难懂的原理，下面举一个例子来跟大家解释什么是 AOP。

> 假如A和B家里各有一棵苹果树，今天市场上苹果很畅销，A和B都很开心，因为他们可以摘苹果去卖钱。
> 但是第二天市场上桃子变得畅销了，苹果滞销了，B不开心了，因为他只有一颗苹果树，他的苹果树只能结苹果，长不出桃子来。但是A依然很开心，因为他在他的苹果树上嫁接了一根桃枝，当天就长出了很多桃子，又卖了很多钱。第三天市场上橘子变得畅销了，B依然不开心，因为他只有苹果；A依然很开心，因为他在苹果树上又嫁接了一根橘子枝。第四天A在苹果树上嫁接了一根梨枝，第五天嫁接了一根西瓜枝，第六天嫁接了一根巧克力枝A的做法就是 AOP，A的苹果树就是一个基于面对切面编程思想架构的 Web。

# 2.Django 的前后端分离

Django 的普通项目是基于 MVT 模式(Model View Template)开发的，而 Django 的前后端分离项目则是基于 MVVM 模式(Model View ViewModel)开发的，解耦得更彻底，彻底到前后端分离了，甚至可以说分离成了两个项目。

Django 前后端分离项目原理：后端遵循 restful 规范开发 API，与前端进行数据交互，实现多端应用。

## 1.什么是API

API 作为一个互联网行业的术语，很少被直接翻译过来，因为中文中并没有一个对应的词汇可以完全表达其含义，如果强行翻译，可以被翻译为数据接口，但显然这个翻译并不准确。
举个现实中的例子，比如购房网上面有全国房屋买卖的交易数据，万达公司在需要一些房屋交易数据来作为参考投产项目时，如果自己去做社会调研，费时、费力，非常不合算，所以万达公司每年都要向购房网支付数百万元来购买这些交易数据。
大家是否考虑过，这一笔交易是以怎样的方式进行的呢？

所谓一手交钱一手交货，交钱的流程比较简单，只要万达公司将资金汇给购房网就可以了，但是购房网是怎样将全国房屋买卖的交易数据交给万达公司呢？
难道是直接将数据库复制给万达公司一份吗？这显然不可能。
购房网是将一些 API 和权限交给万达公司的技术人员，万达公司的技术人员就可以通过调用这些 API 获得到他们所需要的交易数据。

当然，API 是一个广义的概念，除了可以通过调用 API 获取到数据资源外，还可以通过 API 提供和获取技术服务，在无数的 SDK(软件开发包)中都有所体现。

在业内编写这类 API，不论是使用什么编程语言，都需要遵循 RESTful 规范，当然这是众所周知的事情。

## 2.RESTful规范(如何写API)

API 接口应该如何写？API 跟 URL 有什么不同？
这绝对是不可以被忽略的问题，如果 API 写得乱七八糟，很有可能会失去负责前端开发的同事的信任。
将 API 写得“高大上”，也是一名开发者工匠精神的一种体现。
下面来介绍如何写 API

(1) **如果是对同一个表进行数据操作(增、删、改、查)，应该使用一条 API，然后根据 method 的不同，进行不同的操作**

```
GET/POST/PUT/DELETE/PATCH
```

(2) **面向资源编程，通过 API 提交的参数最好是名次，比如 name，尽量少用动词。**

```
http://www.abc.com/name
```

(3) **体现版本，在 API 中加入像 v1、v2 这样的版本代码**：

```
http://www.abc.com/v1/name
http://www.abc.com/v2/name
```

(4) **体现 API，让使用者一眼能看出这是 API 而不是 URL，应该在 API 中加入提示：**

```
http://www.abc.com/api/v1/name
http://www.abc.com/api/v2/name
```

(5) **使用 HTTPS，这一项原本是为了安全考虑，但是随着国内外互联网环境对安全性越来越重视，谷歌浏览器对所有不是 HTTPS 请求的链接全都会提示用户此链接为不安全链接，腾讯等平台也对小程序等产品强制要求使用 HTTPS 协议。**
不过，好在国内许多提供云服务的公司，像腾讯云、阿里云等，都提供免费的 SSL 证书，供开发者去申请。

> 众所周知 HTTPS 是保证 HTTP 通讯安全的协议，网站启用 HTTPS 可以避免很多安全性的问题， 而且 Chrome 浏览器 从 68 版本开始直接将 HTTP 网站标记为不安全了。
>
> 所以把网站升级成 HTTPS 自然是大势所趋，不过启用 HTTPS 有个最重要的问题是 HTTPS 证书`要花钱`！如果每年额外花钱去购买 HTTPS 证书，那也是一笔很大的开销。那么有没有免费的`HTTPS`证书可以用，有个叫[`Let’s Encrypt`](https://links.jianshu.com/go?to=https%3A%2F%2Fletsencrypt.org)的项目就提供了免费签发 HTTPS 证书的服务
>
> ```
> https://www.abc.com/api/v1/name
> https://www.abc.com/api/v2/name
> ```

(6) 响应式设置状态码，例如，200 和 201 代表操作成功，403 代表权限不够，404 代表没有指定资源，500 代表运行时发现代码逻辑错误等。

```
return HttpResponse("adgbag", status=300)
```

(7) API 的参数中加入筛选条件参数，也可以理解为获取资源优先选择 GET 的方式。

```
https://www.abc.com/aip/v2/name?page=1&size=10
```

(8) 返回值的规范，不同的 method 操作成功后，后端应该响应的返回值如下：

```
https://www.bab.com/api/v1/name
```

(9) 不同的提交方式代表对数据进行不同的操作：

- GET: 所有列表
- POST: 新增的数据

```
https://www.bab.com/api/v1/name/1
```

- GET: 单条数据
- PUT: 更新，返回更新的数据
- PATCH: 局部更新，返回更新的数据
- DELETE: 删除，返回空文档。

(10) 返回错误信息，应该加入错误代号 code，让用户能直接看出是哪种类型的错误。

```
ret {
    code: 1000,
    data: {
        {"id": 1, "title": "lala"}
    }
}
```

(11) 返回的详细信息，应该以字典的形式放在 data中呢。

```
ret {
    code: 1000,
    data: {
        {"id": 1, "title": "lala", "detail": "http://www...."}
    }
}
```



## 3.certbot 介绍（签发证书）

`certbot`是用于从 Let's Encrypt 获取证书的命令行工具，代码开源在[github](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Fcertbot%2Fcertbot%2F)上。

使用`certbot`命令行工具可以轻松的实现`HTTPS证书`签发，在签发证书之前，需要证明签发的域名是属于你控制的，目前`certbot`有两种验证方式：

1.HTTP
HTTP 方式就是`certbot`会生成一个特定的文件名和文件内容，要求放在你对应域名下对应路径(`/.well-known/acme-challenge/`)下，然后`certbot`再通过 HTTP 请求访问到此文件，并且文件内容与生成时候的一致。</br></br>

2.DNS
DNS 则是`certbot`生成一段特定的文本，要求在你对应域名中配置一条对应子域名(`_acme-challenge`)的`TXT`类型解析记录。</br></br>

例如：`certbot`生成内容`!@#$%^`，你需要申请的域名为`baidu.com`，则需要添加一条`_acme-challenge.baidu.com`的`TXT`类型解析记录，值为之前生成的内容。

在域名验证通过之后，`certbot`就可以签发`HTTPS`证书了，注意在此验证步骤基础上，`certbot`提供了很多开箱即用的自动验证方案

#### 1.使用 certbot 签发 HTTPS 证书

```
//下载
apt-get update
sudo apt-get install certbot -t stretch-backports
//开始签发证书
certbot certonly --cert-name pdown.org -d *.pdown.org,*.proxyee-down.com --manual --register-unsafely-without-email  --preferred-challenges dns --server https://acme-v02.api.letsencrypt.org/directory
```

这里签发了一个支持`*.pdown.org`和`*.proxyee-down.com`通配符域名的证书，注意如果是通配符域名证书需要指定`--server https://acme-v02.api.letsencrypt.org/directory`

```
Saving debug log to /var/log/letsencrypt/letsencrypt.log
Plugins selected: Authenticator manual, Installer None
Registering without email!

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Please read the Terms of Service at
https://letsencrypt.org/documents/LE-SA-v1.2-November-15-2017.pdf. You must
agree in order to register with the ACME server at
https://acme-v02.api.letsencrypt.org/directory
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
(A)gree/(C)ancel: A
Obtaining a new certificate
Performing the following challenges:
dns-01 challenge for pdown.org
dns-01 challenge for proxyee-down.com

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
NOTE: The IP of this machine will be publicly logged as having requested this
certificate. If you're running certbot in manual mode on a machine that is not
your server, please ensure you're okay with that.

Are you OK with your IP being logged?
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
(Y)es/(N)o: Y

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Please deploy a DNS TXT record under the name
_acme-challenge.pdown.org with the following value:

Axdqtserd184wvJc86Dxen386UXqbK2wrgb-*******

Before continuing, verify the record is deployed.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Press Enter to Continue
```

这里会生成一串随机字符并阻塞住，需要去设置一条对应的 TXT 类型的 DNS 解析记录再继续，在设置好之后可以用`nslookup`进行本地验证：

当验证通过的时候会输出证书生成的目录，里面会包含证书和对应的私钥，这里目录是`/etc/letsencrypt/live/pdown.org/`。

#### 2.使用 certbot hook 自动续签

上面证书虽然是生成好了，但是证书的有效期只有三个月，意味着每过三个月就得重新签发一个新的证书，一不注意证书就过期了，而且每次手动签发都非常的繁琐需要去手动设置 DNS 解析，所以`certbot`提供了一种自动续签的方案：hook

在创建证书的时候`certbot`提供了两个`hook`参数：

- manual-auth-hook
  指定用于验证域名的脚本文件
- manual-cleanup-hook
  指定用于清理的脚本文件，即验证完成之后

通过自定义这两个脚本就可以做到自动续签了，文档参考[pre-and-post-validation-hooks](https://links.jianshu.com/go?to=https%3A%2F%2Fcertbot.eff.org%2Fdocs%2Fusing.html%23pre-and-post-validation-hooks)。

## 3.Django REST framework 简介

> 在 Python 的 Web 业内广为流传的一句话“使用 Python 进行 Web 全栈开发者必会 Django，使用 Django 开发前后端分离项目者必会 Django REST framework”。

可以毫不夸张地说，如果可以将 Django REST framework 的 10 个常用组件融合贯通，那么使用 Django 开发前后端分离的项目中有可能遇到的绝大部分需求，都能得到高效的解决。

Django REST framework 的 10 个常用组件如下：

- 权限组件
- 认证组件
- 访问频率限制组件
- 序列化组件
- 路由组件
- 视图组件
- 分页组件
- 解析器组件
- 渲染器组件
- 版本组件
  