#include<iostream>
#include<vector>
using namespace std;

//合并
// void merge(vector<int> &nums, vector<int> &temp, int left, int mid, int right)
// {
//     int lpos = left; //标记左半区第一个未排序的元素
//     int rpos = mid + 1; //标记右半区第一个未排序的元素
//     int pos = left;     //临时数组元素的下标

//     //合并
//     while(lpos<=mid && rpos<=right)
//     {
//         if(nums[lpos]<nums[rpos]) //左半区第一个剩余元素更小
//             temp[pos++] = nums[lpos++];
//         else                      //右半区第一个剩余元素更小
//             temp[pos++] = nums[rpos++];
//     }
//     //合并左半区剩余元素
//     while(lpos<=mid)
//         temp[pos++] = nums[lpos++];
//     //合并右半区剩余元素
//     while(rpos<=right)
//         temp[pos++] = nums[rpos++];
    
//     //把临时数组中合并后的数组复制回原来的数组
//     //nums = temp;
//     while(left<=right )
//     {
//         nums[left] = temp[left];
//         left++;
//     }
// }
// //划分
// void msort(vector<int> &nums, vector<int> &temp, int left, int right)
// {
//     //如果只有一个元素不需要划分
//     if(left<right)
//     {
//         //找中间点
//         int mid = left + (right - left) / 2;
//         //递归划分左半区(左半区是包含中间点之前的，所以要包括mid)
//         msort(nums, temp, left, mid);
//         //递归划分右半区
//         msort(nums, temp, mid + 1, right);
//         //合并已经排序好的部分
//         merge(nums, temp, left, mid, right);
//     }
// }
// //归并排序入口
// void mergeSort(vector<int>&nums,int n)
// {
//     vector<int> temp(n, 0);
//     {
//         msort(nums, temp, 0, n - 1);
//     }
// }

void merge(vector<int> &nums,vector<int> &temp,int left,int mid,int right)
{
    //左右半区未排序的第一个
    int lpos = left, rpos = mid + 1;
    int pos = left;
    while(lpos<=mid && rpos<=right)
    {
        if(nums[lpos]<nums[rpos])
            temp[pos++] = nums[lpos++];
        else
            temp[pos++] = nums[rpos++];
    }
    while(lpos<=mid)
        temp[pos++] = nums[lpos++];
    while(rpos<=right)
        temp[pos++] = nums[rpos++];
    
    while(left<=right)
    {
        nums[left]=temp[left];
        left++;
    }
}

void mergeSplit(vector<int> &nums,vector<int> &temp,int left,int right)
{
    if(left<right)
    {
        int mid = left + (right - left) / 2;
        mergeSplit(nums, temp, left, mid);
        mergeSplit(nums, temp, mid + 1, right);
        merge(nums, temp, left, mid, right);
    }
}

void mergeSort(vector<int> &nums,int n)
{
    vector<int> temp(n);
    mergeSplit(nums,temp,0,n-1);
}
void print(const vector<int> &nums)
{
    for(int i:nums)
    {
        cout << i << " ";
    }
    cout << endl;
}
int main()
{
    vector<int> nums = {1, 5, 2, 99, 3, 6};
    mergeSort(nums, nums.size());
    print(nums);
}