#include <bits/stdc++.h>
using namespace std;


int recurssiveBinarySearch(vector<int> &vec,int low,int high, int target)
{
    if(low>high)
    {
        return -1;
    }
    int mid=(low+high)/2;
    if(vec[mid]==target)
    {
        return mid;
    }
    else if(vec[mid]>target)
    {
        return recurssiveBinarySearch(vec,low,mid-1,target);
    }
    else
    {
        return recurssiveBinarySearch(vec,mid+1,high,target);
    }
}

void binarySearch(vector<int> &vec,int target)
{
    int low=0;
    int high=vec.size()-1;
    int mid=(low+high)/2;
    while(high>=low)
    {
        if(vec[mid]==target)
        {
            cout<<"Target Found"<<endl;
            cout<<mid;
            break;
        }
        else if(vec[mid]>target)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
        mid=(low+high)/2;
    }
    if(high<low)
    {
        cout<<"Target not in the array"<<endl;
    }
}
int main()
{
    vector<int> vec={3,4,6,7,9,12,16,17};
    binarySearch(vec,15);
    int result=recurssiveBinarySearch(vec,0,vec.size()-1,15);
    if(result==-1)
    {
        cout<<"Target not found"<<endl;
    }
    else
    {
        cout<<"Target Found at index: "<<result<<endl;
    }
    return 0;
}