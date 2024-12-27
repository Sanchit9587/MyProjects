#include<bits/stdc++.h>
using namespace std;

//func that calculates the prefix max
vector<int> prefixMax(int size,vector<int> vec)
{
    vector<int> prevec;
    prevec.push_back(vec[0]);
    for(int i=1;i<size;i++)
    {
        if(vec[i]>prevec[i-1])
        {
            prevec.push_back(vec[i]);
        }
        else
        {
            prevec.push_back(prevec[i-1]);
        }
    }
    return prevec;
}

//func that calculates the suffix max
vector<int> suffixMax(int size,vector<int> vec)
{
    vector<int> suffvec(size,0);
    suffvec[size-1]=vec[size-1];
    for(int i=size-2;i>=0;i--)
    {
        if(vec[i]>suffvec[i+1])
        {
            suffvec[i]=vec[i];
        }
        else
        {
            suffvec[i]=suffvec[i+1];
        }
    }
    return suffvec;
}

//func that traverses through the top of each building implementing the formula
//formula=min(leftMax,rightMax)-arr[i]
void solve(int size,vector<int> vec)
{
    vector<int> prevec=prefixMax(size,vec);
    vector<int> suffvec=suffixMax(size,vec);
    int total=0;
    for(int i=1;i<size-1;i++)
    {
        int current=vec[i];
        if(current<prevec[i] && current<suffvec[i])
        {
            total+=min(prevec[i],suffvec[i])-vec[i];
        }
    }
    cout<<total<<endl;
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
    //calling the solve func
    solve(n,vec);
    return 0;
}