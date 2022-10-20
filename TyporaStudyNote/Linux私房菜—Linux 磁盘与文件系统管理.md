# Linux私房菜—Linux 磁盘与文件系统管理

系统管理员很重要的任务之一就是管理好自己的磁盘文件系统，每个分区不可太大也不能太小， 太大会造成磁盘容量的浪费，太小则会产生文件无法储存的困扰。此外，我们在前面几章谈到的文件权限与属性中， 这些权限与属性分别记录在文件系统的哪个区块内？

这就得要谈到 `filesystem` 中的 `inode` 与 `block` 了，同时，为了虚拟化与大容量磁盘， 现在的 `CentOS 7` 默认使用大容量性能较佳的 `xfs` 当默认文件系统了。

**在本章我们的重点在于如何制作文件系统，包括分区、格式化与挂载等**

### 7.1 认识 Linux 文件系统

Linux 最传统的磁盘文件系统 （`filesystem）` 使用的是 `EXT2`，要了解 Linux 的文件系统就得要由认识 `EXT2` 开始！ 而文件系统是创建在磁盘上面的，因此我们得了解磁盘的物理组成才行。

重点在于 `inode`, block 还有 `superblock` 等文件系统的基本部分。

#### 7.1.1 磁盘组成与分区的复习

首先说明一下磁盘的物理组成，整颗磁盘的组成主要有：

- 圆形的盘片（主要记录数据的部分）；
- 机械手臂，与在机械手臂上的磁头（可读写盘片上的数据）；
- 主轴马达，可以转动盘片，让机械手臂的磁头在盘片上读写数据

从上面我们知道数据储存与读取的重点在于盘片，而盘片上的物理组成则为（假设此磁盘为单碟片

- 扇区（Sector）为最小的物理储存单位，且依据磁盘设计的不同，目前主要有 `512Bytes`与 `4K` 两种格式；
- 将扇区组成一个圆，那就是柱面（Cylinder）；
- 早期的分区主要以柱面为最小分区单位，现在的分区通常使用扇区为最小分区单位（每个扇区都有其号码喔，就好像座位一样）；
- 磁盘分区表主要有两种格式，一种是限制较多的 `MBR` 分区表，一种是较新且限制较少的`GPT` 分区表。
- `MBR` 分区表中，第一个扇区最重要，里面有：（1）主要开机区（Master boot record`,MBR`）及分区表（partition table）， 其中 `MBR` 占有 446 Bytes，而 partition table 则占有 64 Bytes
- `GPT` 分区表除了分区数量扩充较多之外，支持的磁盘容量也可以超过 `2TB`。

至于磁盘的文件名部份，基本上，所有实体磁盘的文件名都已经被仿真成 `/dev/sd[a-p]` 的格式，第一颗磁盘文件名为 `/dev/sda`。 而分区的文件名若以第一颗磁盘为例，则为 `/dev/sda[1-128]` 。除了实体磁盘之外，虚拟机的磁盘通常为 `/dev/vd[a-p]` 的格式。 若有使用到软件磁盘阵列的话，那还有 `/dev/md[0-128]` 的磁盘文件名。使用的是 `LVM` 时，文件名则为
`/dev/VGNAME/LVNAME` 等格式。 关于软件磁盘阵列与 `LVM` 我们会在后面继续介绍，这里主要介绍的以实体磁盘及虚拟磁盘为主！

- `/dev/sd[a-p][1-128`   为实体磁盘的磁盘文件名
- `/dev/vd[a-d][1-128`   为虚拟磁盘的磁盘文件名

以前磁盘分区最小单位经常是柱面，但 `CentOS 7` 的分区软件， 已经将最小单位改成扇区了，所以容量大的分区可以切的更细～此外，由于新的大容量磁盘大多得要使用 `GPT` 分区表才能够使用全部的容量， 因此过
去那个 `MBR` 的传统磁盘分区表限制就不会存在了。不过，由于还是有小磁盘啊！因此， 你在处理分区的时候，还是得要先查询一下，你的分区是 `MBR` 的分区？还是 `GPT` 的分区？

#### 7.1.2 文件系统特性

我们都知道磁盘分区完毕后还需要进行格式化（format），之后操作系统才能够使用这个文件系统。 为什么需要进行“格式化”呢？这是因为每种操作系统所设置的文件属性/权限并不相同， 为了存放这些文件所需的数据，因此就需要将分区进行格式化，以成为操作系统能够利用的“文件系统格式`（filesystem）`传统的磁盘与文件系统之应用中，一个分区就是只能够被格式化成为一个文件系统，所以我们可以说一个 `filesystem` 就是一个 partition。但是由于新技术的利用，例如我们常听到的`LVM`
与软件磁盘阵列（software raid）， 这些技术可以将一个分区格式化为多个文件系统（例如`LVM`），也能够将多个分区合成一个文件系统（`LVM`, RAID）！ 所以说，目前我们在格式化时已经不再说成针对 partition 来格式化了， 通常我们可以称呼一个可被挂载的数据为一个文件系统而不是一个分区喔！

文件系统是如何运行的？

答：这与操作系统的文件数据有关。较新的操作系统的文件数据除了文件实际内容外， 通常含有非常多的属性，例如 Linux 操作系统的文件权（`rwx`）与文件属性（拥有者、群组、时间参数等）。 文件系统通常会将这两部份的数据分别存放在不同的区块，权限与属性放置到 `inode` 中，至于实际数据则放置到 data block 区块中。另外，还有一个超级区块 （`superblock`） 会记录整个文件系统的整体信息，包括 `inode` 与 `block` 的总量、使用量、剩余量等。

每个 `inode` 与 block 都有编号，至于这三个数据的意义可以简略说明如下：

- `superblock：`记录此 `filesystem` 的整体信息，包括`inode/block`的总量、使用量、剩余量，以及文件系统的格式与相关信息等；

- `inode：`记录文件的属性，一个文件占用一个`inode，`同时记录此文件的数据所在的 block号码；

- block：实际记录文件的内容，若文件太大时，会占用多个 block。

  由于每个 `inode` 与 block 都有编号，而每个文件都会占用一个 `inode` ，`inode` 内则有文件数据放置的 block 号码。 因此，我们可以知道的是，如果能够找到文件的 `inode` 的话，那么自然就会知道这个文件所放置数据的 block 号码， 当然也就能够读出该文件的实际数据了。这是
  个比较有效率的作法，因为如此一来我们的磁盘就能够在短时间内读取出全部的数据， 读写的性能比较好。

我们将 `inode` 与 block 区块用图解来说明一下，如下图所示，文件系统先格式化出 `inode` 与block 的区块，假设某一个文件的属性与权限数据是放置到 `inode 4` 号，而这个 `inode` 记录了文件数据的实际放置点为 2, 7, 13, 15 这四个 block 号码。此时我们的操作系统就能够据此来排列磁盘的读取顺序，可以一口气将四个 block 内容读出来！ 那么数据的读取就如同下图中的箭头所指定的模样。

这种数据存取的方法我们称为索引式文件系统（indexed allocation），那有没有其他的惯用
文件系统可以比较一下啊？ 有的，那就是我们惯用的U盘（闪存），U盘使用的文件系统一般
为 FAT 格式。FAT 这种格式的文件系统并没有 `inode` 存在，所以 FAT 没有办法将这个文件的所有 block 在一开始就读取出来。每个 block 号码都记录在前一个 block 当中， 他的读取方式有点像下面这样：

我们假设文件的数据依序写入1->7->4->15号这四个 block 号码中， 但这个文件系统没有办法一口气就知道四个 block 的号码，他得要一个一个的将 block 读出后，才会知道下一个block 在何处。 如果同一个文件数据写入的 block 分散的太过厉害时，则我们的磁头将无法在磁盘转一圈就读到所有的数据， 因此磁盘就会多转好几圈才能完整的读取到这个文件的内容！

常常会听到所谓的“磁盘重组”吧？ 需要磁盘重组的原因就是文件写入的 block 太过于离散了，此时文件读取的性能将会变的很差所致。 这个时候可以通过磁盘重组将同一个文件所属的blocks 汇整在一起，这样数据的读取会比较容易啊！ 想当然尔，FAT 的文件系统需要三不五时的磁盘重组一下，那么 `Ext2` 是否需要磁盘重整呢？

由于 `Ext2` 是索引式文件系统，基本上不太需要常常进行磁盘重组的。但是如果文件系统使用太久， 常常删除/编辑/新增文件时，那么还是可能会造成文件数据太过于离散的问题，此时或许会需要进行重整一下的。

#### 7.1.3 Linux 的 `EXT2` 文件系统`（inode）`

过 Linux 的文件除了原有的数据内容外，还含有非常多的权限与属
性，这些权限与属性是为了保护每个使用者所拥有数据的隐密性。 而前一小节我们知道`filesystem` 里面可能含有的 `inode/block/superblock` 等。为什么要谈这个呢？因为标准的Linux 文件系统 `Ext2` 就是使用这种 `inode` 为基础的文件系统啦！

