// EdoyumIMServer.cpp: 定义应用程序的入口点。
//

#include "EdoyumIMServer.h"
#include <signal.h>
#include <fcntl.h>

#include "IMServer.h"
#include "base/Singleton.h"
#include "MySqlManager.h"
#include "UserManager.h"

using namespace std;

void show_help(const char* cmd)
{
	cout << "found error argument!\r\n";
	cout << "Usage:" << std::endl;
	cout << cmd << " [-d]" << std::endl;
	cout << "\t-d run in daemon mode.\r\n";
}

void signal_exit(int signum)
{
	cout << "signal " << signum << " found, exit ...\r\n";
	//TODO:退出的清除
	switch (signum)
	{
	case SIGINT:
	case SIGKILL:
	case SIGTERM:
	case SIGILL:
	case SIGSEGV:
	case SIGTRAP:
	case SIGABRT:
		//TODO:
		break;
	default:
		//TODO:
		break;
	}
	exit(signum);
}

void daemon()
{
	signal(SIGCHLD, SIG_IGN);
	int pid = fork();
	if (pid < 0) {
		cout << "fork call error,code is " << pid << " error code is " << errno << std::endl;
		exit(-1);
	}
	if (pid > 0) {//主进程在此结束
		exit(0);
	}
	//这里的代码只可能是子进程了
	//这里可以避免父进程所在的会话结束时，把子进程带走
	//不让前台影响后台
	setsid();

	//不让后台影响前台
	int fd = open("/dev/null", O_RDWR, 0);
	cout << "invoke success!" << std::endl;
	cout << "STDIN_FILENO is " << STDIN_FILENO << std::endl;
	cout << "STDOUT_FILENO is " << STDOUT_FILENO << std::endl;
	cout << "STDERR_FILENO is " << STDERR_FILENO << std::endl;
	cout << "fd is " << fd << std::endl;
	if (fd != -1) {
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
	}
	if (fd > STDERR_FILENO)
		close(fd);
}
void onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	cout << conn->name() << std::endl;
}

void onMessage(const muduo::net::TcpConnectionPtr& conn,
	muduo::net::Buffer* buf,
	muduo::Timestamp time)
{
	conn->send(buf);
	conn->shutdown();
}

void test(muduo::net::EventLoop& loop)
{
	muduo::net::InetAddress addr(9527);
	muduo::net::TcpServer server(&loop, addr, "echo server");
	server.setConnectionCallback(onConnection);
	server.setMessageCallback(onMessage);
	server.start();
}

int main(int argc, char* argv[], char* env[])
{
	signal(SIGCHLD, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);//网络当中，管道操作
	signal(SIGINT, signal_exit);//中断错误
	signal(SIGKILL, signal_exit);
	signal(SIGTERM, signal_exit);//ctrl + c
	signal(SIGILL, signal_exit);//非法指令错误
	signal(SIGSEGV, signal_exit);//段错误
	signal(SIGTRAP, signal_exit);//ctrl + break
	signal(SIGABRT, signal_exit);//abort函数调用触发

	cout << "imchatserver is invoking ..." << endl;
	int ch = 0;
	//sever -a    server a
	bool is_daemon = false;
	while ((ch = getopt(argc, argv, "d")) != -1) {
		cout << "ch = " << ch << std::endl;
		cout << "current " << optind << " value:" << argv[optind - 1] << std::endl;
		switch (ch)
		{
		case 'd':
			is_daemon = true;
			break;
		default:
			show_help(argv[0]);
			return -1;
		}
	}

	if (is_daemon) {
		daemon();
	}

	muduo::net::EventLoop loop;
	//test();
	if (Singleton<MySqlManager>::instance().Init("127.0.0.1", "root", "123456", "myim") == false) {
		cout << "database init error!\r\n";
		return -2;
	}
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	if (Singleton<UserManager>::instance().Init() == false) {
		cout << "load user failed!\r\n";
		return -3;
	}
	cout << __FILE__ << "(" << __LINE__ << ")\r\n";
	//单例解决了两个问题：全局访问、单个实例
	if (Singleton<IMServer>::instance().Init("0.0.0.0", 9527, &loop) == false) {
		cout << "server init error!\r\n";
		return -1;
	}
	loop.loop();

	return 0;
}
