#include<bits/stdc++.h>
using namespace std;
//func that reverses the array within the given indices
void reverse(int arr[],int start,int end)
{
    int last=end;
    int times=((end-start)/2)+1;
    for(int i=start;i<start+times;i++)
    {
        int temp=arr[i];
        arr[i]=arr[last];
        arr[last]=temp;
        last--;
    }
}

int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }

    int d;
    cin>>d;
    d%=7;

    //to left rotate by d you have to first reverse the first d element then the rest and then the whole array
    reverse(arr,0,d-1);
    reverse(arr,d,n-1);
    reverse(arr,0,n-1);

    //displaying the rotated array
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    return 0;
}