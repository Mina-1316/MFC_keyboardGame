#pragma once

// vcpkg�� ����, curl, cppjson ��Ű���� ��ġ�ؾ� ���� ������
#include <curl/curl.h>
#include <json/json.h>

#include <string.h>
#include <sstream>
#include <list>

struct HttpConnException {
	std::string causeLoc;
};

class HttpConnClass
{
public:
	static Json::Value jsonPostRequest(const char domain[], const char body[]);
	static std::string stringPostRequest(const char domain[], const char body[]);

private:
	//member function
	static std::string url_post_proc(const char url[], const char body[]);
	static size_t callBackFunc(char* ptr, size_t size, size_t nmemb, std::string* stream);

	//const
	static const char *jsonHeader;

};
