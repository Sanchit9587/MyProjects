#include<bits/stdc++.h>
using namespace std;

int times=0;
int print_num=1;//helps print the t variable on the screen

//just a func that helped me detect bugs
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

//func that returns true if the string contains a number false otherwise
bool is_number(string num)
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

//func that returns true if the string contains a variable
bool is_var(string var)
{
    if(var=="y")
    {
        return true;
    }
    return false;
}

//func that gives us the precedence of arithemtic operators 
int get_precendence(string op)
{
    if(op=="*" || op=="/") return 2;
    else if(op=="+" || op=="-") return 1;
    else return 0;
}

//func that displays error
void display_error()
{
    cout<<"The input is not a valid arithmetic statement thus terminating the program"<<endl;
}


//func that checks if the inputted arithmetic statement is correct or not
bool error_detection(string input)
{
    int n=input.length();
    //basically i am checking that a number is typed after a operator and there are no spaces in between the numbers like 1 2
    bool was_space=false;
    bool was_op=true;
    bool was_num=false;
    bool was_bracket_opening=false;
    bool was_bracket_closing=false;
    bool was_var=false;
    int start=input.find("=")+1;
    for(int i=start;i<n;i++)
    {
        string curr=string(1,input[i]);
        if(is_number(curr))
        {
            if(was_num && was_space) return true;
            if(was_bracket_closing) return true;
            was_num=true;
            was_space=false;
            was_op=false;
            was_bracket_opening=false;
            was_bracket_closing=false;
            was_var=false;
        }
        else if(is_op(curr))
        {
            if(was_op) return true;
            if(was_bracket_opening) return true;
            was_num=false;
            was_space=false;
            was_op=true;
            was_bracket_opening=false;
            was_bracket_closing=false;
            was_var=false;
        }
        else if(curr=="(")
        {
            if(was_num) return true;
            was_num=false;
            was_space=false;
            was_op=false;
            was_bracket_opening=true;
            was_bracket_closing=false;
            was_var=false;
        }   
        else if(curr==")")
        {
            if(was_op) return true;
            was_num=false;
            was_space=false;
            was_op=false;
            was_bracket_opening=false;
            was_bracket_closing=true;
            was_var=false;
        }
        else if(is_var(curr))
        {
            if(was_num || was_var) return true;
            if(was_bracket_closing) return true;
            was_num=false;
            was_space=false;
            was_op=false;
            was_bracket_opening=false;
            was_bracket_closing=false;
            was_var=true;
        }
        else
        {
            was_space=true;
        }
    }
    return false;
}

//this func helps removes 2 numbers and 1 operator from the stack on which i will operator
string steps(stack<string> &expression_st)
{
    string num1,op,num2;
    num2=expression_st.top();
    expression_st.pop();
    op=expression_st.top();
    expression_st.pop();
    num1=expression_st.top();
    expression_st.pop();
    string result=num1+op+num2;//returns a string after attaching the two numbers and the operator in bwt
    return result;
}

//this func helps in output 2 it basically checks if both the operands and numbers it operators on them giving the answer otherwise it returns the same string
string process(string result)
{
    string num1,op,num2;
    for(int i=0;i<result.length();i++) //separting the two numbers and the operator
    {
        string curr=string(1,result[i]);
        if(is_op(curr))
        {
            num1=result.substr(0,i);
            op=curr;
            num2=result.substr(i+1,result.length()-i-1);
        }
    }
    //checking if both operands are numbers and if true using the specific operator on them to get result
    if(is_number(num1) && is_number(num2))
    {
        if(op=="*")
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
       
    }
    return result;
}

