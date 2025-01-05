#include<bits/stdc++.h>
using namespace std;

bool is_op(char character)
{
    if(character=='*' || character=='/' || character=='+' || character=='-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int get_precendence(char op)
{
    if(op=='*' || op=='/')
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

int get_result(int num1,int num2,char op)
{
    if(op=='*')
    {
        return num1*num2;
    }
    else if(op=='/')
    {
        return num1/num2;
    }
    else if(op=='+')
    {
        return num1+num2;
    }
    else
    {
        return num1-num2;
    }
}

void stack_operations(vector<int> nums, vector<char> ops)
{
    
    stack<int> numst;
    stack<char> opst;
    int i=0;
    int j=0;
    while(j<ops.size())
    {
        
        numst.push(nums[i]);
        char curr=ops[j];
        
        if(opst.empty() || get_precendence(curr)>get_precendence(opst.top()))
        {
            opst.push(curr);
        }
        else if(get_precendence(curr)<=get_precendence(opst.top()))
        {
            
            while(!opst.empty() && get_precendence(curr)<=get_precendence(opst.top()))
            {
                
                int num1,num2;
                num2=numst.top();
                numst.pop();
                num1=numst.top();
                numst.pop();
                char op=opst.top();
                opst.pop();
                numst.push(get_result(num1,num2,op));
                
            }
            opst.push(curr);
        }
        i++;
        j++;
    }
    
    numst.push(nums[nums.size()-1]);
    while(!opst.empty())
    {
        int num1,num2;
        char op;
        num2=numst.top();
        numst.pop();
        num1=numst.top();
        numst.pop();
        op=opst.top();
        opst.pop();
        numst.push(get_result(num1,num2,op));
    }
    cout<<numst.top();
    
}

void solve(string input)
{
    int n=input.length();
    vector<int> nums;
    vector<char> ops;
    string temp_str;
    int temp_num;

    for(int i=0;i<n;i++)
    {
        char current=input[i];
        if(is_op(current))
        {
            ops.push_back(current);
            temp_num=stoi(temp_str);
            temp_str="";
            nums.push_back(temp_num);
        }
        else
        {
            temp_str+=current;
        }

        if(i==n-1)
        {
            temp_num=stoi(temp_str);
            temp_str="";
            nums.push_back(temp_num);
        }
    }
    stack_operations(nums,ops);
}

int main()
{
    string input;
    getline(cin,input);
    solve(input);
    return 0;
}