---
title: 植物大战僵尸制作说明
tags:

---

# 植物大战僵尸制作说明

## 目标

双人网络对战游戏，一人摆植物，一人摆僵尸。

## 用户的注册和登录

要有一张背景图，尺寸1400 * 600像素，设计几个按钮，显示登录，注册

比如，就像许多软件的登录注册

用户名输入框

密码输入框

  登录按钮

​				---没有账号？注册一个！

如果点击登录按钮，那么来到游戏主界面；如果点击注册按钮，来到注册界面。

注册时要求用户名不能重复，密码复杂度要求（自己设计）。点击注册按钮后，提示注册是否成功，如果失败，则提示失败。如果成功，则提示成功，然后回到登录界面。



以上为一个场景，登录界面、注册界面用不同的层来表示。



数据库的设计---mysql

目前需要保存用户名和密码，可以再添加一些胜率等信息



## 服务器端

数据库保存在linux服务器上，服务器上运行程序，接收来自客户端的tcp连接 ， 我们要在此处体现多线程，高并发

用python 的 async io来写？这是异步io，可能无法满足老师要求

处理客户端发来的sql查询，插入请求，将结果返回客户端。

当用户进行双人对战时，如何显示对方的信息。可以当对方每放一个植物/僵尸时，向服务器发送放植物的种类和位置，服务器发送给另一客户端

多线程？采用线程池

NO！采用python的async IO，可以减少很多不必要的麻烦。当然如果你的C++很好，并且可以很好的控制多线程的同步问题以及很好的使用TCP，也可以采用C++。

python的异步IO可以满足并发要求，利用python课学到的知识即可。

### 需求：

#### 1、登录：

**不允许一个账号多人登录**

你会收到来自客户端的登录请求 

格式为 

```
LOGIN;username;password;\n
```

​        比如:    

```
LOGIN;zrf;123456;\n
```

你需要根据收到的用户名和密码，查询sql数据库，并且返回登录成功或失败。

登录成功，返回  

```
LOGIN;1;\n    
```

登陆失败（用户名或密码错误） 

```
LOGIN;0;\n
```

账户已经登录

```
LOGIN;2;\n
```



#### 2、注册：

你会收到来自客户端的注册请求   

格式为  

```
REGISTER;username;password;\n
```

  比如

```
REGISTER;zrf;123456;\n
```

根据得到的用户名和密码，查询用户名是否已经存在，

若存在，返回错误   

```
REGISTER;0;\n  
```

 如果不存在，注册成功，返回 

```
REGISTER;1;\n
```

 并且把用户名密码存入数据库中

#### 3、匹配

当用户点击主界面的匹配按钮时，就会向服务器发送  

```
MATCH;\n
```

再还未匹配到对手之前，用户可以点击取消匹配按钮，然后客户端重新回到主界面

```
CANCELMATCH;\n
```

当匹配成功后，服务器向客户端发送

```
MATCHSUCCESS;0;\n
```

客户端收到后，则自己为植物

```
MATCHSUCCESS;1;\n
```

客户端收到后，则自己为僵尸



2020/11/14

由于程序切换场景时要加载很多东西，麻烦服务器在匹配好对手后，**延迟3秒**再向客户端发送MATCHSUCCESS信息  ？（是否可以在客户端解决这个问题）



同步问题，由于从匹配场景切换到对战场景需要加载好几秒中，并且不同电脑加载时间也不一样，为了同步两个客户端的信息，服务器需要在发送过MATCHSUCCESS信息后，**过5秒后**（这段时间留给客户端加载信息），向两个客户端**同时**发送

```
START;\n
```



注意，服务器收到两个客户端的匹配请求后，要随机向其中一个客户端发送MATCHSUCCESS;0;向另一个客户端发送MATCHSUCCESS;1;

#### 4、对战过程

两个客户端匹配成功后，服务器保持与这两个客户端的连接

每个客户端每隔0.5秒会向服务器发送自己方（植物方或僵尸方）的信息，以此来同步两个客户端

你不需要处理其中的内容，只需要将信息发送个另一个客户端

1、植物方，发送植物的信息

```
PLANT:PeaShooter:x,y;Peashooter:x,y;.....\n
```

2、僵尸端

```
ZOMBIE:NormalZombie:x,y;NormalZombie:x,y;......\n
```

#### 5、比赛结果

如果一方获胜，则会向服务器发送；注意，失败方不会向服务器发送任何信息；注意，服务器判定第一次收到发送WIN的客户端是胜利方。如果客户端收到WIN则胜利了，如果客户端收到LOSE则失败。

```
WIN;\n
```

判定那一方胜利后，向胜利的客户端发送

```
WIN;\n
```

然后服务器向失败的客户端发送

```
LOSE;\n
```

其中一个客户端收到LOSE后，再向服务器发送一个LOSE

这次比赛结束，服务器释放与这两个客户端的连接。

#### 6、TCP心跳包

客户端每隔一秒向服务器发送一个心跳包，内容为，服务器每隔一段时间也向客户端发送同样的内容

```
HeartBeat;\n
```

#### 7、同步方案

以植物方的为准，植物方决定僵尸何时行走、攻击、掉头、死亡，以及僵尸的位置。

僵尸方不进行任何计算，只展示僵尸的位置和动作。

植物方植物死亡时，向僵尸方发送植物死亡的信息。

## ISSUE

1、土豆地雷只能炸死完全重合的多只僵尸，邻近的僵尸不能同时炸死

​	//目前只能炸掉一个僵尸，以后再做调整

2、土豆地雷的价格为25，每次应该减去25  **已解决**

3、僵尸掉头动作与前进动作一块执行时，会发生闪烁，是否要删除僵尸死亡动画？

4、缓存？每当创建一个精灵时，都是从硬盘里读plist，是否应该做成缓存以加快图片绘制速度？

5、食人花吃僵尸时，僵尸会停顿一下，主要原因是把僵尸从总僵尸数组中删除了，于是僵尸就停止运动了   **已解决** 2020/11/16



