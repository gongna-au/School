# Redis学习

> Redis ( **RE** mote **DI** ctionary **Server** ) 是一种**高级 NoSQL 键值数据存储，**用作数据库、缓存和消息代理。Redis 以其快速的读写操作、丰富的数据类型和先进的内存结构而著称。它非常适合开发高性能、可扩展的 Web 应用程序。

![编辑页面封面](https://www.educative.io/cdn-cgi/image/f=auto,fit=contain,w=600/api/page/4615968400080896/image/download/4802720607764480)

Redis 通常用作缓存，将经常访问的数据存储在内存中，以便应用程序可以响应用户。Redis 能够指定要保留数据的时间以及首先驱逐哪些数据，因此启用了一系列智能缓存模式。

## Part1.什么是Redis？

![widget](https://www.educative.io/cdn-cgi/image/f=auto,fit=contain,w=600/api/page/4615968400080896/image/download/5443270872662016)



Redis 是一种开源的内存数据结构存储，用作数据库、缓存和消息代理。Redis 由 Salvatore Sanfilippo 于 2006 年创建，用 C 语言编写。

它是一种 NoSQL 高级键值数据存储，通常被称为**数据结构服务器，**因为它的键包含字符串、散列、列表、集合、排序集合、位图和超级日志。Redis 的读写操作非常快，因为它将数据存储在内存中。数据也可以存储在磁盘上或写回到内存中。

由于 Redis 将其数据存储在内存中，因此它最常用作缓存。一些使用 Redis 的大型组织是 Twitter、GitHub、Instagram、Pinterest 和 Snapchat。

### Redis的优势

- **速度：** Redis 非常快。它可以每秒执行 110,000 次 SET 和每秒 81,000 次 GET。
- **支持丰富的数据类型：** Redis 支持大部分的数据类型，如列表、集合、有序集合和哈希。这给了你很大的灵活性
- **操作是原子的：**这确保如果两个客户端同时访问数据，Redis 服务器将收到更新的值。
- **用途广泛：** Redis 可用于缓存、消息队列和短期数据，例如 Web 应用程序会话。
- **易于设置：** Redis 易于配置

## Part2.如何安装Redis

根据官方文档，安装Redis的推荐方式是从源代码编译。首先，从官方网站下载它，然后按照以下步骤编译：

根据官方文档，安装Redis的推荐方式是从源代码编译。首先，从官方网站下载它，然后按照以下步骤编译：

```
wget http://download.redis.io/redis-stable.tar.gz
tar xvzf redis-stable.tar.gz
cd redis-stable
make
```

然后，您可以通过键入 来测试您的构建`make test`。该`src`目录将填充 Redis 可执行文件。

建议使用以下两种策略之一将 Redis 服务器和命令行界面复制到适当的位置。

1. `sudo make install`
2. 手动使用以下命令：

```
sudo cp src/redis-server /usr/local/bin/

sudo cp src/redis-cli /usr/local/bin/
```

从`/usr/local/bin/`，通过执行`redis-server`二进制文件（不带参数）来启动 Redis 服务器。由于没有明确的配置文件，所有参数都使用内部默认值。如果你不熟悉 Redis 并想探索环境，这是最好的开始方式。

> 要从我们的应用程序使用 Redis，请根据您要使用的编程语言下载并安装 Redis 客户端库。



## Part3.Redis 数据类型

Redis 是一种**键值存储**，但它**支持多种类型的数据结构**作为字符串以外的值。

Redis 中的键是**二进制安全字符串**，最大大小为 512 MB。

让我们讨论值中支持的数据类型。

### String

> A string in Redis is a sequence of bytes. They are binary safe, so they have a **known length** that is **not determined by any terminating characters.** You can store up to 512 megabytes in a Redis string. It can store any type of data, like text, integers, floats, videos, images, or audio files.
>
> Redis 中的字符串是一个字节序列。它们是二进制安全的，因此它们具有**不由任何终止字符确定**的**已知长度**。您最多可以在 Redis 字符串中存储 512 MB。它可以存储任何类型的数据，如文本、整数、浮点数、视频、图像或音频文件。

```redis
redis 127.0.0.1:6379> SET name "educative" 
OK 
redis 127.0.0.1:6379> GET name 
"educative"
```

在这个例子中，`SET`和`GET`是 Redis 命令，我们将在后面讨论。`name`是键，`educative`是我们存储的字符串值。

### List

> In Redis, lists are lists of strings that are **sorted by an insertion order**, so the elements are stored in a **linked list**. You can add **elements to either on the head or tail**. If we need to insert an element in a list with 500 records, then it will take the **same amount of time** as adding the element to a list of 50,000 records.

以下是列出结果列表的一些示例操作：

```redis
LPUSH mylist x   # now the list is "x"
LPUSH mylist y   # now the list is "y","x"
RPUSH mylist z   # now the list is "y","x","z" (RPUSH was used this time)
```

### Sets

> Sets in Redis are **unordered collections** of strings. This value type is similar to **List**, but **sets don’t allow for duplicates**, and **the elements are not sorted in any order**. **You can add or remove members in O(1)*O*(1) time complexity**.
>
> Sets are useful when we want to store data where **uniqueness** matters. For example, storing the number of unique visitors to a website.



### Sorted Sets

> We can sort elements with a Sorted Set value type. Each element will is associated with a number, which we call a score. This determines the order.
>
> For example, if we have a key called `vegetables`, and we want to store `carrot` and `celery` as the value. The score of `carrot` is 10, and `celery` is 15. Carrot will be first, followed by celery.
>
> 例如，如果我们有一个名为 的键`vegetables`，并且我们想要存储`carrot`和`celery`作为值。`carrot`的分数是10. `celery`是15。先是胡萝卜，然后是芹菜。

如果两个不同元素的分数相同，那么我们检查哪个字符串在*字典上*更大。

### Hash

> In Redis, the hash value type is a **field-value pair.** They are used to **represent objects**, but can **store many elements** and are useful for **other tasks** as well. A **hash takes very little space,** so you can store **millions of objects** in a small **hash instance.**

在Redis中，哈希值类型是一个字段值对。它们用于表示对象，但可以存储许多元素，也可用于其他任务。Hash占用的空间非常小，因此**可以在一个小的Hash实例中存储数百万个对象**。

> 事实上，一个哈希最多可以存储 {2}^{32}23 2- 1− 1 字段值对，相当于超过 40 亿

Say we want to store the information about the grades of students. The subject can be the key. The value can be a field-value pair, with the field being the student name and the value being the grade of each student.

```
HMSET user:1000 username antirez password P1pp0 age 34
HGETALL user:1000
HSET user:1000 password 12345
HGETALL user:1000
```



### 1.在 Redis 中存储字符串：插入和检索命令

```
SET command
GET command
SETEX command
PSETEX command
SETNX command
STRLEN command
MSET command
MGET command
```

Redis 数据库中可以存储的最简单的数据形式是字符串。我们可以将静态 HTML 页面存储在 Redis 数据库中，其中键是一些用于标识页面的名称，值是 HTML 字符串。当值类型为 String 时，学习用于从 Redis 数据库存储和获取记录的所有命令。

#### `SET` command

```
SET key value
```

假设我们需要在 Redis 中保存公司名称及其股票价格。在下面的示例中，我们将**Apple**的股票价格存储在 Redis 中。当我们在Redis中执行一个命令时，返回OK，表示该命令执行成功。

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/6685402472644608)

#### `GET` command

```
GET key
```

在下面的例子中，我们得到了**Apple**的股票价格。

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/6539974880002048)

