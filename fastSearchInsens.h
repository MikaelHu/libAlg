#pragma once
#include <string>

static unsigned char searchstr[256];	//ģʽ��󳤶�Ϊ256
static unsigned char alfa[256];		//��ס��ĸ��λ��
static unsigned char skipsInsens[256];	//��������
static unsigned char patlenInsens;		//����ģʽ�ĳ���


//init����
inline void initInsens(const char* str) {
	int len1 = 0;

	//��ó��ȣ� ����С�鿽��
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

	//���ڲ���ģʽ�е��ַ�
	for (int i = 0; i < 255; i++)
		skipsInsens[i] = len2;	//length + 1

	//������ģʽ�е��ַ�
	//ֻ�����ұߵ�˫�ַ���������
	for (int i = 0; i < len1; i++) {
		skipsInsens[searchstr[i]] = len1 - i;
		if (alfa[i]) skipsInsens[searchstr[i] - 0x20] = len1 - i;
	}

	patlenInsens = len1;
}

int fastSearchInsens(const char* str, const char* textf, int len) {
	//��ʼ��
	initInsens(str);
	//���searchstr�Ƿ��textf���㳤�ȳ�
	if (patlenInsens > len || patlenInsens == 0)
		return -1/*NULL*/;

	unsigned char* end = (unsigned char*)textf + len;
	int len2 = patlenInsens - 1;
	int j{ 0 };
	int pos{ 0 };

	for (;;) {
		//�Ƚ��ַ�������ѭ��
		j = len2;
		while (
			((textf[j] == searchstr[j]) || 
				(alfa[j] && (textf[j] == (char)(searchstr[j] - 0x20))))
			&& --j >= 0);

		if (j != -1) {
			//��ƥ�䣬��������textfβ��
			unsigned char* skipindex = (unsigned char*)textf + patlenInsens;
			if (skipindex >= end)
				return -1/*NULL*/;	//����textf�е��ַ���
			textf += skipsInsens[*skipindex];
			pos += skipsInsens[*skipindex];
		}
		else {
			//����ƥ��
			//return (char*)textf;
			return pos;
		}
	}
	return -1/*NULL*/;
}