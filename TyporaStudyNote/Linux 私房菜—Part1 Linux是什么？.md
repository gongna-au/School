# Linux 私房菜—Part1 Linux是什么？

### 1.1 Linux是什么

#### 1.1.1 Linux是什么？操作系统/应用程序？

Linux就是一套操作系统

由于不同的硬件他的功能函数并不相同，例如IBM的Power CPU与Intel的x86架构就是不一样！ 所以同一套操作系统是无法在不同的硬件平台上面运行的！举例来说，如果你想要让x86上面跑的那套操作系统也能够在Power CPU上运行时，就得要将该操作系统进行修改才行。如果能够参考硬件的功能函数并据以修改你的操作系统程序码， 那经过改版后的操作系统就能够在另一个硬件平台上面运行了。 这个动作我们通常就称为**“软件移植”**了！

Windows操作系统本来就是针对个人计算机x86架构的硬件去设计的，所以他当然只能在x86的个人计算机上面运行，在不同的硬件平台当然就无法运行了。也就是说，每种操作系统都是在他专门的硬件机器上面运行

**不过，Linux由于是Open Source的操作系统，，所以他的程序码可以被修改成适合在各种机器上面运行的， 也就是说，Linux是具有“可移植性”，这可是很重要的一个功能。**

这是因为： **Linux提供了一个完整的操作系统当中最底层的硬件控制与资源管理的完整架构。这个架构是沿袭了Unix的良好传统而来。这个架构可以在个人计算机上跑，所以很多软件开发者也在这个架构上贡献了自己的心血。**

**Linux仅仅只是核心与核心工具，不过由于这个东西与软件开发者提供的软件的整合才使得Linux成为一个完整而强大的操作系统。**

Thompson因为自己的需要，希望开发一个小小的操作系统以提供自己的需求，经过四个星期的奋斗，他终于以组合语言（Assembler）写出了一组核心程序，同时包括一些核心工具程序， 以及一个小小的文件系统。那个系统就是Unix的原型。

**Thompson 的这个文件系统有两个重要的概念，分别是：**

- **所有的程序或系统设备都是文件**
- **不管建构编辑器还是附属文件，所写的程序只有一个目的，且要有效的完成目标**

**重要的Unix分支--BSD的诞生：**

柏克莱大学的Bill Joy [4]在取得了Unix的核心源代码后，着手修改成适合自己机器的版本， 并且同时增加了很多工具软件与编译程序，最终将它命名为Berkeley Software Distribution（BSD）。这个BSD是Unix很重要的一个分支，Bill Joy也是Unix业者“Sun（升阳）”这家公司的创办者！ Sun公司即是以BSD发展的核心进行自己的商业Unix版本的发展的。 （后来可以
安装在x86硬件架构上面FreeBSD即是BSD改版而来！）

**1979年：重要的 System V 架构与版权宣告**：

由于Unix的高度可移植性与强大的性能，加上当时并没有版权的纠纷， 所以让很多商业公司开始了Unix操作系统的发展，例如AT&T自家的System V、IBM的AIX以及HP与DEC等公司，都有推出自家的主机搭配自己的Unix操作系统

如同相容分时系统的功能一般，Unix强调的是多用户多任务的环境！ 但早期的286个人计算机架构下的CPU是没有能力达到多任务的作业，因此，并没有人对移植Unix到x86的计算机上有兴趣。每一家公司自己出的Unix虽然在架构上面大同小异，但是却真的仅能支持自身的硬件， 所以啰，早先的Unix只能与服务器（Server）或者是大型工作站（Workstation）划上等号！ 但

**Tips 目前被称为纯种的Unix指的就是System V以及BSD这两套：**

既然1979年的Unix第七版可以在Intel的x86架构上面进行移植， 那么是否意味着可以将Unix改写并移植到x86上面了呢？在这个想法上， 谭宁邦教授于是乎自己动手写了Minix这个UnixLike的核心程序！ 在撰写的过程中，为了避免版权纠纷，谭宁邦完全不看Unix核心源代码！
并且强调他的Minix必须能够与Unix相容才行！谭宁邦在1984年开始撰写核心程序， 到了1986年终于完成，并于次年出版Minix相关书籍，同时与新闻群组（BBS及News）相结合～

**之所以称为Minix的原因，是因为他是个Mini （微小的） 的Unix系统**

**GNU计划与FSF基金会的成立：**

对于现今的自由软件风潮，真有不可磨灭的地位！目前我们所使用的很多自由软件或开源软件，几乎均直接或间接受益于GNU这个计划呢！ 那么史托曼是何许人也？为何他会发起这个GNU计划呢？