而如同前一小节所说的，`inode` 的内容在记录文件的权限与相关属性。至于 block 区块则是在记录文件的实际内容。并且文件系统一开始就规划好了`inode`与`block`,除非重新格式化。或者利用 `resize2fs` 等指令变更文件系统大小否则 `inode` 与 block 固定后就不再变动。但是如果仔细考虑一下，如果我的文件系统高达数百GB时， 那么将所有的 `inode` 与 block 通
通放置在一起将是很不智的决定，因为 `inode` 与 block 的数量太庞大，不容易管理。

为此之故，因此 `Ext2` 文件系统在格式化的时候基本上是区分为多个区块群组 （block group） 的，每个区块群组都有独立的`inode/block/superblock` 系统。感觉上就好像我们在当兵时，一个营里面有分成数个连，每个连有自己的联络系统， 但最终都向营部回报连上最正
确的信息一般！这样分成一群群的比较好管理啦！整个来说，`Ext2` 格式化后有点像下面这样：

在整体的规划当中，文件系统最前面有一个开机扇区（boot sector），这个开机扇区可以安装开机管理程序， 这是个非常重要的设计，因为如此一来我们就能够将不同的开机管理程序安装到个别的文件系统最前端，而不用覆盖整颗磁盘唯一的 `MBR`， 这样也才能够制作出多重开机的环境啊！至于每一个区块群组（block group）的六个主要内容说明如下：

- data block （数据区块）

  data block 是用来放置文件内容数据地方，在 `Ext2` 文件系统中所支持的 block 大小有 `1K, 2K及 4K` 三种而已。在格式化时 block 的大小就固定了，且每个 block 都有编号，以方便 `inode`的记录啦。 不过要注意的是，由于 block 大小的差异，会导致该文件系统能够支持的最大磁
  盘容量与最大单一文件大小并不相同。 因为 block 大小而产生的 `Ext2` 文件系统限制如下：

  | Block 大小         | `1KB`  | `2KB`   | `4KB`  |
  | ------------------ | ------ | ------- | ------ |
  | 最大单一文件限制   | `16GB` | `256GB` | `2TB`  |
  | 最大文件系统总容量 | `2TB`  | `8TB`   | `16TB` |

  

除此之外 `Ext2` 文件系统的 block 还有什么限制呢？有的！基本限制如下：

- 原则上，block 的大小与数量在格式化完就不能够再改变了（除非重新格式化）；
- 每个 block 内最多只能够放置一个文件的数据；
- 如果文件大于 block 的大小，则一个文件会占用多个 block 数量；
- 若文件小于 block ，则该 block 的剩余容量就不能够再被使用了（磁盘空间会浪费）。

由于每个 block 仅能容纳一个文件的数据而已，因此如果你的文件都非常
小，但是你的 block 在格式化时却选用最大的 `4K` 时，可能会产生一些容量的浪费。

例题：假设你的`Ext2`文件系统使用 `4K block` ，而该文件系统中有 10000 个小文件，每个文件大小均为 `50Bytes`， 请问此时你的磁盘浪费多少容量？

答：由于 `Ext2` 文件系统中一个 block仅能容纳一个文件，因此每个 block 会浪费“ 4096 - 50 = 4046 （Byte）”， 系统中总共有一万个小文件，所有文件大小为：50 （Bytes） x 10000 = `488.3KBytes`，但此时浪费的容量
为：“ 4046 （Bytes） x 10000 = `38.6MBytes` ”。想一想，不到 `1MB` 的总文件大小却浪费将近 `40MB` 的容量，且文件越多将造成越多的磁盘容量浪费。

好，既然大的 block 可能会产生较严重的磁盘容量浪费，那么我们是否就将 block 大小订为`1K` 即可？ 这也不妥，因为如果 block 较小的话，那么大型文件将会占用数量更多的 block ，而 `inode` 也要记录更多的 block 号码，此时将可能导致文件系统不良的读写性能。

事实上，现在的磁盘容量都太大了！所以，大概大家都只会选择 `4K` 的 block 大小。

- `inode table` （`inode` 表格）

再来讨论一下 `inode` 这个玩意儿吧！如前所述 `inode` 的内容在记录文件的属性以及该文件实际数据是放置在哪几号 block 内！ 基本上，`inode` 记录的文件数据至少有下面这些：

- 该文件的存取模式（`read/write/excute`）；
- 该文件的拥有者与群组（owner/group）；
- 该文件的容量；
- 该文件创建或状态改变的时间（`ctime`）；
- 最近一次的读取时间（`atime`）；
- 最近修改的时间（`mtime`）；
- 定义文件特性的旗标（flag），如 `SetUID...`；
- 该文件真正内容的指向 （pointer）；

`inode` 的数量与大小也是在格式化时就已经固定了，除此之外 `inode` 还有些什么特色呢？

答：

- 每个 `inode` 大小均固定为 128 Bytes （新的 `ext4` 与 `xfs` 可设置到 256 Bytes）；

- 每个文件都仅会占用一个 `inode` 而已

- 因此文件系统能够创建的文件数量与 `inode` 的数量有关；

- 系统读取文件时需要先找到 `inode`，并分析 `inode` 所记录的权限与使用者是否符合，若符合才能够开始实际读取 block 的内容。

  我们约略来分析一下 `EXT2` 的 `inode / block` 与文件大小的关系好了。`inode` 要记录的数据非常多，但偏偏又只有 `128Bytes` 而已， 而 `inode` 记录一个 block 号码要花掉 `4Byte` ，假设我一个文件有 `400MB` 且每个 block 为 `4K` 时， 那么至少也要十万笔 block 号码的记录呢！`inode` 哪有这么多可记录的信息？为此我们的系统很聪明的将 `inode` 记录 block 号码的区域定义为12个直接，一个间接, 一个双间接与一个三间接记录区。

  `inode` 本身 （128 Bytes），里面有 12 个直接指向 block 号码的对照，这 12笔记录就能够直接取得 block 号码啦！ 至于所谓的间接就是再拿一个 block 来当作记录 block号码的记录区，如果文件太大时， 就会使用间接的 block 来记录号码。当中间接只是拿一个 block 来记录额外的号码而已。 同理，如果文件持续长大，那么就会利用所谓
  的双间接，第一个 block 仅再指出下一个记录号码的 block 在哪里， 实际记录的在第二个block 当中。依此类推，三间接就是利用第三层 block 来记录号码啦！

  - 12 个直接指向： 12*1K=12K 由于是直接指向，所以总共可记录 12 笔记录，因此总额大小为如上所示；
  - 256*1K=256K 每笔 block 号码的记录会花去 4Bytes，因此 1K 的大小能够记录256 笔记录，因此一个间接可以记录的文件大小如上；
  - 双间接： 2562561K=2562K 第一层 block 会指定 256 个第二层，每个第二层可以指定256 个号码，因此总额大小如上；
  - 三间接： 256256256*1K=2563K 第一层 block 会指定 256 个第二层，每个第二层可以指定 256 个第三层，每个第三层可以指定 256个号码，因此总额大小如上；
  - 总额：将直接、间接、双间接、三间接加总，得到 12 + 256 + 256256 + 256256*256（K） = 16GB
  - 此时我们知道当文件系统将 block 格式化为 1K 大小时，能够容纳的最大文件为 16GB，比较一下文件系统限制表的结果可发现是一致的！但这个方法不能用在 2K 及 4K block 大小的计算中， 因为大于 2K 的 block 将会受到 Ext2 文件系统本身的限制，所以计算的结果会不太符合之故。

**总结：**如果你的 Linux 依旧使用 Ext2/Ext3/Ext4 文件系统的话，例如鸟哥之前的 CentOS 6.x系统，那么默认还是使用 Ext4 的文件系统喔！ Ext4 文件系统的 inode 容量已经可以扩大到256Bytes 了，更大的 inode 容量，可以纪录更多的文件系统信息，包括新的 ACL 以及SELinux 类型等， 当然，可以纪录的单一文件大小达 16TB 且单一文件系统总容量可达 1EB

- Superblock （超级区块）

  Superblock 是记录整个 filesystem 相关信息的地方， 没有 Superblock 就没有这个filesystem 了。他记录的信息主要有：

  - block 与 inode 的总量；
  - 未使用与已使用的 inode / block 数量；
  - block 与 inode 的大小 （block 为 1, 2, 4K，inode 为 128Bytes 或 256Bytes）；
  - filesystem 的挂载时间、最近一次写入数据的时间、最近一次检验磁盘 （fsck） 的时间等文件系统的相关信息
  - 一个 valid bit 数值，若此文件系统已被挂载，则 valid bit 为 0 ，若未被挂载，则 valid bit为 1 。

Superblock 是非常重要的，因为我们这个文件系统的基本信息都写在这里，因此，如果superblock 死掉了， 你的文件系统可能就需要花费很多时间去挽救啦！一般来说，superblock 的大小为 1024Bytes。相关的 superblock 讯息我们等一下会以 dumpe2fs 指令来调用出来观察

