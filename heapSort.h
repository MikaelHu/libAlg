#pragma once

//*****************
//** 调整大顶堆（仅是调整过程，建立在大顶堆已构建的基础上）
//*****************
template <class T>
inline void adjustHeap(T* arr, int i, int length) {
    int temp = arr[i];//先取出当前元素i
    for (int k = i * 2 + 1; k < length; k = k * 2 + 1) {//从i结点的左子结点开始，也就是2i+1处开始
        if (k + 1 < length && arr[k] < arr[k + 1]) {//如果左子结点小于右子结点，k指向右子结点
            k++;
        }
        if (arr[k] > temp) {//如果子节点大于父节点，将子节点值赋给父节点（不用进行交换）
            arr[i] = arr[k];
            i = k;
        }
        else {
            break;
        }
    }
    arr[i] = temp;//将temp值放到最终的位置
}

//*****************
//** 交换元素
//*****************
template <class T>
inline void swap(T* arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

//*****************
//** 堆排序
//** arr:排序数据
//** length:数据大小
//*****************
template <class T>
void heapSort(T* arr, int length) {
    //1.构建大顶堆
    for (int i = length / 2 - 1; i >= 0; i--) {
        //从第一个非叶子结点从下至上，从右至左调整结构
        adjustHeap(arr, i, length);
    }
    //2.调整堆结构+交换堆顶元素与末尾元素
    for (int j = length - 1; j > 0; j--) {
        swap(arr, 0, j);//将堆顶元素与末尾元素进行交换
        adjustHeap(arr, 0, j);//重新对堆进行调整
    }
}