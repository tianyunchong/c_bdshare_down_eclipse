#include "headers.h"
#include "curl/curl.h"
/**
 * 获取下盘多多页面的请求headers
 * @return
 */
struct curl_slist getPanduduoHeaders()
{
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    //headers = curl_slist_append(headers, "Accept-Encoding:gunzip, deflate, sdch");
    headers = curl_slist_append(headers, "Accept-Language:zh-CN,zh;q=0.8");
    headers = curl_slist_append(headers, "Connection:keep-alive");
    headers = curl_slist_append(headers, "Cookie:PANWEB=1; bdshare_firstime=1480907431423; secu=1; t_pcnt=20161209-0; recommendTime=mac2016-12-07%2016%3A35; BAIDUID=4F204B77C662244B40525F2591499BA2:FG=1; PSTM=1481331186; BIDUPSID=A5702516B9D4C0E05BF8B7BD7EF752E3; BDUSS=Ux3RDFSNEZBNUVacmhMNWs1Tk1MOEVNa2QxTjczLXcxaEt2RjY2c21hLVgzM0pZSVFBQUFBJCQAAAAAAAAAAAEAAABM5u8kemhhbmd5YW5naHVhMTEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJdSS1iXUktYQ; STOKEN=a21ee625d0a87d975019aa15494c4fd32ed63c52850ea2fdb800e7834cb4c7fa; SCRC=b33aedf286ca77967079eae23f407308; Hm_lvt_7a3960b6f067eb0085b7f96ff5e660b0=1481264143,1481264398,1481264491,1481265033; Hm_lpvt_7a3960b6f067eb0085b7f96ff5e660b0=1481510699; BDRCVFR[feWj1Vr5u3D]=I67x6TjHwwYf0; PSINO=5; H_PS_PSSID=1429_21121_20592_21554_21408_21614_20718; PANPSC=17706447275084148842%3a0JkSUlxv8cXKfhx8dzF5Pi%2brrbuHl7SO1xvRpgWaXhU2NqqtBIcaCD9hnwPONS7CfPb0JMZPTIzIHinbRm95htG%2fFln7qaGWRPoS1ZAzLYrIUyrvncE2%2fxnaAP1cyVD%2fkKn4IHRP%2fJall4fXSwQiYKikII2LTYQXcW%2bHrBiQZjjPxrXw1kkdgx1rCf0MdMHcn10UGSKsliQtCEV17h5v%2fA%3d%3d");
    headers = curl_slist_append(headers, "Host:www.panduoduo.net");
    headers = curl_slist_append(headers, "Upgrade-Insecure-Requests:1");
    headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.100 Safari/537.36");
    return *headers;
}
/**
 * 获取百度分享的header头
 */
struct curl_slist getBdshareHeaders() {
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept:*/*");
	headers = curl_slist_append(headers, "Accept-Encoding:gzip, deflate, br");
	headers = curl_slist_append(headers, "Accept-Language:zh-CN,zh;q=0.8");
	headers = curl_slist_append(headers, "Connection:keep-alive");
	headers = curl_slist_append(headers, "Content-Length:282");
	headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded; charset=UTF-8");
	headers = curl_slist_append(headers, "Cookie:PANWEB=1; bdshare_firstime=1482454432394; secu=1; BAIDUID=3C82B203A91CD31F1CF13149B3CA03D4:FG=1; BIDUPSID=A5702516B9D4C0E05BF8B7BD7EF752E3; PSTM=1482476666; BDRCVFR[feWj1Vr5u3D]=I67x6TjHwwYf0; BDRCVFR[S4-dAuiWMmn]=I67x6TjHwwYf0; PSINO=5; H_PS_PSSID=1431_21100_17001_21554; STOKEN=89597f888aba488bb4e1d9b66b541a09ce5fc9d5bdc2a68fdb86f232dbd7b9f1; SCRC=4dc367f3cebd4ca70e23f6aedda495d2; cflag=15%3A3; PANPSC=14752934435026528884%3AEFB88jicTNLIIQ%2FGwTQ8zqikII2LTYQXcW%2BHrBiQZjjPxrXw1kkdg%2FFMne%2FXPWb62wyKzCEShLJUr5G93jOpU%2BeQVSd8i5P5yt%2FP6svRCu29Q07q%2Fjo4G61Sr93PEHDiYPmcdmbZp7t47JUMmOhyXSeKHrlyURG2vIcMCeE%2BEzPl0236xFtTr%2BHiRzDwUrQ6; Hm_lvt_7a3960b6f067eb0085b7f96ff5e660b0=1482454418,1482454425,1482454432,1482454472; Hm_lpvt_7a3960b6f067eb0085b7f96ff5e660b0=1482546794");
	headers = curl_slist_append(headers, "Host:pan.baidu.com");
	headers = curl_slist_append(headers, "Origin:https://pan.baidu.com");
	headers = curl_slist_append(headers, "Origin:https://pan.baidu.com");
	return *headers;
}
