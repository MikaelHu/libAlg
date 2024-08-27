#pragma once

//*****************
//** 快速排序
//** arr:排序数据
//** low: 低位
//** high: 高位
//*****************
template <class T>
void quickSort(T* arr, int low, int high) {
    if (high <= low) return;
    int i = low;
    int j = high + 1;
    T key = arr[low];
    while (true)
    {
        /*从左向右找比key大的值*/
        while (arr[++i] < key)
        {
            if (i == high)
                break;
        }
        /*从右向左找比key小的值*/
        while (arr[--j] > key)
        {
            if (j == low)
                break;
        }
        if (i >= j) break;
        /*交换i,j对应的值*/
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    /*中枢值与j对应值交换*/
    T temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;
    quickSort(arr, low, j - 1);
    quickSort(arr, j + 1, high);
}