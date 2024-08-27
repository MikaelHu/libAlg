#pragma once
#include <string>

static unsigned char skips[256];	//���ܽ��еĲ��Ҵ���
static unsigned char search_len;	//�����ַ�������
static char* searchstr;			//ʵ�ʲ����ַ���

inline void init(const char* str) {
	search_len = strlen(str);
	int len2 = search_len + 1;

	//���ڲ���searchstr�е��ַ�
	for (int i = 0; i < 256; i++)
		skips[i] = len2; //length + 1

	//������searchstr�е��ַ�
	//ֻ�����ұߵ�˫�ַ���������
	for (int i = 0; i < search_len; i++)
		skips[str[i]] = search_len - i;	//����ǰ��λ��

	searchstr = (char*)str;
}

int fastSearch(const char* str, const char* textf, int len) {
	//��ʼ��
	init(str);
	//���searchstr�Ƿ��textf���㳤�ȳ�
	if (search_len > len || search_len == 0)
		return -1/*NULL*/;

	unsigned char* end = (unsigned char*)textf + len;
	int len2 = search_len - 1;
	int j{ 0 };
	int pos{ 0 };

	for (;;) {
		//�Ƚ��ַ�������ѭ��
		j = len2;
		while (textf[j] == searchstr[j] && --j >= 0);

		if (j != -1) {
			//��ƥ�䣬��������textfβ��
			unsigned char* skipindex = (unsigned char*)textf + search_len;
			if (skipindex >= end)
				return -1/*NULL*/;	//����textf�е��ַ���
			textf += skips[*skipindex];
			pos += skips[*skipindex];
		}
		else {
			//����ƥ��
			//return (char*)textf;
			return pos;
		}
	}
	return -1/*NULL*/;
}