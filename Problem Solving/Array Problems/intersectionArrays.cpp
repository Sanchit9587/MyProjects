#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int m;
    cin>>m;
    int b[m];
    for(int i=0;i<m;i++){
        cin>>b[i];
    }

    int i=0;
    int j=0;
    int current=INT_MIN;
    int toInsert=INT_MIN;
    vector<int> intersection;
    while(i<n && j<m)
    {
        if(a[i]==b[j])
        {
            toInsert=a[i];
            i++;
            j++;
        }
        else if(a[i]<b[j])
        {
            i++;
        }
        else
        {
            j++;
        }

        if(toInsert!=current)
        {
            intersection.push_back(toInsert);
            current=toInsert;
        }
    }

    for(int t=0;t<intersection.size();t++)
    {
        cout<<intersection[t]<<" ";
    }
    return 0;
}