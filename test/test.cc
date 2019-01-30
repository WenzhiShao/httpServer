#include<iostream>
#include<sstream>
#include<string>
int main()
{
	char *c = "aa bb cc dd";
	std::stringstream ss(c);
	std::string p1,p2,p3;
	ss>>p1>>p2>>p3;
	std::cout<<p1+" "<<p2+" "<<p3+" "<<std::endl;
//	std::cout<<"test"<<std::endl;
}
