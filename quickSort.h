#pragma once

//*****************
//** ��������
//** arr:��������
//** low: ��λ
//** high: ��λ
//*****************
template <class T>
void quickSort(T* arr, int low, int high) {
    if (high <= low) return;
    int i = low;
    int j = high + 1;
    T key = arr[low];
    while (true)
    {
        /*���������ұ�key���ֵ*/
        while (arr[++i] < key)
        {
            if (i == high)
                break;
        }
        /*���������ұ�keyС��ֵ*/
        while (arr[--j] > key)
        {
            if (j == low)
                break;
        }
        if (i >= j) break;
        /*����i,j��Ӧ��ֵ*/
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    /*����ֵ��j��Ӧֵ����*/
    T temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;
    quickSort(arr, low, j - 1);
    quickSort(arr, j + 1, high);
}