史托曼开始GNU计划， 这个计划的目的是：创建一个自由、开放的Unix操作系统（Free Unix）。聪明的史托曼干脆反其道而行～“既然操作系统太复杂，我就先写可以在Unix上面运行的小序，这总可以了吧？”在这个想法上， 史托曼开始参考Unix上面现有的软件，并依据这些软件的作用开发出功能相同的软件，且开发期间史托曼绝不看其他软件的源代码， 以避免吃上官
司。后来一堆人知道免费的GNU软件，并且实际使用后发现与原有的专利软件也差不了太多，于是便转而使用GNU软件， 于是GNU计划逐渐打开知名度。如果能够写出一个不错的编译器，那不就是大家都需要的软件了吗？ 因此他便开始撰写C语言的编译器，**相当有名的GNU C Compiler（gcc），但开始撰写GCC时并不顺利，为此，他先转而将他原先就已经写过的Emacs编辑器写成可以在Unix上面跑的软件，并公布源代码。 Emacs是一种程序编辑器，他可以在使用者撰写程序的过程中就进行程序语法的检验，此一功能可以减少程序设计师除错的时间！ 因为Emacs太优秀了，因此，很多人便直接向他购买，此时网际网络尚未流行，所以，史托曼便借着Emacs以磁带（tape）出售，赚了一点钱 ，进而开始全力撰写其他软件。并且成立自由软件基金会（FSF, Free Software Foundation），请更多工程师与志工撰写软件。终于还是完成了GCC，这比Emacs还更有帮助！ 此外，他还撰
写了更多可以被调用的C函数库（GNU C library），**

- GNU的通用公共许可证

  到了1985年，为了避免GNU所开发的自由软件被其他人所利用而成为专利软件， 所以他与律师草拟了有名的通用公共许可证（General Public License, GPL）， 并且称呼他为copyleft（相对于专利软件copyright！）。 关于GPL的相关内容我们在下一个小节继续谈
  论，在这里，必须要说明的是， 由于有GNU所开发的几个重要软件

  - Emacs
  - GNU C （GCC）
  - GNU C Library （glibc）
  - Bash shell

造成后来很多的软件开发者可以借由这些基础的工具来进行程序开发！ 进一步壮大了自由软件团体！这是很重要的！不过，对于GNU的最初构想 “创建一个自由的Unix操作系统”来说，有这些优秀的程序是仍无法满足， 因为，当下并没有“自由的Unix核心”存在..所以这些软件仍只能在那些有专利的 Unix平台上工作～～一直到Linux的出现..

到了1991年，芬兰的赫尔辛基大学的Linus Torvalds在BBS上面贴了一则消息， 宣称他以bash, gcc等 GNU 的工具写了一个小小的核心程序，该核心程序单纯是个玩具，不像 GNU 那么专业。 不过该核心程序可以在Intel的386机器上面运行就是了。这让很多人很感兴趣！从此开始了Linux不平凡的路程！

#### 1.1.3).关于GNU计划、自由软件与开放源代码

- 自由软件的活动：

  1984年创立GNU计划与FSF基金会的Stallman先生认为：而既然程序是想要分享给大家使用的，不过，每个人所使用的计算机软硬件并不相同， 既然如此的话，那么该程序的源代码（Source code）就应该要同时释出， 这样才能方便大家修而适用于每个人的计算机中呢！这个将源代码连同软件程序释出的举动，在 GNU 计划的范畴之内就称为自由软件（Free Software）运动！

- 自由软件的版权GNU GPL：

  而为了避免自己的开发出来的Open source自由软件被拿去做成专利软件， 于是Stallman同时将GNU与FSF发展出来的软件，都挂上GPL的版权宣告～ 

**为什么要称为GNU呢？其实GNU是GNU's Not Unix的缩写，意思是说，GNU并不是Unix啊！那么GNU又是什么呢？ 就是GNU's Not Unix嘛！.....如果你写过程序就会知道，这个GNU = GNU's Not Unix可是无穷循环啊**

因为如此一来，你所拿到的软件可能原先只能在Unix上面跑， 但是经过
源代码的修改之后，你将可以拿他在Linux或者是Windows上面来跑！总之， 一个软件挂上了GPL版权宣告之后，他自然就成了自由软件！这个软件就具有下面的特色：

- 取得软件与源代码：你可以根据自己的需求来执行这个自由软件；
- 复制：你可以自由的复制该软件
- 修改：你可以将取得的源代码进行程序修改工作，使之适合你的工作
- 再发行：你可以将你修改过的程序，再度的自由发行，而不会与原先的撰写者

但是不可以这样：

- 修改授权：你不能将一个GPL授权的自由软件，在你修改后而将他取消GPL授权～
- 单纯贩卖：你不能单纯的贩卖自由软件。

**所以说，目前自由软件工作者，他们所赖以维生的，几乎都是在“服务”这个领域呢！ 毕竟自由软件并不是每个人都会撰写，有人有需要你的自由软件时，他就会请求你的协助， 此时，你就可以通过服务来收费了！这样来说， 自由软件确实还是具有商业空间的喔！**

另外，并非软件可以被读取源代码就可以被称为开源软件喔！该软件的授权必须要符合下面的基本需求，才可以算是 open source 的软件哩！

- 公布源代码且用户具有修改权：用户可以任意的修改与编译程序码，这点与自由软件差异不大
- 任意的再散佈：该程序码全部或部份可以被贩售，且程序码可成为其他软件的元件之一，作者不该宣称具有拥有权或收取其他额外费用
- 必须允许修改或衍生的作品，且可让再发布的软件使用相似的授权来发表即可
- 不可限制某些个人或团体的使用权
- 不可具有排他条款，例如不可限制本程序码不能用于教育类的研究中，诸如此类。

另外，Open source 这个名词只是一个指引，而实际上并不是先有 open source 才有相关授权。早在 open source 出来之前就有些开源软件的授权存在了 （例如 GPL 啊！）！ 不有 open source 这个名词之后，大家才更了解到开源软件授权的意义就是了。那常见的开源代码授权有哪些呢？

