#pragma once
#include <memory>

template <class T>
inline void radix(int byte, unsigned long n, T* source, T* dest) {
	unsigned long count[256], i, c, s = 0;
	unsigned char* q;
	int size = sizeof(T);

	//创建子段索引数组
	memset(&count[0], 0x0, 256*sizeof(unsigned long));

	//统计T中每字节值出现的次数
	q = (unsigned char*)source;
	for (i = 0; i < n; i++) {
		count[q[byte]]++;
		q += size;
	}

	//根据计数值，创建索引
	for (i = 0; i < 256; i++) {
		c = count[i];
		count[i] = s;
		s += c;
	}

	//从源数组中，把元素拷贝到目标数组中
	q = (unsigned char*)source;
	for (i = 0; i < n; i++) {
		dest[count[q[byte]]++] = *(T*)q;
		q += size;
	}
}

#define L_ENDIAN //或不定义L_ENDIAN

//*****************
//** 基数排序
//** data:排序数据
//** n:数据大小
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
		if (elemsize & 1) //奇 elemsize->转到另一个？
		{
			radix(elemsize - 1, n, data, temp);
			memcpy(data, temp, n * elemsize);
		}
#else
		for (i = elemsize - 1; i > 0; i -= 2) {
			radix(i, n, data, temp);
			radix(i - 1, n, temp, data);
	}
		if (elemsize & 1) //奇 elemsize->转到另一个？
		{
			radix(0, n, data, temp);
			memcpy(data, temp, n * elemsize);
		}
#endif //L_ENDIAN
		free(temp);
	}
}