#include <stdio.h>
#include "common/common.h"
#include "bdshareHelper/bdshareHelper.h"
#include "urlHelper/urlHelper.h"
#include "bdshareHelper/downloadApiHelper.h"
#include <string.h>
#include <stdlib.h>
void test(char * test11) {
	sprintf(test11, "%saaabbb", "http://w");
}
void ccc(char * test11) {
	test(test11);
}
int main() {
//	char test11[100];
//	ccc(test11);
//	printf("%s\n", test11);
	//videoInfoType videoRs[2000];
	char *url = "https://pan.baidu.com/share/link?shareid=2405592869&uk=756635525#list/path=%2F";
	bdshareInfoType bdshareInfo = getVideoFromBdshare(url);
	if (bdshareInfo.url[0] == '\0') {
		printf("%s\n", "未获取到分享视频页面url");
		return 0;
	}
	/** 从单个文件分享页面提取组合下载信息api链接 */
	char downloadUrl[1000];
	getDownloadUrlByBdsharePage(bdshareInfo.url, downloadUrl);
	printf("aa%s\n", downloadUrl);
	return 1;
}


