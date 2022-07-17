#include<iostream>
#include<vector>
using namespace std;

// void merge(vector<int> &nums,vector<int> &temp,int left,int mid, int right)
// {
//     int lpos = left; // 左半区第一个未排序的元素
//     //int rpos = right;// 右半区第一个未排序的元素
//     int rpos = mid + 1;
//     int pos = left; // 临时数组元素下标

//     //while(lpos<=left && rpos<=right)
//     while(lpos<=mid && rpos<=right)
//     {
//         if(nums[lpos]<=nums[rpos]) // 如果左半区的元素更小
//             temp[pos++] = nums[lpos++];
//         else
//             temp[pos++] = nums[rpos++];
//     }
//     //合并剩余元素
//     //while(lpos<=left)
//     while(lpos<=mid)
//         temp[pos++] = nums[lpos++];
//     while(rpos <= right)
//         temp[pos++] = nums[rpos++];
    
//     //把临时数组元素合并后的元素复制给原来的数组
//     while(left<=right)
//         //nums[left++] = temp[left++];
//     {
//         nums[left] = temp[left];
//         left++;
//     }
// }

// void mergeSplit(vector<int> &nums,vector<int> &temp,int left,int right)
// {
//     if(left<right) // 剩余一个不需要拆分
//     {
//         int mid = left + (right - left) / 2;
//         mergeSplit(nums, temp, left, mid); //划分左半区
//         mergeSplit(nums, temp, mid + 1, right); //划分右半区
//         merge(nums, temp, left, mid, right);//合并
//     }
// }

// void mergeSort(vector<int> &nums)
// {
//     int n = nums.size();
//     vector<int> temp(n, 0);
//     mergeSplit(nums, temp, 0, n - 1);
// }

void merge(vector<int> &nums, vector<int> &temp, int left, int mid, int right)
{
    //左、右半区第一个未排序的元素下标
    int lpos = left, rpos = mid + 1;
    int pos = left;

    //左右半区进行排序
    while(lpos<=mid && rpos<=right)
    {
        if(nums[lpos]<nums[rpos])
            temp[pos++] = nums[lpos++];
        else
            temp[pos++] = nums[rpos++];
    }

    //合并剩余元素
    while(lpos<=mid)
        temp[pos++] = nums[lpos++];
    while (rpos <= right)
        temp[pos++] = nums[rpos++];

    //将temp复制给nums
    while(left<=right)
    {
        nums[left] = temp[left];
        ++left;
    }
}

void mergeSplit(vector<int> &nums, vector<int> &temp, int left, int right)
{
    if(left<right)
    {
        int mid = left + (right - left) / 2;
        //分别拆分左右半区
        mergeSplit(nums, temp, left, mid);
        mergeSplit(nums, temp, mid + 1, right);
        //合并两个半区
        merge(nums, temp, left, mid, right);
    }
}

void mergeSort(vector<int> &nums)
{
    int n = nums.size();
    vector<int> temp(n, 0);
    mergeSplit(nums, temp, 0, n - 1);
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
    vector<int> nums = {66, 5, 2, 4, 3, 6};
    mergeSort(nums);
    print(nums);
}