- Apache License 2.0
- BSD 3-Clause "New" or "Revised" license
- BSD 2-Clause "Simplified" or "FreeBSD" license
- GNU General Public License （GPL）
- GNU Library or "Lesser" General Public License （LGPL）
- MIT license
- Mozilla Public License 2.0
- Common Development and Distribution License

虽然专利软件常常代表就是需要花钱去购买，不过有些专利软件还是可以“免费”提供福斯使用的！免费的专利软件代表的授权模式有：

- Freeware
- Shareware

### 1.2 Torvalds的Linux发展

#### 1.2.1).与Minix之间

托瓦兹接触了组合语言（Assembly Language），那是一种直接与芯片对谈的程序语言，也就是所谓的低阶语言。 必须要很了解硬件的架构，否则很难以组合语言撰写程序。他在购买了最新的Intel 386的个人计算机后，就立
即安装了Minix这个操作系统。 另外，上个小节当中也谈到，Minix这个操作系统是有附上源代码的， 所以托瓦兹也经由这个源代码学习到了很多的核心程序设计的设计概念喔！

#### 1.2.2).对386硬件的多任务测试

事实上，托瓦兹对于个人计算机的CPU其实并不满意，因为他之前碰的计算机都是工作站型的计算机， 这类计算机的CPU特色就是可以进行“多任务处理”的能力。**什么是多任务呢？**论上， 一个CPU在一个时间内仅能进行一个程序， 那如果有两个以上的程序同时出现到系统中呢？举例来说， 你可以在现今的计算机中同时打开两个以上的办公软件，例如电子试算表与文书处理软件。 这个同时打开的动作代表着这两个程序同时要交给CPU来处理～
啊！CPU一个时间点内仅能处理一个程序，那怎么办？没关系，这个时候如果**具有多任务能力的CPU就会在不同的程序间切换**～ 还记得前一章谈到的CPU频率吧,假设CPU频率为1GHz的话，那表示CPU一秒钟可以进行109次工作。 假设CPU对每个程序都只进行1000次,运行周期，然后就得要切换到下个程序的话，那么CPU一秒钟就能够切换106次呢！ （当然
啦，切换工作这件事情也会花去一些CPU时间，不过这里暂不讨论）。这么快的处理速度下，你会发现， 两个程序感觉上几乎是同步

为什么有的时候我同时开两个文件（假设为A, B文件）所花的时间， 要比开完A再去开B文件的时间还要多？现在是否稍微可以理解？ 因为如果同时打开的话，CPU就必须要在两个工作之间不停的切换～ 而切换的动作还是会耗去一些CPU时间的！所以啰，同时启用两个以上的工作在一个CPU上， 要比一个一个的执行还要耗时一点。这也是为何现在CPU开发商要
整合多个CPU于一个芯片中！ 也是为何在运行情况比较复杂的服务器上，需要比较多的CPU负责的原因。

早期Intel x86架构计算机不是很受重视的原因，就是因为x86的芯片对于多任务的处理不佳，CPU在不同的工作之间切换不是很顺畅。但是这个情况在386计算机推出后，有很大的改善。托瓦兹在得知新的386芯片的相关信息后，他认为，以性能价格比的观点来看， Intel的386相当的便宜，所以在性能上也就稍微可以将就将就 ^_^。最终他就贷款去买了一部Intel的386来
玩。，托瓦兹自己也说：“我始终是
个性能癖”^^。 为了彻底发挥386的性能，于是托瓦兹花了不少时间在测试386机器上！ 他的重要测试就是在测试386的多功性能。首先，他写了三个小程序，一个程序会持续输出A、一个会持续输出B， 最后一个会将两个程序进行切换。他将三个程序同时执行，结果，他看到屏幕上很顺利的一直出现ABABAB...... 他知道，他成功了！ 

**总结：要达到多工（multitasking）的环境，除了硬件（主要是CPU）需要能够具有多任务的特性外，操作系统也需要支持这个功能喔！ 一些不具有多任务特性的操作系统，想要同时执行两个程序是不可能的。除非先被执行的程序执行完毕，否则， 后面的程序不可能被主动执行。**

**至于多任务的操作系统中，每个程序被执行时，都会有一个最大CPU使用时间，若该工作行的时间超过这个CPU使用时间时， 该工作就会先被丢出CPU的运行中，而再度的进入核心工作调度中等待下一次被CPU取用来运行**

#### 1.2.3).初次释出Linux 0.02

探索完386的硬件性能之后，终于拿到Minix并且安装在托瓦兹的386计算机上之后，托瓦兹跟BBS上面一堆工程师一样， 他发现Minix虽然真的很棒，但是谭宁邦教授就是不愿意进行功能的加强，导致一堆工程师在操作系统功能上面的欲求不满！ 这个时候年轻的托瓦兹就想：“既然如此，那我何不自己来改写一个我想要的操作系统？” 于是他就开始了核心程序的撰写了