//func that manages the stack for output 1
void stack_operations(vector<string> &expression)
{
    cout<<"Output 1"<<endl;
    stack<string> expression_st;
    int n=expression.size();
    string prev_op="0"; //helps with the logic that higher precedence operator chould be executed first
    for(int i=0;i<n;i++)
    {
        string curr=expression[i];
        if(is_number(curr) || is_var(curr)) //if it a number or variable directly push it to the stack
        {
            expression_st.push(curr);
        }
        else if(is_op(curr) && get_precendence(curr)>get_precendence(prev_op)) // if it is a operator of higher precedence than the previous one then directly push it on to the stack
        {
            expression_st.push(curr);
            prev_op=curr;
        }
        else if(is_op(curr) && get_precendence(curr)<=get_precendence(prev_op)) // if not performs operations until the stack is empty or a operator of lesser precedence than the current appears on top
        {
            while(get_precendence(curr)<=get_precendence(prev_op))
            {
                string result=steps(expression_st);
                if(!expression_st.empty()) prev_op=expression_st.top();
                else prev_op="0";
                cout<<"t"<<print_num<<"="<<result<<endl;
                expression_st.push("t"+to_string(print_num));
                print_num++;
            }
            expression_st.push(curr);
            prev_op=curr;
        }
        else if(curr=="(") //resets the precendence to zero so that only the operations inside the brackets are considered till we encounter a closing bracket
        {
            prev_op="0";
            expression_st.push(curr);
        }
        else if(curr==")") //performs all the operations till it encounters a opening bracket
        {
            bool terminate=false;
            string check="";
            while(!terminate)
            {
                string result=steps(expression_st);
                if(!expression_st.empty()) check=expression_st.top();
                else check="0";
                cout<<"t"<<print_num<<"="<<result<<endl;
                expression_st.push("t"+to_string(print_num));
                print_num++;
                terminate= (check=="(") ? true:false;
            }
            //this chunk of code pops the opening bracket which is in the stack and pushs the value obtained ater solving the brackets and also resets the prev_op variable to the last operator which was outside the bracket to perform the further operations
            string store=expression_st.top();
            expression_st.pop();
            expression_st.pop();
            if(!expression_st.empty()) prev_op=expression_st.top();
            else prev_op="0";
            expression_st.push(store);
        }
        
    }

    //this chunk performs operations until the stack is empty
    bool terminate=false;
    while(!terminate)
    {
        string result=steps(expression_st);
        if(expression_st.empty()) terminate=true;
        cout<<"t"<<print_num<<"="<<result<<endl;
        expression_st.push("t"+to_string(print_num));
        print_num++;
    }
    cout<<"x="<<expression_st.top()<<endl;
}

//func that manages the stack for output 2
//it is very similar to output 1 just using the process func before pushing on the stack
void stack_operations_output2(vector<string> &expression,bool printx)
{
    print_num=1;
    cout<<"Output 2"<<endl;
    stack<string> expression_st;
    int n=expression.size();
    string prev_op="0";
    for(int i=0;i<n;i++)
    {
        string curr=expression[i];
        if(is_number(curr) || is_var(curr))
        {
            expression_st.push(curr);
        }
        else if(is_op(curr) && get_precendence(curr)>get_precendence(prev_op))
        {
            expression_st.push(curr);
            prev_op=curr;
        }
        else if(is_op(curr) && get_precendence(curr)<=get_precendence(prev_op))
        {
            while(get_precendence(curr)<=get_precendence(prev_op))
            {
                string result=steps(expression_st);
                result=process(result);
                
                if(!expression_st.empty()) prev_op=expression_st.top();
                else prev_op="0";
                if(!is_number(result))
                {
                    cout<<"t"<<print_num<<"="<<result<<endl;
                    expression_st.push("t"+to_string(print_num));
                    print_num++;
                }
                else
                {
                    expression_st.push(result);
                }
                
            }
            expression_st.push(curr);
            prev_op=curr;
        }
        else if(curr=="(")
        {
            prev_op="0";
            expression_st.push(curr);
        }
        else if(curr==")")
        {
            bool terminate=false;
            string check="";
            while(!terminate)
            {
                string result=steps(expression_st);
                result=process(result);
                if(!expression_st.empty()) check=expression_st.top();
                else check="0";
                if(!is_number(result))
                {
                    cout<<"t"<<print_num<<"="<<result<<endl;
                    expression_st.push("t"+to_string(print_num));
                    print_num++;
                }
                else
                {
                    expression_st.push(result);
                }
                terminate= (check=="(") ? true:false;
            }
            string store=expression_st.top();
            expression_st.pop();
            expression_st.pop();
            if(!expression_st.empty()) prev_op=expression_st.top();
            else prev_op="0";
            expression_st.push(store);
        }
        
    }

    bool terminate=false;
    while(!terminate)
    {
        string result=steps(expression_st);
        result=process(result);
        if(expression_st.empty()) terminate=true;
        if(!is_number(result))
        {
            cout<<"t"<<print_num<<"="<<result<<endl;
            expression_st.push("t"+to_string(print_num));
            print_num++;
        }
        else
        {
            expression_st.push(result);
        }
    }
    //this if else if handles the print x part, if print x written we print the definite value of x
    if(printx)
    {
        
        cout<<"x="<<expression_st.top()<<endl;
    }
    else if(printx==false && (!is_number(expression_st.top()))) //print x is not written and x does not have a definite value so we print the variable t
    {
        int sub=0;
        if(print_num!=1) sub=1;
        cout<<"x=t"<<print_num-sub<<endl;
    }
    
}

//this func splits the input nicely into a vector for the stack operations and also calls the error detection func
void input_splitter(string input,bool printx)
{
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
        else if(!is_number(curr))
        {
            if(temp.length()>0)
            {
                expression.push_back(temp);
                temp="";
            }
            expression.push_back(curr);
        }
        else if(is_number(curr)) temp+=curr;
        if(i==n-1)
        {
            expression.push_back(temp);
            temp="";
        }
    }
    //print_vec(expression);
    stack_operations(expression);
    stack_operations_output2(expression,printx);
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