如果我们`SET`再次为**Apple**运行该命令，并使用不同的值，则 Redis 中的记录将被更新

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/5835617423327232)



#### `SETEX`  command

```
SETEX key seconds value
```

如果我们需要设置某个时间后，密钥将从数据库中删除，则使用此命令。提供的时间以秒为单位。

在下面的示例中，我们存储了 Microsoft 的股票价格。我们提供的时间为 40 秒。当我们尝试在 40 秒之前获取此密钥时，我们将获取数据。我们将在 40 秒后重试，数据将不会返回。两个 GET 命令演示了这种情况。

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/4912989728669696)



除了使用`SETEX`命令，我们还可以使用`SET`带有`EX`选项的命令，如下所示。

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/5999861401911296)



#### `PSETEX`命令

此命令类似于`SETEX`命令。唯一的区别是提供的时间以毫秒为单位。

```
PSETEX key millisecond value

```

在下面的示例中，我们将亚马逊的股票价格存储为 20,000 毫秒作为到期时间。

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/6426679695114240)



#### `SETNX`命令

`SETNX`如果密钥已经存在，则使用该命令。如果一个键已经存在并且我们`SET`再次运行，那么该值被更新。如果我们需要避免这种情况，我们可以使用`SETNX`. 此命令的语法是：

