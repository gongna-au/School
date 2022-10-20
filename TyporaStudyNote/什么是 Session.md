#### **什么是 Session**

> Session 代表着服务器和客户端一次会话的过程。Session 对象存储特定用户会话所需的属性及配置信息。这样，当用户在应用程序的 Web 页之间跳转时，存储在 Session 对象中的变量将不会丢失，而是在整个用户会话中一直存在下去。当客户端关闭会话，或者 Session 超时失效时会话结束。

- **由于HTTP协议是*无状态* 的协议，所以服务端需要记录用户的状态时，就需要用某种机制来识别具体的用户，这个机制就是Session。**

  **什么是无状态？**

  **答：无状态就是：假如你点击物品，把某个商品加入到自己的购物车，当你点击按钮时，因为Http协议无状态。所以你的点击操作，并不会告诉服务器，是哪个用户操作的。所以服务器要为特定的用户创建特定的Session,用来标志这个用户，并且要跟踪用户，这样才知道你的购物车里到底有几个衣服，几本书.**

  **而且，这个Session是保存在服务器里面的，有一个唯一的标识。在服务器里面保存数据的形式有很多，可以是文件，也可以是内存，还可以是数据库。**

  **集群的时候还要考虑Session的转移，在大型的网站中，一般都会有专门的Session服务器集群。用来保存用户会话，这个时候的信息都是放在内存中的，使用一些缓存服务Memcached来放Session.**

- **服务端如何识别特定的用户？这个时候Cookie就登场了。每次Http请求的时候，客户都会发送相应的Cookie到服务端，大多数的应用都是通过Cookie来实现Session的跟踪的。**

  **每次HTTP请求的时候，客户端都会发送相应的Cookie信息到服务端。所以在第一次创建Session的时候，服务端会在HTTP协议中告诉客户端，需要在 Cookie 里面记录一个Session ID，以后每次请求把这个会话ID发送到服务器，我就知道你是谁了。**

  **客户端的浏览器禁用了 Cookie 怎么办？**

  **一般这种情况下，会使用一种叫做URL重写的技术来进行会话跟踪（说白了，就是你不让我在Cookie里面带Session对吧？那我只能在Url里面带一些信息以此来识别用户的身份了。），即每次HTTP交互，URL后面都会被附加上一个诸如 sid=xxxxx 这样的参数，服务端据此来识别用户。**

**总结：**

**Session是在服务端保存的一个数据结构，用来跟踪用户的状态，这个数据可以保存在集群、数据库、文件中**

**Cookie是客户端保存用户信息的一种机制，用来记录用户的一些信息，也是实现Session的一种方式。**

**区别：**

**Cookie 只能保存 ASCII，Session 可以存任意数据类型，一般情况下我们可以在 Session 中保持一些常用变量信息，比如说 UserId 等**

**有效期不同，Cookie 可设置为长时间保持，比如我们经常使用的默认登录功能，Session 一般失效时间较短，客户端关闭或者 Session 超时都会失效。**

**存储大小不同， 单个 Cookie 保存的数据不能超过 4K，Session 可存储数据远高于 Cookie。**



**为什么需要 Cookie 和 Session，他们有什么关联？**

> **说起来为什么需要 Cookie ，这就需要从浏览器开始说起，我们都知道浏览器是没有状态的(HTTP 协议无状态)，这意味着浏览器并不知道是张三还是李四在和服务端打交道。**

