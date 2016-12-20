#include "curlHelper.h"
#include "curl/curl.h"
#include <stdlib.h>
#include <string.h>
/**
 * curl抓取下页面html内容
 */
char *curlHtml(char *url, struct curl_slist *headers) {
	char * html = (char *) malloc(sizeof(char) * 200000);
	memset(html, '\0', strlen(html));
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_gethtml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, html);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return html;
}

/**
 * 获取返回html内容
 */
size_t callback_gethtml(void *ptr, size_t size, size_t nmemb, void *userp) {
	strcat(userp, (char *) ptr);
	return size * nmemb;
}

