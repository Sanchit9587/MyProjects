#include<bits/stdc++.h>
using namespace std;

//decides the pivot and puts it in its right spot and returns the index of that spot
int pivoted(vector<int> &vec,int low,int high)
{
    int pivot=(low+high)/2;
    int i=low;
    int j=high;
    while(i<j)
    {
        while(vec[i]<=vec[pivot] && i<=high)
        {
            i++;
        }

        while(vec[j]>vec[pivot] && j>=low)
        {
            j--;
        }
        
        if(i<j)
        {
            int temp=vec[i];
            vec[i]=vec[j];
            vec[j]=temp;
        }       
    }

    int temp=vec[j];
    vec[j]=vec[pivot];
    vec[pivot]=temp;

    return j;
}

//recurssive func that keeps on dividing the array into smaller portions
void quickSort(vector<int> &vec,int low,int high)
{
    if(low<high)
    {
        int partition=pivoted(vec,low,high);
        quickSort(vec,low,partition-1);
        quickSort(vec,partition+1,high);
    }
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

    //func call
    quickSort(vec,0,n-1);

    //displaying the sorted array
    for(int i=0;i<n;i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;

    return 0;
}