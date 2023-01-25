#include <stdio.h>

/************** ���ֲ��� ���� ģ�� **************/
/*

  1�����ε��������㣺����������������������̣� 
  2������ֵ����ɫ���ε���߽磻 
*/

int isGreen(int val, int x);

int binarySearch(int *arr, int arrSize, int x) {
    int l = -1, r = arrSize;
    int mid;
    while(l + 1 < r) {
        mid = l + (r - l) / 2;
        if( isGreen(arr[mid], x) )
            r = mid;
        else
            l = mid;
    }
    return r;
}
/************** ���ֲ��� ���� ģ�� **************/

int isGreen(int val, int x) {
    return val >= x;
}

int search(int* nums, int n, int target){
    int r = binarySearch(nums, n, target);
    if(r == n || nums[r] != target)
        return -1;
    return r;
}
