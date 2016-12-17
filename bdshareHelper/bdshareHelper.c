#include "bdshareHelper.h"
#include "../common/common.h"
#include <stdio.h>
#include <string.h>
/**
 * 从百度分享的链接中提取需要的参数
 */
void getParamsFromBdshareUrl(char *url, bdshareInfoType *bdshareInfo) {
	strcpy(bdshareInfo->fid, "122145");
}
/**
 * 提取下video视频信息
 */
void getVideoFromBdshare(char *url, videoInfoType *videoArr) {
	bdshareInfoType bdshareInfo;
	/** 从url提取需要的百度分享参数 */
	getParamsFromBdshareUrl(url, &bdshareInfo);
	printf("%s\n", bdshareInfo.fid);
	return;
}