撰写程序需要什么呢？首先需要的是能够进行工作的环境，再来则是可以将源代码编译成为可可执行文件的编译器。 好在有GNU计划提供的bash工作环境软件以及gcc编译器等自由软件， 让托瓦兹得以顺利的撰写核心程序。他参考Minix的设计理念与书上的程序码，然后仔细研究出386个人计算机的性能最优化， 然后使用GNU的自由软件将核心程序码与386紧紧的结合在一起，最终写出他所需要的核心程序。 而这个小玩意竟然真的可以在386上面顺利的跑起来～还可以读取Minix的文件系统。 真是太好了！不过还不够，他希望这个程序可以获得大家的一些修改建议， 于是他便将这个核心放置在网络上提供大家下载，同时在BBS上面贴了一则消息：

不过，他发现到有很多的软件无法在Linux这个核心上运行。这
个时候他有两种作法， 一种是修改软件，让该软件可以在Linux上跑， 另一种则是修改 Linux，让Linux符合软件能够运行的规范！ 由于Linux希望能够相容于Unix，于是托瓦兹选择了第二个作法“修改Linux”！ 为了让所有的软件都可以在Linux上执行，于是托瓦兹开始参考标准的POSIX规范。

**总结： POSIX是可携式操作系统接口（Portable Operating System Interface）** 用于：**规范核心与应用程序之间的接口**

这个正确的决定让Linux在起步的时候体质就比别人优良～因为POSIX标准主要是针对Unix与一些软件运行时候的标准规范， 只要依据这些标准规范来设计的核心与软件，理论上，就可以搭配在一起执行了。 而Linux的发展就是依据这个POSIX的标准规范，Unix上面的软件也是遵循这个规范来设计的， 如此一来，让Linux很容易就与Unix相容共享互有的软件了！

#### 1.2.4).Linux 的发展：虚拟团队的产生

Linux能够成功除了托瓦兹个人的理念与力量之外，其实还有个最重要的团队！

- 单一个人维护阶段

  首先，他将释出的Linux核心放置在FTP上面，并请告
  知大家新的版本信息， 等到使用者下载了这个核心并且安装之后，如果发生问题，或者是由于特殊需求亟需某些硬件的驱动程序，那么这些使用者就会主动回报给托瓦兹。 在托瓦兹能够解决的问题范围内，他都能很快速的进行Linux核心的更新与除错。

- 广大骇客志工加入阶段

  不过，托瓦兹总是有些硬件无法取得的啊，那么他当然无法帮助进行驱动程序的撰写与相关软件的改良。 这个时候，就会有些志工跳出来说：“这个硬件我有，我来帮忙写相关的驱动程序。” 因为Linux的核心是Open Source的，骇客志工们很容易就能够跟随Linux的原本设计架
  构， 并且写出相容的驱动程序或者软件。志工们写完的驱动程序与软件托瓦兹是如何看待的呢？ 首先，他将该驱动程序/软件带入核心中，并且加以测试。 只要测试可以运行，并且没有什么主要的大问题，那么他就会很乐意的将志工们写的程序码加入核心中！

**另外，为因应这种随时都有程序码加入的状况，于是Linux便逐渐发展成具有模块的功能！ 亦即是将某些功能独立出于核心外,在需要的时候才载入到核心中。果有新的硬件驱动程序或者其他协定的程序码进来时，就可以模块化， 大大的增加了Linux核心的可维护能力！**

- 核心功能细部分工发展阶段

  后来，因为Linux核心加入了太多的功能，光靠托瓦兹一个人进行核心的实际测试并加入核心原始程序实在太费力～ 结果，就有很多的朋友跳出来帮忙这个前置作业！例如考克斯（AlanCox）、与崔迪（Stephen Tweedie）等等， 这些重要的副手会先将来自志工们的修补程序或
  者新功能的程序码进行测试， 并且结果上传给托瓦兹看，让托瓦兹作最后核心加入的源代码的选择与整并！ 这个分层负责的结果，让Linux的发展更加的容易！

#### 1.2.5).Linux的核心版本

Linux的核心版本编号有点类似如下的样子：

```
3.10.0-123.el7.x86_64
主版本.次版本.释出版本-修改版本
```

#### 1.2.6). Linux distributions

好了，经过上面的说明，我们知道了Linux其实就是一个操作系统最底层的核心及其提供的核心工具。 他是GNU GPL授权模式，所以，任何人均可取得源代码与可执行这个核心程序，并且可以修改。 此外，因为Linux参考POSIX设计规范，于是相容于Unix操作系统，故亦可称之为Unix Like的一种。

为了让使用者能够接触到Linux，于是很多的商业公司或非营利团体， 就将Linux Kernel（含tools）与可运行的软件整合起来，加上自己具有创意的工具程序， 这个工具程序可以让使用者以光盘/DVD或者通过网络直接安装/管理Linux系统。 这个“Kernel + Softwares + Tools + 可完整安装程序”的咚咚，我们称之为Linux distribution， 一般中文翻译成可完整安装套件，或
者Linux发布商套件等