此外，每个 block group 都可能含有 superblock 喔！但是我们也说一个文件系统应该仅有一个 superblock 而已，那是怎么回事啊？ 事实上除了第一个 block group 内会含有 superblock之外，后续的 block group 不一定含有 superblock ， 而若含有 superblock 则该 superblock主要是做为第一个 block group 内 superblock 的备份咯，这样可以进行 superblock 的救援
呢！

- Filesystem Description （文件系统描述说明）

  这个区段可以描述每个 block group 的开始与结束的 block 号码，以及说明每个区段（superblock, bitmap, inodemap, data block） 分别介于哪一个 block 号码之间。这部份也能够用 dumpe2fs 来观察的。

- block bitmap （区块对照表）

  如果你想要新增文件时总会用到 block 吧！那你要使用哪个 block 来记录呢？当然是选择“空的 block ”来记录新文件的数据啰。 那你怎么知道哪个 block 是空的？这就得要通过 `blockbitmap` 的辅助了。从 block bitmap 当中可以知道哪些 block 是空的，因此我们的系统就能够很快速的找到可使用的空间来处置文件。

  同样的，如果你删除某些文件时，那么那些文件原本占用的 block 号码就得要释放出来， 此时在 block bitmap 当中相对应到该 block 号码的标志就得要修改成为“未使用中”啰！这就是bitmap 的功能

- `inode bitmap （inode 对照表）`

  这个其实与 block bitmap 是类似的功能，只是 block bitmap 记录的是使用与未使用的 block号码， 至于 inode bitmap 则是记录使用与未使用的 inode 号码

- dumpe2fs： 查询 Ext 家族 superblock 信息的指令

假设一块文件系统是 1GB 的容量，使用默认方式来进行格式化的， 观察的内容如下：

```
# dumpe2fs [-bh] 设备文件名
选项与参数：
-b ：列出保留为坏轨的部分（一般用不到吧！？）
-h ：仅列出 superblock 的数据，不会列出其他的区段内容！
// 假设一块 1GB ext4 文件系统内容
# blkid
// 这个指令可以叫出目前系统有被格式化的设备
/dev/vda1: LABEL="myboot" UUID="ce4dbf1b-2b3d-4973-8234-73768e8fd659" TYPE="xfs"
/dev/vda2: LABEL="myroot" UUID="21ad8b9a-aaad-443c-b732-4e2522e95e23" TYPE="xfs"
/dev/vda3: UUID="12y99K-bv2A-y7RY-jhEW-rIWf-PcH5-SaiApN" TYPE="LVM2_member"
/dev/vda5: UUID="e20d65d9-20d4-472f-9f91-cdcfb30219d6" TYPE="ext4"
// 看到 ext4
# dumpe2fs /dev/vda5
dumpe2fs 1.42.9 （28-Dec-2013）
Filesystem volume name:
// 文件系统的名称，不一定有
Last mounted on:
// 上一次被挂载的目录
Filesystem UUID: e20d65d9-20d4-472f-9f91-cdcfb30219d6
Filesystem magic number: 0xEF53
// 上方的 UUID 为 Linux 对设备的定义码
Filesystem revision #:1 （dynamic）
// 下方的 features 为文件系统的特征数据
Filesystem features: has_journal ext_attr resize_inode dir_index filetype extent 64bit
flex_bg sparse_super large_file huge_file uninit_bg dir_nlink extra_isize
Filesystem flags: signed_directory_hash
Default mount options: user_xattr acl
// 默认在挂载时会主动加上的挂载参数
Filesystem state:clean
Errors behavior: Continue
Filesystem OS type: Linux
Inode count: 65536
//  inode 的总数
Block count: 262144
//  block 的总数
Reserved block count: 13107
// 保留的 block 总数
Free blocks: 249189 
// 还有多少的 block 可用数量
Free inodes: 65525 
// 还有多少的 inode 可用数量
First block: 0
Block size: 4096 
// 单个 block 的容量大小
Fragment size: 4096
Group descriptor size: 64
....（中间省略）....
Inode size: 256 
// inode 的容量大小！已经是 256 了！
Journal inode: 8
Default directory hash: half_md4
Directory Hash Seed: 3c2568b4-1a7e-44cf-95a2-c8867fb19fbc
Journal backup: inode blocks
Journal features: （none）
Journal size: 32M 
// Journal 日志式数据的可供纪录总容量
Journal length: 8192
Journal sequence: 0x00000001
Journal start: 0
Group 0: （Blocks 0-32767） 
// 第一块 block group 位置
	Checksum 0x13be, unused inodes 8181
	Primary superblock at 0, Group descriptors at 1-1 
	// 主要 	superblock 的所在喔！
	Reserved GDT blocks at 2-128
	Block bitmap at 129 （+129）, Inode bitmap at 145 （+145）
	Inode table at 161-672 （+161）
	// inode table 的所在喔！
	28521 free blocks, 8181 free inodes, 2 directories, 8181 unused inodes
	Free blocks: 142-144, 153-160, 4258-32767
	// 下面两行说明剩余的容量有多少
	Free inodes: 12-8192
	Group 1: （Blocks 32768-65535） [INODE_UNINIT] 
	// 后续为更多其他的 block group 喔！
	
	//前半部在秀出 supberblock 的内容，包括标头名称（Label）以及inode/block的相关信息
	// 后面则是每个 block group 的个别信息了！您可以看到各区段数据所在的号码！
	// 也就是说，基本上所有的数据还是与 block 的号码有关就是了！很重要
```

如上所示，利用 dumpe2fs 可以查询到非常多的信息，不过依内容主要可以区分为上半部是superblock 内容， 下半部则是每个 block group 的信息.从上面的表格中我们可以观察到鸟哥这个 /dev/vda5 规划的 block 为 4K， 第一个 block 号码为 0 号，且 block group 内的所有信息都以 block 的号码来表示的.然后在 superblock 中还有谈到目前这个文件系统的可用block 与 inode 数量！

至于 block group 的内容我们单纯看 Group0 信息好了。从上表中我们可以发现：

- Group0 所占用的 block 号码由 0 到 32767 号，superblock 则在第 0 号的 block 区块内

- 文件系统描述说明在第 1 号 block 中；

- block bitmap 与 inode bitmap 则在 129 及 145 的 block 号码上

- 至于 inode table 分布于 161-672 的 block 号码中！

- 由于 （1）一个 inode 占用 256 Bytes ，

  2）总共有 672 - 161 + 1（161本身） = 512
  个 block 花在 inode table 上， （3）每个 block 的大小为 4096 Bytes（4K）。由这些数据可以算出 inode 的数量共有 512 * 4096 / 256 = 8192 个 inode 

- 这个 Group0 目前可用的 block 有 28521 个，可用的 inode 有 8181 个

- 剩余的 inode 号码为 12 号到 8192 号

那么这个文件系统概念与实际的目录树应用有啥关联啊？

#### 7.1.4 与目录树的关系

道在 Linux 系统下，每个文件（不管是一般文件还是目录文件）都会占用一个 inode ， 且可依据文件内容的大小来分配多个 block 给该文件使用。而由第五章的权限说明中我们知道目录的内容在记录文件名， 一般文件才是实际记录数据内容的地方。那么目录与文件在文件系统当中是如何记录数据的呢？基本上可以这样说：

- 目录

  当我们在 Linux 下的文件系统创建一个目录时，文件系统会分配一个 inode 与至少一块 block给该目录。inode 记录该目录的相关权限与属性，并可记录分配到的那块 block 号码；而 block 则是记录在这个目录下的文件名与该文件名占用的 inode 号码数据。也就是说目录所
  占用的 block 内容在记录如下的信息。

  | Inoder number | 文件名  |
  | ------------- | ------- |
  | 53735697      | cdf.cfg |

  ```
  # ls -li
  total 8
  53735697 -rw-------. 1 root root 1816 May 4 17:57 anaconda-ks.cfg
  53745858 -rw-r--r--. 1 root root 1864 May 4 18:01 initial-setup-ks.cfg
  实际观察 root 主文件夹内的文件所占用的 inode 号码时，可以使用 ls -i 这个选项来处理：
  ```

  由于每个人所使用的计算机并不相同，系统安装时选择的项目与 partition 都不一样，因此你的环境不可能与我的 inode 号码一模一样

  当你使用“ ll / ”时，出现的目录几乎都是 1024 的倍数，为什么呢？因为每个 block 的数量都是 1K, 2K, 4K

  ```
  ll -d / /boot /usr/sbin /proc /sys
  dr-xr-xr-x. 17 root root 4096 May 4 17:56 / 
  // 1 个 4K block
  dr-xr-xr-x. 4 root root 4096 May 4 17:59 /boot
  // 1 个 4K block
  dr-xr-xr-x. 155 root root 0 Jun 15 15:43 /proc 
  // 这两个为内存内数据，不占磁盘容量
  dr-xr-xr-x. 13 root root 0 Jun 15 23:43 /sys
  dr-xr-xr-x. 2 root root 16384 May 4 17:55 /usr/sbin 
  // 4 个 4K block
  ```

