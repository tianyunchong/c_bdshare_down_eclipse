#include <stdio.h>
#include "common/common.h"
#include "bdshareHelper/bdshareHelper.h"
#include "urlHelper/urlHelper.h"
#include "curlHelper/curlHelper.h"
#include <string.h>
#include <stdlib.h>
#include "curl/curl.h"
void test11() {
	char * p = (char *)malloc(sizeof(char) * 10);
	memset(p, '\0', strlen(p));
	strcpy(p, "http://ww.baidu.comggg");
	printf("%s\n", p);
	free(p);
}
int main() {
	//videoInfoType videoRs[2000];
	char *url = "https://pan.baidu.com/share/link?shareid=2405592869&uk=756635525#list/path=%2F";
	bdshareInfoType bdshareInfo = getVideoFromBdshare(url);
	printf("%s\n", bdshareInfo.url);
	return 1;
}


