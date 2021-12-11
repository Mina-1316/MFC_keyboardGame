#pragma once

// vcpkg�� ����, curl, cppjson ��Ű���� ��ġ�ؾ� ���� ������
#include <curl/curl.h>
#include <json/json.h>

#include <string.h>
#include <sstream>

struct HttpConnException {
	std::string causeLoc;
};

class HttpConnClass
{
public:
	static Json::Value jsonPostRequest(const char domain[], const char postData[]);
	static std::string stringPostRequest(const char domain[], const char postData[]);

private:
	//member function
	static std::string url_post_proc(const char url[], const char post_data[]);
	static size_t callBackFunc(char* ptr, size_t size, size_t nmemb, std::string* stream);
};
