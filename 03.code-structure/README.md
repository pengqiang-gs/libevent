# libevent源代码组织结构
## 公共头文件
* `xxx-internal.h` 内部数据结构和函数，对外不可见。

## event框架
* `event.h/c` 整体`event`的结构声明，接口定义和框架实现。

## 系统IO多路复用
* `epoll.c` 对`epoll`封装。
* `select.c` 对`select`封装。
* `devpoll.c` 对`dev/poll`的封装。
* `kqueue.c` 对`kqueue`的封装。

## 信号管理
* `singal.c` 对信号事件的处理封装。

## 辅助功能函数
* `evutil.h/c` 一些辅助功能函数，包括创建`socket pair`和一些时间操作函数。

## 日志
* `log.h/c` 内部日志

## 缓冲区管理
* `evbuffer.c` 对缓冲区的封装。
* `buffer.c` 对缓冲区的封装。
新版本中对各种缓冲区的封装更多，后续再讨论更新。

## 基本数据结构
* `queue.h` 链表，双向链表，队列。
* `min-heap.h` 小根堆。

## 网络库
* `http` 基于`libevent`实现的`http`服务器。
* `dns` 基于`libevent`实现的异步`dns`查询库。
