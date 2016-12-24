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
 *	post提交数据获取数据内容
 */
void curlPost(char * url, char * postFields, char * getHtml, struct curl_slist *headers) {
	CURL * curl = curl_easy_init();
	if (!curl) {
		printf("%s\n", "curl init failed!");
		return;
	}
	curl_easy_setopt(curl,CURLOPT_URL,url); //url地址
	curl_easy_setopt(curl,CURLOPT_POSTFIELDS,postFields); //post参数
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,callback_gethtml); //对返回的数据进行操作的函数地址
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,getHtml); //这是callback_gethtml的第四个参数值
    curl_easy_setopt(curl,CURLOPT_POST,1); //设置问非0表示本次操作为post
    //curl_easy_setopt(curl,CURLOPT_HEADER,1); //将响应头信息和响应体一起传给callback_gethtml
    curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1); //设置为非0,响应头信息location
    //curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"/Users/zhu/CProjects/curlposttest.cookie");//cookie设置
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

}

/**
 * 获取返回html内容
 */
size_t callback_gethtml(void *ptr, size_t size, size_t nmemb, void *userp) {
	strcat(userp, (char *) ptr);
	return size * nmemb;
}

