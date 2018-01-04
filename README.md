# What is libevent
The libevent is an event notification library. More details click [libevent official website]((http://libevent.org/).<br/><br/>

The libevent API provides a mechanism to execute a callback function when a specific event occurs on a file descriptor or after a timeout has been reached. Furthermore, libevent also support callbacks due to signals or regular timeouts.<br/><br/>

The libevent is meant to replace the event loop which found in `event driven network` servers. An application just need to call `event_dispatch()` and then add or remove events dynamically without changing the event loop.<br/><br/>

The libevent support `/dev/poll`, `kqueue`, `event ports`, `POSIX select`, `Windows select`, `poll`, `epoll`, so libevent can be sonpiled on `Linux`, `*BSD`, `MacOS X`, `Windows` and more.<br/><br/>

The internal event mechanism is completely indenpendent of exposed event API, and a simple update of libevent can provide new functionality without redesigning applications. So libevent allows for portable application development and provides the most scalable event notification mechanism available on an operate system.<br/><br/>

The libevent can also be used for multi-thread application. either by isolating each `event_base` so that only a single thread can access it, or by locked access to a single shared `event_base`.<br/><br/>

The libevent additionally provides a sophisticated framework for buffered network IO, with support for `socket`, `filters`, `rate-limiting`, `SSL`, `zero-copy file transmission`, `IOCP`.<br/><br/>

The libevent includes support for several useful protocols, include `DNS`, `HTTP`, `minimal RPC framework`.<br/><br/>

# libevent installation
## Linux
### online 
**Ubuntu**: `sudo apt-get -y install libevent`
**Linux**: `sudo yum install libevent -y`

### offline
omit 

## Windows
omit