**由上面的结果我们知道目录并不只会占用一个 block 而已，也就是说： 在目录下面的文件数如果太多而导致一个 block 无法容纳的下所有的文件名与 inode 对照表时，Linux 会给予该目录多一个 block 来继续记录相关的数据.**

- 文件

  当我们在 Linux 下的 ext2 创建一个一般文件时， ext2 会分配一个 inode 与相对于该文件大小的 block 数量给该文件。。例如：假设我的一个 block 为 4 KBytes ，而我要创建一个 100KBytes 的文件，那么 linux 将分配一个 inode 与 25 个 block 来储存该文件！ 但同时请注意，
  由于 inode 仅有 12 个直接指向，因此还要多一个 block 来作为区块号码的记录喔！

- 目录树读取：

  好了，经过上面的说明你也应该要很清楚的知道 inode 本身并不记录文件名，文件名的记录是在目录的 block 当中，我们才会提到“新增/删除/
  更名文件名与目录的 w 权限有关”的特色！那么因为文件名是记录在目录的 block 当中。因此，当我们要读取某个文件时，就务必会经过目录的 **inode 与 block** ，然后才能够找到那个待读取**文件的 inode 号码，** 最终才会读到正确的**文件的 block 内的数据。**

由于目录树是由根目录开始读起，因此**系统通过挂载的信息可以找到挂载点的 inode 号码**，此时就能够得到根目录的 inode 内容，并依据该 inode 读取根目录的 block 内的文件名数据，再一层一层的往下读到正确的文件名。

举例来说，如果我想要读取 /etc/passwd 这个文件时，系统是如何读取的呢？

```
# ll -di / /etc /etc/passwd
128 dr-xr-xr-x. 17 root root 4096 May 4 17:56 /
33595521 drwxr-xr-x. 131 root root 8192 Jun 17 00:20 /etc
36628004 -rw-r--r--. 1 root root 2092 Jun 17 00:20 /etc/passwd

```

（假设读取者身份为 dmtsai 这个一般身份使用者)读取的流程如下：

- / 的 inode： 通过挂载点的信息找到 inode 号码为 128 的根目录 inode，且 inode 规范的权限让我们可以读取该 block 的内容（有 r 与 x）

- / 的 block： 经过上个步骤取得 block 的号码，并找到该内容有 etc/ 目录的 inode 号码（33595521）

- etc/ 的 inode： 读取 33595521 号 inode 得知 dmtsai 具有 r 与 x 的权限，因此可以读取etc/ 的 block 内容；

- etc/ 的 block： 经过上个步骤取得 block 号码，并找到该内容有 passwd 文件的 inode 号码 （36628004）；

- passwd 的 inode： 读取 36628004 号 inode 得知 dmtsai 具有 r 的权限，因此可以读取passwd 的 block 内容；passwd 的 block： 最后将该 block 内容的数据读出来。

- filesystem 大小与磁盘读取性能

  另外，关于文件系统的使用效率上，当你的一个文件系统规划的很大时，例如 100GB 这么大时， 由于磁盘上面的数据总是来来去去的，所以，整个文件系统上面的文件通常无法连续写在一起（**block 号码不会连续的意思**） 而是**填入式的将数据填入没有被使用的 block 当中**。
  如果文件写入的 block 真的分的很散， 此时就会有所谓的文件数据离散的问题发生了。

虽然我们的 ext2 在 inode 处已经将该文件所记录的 block 号码都记上了， 所以数据可以一次性读取，但是如果文件真的太过离散，确实还是会发生读取效率低落的问题。 因为磁头还是得要在整个文件系统中来来去去的频繁读取！ 果真如此，那么可以将整个filesystme 内的数据全部复制出来，将该 filesystem 重新格式化， 再将数据给他复制回去即可解决这个问题。

此外，如果 filesystem 真的太大了，那么当一个文件分别记录在这个文件系统的最前面与最后面的 block 号码中， 此时会造成磁盘的机械手臂移动幅度过大，也会造成数据读取性能的低落。而且磁头在搜寻整个 filesystem 时， 也会花费比较多的时间去搜寻！因此， partition的规划并不是越大越好， 而是真的要针对您的主机用途来进行规划才行！

#### 7.1.5 EXT2/EXT3/EXT4 文件的存取与日志式文件系统的功能

上一小节谈到的仅是读取而已，那么如果是新建一个文件或目录时，我们的文件系统是如何处理的呢？ 这个时候就得要 block bitmap 及 inode bitmap 的帮忙了！假设我们想要新增一个文件，此时文件系统的行为是：

1. . 先确定使用者对于欲新增文件的目录是否具有 w 与 x 的权限，若有的话才能新增；
2. 根据 inode bitmap 找到没有使用的 inode 号码，并将新文件的权限/属性写入；
3. 根据 block bitmap 找到没有使用中的 block 号码，并将实际的数据写入 block 中，且更新 inode 的 block 指向数据；
4. 将刚刚写入的 inode 与 block 数据同步更新 inode bitmap 与 block bitmap，并更新superblock 的内容

一般来说，我们将 inode table 与 data block 称为数据存放区域，（就是inode与block）至于其他例如 superblock、block bitmap 与 inode bitmap 等区段就被称为 metadata （中介数据）。，因为 superblock, inode bitmap 及 block bitmap 的数据是经常变动的，每次新增、移除、编辑时都可能会影响到这三个部分的数据，因此才被称为中介数据

- 数据的不一致 （Inconsistent） 状态

在一般正常的情况下，上述的新增动作当然可以顺利的完成。但是如果有个万一怎么办？ 例如你的文件在写入文件系统时，因为不知名原因导致系统中断（例如突然的停电啊、 系统核心发生错误啊～等等的怪事发生时），所以写入的数据仅有 inode table 及 data block 而已，最后一个同步更新中介数据的步骤并没有做完，此时就会发生 metadata 的内容与实际数据存放区产生不一致 （Inconsistent） 的情况。

既然有不一致当然就得要克服！在早期的 Ext2 文件系统中，如果发生这个问题， 那么系统在重新开机的时候，就会借由 Superblock 当中记录的 valid bit （是否有挂载） 与 filesystemstate （clean 与否） 等状态来判断是否强制进行数据一致性的检查！若有需要检查时则以e2fsck 这支程序来进行的

这样的检查真的是很费时～因为要针对 metadata 区域与实际数据存放区来进行比对，得要搜寻整个 filesystem 呢～如果你的文件系统有 100GB 以上，而且里面的文件数量又多时， 系统真忙碌～而且在对 Internet 提供服务的服务器主机上面， 这样的检查真的会造成主机复原时间的拉长～真是麻烦～这也就造成后来所谓日志式文件系统的兴起了。

- 日志式文件系统 （Journaling filesystem）

为了避免上述提到的文件系统不一致的情况发生，因此我们的前辈们想到一个方式， 如果在我们的 filesystem 当中规划出一个区块，该区块专门在记录写入或修订文件时的步骤， 那不就可以简化一致性检查的步骤了。也就是说：

1. 预备：当系统要写入一个文件时，会先在日志记录区块中纪录某个文件准备要写入的信息；
2. 实际写入：开始写入文件的权限与数据；开始更新 metadata 的数据
3. 结束：完成数据与 metadata 的更新后，在日志记录区块当中完成该文件的纪录

在这样的程序当中，万一数据的纪录过程当中发生了问题，那么我们的系统只要去检查日志记录区块， 就可以知道哪个文件发生了问题，针对该问题来做一致性的检查即可，而不必针对整块 filesystem 去检查， 这样就可以达到快速修复 filesystem 的能力了！这就是日志式文件最基础的功能

那么我们的 ext2 可达到这样的功能吗？当然可以啊！ 就通过 ext3/ext4 即可！ ext3/ext4 是ext2 的升级版本，并且可向下相容 ext2 版本呢！ 所以啰，目前我们才建议大家，可以直接使用 ext4 这个 filesystem 啊！ 如果你还记得 dumpe2fs 输出的讯息，可以发现 superblock 面含有下面这样的信息：

```
Journal inode: 8
Journal backup: inode blocks
Journal features: （none）
Journal size: 32M
Journal length: 8192
Journal sequence: 0x00000001
```

通过 inode 8 号记录 journal 区块的 block 指向，而且具有 32MB 的容量在处理日志。

#### 7.1.6 Linux 文件系统的运行

目录树与文件系统的关系了，但是由第零章的内容我们也知道， 所有的数据
都得要**载入到内存后 CPU 才能够对该数据进行处理**。想一想，如果你常常编辑一个好大的文件， 在编辑的过程中又频繁的要系统来写入到磁盘中，由于磁盘写入的速度要比内存慢很多， 因此你会常常耗在**等待磁盘的写入/读取**上。真没效率！

