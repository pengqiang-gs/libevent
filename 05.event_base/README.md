# 目的
`event_base`是libevent的事件处理框架，结构体声明在`event-internal.h`头文件中。  
libevent将系统提供的I/O demultiplex机制统一封装为`eventop`结构，因此`eventops`中包含select，poll，kqueue，epoll等等其中的若干个实例对象。  

## event\_base
	struct event_base {
		const struct eventtop* evsel;
		void* evbase;
		int event_count; /* 整个base中所有event的数量 */
		int event_count_active; /* 整个base中所有的激活的event数量 */
		int event_gotterm; /* 设置需要停止运行一次的事件 */
		int event_break; /* 设置需要立即停止的事件 */
		struct event_list** activequeues; /* 激活的事件链表 */
		int nactivequeues; /* 激活事件链表的长度 */
		struct evsignal_info sig; /* 信号事件 */
		struct event_list eventqueue; /* IO事件 */
		struct timeval event_tv; /* 超时事件 */
		struct min_heap timeheap; /* 超时事件小根堆 */
		struct timeval tv_cache; /* 时间缓冲区，防止频繁调用获取时间函数 */
	};

## eventop
	struct eventop {
		const char* name; /* 当前实例的名称 */
		void* (*init)(struct event_base*); /* 设置当前实例的event_base */
		int (*add)(struct event_base*, int fd, short old, short event, void* fdinfo); /* 添加事件 */
		int (*del)(struct event_base*, int fd, short old, short event, void* fdinfo); /* 删除事件 */
		int (*dispatch)(struct event_base*, struct timeval*); /* 主事件循环，以及超时时间设置 */
		void (*dealloc)(struct event_base*); /* 清理 */
		int need_reinit; /* fork子进程后还要不要重新初始化event_base */
	};

## 注册事件
	int event_add(struct event* ev, /* 需要注册的事件 */
			const struct timeval* tv /* 事件响应超时时间 */
			);

该函数将事件`ev`注册到`ev->ev_base`上，事件类型由`ev->ev_events`指定。  
如果注册成功，`ev`将被插入到已注册链表中。  
如果`tv`不等于NULL，将同时注册定时事件，将`ev`添加到`timer`堆上。  
如果其中有一步出错，则保证不会有事件注册，这一步相当于原子操作。  

## 删除事件
	int event_del(struct event* ev /* 删除的事件 */
			);

对于IO事件，从IO的demultiplexr上将事件注销。  
对于信号事件，从信号事件的链表中删除。  
对于定时事件，从最小堆上删除。


