#include<bits/stdc++.h>
using namespace std;

class String
{
    private:
    char* start;
    int size;
    public:

    //default constructor
    String(char* input)
    {
        size=strlen(input);
        start=new char[size+1];
        memcpy(start,input,size);
        start[size]='\0';
    }

    //copy constructor
    String(String &other)
    {
        size=other.size;
        start=new char(other.size+1);
        memcpy(start,other.start,size+1);
    }

    //method that prints the char array which is on the heap
    void print()
    {
        for(int i=0;i<size;i++)
        {
            cout<<start[i];
        }
        cout<<endl;
    }

    //returns a ref to any char in the array so it can be modified
    char &operator[](int index)
    {
        return start[index];
    }

    //handles copy assignment
    String &operator=(String &other)
    {
        size=other.size;
        start=new char(other.size+1);
        memcpy(start,other.start,size+1);
        return *this;
    }

    //destructor
    ~String()
    {
        delete[] start;

    }
};

int main()
{

    String first((char*)"Sanchit");

    //copy initialization
    String second=first;

    //copy assignment
    String third((char*)"Atharva");
    third=first;

    first.print();
    second.print();
    third.print();
    
    return 0;
}