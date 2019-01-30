#pragma once
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#define NOTFOUND 404
#define OK 200

#define WEB_ROOT "wwwroot"
#define HOME_PAGE "index.html"
class Connect{
private:
	int sock;
public:
	Connect(int sock_)
	:sock(sock_)
	{}

	~Connect()
	{
		if(sock >= 0)
		close(sock);
	}

	int ReadOneLine(std::string & line_)
	{
		char buf = 'X';
		while(buf!='\n')
		{
			ssize_t count = recv(sock, &buf, 1, 0);
			if(count > 0)
			{
				if(buf == '\r')
				{
					recv(sock, &buf, 1, MSG_PEEK);
					if(buf == '\n')
					{
					  recv(sock, &buf, 1, 0);
					}
					else
					{
					  buf = '\n';
					}
				}
				line_ += buf;
			}
			else
			{
				break;
			}
		}
		
		return line_.size();
	}
	
};
class Request{
public:
	std::string rq_headline;
	std::string rq_head;
	std::string blank;
	std::string rq_context;
private:
	std::string method;
	std::string uri;
	std::string version;
	std::string param;
	std::string path;
	bool cgi;
public:
	Request()
	:blank("\n")
	,cgi[false]
	,path(WEB_ROOT)
	{}
	
	~Request()
	{}

	void HeadLineParse()
	{
		stringstream ss(rq_headline);
		ss>>method>>uri>>version;
	}

	bool IsMethodValid()
	{
		if(strcasecmp(method, "GET")==0||cgi = (strcasecmp(method, "POST")==0))
			return true;
		return false;
	}

	void UriParse()
	{
		size_t pos_ = uri.find('?');
		if(std::string::npos != pos_)
		{	
			cgi = true;
			param = uri.substr(0, pos_);
			path +=  uri.substr(pos_+1);
		}
		else
		{
           path += uri;
		}

		if(path[path.size()-1]=='\')
			path += HOME_PAGE;
	}
};
class Response{
private:
	std::string rsp_headline;
	std::string rsp_head;
	std::string blank;
	std::string rsp_context;
public:
	int code;
public:
	Response()
	:blank("\n")
	,code(OK)
	{}
	~Response()
	{}
};

class Entry{
public:
	static void*  RequestHander(void* arg_)
	{
		int sock_ = (int)arg_;	
		Connect * link_ = new Connect(sock_);
		Request * re_ = new Request();
		Response * rsp_ = new Response();

		int &code_ = rsp_->code;
		link_->ReadOneLine(re_->rq_headline);
		re_->HeadLineParse();
		if(!re_->IsMethodValid())
		{
			code_ = NOTFOUND;	
			goto end;
		}

		re_->UriParse();

end:
		if(code != OK)
		{
			//错误处理		
		}
		delete link_;
		delete re_;
		delete rsp_;
	}
};
