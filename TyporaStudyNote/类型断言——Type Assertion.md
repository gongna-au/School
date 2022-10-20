# 类型断言——Type Assertion



## Type Assertion

Type Assertion（中文名叫：类型断言），通过它可以做到以下几件事情

1. 检查 `i` 是否为 nil

2. 检查 `i` 存储的值是否为某个类型

   具体的使用方式有两种：

```
t := i.(T)
```

**这个表达式可以断言一个接口对象（i）里不是 nil，并且接口对象（i）存储的值的类型是 T，如果断言成功，就会返回值给 t，如果断言失败，就会触发 panic**

```
package main

import "fmt"

func main() {
    var i interface{} = 10
    t1 := i.(int)
    fmt.Println(t1)

    fmt.Println("=====分隔线=====")

    t2 := i.(string)
    fmt.Println(t2)
}

```

**如果要断言的接口值是 nil，那我们来看看也是不是也如预期一样会触发panic**

```
package main

func main() {
    var i interface{} // nil
    var _ = i.(interface{})
}
```

输出如下，确实是会 触发 panic

```
panic: interface conversion: interface is nil, not interface {}

goroutine 1 [running]:
main.main()
        E:/GoPlayer/src/main.go:5 +0x34
exit status 2
```

**第二种**

```
t, ok:= i.(T)
```

和上面一样，这个表达式也是可以断言一个接口对象（i）里不是 nil，并且接口对象（i）存储的值的类型是 T，如果断言成功，就会返回其值给 t，并且此时 ok 的值 为 true，表示断言成功。

如果接口值的类型，并不是我们所断言的 T，就会断言失败，但和第一种表达式不同的事，这个不会触发 panic，而是将 ok 的值设为 false ，表示断言失败，此时**t 为 T 的零值。**

```
package main

import "fmt"

func main() {
    var i interface{} = 10
    t1, ok := i.(int)
    fmt.Printf("%d-%t\n", t1, ok)

    fmt.Println("=====分隔线1=====")

    t2, ok := i.(string)
    fmt.Printf("%s-%t\n", t2, ok)

    fmt.Println("=====分隔线2=====")

    var k interface{} // nil
    t3, ok := k.(interface{})
    fmt.Println(t3, "-", ok)

    fmt.Println("=====分隔线3=====")
    k = 10
    t4, ok := k.(interface{})
    fmt.Printf("%d-%t\n", t4, ok)

    t5, ok := k.(int)
    fmt.Printf("%d-%t\n", t5, ok)
}
```

运行后输出如下，可以发现在执行第二次断言的时候，虽然失败了，但并没有触发了 panic。

```
10-true
=====分隔线1=====
-false
=====分隔线2=====
<nil> - false
=====分隔线3=====
10-true
10-true
```

上面这段输出，你要注意的是第二个断言的输出在`-false` 之前并不是有没有输出任何 t2 的值，而是由于断言失败，所以 t2 得到的是 string 的零值也是 `""` ，它是零长度的，所以你看不到其输出。

## Type Switch

```
package main

import "fmt"

func findType(i interface{}) {
    switch x := i.(type) {
    case int:
        fmt.Println(x, "is int")
    case string:
        fmt.Println(x, "is string")
    case nil:
        fmt.Println(x, "is nil")
    default:
        fmt.Println(x, "not type matched")
    }
}

func main() {
    findType(10)      // int
    findType("hello") // string

    var k interface{} // nil
    findType(k)

    findType(10.23) //float64
}
输出如下

10 is int
hello is string
<nil> is nil
10.23 not type matched
```

- 如果你的值是 nil，那么匹配的是 `case nil`
- 如果你的值在 switch-case 里并没有匹配对应的类型，那么走的是 default 分支

**类型断言完成后，实际上会返回静态类型为你断言的类型的对象**而要清楚原来的静态类型为空接口类型（interface{}），这是 Go 的隐式转换。

