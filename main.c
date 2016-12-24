#include <stdio.h>
#include "common/common.h"
#include "bdshareHelper/bdshareHelper.h"
#include "urlHelper/urlHelper.h"
#include "curlHelper/curlHelper.h"
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
	char *url = "https://pan.baidu.com/share/link?shareid=2405592869&uk=756635525#list/path=%2F";
	bdshareInfoType bdshareInfo = getVideoFromBdshare(url);
	if (bdshareInfo.url[0] == '\0') {
		printf("%s\n", "未获取到分享视频页面url");
		return 0;
	}
	/** 从单个文件分享页面提取组合下载信息api链接 */
	char downloadUrl[1000];
	getDownloadUrlByBdsharePage(bdshareInfo.url, downloadUrl);
	char html[5000] = {0};
	char postFields[200];
	sprintf(postFields, "encrypt=0&product=share&uk=%s&primaryid=%s&fid_list=[%s]",
			bdshareInfo.uk, bdshareInfo.shareid, bdshareInfo.fid);
	/** curlPost获取具体的下载信息 */
	struct curl_slist *headers = NULL;
	curlPost(downloadUrl, postFields, html, headers);
	printf("%s\n", html);
	return 1;
}