不过，由于发展Linux distributions的社群与公司实在太多了，例如在台湾有名的Red Hat,SuSE, Ubuntu, Fedora, Debian等等，所以很多人都很担心，如此一来每个distribution是否都不相同呢？ 这就不需要担心了，因为每个Linux distributions使用的kernel都是http://www.kernel.org所释出的，而他们所选择的软件，几乎都是目前很知名的软件，重复性相当的高， 例如网页服务器的Apache，电子邮件服务器的Postfix/sendmail，文件服务器的Samba等等。此外，为了让所有的Linux distributions开发不致于差异太大，且让这些开发商在开发的时候有所依据，还有Linux Standard Base （LSB）等标准来规范开发者，以及目录架构的Filesystem Hierarchy Standard （FHS）标准规范！ 唯一差别的，可能就是该开发者自家所开发出来的管理工具，以及套件管理的模式吧！ 所以说，基本上，每个Linux distributions除了架构的严谨度与选择的套件内容外， 其实差异并不太大啦！大家可以选择自己喜好的来安装即可！

**为distributions主要分为两大系统:**

- 使用RPM方式安装软件
- 是使用Debian的dpkg方式安装软件的系统,包括Debian, Ubuntu, B2D等。

Tips 到底是要买商业版还是社群版的Linux distribution呢？如果是要装在个人计算机上面做为桌面电脑用的，建议使用社群版， 包括Fedora, Ubuntu, OpenSuSE等等。如果是用在服务器上面的，建议使用商业版本，包括Red Hat, SuSE等。 这是因为社群版通常开发者会加入最新的软件，这些软件可能会有一些bug存在。至于商业版则是经过一段时间的磨合后， 才将稳定的软件放进去。

举例来说，Fedora兜出来的软件套件经过一段时间的维护后，等到该软件稳定到不容易发生错误后， Red Hat才将该软件放到他们最新的释出版本中。所以，Fedora的软件比较经常改版，Red Hat的软件就较少更版

- Linux在台湾

  当然发行套件者不仅于此。但是值得大书特书的，是中文Linux的延伸计划：CLE这个套件！早期的Linux因为是工程师发展的，而这些工程师大多以英文语系的国家为主， 所以Linux对于国人的学习是比较困扰一点。后来由国人发起的CLE计划， 开发很多的中文套件及翻译了很多的英文文件，使得我们目前得以使用中文的Linux呢。

那我到底应该要选择哪一个distributions？就如同我们上面提到的，其实每个distributions差异性并不大！ 不过，由于套件管理的方式主要分为Debian的dpkg及Red Hat系统的RPM方式，目前鸟哥的建议是，先学习以RPM套件管理为主的RHEL/Fedora/SuSE/CentOS等台湾使用者较多的版本， 这样一来，发生问题时，可以提供解决的管道比较多。如果你已经接触过Linux了， 还想要探讨更严谨的Linux版本，那可以考虑使用Debian，如果你是以性能至上来考虑， 那么或许Gentoo是不错的建议！

- 用于企业环境：建议使用商业版本，例如Red Hat的RHEL或者是SuSE都是很不错的选择。
- 用于个人或教学的服务器环境：要是你的服务器所在环境如果死机还不会造成太大的问题的话， 加上你的环境是在教学的场合当中时（就是说，唔！经费不足的环境啦！）那么可以使用“号称”完全相容商业版RHEL的CentOS。 因为CentOS是抓RHEL的源代码来重新兜起来的一个Linux distribution，所以号称相容于RHEL。 这一版的软件完全与
  RHEL相同，在改版的幅度较小，适合于服务器系统的环境；

### 1.3 Linux当前的应用角色

#### 1.3.1 企业环境的利用

企业对于数码化的目标在于提供消费者或员工一些产品方面的信息 （例如网页介绍），以及整合整个企业内部的数据统一性 （例如统一的帐号管理/文件管理系统等）。另外，某些企业例如金融业等，则强调在数据库、安全强化等重大关键应用。 学术单位则很需要强大的运算能力等。所以企业环境运用Linux作些什么呢？

- 网络服务器

  这是Linux当前最热门的应用了！承袭了Unix高稳定性的良好传统，Linux上面的网络功能特别的稳定与强大！ 此外，由于GNU计划与Linux的GPL授权模式，让很多优秀的软件都在Linux上面发展， 且这些在Linux上面的服务器软件几乎都是自由软件！因此，做为一部网络服务器，例如WWW, Mail Server, File Server等等，Linux绝对是上上之选

从上面的几个大厂的 Linux 支持情况来看，目前 （2015） 支持度比较广泛的依旧是 Red Hat以及 SuSU 两个大厂喔！ 提估给企业采购的时候参考参考！

- 学术机构的高性能运算任务
- 关键任务的应用（金融数据库、大型企业网管环境）

**丛集计算机系统（Cluster）的平行运算能力在近年来一直
被拿出来讨论，平行运算指的是“将原本的工作分成多份，然后交给多部主机去运算，最终再将结果收集起来”的一种方式。由于通过高速网络使用到多部主机，将能够让原本需要很长运算时间的工作，大幅的降低等待的时间！ 例如中央气象局的气象预报就很需要这样的系统来帮忙！而Linux操作系统则是这种架构下相当重要的一个环境平台呢！**

#### 1.3.2).个人环境的使用

- 桌面电脑

  所谓的桌面电脑，其实就是你我在办公室使用的计算机啦。一般我们称之为Desktop的系统。那么这个 Desktop 的系统平时都在做什么呢？大概都是这些工作吧：

  - 上网浏览+实时通讯（Skype, FB, Google, Yahoo...）；
  - 文书处理；
  - 网络接口之公文处理系统；
  - 办公室软件（Office Software）处理数据；
  - 收发电子邮件

