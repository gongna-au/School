# Go **策略**模式

> ddl .......

> **策略**是一种行为设计模式， 它将一组行为转换为对象， 并使其在原始上下文对象内部能够相互替换
>
> **原始对象**被称为**上下文**,包含指向**策略对象的引用**并将**执行行为的任务分派给策略对象**

- **原始对象**= 上下文  
- **原始对象包括策略对象的引用**
- **策略对象执行行为的任务**

## 概念

如果要构建内存缓存，那么由于处在内存中， 故其大小会存在限制。 在达到其上限后， 一些条目就必须被移除以留出空间。此类操作可通过多种算法进行实现。 一些流行的算法有：

- 最少最近使用 （LRU）： 移除最近使用最少的一条条目。
- 先进先出 （FIFO）： 移除最早创建的条目。
- 最少使用 （LFU）： 移除使用频率最低一条条目。

#### 问题

如何将我们的缓存类与这些算法解耦， 以便在运行时更改算法？此外， 在添加新算法时， 缓存类不应改变？

这就是策略模式发挥作用的场景。 可创建一系列的算法， 每个算法都有自己的类。 这些类中的每一个都遵循相同的接口， 这使得系列算法之间可以互换。 假设通用接口名称为 `eviction­Algo`移除算法 。



**`eviction­Algo`接口将嵌入至我们的主要缓存类** ，缓存类会将全部类型的移除算法委派给 `eviction­Algo`接口，而不是自行实现。鉴于 `eviction­Algo`是一个接口， 我们可在运行时将算法更改为 LRU、 FIFO 或者 LFU， 而不需要对缓存类做出任何更改。

```
//服务端代码
//cache.go: 上下文
type cache struct {
    storage      map[string]string
    evictionAlgo evictionAlgo
    capacity     int
    maxCapacity  int
}

//evictionAlgo.go: 策略接口

type evictionAlgo interface {
	//肯定要把上下文传进去
    evict(c *cache)
}

// Fifo.go: 具体策略
type Fifo struct {
}

func (l *Fifo) evict(c *cache) {
    fmt.Println("Evicting by Fifo strtegy")
}

//Lru.go: 具体策略

type Lru struct {
}

func (l *Lru) evict(c *cache) {
    fmt.Println("Evicting by Lru strtegy")
}


//Lfu.go: 具体策略
type Lfu struct {
}

func (l *Lfu) evict(c *cache) {
    fmt.Println("Evicting by lfu strtegy")
}


// 实现根据参数选择具体策略的需求
func initCache(e evictionAlgo) *cache {
    storage := make(map[string]string)
    return &cache{
        storage:      storage,
        evictionAlgo: e,
        capacity:     0,
        maxCapacity:  2,
    }
}

//实现更改策略的需求
func (c *cache) setEvictionAlgo(e evictionAlgo) {

    c.evictionAlgo = e
}

//
func (c *cache) add(key, value string) {
    if c.capacity == c.maxCapacity {
        c.evict()
    }
    c.capacity++
    c.storage[key] = value
}
//删除数据
func (c *cache) get(key string) {
    delete(c.storage, key)
}
//c *cache通过调用具体的c.evictionAlgo的执行函数 c.evictionAlgo.evict(c)实现了从顶部直接执行函数
func (c *cache) evict() {
    c.evictionAlgo.evict(c)
    c.capacity--
}

```

```
//客户端代码
package main

func main() {
    lfu := &lfu{}
    cache := initCache(lfu)

    cache.add("a", "1")
    cache.add("b", "2")

    cache.add("c", "3")

    lru := &lru{}
    cache.setEvictionAlgo(lru)

    cache.add("d", "4")

    fifo := &fifo{}
    cache.setEvictionAlgo(fifo)

    cache.add("e", "5")

}
```

