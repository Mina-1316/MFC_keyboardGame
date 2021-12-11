#include "HttpConnClass.h"

//Header definition. If you want to add more, just add at Header, and below this source both.
const char* HttpConnClass::jsonHeader = "Content-Type: application/json";

//function that returns the response to Json format
Json::Value HttpConnClass::jsonPostRequest(const char domain[], const char body[])
{
	std::string response = url_post_proc(domain, body);

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
std::string HttpConnClass::stringPostRequest(const char domain[], const char body[])
{
	return url_post_proc(domain, body);
}

//functions for request POST connection
std::string HttpConnClass::url_post_proc(const char url[], const char body[])
{
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();
	std::string chunk;

	struct curl_slist* headerlist = nullptr;
	headerlist = curl_slist_append(headerlist, jsonHeader);

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(body));
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