- 手持系统（PDA、手机）

- 嵌入式系统：

  在第零章当中我们谈到过硬件系统， 而要让硬件系统顺利的运行就得要撰写合适的操作系统才行。那硬件系统除了我们常看到的计算机之外， 其实家电产品、PDA、手机、数码相机以及其他微型的计算机配备也是硬件系统啦！ 这些计算机配备也都是需要操作系统来控制的！
  而**操作系统是直接嵌入于产品当中的，理论上你不应该会更动到这个操作系统**， 所以就称为嵌入式系统啦！

  包括：括路由器、防火墙、手机、IP分享器、交换器、机器人控制芯片、家电用品的微计算机控制器等等，都可以是Linux操作系统喔

  **要玩嵌入式系统必须要很熟悉Linux Kernel与驱动程序的结合才行！**这方面的学习可就不是那么简单喔

#### 1.3.3).云端应用

自从个人计算机的 CPU 内置的核心数越来越多常闲置，这个现象让虚拟化技术得以快速发展。而由于硬件资源大量集中化，然后行动办公
室之类的需求越来越多，因此让办公数据集中于云程序中，让企业员工仅须通过端点设备连线到云去取用运算资源， 这样就变成无时无地都可以办公啦

1）早期的大型主机分配数个终端机的集中运算机制

2）2010 年前个人计算机运算能力增强后，大部分的运算都是在台式机或笔记本上自行达成， 再也不需要跑去大型主机取得运算资源了！到现在

3）由于行动设备的发达，产生的庞大数据需要集中处理，因而产生云端系统的需求！让信息/资源集中管理！ 这不是分分合合的过程吗？

- 云程序

  许多公司都有将资源集中管理的打算，之前参与一场座谈会，有幸遇到阿里巴巴的架构师鸟哥偷偷问他说，他们机房里面有多少计算机主机啊？ 他说不多！差不多才 2 万部主机已...鸟哥正在搞的可提供 200 个左右的虚拟机的系统，使用大约 7 部主机就觉得麻烦了们家至少有 2 万部耶！ 这么多的设备底层使用的就是 Linux 操作系统来统一管理。

另外，除了公司自己内部的私有云之外，许多大型网际网络供应商 （ISP） 也提供了所谓的公有云来让企业用户或个人用户来使用 ISP 的虚拟化产品。 因此，如果公司内部缺乏专业管理维护人才，很有可能就将自家所需要的关键应用如 Web、Mail、系统开发环境等操作系统交由 ISP 代管， 自家公司仅须远端登陆该系统进行网站内容维护或程序开发而已。

**总结：所谓的“虚拟化”指的是：在一部实体主机上面仿真出多个逻辑上完全独立的硬件，这个假的虚拟出来的硬件主机，可以用来安装一部逻辑上完全独立的操作系统！因此，通过虚拟化技术，你可以将一部实体主机安装多个同时运行的操作系统 （非多重开机），以达到将硬件资源完整利用的效果。 很多 ISP 就是通过贩售这个虚拟机的使用权来赚钱的喔**

- 端设备

  既然运算资源都集中在云里面了，那我需要连线到云程序的设备应该可以越来越轻量吧？当然没错！所以智能手机才会这么热门啊！ 很多时候你只要有智能手机或者是平板，连线到公司的云里面去，就可以开始办公了哩！

  此外，还有更便宜的端点设备喔！那就是近年来很热门又流行的树莓派 （Raspberry Pi） 与香蕉派 （Banana Pi），这两个小东西售价都不到 50 美元， 有的甚至台币 1000 块有找！这个 Raspberry Pi 其实就是一部小型的计算机，只要加上 USB 键盘、鼠标与 HDMI 的屏幕，立刻就是可以让小朋友学习程序语言的环境！ 如果加上通过网络去取得具有更强大运算资源的云端虚拟机，不就可以做任何事了吗？所以，端点设备理论上会越来越轻量化的！

**Tips 鸟哥近几年来做的主要研究，就是通过一组没很贵的 server 系统达成打开多个虚拟机的环境，然后让学生可以在教室利用类似 banana pi 的设备来连线到服务器， 这时学生就可以通过网络来取得一套完整的操作系统，可以拿来上课、回家实作练习、上机考试等等！相当有趣！鸟哥称为虚拟计算机教室！**

### 1.4 Linux 该如何学习

以服务器或者是嵌入式系统的应用来说，X Window是非必备的软件，因为服务器是要提供用户端来连线的， 并不是要让使用者直接在这部服务器前面按键盘或鼠标来操作的！所以图形接口当然就不是这么重要了！ 更多的时候甚至大家会希望你不要启动X window在服务器主机上，这是因为X Window通常会吃掉很多系统资源的缘故！再举个例子来说，假如你是个软件服务的工程师，你的客户人在台北，而你人在远方的台南。某一天客户来电说他的Linux服务器出了问题， 要你马上解决他，请问：要您亲自上台北去修理？还是他搬机器下来让你修理？或者是直接请他开个帐号给你进去设置即可？ 想当尔，就会选择开帐号给你进入设置即可啰！因为这是最简单而且迅速的方法！这个方法通常使用命令行会较为单纯， 使用图形接口则非常麻烦啦！所以啦！这时候就得要学学命令行来操作Linux比较好啦！

