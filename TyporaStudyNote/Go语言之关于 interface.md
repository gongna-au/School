# Go语言之关于 interface

### 1. Go 语言与鸭子类型的关系

所谓的 **鸭子类型就是动态编程语言对对象的一种推断策略，关注的是这个对象如何去使用，而不是这个对象的类型。**go语言是静态语言，但是通过接口完美的支持了鸭子类型。就是说：某个类型看起来像个鸭子（像鸭子一样嘎嘎叫，像鸭子一样游泳。）那么它就是鸭子类型。

在动态语言python中,我们定义了一个函数hello_world,这个函数里可以传入任意类型，只要这个类型实现了say_hello()函数就可以。

```python
def hello_world(coder):
    coder.say_hello()
```

**当调用此函数的时候，可以传入任意类型，只要它实现了 `say_hello()` 函数就可以。如果没有实现，运行过程中会出现错误。**

而在静态语言如 Java, C++ 中，必须要显示地声明某个类型实现了某个接口，之后，然后这个类型才能被你拿来用在你想用的地方（这里你想用的地方指的是：哪些使用了该接口作为参数的函数）。如果我在程序中调用这个hello_world这个函数，却传进去的是一个没有实现say_hello()方法的参数，那么程序就会报错，在编译阶段就不会通过。这也是静态语言比动态语言更安全的原因之一。**静态语言在编译期间就能发现类型不匹配的错误。而动态语言只有等到程序运行到那一行代码才会报错。**而且 **静态语言要求程序员在编码阶段按照既定的规则来写，为每一个变量规定它的数据类型。**

**Go 采用了折中的做法：不要求类型显示地声明实现了某个接口，只要实现了相关的方法即可，编译器就能检测到，并判断出你的这个变量的类型。**

看一个例子：我们先定义一个接口，使用这个接口作为参数的函数

```
type IGreeting interface{
	sayHello()
}

func Hello(i IGreeting){
	i.sayHello()
}

```

再来定义两个结构体：

```
type Go struct{
}

func （g Go） sayHello（）{
	fmt.Println("Hi  I am GO! ")
}

type PHP struct {

}
func (p PHP) sayHello(){
	fmt.Println("Hi  I am PHP! ")
}

```

在main函数里调用Hello（）函数

```
func main（）{
	go=Go{}
	php=PHP{}
	Hello(go)
	Hello(php)
}
```

程序输出：

```
Hi, I am GO!
Hi, I am PHP!
```

**当我们定义的具体类型，在实现接口时（就是实现接口所规定的行为时，我们在行为内部（函数内部）可以有自己的逻辑，不同的类型可以有不同的逻辑，具体看你的需求是什么）在这里：1.我们Hello函数的逻辑是——传入的类型进行它的行为（在代码上体现的就是，调用该类型的函数）**

```
	再举个例子：现在有一个具体的场景，有很多不同类型的结构体（数据）都需要你要实现拿到数据，打印数据，修改数据这三个功能，
	那么我可以写个总的函数DealWith（这里一定是一个接口类型）
	那么先定义一个接口类型 
	type DataIHave interface{
    	Get() 
        Print()
        Change()
    } 
    
    //写我们总的函数
    func DealWith（ d DataIHave ,string ）{
    	//这里面就是我们具体对那些不同的结构体操作的逻辑
    	d.Get() 
    	d.Print()
    	d.Change(string)
    }
    
    //然后才是我们具体的类型去按照自己的需要去实现接口的函数
    type Person struct{
    	Name   string
    	Age    int
   
    }
    
    func ( p Person) Get(){
    	fmt.Print("已经拿到数据")
    	
   
    }
    
    func ( p Person) Print(){
    	fmt.Println(d)
    }
    
    func ( p Person) Change(name string)(){
    	p.Age=name
    }
    
    
    
    type Company struct{
    	Address string
    	MarketValue  int //市值	
    }
    
     func ( c Company) Get(){
    	fmt.Print("已经拿到数据")
    }
    
    func ( c Company) Print(){
    	fmt.Println(d)
    }
    
    func ( c Company) Change(marketValue string  )(){
    	marketValue
    	value, err := strconv.Atoi(marketValue)
    	c.MarketValue=value
    }
    
    
    //然后我们在主函数中调用
    func main(){
  	 	person:= Person{Name:"www",Age:45}
   company:=Company{Address:"sdbfbjvf",MarketValue:890}
   		DealWith(person,"30")
   		DealWith(company,"70")
    }
    
    
```

**（再举个例子：现在有一个具体的场景，有很多不同类型的结构体（数据）都需要你要实现拿到数据，打印数据，修改数据这三个功能，那么我可以写个总的函数`DealWith`（这里一定是一个接口类型）先定义一个接口类型**