**这个时候就需要有一个机制来告诉服务端，本次操作用户是否登录，是哪个用户在执行的操作，那这套机制的实现就需要 Cookie 和 Session 的配合。**![img](https://nimg.ws.126.net/?url=http%3A%2F%2Fdingyue.ws.126.net%2F2020%2F0506%2F82b5d515j00q9x0tj000kc000hl008hc.jpg&thumbnail=650x2147483647&quality=80&type=jpg)

**用户第一次请求服务器的时候，服务器根据用户提交的相关信息，创建创建对应的 Session ，请求返回时将此 Session 的唯一标识信息 SessionID 返回给浏览器，浏览器接收到服务器返回的 SessionID 信息后，会将此信息存入到 Cookie 中，同时 Cookie 记录此 SessionID 属于哪个域名。**

**当用户第二次访问服务器的时候，请求会自动判断此域名下是否存在 Cookie 信息，如果存在自动将 Cookie 信息也发送给服务端，服务端会从 Cookie 中获取 SessionID，再根据 SessionID 查找对应的 Session 信息，如果没有找到说明用户没有登录或者登录失效，如果找到 Session 证明用户已经登录可执行后面操作。**

**SessionID 是连接 Cookie 和 Session 的一道桥梁，大部分系统也是根据此原理来验证用户登录状态。**

本质：**服务端是根据 Cookie 中的信息判断用户是否登录**

问题：**如果浏览器中禁止了 Cookie，如何保障整个机制的正常运转？**

- **第一种方案，每次请求中都携带一个 SessionID 的参数，也可以 Post 的方式提交，也可以在请求的地址后面拼接 xxx?SessionID=123456...。**

- **Token 机制。Token 机制多用于 App 客户端和服务器交互的模式，也可以用于 Web 端做用户状态管理。**

  **Token 的意思是“令牌”，是服务端生成的一串字符串，作为客户端进行请求的一个标识。Token 机制和 Cookie 和 Session 的使用机制比较类似。**

  **当用户第一次登录后，服务器根据提交的用户信息生成一个 Token，响应时将 Token 返回给客户端，以后客户端只需带上这个 Token 前来请求数据即可，无需再次登录验证。**

  

#### **什么是Cookie?**

> **Cookie 是由浏览器维持的，存储在客户端的一小段文本信息.伴随着用户请求和页面在 Web 服务器和浏览器之间传递。用户每次访问站点时，Web 应用程序都可以读取 cookie 包含的信息。**

- cookie 是有时间限制的，根据生命期不同分成两种：会话 cookie 和持久 cookie；

  如果不设置过期时间，则表示这个 cookie 的生命周期为从创建到浏览器关闭为止，只要关闭浏览器窗口，cookie 就消失了。这种生命期为浏览会话期的 cookie 被称为会话 cookie。会话 cookie 一般不保存在硬盘上而是保存在内存里。
  


**网络协议中的Session**

> **session，中文经常翻译为会话，其本来的含义是指有始有终的一系列动作 / 消息。比如打电话是从拿起电话拨号到挂断电话这中间的一系列过程可以称之为一个 session**
>
> **然而当 session 一词与网络协议相关联时，它又往往隐含了 “面向连接” 和 / 或 “保持状态” 这样两个含义。**
>
> **session 在 Web 开发环境下的语义又有了新的扩展，它的含义是指一类用来在客户端与服务器端之间保持状态的解决方案。有时候 Session 也用来指这种解决方案的存储结构。**

**当程序需要为某个客户端的请求创建一个 session 的时候，服务器首先检查这个客户端的请求里是否包含了一个 session 标识－称为 session id，如果已经包含一个 session id 则说明以前已经为此客户创建过 session，服务器就按照 session id 把这个 session 检索出来使用 (如果检索不到，可能会新建一个，这种情况可能出现在服务端已经删除了该用户对应的 session 对象，但用户人为地在请求的 URL 后面附加上一个 JSESSION 的参数**。



- **如果客户请求不包含 session id，则为此客户创建一个 session 并且同时生成一个与此 session 相关联的 session id，这个 session id 将在本次响应中返回给客户端保存。**
- **session 和 cookie 的目的相同，都是为了克服 http 协议无状态的缺陷。**
- **session 通过 cookie，在客户端保存 session id，而将用户的其他会话消息保存在服务端的 session 对象中**
- **cookie 需要将所有信息都保存在客户端**



#### 使用 session

>  Go 标准包没有为 session 提供任何支持，这小节我们将会自己动手来实现 go 版本的 session 管理和创建。

##### session 创建过程

> 当用户访问 Web 应用时，服务端程序会随需要创建 session，这个过程可以概括为三个步骤：

- **生成全局唯一标识符SessionId**
- **开辟数据存储空间。一般会在内存中创建相应的数据结构。**  **但这种情况下，系统一旦掉电，所有的会话数据就会丢失，如果是电子商务类网站，这将造成严重的后果。所以为了解决这类问题，你可以将会话数据写到文件里或存储在数据库中，当然这样会增加 I/O 开销，但是它可以实现某种程度的 session 持久化，也更有利于 session 的共享**

- **将 session 的全局唯一标示符发送给客户端。**

  **最关键的是如何发送这个 session 的唯一标识这一步**

**数据无非可以放到请求行、头域或 Body 里，所以一般来说会有两种常用的方式：cookie 和 URL 重写。**

1. Cookie
   服务端通过设置 Set-cookie 头就可以将 session 的标识符传送到客户端，而客户端此后的每一次请求都会带上这个标识符，
2. URL 重写
   所谓 URL 重写，就是在返回给用户的页面里的所有的 URL 后面追加 session 标识符，这样用户在收到响应之后，无论点击响应页面里的哪个链接或提交表单，都会自动带上 session 标识符，从而就实现了会话的保持。虽然这种做法比较麻烦，但是，如果客户端禁用了 cookie 的话，此种方案将会是首选。

#### 如何实现 session 管理

- **全局 session 管理器**
- **sessionid 的全局唯一性**
- **每个客户关联一个 session**
- **session 的存储 (可以存储到内存、文件、数据库等)**
- **session 过期处理**

##### **Session 管理器**

```
1.// 定义一个全局的 session 管理器

type Manager struct {
    cookieName  string     // private cookiename
    lock        sync.Mutex // protects session
    provider    Provider
    maxLifeTime int64
}

//构造函数
func NewManager(provideName, cookieName string, maxLifeTime int64) (*Manager, error) {
    provider, ok := provides[provideName]
    if !ok {
        return nil, fmt.Errorf("session: unknown provide %q (forgotten import?)", provideName)
    }
    return &Manager{provider: provider, cookieName: cookieName, maxLifeTime: maxLifeTime}, nil
}


2.// 在 main 包中创建一个全局的 session 管理器
var globalSessions *session.Manager
// 然后在 init 函数中初始化
func init() {
    globalSessions, _ = NewManager("memory", "gosessionid", 3600)
}

3.抽象出一个 Provider 接口，用以表征 session 管理器底层存储结构
//我们知道 session 是保存在服务器端的数据，它可以以任何的方式存储，比如存储在内存、数据库或者文件中。因此我们抽象出一个 Provider 接口，用以表征 session 管理器底层存储结构。

type Provider interface {
    SessionInit(sid string) (Session, error)
    SessionRead(sid string) (Session, error)
    SessionDestroy(sid string) error
    SessionGC(maxLifeTime int64)
}

// SessionInit 函数实现 Session 的初始化，操作成功则返回此新的 Session 变量
// SessionRead 函数返回 sid 所代表的 Session 变量，如果不存在，那么将以 sid 为参数调用 SessionInit 函数创建并返回一个新的 Session 变量
//SessionDestroy 函数用来销毁 sid 对应的 Session 变量
//SessionGC 根据 maxLifeTime 来删除过期的数据
```

- **设计思路：先定义好接口，然后具体的存储结构实现接口，然后注册。相应的功能就可以使用了。**

  ```
  
  var provides = make(map[string]Provider)
  
  // 根据需要注册存储 session 的结构
  func Register(name string, provider Provider){
  	 if provider == nil {
          panic("session: Register provider is nil")
      }
      if _, dup := provides[name]; dup {
          panic("session: Register called twice for provider " + name)
      }
  
      provides[name] = provider
  }
  ```

- ##### 全局唯一的 Session ID

  Session ID 是用来识别访问 Web 应用的每一个用户，因此必须保证它是全局唯一的（GUID），下面代码展示了如何满足这一需求：

  - ```
    func (manager *Manager) sessionId() string {
        b := make([]byte, 32)
        if _, err := rand.Read(b); err != nil {
            return ""
        }
        return base64.URLEncoding.EncodeToString(b)
    }
    ```

- **session 创建**

  **我们需要为每个来访用户分配或获取与他相关连的 Session**

  ```
  func (manager *Manager) SessionStart(w http.ResponseWriter, r *http.Request) (session Session) {
      manager.lock.Lock()
      defer manager.lock.Unlock()
      cookie, err := r.Cookie(manager.cookieName)
      if err != nil || cookie.Value == "" {
          sid := manager.sessionId()
          session, _ = manager.provider.SessionInit(sid)
          cookie := http.Cookie{Name: manager.cookieName, Value: url.QueryEscape(sid), Path: "/", HttpOnly: true, MaxAge: int(manager.maxLifeTime)}
          http.SetCookie(w, &cookie)
      } else {
          sid, _ := url.QueryUnescape(cookie.Value)
          session, _ = manager.provider.SessionRead(sid)
      }
      return
  }
  ```

  ```
  
  func login(w http.ResponseWriter, r *http.Request) {
      sess := globalSessions.SessionStart(w, r)
      r.ParseForm()
      if r.Method == "GET" {
          t, _ := template.ParseFiles("login.gtpl")
          w.Header().Set("Content-Type", "text/html")
          t.Execute(w, sess.Get("username"))
      } else {
          sess.Set("username", r.Form["username"])
          http.Redirect(w, r, "/", 302)
      }
  }
  ```

  ##### 操作值：设置、读取和删除

- **SessionStart 函数返回的是一个满足 Session 接口的变量，那么我们该如何用他来对 session 数据进行操作呢？**

- 上面的例子中的代码 `session.Get("uid")` 已经展示了基本的读取数据的操作，现在我们再来看一下详细的操作:

  ```
  func count(w http.ResponseWriter, r *http.Request) {
      sess := globalSessions.SessionStart(w, r)
      createtime := sess.Get("createtime")
      if createtime == nil {
          sess.Set("createtime", time.Now().Unix())
      } else if (createtime.(int64) + 360) < (time.Now().Unix()) {
          globalSessions.SessionDestroy(w, r)
          sess = globalSessions.SessionStart(w, r)
      }
      ct := sess.Get("countnum")
      if ct == nil {
          sess.Set("countnum", 1)
      } else {
          sess.Set("countnum", (ct.(int) + 1))
      }
      t, _ := template.ParseFiles("count.gtpl")
      w.Header().Set("Content-Type", "text/html")
      t.Execute(w, sess.Get("countnum"))
  }
  
  ```

  通过上面的例子可以看到，Session 的操作和操作 key/value 数据库类似: Set、Get、Delete 等操作

  > 因为 Session 有过期的概念，所以我们定义了 GC 操作，当访问过期时间满足 GC 的触发条件后将会引起 GC，但是当我们进行了任意一个 session 操作，都会对 Session 实体进行更新，都会触发对最后访问时间的修改，这样当 GC 的时候就不会误删除还在使用的 Session 实体。
  >

  - ##### session 重置

  我们知道，Web 应用中有用户退出这个操作，那么当用户退出应用的时候，我们需要对该用户的 session 数据进行销毁操作，上面的代码已经演示了如何使用 session 重置操作，下面这个函数就是实现了这个功能：

  ```
  // Destroy sessionid
  func (manager *Manager) SessionDestroy(w http.ResponseWriter, r *http.Request){
      cookie, err := r.Cookie(manager.cookieName)
      if err != nil || cookie.Value == "" {
          return
      } else {
          manager.lock.Lock()
          defer manager.lock.Unlock()
          manager.provider.SessionDestroy(cookie.Value)
          expiration := time.Now()
          cookie := http.Cookie{Name: manager.cookieName, Path: "/", HttpOnly: true, Expires: expiration, MaxAge: -1}
          http.SetCookie(w, &cookie)
      }
  }
  ```

  - ##### session 销毁

我们来看一下 Session 管理器如何来管理销毁，只要我们在 Main 启动的时候启动：

```go

func init() {
    go globalSessions.GC()
}

func (manager *Manager) GC() {
    manager.lock.Lock()
    defer manager.lock.Unlock()
    manager.provider.SessionGC(manager.maxLifeTime)
    time.AfterFunc(time.Duration(manager.maxLifeTime), func() { manager.GC() })
}


```

##### session 存储

定义了存储 session 的接口，具体存储的函数是怎么写的？

```
package memory

import (
    "container/list"
    "github.com/astaxie/session"
    "sync"
    "time"
)

var pder = &Provider{list: list.New()}

type SessionStore struct {
    sid          string                      // session id唯一标示
    timeAccessed time.Time                   // 最后访问时间
    value        map[interface{}]interface{} // session里面存储的值
}

func (st *SessionStore) Set(key, value interface{}) error {
    st.value[key] = value
    pder.SessionUpdate(st.sid)
    return nil
}

func (st *SessionStore) Get(key interface{}) interface{} {
    pder.SessionUpdate(st.sid)
    if v, ok := st.value[key]; ok {
        return v
    } else {
        return nil
    }
}

func (st *SessionStore) Delete(key interface{}) error {
    delete(st.value, key)
    pder.SessionUpdate(st.sid)
    return nil
}

func (st *SessionStore) SessionID() string {
    return st.sid
}

```

```
type Provider struct {
    lock     sync.Mutex               // 用来锁
    sessions map[string]*list.Element // 用来存储在内存
    list     *list.List               // 用来做 gc
}

func (pder *Provider) SessionInit(sid string) (session.Session, error) {
    pder.lock.Lock()
    defer pder.lock.Unlock()
    v := make(map[interface{}]interface{}, 0)
    newsess := &SessionStore{sid: sid, timeAccessed: time.Now(), value: v}
    element := pder.list.PushFront(newsess)
    pder.sessions[sid] = element
    return newsess, nil
}

func (pder *Provider) SessionRead(sid string) (session.Session, error) {
    if element, ok := pder.sessions[sid]; ok {
        return element.Value.(*SessionStore), nil
    } else {
        sess, err := pder.SessionInit(sid)
        return sess, err
    }
    return nil, nil
}

func (pder *Provider) SessionDestroy(sid string) error {
    if element, ok := pder.sessions[sid]; ok {
        delete(pder.sessions, sid)
        pder.list.Remove(element)
        return nil
    }
    return nil
}
func (pder *Provider) SessionGC(maxlifetime int64) {
    pder.lock.Lock()
    defer pder.lock.Unlock()

    for {
        element := pder.list.Back()
        if element == nil {
            break
        }
        if (element.Value.(*SessionStore).timeAccessed.Unix() + maxlifetime) < time.Now().Unix() {
            pder.list.Remove(element)
            delete(pder.sessions, element.Value.(*SessionStore).sid)
        } else {
            break
        }
    }
}
func (pder *Provider) SessionUpdate(sid string) error {
    pder.lock.Lock()
    defer pder.lock.Unlock()
    if element, ok := pder.sessions[sid]; ok {
        element.Value.(*SessionStore).timeAccessed = time.Now()
        pder.list.MoveToFront(element)
        return nil
    }
    return nil
}

func init() {
    pder.sessions = make(map[string]*list.Element, 0)
    session.Register("memory", pder)
}
上面这个代码实现了一个内存存储的 session 机制。通过 init 函数注册到 session 管理器中。这样就可以方便的调用了。我们如何来调用该引擎呢？请看下面的代码

import (
    "github.com/astaxie/session"
    _ "github.com/astaxie/session/providers/memory"
)

当 import 的时候已经执行了 memory 函数里面的 init 函数，这样就已经注册到 session 管理器中，我们就可以使用了，通过如下方式就可以初始化一个 session 管理器：

var globalSessions *session.Manager

// 然后在 init 函数中初始化
func init() {
    globalSessions, _ = session.NewManager("memory", "gosessionid", 3600)
    go globalSessions.GC()
}

```

### 预防 session 劫持

##### session 劫持过程

我们写了如下的代码来展示一个 count 计数器：

```
func count(w http.ResponseWriter, r *http.Request) {
    sess := globalSessions.SessionStart(w, r)
    ct := sess.Get("countnum")
    if ct == nil {
        sess.Set("countnum", 1)
    } else {
        sess.Set("countnum", (ct.(int) + 1))
    }
    t, _ := template.ParseFiles("count.gtpl")
    w.Header().Set("Content-Type", "text/html")
    t.Execute(w, sess.Get("countnum"))
}
count.gtpl 的代码如下所示：
Hi. Now count:{{.}}
```

**可以看到虽然换了浏览器，但是我们却获得了 sessionID，然后模拟了 cookie 存储的过程。这个例子是在同一台计算机上做的，不过即使换用两台来做，其结果仍然一样。此时如果交替点击两个浏览器里的链接你会发现它们其实操纵的是同一个计数器。**

**不必惊讶，此处 firefox 盗用了 chrome 和 goserver 之间的维持会话的钥匙，即 gosessionid，这是一种类型的 “会话劫持”。简单来说就是：在 goserver 看来，它从 http 请求中得到了一个 gosessionid，由于 HTTP 协议的无状态性，它无法得知这个 gosessionid 是从 chrome 那里 “劫持” 来的，它依然会去查找对应的 session，并执行相关计算。与此同时 chrome 也无法得知自己保持的会话已经被 “劫持”。**

##### session 劫持防范

