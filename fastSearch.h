#pragma once
#include <string>

static unsigned char skips[256];	//可能进行的查找次数
static unsigned char search_len;	//查找字符串长度
static char* searchstr;			//实际查找字符串

inline void init(const char* str) {
	search_len = strlen(str);
	int len2 = search_len + 1;

	//对于不在searchstr中的字符
	for (int i = 0; i < 256; i++)
		skips[i] = len2; //length + 1

	//对于在searchstr中的字符
	//只有最右边的双字符记入数组
	for (int i = 0; i < search_len; i++)
		skips[str[i]] = search_len - i;	//返回前侧位置

	searchstr = (char*)str;
}

int fastSearch(const char* str, const char* textf, int len) {
	//初始化
	init(str);
	//检查searchstr是否比textf或零长度长
	if (search_len > len || search_len == 0)
		return -1/*NULL*/;

	unsigned char* end = (unsigned char*)textf + len;
	int len2 = search_len - 1;
	int j{ 0 };
	int pos{ 0 };

	for (;;) {
		//比较字符串的主循环
		j = len2;
		while (textf[j] == searchstr[j] && --j >= 0);

		if (j != -1) {
			//不匹配，对齐与检查textf尾部
			unsigned char* skipindex = (unsigned char*)textf + search_len;
			if (skipindex >= end)
				return -1/*NULL*/;	//不在textf中的字符串
			textf += skips[*skipindex];
			pos += skips[*skipindex];
		}
		else {
			//发现匹配
			//return (char*)textf;
			return pos;
		}
	}
	return -1/*NULL*/;
}