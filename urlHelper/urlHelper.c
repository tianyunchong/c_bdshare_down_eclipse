#include "urlHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * 从url中提取参数内容copy到res
 */
void getParamFromUrl(char *url, char *key, char * res) {
	char * paramStr = (char *) malloc(sizeof(char) * 100);
	/** 提取参数字符串 */
	substr(url, "?", "#", paramStr);
	/** 分割参数字符串为数组 */
	char equalSplitArr[10][100];
	char andSplitArr[10][100];
	splitString(paramStr, "&", equalSplitArr);
	int i = 0;
	while (equalSplitArr[i][0] != '\0') {
		splitString(equalSplitArr[i], "=", andSplitArr);
		if (strcmp(key, andSplitArr[0]) == 0) {
			strcpy(res, andSplitArr[1]);
			return;
		}
		i++;
	}
	return;
}
/**
 * 截取两个字符串之间的内容
 */
void substr(char *url, char *from, char*to, char *res) {
	char content[200] = { 0 };
	char * posStart = strstr(url, from);
	char * posEnd = strstr(url, to);
	if (posStart == NULL) {
		return;
	}
	if (posEnd == NULL) {
		posEnd = url + strlen(url);
	}
	strncpy(content, posStart + 1, posEnd - posStart - 1);
	strcpy(res, content);
}

/**
 * 字符串分割函数
 * @param string
 * @param sep
 * @param result
 */
void splitString(char * string, char * sep, char result[][100]) {
	char stringbak[200];
	strcpy(stringbak, string);
	char *p = strtok(stringbak, sep);
	int i = 0;
	while (p != NULL) {
		strcpy(result[i++], p);
		p = strtok(NULL, sep);
	}
}

/**
 * 字符串替换函数
 */
char *str_replace(const char *search, const char *replace, char *string) {
	char *stringbak = (char *) malloc(strlen(string) + 1);
	char *res = (char *) malloc(sizeof(char) * 1000 + strlen(string));
	char *p;
	memset(res, '\0', strlen(res));
	strcpy(stringbak, string);
	while ((p = strstr(stringbak, search)) != NULL) {
		/** 开始将检索到的内容之前的copy到res*/
		strncat(res, stringbak, (p - stringbak));
		strncat(res, replace, strlen(replace));
		/** 移动下stringbak的指针 */
		stringbak = p + strlen(search);
	}
	/** 最后将stringbak最后一截连接到res */
	strncat(res, stringbak, strlen(stringbak));
	return res;
}

/**
 * @brief URLEncode 对字符串URL编码
 *
 * @param str 原字符串
 * @param strSize 原字符串长度(不包括最后的\0)
 * @param result 结果缓冲区的地址
 * @param resultSize 结果缓冲区的大小(包括最后的\0)
 *
 * @return: >0:resultstring 里实际有效的长度
 *            0: 解码失败.
 */
int URLEncode(const char* str, const int strSize, char* result,
		const int resultSize) {
	int i;
	int j = 0; //for result index
	char ch;
	if ((str == NULL) || (result == NULL) || (strSize <= 0)
			|| (resultSize <= 0)) {
		return 0;
	}
	for (i = 0; (i < strSize) && (j < resultSize); ++i) {
		ch = str[i];
		if (((ch >= 'A') && (ch < 'Z')) || ((ch >= 'a') && (ch < 'z'))
				|| ((ch >= '0') && (ch < '9'))) {
			result[j++] = ch;
		} else if (ch == ' ') {
			result[j++] = '+';
		} else if (ch == '.' || ch == '-' || ch == '_' || ch == '*') {
			result[j++] = ch;
		} else {
			if (j + 3 < resultSize) {
				sprintf(result + j, "%%%02X", (unsigned char) ch);
				j += 3;
			} else {
				return 0;
			}
		}
	}
	result[j] = '\0';
	return j;
}