在服务器的应用上，文件的安全性、人员帐号的管理、软件的安装/修改/设置、 登录文件的分析以及自动化工作调度与程序的撰写等等，都是需要学习的。

**这里是站在要让 Linux 成为自己的好用的工具 （服务器或开发软件的程序学习平台） 为出发点去介绍如何学习的喔**

#### 1.4.1).从头学习Linux基础

- 计算机概论与硬件相关知识

- 先从Linux的安装与指令学起

- Linux操作系统的基础技能:

  了解“使用者、群组的概念”、“权限的观念”，“程序的定义”等等，尤其是权限的概念， 由于不同的权限设置会妨碍你的使用者的便利性，但是
  太过于便利又会导致入侵的可能！ 所以这里需要了解一下你的系统呦！

- 务必学会vi文书编辑器： Linux的文书编辑器多到会让你数到生气！不过，vi却是强烈建议要先学习的！ 这是因为vi会被很多软件所调用，加上所有的Unix like系统上面都有vi，所以你一定要学会才好！

- Shell与Shell Script的学习： 其实鸟哥上面一直谈到的“命令行”说穿了就是一个名为shell的软件啦！既然要玩命令行，当然就是要会使用shell的意思。 但是shell上面的数据太多了，包括“正则表达式”、“管线命令”与“数据流重导向”等等，真的需要了解比较好呦！ 此外，为了帮助你未来的管理服务器的便利性，shell scripts也是挺重要的！要学要学！

- 一定要会软件管理员：

  Tarball/RPM/DPKG/YUM/APT等软件管理员的安装方式

- 网络基础的创建： 
  这部份包含了“IP概念”“路由概念”等等；

  

#### 1.4.2).选择一本易读的工具书

请推荐有关网络的书：http://linux.vbird.org/linux_basic/0120howtolinux/0120howtolinux_1.php

#### 1.4.3).实作再实作

#### 1.4.4).发生问题怎么处理啊？建议流程是这样

**1. 在自己的主机/网络数据库上查询How-To或FAQ**

其实，在Linux主机及网络上面已经有相当多的FAQ整理出来了！所以，当你发生任何问题的时候，除了自己检查， 或者到上述的实作网站上面查询一下是否有设置错误的问题之外，最重要的当然就是到各大FAQ的网站上查询啰！ 以下列出一些有用的FAQ与How-To网站给您参考一下

- Linux自己的文件数据： /usr/share/doc （在你的Linux系统中）
- CLDP 中文文件计划 http://www.linux.org.tw/CLDP/
- The Linux Documentation Project：http://www.tldp.org/

您也可以通过酷狗来找鸟哥网站上的数据呢！
Google： http://www.google.com.tw
鸟哥网站： http://linux.vbird.org/Searching.php
注意讯息输出，自行解决疑难杂症http://linux.vbird.org/Searching.php

**请注意，发
生错误的时候，请先自行以屏幕前面的信息来进行 debug（除错）的动作**

如果是网络服务的问题时，请到/var/log/这个目录里头去查阅一下 log file（登录文件），这样可以几乎解决大部分的问题了！

1. Netman大大给的建议：
   - 在Windows里面，程序有问题时，如果可能的话先将所有其它程序保存并结束，然后尝试按救命三键 （Ctrl+Alt+Delete），将有问题的程序（不要选错了程序哦）“结束工作”，看看能不能恢复系统。不要动不动就直接关机或reset。
   - 有系统地设计文件目录，不要随便到处保存盘案以至以后不知道放哪里了， 或找到文件也不知道为何物
   - 养成一个做记录的习惯。尤其是发现问题的时候， 把错误信息和引发状况以及解决方法记录清楚，同时最后归类及定期整理。别以为您还年轻，等你再弄多几年计算机了， 您将会非常庆幸您有此一习惯
   - 如果看在网络上看到任何好文章，可以为自己留一份copy，同时定好题目，归类存盘
   - 学写 script 的确没设置 server 那么好玩，不过以我自己的感觉是：关键是会得“偷”， 偷了会得改，改了会得变，变则通矣

#### 1.4.5). 鸟哥的建议（重点在solution的学习）

- 成就感
- 兴趣
  - 创建兴趣： Linux上面可以玩的东西真的太多了，你可以选择一个有趣的课题来深入的玩一玩！不论是Shell还是图形接口等等， 只要能够玩出兴趣，那么再怎么苦你都会不觉得喔！
  - 成就感：成就感是怎么来的？说实在话，就是“被认同”来的！怎么被认同呢？写心得分享啊！当你写了心得分享，并且公告在 BBS 上面，自然有朋友会到你的网页去瞧一瞧，当大家觉得你的网页内容很棒的时候， 哈哈！你肯定会加油继续的分享下去而无法自拔的！

除了这些基本的初学者建议外，其实，对于未来的学习，这里建议大家要“眼光看远！”一般来说，公司行号会发生问题时， 他们绝不会只要求各位“单独解决一部主机的问题”而已，他们需要的是整体环境的总体解决“Total Solution”。 而我们目前学习的Linux其实仅是在一部主机上面进行各项设置而已， 还没有到达解决整体公司所有问题的状态。当然啦，得要先学会Linux相关技巧后 才有办法将这些技巧用之于其他的solution上面！

