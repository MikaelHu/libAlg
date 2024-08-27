#pragma once
#include <string>

static unsigned char searchstr[256];	//模式最大长度为256
static unsigned char alfa[256];		//记住字母的位置
static unsigned char skipsInsens[256];	//跳过数组
static unsigned char patlenInsens;		//查找模式的长度


//init函数
inline void initInsens(const char* str) {
	int len1 = 0;

	//获得长度， 进行小块拷贝
	unsigned char c = str[len1];
	while (c != '\0') {
		alfa[len1] = 0;
		if (c >= 'A' && c <= 'Z') {
			searchstr[len1] = c + 0x20;
			alfa[len1] = 1;
		}
		else {
			searchstr[len1] = c;
			if (c >= 'a' && c <= 'z')
				alfa[len1] = 1;
		}

		c = str[++len1];
	}

	int len2 = len1 + 1;

	//对于不在模式中的字符
	for (int i = 0; i < 255; i++)
		skipsInsens[i] = len2;	//length + 1

	//对于在模式中的字符
	//只有最右边的双字符记入数组
	for (int i = 0; i < len1; i++) {
		skipsInsens[searchstr[i]] = len1 - i;
		if (alfa[i]) skipsInsens[searchstr[i] - 0x20] = len1 - i;
	}

	patlenInsens = len1;
}

int fastSearchInsens(const char* str, const char* textf, int len) {
	//初始化
	initInsens(str);
	//检查searchstr是否比textf或零长度长
	if (patlenInsens > len || patlenInsens == 0)
		return -1/*NULL*/;

	unsigned char* end = (unsigned char*)textf + len;
	int len2 = patlenInsens - 1;
	int j{ 0 };
	int pos{ 0 };

	for (;;) {
		//比较字符串的主循环
		j = len2;
		while (
			((textf[j] == searchstr[j]) || 
				(alfa[j] && (textf[j] == (char)(searchstr[j] - 0x20))))
			&& --j >= 0);

		if (j != -1) {
			//不匹配，对齐与检查textf尾部
			unsigned char* skipindex = (unsigned char*)textf + patlenInsens;
			if (skipindex >= end)
				return -1/*NULL*/;	//不在textf中的字符串
			textf += skipsInsens[*skipindex];
			pos += skipsInsens[*skipindex];
		}
		else {
			//发现匹配
			//return (char*)textf;
			return pos;
		}
	}
	return -1/*NULL*/;
}