#include "HttpConnClass.h"

//function that returns the response to Json format
Json::Value HttpConnClass::jsonPostRequest(const char domain[], const char postData[])
{
	std::string response = url_post_proc(domain,postData);
	
	Json::Value json;
	Json::CharReaderBuilder reader;
	Json::String errs;
	std::stringstream ss(response.c_str());

	if (!ss) throw HttpConnException{ "Errors on Http : HttpConnClass::jsonPostRequest/invalid stringstream" };

	auto bret = Json::parseFromStream(reader, ss, &json, &errs);

	if (bret == false) {
		throw HttpConnException{ "Errors on Http : HttpConnClass::jsonPostRequest/Invalid Json Parsing" };
	}
	
	return json;
}

//function that returns the response to string format
std::string HttpConnClass::stringPostRequest(const char domain[], const char postData[])
{
	return url_post_proc(domain, postData);
}

//functions for request POST connection
std::string HttpConnClass::url_post_proc(const char url[], const char post_data[])
{
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();
	std::string chunk;

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post_data));
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (std::string*)&chunk);
		curl_easy_setopt(curl, CURLOPT_PROXY, "");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	if (res != CURLE_OK) {
		throw HttpConnException{ "Errors on Http : HttpConnClass::url_post_proc" };
	}

	return chunk;
}

//functions for writing function callback
size_t HttpConnClass::callBackFunc(char* ptr, size_t size, size_t nmemb, std::string* stream)
{
	int realsize = size * nmemb;
	stream->append(ptr, realsize);
	return realsize;
}