所以，大家在学习Linux的时候，千万不要有“门户之见”，认为MS的东西就比较不好～ 否则，未来在职场上，竞争力会比人家弱的！有办法的话，多接触，不排斥任何学习的机会！都会带给自己很多的成长！ 而且要谨记：“不同的环境下，解决问题的方法有很多种，只要行的通，就是好方法。

### 1.5重点回顾

- 操作系统（Operation System）主要在于 **驱动硬盘与管理资源**，因此必须要能够管理内存、管理设备、 负责行程管理以及系统调用等等。因此，只要能够让硬件准备妥当（Ready）的情况， 就是一个好的操作系统了
- Unix的前身是由贝尔实验室（Bell lab.）的Ken Thompson利用组合语言写成的， 后来在1971-1973年间由Dennis Ritchie以C程序语言进行改写，才称为Unix。
- 1977年由Bill Joy释出BSD （Berkeley Software Distribution），这些称为Unix-like的操作系统
- 1984年由Andrew Tanenbaum开始制作Minix操作系统，该系统可以提供源代码以及软件；
- 1984年由Richard Stallman提倡GNU计划，倡导自由软件（Free software）， 强调其软件可以“自由的取得、复制、修改与再发行”，并规范出GPL授权模式， 任何GPL（General Public License）软件均不可单纯仅贩卖其软件，也不可修改软件授权
- 1991年由芬兰人Linus Torvalds开发出Linux操作系统。简而言之，Linux成功的地方主要在于： Minix（Unix）, GNU, Internet, POSIX 及虚拟团队的产生。
- 符合 Open source 理念的授权相当多，比较知名的如 Apache / BSD / GPL / MIT 等
- Linux本身就是个操作系统，其开发网站设立在http://www.kernel.org，我们亦称Linux操作系统最底层的数据为“核心（Kernel）”。
- Linux distributions的组成含有：“Linux Kernel + Free Software +
  Documentations（Tools） + 可完整安装的程序”所制成的一套完整的系统。
- 常见的 Linux distributions 分类有“商业、社群”分类法，或“RPM、DPKG”分类法

1.你的主机上面安装了一张网卡，但是开机之后，系统却无法使用，你确定网卡是好的，那么可能的问题出在哪里？

答：该如何解决？因为所有的硬件都没有问题，所以，可能出问题的地方在于系统的核心（kernel） 不支持这张网卡。解决方法（1）到网卡的开发商网站（2）下载支持你主机操作系统的驱动程序， （3）安装网卡驱动程序后，就可以使用

2.我在Windows上面玩的游戏，可不可以拿到Linux去玩？

答：当然不行！因为游戏也是一个应用程序 （application），他必须要使用到核心所提供的工具来开发他的游戏， 所以这个游戏是不可在不同的平台间运行的。除非这个游戏已经进行了移植。

3.Linux本身仅是一个核心与相关的核心工具而已，不过，他已经可以驱动所有的硬件， 所以可以算个操作系统了。经过其他应用程序的开发之后，被整合成为Linux distribitions。请问众多的distributions之间，有何异同？

答：相同：（1）同样使用http://www.kernel.org 所释出的核心；

​    				（2）相同的标准，如 FHS、LSB 等； 

​				    （3）使用几乎自由的软件。

​					（4）使用几乎相同的操作接口 

​      不同点： 不同的Kernel 与各软件的版本可能不同，各开发商加入的应用工具不同，使用的套件管理模式不同。

4.Unix 是谁写出来的？ GNU 计划是谁发起的？

答：Unix 是 Ken Thompson 写的，1973 年再由 Dennis Ritchie 以 C 语言改写成功。于 GNU 与 FSF 则是 Richard Stallman 发起的。

5.GNU 的全名为何？他主要由那个基金会支持？

答：GNU 是 GNU is Not Unix 的简写，是个无穷循环！ 另外，这个计划是由自由软件基金会 （Free Software Foundation, FSF） 所支持的。两者都是由 Stallman 先生所发起的！

6.何谓多用户 （ Multi-user ） 多任务 （ Multitask ）？

答：Multiuser 指的是 Linux 允许多人同时连上主机之外，每个使用者皆有其各人的使用环境，并且可以同时使用系统的资源！

Multitask 指的是多任务环境，在 Linux 系统下， CPU 与其他例如网络资源可以同时进多项工作， Linux 最大的特色之一即在于其多任务时，资源分配较为平均！

7.什么是 POSIX ?为何说 Linux 使用 POSIX 对于发展有很好的影响？

答：POSIX 是一种标准
规范，主要针对在 Unix 操作系统上面跑的程序来进行规范。 若你的操作系统符合POSIX ，则符合 POSIX 的程序就可以在你的操作系统上面运行。 Linux 由于支持POSIX ，因此很多 Unix 上的程序可以直接在 Linux 上运行， 因此程序的移植相当简易！也让大家容易转换平台，提升 Linux 的使用率

8.简单说明 Linux 成功的因素？

1.） 借由 Minix 操作系统开发的 Unix like ，没有版权的纠纷

2.） 借助于 GNU 计划所提供的各项工具软件， gcc/bash 等；

3.） 借由 Internet 广为流传；

4.） 借由支持 POSIX 标准，让核心能够适合所有软件的开发；

 