```
SETNX key value
```

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/5713434193690624)



Instead of using the `SETNX` command, we can use the `SET` command with the `NX` option.

In the example below, the stock price of **apple** is already available in the database. We can set it again with the `NX` option so that the value is not updated.

#### `STRLEN` command

This command is used if we need to find the length of the value for a particular key. The syntax of this command is

```
STRLEN key 
```

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/5646065215733760)

#### `MSET` command

If we need to save multiple records in a single command, we can use the `MSET` command. In the example below, we are setting the stock prices of multiple companies in a single command. The syntax of this command is:

```
MSET key1 value1 key2 value2
```

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/5066539238686720)



#### `MGET`命令

If we need to get the value of multiple keys in a single command, we can use the `MGET` command. In the example below, we are getting the stock prices of multiple companies in a single comman

```
MGET key1 key2
```

![img](https://www.educative.io/api/collection/6650775272947712/6601946975698944/page/6141570303655936/image/5652222990876672)



### 2.在 Redis 中存储列表

We can also store lists, and The Redis database stores them as a linked list. When we insert a new element, we can insert it either at the head (left-most element) or tail (right-most element). We will look at two commands used to add and remove records from the head when using lists.

- **`LPUSH` command:**

  该`LPUSH`命令用于在列表的头部插入一个值。我们可以使用一个或多个值，语法是：

  ```
  LPUSH key value
  ```

  **注意：**元素以相反的顺序插入，因为每个元素都被拾取并插入到头部。

- **`LPOP` 命令**

  LPOP 命令用于从列表的头部（或左侧）中删除元素。

  ```
  LPOP key
  ```

### 3.在 Redis 中存储Sets

谈到列表，我们允许重复元素。所以，如果我们需要添加唯一元素，我们应该使用一个集合，它在内部存储为一个哈希表。这意味着元素是随机存储的，不允许重复。让我们看看从 Redis 集中添加元素的命令。

- **`SADD` 命令**

  这允许我们将指定的成员添加到存储在键中的集合中。如果键不存在，则创建一个新集合。

  ```
  SADD key value
  ```

### 4.在Redis中存储 Sorted sets 

Redis 集合中的元素不按任何顺序存储。因此，如果我们想按排序顺序存储元素，我们可以使用排序集，也称为`ZSets`.

每个元素在插入之前都应该被分配一个分数。Redis 数据库将按分数升序对元素进行排序。让我们看看将元素添加到有序集合的命令。

- **`ZADD` 命令**

  此命令将向 Redis 数据库中的排序集中添加元素。我们可以指定多个分数或成员对。如果某个成员已经在该排序集中，则更新分数，并在正确的位置重新插入元素以保持分数。这是语法：

  ```
  ZADD key score value 
  ```

### 5.在 Redis 中存储哈希

在Redis中，一个值也可以是一个字段值对，我们称之为Hash数据结构。让我们看看在 Redis 中存储哈希的命令。

> Hashing 
>
> 假设我们要设计一个系统来存储使用电话号码键入的员工记录。我们希望有效地执行以下查询： 
>  
>
> 1. 插入电话号码和相应信息。
> 2. 搜索电话号码并获取信息。
> 3. 删除电话号码及相关信息。
>
> 我们可以考虑使用以下数据结构来维护不同电话号码的信息。 
>
> 1. 电话号码和记录数组。
> 2. 电话号码和记录的链接列表。
> 3. 以电话号码为关键字的平衡二叉搜索树。
> 4. 直接访问表。
>
> 对于**数组和链表**，我们需要以线性方式搜索，这在实践中可能会很昂贵。如果我们使用数组并保持数据排序，那么可以使用二进制搜索在 O(Logn) 时间内搜索电话号码，但插入和删除操作变得昂贵，因为我们必须维护排序顺序。
>
> 可以想到的另一种解决方案是使用**直接访问表**，我们在其中创建一个大数组并使用电话号码作为数组中的索引。如果电话号码不存在，则数组中的条目为 NIL，否则数组条目存储指向与电话号码对应的记录的指针。
>
> 在时间复杂度方面，这个解决方案是最好的，我们可以在 O(1) 时间内完成所有操作。例如，要插入电话号码，我们创建一个包含给定电话号码详细信息的记录，使用电话号码作为索引并将指向创建的记录的指针存储在表中。 
>
> 该解决方案具有许多实际限制。此解决方案的第一个问题是所需的额外空间很大。例如，如果电话号码是 n 位数字，我们需要 O(m * 10 n) 表空间，其中 m 是要记录的指针的大小。另一个问题是编程语言中的整数可能无法存储 n 位数字。 
>
> 由于上述限制，不能总是使用直接访问表。**散列**是几乎可以在所有此类情况下使用的解决方案，并且在实践中与上述数据结构（如数组、链表、平衡 BST）相比性能非常好。通过散列，我们平均（在合理假设下）获得 O(1) 搜索时间，在最坏情况下获得 O(n) 搜索时间。 
>
> ***散列是对直接访问表的改进。这个想法是使用散列函数将给定的电话号码或任何其他键转换为较小的数字，并使用较小的数字作为称为散列表的表中的索引。*** 
>
> [**哈希函数**](http://en.wikipedia.org/wiki/Hash_function)**：**将给定的大电话号码转换为实用的小整数值的函数。映射的整数值用作哈希表中的索引。简单来说，哈希函数将一个大数字或字符串映射到一个小整数，该整数可以用作哈希表中的索引。
>
> A good hash function should have following properties 
>
> 1) Efficiently computable. 
> 2) Should uniformly distribute the keys (Each table position equally likely for each key)
>
> 例如，对于电话号码，一个不好的哈希函数是取前三位数字。更好的功能是考虑最后三位数字。请注意，这可能不是最好的哈希函数。可能有更好的方法。 
>
> [**哈希表**](http://en.wikipedia.org/wiki/Hash_table)**：**存储指向与给定电话号码对应的记录的指针的数组。如果没有现有电话号码具有等于条目索引的哈希函数值，则哈希表中的条目为 NIL。 
>
> **冲突处理**：由于散列函数为我们提供了一个大键的小数字，因此两个键可能会产生相同的值。新插入的键映射到哈希表中已经占用的槽的情况称为冲突，必须使用某种冲突处理技术进行处理。以下是处理碰撞的方法： 
>
> 1. **链接：**思想是使哈希表的每个单元格都指向具有相同哈希函数值的记录的链表。链接很简单，但需要额外的表外内存。
>
>    ![哈希链](https://media.geeksforgeeks.org/wp-content/cdn-uploads/gq/2015/07/hashChaining1.png)
>
>    
>
> 2. **优点：** 
>    1.实现简单。 
>    2.哈希表永远不会填满，我们可以随时向链中添加更多元素。 3.对散列函数或负载因子不太敏感。 
>
>    4.它主要用于不知道可以插入或删除的密钥数量和频率。
>
> 3. **缺点：** 
>    1）链接的缓存性能不好，因为键是使用链表存储的。开放寻址提供了更好的缓存性能，因为所有内容都存储在同一个表中。 
>    2）空间浪费（哈希表的某些部分从未使用过） 
>    3）如果链变长，那么在最坏的情况下，搜索时间会变成 O(n)。 
>
>    4）为链接使用额外的空间。
>
>    #### 存储链的数据结构： 
>
>    - 链表
>      - 搜索：O(l) 其中 l = 链表的长度
>      - 删除：O(l)
>      - 插入：O(l)
>      - 缓存不友好
>    - 动态大小的数组（C++ 中的向量，Java 中的 ArrayList，Python 中的列表）
>      - 搜索：O(l) 其中 l = 数组长度
>      - 删除：O(l)
>      - 插入：O(l)
>      - 缓存友好
>    - 自平衡 BST（AVL 树、红黑树）
>      - 搜索：O(log(l))
>      - 删除：O(log(l))
>      - 插入：O(l)
>      - 缓存不友好
>      - Java 8 以后将此用于 HashMap
>
> 4. **开放寻址：**在开放寻址中，所有元素都存储在哈希表本身中。每个表条目包含一条记录或 NIL。在搜索元素时，我们会一一检查表槽，直到找到所需元素或很明显该元素不在表中。
>    与单独链接一样，开放寻址是一种处理冲突的方法。在开放寻址中，所有元素都存储在哈希表本身中。所以在任何时候，表的大小都必须大于或等于键的总数（注意，如果需要，我们可以通过复制旧数据来增加表的大小）。 
>
>    Insert(k)：继续探测直到找到一个空槽。找到空槽后，插入k。 
>
>    Search(k)：继续探测直到槽的键不等于 k 或到达一个空槽。
>
>    Delete(k)：***删除操作很有趣***。如果我们简单地删除一个键，那么搜索可能会失败。因此，已删除键的插槽被特别标记为“已删除”。  
>
>    插入可以在已删除的插槽中插入项目，但搜索不会在已删除的插槽处停止
>
>    开放寻址通过以下方式完成： 
>
>    ```
>    设hash(x)是使用散列函数计算的槽索引， S是表大小 
>    如果槽 hash(x) % S 已满，那么我们尝试 (hash(x) + 1) % S
>    如果 (hash(x) + 1) % S 也满了，那么我们尝试 (hash(x) + 2) % S
>    如果 (hash(x) + 2) % S 也满了，那么我们尝试 (hash(x) + 3) % S 
>    ```
>
>    
>
>    **线性探测的挑战：**

> 1. ​	**主要聚类：**线性探测的问题之一是主要聚类，许多连续的元素形成组，并且开始需要时间来寻找空闲槽或搜索元素。
> 2. **Secondary Clustering** ***：*** Secondary Clustering 不那么严重，如果两个记录的初始位置相同，则它们只有相同的碰撞链（Probe Sequence）。
>
> ***b) 二次探测***我们在第 i 次迭代中寻找第i 2个槽。 
>
> ```
> let hash(x) be the slot index computed using hash function.  
> If slot hash(x) % S is full, then we try (hash(x) + 1*1) % S
> If (hash(x) + 1*1) % S is also full, then we try (hash(x) + 2*2) % S
> If (hash(x) + 2*2) % S is also full, then we try (hash(x) + 3*3) % S
> ```
>
> **c)**[**双散列**](https://www.geeksforgeeks.org/double-hashing/)我们使用另一个散列函数 hash2(x) 并在第 i 个循环中寻找 i*hash2(x) 槽。 
>
> ```
> 让 hash(x) 是使用哈希函数计算的槽索引。  
> 如果插槽 hash(x) % S 已满，则我们尝试 (hash(x) + 1*hash2(x)) % S
> 如果 (hash(x) + 1*hash2(x)) % S 也已满，则我们尝试 (hash(x) + 2*hash2(x)) % S
> 如果 (hash(x) + 2*hash2(x)) % S 也已满，那么我们尝试 (hash(x) + 3*hash2( x)) % S 
> ```
>
> | 号   | **单独链接**                                                 | **开放寻址**                                                 |
> | :--- | :----------------------------------------------------------- | :----------------------------------------------------------- |
> | 1.   | 链接更容易实现。                                             | 开放寻址需要更多的计算。                                     |
> | 2.   | 在链接中，哈希表永远不会填满，我们总是可以添加更多元素到链中。 | 在开放寻址中，表可能会变满。                                 |
> | 3.   | 链接对散列函数或负载因子不太敏感。                           | 开放寻址需要格外小心以避免集群和负载因子。                   |
> | 4.   | 当不知道可以插入或删除多少键以及多频繁地插入或删除键时，最常使用链接。 | 当键的频率和数量已知时使用开放寻址。                         |
> | 5.   | 链接的缓存性能不好，因为键是使用链表存储的。                 | 开放寻址提供了更好的缓存性能，因为所有内容都存储在同一个表中。 |
> | 6.   | 空间浪费（链中哈希表的某些部分从未使用过）。                 | 在开放寻址中，即使输入没有映射到插槽，也可以使用插槽。       |
> | 7.   | 链接为链接使用额外的空间。                                   | 开放式寻址中没有链接                                         |
>
> **Open Addressing** 的性能**：**
>
> 与 Chaining 一样，可以在假设每个键同样可能被散列到表的任何插槽的情况下评估散列的性能（简单的统一散列） 
>
> ```
> m = 哈希表中的槽数
> n = 要插入哈希表中的键数
>  
> 负载因子 α = n/m ( < 1 )
> 
> 搜索/插入/删除的预期时间 < 1/(1 - α) 
> 
> So Search , Insert 和 Delete 花费 (1/(1 - α)) 时间
> ```
>
>  在 Redis 中存储哈希
>
> 在Redis中，一个值也可以是一个字段值对，我们称之为Hash数据结构。让我们看看在 Redis 中存储哈希的命令。
>
> - **`HMSET` 命令**
>
> 此命令用于在 Redis 中存储哈希。它将字段设置为它们各自在哈希中的值。此命令覆盖散列中已存在的字段。此命令的语法是：
>
> ```
> HMSET  key field value
> ```
>
> - **如果使用 Redis 4.0.0，`HMSET`则被视为已弃用，并且`HSET`是首选。**

## Redis 命令



## 高级Redis概念

> 现在我们了解了Redis的一些基础知识并介绍了命令，让我们来看看一些高级概念。
>
> **关于 Redis 的重要说明**
>
> 在本教程中，我们将使用渐进式`leader`/`follower`隐喻代替模型/从属术语。我们使用该术语不会干扰您对 Redis 的理解。
>
> Redis 的官方文档使用了 Master/Slave 模型，该模型在计算机科学中已经流行了几十年，可以追溯到 1904 年。

### Redis 中的数据复制

当数据存储在服务器上并且服务器崩溃时，数据可能会丢失。我们使用数据复制技术来避免这个问题。这基本上意味着数据存储在两个或多个服务器上以**防止丢失或崩溃**。数据复制还减少了我们服务器的负载，因为用户请求是负载平衡的。

Redis 遵循**leader/follower approach**方法进行基于服务器的数据复制。其中一台服务器是`leader`，其他服务器是`followers`，它们都连接到`leader`。我们将所有内容写入`leader`，然后将更改发送到`followers`。

如果 a`follower`断开连接，它将自动重新连接并`leader`准确复制。这可以通过两种方法完成：

- **部分同步**
- **完全同步**

> **注意：**在Redis中，复制过程是异步的。所述`follower`服务器异步地确认从数据`leader`，所以`leader`知道哪些命令已经被处理。

### 坚持

由于 Redis 是内存数据库，因此数据存储在内存（或 RAM）中。如果服务器崩溃，所有存储的数据都会丢失。Redis对磁盘上的数据有适当**的备份机制**。这样，当服务器重新启动时，数据就会从磁盘加载到内存中。Redis 有两个持久化选项：

RDB 持久化（snapshotting）：数据的快照存储在磁盘中的一个`dump.rdb`文件中。持久性取决于将数据转储到磁盘的频率。

**Append-only file (AOF) 持久化：**服务器收到的每一次写操作都会记录到一个文件中，因此在重新启动时会再次运行 AOF 文件中的所有命令。

## 接下来要学什么