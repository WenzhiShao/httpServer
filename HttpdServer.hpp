#pragma once
#include<iostream>
#include<string>
#include<cstdlib>
#include<arpa/inet.h>
#include<pthread.h>
#include<unistd.h>
#include"Log.hpp"
#include"ProtocolUtil.hpp"
class Server{
private:
	int port;
	int listen_socket;
public:
	Server(int port_)
	:port(port_)
	,listen_socket(-1)
	{}
	
	~Server()
	{
		if(listen_socket>-1)
		  close(listen_socket);
		port = -1;
	}

	void InitServer()
	{
	//	std::cout<<"test"<<std::endl;
		listen_socket = socket(AF_INET, SOCK_STREAM,0);
		if(listen_socket<0)
		{
		  LOG(ERROR,"create listen_sock failed");
		  exit(2);
		}
		LOG(INFO,"create listen_sock suceed");
		int opt_ = 1;
		setsockopt(listen_socket,SOL_SOCKET,SO_REUSEADDR,&opt_,sizeof(opt_));
		struct sockaddr_in local_;
		local_.sin_family = AF_INET;
		local_.sin_port = htons(port);
		local_.sin_addr.s_addr = INADDR_ANY;
		
		if(bind(listen_socket,(struct sockaddr *)&local_,sizeof(local_))<0)
		{
		  Log(ERROR,"bind failed",__FILE__,__LINE__);
		  exit(3);
		}
		LOG(INFO,"bind succeed");
		if(listen(listen_socket, 5)<0)
		{
		  LOG(WARNING,"create queue failed");
		  exit(4);
		}
	}
	
	void Start()
	{
		while(1)
		{
			struct sockaddr_in peer;
			socklen_t len = sizeof(peer);
			int sock_ = accept(listen_socket,(struct sockaddr *)&peer,&len);
			if(sock_ < 0)
			{
				LOG(WARNING,"connect failed");
				continue;
			}
			LOG(INFO,"accept succeed");		
			pthread_t tid;
			pthread_create(&tid,NULL,Entry::RequestHander,(void *)sock_);
		}
	}
};
