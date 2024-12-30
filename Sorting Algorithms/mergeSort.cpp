#include<bits/stdc++.h>
using namespace std;

//Divide and Merge

//func that merges two arrays while sorting them
void merge(vector<int> &vec,int low,int mid,int high)
{
    vector<int> temp;
    int left=low;
    int right=mid+1;
    while(left<=mid && right<=high)
    {
        if(vec[left]<=vec[right])
        {
            temp.push_back(vec[left]);
            left++;
        }
        else
        {
            temp.push_back(vec[right]);
            right++;
        }

    }
    while(left<=mid)
    {
        temp.push_back(vec[left]);
        left++;
    }
    while(right<=high)
    {
        temp.push_back(vec[right]);
        right++;
    }
    for(int i=low;i<high;i++)
    {
        vec[i]=temp[i-low];
    }
}

//func that divides the arr, this is a recurssive function
void mergeSort(vector<int> &vec,int low,int high)
{
    if(low>=high) return;
    int mid=floor((low+high)/2);
    mergeSort(vec,low,mid);
    mergeSort(vec,mid+1,high);
    merge(vec,low,mid,high);
}


int main()
{
    //taking input
    int n;
    cin>>n;
    vector<int> vec;
    for(int i=0;i<n;i++)
    {
        int temp;
        cin>>temp;
        vec.push_back(temp);
    }

    mergeSort(vec,0,n-1);

    //displaying the results
    for(int i=0;i<n;i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
    return 0;
}