为了解决这个效率的问题，因此我们的 Linux 使用的方式是通过一个称为非同步处理（asynchronously） 的方式。所谓的非同步处理是这样的：

当系统载入一个文件到内存后，如果该文件没有被更动过，则在内存区段的文件数据会被设置为干净（clean）。但如果内存中的文件数据被更改过了（例如你用 nano 去编辑过这个文件），此时该内存中的数据会被设置为脏的 （Dirty），此时所有的动作都还在内存中执行，并没有写入到磁盘中！

**系统是不定时的将内存中设置为“Dirty”的数据写回磁盘。以保持
磁盘与内存数据的一致性。**你也可以利用第四章谈到的 sync指令来手动强迫写入磁盘。

我们知道内存的速度要比磁盘快的多，因此如果能够将常用的文件放置到内存当中，这不就会增加系统性能吗？ 没错！是有这样的想法！因此我们 Linux 系统上面文件系统与内存有非常大的关系

- 系统会将常用的文件数据放置到内存的缓冲区，以加速文件系统的读/写；
- 因此 Linux 的实体内存最后都会被用光！这是正常的情况！可加速系统性能
- 你可以手动使用 sync 来强迫内存中设置为 Dirty 的文件回写到磁盘中；
- 若正常关机时，关机指令会主动调用 sync 来将内存的数据回写入磁盘内；
- 但若不正常关机（如跳电、死机或其他不明原因），由于数据尚未回写到磁盘内， 因此重新开机后可能会花很多时间在进行磁盘检验，甚至可能导致文件系统的损毁（非磁盘损毁）

#### 7.1.7 挂载点的意义 （mount point）

每个 filesystem 都有独立的 inode / block / superblock 等信息，这个文件系统要能够链接到目录树才能被我们使用。**将文件系统与目录树结合的动作我们称为“挂载”**挂载的特性：**挂载点一定是目录，该目录为进入该文件系统的入口**，也就是说：并不是你有的文件系统都可以使用，而是你的文件系统必须要与某个目录树结合起来。然后才能使用这个文件系统。

举例来说，如果你是安装 CentOS 7.x 的话， 那么应该会有三个挂载点才是，分别是 /, /boot, /home 三个 （系统上对应的设备文件名为 LVM,LVM,/dev/vda2）。 那如果观察这三个目录的 inode 号码时，我们可以发现如下的情况：

```
# ls -lid / /boot /home
128 dr-xr-xr-x. 17 root root 4096 May 4 17:56 /
128 dr-xr-xr-x. 4 root root 4096 May 4 17:59 /boot
128 drwxr-xr-x. 5 root root 41 Jun 17 00:20 /home
```

因为每一行的文件属性并不相同，且三个目录的挂载点也均不相同，因此可以发现 /,/boot, /home 为三个不同的 filesystem 

到根目录下的 . 与 .. 是相同的东西， 因为权限是一模一样嘛！如果使用文件系统的观点来看，同一个 filesystem 的某个 inode 只会对应到一个文件内容而已（因为一个文件占用一个 inode 之故）， 因此我们可以通过判断 inode 号码来确认不同文件名是否为相同的文件喔！所以可以这样看

```
# ls -ild / /. /..
128 dr-xr-xr-x. 17 root root 4096 May 4 17:56 /
128 dr-xr-xr-x. 17 root root 4096 May 4 17:56 /.
128 dr-xr-xr-x. 17 root root 4096 May 4 17:56 /..
```

上面的信息中由于挂载点均为 / ，因此三个文件 （/, /., /..） 均在同一个 filesystem 内，而这三个文件的 inode 号码均为 128 号，因此这三个文件名都指向同一个 inode 号码，当然这三个文件的内容也就完全一模一样了！ 也就是说，根目录的上层 （/..） 就是他自己。

#### 7.1.8 其他 Linux 支持的文件系统与 VFS

虽然 Linux 的标准文件系统是 ext2 ，且还有增加了日志功能的 ext3/ext4 ，事实上，Linux 还有支持很多文件系统格式的， 尤其是最近这几年推出了好几种速度很快的日志式文件系统，包括 SGI 的 XFS 文件系统， 可以适用更小型文件的 Reiserfs 文件系统，以及 Windows 的FAT 文件系统等等， 都能够被 Linux 所支持喔！常见的支持文件系统有：

- 传统文件系统：ext2 / minix / MS-DOS / FAT （用 vfat 模块） / iso9660 （光盘）等等；
- 日志式文件系统： ext3 /ext4 / ReiserFS / Windows' NTFS / IBM's JFS / SGI's XFS /ZFS
- 网络文件系统： NFS / SMBFS

想要知道你的 Linux 支持的文件系统有哪些，可以察看下面这个目录：

```
# ls -l /lib/modules/$（uname -r）/kernel/fs
```

系统目前已载入到内存中支持的文件系统则有：

```
# cat /proc/filesystems
```

- **Linux VFS**

 Linux 的核心又是如何管理这些认识的文件系统呢？ 

答：，整个 Linux 的系统都是通过一个名为 Virtual Filesystem Switch 的核
心功能去读取 filesystem 的，也就是说，整个 Linux 认识的 filesystem 其实都是 VFS 在进行管理，我们使用者并不需要知道每个 partition 上头的 filesystem 是什么～ VFS 会主动的帮我们做好读取的动作

假设你的 / 使用的是 /dev/hda1 ，用 ext3 ，而 /home 使用 /dev/hda2 ，用 reiserfs ， 那么你取用 /home/dmtsai/.bashrc 时，有特别指定要用的什么文件系统的模块来读取吗？ 

答：应该是没有吧！这个就是 VFS 的功能啦！通过这个 VFS 的功能来管理所有的 filesystem， 省去我们需要自行设置读取文件系统的定义

#### 7.1.9 XFS 文件系统简介

CentOS 7 开始，默认的文件系统已经由原本的 EXT4 变成了 XFS 文件系统了！为啥CentOS 要舍弃对 Linux 支持度最完整的 EXT 家族而改用 XFS 呢？ 这是有一些原因存在的

- EXT 家族当前较伤脑筋的地方：支持度最广，但格式化超慢！

  Ext 文件系统家族对于文件格式化的处理方面，采用的是预先规划出所有的 inode/block/metadata 等数据，未来系统可以直接取用， 不需要再进行动态配置的作法。这个作法在早期磁盘容量还不大的时候还算 OK 没啥问题，但时至今日，磁盘容量越来越大，连传统的 MBR 都已经被 GPT 所取代，连我们这些老人家以前听到的超大 TB 容量也已经不够看了！现在都已经说到 PB 或 EB 以上容量了呢！那你可以想像得到，当你的 TB 以上等级的传统 ext 家族文件系统在格式化的时候，光是系统要预先分配 inode 与 block 就消耗你好多好多的人类时间了...

  之前格式化过一个 70 TB 以上的磁盘阵列成为 ext4 文件系统，按下格式化，去喝了咖啡、吃了便当才回来看做完了没有... 所以，后来立刻改成 xfs 文件系统。

**由于虚拟化的应用越来越广泛，而作为虚拟化磁盘来源的巨型文件 （单一文件好几个GB 以上！） 也就越来越常见了。 这种巨型文件在处理上需要考虑到性能问题，否则虚拟磁盘的效率就会不太好看。因此，从 CentOS 7.x 开始， 文件系统已经由默认的 Ext4 变成了xfs 这一个较适合大容量磁盘与巨型文件性能较佳的文件系统了。**

- **XFS 文件系统的配置 ：**

基本上 xfs 就是一个日志式文件系统，而 CentOS 7.x 拿它当默认的文件系统，自然就是因为最早之前，这个 xfs 就是被开发来用于大容量磁盘以及高性能文件系统之用， 因此，相当适合现在的系统环境。此外，几乎所有 Ext4 文件系统有的功能， xfs 都可以具备！也因此在本小节前几部份谈到文件系统时， 其实大部份的操作依旧是在 xfs 文件系统环境下介绍。

xfs 文件系统在数据的分佈上，主要规划为三个部份，一个数据区 （data section）、一个文件系统活动登录区 （log section）以及一个实时运行区 （realtime section）。 这三个区域的数据内容如下：

- 数据区 （data section）

基本上，数据区就跟我们之前谈到的 ext 家族一样，包括 inode/data block/superblock 等数据，都放置在这个区块。 这个数据区与 ext 家族的 block group 类似，也是分为多个储存区群组 （allocation groups） 来分别放置文件系统所需要的数据。每个储存区群组都包含了（1）整个文件系统的 superblock、 （2）剩余空间的管理机制、 （3）inode的分配与追踪。此外，inode与 block 都是系统需要用到时， 这才动态配置产生，所以格式化动作超级快！与 ext 家族不同的是， xfs 的 block 与 inode 有多种不同的容量可供设置，block 容量可由 512Bytes ~ 64K 调配，不过，Linux 的环境下， 由于内存控制的关系 （分页档pagesize 的容量之故），因此最高可以使用的 block 大小为 4K 而已

