#include<vector>
#include<iostream>
using namespace std;


/*建堆*/
//下标为i的父节点(i-1)/2
//下标为i的左孩子i*2+1
//下标为i的右孩子i*2+2

// void heapget(vector<int> &nums,int n,int i)
// {
//     int max = i;
//     int lson = i * 2 + 1, rson = i * 2 + 2;
//     if(lson<n && nums[lson]>nums[max])
//         max = lson;
//     if(rson<n && nums[rson]>nums[max])
//         max = rson;
//     if(max!=i)
//     {
//         swap(nums[max], nums[i]);
//         heapget(nums, n, max);
//     }
// }

// /*排序*/
// //从最后一个节点的父节点开始建堆
// //倒叙遍历 每次交换最后一个与第一个
// void heapsort(vector<int> &nums,int n)
// {
//     int i;
//     //建堆从最后一个节点的父节点
//     for (int i = n / 2 - 1;i>=0;--i)
//     {
//         heapget(nums, n, i);
//     }
//     //交换
//     for (int i = n - 1; i >= 0;--i)
//     {
//         swap(nums[0], nums[i]);
//         heapget(nums, i, 0);
//     }
// }


// void buildHeap(vector<int>& nums,int n,int i)
// {
//     int max = i;
//     int lson = i * 2 + 1, rson = i * 2 + 2;

//     if(lson<n && nums[lson]>nums[max])
//         max = lson;
//     if(rson<n && nums[rson]>nums[max])
//         max = rson;
//     if (max != i)
//     {
//         swap(nums[i], nums[max]);
//         buildHeap(nums, n, max);
//     }
// }

// void heapsort(vector<int> &nums,int n)
// {
//     int i;
//     //从最后一个结点的父节点开始建立堆
//     for (int i = n / 2 - 1; i >= 0;--i)
//     {
//         buildHeap(nums, n, i);
//     }
//     for (int i = n - 1; i >= 0;--i)
//     {
//         swap(nums[0], nums[i]);
//         buildHeap(nums, i, 0);
//     }
// }

// void buildHeap(vector<int> &nums,int n,int i)
// {
//     int max = i;
//     int lson = i * 2 + 1, rson = i * 2 + 2;
//     if (lson < n && nums[lson] > nums[max])
//         max = lson;
//     if (rson < n && nums[rson] > nums[max])
//         max = rson;
//     if (max != i)
//     {
//         swap(nums[i], nums[max]);
//         buildHeap(nums, n, max);
//     }
// }

// void heapSort(vector<int> &nums,int n)
// {
//     for (int i = n / 2 - 1; i >= 0;--i)//从最后一个节点的父节点开始建堆
//     {
//         buildHeap(nums, n, i);
//     }
//     for (int i = n - 1; i >= 0;--i) //从最后一个开始交换
//     {
//         swap(nums[i], nums[0]);
//         buildHeap(nums, i, 0);
//     }
// }

void buildHeap(vector<int>&nums,int n,int i)
{
    int max = i;
    int lson = i * 2 + 1, rson = i * 2 + 2;
    if (lson < n && nums[lson] > nums[max])
        max = lson;
    if (rson < n && nums[rson] > nums[max])
        max = rson;
    if (max != i)
    {
        swap(nums[i], nums[max]);
        buildHeap(nums, n, max);
    }
}

void heapSort(vector<int> &nums,int n)
{
    for (int i = n / 2 - 1; i >= 0;--i)
    {
        buildHeap(nums, n, i);
    }
    for (int i = n - 1; i >= 0;--i)
    {
        swap(nums[i], nums[0]);
        buildHeap(nums, i, 0);
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
    vector<int> nums = {1, 6, 4, 3, 5, 88};
    heapSort(nums,6);
    print(nums);
}