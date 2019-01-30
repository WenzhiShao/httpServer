#include<cstdlib>
#include"HttpdServer.hpp"

void Usage(std::string order_)
{
	std::cout<<order_<<" port"<<std::endl;
}
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		Usage(argv[0]);
		exit(1);
	}
	Server* hs = new Server(atoi(argv[1]));
	hs->InitServer();
	hs->Start();
	delete hs;
}