总之， xfs 的这个数据区的储存区群组 （allocation groups, AG），你就将它想成是 ext家族的 block 群组 （block groups） 就对了。只是 inode 与 block 是动态产生，并非一开始于格式化就完成配置的。

- 文件系统活动登录区 （log section）

  在登录区这个区域主要被用来纪录文件系统的变化，其实有点像是日志区啦！文件的变化会在这里纪录下来，直到该变化完整的写入到数据区后， 该笔纪录才会被终结。如果文件系统因为某些缘故 （例如最常见的停电） 而损毁时，系统会拿这个登录区块来进行检验，看看系统挂掉之前， 文件系统正在运行些啥动作，借以快速的修复文件系统。

  因为系统所有动作的时候都会在这个区块做个纪录，因此这个区块的磁盘活动是相当频繁的！xfs 设计有点有趣，在这个区域中， 你可以指定外部的磁盘来作为 xfs 文件系统的日志区块喔！例如，你可以将 SSD 磁盘作为 xfs 的登录区，这样当系统需要进行任何活动时， 就可以更快速的进行工作！相当有趣！

- 实时运行区 （realtime section）

  当有文件要被创建时，xfs 会在这个区段里面找一个到数个的 extent 区块，将文件放置在这个区块内，等到分配完毕后，再写入到 data section 的 inode 与 block 去！ 这个 extent 区块的大小得要在格式化的时候就先指定，最小值是 4K 最大可到 1G

- XFS 文件系统的描述数据观察

  可以使用 xfs_info 去观察。像 EXT 家族的 dumpe2fs 去观察superblock

  ```
  # xfs_info 挂载点&#124;设备文件
  ```

  ```
  范例一：找出系统 /boot 这个挂载点下面的文件系统的 superblock 纪录
  # df -T /boot
  Filesystem Type 1K-blocks Used Available Use% Mounted on
  /dev/vda2 xfs 1038336 133704 904632 13% /boot
  // 可以看得出来是 xfs 文件系统的！来观察一下内容吧
  # xfs_info /dev/vda2
  1 meta-data=/dev/vda2 isize=256 agcount=4, agsize=65536 blks
  2 = sectsz=512 attr=2, projid32bit=1
  3 = crc=0 finobt=0
  4 data = bsize=4096 blocks=262144, imaxpct=25
  5 = sunit=0 swidth=0 blks
  6 naming =version 2 bsize=4096 ascii-ci=0 ftype=0
  7 log =internal bsize=4096 blocks=2560, version=2
  8 = sectsz=512 sunit=0 blks, lazy-count=1
  9 realtime =none extsz=4096 blocks=0, rtextents=0
  ```

  - 第 1 行里面的 isize 指的是 inode 的容量，每个有 256Bytes 这么大。至于 agcount 则是前面谈到的储存区群组 （allocation group） 的个数，共有 4 个， agsize 则是指每个储存区群组具有 65536 个 block 。配合第 4 行的 block 设置为 4K，因此整个文件系统的容量应该就是 4655364K 这么大！
  - 第 2 行里面 sectsz 指的是逻辑扇区 （sector） 的容量设置为 512Bytes 这么大的意思
  - 第 4 行里面的 bsize 指的是 block 的容量，每个 block 为 4K 的意思，共有 262144 个block 在这个文件系统内
  - 第 5 行里面的 sunit 与 swidth 与磁盘阵列的 stripe 相关性较高。这部份我们下面格式化的时候会举一个例子来说明。
  - 第 7 行里面的 internal 指的是这个登录区的位置在文件系统内，而不是外部设备的意思。且占用了 4K * 2560 个 block，总共约 10M 的容量。
  - 第 9 行里面的 realtime 区域，里面的 extent 容量为 4K。不过目前没有使用.

### 7.2 文件系统的简单操作

如何查询整体文件系统的总容量与每个目录所占用的容量？

#### 7.2.1 磁盘与目录的容量

现在我们知道磁盘的整体数据是在 superblock 区块中，但是每个各别文件的容量则在 inode当中记载的。 那在命令行下面该如何叫出这几个数据呢？下面就让我们来谈一谈这两个指令

- df：列出文件系统的整体磁盘使用量；
- du：评估文件系统的磁盘使用量（常用在推估目录所占容量）

- df

  ```
  # df [-ahikHTm] [目录或文件名]
  选项与参数：
  -a ：列出所有的文件系统，包括系统特有的 /proc 等文件系统；
  -k ：以 KBytes 的容量显示各文件系统；
  -m ：以 MBytes 的容量显示各文件系统；
  -h ：以人们较易阅读的 GBytes, MBytes, KBytes 等格式自行显示；
  -H ：以 M=1000K 取代 M=1024K 的进位方式；
  -T ：连同该 partition 的 filesystem 名称 （例如 xfs） 也列出；
  -i ：不用磁盘容量，而以 inode 的数量来显示
  ```

  ```
  范例一：将系统内所有的 filesystem 列出来！
  [root@study ~]# df
  Filesystem 1K-blocks Used Available Use% Mounted on
  /dev/mapper/centos-root 10475520 3409408 7066112 33% /
  devtmpfs 627700 0 627700 0% /dev
  tmpfs 637568 80 637488 1% /dev/shm
  tmpfs 637568 24684 612884 4% /run
  tmpfs 637568 0 637568 0% /sys/fs/cgroup
  /dev/mapper/centos-home 5232640 67720 5164920 2% /home
  /dev/vda2 1038336 133704 904632 13% /boot
  // 在 Linux 下面如果 df 没有加任何选项，那么默认会将系统内所有的
  // （不含特殊内存内的文件系统与 swap） 都以 1 KBytes 的容量来列出来！
  // 至于那个 /dev/shm 是与内存有关的挂载，先不要理他！
  
  ```

  先来说明一下范例一所输出的结果讯息为：

  - Filesystem：代表该文件系统是在哪个 partition ，所以列出设备名称；
  - 1k-blocks：说明下面的数字单位是 1KB 呦！可利用 -h 或 -m 来改变容量
  - Used：顾名思义，就是使用掉的磁盘空间啦！
  - Available：也就是剩下的磁盘空间大小；
  - Use%：就是磁盘的使用率啦！如果使用率高达 90% 以上时， 最好需要注意一下了，免得容量不足造成系统问题喔！（例如最容易被灌爆的 /var/spool/mail 这个放置邮件的磁盘）
  - Mounted on：就是磁盘挂载的目录所在啦！（挂载点啦！）

```
范例二：将容量结果以易读的容量格式显示出来
# df -h
Filesystem Size Used Avail Use% Mounted on
/dev/mapper/centos-root 10G 3.3G 6.8G 33% /
devtmpfs 613M 0 613M 0% /dev
tmpfs 623M 80K 623M 1% /dev/shm
tmpfs 623M 25M 599M 4% /run
tmpfs 623M 0 623M 0% /sys/fs/cgroup
/dev/mapper/centos-home 5.0G 67M 5.0G 2% /home
/dev/vda2 1014M 131M 884M 13% /boot
// 不同于范例一，这里会以 G/M 等容量格式显示出来，比较容易看啦！
```

```
范例三：将系统内的所有特殊文件格式及名称都列出来
# df -aT
Filesystem Type 1K-blocks Used Available Use% Mounted on
rootfs rootfs 10475520 3409368 7066152 33% /
proc proc 0 0 0 - /proc
sysfs sysfs 0 0 0 - /sys
devtmpfs devtmpfs 627700 0 627700 0% /dev
securityfs securityfs 0 0 0 - /sys/kernel/security
tmpfs tmpfs 637568 80 637488 1% /dev/shm
devpts devpts 0 0 0 - /dev/pts
tmpfs tmpfs 637568 24684 612884 4% /run
tmpfs tmpfs 637568 0 637568 0% /sys/fs/cgroup
.....（中间省略）.....
/dev/mapper/centos-root xfs 10475520 3409368 7066152 33% /
selinuxfs selinuxfs 0 0 0 - /sys/fs/selinux
.....（中间省略）.....
/dev/mapper/centos-home xfs 5232640 67720 5164920 2% /home
/dev/vda2 xfs 1038336 133704 904632 13% /boot
binfmt_misc binfmt_misc 0 0 0 - /proc/sys/fs/binfmt_
// 系统里面其实还有很多特殊的文件系统存在的。那些比较特殊的文件系统几乎都是在内存当中，例如 /proc 这个挂载点。因此，这些特殊的文件系统 都不会占据磁盘空间
```

```
范例四：将 /etc 下面的可用的磁盘容量以易读的容量格式显示
#  df -h /etc
Filesy
// stem Size Used Avail Use% Mounted on
/dev/mapper/centos-root 10G 3.3G 6.8G 33% /
// 在 df 后面加上目录或者是文件时， df 会自动的分析该目录或文件所在的 partition ，并将该 partition 的容量显示出来，所以，您就可以知道某个目录下面还有多少容量可以使用了.
```

