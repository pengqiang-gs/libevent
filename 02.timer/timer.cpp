#include <cstdio>
#include <sys/time.h>
#include <event2/event_struct.h>
#include <event2/event_compat.h>
#include <event2/event.h>

struct event _event;
struct timeval _tv;

void timer_callback(int fd, short event, void* arg)
{
	std::printf("timer callback.\n");
	event_add(&_event, &_tv);
}

int main(const int argc, const char* argv[])
{
	struct event_base* base = event_init();

	_tv.tv_sec = 1;
	_tv.tv_usec = 0;
	event_set(&_event, -1, 0, timer_callback, NULL);

	event_add(&_event, &_tv);

	event_base_set(base, &_event);

	event_base_dispatch(base);

	return 0;
}
