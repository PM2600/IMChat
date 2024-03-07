// protobufstudy.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "edy.pb.h"

int main()
{
	EdyMsg msg;
	msg.set_ncmd(0);
	msg.set_strdata("hello world");
	EmbeddedMessage* sub = new EmbeddedMessage();
	sub->set_msubcmd(1);
	sub->set_strparams("edy");
	msg.set_allocated_submsg(sub);
	std::string result = msg.SerializeAsString();	
	msg.SerializePartialToOstream(&std::cout);
	// 网络发送
	EdyMsg msg2;
	msg2.ParseFromString(result);
	std::cout << "\ncmd: " << msg2.ncmd() << "\ndata: " << msg2.strdata() << std::endl;
	return 0;
}