```
范例五：将目前各个 partition 当中可用的 inode 数量列出
# df -ih
Filesystem Inodes IUsed IFree IUse% Mounted on
/dev/mapper/centos-root 10M 108K 9.9M 2% /
devtmpfs 154K 397 153K 1% /dev
tmpfs 156K 5 156K 1% /dev/shm
tmpfs 156K 497 156K 1% /run
tmpfs 156K 13 156K 1% /sys/fs/cgroup
// 这个范例则主要列出可用的 inode 剩余量与总容量。分析一下与范例一的关系
// 你可以清楚的发现到，通常 inode 的数量剩余都比 block 还要多
```

由于 df 主要读取的数据几乎都是针对一整个文件系统，因此读取的范围主要是在 Superblock内的信息， 所以这个指令显示结果的速度非常的快速！在显示的结果中你需要特别留意的是那个根目录的剩余容量！ 因为我们所有的数据都是由根目录衍生出来的，因此当根目录的剩余容量剩下 0 时，那你的 Linux 可能就问题很大了

如果使用 -a 这个参数时，系统会出现 /proc 这个挂载点，但是里面的东
西都是 0 ，不要紧张！ /proc 的东西都是 Linux 系统所需要载入的系统数据，而且是挂载在“内存当中”的， 所以当然没有占任何的磁盘空间.至于那个 /dev/shm/ 目录，其实是利用内存虚拟出来的磁盘空间，通常是总实体内存的一半！
由于是**通过内存仿真出来的磁盘**，因此你在这个目录下面创建任何数据文件时，存取速度是非常快速的！（在内存内工作） 不过，也由于他是内存仿真出来的，因此这个文件系统的大小在每部主机上都不一样，**而且创建的东西在下次开机时就消失了！ 因为是在内存中**

- du

```
 du [-ahskm] 文件或目录名称
 选项与参数：
-a ：列出所有的文件与目录容量，因为默认仅统计目录下面的文件量而已。
-h ：以人们较易读的容量格式 （G/M） 显示；
-s ：列出总量而已，而不列出每个各别的目录占用容量；
-S ：不包括子目录下的总计，与 -s 有点差别。
-k ：以 KBytes 列出容量显示；
-m ：以 MBytes 列出容量显示；
```

```
范例一：列出目前目录下的所有文件大小
# du
	./.cache/dconf 
     // 每个目录都会列出来
	./.cache/abrt
	./.cache
....（中间省略）....
	 ./test4
	 ./.ssh 
	 //包括隐藏文件的目录
	 . 
	 //这个目录（.）所占用的总量
	 
//直接输入 du 没有加任何选项时，则 du 会分析“目前所在目录”的文件与目录所占用的磁盘空间。但是，实际显示时，仅会显示目录容量（不含文件）
//目录有很多文件没有被列出来，所以全部的目录相加不会等于 . 的容量
//此外，输出的数值数据为 1K 大小的容量单位
```

```
范例二：同范例一，但是将文件的容量也列出来
# du -a
 ./.bash_logout 
 //有文件的列表了
 ./.bash_profile
 ./.bashrc
....（中间省略）....
 ./.ssh/known_hosts
 ./.ssh
 .
```

```
范例三：检查根目录下面每个目录所占用的容量
# du -sm /*
0 /bin
99 /boot
....（中间省略）....
du: cannot access ‘/proc/17772/task/17772/fd/4’: No such file or directory
du: cannot access ‘/proc/17772/fdinfo/4’: No such file or directory
0 /proc &lt;==不会占用硬盘空间！
1 /root
25 /run
....（中间省略）....
3126 /usr &lt;==系统初期最大就是他了啦！
117 /var
// 这是个很常被使用的功能～利用万用字符 * 来代表每个目录，如果想要检查某个目录下
// 哪个次目录占用最大的容量，可以用这个方法找出来。值得注意的是，如果刚刚安装好 Linux 时，那么整个系统容量最大的应该是 /usr 。而 /proc 虽然有列出容量，但是那个容量是在内存中
// 不占磁盘空间。至于 /proc 里头会列出一堆“No such file or directory” 的错误
// 别担心！因为是内存内的程序，程序执行结束就会消失，因此会有些目录找不到，是正确的！ 
```

与 df 不一样的是，du 这个指令其实会直接到文件系统内去搜寻所有的文件数据， 所以上述第三个范例指令的运行会执行一小段时间！此外，在默认的情况下，容量的输出是以 KB 来设计的， 如果你想要知道目录占了多少 MB ，那么就使用 -m 这个参数即可啰！而， 如果你只想要知道该目录占了多少容量的话，使用 -s 就可以啦！至于 -S 这个选项部分，由于 du 默认会将所有文件的大小均列出，因此假设你在 /etc 下面使用 du 时， 所有的文件大小，包括 /etc 下面的次目录容量也会被计算一次。然后最终的容量（/etc） 也会加总一次， 因此很多朋友都会误会 du 分析的结果不太对劲。所以啰，如果想要列出某目录下的全部数据， 或许也可以加上 -S 的选项，减少次目录的加总！

#### 7.2.2 实体链接与符号链接： ln

在 Linux 下面的链接文件有两种

- 一种是类似 Windows 的捷径功能的文件，可以让你快速的链接到目标文件（或目录）；

- 在 Linux 下面的链接文件有两种，一种是类似 Windows 的捷径功能的文件，可以让你快速的链接到目标文件（或目录）；

  分别来谈谈

- Hard Link （实体链接, 硬式链接或实际链接）
  - 因为每个文件都会占用一个 inode ，文件内容由 inode 的记录来指向
  - 想要读取该文件，必须要经过目录记录的文件名来指向到正确的 inode 号码才能读取。

其实文件名只与目录有关，但是文件内容则与 inode 有关。有没有可能有多个文件名对应到同一个 inode 号码？

答：有的！那就是 hard link 的由来。 所以简单的说：hard link 只是在某个目录下新增一笔文件名链接到某 inode 号码的关联记录而已。

举个例子来说，假设我系统有个 /root/crontab 他是 /etc/crontab 的实体链接，也就是说这两个文件名链接到同一个 inode ， 自然这两个文件名的所有相关信息都会一模一样（除了文件名之外）。实际的情况可以如下所示：

```
# ll -i /etc/crontab
34474855 -rw-r--r--. 1 root root 451 Jun 10 2014 /etc/crontab
# ln /etc/crontab .
// 创建实体链接的指令
# ll -i /etc/crontab crontab
34474855 -rw-r--r--. 2 root root 451 Jun 10 2014 crontab
34474855 -rw-r--r--. 2 root root 451 Jun 10 2014 /etc/crontab
```

你可以发现两个文件名都链接到 34474855 这个 inode 号码，所以你看，是否文件的权限/属性完全一样呢？ 

因为这两个“文件名”其实是一模一样的“文件”啦！而且你也会发现第二个字段由原本的 1 变成 2 了！ 那个字段称为“链接”，这个字段的意义为：“有多少个文件名链接到这个 inode 号码”的意思。 如果将读取到正确数据的方式画成示意图，就类似如下画面。

<img src="/home/gongna/图片/2021-08-31_20-41.png" style="zoom:200%;" />

**你可以通过 1 或 2 的目录之 inode 指定的 block 找到两个不同的文件名，而不管使用哪个文件名均可以指到 real 那个 inode 去读取到最终数据。那这样有什么好处呢？最大的好处就是“安全”！**如果你将任何一个“文件名”删除，其实 inode 与 block都还是存在的！ 此时你可以通过另一个“文件名”来读取到正确的文件数据喔！此外，不论你使用哪个“文件名”来编辑， 最终的结果都会写入到相同的 inode 与 block 中，因此均能进行数据的修改！

一般来说，使用 hard link 设置链接文件时，**磁盘的空间**与 **inode 的数目**都不会改变！ 我们还是由图 7.2.1 来看，由图中可以知道， **hard link 只是在某个目录下的 block 多写入一个关连数据而已**，**既不会增加 inode 也不会耗用 block 数量！**

hard link 的制作中，其实还是可能会改变系统的 block 的，那就是当你新增这笔数据却刚好将目录的 block 填满时，就可能会新加一个 block 来记录文件名关连性，而导致磁盘空间的变化！不过，一般 hard link 所用掉的关连数据量很小，所以通常不会改变 inode 与磁盘空间的大小。

**事实上 hard link 应该仅能在单一文件系统中进行的，应该是不能够跨文件系统** 所以 hard link 是有限制的：

- 不能跨 Filesystem；
- 不能 link 目录。

不能跨 Filesystem 还好理解，那不能 hard link 到目录又是怎么回事呢？这是因为如果使用hard link 链接到目录时， 链接的数据需要连同被链接目录下面的所有数据都创建链接，举例来说，如果你要将 /etc 使用实体链接创建一个 /etc_hd 的目录时，那么在 /etc_hd 下面的所有文件名同时都与 /etc 下面的文件名要创建 hard link 的，而不是仅链接到 /etc_hd 与 /etc 而已。

