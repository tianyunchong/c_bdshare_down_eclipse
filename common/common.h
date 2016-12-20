#ifndef _COMMON_H_
#define _COMMON_H_
/** 视频相关信息 */
typedef struct _videoInfoType {
    char title[100];//视频的标题
    char downUrl[200];//视频的下载地址
    int  sizel;//视频的大小
} videoInfoType;
typedef struct _bdshareInfoType {
	char shareid[100];//百度shareid
	char uk[100];//百度分享uk
	char fid[100];//fid
	char url[500];//百度视频分享地址(非目录页面)
} bdshareInfoType;
/** 文件数组结构,用于比较获取最大的视频文件的地址 */
typedef struct _videoCompare {
    int key;//下标
    int size;//文件大小
} videoCompare;
#endif
