# CSAPP——简化的计算机模型和指令集

> 为了研究处理器的架构, CSAPP设计了一套简化的计算机模型和对应的指令集叫做Y86-64.

主要特点如下:

1. 15个寄存器, 不包括%r15. 这样内部寻址可以用0-15来选择寄存器. %rsp依然用作栈指针
2. 每个寄存器都报保存64位=8字节值, 机器里操作的所有值也都是8字节长
3. 三个一位的条件码: ZF SF 和 OF
4. 程序计数器 PC
5. 有一个状态码 Stat 用于表示程序状态
6. DMEM 内存, 这里把内存当成一个连续的虚拟内存, 内存使用基址+偏移量方式寻找, 不支持复杂的寻址运算, 其实就相当于直接用固定基础地址寻址

同时也对指令集进行了简化:

1. movq被分成了四个更好的跟踪程序的详细指令： irmovq, rrmovq, mrmovq, rmmovq. 第一个字母表示源, 第二个字母表示目标. i = 立即数, r = 寄存器, m = 内存
2. 运算指令有四个, addq, subq, andq, xorq, 只能对寄存器进行操作. 这些指令会同时设置条件码.
3. 7个跳转指令, jmp, jle, jl, je, jne, jge, jg.
4. 6个条件传送指令, cmovle, cmovl, cmove, cmovne, cmovge, cmovg. 这些指令与寄存器传送指令rrmovq一样, 只能在寄存器之间传送.
5. call 和 ret 与 原来的一样, 将地址入栈和出栈
6. pushq 和 popq 实现入栈和出栈
7. halt 停止指令执行, 状态码会设置成HLT

**指令集的编码**

- **指令长一个字节**
- **同类型的指令，低四位指示是哪个具体的指令**
- **第二个字节的高四位，是第一个操作数寄存器，低四位是第二个操作数寄存器，如果没有就用0xF表示。之后可以根据指令的不同可以跟8个字节的操作数，用来表示常数，地址。**

1. `halt` 0000 0000,这条是前边说的halt指令
2. `nop` 0001 0000, 这个是nop指令, 即什么也不做, 继续取下一条指令
3. `rrmovq rA, rB` 0010 0000 rA rB, 这是寄存器传送, 字节编码是20, rA和rB是寄存器地址, 比如从%rbx传送到%rax, 指令就是 20 3 1
4. `irmovq V, rB` 0011 0000 0xF rB V, 这条指令是将立即数传入指定寄存器, 很显然源寄存器没有, 用0xF表示, 立即数放在第三个字节开始的8个字节中, 这样这条指令长10个字节
5. `rmmovq rA, D(rB)` 0100 0000 rA rB D, 这条指令是将寄存器传入内存, 很显然要取地址, 地址会在最后加上8位的立即数D来表示
6. `mrmovq rA, D(rB)` 0101 0000 D(rA) rB D, 这条指令的数据结构和上边一条一样, 但是指令从40 变成了 50
7. `OPq rA, rB` 0110 ???? rA rB, 这个表示操作类的四条指令, 指令字节低位使用0-3表示四条不同的指令.
8. `jxx Dest` 0110 ???? Dest, 跳转类之类, 指令字节低位使用0-6表示7条不同的指令. 后边跟上8字节的地址
9. `cmovxx rA rB` 0010 ???? rA rB, 条件传送, 这里注意, ????是0-6共7个, 不是只有6个条件传送吗, 是因为 0010 0000 表示 rrmovq, 也就是不去判断标志位的无条件传送. 剩下的6个才是有条件的传送.
10. `call Dest` 1000 0000 Dest, 调用指令, 压之后的地址入栈并且跳转. 指令字节为80
11. `ret` 1001 0000, 无操作数, 返回指令, 弹出栈中的地址到PC
12. `pushq rA` 1010 0000 rA 0xF, 将rA寄存器中的值放入栈中, 由于无需使用第二个寄存器, 所以设置为0xF
13. `popq rA` 1011 0000 rA 0xF, popq指令要注意一下, 是将值弹出到源寄存器的位置, 由于无需使用第二个寄存器, 所以设置为0xF

通过上边的指令集, 可以发现, 只要指令使用了寄存器, 两个寄存器地址必须成对出现. 操作数始终跟在寄存器的后边, 如果指令不需要寄存器, 就无需寄存器部分

其中涉及到寻址的比如rmmovq等过程, rB寄存器内的值表示偏移量, 后边的D是表示立即数的值, 不是计算后的值.

几个指令类的具体代码对应关系如下:

