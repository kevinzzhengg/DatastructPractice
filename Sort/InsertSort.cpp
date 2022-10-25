#include<iostream>
using namespace std;

void PrintArray(int *arr, int length);
void InsertSort(int *arr, int length)
{
    int temp, loc;
    for (loc = 1; loc < length ; loc++)
    {
        temp = arr[loc];
        int i;
        for (i = loc - 1; i >= 0 ; i--)
        {
            if (arr[i] > temp)
            {
                arr[i+1] = arr[i];
                continue;
            }else{
                break;
            }
        }
        arr[i+1] = temp;
    }  
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
    InsertSort(array,array_len);
    PrintArray(array,array_len);
    return 0;
}

