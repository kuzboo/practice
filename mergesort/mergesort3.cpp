#include<iostream>
#include<vector>
using namespace std;

void merge(vector<int> &nums,vector<int> &temp,int left,int mid,int right)
{
    //左右半区第一个为排序的元素
    int lpos = left, rpos = mid + 1;
    //临时数组下标
    int pos = left;

    //合并
    while(lpos<=mid && rpos<=right)
    {
        if(nums[lpos]<nums[rpos])
            temp[pos++] = nums[lpos++];
        else
            temp[pos++] = nums[rpos++];
    }

    //合并剩余元素
    while(lpos<=mid)
    {
        temp[pos++] = nums[lpos++];
    }
    while(rpos<=right)
    {
        temp[pos++] = nums[rpos++];
    }

    while(left<=right)
    {
        nums[left] = temp[left];
        left++;
    }
}

void mergeSplit(vector<int> &nums, vector<int> &temp, int left, int right)
{
    if(left<right)
    {
        //分别拆分左右半区
        int mid = left + (right - left) / 2;
        mergeSplit(nums, temp, left, mid);
        mergeSplit(nums, temp, mid + 1, right);
        //合并左右半区
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
    vector<int> nums = {66, 77, 2, 4, 3, 6};
    mergeSort(nums);
    print(nums);
}