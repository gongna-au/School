# 命令行参数的解析：flag 库详解

在 Golang 程序中有很多种方法来处理命令行参数

简单的情况下可以不使用任何库，直接使用 `os.Args`

```
package main

import (
    "fmt"
    "os"
)

func main() {
    //os.Args是一个[]string
    if len(os.Args) > 0 {
        for index, arg := range os.Args {
            fmt.Printf("args[%d]=%v\n", index, arg)
        }
    }
}
```

试着运行一下，第一个参数是执行文件的路径。

```
$ go run demo.go hello world hello golang
args[0]=/var/folders/72/lkr7ltfd27lcf36d75jdyjr40000gp/T/go-build187785213/b001/exe/demo
args[1]=hello
args[2]=world
args[3]=hello
args[4]=golang
```

## 1. 参数种类

根据参数是否为布尔型，可以分为两种：

- 布尔型参数：如 `--debug`，后面不用再接具体的值，指定就为 True，不指定就为 False非布尔型参数
- 非布尔型参数：非布尔型，有可能是int，string 等其他类型，如 `--name jack` ，后面可以接具体的参数值

根据参数名的长短，还可以分为：

- 长参数：比如 `--name jack` 就是一个长参数，参数名前有两个 `-`
- 短参数：通常为一个或两个字母（是对应长参数的简写），比如 `-n` ，参数名前只有一个 `-`

## 2. 入门示例

我先用一个字符串类型的参数的示例，抛砖引玉

```
package main

import (
    "flag"
    "fmt"
)

func main(){
    var name string
    flag.StringVar(&name, "name", "jack", "your name")

flag.Parse()  // 解析参数
    fmt.Println(name)
}

```

`flag.StringVar` 定义了一个字符串参数，它接收几个参数

- 第一个参数 ：接收值后，存放在哪个变量里，需为指针
- 第二个参数 ：在命令行中使用的参数名，比如 `--name jack` 里的 name
- 第三个参数 ：若命令行中未指定该参数值，那么默认值为 `jack`
- 第四个参数：记录这个参数的用途或意义

运行以上程序，输出如下

```
$ go run demo.go
jack

$ go run demo.go --name wangbm
wangbm
```

## 3. 改进一下

如果你的程序只接收很少的几个参数时，上面那样写也没有什么问题。

但一旦参数数量多了以后，一大堆参数解析的代码堆积在 main 函数里，影响代码的可读性、美观性。

建议将参数解析的代码放入 `init` 函数中，`init` 函数会先于 `main` 函数执行。

```
package main

import (
    "flag"
    "fmt"
)

var name string

func init()  {
    flag.StringVar(&name, "name", "jack", "your name")
}

func main(){
    flag.Parse()
    fmt.Println(name)
}
```

## 4. 参数类型

当你在命令行中指定了参数，Go 如何解析这个参数，转化成何种类型，是需要你事先定义的。

不同的参数，对应着 `flag` 中不同的方法。

下面分别讲讲不同的参数类型，都该如何定义。

### 布尔型

**实现效果**：当不指定 `--debug` 时，debug 的默认值为 false，你一指定 `--debug`，debug 为赋值为 true。

```
ar debug bool

func init()  {
    flag.BoolVar(&debug, "debug", false, "是否开启 DEBUG 模式")
}

func main(){
    flag.Parse()
    fmt.Println(debug)
}
```

运行后，执行结果如下

```
$ go run main.go
false

$ go run main.go --debug
true
```

### 数值型

定义一个 age 参数，不指定默认为 18

```
var age int

func init()  {
    flag.IntVar(&age, "age", 18, "你的年龄")
}

func main(){
    flag.Parse()
    fmt.Println(age)
}
```

运行后，执行结果如下

```
$ go run main.go
18

$ go run main.go --age 20
20
```

### 字符串

定义一个 name参数，不指定默认为 jack

```
var name string

func init()  {
    flag.StringVar(&name, "name", "jack", "你的名字")
}

func main(){
    flag.Parse()
    fmt.Println(name)
}
```

运行后，执行结果如下

```
$ go run main.go
jack

$ go run main.go --name wangbm
wangbm
```

### 时间类型

定义一个 interval 参数，不指定默认为 1s

```
var interval time.Duration

func init()  {
    flag.DurationVar(&interval, "interval", 1 * time.Second, "循环间隔")
}

func main(){
    flag.Parse()
    fmt.Println(interval)
}
```

## 5. 自定义类型

flag 包支持的类型有 Bool、Duration、Float64、Int、Int64、String、Uint、Uint64。

这些类型的参数被封装到其对应的后端类型中，比如 Int 类型的参数被封装为 intValue，String 类型的参数被封装为 stringValue。

这些后端的类型都实现了 flag.Value 接口，因此可以把一个命令行参数抽象为一个 Flag 类型的实例。下面是 Value 接口和 Flag 类型的代码：

```
type Value interface {
    String() string
    Set(string) error
}

// Flag 类型
type Flag struct {
    Name     string // name as it appears on command line
    Usage    string // help message
    Value    Value  // value as set 是个 interface，因此可以是不同类型的实例。
    DefValue string // default value (as text); for usage message
}

func Var(value Value, name string, usage string) {
    CommandLine.Var(value, name, usage)
}
```

想要实现自定义类型的参数，其实只要 Var 函数的第一个参数对象实现 flag.Value接口即可

```
type sliceValue []string


func newSliceValue(vals []string, p *[]string) *sliceValue {
    *p = vals
    return (*sliceValue)(p)
}

func (s *sliceValue) Set(val string) error {
         // 如何解析参数值
    *s = sliceValue(strings.Split(val, ","))
    return nil
}

func (s *sliceValue) String() string {
    return strings.Join([]string(*s), ",")
}
```

比如我想实现如下效果，传入的参数是一个字符串，以逗号分隔，flag 的解析时将其转成 slice。

```
$ go run demo.go -members "Jack,Tom"
[Jack Tom]
```

那我可以这样子编写代码

```
var members []string
type sliceValue []string


func newSliceValue(vals []string, p *[]string) *sliceValue {
    *p = vals
    return (*sliceValue)(p)
}

func (s *sliceValue) Set(val string) error {
         // 如何解析参数值
    *s = sliceValue(strings.Split(val, ","))
    return nil
}


func (s *sliceValue) String() string {
    return strings.Join([]string(*s), ",")
}

func init()  {
    flag.Var(newSliceValue([]string{}, &members), "members", "会员列表")
}

func main(){
    flag.Parse()
    fmt.Println(members)
}
```

```



type sliceValue []string 

func (val []string,p *[]string)*sliceValue{
*p=val
return (*sliceValue)p
}
```

