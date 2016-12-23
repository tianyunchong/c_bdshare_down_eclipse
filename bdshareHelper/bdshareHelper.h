#ifndef _BDSHAREHELPER_H_
#define _BDSHAREHELPER_H_
#include "../common/common.h"
/** 从百度分享的链接中提取需要的参数*/
void getParamsFromBdshareUrl(char *url, bdshareInfoType *bdshareInfo);
/** 提取下video视频信息 */
bdshareInfoType getVideoFromBdshare(char *url);
/** 请求分享目录api接口，提取最终的的分享页面网址*/
void getVideoFromDirApi(char * childDirApi, bdshareInfoType * bdshareInfo);
/** 从获取的json中提取正确的那个视频地址 */
void getVideoFromDirApiJson(char *jsonStr, bdshareInfoType * bdshareInfo);
/** 根据文件名称判断是否是视频文件 */
int isVideoByFileName(char * filename);
#endif
