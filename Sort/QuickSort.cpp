#include<iostream>
using namespace std;

int Partition(int *arr, int low, int high);
void QuickSort(int *arr, int low, int high)
{
    if (low < high) {
        //the length of the sub-array is bigger than 1
        int pivotloc = Partition(arr,low,high);
        QuickSort(arr,low,pivotloc-1);
        QuickSort(arr,pivotloc+1,high);
    }
}

int Partition(int *arr, int low, int high)
{
    int tmp = arr[low];
    while (low < high) //check the low < high anytime.
    {
        while ((arr[high] >= tmp) && (low < high))
            high--;
        arr[low] = arr[high];

        while ((arr[low] <= tmp) && (low < high))
            low++;
        arr[high] = arr[low];   
    }
    arr[low] = tmp; 
    return low;
}

void PrintArray(int *arr, int length){
    for (int i = 0; i < length; i++)
        cout<<' '<<arr[i]<<' ';
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    int array[] = {12,33,4,27,98,9,9};
    int array_len = sizeof(array)/sizeof(*array);
    PrintArray(array,array_len);
    QuickSort(array,0,array_len-1);
    PrintArray(array,array_len);
    return 0;
}
