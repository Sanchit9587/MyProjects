#include<bits/stdc++.h>
using namespace std;

//defining a Course datatype
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
    vector<pair<string,int>> en;
    int timestamp;
    queue<string> waitlist;
    char slot;
    //constructor initializes the current count of students to zero at time of course addition
    Course()
    {
        timestamp=0;
        curr_cnt=0;
    }
};  

//defining a Student datatype
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

//defining a class which facilitates the interaction of a Course and a Student
class Academic
{
    public:
    //defining a map which stores the Student datatype of all exisiting students
    map<string,Student> Students;
    //defining a map which stores the Course datatype of all exisiting courses
    map<string,Course> Courses;
    char arr[10]={'A','B','C','D','E','F','G','H','I','J'};

    //func to add a student to the database
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
    //func to add a course to the database
    void add_course()
    {
        Course temp;
        cin>>temp.co_id>>temp.co_name>>temp.credits>>temp.capacity>>temp.slot>>temp.no_prereq;
        int cnt=0;
        //checking prereqs
        for(int i=0;i<temp.no_prereq;i++)
        {
            string place;
            cin>>place;
            if(Courses[place].co_name=="" || place==temp.co_id)
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
    //func which enrolls a student in a course after checking all the criteria
    void enroll()
    {
        string studid,courid;
        cin>>studid>>courid;
        //checking if the student and the course exists or not
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
        //checking if the student as completed all the prereqs
        for(auto itr: c.prereq)
        {
            string to_find=s.comp_id[itr.second];
            if(to_find=="")
            {
                return;
            }
        }
        //checking if the student has the course's slot free
        char a=c.slot;
        char itr1=s.occupied_slots[a];
        if(itr1==a)
        {
            return;
        }
        //checking if the student is already enrolled in that course
        string itr2=s.enrolled[c.co_id];
        if(itr2==c.co_id)
        {
            return;
        }      
        //checking if capacity of the course is full or not if its full adding student to waitlist
        if(c.curr_cnt==c.capacity)
        {
            c.waitlist.push(s.st_id);
            return;
        }
       
        //after passing all checks student is enrolled in that course
        s.enrolled[c.co_id]=c.co_id;
        c.curr_cnt=c.curr_cnt+1;
        s.occupied_slots[c.slot]=c.slot;
        c.en.push_back({s.st_id,c.timestamp++});

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
        vector<pair<string, int>> sorted_en = c.en;

        sort(sorted_en.begin(), sorted_en.end(), [](auto& a, auto& b) {
            return a.second < b.second;
        });

        cout << "Enrolled students in " << c.co_id << ":" << endl;
        for (const auto& student : sorted_en)
            cout << student.first << " ";
        cout << endl;
    }
    void drop()
    {
        string studid, courid;
        cin >> studid >> courid;

        if (Students[studid].st_name == "")
        {
            Students.erase(studid);
            return;
        }
        if (Courses[courid].co_name == "")
        {
            Courses.erase(courid);
            return;
        }

        Student& s = Students[studid];
        Course& c = Courses[courid];


        auto it = find_if(c.en.begin(), c.en.end(), [&studid](const pair<string, int>& p)
        {
            return p.first == studid;
        });

    
        if (it == c.en.end())
        {
            return;
        }


        c.en.erase(it);
        c.curr_cnt--;
        s.enrolled.erase(c.co_id);
        s.occupied_slots.erase(c.slot);


        if (!c.waitlist.empty())
        {
            Student& s1 = Students[c.waitlist.front()];
            c.waitlist.pop();


            s1.enrolled[c.co_id] = c.co_id;
            c.curr_cnt++;
            s1.occupied_slots[c.slot] = c.slot;


            c.en.push_back({s1.st_id, c.timestamp++});
        }
}

};

int main()
{
    int q;
    cin>>q;
    Academic iitm;
    for(int i=0;i<q;i++)
    {
        //cout<<i+1<<endl;
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
        if(input=="drop")
        {
            iitm.drop();
        }
    }
    return 0;
}