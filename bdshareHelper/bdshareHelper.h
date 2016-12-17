#ifndef _BDSHAREHELPER_H_
#define _BDSHAREHELPER_H_
#include "../common/common.h"
/** 从百度分享的链接中提取需要的参数*/
void getParamsFromBdshareUrl(char *url, bdshareInfoType *bdshareInfo);
/** 提取下video视频信息 */
void getVideoFromBdshare(char *url, videoInfoType *videoArr);
#endif
