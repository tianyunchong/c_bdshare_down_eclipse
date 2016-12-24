#ifndef _DOWNLOADAPIHELPER_H_
#define _DOWNLOADAPIHELPER_H_
void pregYunDataJson(char * url, char * jsonStr);
void getDownloadUrlByBdsharePage(char *url, char * downApiUrl);
void getDownloadUrlFromYunDataJson(char * jsonStr, char * downApiUrl);
#endif

