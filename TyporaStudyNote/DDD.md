# DDD

> 首先我们应该先理解这里的领域是什么意思？假设公司内部正在开发一套电商平台，而电商平台中包含了库存、订单、商品等核心业务。这些核心业务逻辑其实呈现的就是电商平台领域。通俗的理解就是一整套体系的业务知识即代表了一个领域。好比在线教育平台，它需要有一套体系的业务，包括招生、线上教学、课程等内容。我们将这些业务抽象出领域模型，而这些领域模型表达了产品经理所阐述的业务需求，我们反复地用这些领域模型与产品经理进行讨论沟通最终确定初步的领域模型。再使用初步的领域模型指导代码设计开发。

**采用领域驱动设计的好处在于项目以领域模型为核心，在领域模型不变的情况下，我们是很容易对我们的基础设施进行更换的。**

> 业务知识 --> 领域模型 --> 项目设计与代码开发

我们之前的开发也是有这些业务逻辑支撑？那我们之前传统的开发模式为什么不能称之为面向领域驱动设计呢？回想一下我们之前的代码开发，比如一个实现一个购物车下订单的功能，我们根据订单表的字段，依次用商品字段、金额字段、用户字段等**拼凑**出订单表中的一条**记录**，然后写入到订单表当中去。其实我们是面向数据库在进行开发，**以数据库为重心**，而**业务逻辑零散地分布在各个Service当中**。采用的是面向过程的编程方式而不是面向对象的方式，也就没有形成一套有机的业务逻辑。

面向领域驱动设计则不一样，它以领域为重心，以刚才的购物车下订单功能为例子。在DDD当中，会将购物车相关的业务逻辑封装到一个ShoppingCart对象中，并直接调用shoppingCart.takeOrder()下订单的方法，代码的重心从生成订单表中的记录转移到购物车对象本身。具体数据库中如何生成这条记录并不属于我们的核心业务逻辑，它被下放到基础设施层，由**Repository**或者**Dao**等数据交互对象负责去持久化我们对领域模型下达的指令所产生的数据库变化。

#### 贫血症和失忆症

传统的开发模式中，我们经常使用的是一个JavaBean，其中只有映射到数据库的字段，并没有业务行为。通过填充这个JavaBean，并在对象外部进行业务逻辑的编写，如计算订单的最终金额填充到JavaBean中再交由数据库映射框架进行持久化。

而其实这就是Evans所说的贫血症，因为数据和业务行为隔离开来，形成一种无机的代码组成。其实这并非面向对象的编码方式，当我们看到Order对象时，我们根本不知道它含有计算最终金额的业务逻辑，而这其实就是一种所谓的贫血症引起的失忆症。数据和行为并没有紧密的联系到一起。

```
func buyProduct( orderId int, price float64, productId int ,  discount float) error{
       if(discount == 0) {
            return errors.New(" 折扣不可为0")
        }
        // 计算最终付款金额
        paid := price * discount
        order := newOrder(orderId,price,productId,discount)
        OrderDao.save(order);
}

```

```
//一个更好的例子

func buyProduct (orderId int, price float64, productId int ,  discount float) error{
        order := newOrder(orderId,price,productId,discount)
        order.calculatePaid()
        OrderDao.save(order)
}

```

而更好的方式我们应该通过将**数据和业务行为整合**到一个对象中去，让二者形成一种有机的代码组成。在GRASP对象职责中有一个原则就是当一个对象拥有某个方法所需的属性时，那么更应该将这个方法放置到这个对象中去，而不是放在其他地方。

上面的例子更加符合我们对于业务的描述，但仅仅强调将**业务逻辑封装到数据对象**中去还不够，我们还需要通过这些**对象之间的协作来进行业务的表达**。一个很显而易见的例子就是关于转账的例子。

```
func  main() {
        a := newAccount(5);

        b := newAccount(5);
        transferMoney := 4.0;

        if (a.getMoney() < transferMoney) {
        	fmt.Println(errors.New("余额不足"))
        }
        a.setMoney(a.getMoney() - transferMoney)
        b.setMoney(b.getMoney() + transferMoney)

    }

```

更好的做法我们应该借鉴面向对象的建模方式，将领域知识封装到账户Account模型中去。

```
func (a *Account) Transfer (another Account , transferMoney float){
	if a.money <  transferMoney{
		fmt.Println(errors.New("余额不足"))
	}
	a.money =a.money - transferMoney
	another.SetMoney(another.getMoney()+transferMoney )
}
```

```
//A账户向B账户进行转账
func main(){
		 a := new Account(5)
         b := new Account(5) 
         transferMoney:=4
         a.Transfer(b, transferMoney)
        
}

```

通过领域模型之间的协作，呈现出来的代码就像**白话**一样。有**主语谓语宾语**。主语是A账户，**谓语是transfer()方法**，宾语是B账户。这样一来，代码的自解释能力也就非常强了。

#### DDD的适用场景

那什么场景才是适合DDD的场景呢？
 在可预见的未来中，项目的业务复杂度会越来越高，那就非常适合使用DDD的设计方式。而如果项目全部都是一些非常简单的增删查改而很少包含业务知识的话，那真是想D也D不起来，因为DDD的思想就是为了通过模型来表达领域知识，而领域知识本身就很匮乏的话，表达也就无从谈起。