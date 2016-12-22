#include "stringHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * 将浮点型的数据转换成字符型
 */
void convertDoubleToString(double from, char * to) {
	char *tmp = (char *)malloc(sizeof(char) * 200);
	sprintf(tmp, "%f", from);
	char * p = strstr(tmp, ".");
	if (p == NULL) {
		return;
	}
	memset(p, '\0', strlen(p));
	strcpy(to, tmp);
	free(tmp);
}