并且，未来如果需要在 /etc_hd 下面创建新文件时，连带的， /etc 下面的数据又得要创建一次 hard link ，因此造成环境相当大的复杂度。 所以啰，目前 hard link 对于目录暂时还是不支持的啊！

- Symbolic Link （符号链接，亦即是捷径）

  相对于 hard link ， Symbolic link 可就好理解多了，基本上， Symbolic link 就是在创建一个独立的文件，而这个文件会让数据的读取指向他 link 的那个文件的文件名。由于只是利用文件来做为指向的动作， 所以，当来源文件被删除之后，symbolic link 的文件会“开不了”， 会一直说“无法打开某文件！”。实际上就是找不到原始“文件名”而已啦！

举例来说，我们先创建一个符号链接文件链接到 /etc/crontab 去看看：

```
# ln -s /etc/crontab crontab2
# ll -i /etc/crontab /root/crontab2
34474855 -rw-r--r--. 2 root root 451 Jun 10 2014 /etc/crontab
53745909 lrwxrwxrwx. 1 root root 12 Jun 23 22:31 /root/crontab2 ---> /etc/crontab
```

由上表的结果我们可以知道两个文件指向不同的 inode 号码，当然就是两个独立的文件存在，而且链接文件的重要内容就是他会写上目标文件的“文件名”， 你可以发现为什么上表中链接文件的大小为 12 Bytes 呢？ 因为箭头（-->）右边的文件名“/etc/crontab”总共有 12 个英文，每个英文占用 1 个 Bytes ，所以文件大小就是 12Bytes了！

<img src="/home/gongna/图片/2021-08-31_21-06.png" style="zoom:200%;" />

由 1 号 inode 读取到链接文件的内容仅有文件名，根据文件名链接到正确的目录去取得目标文件的 inode ， 最终就能够读取到正确的数据了。你可以发现的是，如果目标文件（/etc/crontab）被删除了，那么就无法通过链接文件来读取。

这里还是得特别留意，这个 Symbolic Link 与 Windows 的捷径可以给他划上等号，由Symbolic link 所创建的文件为一个独立的新的文件，所以会占用掉 inode 与 block。

由上面的说明来看，似乎 hard link 比较安全，因为即使某一个目录下的关连数据被杀掉了，也没有关系，只要有任何一个目录下存在着关连数据，那么该文件就不会不见！举上面的例子来说，我的 /etc/crontab 与 /root/crontab 指向同一个文件，如果我删除了 /etc/crontab 这个文件，该删除的动作其实只是将 /etc 目录下关于 crontab 的关连数据拿掉而已， crontab 所在的 inode 与 block 其实都没有被变动！

不过由于 Hard Link 的限制太多了，包括无法做“目录”的 link ， 所以在用途上面是比较受限的！反而是 Symbolic Link 的使用方面较广。

```
# ln [-sf] 来源文件 目标文件
选项与参数：
-s ：如果不加任何参数就进行链接，那就是hard link，至于 -s 就是symbolic link
-f ：如果 目标文件 存在时，就主动的将目标文件直接移除后再创建！
```

```
范例一：将 /etc/passwd 复制到 /tmp 下面，并且观察 inode 与 block
# cd /tmp
# cp -a /etc/passwd .
# du -sb ; df -i .
6602 .
// 先注意一下这里的容量是多少！
Filesystem Inodes IUsed IFree IUse% Mounted on
/dev/mapper/centos-root 10485760 109748 10376012 2% /
// 利用 du 与 df 来检查一下目前的参数～那个 du -sb 是计算整个 /tmp 下面有多少 Bytes 的容量
```

```
范例二：将 /tmp/passwd 制作 hard link 成为 passwd-hd 文件，并观察文件与容量
# ln passwd passwd-hd
# du -sb ; df -i .
6602 .
Filesystem Inodes IUsed IFree IUse% Mounted on
/dev/mapper/centos-root 10485760 109748 10376012 2% /
// 仔细看，即使多了一个文件在 /tmp 下面，整个 inode 与 block 的容量并没有改变！
```

```
# ls -il passwd*
2668897 -rw-r--r--. 2 root root 2092 Jun 17 00:20 passwd
2668897 -rw-r--r--. 2 root root 2092 Jun 17 00:20 passwd-hd
// 原来是指向同一个 inode 啊！这是个重点啊！另外，那个第二栏的链接数也会增加！

```

```
范例三：将 /tmp/passwd 创建一个符号链接
# ln -s passwd passwd-so
# ls -li passwd*
2668897 -rw-r--r--. 2 root root 2092 Jun 17 00:20 passwd
2668897 -rw-r--r--. 2 root root 2092 Jun 17 00:20 passwd-hd
2668898 lrwxrwxrwx. 1 root root 6 Jun 23 22:40 passwd-so -&gt; passwd
// passwd-so 指向的 inode number 不同,这是一个新的文件～这个文件的内容是指向passwd 的。passwd-so 的大小是 6Bytes ，因为 “passwd” 这个单字共有六个字符
# du -sb ; df -i .
6608 .
Filesystem Inodes IUsed IFree IUse% Mounted on
/dev/mapper/centos-root 10485760 109749 10376011 2% /
// 呼呼！整个容量与 inode 使用数都改变啰～确实如此啊！
```

```
范例四：删除原始文件 passwd ，其他两个文件是否能够打开？
# rm passwd
# cat passwd-hd
.....（正常显示完毕！)
# cat passwd-so
cat: passwd-so: No such file or directory
# ll passwd*
-rw-r--r--. 1 root root 2092 Jun 17 00:20 passwd-hd
lrwxrwxrwx. 1 root root 6 Jun 23 22:40 passwd-so -&gt; passwd
//怕了吧！符号链接果然无法打开！另外，如果符号链接的目标文件不存在，其实文件名的部分就会有特殊的颜色显示喔！
```

**当你修改 Linux下的 symbolic link 文件时，则更动的其实是“原始文件”， 所以不论你的这个原始文件被链接到哪里去，只要你修改了链接文件，原始文件就跟着变.**

> ln -s /bin /root/bin

那么如果你进入 /root/bin 这个目录下，“请注意呦！该目录其实是 /bin 这个目录，因为你做了链接文件了！”所以，如果你进入 /root/bin 这个刚刚创建的链接目录， 并且将其中的数据杀掉时，嗯！ /bin 里面的数据就通通不见了！这点请千万注意！所以赶紧利用“rm /root/bin ” 将这个链接文件删除吧！

- **关于目录的 link 数量：**

或许您已经发现了，那就是，当我们以 hard link 进行“文件的链接”时，可以发现，在 ls -l 所显示的第二字段会增加一才对，那么请教，如果创建目录时，他默认的 link 数量会是多少？让我们来想一想，一个“空目录”里面至少会存在些什么？就是存在 . 与 .. 这两个目录啊！ 那么，当我们创建一个新目录名称为 /tmp/testing 时，基本上会有三个东西，那就是：

- /tmp/testing
- /tmp/testing/.
- /tmp/testing/..

而其中 /tmp/testing 与 /tmp/testing/. 其实是一样的！都代表该目录。而 /tmp/testing/.. 则代表 /tmp 这个目录。所以说，当我们创建一个新的目录时， “新的目录的 link 数为 2 ，而上层目录的 link 数则会增加 1 ” 不信的话，我们来作个测试看看：

```
# ls -ld /tmp
drwxrwxrwt. 14 root root 4096 Jun 23 22:42 /tmp
# mkdir /tmp/testing1
# ls -ld /tmp
drwxrwxrwt. 15 root root 4096 Jun 23 22:45 /tmp 
// 这里的 link 数量加 1 了！
# ls -ld /tmp/testing1
drwxr-xr-x. 2 root root 6 Jun 23 22:45 /tmp/testing1/
// 新目录 /tmp/testing 则为 2
```

### 7.3 磁盘的分区、格式化、检验与挂载

“单个开关可以打开或关闭，从而能够存储 1 位信息。开关可以组合在一起以存储更大的数字。这就是为什么在数字系统中使用二进制的关键原因。”数字可以用二进制格式编码并使用开关存储。使用该系统的数字技术可以是计算机、计算器、数字电视解码器盒、手机、防盗报警器、手表等。值以二进制格式存储在内存中，这基本上是一堆电子开关。

简短的回答：硬件和物理定律。计算机中的每个数字都是一个电信号，在计算的早期，电信号很难非常精确地测量和控制。仅区分“开启”状态（由负电荷表示）和“关闭”状态（由正电荷表示）更有意义。对于那些不确定为什么“关闭”用正电荷表示的人来说，这是因为电子带有负电荷——更多的电子意味着更多的带有负电荷的电流。

因此，早期的房间大小的计算机使用二进制来构建它们的系统，即使它们使用更旧、更笨重的硬件，我们也保持了相同的基本原则。现代计算机使用所谓的晶体管来执行二进制计算。