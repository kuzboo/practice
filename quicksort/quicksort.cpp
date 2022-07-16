#include<vector>
#include<iostream>
using namespace std;

/*
//选取最后一个元素作为标志，把小的都放到前头
int getMid(vector<int>&nums,int low,int high)
{
    int key = nums[high];
    int i = low;
    for (int j = low; j < high;++j)
    {
        if(nums[j]<key)
        {
            swap(nums[i++], nums[j]);
        }
    }
    //最后i指向的位置一定大于=key
    swap(nums[i], nums[high]);
    return i;
}

void quickSort(vector<int>&nums,int low,int high)
{
    if(low<high)
    {
        int mid = getMid(nums, low, high);
        quickSort(nums, low, mid - 1);
        quickSort(nums, mid + 1, high);
    }
}*/

// int getMid(vector<int> &nums,int low,int high)
// {
//     int key = nums[high];
//     int i = low;
//     //比key小的放前头
//     for (int j = low; j < high;++j)
//     {
//         if(nums[j]<key)
//         {
//             swap(nums[j], nums[i++]);
//         }
//     }
//     //i指向的元素肯定>=key
//     swap(nums[i], nums[high]);
//     return i;
// }

// //递归
// void quickSort(vector<int> &nums,int low,int high)
// {
//     if(low<high)
//     {
//         int mid = getMid(nums, low, high);
//         quickSort(nums, low, mid - 1);
//         quickSort(nums, mid + 1, high);
//     }
// }

int getMid(vector<int> &nums,int low,int high)
{
    int key = nums[high];  //选择最后一个元素作为标志
    int i = low;
    for (int j = low; j < high;j++)
    {
        if(nums[j]<key)
        {
            swap(nums[j], nums[i++]);
        }
    }
    swap(nums[i], nums[high]);
    return i;
}

void quickSort(vector<int> &nums,int low, int high)
{
    if(low<high)
    {
        int mid = getMid(nums, low, high);
        quickSort(nums, low, mid - 1);
        quickSort(nums, mid + 1, high);
    }
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
    vector<int> nums = {1, 6, 2, 3, 99, 7};
    quickSort(nums,0,6);
    print(nums);
}