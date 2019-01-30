#pragma once
#include<string>
#define INFO 0
#define ERROR 1
#define WARNING 2
std::string GetLevel(int arg_)
{
	switch(arg_)
	{
		case 0:
			return "INFO";
		case 1:
			return "ERROR";
		case 2:
			return "WARNING";
		default:
			return "UNKOW";
	}
}
void Log(int level_,std::string info_,std::string file_,int line_)
{
	std::cout<<"[ "<<GetLevel(level_)<<" ]"<<" "<<info_<<" "<<file_<<":"<<line_<<std::endl;
	
}
#define LOG(level_ ,  info_)  Log(level_ , info_ , __FILE__, __LINE__)
