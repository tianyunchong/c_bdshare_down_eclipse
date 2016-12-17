#include <stdio.h>
#include "common/common.h"
#include "bdshareHelper/bdshareHelper.h"
int main() {
	videoInfoType videoRs[2000];
	char *url = "https://pan.baidu.com/share/link?shareid=2405592869&uk=756635525#list/path=%2F";
	getVideoFromBdshare(url, videoRs);
	return 1;
}