类型断言，仅能对静态类型为空接口（interface{}）的对象进行断言，否则会抛出错误，具体内容可以参考：[关于接口的三个“潜规则”](http://golang.iswbm.com/en/latest/c02/c02_07.html)



# 学习接口：Go 语言中的空接口

## 1. 什么是空接口？

空接口是特殊形式的接口类型，普通的接口都有方法，而空接口没有定义任何方法口，也因此，我们可以说**所有类型都至少实现了空接口。**

```
type empty_iface interface {
}
```

每一个接口都包含两个属性，一个是值，一个是类型。

## 2. 如何使用空接口？

- **第一**，通常我们会直接使用 `interface{}` 作为类型声明一个实例，而这个实例可以承载任意类型的值。

```
package main

import (
    "fmt"
)

func main()  {
    // 声明一个空接口实例
    var i interface{}

    // 存 int 没有问题
    i = 1
    fmt.Println(i)

    // 存字符串也没有问题
    i = "hello"
    fmt.Println(i)

    // 存布尔值也没有问题
    i = false
    fmt.Println(i)
}
```

- **第二**，如果想让你的函数可以接收任意类型的值 ，也可以使用空接口

```
接收一个任意类型的值 示例


package main

import (
    "fmt"
)

func myfunc(iface interface{}){
    fmt.Println(iface)
}

func main()  {
    a := 10
    b := "hello"
    c := true

    myfunc(a)
    myfunc(b)
    myfunc(c)
}
```

接收任意个任意类型的值 示例

```
package main

import (
    "fmt"
)

func myfunc(ifaces ...interface{}){
    for _,iface := range ifaces{
        fmt.Println(iface)
    }
}

func main()  {
    a := 10
    b := "hello"
    c := true

    myfunc(a, b, c)
}
```

- **第三**，你也定义一个可以接收任意类型的 array、slice、map、strcut，例如这边定义一个切片

```
package main

import "fmt"

func main() {
    any := make([]interface{}, 5)
    any[0] = 11
    any[1] = "hello world"
    any[2] = []int{11, 22, 33, 44}
    for _, value := range any {
        fmt.Println(value)
    }
}
```

## 3. 空接口几个要注意的坑

**坑1**：空接口可以承载任意值，但不代表任意类型就可以承接空接口类型的值

从实现的角度看，任何类型的值都满足空接口。因此空接口类型可以保存任何值，也可以从空接口中取出原值。

但要是你**把一个空接口类型的对象，再赋值给一个固定类型（比如 int, string等类型）的对象赋值，是会报错的。**

```
package main

func main() {
    // 声明a变量, 类型int, 初始值为1
    var a int = 1

    // 声明i变量, 类型为interface{}, 初始值为a, 此时i的值变为1
    var i interface{} = a

    // 声明b变量, 尝试赋值i
    var b int = i
}
```

**坑2：**：当空接口承载数组和切片后，该对象无法再进行切片

```
package main

import "fmt"

func main() {
    sli := []int{2, 3, 5, 7, 11, 13}

    var i interface{}
    i = sli

    g := i[1:3]
    fmt.Println(g)
}
```

**坑3**：当你使用空接口来接收任意类型的参数时，它的静态类型是 interface{}，但动态类型（是 int，string 还是其他类型）我们并不知道，因此需要使用类型断言。

```
package main

import (
    "fmt"
)

func myfunc(i interface{})  {

    switch i.(type) {
    case int:
        fmt.Println("参数的类型是 int")
    case string:
        fmt.Println("参数的类型是 string")
    }
}

func main() {
    a := 10
    b := "hello"
    myfunc(a)
    myfunc(b)
}
```

#  学习接口：接口的三个“潜规则”

## 1. 对方法的调用限制

接口是一组固定的方法集，由于静态类型的限制，接口变量有时仅能调用其中特定的一些方法。

```
package main

import "fmt"

type Phone interface {
    call()
}

type iPhone struct {
    name string
}

func (phone iPhone)call()  {
    fmt.Println("Hello, iPhone.")
}

func (phone iPhone)send_wechat()  {
    fmt.Println("Hello, Wechat.")
}

func main() {
    var phone Phone
    // phone对象显示声明为 Phone 接口类型,也就是phone只能调用该接口下的方法，即便它被某种具体类型赋值
    phone = iPhone{name:"ming's iphone"}
    phone.call()
    phone.send_wechat()
}
```

我定义了一个 Phone 的接口，只要求实现 call 方法即可，也就是只要能打电话的设备就是一个电话（好像是一句没用的废话）。

然后再定义了一个 iPhone 的结构体，该结构体接收两个方法，一个是打电话（ call 函数），一个是发微信（send_wechat 函数）。

最后一步是关键，我们定义了一个 Phone 接口类型的 phone 对象，该对象的内容是 iPhone 结构体。然后我们调用该对象的 call 方法，一切正常。

但是当你调用 `phone.send_wechat`方法，程序会报错，提示我们 Phone 类型的方法没有 send_wechat 的字段或方法。

```
# command-line-arguments
./demo.go:30:10: phone.send_wechat undefined (type Phone has no field or method send_wechat)
```

原因也很明显，**因为我们的phone对象显示声明为 Phone 接口类型，因此 phone调用的方法会受到此接口的限制。**

**那么如何让 phone 可以调用 send_wechat 方法呢？**

答案是可以不显示的声明为 Phone接口类型 ，但要清楚 phone 对象实际上是隐式的实现了 Phone 接口，如此一来，方法的调用就不会受到接口类型的约束。

```
func main() {
    phone := iPhone{name:"ming's iphone"}
    phone.call()
    phone.send_wechat()
}
运行后，一切正常，没有报错。

Hello, iPhone.
Hello, Wechat.
```

## 2. 调用函数时的隐式转换

Go 语言中的函数调用都是值传递的，变量会在方法调用前进行类型转换。

```
func printType(i interface{})  {

    switch i.(type) {
    case int:
        fmt.Println("参数的类型是 int")
    case string:
        fmt.Println("参数的类型是 string")
    }
}

func main() {
    a := 10
    printType(a)
}
如果你运行后，会发现一切都很正常

参数的类型是 int
```

但是如果你把函数内的内容搬到到外面来

```
package main

import "fmt"


func main() {
    a := 10

    switch a.(type) {
    case int:
        fmt.Println("参数的类型是 int")
    case string:
        fmt.Println("参数的类型是 string")
    }
}
```

**当一个函数接口 interface{} 空接口类型时，我们说它可以接收什么任意类型的参数（江湖上称之为无招胜有招）。**当你使用这种写法时，Go 会默默地为我们做一件事，就是把传入函数的参数值（注意：Go 语言中的函数调用都是值传递的）的类型隐式的转换成 interface{} 类型。

### 如何进行接口类型的显示转换

上面了解了函数中 接口类型的隐式转换后，你的心里可能开始有了疑问了，难道我使用类型断言，只能通过一个接收空接口类型的函数才能实现吗？

答案当然是 No.

如果你想手动对其进行类型转换，可以像下面这样子，就可以将变量 a 的静态类型转换为 interface{} 类型然后赋值给 b （此时 a 的静态类型还是 int，而 b 的静态类型为 interface{}）

```
var a int = 25
b := interface{}(a)
// 对a进行空接口类型的显示转化
```

```
package main

import "fmt"


func main() {
    a := 10

    switch interface{}(a).(type) {
    case int:
        fmt.Println("参数的类型是 int")
    case string:
        fmt.Println("参数的类型是 string")
    }
}
```

## 3. 类型断言中的隐式转换

上面我们知道了，只有**静态类型**为接口类型的对象才可以进行类型断言。

**go语言里的静态类型与动态类型分析：**

**我们在给 `i` 声明了 `interface{}` 类型，所以 `i` 的静态类型就是 `interface{}` **

**当我们给变量 `i` 赋一个 int 类型的值时，它的静态类型还是 interface{}，这是不会变的，但是它的动态类型此时变成了 int 类型。**

**接口组成：**

每个接口变量，实际上都是由一 pair 对（type 和 data）组合而成，pair 对中记录着实际变量的值和类型。

比如下面这条语句

```go
var age int = 25
```

**接口细分:**
根据接口是否包含方法，可以将接口分为 `iface` 和 `eface`

### iface

第一种：**iface**，表示带有一组方法的接口。

比如

```go
type Phone interface {
   call()
}
```

### eface

第二种：**eface**，表示不带有方法的接口

比如

```go
var i interface{} 
```



而当类型断言完成后，会返回一个静态类型为你断言的类型的对象，也就是说，当我们使用了类型断言，Go 实际上又会默认为我们进行了一次隐式的类型转换。

验证方法也很简单，使用完一次类型断言后，对返回的对象再一次使用类型断言，Goland 立马就会提示我们新对象 b 不是一个接口类型的对象，不允许进行类型断言

# 学习反射：反射三定律

## 1. 真实世界与反射世界

在本篇文章里，为了区分反射前后的变量值类型，我将反射前环境称为 **真实世界**，而将反射后的环境称为 **反射世界**。这种比喻不严谨，但是对于我理解是有帮助的，也希望对你有用。

在反射的世界里，我们拥有了获取一个对象的类型，属性及方法的能力。

![image1](http://image.iswbm.com/20200614174556.png)

## 2. 两种类型：Type 和 Value

在 Go 反射的世界里，有两种类型非常重要，是整个反射的核心，在学习 reflect 包的使用时，先得学习下这两种类型：

1. reflect.Type
2. reflect.Value

它们分别对应着真实世界里的 type 和 value，只不过在反射对象里，它们拥有更多的内容。

**通过上一节的内容（[关于接口的三个 『潜规则』](http://golang.iswbm.com/en/latest/c02/c02_07.html)），我们知道了一个接口变量，实际上都是由一 pair 对（type 和 data）组合而成，pair 对中记录着实际变量的值和类型。也就是说在真实世界里，type 和 value 是合并在一起组成 接口变量的。**

## 3. 解读反射的三大定律

翻译一下，就是：

1. 反射可以将接口类型变量 转换为“反射类型对象”；
2. 反射可以将 “反射类型对象”转换为 接口类型变量；
3. 如果要修改 “反射类型对象” 其类型必须是 可写的；

### 第一定律

为了实现从接口变量到反射对象的转换，需要提到 reflect 包里很重要的两个方法：

1. reflect.TypeOf(i) ：获得接口值的类型
2. reflect.ValueOf(i)：获得接口值的值

这两个方法返回的对象，我们称之为反射对象：Type object 和 Value object。

<img src="http://image.iswbm.com/image-20200614175219320.png" alt="golang reflection" style="zoom:200%;" />

```
package main

import (
"fmt"
"reflect"
)

func main() {
    var age interface{} = 25

    fmt.Printf("原始接口变量的类型为 %T，值为 %v \n", age, age)

    t := reflect.TypeOf(age)
    v := reflect.ValueOf(age)

    // 从接口变量到反射对象
    fmt.Printf("从接口变量到反射对象：Type对象的类型为 %T \n", t)
    fmt.Printf("从接口变量到反射对象：Value对象的类型为 %T \n", v)

}

原始接口变量的类型为 int，值为 25
从接口变量到反射对象：Type对象的类型为 *reflect.rtype
从接口变量到反射对象：Value对象的类型为 reflect.Value
```

如此我们完成了从接口类型变量到反射对象的转换。

关于这点，其实在上一节（[关于接口的三个 『潜规则』](http://golang.iswbm.com/en/latest/c02/c02_07.html)）已经提到过了，由于 TypeOf 和 ValueOf 两个函数接收的是 interface{} 空接口类型，而 Go 语言函数都是值传递，因此Go语言会将我们的类型隐式地转换成接口类型。

### 第二定律

> Reflection goes from reflection object to interface value.

和第一定律刚好相反，第二定律描述的是，从反射对象到接口变量的转换

![golang reflection](http://image.iswbm.com/image-20200614175325721.png)

通过源码可知， reflect.Value 的结构体会接收 `Interface` 方法，返回了一个 `interface{}` 类型的变量（**注意：只有 Value 才能逆向转换，而 Type 则不行，这也很容易理解，如果 Type 能逆向，那么逆向成什么呢？**）

```
// Interface returns v's current value as an interface{}.
// It is equivalent to:
//  var i interface{} = (v's underlying value)
// It panics if the Value was obtained by accessing
// unexported struct fields.
func (v Value) Interface() (i interface{}) {
    return valueInterface(v, true)
}
```

这个函数就是我们用来实现将反射对象转换成接口变量的一个桥梁。

例子如下

```
package main

import (
"fmt"
"reflect"
)

func main() {
    var age interface{} = 25

    fmt.Printf("原始接口变量的类型为 %T，值为 %v \n", age, age)

    t := reflect.TypeOf(age)
    v := reflect.ValueOf(age)

    // 从接口变量到反射对象
    fmt.Printf("从接口变量到反射对象：Type对象的类型为 %T \n", t)
    fmt.Printf("从接口变量到反射对象：Value对象的类型为 %T \n", v)

    // 从反射对象到接口变量
    i := v.Interface()
    fmt.Printf("从反射对象到接口变量：新对象的类型为 %T 值为 %v \n", i, i)

}
```

输出如下

```
原始接口变量的类型为 int，值为 25
从接口变量到反射对象：Type对象的类型为 *reflect.rtype
从接口变量到反射对象：Value对象的类型为 reflect.Value
从反射对象到接口变量：新对象的类型为 int 值为 25
```

```
i := v.Interface().(int)
```

### 第三定律

反射世界是真实世界的一个『映射』，是我的一个描述，但这并不严格，因为并不是你在反射世界里所做的事情都会还原到真实世界里。

第三定律引出了一个 `settable` （可设置性，或可写性）的概念。

其实早在以前的文章中，我们就一直在说，Go 语言里的函数都是值传递，只要你传递的不是变量的指针，你在函数内部对变量的修改是不会影响到原始的变量的。

回到反射上来，当你使用 reflect.Typeof 和 reflect.Valueof 的时候，如果传递的不是接口变量的指针，反射世界里的变量值始终将只是真实世界里的一个拷贝，你对该反射对象进行修改，并不能反映到真实世界里。

因此在反射的规则里:

- 不是接收变量指针创建的反射对象，是不具备『**可写性**』的
- 是否具备『**可写性**』，可使用 `CanSet()` 来获取得知
- 对不具备『**可写性**』的对象进行修改，是没有意义的，也认为是不合法的，因此会报错。

```
package main

import (
    "fmt"
    "reflect"
)

func main() {
    var name string = "Go编程时光"

    v := reflect.ValueOf(name)
    fmt.Println("可写性为:", v.CanSet())
}
```

输出如下

```
可写性为: false
```

要让反射对象具备可写性，需要注意两点

1. 创建反射对象时传入变量的指针
2. **使用 `Elem()`函数返回指针指向的数据**

```
package main

import (
    "fmt"
    "reflect"
)

func main() {
    var name string = "Go编程时光"
    v1 := reflect.ValueOf(&name)
    fmt.Println("v1 可写性为:", v1.CanSet())

    v2 := v1.Elem()
    fmt.Println("v2 可写性为:", v2.CanSet())
}
```

知道了如何使反射的世界里的对象具有可写性后，接下来是时候了解一下如何对修改更新它。

反射对象，都会有如下几个以 `Set` 单词开头的方法

<img src="http://image.iswbm.com/image-20200614161613417.png" alt="image3" style="zoom:200%;" />

这些方法就是我们修改值的入口

```
package main

import (
    "fmt"
    "reflect"
)

func main() {
    var name string = "Go编程时光"
    fmt.Println("真实世界里 name 的原始值为：", name)

    v1 := reflect.ValueOf(&name)
    v2 := v1.Elem()

    v2.SetString("Python编程时光")
    fmt.Println("通过反射对象进行更新后，真实世界里 name 变为：", name)
}
```

