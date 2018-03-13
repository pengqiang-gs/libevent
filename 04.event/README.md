# 目的
libevent是基于事件驱动的，event是整个库的核心，event就是反应堆模式中事件处理的组件。   
event提供函数接口，供反应堆在事件发生时调用，执行相应的处理。  

## libevent之event结构
	struct event {
		TAILQ_ENTRY (event) ev_next;
		TAILQ_ENTRY (event) ev_active_next;
		TAILQ_ENTRY (event) ev_signal_next;
		unsigned int min_heap_idx; /* for managing timeouts */
		struct event_base *ev_base;
		int ev_fd;
		short ev_events;
		short ev_ncalls;
		short *ev_pncalls; /* Allows deletes in callback */ 
		struct timeval ev_timeout;
		int ev_pri;  /* smaller numbers are higher priority */
		void (*ev_callback)(int, short, void *arg); 
		void *ev_arg;
		int ev_res;  /* result passed to event callback */  
		int ev_flags;
	};   

1. `ev_event`: event关注的事件类型
> IO事件：`EV_WRITE` / `EV_READ`
> 定时时间：`EV_TIMEOUT`
> 信号：`EV_SIGNAL`
> 辅助值：`EV_PERSIST`，表示一个永久事件  

2. `ev_next`, `ev_signal_next`, `ev_active_next`: libevent事件管理，双向链表的指针 
> `ev_next`是IO事件的保存的下一个的链表指针  
> `ev_signal_next`是信号事件保存的下一个的链表指针  
> `ev_active_next`是所有激活的事件的下一个链表指针  

3. `min_heap_idx`, `ev_timeout`: libevent超时管理，管理定时事件  

4. `ev_base`: libevent处理事件所属的反应堆实例。  

5. `ev_fd`: 文件描述符，IO事件时是打开的文件描述符，信号事件是绑定的信号。  

6. `ev_callback`: `ev_event`的回调函数，被`ev_base`调用，执行事件处理函数。  

7. `ev_arg`: `void*`任意类型数据，在设置`event`的时候指定。  

8. `ev_flags`: libevent用于标记`event`信息的字段，标识当前的状态。

9. `ev_ncalls`: 事件就绪室，调用`ev_callback`的次数，通常为1。  

10. `ev_pncalls`: 指向`ev_ncalls`的指针，或者为NULL。  

11. `ev_res`: 记录当前激活事件的类型。  

## libevent对event的管理
如上，三个链表对event进行管理。

## libevent设置事件
### 设置event
	void event_set(struct event* ev, /* 需要设置的event对象 */
			int fd, /* 事件event对应的文件描述符或者信号 */
			short event, /* 事件的类型，EV_READ|EV_PERSIST, EV_WRITE, EV_SIGNAL等 */
			void (*callback)(int, short, void*), /*设置响应事件的回调函数 */
			void *arg /*回调函数的参数 */
			);
### 设置event\_base
	int event_base_set(struct event_base* base, /* 需要设置的event注册到的base */
			struct event* ev /* event */
			);   
libevent有一个全局的`event_base`指针`current_base`，默认情况下event都注册到这里，这个函数可以指定不同的`event_base`。

### 设置优先级
	int event_priority_set(struct event* ev,
			int pri
			);   
当event处于就绪状态时，不可以再设置其优先级。

