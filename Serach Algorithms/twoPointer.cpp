
//Could have just used normal array but wanted to try out pointers and heap allocation

#include<bits/stdc++.h>
using namespace std;

int main()
{
    //Taking Input
    int n;
    cin>>n;
    int* firstp=new int[n];
    int* secondp=&firstp[n-1];
    for(int i=0;i<n;i++)
    {
        cin>>firstp[i];
    }
    int target;
    cin>>target;

    //running the loop until sum target is reached(sol exists) or both pointers collide(No sol)
    while(true)
    {
        int sum=(*firstp)+(*secondp);

        if(sum>target) secondp--; 
        else if(sum<target) firstp++;
        else //target hit
        {
            cout<<"Yes"<<endl;
            cout<<"("<<*firstp<<" "<<*secondp<<")"<<endl;
            break;
        }
        
        //if pointers collide
        if(firstp==secondp)
        {
            cout<<"No"<<endl;
            break;
        }

    }
    return 0;
}