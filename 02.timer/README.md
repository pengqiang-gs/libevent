# 目的
使用libevent设置一个定时器。

## 第一步：初始化libevent库
	struct event_base* base = event_init();
这一步相当于初始化了一个Reactor实例，初始化完成之后，就可以向Reactor注册事件了。

## 第二步，初始化event事件以及回调函数
	evtimer_set(&event, timer_callback, NULL);

上面这个调用等价于：
``    event_set(&event, -1, 0, timer_callback, NULL);``

`event_set`这个函数的原型：
``    void event_set(struct event *ev, ``
``			evutil_socket_t fd, ``
``			short events, ``
``			void (*callback)(evutil_socket_t, short, void *), ``
``			void *arg);``
1. `ev`：需要初始化的event对象。
2. `fd`：该event绑定的处理句柄，对于信号事件，就是信号；IO事件，就是文件描述符。
3. `event`：处理句柄上的事件类型，EV\_READ, EV\_WRITE, EV\_SIGNAL。
4. `callback`：函数指针，指向事件触发时响应的回调函数。
5. `arg`：传递给回调函数的参数结构。

``定时事件因为不需要fd，只需要超时事件，因此这地方默认-1。``
这一步相当于初始化一个`event_handler`。

## 第三步，设置event从属的event base
	event_base_set(base, &ev);
这一步相当于指定event要注册到哪个Reactor实例上去。

## 第四步，添加事件
	event_add(&ev, timeout);
`timeout`：就是事件相应的超时值。
这一步相当于调用`Reactor::register_handler`注册事件。

## 第五步，进入事件循环
	event_base_dispath(base);
这一步就是一直进行事件无线循环，如果已经有就绪事件，则进行事件处理。

