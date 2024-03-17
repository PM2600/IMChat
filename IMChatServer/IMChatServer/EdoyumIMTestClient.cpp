#include <iostream>

// TODO: 在此处引用程序需要的其他标头。
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

#include "base/Logging.h"
#include "net/TcpClient.h"
#include "net/EventLoop.h"
#include "net/InetAddress.h"


using namespace muduo;
using namespace muduo::net;
TcpClient* pclient = NULL;
EventLoop* ploop = NULL;
void onClose(const TcpConnectionPtr& conn)
{
	std::cout << "onClose called!" << std::endl;
	//ploop->quit();
	exit(0);
}

void onConnected(const TcpConnectionPtr& conn)
{
	conn->send("hello");
	conn->setCloseCallback(onClose);
}

void onMessage(const TcpConnectionPtr& conn, Buffer* buffer,
	Timestamp ts)
{
	std::cout << buffer->retrieveAllAsString() << std::endl;
	
	//conn->shutdown();
	//pclient->stop();
	//conn->getLoop()->queueInLoop(onClose);
}

int main()
{
	EventLoop loop;
	ploop = &loop;
	InetAddress servAddr("127.0.0.1", 9527);
	TcpClient client(&loop, servAddr, "echo client");
	pclient = &client;
	client.setConnectionCallback(onConnected);
	client.setMessageCallback(onMessage);
	client.connect();
	loop.loop();
}