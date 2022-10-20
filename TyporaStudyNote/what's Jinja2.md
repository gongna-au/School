# what's Jinja2

Flask和Django，以及其它很多Python框架如Ansible，都默认使用Jinja2来作为模版引擎. 

> Jinja是一个基于Python设计语言的“全功能模板引擎.

## 模板引擎?

在Python中，什么是模版？  

**就是在一个静态HTML加入一些类似变量的标签**，然后**引擎在渲染这个HTML时候会动态的把变量填入内容，生成一个最终的HTML。** 什么是模版引擎？其实就是一种能解析`类似Python语言`的标记语言的解释器。

```
比如我们在HTML模版中输入一个`<p> {{ post.title }} </p>`，显然这不是真正的HTML语法。但是当Jinja2解释器读取到`{{ ...}}`后知道里面是一个变量，那么就把这个变量替换为真正的值，最后翻译出来就变成了`<p> 大标题 </p>`这样的HTML内容。

```

## Jinja2语言基础

`Jinja2`模版语言，是不区分缩进的，和纯python不同。实际上所有模版语言都不区分缩紧。

```
注释：`{# 这是注释 #}`
变量：`{{ post.title }}`，或字典元素`{{your_dict['key']}}`，或列表`{{your_list[0]}}`
多行代码块：`{% 开始 %} HTML标签 {% 结束 %}`
```

### Variables（变量）

除了普通的字符串变量，Jinja2还支持列表、字典和对象，你可以这样获取变量值：

```
{{ mydict['key'] }}
{{ mylist[3] }}
{{ mylist[myintvar] }}
{{ myobj.somemethod() }}
```

获取一个变量的属性有两种方式

```
{{ foo.bar }}
{{ foo['bar'] }}
```

### Filter 过滤器()

一个filter过滤器的本质就是一个function函数。使用格式为：`变量名 | 函数`。 它做到的就是，把变量传给函数，然后再把函数返回值作为这个代码块的值。

```
<!-- 带参数的 -->
{{变量 | 函数名(*args)}}

<!-- 不带参数可以省略括号 -->
{{变量 | 函数名}}
```

链式调用（管道式）： 和命令行的pipline管道一样，可以一次调用多个函数（过滤器），如：

```
{{ "hello world" | reverse | upper }}
```

文本块调用（将中间的所有文字都作为变量内容传入到过滤器中）：

```
{% filter upper %}
    一大堆文字
{% endfilter %}
```

Jinja2常用过滤器:

```
safe：禁用转义
<p>{{ '<em>hello</em>' | safe }}</p>

capitalize：把变量值的首字母转成大写，其余字母转小写
<p>{{ 'hello' | capitalize }}</p>

lower：把值转成小写
<p>{{ 'HELLO' | lower }}</p>

upper：把值转成大写
<p>{{ 'hello' | upper }}</p>

title：把值中的每个单词的首字母都转成大写
<p>{{ 'hello' | title }}</p>

reverse：字符串反转
<p>{{ 'olleh' | reverse }}</p>

format：格式化输出
<p>{{ '%s is %d' | format('name',17) }}</p>

striptags：渲染之前把值中所有的HTML标签都删掉
<p>{{ '<em>hello</em>' | striptags }}</p>

truncate: 字符串截断
<p>{{ 'hello every one' | truncate(9)}}</p>
```

列表操作：

```
first：取第一个元素
<p>{{ [1,2,3,4,5,6] | first }}</p>

last：取最后一个元素
<p>{{ [1,2,3,4,5,6] | last }}</p>

length：获取列表长度
<p>{{ [1,2,3,4,5,6] | length }}</p>

sum：列表求和
<p>{{ [1,2,3,4,5,6] | sum }}</p>

sort：列表排序
<p>{{ [6,2,3,1,5,4] | sort }}</p>
```

For/If (列表控制结构)

```
<h1>Members</h1>
<ul>
{% for user in users %}
  <li>{{ user.username|e }}</li>
{% endfor %}
</ul>
```

```
<dl>
{% for key, value in my_dict.items() %}
    <dt>{{ key|e }}</dt>
    <dd>{{ value|e }}</dd>
{% endfor %}
</dl>
```

if

```
{% if users %}
<ul>
{% for user in users %}
    <li>{{ user.username|e }}</li>
{% endfor %}
</ul>
{% endif %}
```

```
{% if kenny.sick %}
    Kenny is sick.
{% elif kenny.dead %}
    You killed Kenny!  You bastard!!!
{% else %}
    Kenny looks okay --- so far
{% endif %}
```

