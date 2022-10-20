# AOP

AOP（Aspect Oriented Programming），即面向切面编程

- 其主要作用是，在不修改源代码的情况下给某个或者一组操作添加额外的功能。
- 像日志记录，事务处理，权限控制等功能，都可以用AOP来“优雅”地实现，使这些额外功能和真正的业务逻辑分离开来，软件的结构将更加清晰。
- **最关键的点在于：你写的像日志记录，事务处理，权限控制等功能要能动态的感知业务函数执行到了哪里，然后在业务函数执行前，执行完，或者在执行中需要调用我们写的这些动态的功能。**比如我们要向在这个业务逻辑方法运行前，运行结束时，方法出现异常时都将日志文件打印。

```
//用go实现就是先写一个结构体
//然后结构体下面是几个函数
分别是：
前置通知 LogStart() 在目标方法运行之前运行
后置通知 logEnd()  在目标方法运行结束之后运行
返回通知 logReturn() 在目标方法运行正常返回之后运行
异常通知 logException() 在目标方法出现异常之后运行
环绕通知 动态代理，手动推进目标方法运行
type LogFunc func (joinPoint JoinPoint,others interface{})

//说明：JoinPoint是一个结构体，这个结构体首先已经保存好了我们需要的信息，然后这个结构体有一些无参的方法，我们可以调用这些方法得到我们需要的信息
type Log struct{
	logStart  LogFunc
	logEnd    LogFunc
	logReturn LogFunc
	logException LogFunc
}
func logStart (joinPoint JoinPoint, others interface{}){
	fmt.Println(others)
	//也可以不处理
	//fmt.Println(others)
 	methodName := joinPoint.getSignature().getName()
  	args := joinPoint.getArgs()
  	fmt.Println("[Before]...方法名{",methodName,"}参数列表是:{",args,"}")
  	fmt.Println(args)
}

func logEnd (joinPoint JoinPoint，others interface{}){
	fmt.Println(others)
	fmt.Println("[After]...{"+joinPoint.getSignature().getName()+"}结束...")
}
func logReturn(joinPoint JoinPoint，others interface{}){
	fmt.Println(others)
	fmt.Println("[AfterReturning]...{"+joinPoint.getSignature().getName()+"}正常返回，运行结果是{"+result+"}")

}
func logException(joinPoint JoinPoint,err interface{}){
	fmt.Println()
    fmt.Println( "[AfterErr]...{", joinPoint.getSignature().getName(), "}\n",err)
    }


```

```
//Java 内置了丰富的容器类，不同容器用于处理各种业务场景
Go 提供的基本容器主要有6个：
map: 关联容器
slice： 动态扩容的顺序容器
channels：队列
container标准库（pkg/container
list：链表容器
ring：循环链表容器
heap： 堆容器，提供 heap 的实现
slice 、map 和 channel 是 Go 最常见、也是内置的容器数据结构，其他容器都在标准库的 container 包下。在使用 container 三个容器的时候，不必再费心实现数据结构相关的算法。同时，因为container 提供的容器支持的入参类型都是 interface{}， 所以只要实现了容器的 interface, 就可以处理任何类型的值。

```

```
//再写个结构体
type MainConfigOfAop struct{
	
}
func NewMainConfigOfAop() *MainConfigOfAop{
	return &MainConfigOfAop{
		
	}
}
```

