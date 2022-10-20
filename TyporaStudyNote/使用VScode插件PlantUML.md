# 使用VScode插件PlantUML

> UML图 起因是我想用直接用写好的c++代码自动生成UML图，但是！！要安装软件才能实现，如果能直接用VScode实现的绝不多安装一个软件.....毕竟重装系统啥的太烦......

## 1.UML和PlantUML

> UML-Unified Modeling Language 统一建模语言，又称标准建模语言。是用来对软件密集系统进行可视化建模的一种语言。UML的定义包括UML语义和UML表示法两个元素。PlantUML是一个实现UML快速绘图的开源项目，你可以在他的官网 [plantuml.com/zh/](https://link.juejin.cn/?target=http%3A%2F%2Fplantuml.com%2Fzh%2F) 找到下载包，是一个Java的jar包，但是你首先需要安装Java环境。在VScode上利用PlantUML插件和Markdown Preview Enhance插件实现快速绘图，并导出图像。但是前提都是你首先安装了java 环境
>
> ```
> java -version 
> //检查java的版本
> //如果安装成功，那么就ok
> //最最简单的办法就是直接在他们官方的在线网站里面使用UML语法画图，连软件都省的安装......
> //https://www.plantuml.com/plantuml
> //使用在线编辑服务
> ```

在VScode上利用PlantUML插件和Markdown Preview Enhance插件实现快速绘图，并导出图像。支持`*.wsd, *.pu, *.puml, *.plantuml, *.iuml`格式的文件

## 2.VScode的安装和下载

> 请在官网自行安装

## 3.Java的安装和下载

> 你可以在ORACLE的Java官方站点下载对应系统的Java安装包，最新版的是Java SE12.0.1，推荐安装Java SE 8u211版本，在JDK那一项，点击Downloade。你需要下载的是 **Java SE Development Kit 8u211**，然后点击**Accept License Agreement**前面的按钮，X86代表32位的操作系统，X64代表64位的操作系统，选择对应的包下载即可。

## 4.环境变量相关

#### Ubuntu修改全局变量

```
sudo vim /etc/profile
//在profile末尾增加JAVA_HOME、CLASSPATH和PATH，例如
export JAVA_HOME=/usr/local/java/jdk1.8.0_171  # java的安装或解压目录
export CLASSPATH=.:${JAVA_HOME}/lib/dt.jar:${JAVA_HOME}/lib/tools.jar
export PATH=${JAVA_HOME}/bin:$PATH
```

**运行**

```
source /etc/profile  
//使环境立即生效
```

#### **Ubuntu修改用户变量**

```
//修改当前用户配置文件.bashrc，只作用于当前用户：
sudo vim ~/.bashrc
```

**运行**

```
source /etc/profile
//使环境立即生效
```

## 5.VScode安装PlantUML开源插件

> 支持多种文件后缀的UML图。找到VScode扩展页，或者按Ctrl+Shift+X快捷键，直接打开。在搜索栏中搜索**PlantUML**，点击安装。生成其他的图形你可能需要安装GrapgViz(非必需)，不过一般情况下PlantUML足矣。

#### 设置

点击VScode左下角的设置，然后点击设置右上角花括号，如图

![img](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2019/11/21/16e8d9fb3e345238~tplv-t2oaga2asx-zoom-in-crop-mark:1304:0:0:0.awebp)

点击后：

![img](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2019/11/21/16e8da06378d7aed~tplv-t2oaga2asx-zoom-in-crop-mark:1304:0:0:0.awebp)

添加下面一行：

```
"plantuml.includepaths": ["docs/diagrams/style","docs/diagrams/src"],
```

你也可以设置导出和引用的目录，官方的提示是：

```
"plantuml.diagramsRoot": "docs/diagrams/src",
"plantuml.exportOutDir": "docs/diagrams/out"
```

基本的设置就是这些

#### 使用

UML的语法可以在[PlantUML](https://link.juejin.cn?target=http%3A%2F%2Fplantuml.com%2Fzh%2F)或者网页搜索UML语法查看。这里不再赘述。在VScode中创建新文件，后缀改为`*.wsd, *.pu, *.puml, *.plantuml, *.iuml`，输入代码。

PlantUML语法，以`@startuml`开头，以`@enduml`结束，中间键入图表代码。