| 整数操作 | 分支指令 | 传送指令 |          |      |          |        |          |        |          |
| :------: | :------: | :------: | :------: | :--: | :------: | :----: | :------: | :----: | :------: |
|   指令   | 字节编码 |   指令   | 字节编码 | 指令 | 字节编码 |  指令  | 字节编码 |  指令  | 字节编码 |
|   addq   |    60    |   jmp    |    70    | jne  |    74    | rrmovq |    20    | cmovne |    24    |
|   subq   |    61    |   jle    |    71    | jge  |    75    | cmovle |    21    | cmovge |    25    |
|   andq   |    62    |    jl    |    72    |  jg  |    76    | cmovl  |    22    | cmovg  |    26    |
|   xorq   |    63    |    je    |    73    |      |          | cmove  |    23    |        |          |

寄存器的编码是:

|  寄存器  | 编码 |
| :------: | :--: |
|   %rax   |  0   |
|   %rcx   |  1   |
|   %rdx   |  2   |
|   %rbx   |  3   |
|   %rsp   |  4   |
|   %rbp   |  5   |
|   %rsi   |  6   |
|   %rdi   |  7   |
| %r8-%r14 | 8-E  |
| 无寄存器 |  F   |

| **rrmovq** | **20   (16进制表示)** |
| ---------- | --------------------- |
| **irmovq** | **30**                |
| **rmmovq** | **40**                |
| **mrmovq** | **50**                |

movq指令：其中r为寄存器，i为立即数，m为内存

