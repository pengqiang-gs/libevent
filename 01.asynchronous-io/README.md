# synchronous io
Most beginning network programming start with blocking IO.<br/>
An IO is synchronous, when you call it, it does not return until the operation is compeleted, or until enough time has passed that your network stack gives up. such as `connection()` on a TCP connection.<br/>

## synchronous blocking attempt
### use child process

	void child(int fd)
	{
		// do something

		while(1)
		{
			result = recv(fd, buffer, sizeof(buffer), 0);
			if(result == 0)
				break;
			else if(result < 0)
			{
				perror("recv");
				break;
			}
			else
			{
				// process recv data.
			}
		}
	}

	void main()
	{
		// create server socket.
		int server = socket(AF_INET, SOCK_STREAM, 0);
		// omit something.

		// bind server socket.
		if(bind(server, ...) < 0)
			// ...

		// listen
		if(listen(server, LISTEN_COUNT) < 0)
			// ...

		while(1)
		{
			int fd = accept(server, ...);
			if(fd < 0)
				perror("accept");
			else
			{
				if(fork() == 0)
					child(fd);
			}
		}
	}

### fcntl noblocking

	for(int i = 0; i < socket_count; ++i)
		fcntl(fd[i], F_SETFL, O_NOBLOCK);

### select
	
	fd_set readset;
	int maxfd = -1;
	FD_ZERO(&readset);
	for(int i = 0; i < socket_count, ++i)
	{
		if(fd[i] > maxfd)
			maxfd = fd[i];
		FD_SET(fd[i], &readset);
	}

	select(maxfd+1, &readset, NULL, NULL);
	for(int i = 0; i < socket_count, ++i)
	{
		if(FD_ISSET(fd[i], &readset))
			// do process.
	}

# asynchronous io

