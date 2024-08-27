#pragma once

//*****************
//** 希尔排序
//** data:排序数据
//** n:数据大小
//*****************
template <class T>
void shellSort(T* data, long n) {
	long i, j, h;
	T t;

	//计算最大步长
	h = 1;
	if (n < 14)
		h = 1;
	else
	{
		while (h < n)
			h = 3 * h + 1;
		h /= 3;
		h /= 3;
	}

	while (h > 0) {
		//步长为h时的迭代排序
		for (i = h; i < n; i++) {
			t = data[i];
			for (j = i - h; j >= 0 && (data[j] > t); j -= h)
				data[j + h] = data[j];
			data[j + h] = t;
		}

		//计算下一步长
		h /= 3;
	}
}