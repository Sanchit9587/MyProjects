#include<bits/stdc++.h>
using namespace std;

int times=0;
void print_vec(vector<string> &vec)
{
    for(int i=0;i<vec.size();i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

//function that tells us if any char is a arithemtic operator or not
bool is_op(string op)
{
    if(op=="*" || op=="/" || op=="+" || op=="-") return true;
    else return false;
}

bool isNumber(string num)
{
    int n=num.length();
    for(int i=0;i<n;i++)
    {
        if(!isdigit(num[i]))
        {
            return false;
        }
    }
    return true;
}

bool is_var(string var)
{
    if(!isNumber(var) && !is_op(var) && var!=" ")
    {
        return true;
    }
    return false;
}

string process(string num1,string num2, string op)
{
    string result;
    if(!isNumber(num1) || !isNumber(num2))
    {
        result=num1+op+num2;
    }
    else if(op=="*")
    {
        int a=stoi(num1)*stoi(num2);
        result=to_string(a);
    }
    else if(op=="/")
    {
        int a=stoi(num1)/stoi(num2);
        result=to_string(a);
    }
    else if(op=="+")
    {
        int a=stoi(num1)+stoi(num2);
        result=to_string(a);
    }
    else if(op=="-")
    {
        int a=stoi(num1)-stoi(num2);
        result=to_string(a);
    }
    return result;
}

//func that gives us the precedence of arithemtic operators 
int get_precendence(string op)
{
    if(op=="*" || op=="/") return 2;
    else if(op=="+" || op=="-") return 1;
    else return 0;
}

void display_error()
{
    cout<<"The input is not a valid arithmetic statement thus terminating the program"<<endl;
}
bool error_detection(string input)
{
    bool was_num=false;
    bool was_op=true;
    bool was_var=false;
    bool was_space=false;
    int start=input.find("=")+1;
    //cout<<start<<endl;
    int len=input.length();
    for(int i=start;i<len;i++)
    {
        string curr=string(1,input[i]);
        if(isNumber(curr))
        {   
            if(was_space && was_num)
            {
                return true;
            }
            if(was_op==false && was_num==false)
            {
                return true;
            }
            was_num=true;
            was_op=false;
            was_space=false;
            was_var=false;
        }
        else if(is_op(curr))
        {
            if((!was_num) && (!was_var))
            {
                return true;
            }
            was_op=true;
            was_num=false;
            was_space=false;
            was_var=false;
        }
        else if(is_var(curr))
        {
            if(!was_op)
            {
                return true;
            }
            was_var=true;
            was_num=false;
            was_op=false;
            was_space=false;
        }

        was_space= curr==" " ? true:false;
    }
    return false;
}


//func that helps us print a statement to the console and modify the stack accordingly 
string steps_output2(stack<string> &expression_st, int print_num)
{
    string to_push;
    string num1,num2,op;
    num2=expression_st.top();
    expression_st.pop();
    op=expression_st.top();
    expression_st.pop();
    num1=expression_st.top();
    expression_st.pop();
    string result=process(num1,num2,op);
    if(isNumber(num1) && isNumber(num2))
    {
        to_push=result;
        times++;
    }
    else
    {
        int t=print_num-times<=0 ? 1:print_num-times;
        to_push="t"+to_string(t);
        cout<<"t"<<t<<"="<<result<<endl;
    }
    return to_push;
}

//func that helps us print a statement to the console and modify the stack accordingly 
void steps(stack<string> &expression_st, int print_num)
{
    string num1,num2,op;
    num2=expression_st.top();
    expression_st.pop();
    op=expression_st.top();
    expression_st.pop();
    num1=expression_st.top();
    expression_st.pop();
    cout<<"t"<<print_num<<"="<<num1<<op<<num2<<endl;
}
//main func that maintains a stack which help us evaluate the order in which the expression should be carried out
void stack_operations(vector<string> expression,char variable,int num_op)
{
    cout<<"Output 1"<<endl;
    stack<string> expression_st;
    string prev_op; //this var stores the operator previous to the current one which helps in tracking precedence 
    int print_num=1; //helps in printing the t variable
    for(int i=0;i<expression.size();i++)
    {
        string curr=expression[i];

        if(!is_op(curr) || i==1) //if it is a number we directly push it onto the stack
        {
            expression_st.push(curr);
            if(is_op(curr)) prev_op=curr;
        }
        else if(get_precendence(curr)>get_precendence(prev_op)) //if the precendence of the current operator is more than the prev we push it onto the stack
        {
            expression_st.push(curr);
            prev_op=curr;
        }
        else
        {
            while((!expression_st.empty()) && get_precendence(curr)<=get_precendence(prev_op)) //we keep printing statements to execute until the curr operator has the highest priority
            {
                steps(expression_st,print_num);
                if(!expression_st.empty()) prev_op=expression_st.top();
                else prev_op="0";
                expression_st.push("t"+to_string(print_num));
                print_num++;
            }
            expression_st.push(curr);
            prev_op=curr;
        }
        
    }
    //when we have gone through the expression and still the stack if not empty
    while(print_num<=num_op)
    {
        steps(expression_st,print_num);
        expression_st.push("t"+to_string(print_num));
        print_num++;
    }
    cout<<variable<<"="<<"t"<<print_num-1<<endl;
}


//main func that maintains a stack which help us evaluate the order in which the expression should be carried out
void stack_operations_output2(vector<string> expression,char variable,int num_op,bool printx)
{
    cout<<"Output 2"<<endl;
    stack<string> expression_st;
    string prev_op; //this var stores the operator previous to the current one which helps in tracking precedence 
    int print_num=1; //helps in printing the t variable
    for(int i=0;i<expression.size();i++)
    {
        string curr=expression[i];

        if(!is_op(curr) || i==1) //if it is a number we directly push it onto the stack
        {
            expression_st.push(curr);
            if(is_op(curr)) prev_op=curr;
        }
        else if(get_precendence(curr)>get_precendence(prev_op)) //if the precendence of the current operator is more than the prev we push it onto the stack
        {
            expression_st.push(curr);
            prev_op=curr;
        }
        else
        {
            while((!expression_st.empty()) && get_precendence(curr)<=get_precendence(prev_op)) //we keep printing statements to execute until the curr operator has the highest priority
            {
                string to_push=steps_output2(expression_st,print_num);
                if(!expression_st.empty()) prev_op=expression_st.top();
                else prev_op="0";
                expression_st.push(to_push);
                print_num++;
            }
            expression_st.push(curr);
            prev_op=curr;
        }
        
    }
    //when we have gone through the expression and still the stack if not empty
    while(print_num<=num_op)
    {
        string to_push=steps_output2(expression_st,print_num);
        expression_st.push(to_push);
        print_num++;
    }
    if(times==print_num-1)
    {
        times--;
    }
    if(printx==true)
    {
        cout<<variable<<"="<<expression_st.top()<<endl;
    }
    else
    {
        cout<<variable<<"="<<"t"<<print_num-times-1<<endl;
    }
    
}

//func that takes the string input and nicely separates all the numbers and operators into a vector
void input_splitter(string input,bool printx)
{
    char variable='x';
    int n=input.length();
    vector<string> expression;
    int num_op=0;
    string temp;
    int start=input.find("=")+1;
    bool result=error_detection(input);

    if(result)
    {
        display_error();
        return;
    }

    if(start>n)
    {
        display_error();
        return;
    }
    for(int i=start;i<n;i++)
    {
        string curr=string(1,input[i]);
        if(curr==" ")
        {
            continue;
        }
        else if(is_op(curr))
        {
            if(temp.length()>0)
            {
                expression.push_back(temp);
                temp="";
            }
            expression.push_back(curr);
            num_op++;
        }
        else if(!isNumber(curr))
        {
            if(temp.length()>0)
            {
                expression.push_back(temp);
                temp="";
            }
            expression.push_back(curr);
        }
        else if(isNumber(curr)) temp+=curr;
        if(i==n-1)
        {
            expression.push_back(temp);
            temp="";
        }
    }
    //print_vec(expression);
    stack_operations(expression,variable,num_op);
    stack_operations_output2(expression,variable,num_op,printx);
}

int main()
{
    //taking input
    string input;
    string input2;
    bool printx=false;
    getline(cin,input);
    getline(cin,input2);
    if(input2=="print x")
    {
        printx=true;
    }
    input_splitter(input,printx);
    return 0;
}
