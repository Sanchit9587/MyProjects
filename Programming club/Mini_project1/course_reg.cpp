#include<bits/stdc++.h>
using namespace std;

struct Course
{
    public:
    string co_id;
    string co_name;
    int capacity;
    int curr_cnt;
    int credits;
    int no_prereq;
    map<string, string> prereq;
    map<string, string> en;
    char slot;
    Course()
    {
        curr_cnt=0;
    }
};  

struct Student
{
    public:
    string st_id;
    string st_name;
    int year;
    int co_comp;
    map<string,string> comp_id;
    map<string,string> enrolled;
    map<char,char> occupied_slots;
};

class Academic
{
    public:
    map<string,Student> Students;
    map<string,Course> Courses;
    char arr[8]={'A','B','C','D','E','F','G','H',};

    void add_student()
    {
        Student temp;
        cin>>temp.st_id>>temp.st_name>>temp.year>>temp.co_comp;
        for(int i=0;i<temp.co_comp;i++)
        {
            string place;
            cin>>place;
            temp.comp_id[place]=place;
        }
        Students[temp.st_id]=temp;
    }
    void add_course()
    {
        Course temp;
        cin>>temp.co_id>>temp.co_name>>temp.credits>>temp.capacity>>temp.slot>>temp.no_prereq;
        int cnt=0;
        for(int i=0;i<temp.no_prereq;i++)
        {
            string place;
            cin>>place;
            if(Courses[place].co_name=="")
            {
                cnt++;
            }
            temp.prereq[place]=place;
        }
        if(cnt==0)
        {
            Courses[temp.co_id]=temp;
        }
        else
        {
            return;
        }
    }
    void enroll()
    {
        string studid,courid;
        cin>>studid>>courid;

        if(Students[studid].st_name=="")
        {
            Students.erase(studid);
            return;
        }
        if(Courses[courid].co_name=="")
        {
            Courses.erase(courid);
            return;
        }
        Student& s=Students[studid];
        Course& c=Courses[courid];

        for(auto itr: c.prereq)
        {
            string to_find=s.comp_id[itr.second];
            if(to_find=="")
            {
                return;
            }
        }
        char a=c.slot;
        char itr1=s.occupied_slots[a];
        if(itr1==a)
        {
            return;
        }
        string itr2=s.enrolled[c.co_id];
        if(itr2==c.co_id)
        {
            return;
        }      
        if(c.curr_cnt==c.capacity)
        {
            return;
        }
       
        s.enrolled[c.co_id]=c.co_id;
        c.curr_cnt=c.curr_cnt+1;
        s.occupied_slots[c.slot]=c.slot;
        c.en[s.st_id]=s.st_id;

    }
    void print()
    {
        string cid;
        cin>>cid;

        if(Courses[cid].co_name=="")
        {
            Courses.erase(cid);
            cout<<"Invalid Course "<<cid<<endl;
            return;
        }
        Course& c=Courses[cid];
        cout<<"Enrolled students in "<<c.co_id<<":"<<endl;
        for(auto itr: c.en)
        {
            cout<<itr.first<<" ";
        }
        cout<<endl;
    }
    
};

int main()
{
    int q;
    cin>>q;
    Academic iitm;
    for(int i=0;i<q;i++)
    {
        string input;
        cin>>input;
        if(input=="add_student")
        {
            iitm.add_student();
        }
        if(input=="add_course")
        {
            iitm.add_course();
        }
        if(input=="enroll")
        {
            iitm.enroll();
        }
        if(input=="print")
        {
            iitm.print();
        }        
    }
    return 0;
}