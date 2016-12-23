#include "bdshareHelper.h"
#include "../common/common.h"
#include "../urlHelper/urlHelper.h"
#include "../curlHelper/curlHelper.h"
#include "../stringHelper/stringHelper.h"
#include "cjson/cJSON.h"
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

/**
 * 从百度分享的链接中提取需要的参数
 */
void getParamsFromBdshareUrl(char *url, bdshareInfoType *bdshareInfo) {
	getParamFromUrl(url, "fid", bdshareInfo->fid);
	getParamFromUrl(url, "shareid", bdshareInfo->shareid);
	getParamFromUrl(url, "uk", bdshareInfo->uk);
}
/**
 * 根据url获取当前的分享目录结构路径
 */
void getCurSharePath(char *url, char * curSharePath) {
	struct curl_slist *headers = NULL;
	char *html = curlHtml(url, headers);
	/** 正则表达式开始提取目录 */
	regex_t reg;
	char *pattern = "yunData.PATH = \"([^\"]+)\";";
	int nm = 10;
	regmatch_t pmatch[nm];
	if (regcomp(&reg, pattern, REG_EXTENDED) < 0) {
		return;
	}
	regexec(&reg, html, nm, pmatch, 0);
	int len = pmatch[1].rm_eo - pmatch[1].rm_so;
	if (len) {
		memcpy(curSharePath, html + pmatch[1].rm_so, len);
		/** 去除下右斜杠 */
		char newPath[200];
		str_replace("\\", "", curSharePath, newPath);
		strcpy(curSharePath, newPath);
	}
	return;
}
/**
 * 请求分享目录api接口，提取最终的的分享页面网址
 */
void getVideoFromDirApi(char * childDirApi, bdshareInfoType * bdshareInfo) {
	printf("%s\n", childDirApi);
	struct curl_slist *headers = NULL;
	char *jsonStr = curlHtml(childDirApi, headers);
	getVideoFromDirApiJson(jsonStr, bdshareInfo);
}
/**
 * 从获取的json中提取正确的那个视频地址
 */
void getVideoFromDirApiJson(char *jsonStr, bdshareInfoType * bdshareInfo) {
	if (jsonStr == NULL) {
		return;
	}
	/** 处理可能多余的换行避免影响json的解析 */
	str_replace("\r\n", "", jsonStr, jsonStr);
	//str_replace("\n", "", jsonStr, jsonStr);
	//str_replace("\r", "", jsonStr, jsonStr);
	cJSON *root = cJSON_Parse(jsonStr);
	if (root == NULL) {
		/** 问题原因，获取的json字符串中存在换行，多余的空格的问题 */
		printf("%s\n", jsonStr);
		printf("%s\n", "无法提取到json根数据");
		return;
	}
	int errno = cJSON_GetObjectItem(root, "errno")->valueint;
	if (errno != 0) {
		printf("%s\n", "errno等于0,该目录下没有内容");
		return;
	}
	/** 获取下list节点 */
	cJSON *list = cJSON_GetObjectItem(root, "list");
	if (!list) {
		return;
	}
	/** 遍历下list节点 */
	cJSON *child = cJSON_GetObjectItem(list, 0);
	int key = 0, compareKey = 0;
	int minSize = 0;
	while (child) {
		/** 判断下是否是目录 */
		int is_dir = cJSON_GetObjectItem(child, "isdir")->valueint;
		if (is_dir) {
			goto jump;
		}
		/** 判断是否是视频文件 */
		char *filename =
				cJSON_GetObjectItem(child, "server_filename")->valuestring;
		int isVideo = isVideoByFileName(filename);
		if (isVideo < 1) {
			goto jump;
		}
		/** 获取下视频的长度 */
		int length = cJSON_GetObjectItem(child, "size")->valueint;
		/** 将视频文件加入videoCompare */
		if (length > minSize) {
			minSize = length;
			compareKey = key;
		}
		jump:
		child = child->next;
		key++;
		continue;
	}
	/** 获取符合条件的Key */
	if (minSize <= 0) {
		return;
	}
	/** 获取符合条件的节点 */
	child = cJSON_GetArrayItem(list, compareKey);
	if (child == NULL) {
		printf("%s\n", "未获取到对应的节点");
		return;
	}
	char *filename =
					cJSON_GetObjectItem(child, "server_filename")->valuestring;
	double fs_fid = cJSON_GetObjectItem(child, "fs_id")->valuedouble;
	convertDoubleToString(fs_fid, bdshareInfo->fid);
	/** 将页面数据存入bdshareInfo */
	strcpy(bdshareInfo->title, filename);
}
/**
 * 根据文件名称判断是否是文件名
 */
int isVideoByFileName(char * filename) {
	char *p;
	char *exten[] = { ".avi", ".rmvb", ".rm", ".mp4", ".wmv", ".mkv" };
	int len = sizeof(exten) / sizeof(char *);
	for (int i = 0; i < len; i++) {
		p = strstr(filename, exten[i]);
		if (p != NULL) {
			return 1;
		}
	}
	return 0;
}
/**
 * 提取下video视频信息
 */
bdshareInfoType getVideoFromBdshare(char *url) {
	bdshareInfoType bdshareInfo;
	/** 从url提取需要的百度分享参数 */
	getParamsFromBdshareUrl(url, &bdshareInfo);
	/** 判断是否提取到了fid, 没有则是百度分享目录链接 */
	if (bdshareInfo.fid[0] != '\0') {
		sprintf(bdshareInfo.url, "https://pan.baidu.com/share/link?shareid=%s&uk=%s&fid=%s", bdshareInfo.shareid, bdshareInfo.uk,
				bdshareInfo.fid);
		return bdshareInfo;
	}
	/** 获取当前分享目录path */
	char curSharePath[100] = {0};
	char curSharePathUrlEncode[100];
	printf("%s\n", url);
	getCurSharePath(url, curSharePath);
	URLEncode(curSharePath, strlen(curSharePath), curSharePathUrlEncode, 100);
	/** 获取子目录的api接口地址 */
	char childDirApi[500];
	sprintf(childDirApi,
			"https://pan.baidu.com/share/list?uk=%s&shareid=%s&order=other&desc=1&showempty=0&web=1&page=1&num=100&dir=%s",
			bdshareInfo.uk, bdshareInfo.shareid, curSharePathUrlEncode);
	/** 从api接口中提取分享页面url */
	getVideoFromDirApi(childDirApi, &bdshareInfo);
	if (bdshareInfo.fid[0] != '\0') {
		sprintf(bdshareInfo.url, "https://pan.baidu.com/share/link?shareid=%s&uk=%s&fid=%s", bdshareInfo.shareid, bdshareInfo.uk,
							bdshareInfo.fid);
		return bdshareInfo;
	}
	printf("最终无法从链接%s获取到符合条件的视频文件分享地址\n", url);
	memset(bdshareInfo.url, '\0', strlen(bdshareInfo.url));
	return bdshareInfo;
}