```
 type DataIHave interface{
 // 让这个接口去容纳我们的很多功能（函数）
 	Get()
 	Print()
 	Change()
 } 
```

**2.然后写不同的结构体去实现这些函数**, **面对对象编程最本质的就是**:"相互协作共同完成一件事。"谁和谁相互协作？当然是不同的功能了。怎么实现相互协作？把这些不同的功能函数放在同一个函数下调用就实现了不同功能之间的相互协作。让函数的参数是 **接口类型**，那么不同功能的函数（就是哪些相互协作的函数）的参数来自哪里？这里它们所需要的参数，可以来自用户输入，或者调用其他获取参数的函数来获取。（这里就涉及到为什么我们要写一些生产者函数，把一些步骤写成函数的形式方便了我们重复的使用，我们需要做的就仅仅只是在需要时调用它）

**3.在一个接收`DataIHave`这个接口类型的函数中去协调这些功能函数的“协作”。**

**4.还要一个需要值得注意的点是：“思考要把哪些类型参数放在一起，然后把放在同一个函数中进行使用。”**



```
func Load(g *gin.Engine, mw ...gin.HandlerFunc) *gin.Engine {
	// middleware
	g.Use(gin.Recovery())
	g.Use(middleware.NoCache)
	g.Use(middleware.Options)
	g.Use(middleware.Secure)
	g.Use(mw...)
	// 404 Handler.
	g.NoRoute(func(c *gin.Context) {
		c.String(http.StatusNotFound, "The incorrect API route.")
	})
	g.GET("/swagger/*any", ginSwagger.WrapHandler(swaggerFiles.Handler))
	// router
	authRouter := g.Group("/api/v1/auth")
	{
		authRouter.POST("/register", auth.Register)
		authRouter.POST("/login", auth.Login)
	}

	userRouter := g.Group("/api/v1/user")
	userRouter.Use(middleware.AuthMiddleware)
	{
		userRouter.GET("/detail/:id", user.GetUserInfo)
		userRouter.PUT("", user.UpdateUserInfo)
	}

	ideaRouter := g.Group("/api/v1/idea")
	ideaRouter.Use(middleware.AuthMiddleware)
	{
		// idea
		ideaRouter.POST("", idea.CreateIdea)
		ideaRouter.DELETE("detail/:id", idea.DeleteIdea)
		ideaRouter.GET("/list", idea.GetIdeaList)
		ideaRouter.GET("/detail/:id", idea.GetIdea)

		ideaRouter.GET("/liked", idea.GetIdeaLikedList)

		// comment
		ideaRouter.POST("/detail/:id/comment", idea.CreateComment)
		ideaRouter.DELETE("/detail/:id/comment/:comment_id", idea.DeleteComment)
		ideaRouter.GET("/detail/:id/comment", idea.GetCommentList)

		// like
		ideaRouter.PUT("/detail/:id/like", idea.UpdateIdeaLike)
		ideaRouter.PUT("/comment/:id/like", idea.UpdateCommentLike)
	}

	collectionRouter := g.Group("/api/v1/collection")
	collectionRouter.Use(middleware.AuthMiddleware)
	{
		collectionRouter.GET("", collection.GetCollection)
		collectionRouter.POST("", collection.CreateCollection)
		collectionRouter.DELETE("", collection.DeleteCollection)
	}

	searchRouter := g.Group("/api/v1/search")
	searchRouter.Use(middleware.AuthMiddleware)
	{
		searchRouter.GET("", search.GetSearchResult)
		searchRouter.DELETE("", search.DeleteHistory)
		searchRouter.GET("/histories", search.GetHistories)
	}

	// 举报
	reportRouter := g.Group("/api/v1/report")
	reportRouter.Use(middleware.AuthMiddleware)
	{
		reportRouter.POST("", report.CreateReport)
	}

	// 消息
	messageRouter := g.Group("api/v1/message")
	messageRouter.Use(middleware.AuthMiddleware)
	{
		messageRouter.GET("/tip", message.GetMessageTip)
		messageRouter.PUT("/readall", message.UpdateMessageReadAll)
		messageRouter.GET("/like", message.GetMessageForLike)
		messageRouter.GET("/comment", message.GetMessageForComment)

		// 系统通知，先不做
		// messageRouter.GET("/notice",message.GetMessageForNotice)
	}

	// The health check handlers
	svcd := g.Group("/sd")
	{
		svcd.GET("/health", sd.HealthCheck)
		svcd.GET("/disk", sd.DiskCheck)
		svcd.GET("/cpu", sd.CPUCheck)
		svcd.GET("/ram", sd.RAMCheck)
	}

	return g
}



// 调用这个函数
	router.Load(
		// Cores
		g,

		// Middleware
		middleware.Logging(),
		middleware.RequestId(),
	)
```

