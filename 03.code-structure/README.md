# libevent源代码组织结构
## 公共头文件
1. xxx-internal.h: 内部数据结构和函数，对外不可见。

## event框架
1. event.h/c: 整体event框架

## 系统IO多路复用
1. epoll.c: 对epoll封装。
2. select.c: 对select封装。
3. devpoll.c: 对dev/poll的封装。
4. kqueue.c: 对kqueue的封装。

## 信号管理
1. singal.c

## 辅助功能函数
1. evutil.h/c: 一些辅助功能函数，包括创建socket pair和一些时间操作函数.

## 日志
1. log.h/c

## 缓冲区管理
1. evbuffer.c
2. buffer.c

## 基本数据结构
1. queue.h: 链表，双向链表，队列。
2. min-heap.h: 小根堆。

## 网络库
1. http
2. dns
