#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int max=arr[0];
    int slarge=INT_MIN;
    for(int i=1;i<n;i++)
    {
        if(arr[i]>max)
        {
            slarge=max;
            max=arr[i];
        }
        else if(arr[i]<max && arr[i]>slarge)
        {
            slarge=arr[i];
        }
    }
    cout<<slarge;
    return 0;
}