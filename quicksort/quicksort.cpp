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


// int getMid(vector<int> &nums,int low,int high)
// {
//     int key = nums[high];  //选择最后一个元素作为标志
//     int i = low;
//     for (int j = low; j < high;j++)
//     {
//         if(nums[j]<key)
//         {
//             swap(nums[j], nums[i++]);
//         }
//     }
//     swap(nums[i], nums[high]);
//     return i;
// }

// void quickSort(vector<int> &nums,int low, int high)
// {
//     if(low<high)
//     {
//         int mid = getMid(nums, low, high);
//         quickSort(nums, low, mid - 1);
//         quickSort(nums, mid + 1, high);
//     }
// }

// int getMid(vector<int> &nums,int low,int high)
// {
//     int key = nums[high];
//     int i = low;
//     for (int j = low; j < high;++j)
//     {
//         if(nums[j]<key)//小于key 不是大于key
//         {
//             swap(nums[i++], nums[j]);
//         }
//     }
//     swap(nums[high], nums[i]);
//     return i;
// }

// void quickSort(vector<int> &nums,int low,int high)
// {
//     if(low<high)
//     {
//         int mid = getMid(nums, low, high);
//         quickSort(nums, low, mid - 1);
//         quickSort(nums, mid + 1, high);
//     }
// }

int getMid(vector<int>&nums,int left,int right)
{
    int key = nums[right];
    int i = left;
    for (int j = left; j < right;++j)
    {
        if(nums[j]<key)
        {
            swap(nums[j], nums[i++]);
        }
    }
    swap(nums[i], nums[right]);
    return i;
}

void quickSort(vector<int> &nums,int left,int right)
{
    if(left<right)
    {
        int mid = getMid(nums, left, right);
        quickSort(nums, left, mid - 1);
        quickSort(nums, mid + 1, right);
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
    vector<int> nums = {1, 6, 4, 3, 99, 222};
    quickSort(nums,0,6);
    print(nums);
    cout << sizeof(int) << endl;
}