#include<bits/stdc++.h>
using namespace std;

class String
{
    private:
    char* start;
    int size;
    public:

    //default
    String(char* input)
    {
        size=strlen(input);
        start=new char[size+1];
        memcpy(start,input,size);
        start[size]='\0';
        cout<<"Created"<<endl;
    }

    //Copy Constructor
    String(String& other)
    {
        size=other.size;
        start=new char[size+1];
        memcpy(start,other.start,size+1);
        cout<<"Copied"<<endl;
    }

    //Move Constructor
    String(String&& other)
    {
        size=other.size;
        start=other.start;
        other.start=nullptr;
        other.size=0;
        cout<<"Moved"<<endl;
    }

    //Move Asssignment
    String &operator=(String &other)
    {
        size=other.size;
        start=other.start;
        other.start=nullptr;
        other.size=0;
        cout<<"Move Assignement"<<endl;
        return *this;
    }

    //func that prints the char array which is on the heap
    void print()
    {
        for(int i=0;i<size;i++)
        {
            cout<<start[i];
        }
        cout<<endl;
    }

    //Destructor
    ~String()
    {
        delete[] start;
        cout<<"Destroyed"<<endl;
    }

};

class Entity
{
    public:
    Entity(String&& name): m_name(move(name))
    {
    }
    void printName()
    {
        m_name.print();
    }
    private:
    String m_name;
};

int main()
{
    //Example to show move operation
    Entity entity((char*)"Sanchit");
    entity.printName();


    String first((char*)"Sanchit");

    //Move Assignment
    String second((char*)"Atharva");
    second=first;
    
    second.print();
    first.print();
    return 0;
}