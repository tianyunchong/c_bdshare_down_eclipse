#ifndef _CURLHELPER_H_
#define _CURLHELPER_H_
#include "curl/curl.h"
char *curlHtml(char *url, struct curl_slist *headers);
size_t callback_gethtml(void *ptr, size_t size, size_t nmemb, void *userp);
#endif
