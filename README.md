# ReactorHttp-Cpp
 基于线程池的多反应堆reactor服务器模型

“pdf”文件夹是学习linux时阅读的文章

“图”是学习时画的方便理解的图

“Linux”是学习时做的知识思维导图

“code”是学习时写的所有demo




“项目”文件夹中包含了项目模块的xmind，以及各个子模块的图形描述

大致文字描述如下：

- Buffer作为人工控制的内存，实现通信数据的存储
- Channel主要是对fd的封装，围绕fd实现一系列功能
- Dispatcher作为调度器使用，在最底层提供了三种通信方式，分别为epoll、poll和select，操作者可以自行配置
- EventLoop作为最核心的反应堆模型，包含一个任务队列来解决channel的需求，并且每个EventLoop都有一个调度器，来调用需求函数。每个线程都包含一个EventLoop，主线程的任务队列中只有监听的fd的channel，它只创建子线程来解决多个服务器连接。
- TcpConnection处理HttpRequest和HttpResponse
- TcpServer将上述所有模块集中封装，集中调用
