#pragma once
#include <memory>

template <class T>
inline void radix(int byte, unsigned long n, T* source, T* dest) {
	unsigned long count[256], i, c, s = 0;
	unsigned char* q;
	int size = sizeof(T);

	//�����Ӷ���������
	memset(&count[0], 0x0, 256*sizeof(unsigned long));

	//ͳ��T��ÿ�ֽ�ֵ���ֵĴ���
	q = (unsigned char*)source;
	for (i = 0; i < n; i++) {
		count[q[byte]]++;
		q += size;
	}

	//���ݼ���ֵ����������
	for (i = 0; i < 256; i++) {
		c = count[i];
		count[i] = s;
		s += c;
	}

	//��Դ�����У���Ԫ�ؿ�����Ŀ��������
	q = (unsigned char*)source;
	for (i = 0; i < n; i++) {
		dest[count[q[byte]]++] = *(T*)q;
		q += size;
	}
}

#define L_ENDIAN //�򲻶���L_ENDIAN

//*****************
//** ��������
//** data:��������
//** n:���ݴ�С
//*****************
template <class T> 
void radixSort(T* data, unsigned long n) {
	int i, elemsize = sizeof(T);
	T* temp = (T*)malloc(n* elemsize);

	if (temp != NULL)
	{
#ifdef L_ENDIAN
		for (i = 0; i < elemsize; i += 2) {
			radix(i, n, data, temp);
			radix(i + 1, n, temp, data);
		}
		if (elemsize & 1) //�� elemsize->ת����һ����
		{
			radix(elemsize - 1, n, data, temp);
			memcpy(data, temp, n * elemsize);
		}
#else
		for (i = elemsize - 1; i > 0; i -= 2) {
			radix(i, n, data, temp);
			radix(i - 1, n, temp, data);
	}
		if (elemsize & 1) //�� elemsize->ת����һ����
		{
			radix(0, n, data, temp);
			memcpy(data, temp, n * elemsize);
		}
#endif //L_ENDIAN
		free(temp);
	}
}