#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int arr1[n];
    for(int i=0;i<n;i++){
        cin>>arr1[i];
    }
    int m;
    cin>>m;
    int arr2[m];
    for(int i=0;i<m;i++){
        cin>>arr2[i];
    }
    int i=0;
    int j=0;
    vector<int> vec;
   
    int current=0;
    int toInsert=0;
    while(i<n && j<m)
    {
        
        if(arr1[i]<arr2[j])
        {
            toInsert=arr1[i];
            i++;
        }
        else if(arr2[j]<arr1[i])
        {
            toInsert=arr2[j];
            j++;
        }
        else
        {
            toInsert=arr1[i];
            i++;
            j++;
        }

        if(toInsert!=current)
        {
            vec.push_back(toInsert);
            current=toInsert;
        }
    }

    while(j<m)
    {
        toInsert=arr2[j];
        j++;
        if(toInsert!=current)
        {
            vec.push_back(toInsert);
            current=toInsert;
        }
    }
    
    while(i<n)
    {
        toInsert=arr1[i];
        i++;
        if(toInsert!=current)
        {
            vec.push_back(toInsert);
            current=toInsert;
        }
    }

    for(int t=0;t<vec.size();t++)
    {
        cout<<vec[t]<<" ";
    }
    return 0;
}