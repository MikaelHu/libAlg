#pragma once

//*****************
//** ϣ������
//** data:��������
//** n:���ݴ�С
//*****************
template <class T>
void shellSort(T* data, long n) {
	long i, j, h;
	T t;

	//������󲽳�
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
		//����Ϊhʱ�ĵ�������
		for (i = h; i < n; i++) {
			t = data[i];
			for (j = i - h; j >= 0 && (data[j] > t); j -= h)
				data[j + h] = data[j];
			data[j + h] = t;
		}

		//������һ����
		h /= 3;
	}
}