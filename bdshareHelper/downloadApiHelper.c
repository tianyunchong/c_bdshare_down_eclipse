#include "downloadApiHelper.h"
#include "../urlHelper/urlHelper.h"
#include "../curlHelper/curlHelper.h"
#include "cjson/cJSON.h"
#include <stdio.h>
#include "curl/curl.h"
#include <regex.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
/**
 * 从单个的百度视频分享页面获取参数并组合成最终想要的下载请求链接
 */
void getDownloadUrlByBdsharePage(char *url, char * downApiUrl) {
	/** 从html中提取yunData的json数据字符串 */
	char jsonStr[5000];
	pregYunDataJson(url, jsonStr);
	str_replace("\r\n", "", jsonStr, jsonStr);
	/** 从json中提取元素组合下载接口 */
	getDownloadUrlFromYunDataJson(jsonStr, downApiUrl);
}
/**
 * 从yunData的json字符串中提取需要的数组组合下载接口链接
 */
void getDownloadUrlFromYunDataJson(char * jsonStr, char * downApiUrl) {
	cJSON *root = cJSON_Parse(jsonStr);
	if (root == NULL) {
		return;
	}
	cJSON *file_list = cJSON_GetObjectItem(root, "file_list");
	char * sign =  cJSON_GetObjectItem(root, "sign")->valuestring;
	cJSON *list = cJSON_GetObjectItem(file_list, "list");
	if (list == NULL) {
		return;
	}
	cJSON * listFirst = cJSON_GetArrayItem(list, 0);
	if (listFirst == NULL) {
		return;
	}
	char * app_id = cJSON_GetObjectItem(listFirst, "app_id")->valuestring;
	time_t rawtime;
	time(&rawtime);
	sprintf(downApiUrl,  "https://pan.baidu.com/api/sharedownload?sign=%s&timestamp=%ld&bdstoken=null&channel=chunlei&clienttype=0&web=1&app_id=%s",
			sign, rawtime, app_id);
}

/**
 * 从html中提取yunData的json字符串内容
 */
void pregYunDataJson(char * url, char * jsonStr) {
	struct curl_slist *headers = NULL;
	char * html = curlHtml(url, headers);
	regex_t reg;
	char *pattern = "yunData.setData\\(([^;]+)\\);";
	int nm = 10;
	regmatch_t pmatch[nm];
	if (regcomp(&reg, pattern, REG_EXTENDED) < 0) {
		return;
	}
	regexec(&reg, html, nm, pmatch, 0);
	int len = pmatch[1].rm_eo - pmatch[1].rm_so;
	if (len) {
			memcpy(jsonStr, html + pmatch[1].rm_so, len);
			str_replace("\\", "", jsonStr, jsonStr);
	}
	return;
}

