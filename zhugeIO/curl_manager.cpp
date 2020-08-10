#include "curl_manager.h"
#include "../include/thirdpart/libcurl/include/curl/curl.h"
#pragma comment(lib, "../include/thirdpart/libcurl/lib/libcurl.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "wldap32.lib")
CURLM* cm = nullptr;

/// <summary>
/// ////////////////////////////////////////////////////////////////////////////////////////////////////start
/// </summary>
void Initcurl()
{
	curl_global_init(CURL_GLOBAL_ALL);
	cm = curl_multi_init();
	curl_multi_setopt(cm, CURLMOPT_MAXCONNECTS, (long)1024);
};


#define ENABLE_PROXY
void send(string auth, string data, writeCb cb)
{
	string url = CTransCoding::GBK_To_UTF8(ZHUGE_ADDRESS);
	url = CTransCoding::UrlEncode(url);
	CURL* curl = curl_easy_init();
	if (curl)
	{
		struct curl_slist* headers = NULL;
		//string auth = ZhugeIO::GetAuthority();
		//string auth = "Authorization: Basic MjhjNmQ2YzA2NjcxNDE3Y2E2ZjYwYTNiZjY4ZDc4ZTA6MGFkMjBkNzU1MmRkNGFiZWFkNDYxNjUxOWIxZDRjYjc=";
		//LOG(INFO) << "CCurlMulti::postZhuge Öî¸ðIO auth:" << auth;
		headers = curl_slist_append(headers, "charset:utf-8");
		headers = curl_slist_append(headers, auth.c_str());
		headers = curl_slist_append(headers, "Accept-Encoding:gzip");
		headers = curl_slist_append(headers, "Connection:Keep-Alive");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
#ifdef ENABLE_PROXY
		curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888");
#endif
		curl_easy_setopt(curl, CURLOPT_URL, ZHUGE_ADDRESS.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		//std::string data = "cmjhhhhhaha!";//
		data = CTransCoding::GBK_To_UTF8("data=" + data);
		string postData = CTransCoding::UrlEncode(data);
		//LOG(INFO) << "CCurlMulti::postZhuge Öî¸ðIO data : " << data;
		//LOG(INFO) << "CCurlMulti::postZhuge : " + postData;

		curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, postData.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &pMultiCb->cbJson);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1000);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 1000);

		curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_multi_add_handle(cm, curl);
		int running_count = 0;

		CURLMcode res = curl_multi_perform(cm, &running_count);
		do {
			int numfds = 0;
			int res = curl_multi_wait(cm, NULL, 0, 3000, &numfds);
			if (res != CURLM_OK) {
				//LOG(WARNING) << "error: curl_multi_wait() returned" << res;
			//	return false;
			}
			curl_multi_perform(cm, &running_count);
		} while (running_count);
		curl_easy_cleanup(curl);
	}
}
/// <summary>
/// ////////////////////////////////////////////////////////////////////////////////////////////////////end
/// </summary>