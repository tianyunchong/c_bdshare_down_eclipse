#ifndef _URLHELPER_H_
#define _URLHELPER_H_
/** 从url中提取参数内容copy到res*/
void getParamFromUrl(char *url, char *key, char * res);
/**截取两个字符串之间的内容*/
void substr(char *url, char *from, char*to, char *res) ;
/** 字符串分割函数*/
void splitString(char * string, char * sep, char result[][100]);
/** 字符串替换函数 */
char *str_replace(const char *search, const char *replace, char *string);
/** urlencode加密函数 */
int URLEncode(const char* str, const int strSize, char* result,const int resultSize);
#endif