![在这里插入图片描述](https://i2.wp.com/img-blog.csdnimg.cn/b49f3ad5d82141569b16e0c2b981f96f.png?,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAdGFuZ2ZhdHRlcg==,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

寄存器编号

![在这里插入图片描述](https://i2.wp.com/img-blog.csdnimg.cn/3a1cde444f9148bfb53d988b6fea6c80.png?,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAdGFuZ2ZhdHRlcg==,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

整数操作指令



![在这里插入图片描述](https://i2.wp.com/img-blog.csdnimg.cn/da3231d89db142b88422509d4d8eff9f.png?,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAdGFuZ2ZhdHRlcg==,size_13,color_FFFFFF,t_70,g_se,x_16#pic_center)



跳转操作指令



![在这里插入图片描述](https://i2.wp.com/img-blog.csdnimg.cn/0bca08606c97494b90f7200b72c11c13.png?,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAdGFuZ2ZhdHRlcg==,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)



数据传送指令



![在这里插入图片描述](https://i2.wp.com/img-blog.csdnimg.cn/36fd9f8eee3646dd9cd68bbea06bdd95.png?,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAdGFuZ2ZhdHRlcg==,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

其他指令

![在这里插入图片描述](https://i2.wp.com/img-blog.csdnimg.cn/018207729b3c48988a0b042d4728eb5b.png?,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAdGFuZ2ZhdHRlcg==,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

其中halt表示停止指令，执行后处理器停止，并将状态码设为HLT；nop表示一个空操作；call和ret表示函数的调用和返回；push和pop为压栈和弹栈操作。



##### 练习 4.1 

**确定下列指令序列的字节编码, .pos 0x100表示程序起始地址是0x100**

`irmovq $15, $rbx`,

```
第一步：
30 F3 00 00 00 00 00 00 00 0F
第二步：
30 F3 0F 00 00 00 00 00 00 00
```

 `rrmovq %rbx, %rcx`

```
20 31
```

`rmmovq %rcx, -3(%rbx)`

```
第一步
40 13 
第二步
-3
FF FF FF FF FF FF FF Fd
第三步
Fd FF FF FF FF FF FF FF
第四个
40 13 Fd FF FF FF FF FF FF FF

 00000000  00000000  00000000  00000000  00000000  00000000  00000000  00000011
 求补码
 11111111  11111111  11111111  11111111  11111111  11111111  11111111  1111 1101
 FF FF FF FF FF FF FF Fd
```

`addq %rbx, %rcx`

```
60 31
```

`jmp loop`

```
第一条指令的起始地址是 0x100 
10字节长
指令结束在0x109
下一条指令2字节 从 0x10A-0x10B.
再下一条指令是 0x10C开始的10字节, 0x10C-0x115.
D E F 0 1  2 3 4 5 
最后的汇编代码如下:
0x100 30 F3 0F 00 00 00 00 00 00 00
0x10A 20 31
0x10C 40 13 fd ff ff ff ff ff ff ff
0x116 60 31
0x118 70 0C 01 00 00 00 00 00 00

第一个指令起始地址0x100
第一个指令终点地址0x100+(10-1)=0x109
第一个指令从起始到结束  0x100~0x109

第二个指令起始地址0x109+1=0x10A
第二个指令终点地址0x10A+(2-1)=0x10B
第二个指令从起始到结束  0x10A～0x10B

第三个指令起始地址0x10B+1=0x10C
第三个指令终点地址0x10C+(9)=0x115
第三个指令从起始到结束  0x10C～0x115

第四个指令起始地址0x115+1=0x116
第四个指令终点地址0x116+1=0x117
第四个指令从起始到结束0x116 ~0x117

第五个指令起始地址0x117+1=0x118
0x100 30 F3 0F 00 00 00 00 00 00 00
0x10A 20 31
0x10C 40 13 fd ff ff ff ff ff ff ff
0x116 60 31
0x118 70 0C 01 00 00 00 00 00 00
```



##### 练习 4.2 

**将字节指令翻译成汇编指令**

1.`0x100: 30 f3 fc ff ff ff ff ff ff ff 40 63 00 08 00 00 00 00 00 00`

```
00 00 00 00 00 00 00 0000 0100
irmovq  $-4,%rbx

40 63 00 08 00 00 00 00 00 00
rmmovq  %rsi 2048（%rdx）
00 00 00 00 00 00 80 00

1000 0000 0000 0000
2的15次方=2048
```



2.`0x200: a0 6f 80 0c 02 00 00 00 00 00 00 00 30 f3 0a 00 00 00 00 00 00 00 90`

```
0x200: a0 6f    80 0c 02 00 00 00 00 00 00   00  30 f3 0a 00 00 00 00 00 00 00 90
第一部分：
a0 6f 
pushq %rsi 

第二部分：
80 0c 02 00 00 00 00 00 00 
call   00 00 00 00 00 00 0010 0000 1100 0000
call   2的13次方+2的6次方+2的七次方 0x020C

第三部分：
00 
00指令即HLT, 执行到这里就停机了

第四部分：
30 f3 0a 00 00 00 00 00 00 00  
irmmovq $0xa0 %rbx  
00 00 00 00 00 00 00 00 a0 

第五部分
90 
ret

```

3.`50 54 07 00 00 00 00 00 00 00 10 f0 b0 1f`

```
第一部分：
50 54 07 00 00 00 00 00 00 00 
mrmmovq %rbp 112(%rsp)
00 00 00 00 00 00 00 70
					0111 0000
					7*16=112
第二部分：10				
nop	

第三部分：
f0 b0 1f
没有这个指令
```

4.`61 13 73 00 04 00 00 00 00 00 00 00`

```
61 13 
subq %rcx %rdx 

73 00 04 00 00 00 00 00 00
73 00 00 00 00 00 00 40 00
je 40 00 
00  
halt 

```

5.`63 62 a0 f0`

```
63 62
xorq %rsi %rdx  

a0 f0
pushq  %rax
```

## 异常代码

|  值  | 名称 |     含义      |
| :--: | :--: | :-----------: |
|  1   | AOK  |   正常操作    |
|  2   | HLT  | 执行了HLT命令 |
|  3   | ADR  |   非法地址    |
|  4   | INS  |   非法指令    |

##### 练习4.3 

**用iaddq重写sum函数**

##### 练习4.4 

用Y86-64语言写程序

```
long rsum(long *start, long count) {
    if (count <= 0) {
        return 0;
    }
    return *start + rsum(start + 1, count - 1);
}
可以先写出X86的汇编:
long rsum(long *start, long count)
start in %rdi, count in %rsi
rsum:
    xorq %rax, %rax         %rax置0
    test %rsi, %rsi         测试count
    jle L2
    pushq %rbp
    movq(%rdi),%rbx
    addq $8 ,%rdi       准备参数 start + 1
    subq $1, %rsi		准备参数 count - 1
    call rsum			调用新过程
    addq %rbx, %rax 	将保存的start的值加到返回值上
    popq %rbx 			恢复%rbp的值
    ret 				返回%rax

L2:
rep;ret
```

```
然后改成Y86的汇编代码, 操作常数需要使用寄存器中转, 在进入判断之前, 还需要使用一个 andq 来设置标志位, 标红的部分为改动的部分:


long rsum(long *start, long count)
start in %rdi, count in %rsi

rsum:
    xorq %rax, %rax         %rax置0
*   andq %rsi, %rsi         测试count
    jle  L2                 小于等于0则跳转到L2

    pushq %rbp
 *  mrmovq (%rdi), %rbx     把start的值保存到%rbp中
 *  irmovq $1, %r8          准备常量1到%r8寄存器
 *  irmovq $8, %r9          准备常量8到%r9寄存器
 *  addq %r9, %rdi          准备参数 start + 1
 *  subq %r8, %rsi          准备参数 count - 1
    callq rsum              调用新过程
    addq %rbx, %rax         将保存的start的值加到返回值上
    popq %rbx               恢复%rbp的值
    ret                     返回%rax
.L2
    rep; ret                返回0, 直接返回0的情况下, 没有用到%rbp, 所以也无需弹栈    
```

##### 练习4.5 

求数组的中元素的绝对值之和.

在内循环中使用条件跳转, 其实就是再判断一次元素的值, 如果大于等于0就使用原来的值, 如果小于就使用subq减去这个值. 这里简单采取跳转的方式.

```
sum:
    irmovq      $8, %r8         准备常数8
    irmovq      $1, %r9         准备常数1
    xorq        %rax,%rax       sum=0
    andq        %rsi, %rsi      测试%rsi
    jmp         test            无条件跳转进循环

.loop:
    mrmovq      (%rdi), %r10    获取*start的值放入%r10
    andq        %r10, %r10      测试*start的值
    jl          L2              如果小于0, 跳转到L2
    addq        %r10, %rax      sum += *start

.L3:
    addq        %r8, %rdi       start ++
    subq        %r9, %rsi       count --

.test:
    jne         loop
    ret

.L2:
    subq        %r10, %rax      当*start小于0的时候, sum-=*start, 相当于加上绝对值
    jmp         L3              无条件跳回L3
```

练习4.6 求数组的中元素的绝对值之和

但是这次使用条件传送, 其实也很简单, 先准备好-x的值, 然后判断*start是否小于0来进行条件传送.

```
sum:
    irmovq      $8, %r8         准备常数8
    irmovq      $1, %r9         准备常数1
    xorq        %rax,%rax       sum=0
    andq        %rsi, %rsi      测试%rsi
    jmp         test            无条件跳转进循环

.loop:
    mrmovq      (%rdi), %r10    获取*start的值放入%r10
    xorq        %r11, %r11      %r11清零
    subq        %r10, %r11      向%r11中放入-x
    andq        %r10, %r10      测试*start的值
    cmovl       %r11, %r10      如果*start小于0 , 就传送-x 到 %r10寄存器
    addq        %r10, %rax      sum += *start

    addq        %r8, %rdi       start ++
    subq        %r9, %rsi       count --

.test:
    jne         loop
    ret
```

##### 练习4.6 

求数组的中元素的绝对值之和

```
sum:
    irmovq      $8, %r8         准备常数8
    irmovq      $1, %r9         准备常数1
    xorq        %rax,%rax       sum=0
    andq        %rsi, %rsi      测试%rsi
    jmp         test            无条件跳转进循环

.loop:
    mrmovq      (%rdi), %r10    获取*start的值放入%r10
    xorq        %r11, %r11      %r11清零
    subq        %r10, %r11      向%r11中放入-x
    andq        %r10, %r10      测试*start的值
    cmovl       %r11, %r10      如果*start小于0 , 就传送-x 到 %r10寄存器
    addq        %r10, %rax      sum += *start

    addq        %r8, %rdi       start ++
    subq        %r9, %rsi       count --

.test:
    jne         loop
    ret
```

答案这里比我高明一些, 因为subq同时设置条件码, 直接用cmovg判断 -x>0, 即x<0的情况, 就传送%r11 到 %10即可.

## 特殊指令 – %rsp入栈出栈

还有一条特殊的指令需要注意一下, 就是把栈指针压入栈会如何. 这条指令是 `pushq %rsp`, 问题是pushq本身会把%rsp的值-8, 那到底压入的是在执行这条指令之前%rsp-8之前的数字还是之后的数字呢?

##### 练习 4.7 

判断pushq %rsp哪个值

在用到栈之前, 将当前的栈指针保存进了%rax, push之后再弹出来, 保存到了%rdx中, 最后用%rax-%rdx, 结果总是0, 说明pushq %rsp ,保存的是当前的%rsp,而不是减去8之后的结果.

##### 练习 4.8 

判断popq %rsp的值

popq也有类似的问题, 是先把栈指针+8, 还是不+8呢, 这个练习的试验证明, 弹出的时候就是原来的值 ,不会进行+8的操作.

综合4.7和4.8的结果, push压入%rsp的时候, 都不会对已经存在的%rsp进行修改, 压入之后再将%rsp+8, 而popq 会直接将%rsp设置为栈里的值.