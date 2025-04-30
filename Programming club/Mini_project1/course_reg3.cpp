#include<bits/stdc++.h>
using namespace std;


// Define a structure for a tree node
struct TreeNode
{
    string val;  // Value of the node
    char slot;//slot variable so that no course in the tree has scheduling conflicts
    vector<TreeNode*> children;  // Children of the node

    // Constructor
    TreeNode(string value,char s) : val(value), slot(s) {}

};

//function that calculates the distance between the root and the required node
int findNodeHeight(TreeNode* root,string target)
{
    if (root == nullptr)//edge case
    {
        return -1;
    }

    //maintaing a queue which helps us traverse through the tree
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
    while (!q.empty())
    {
        auto [current, level] = q.front();//obtaning a node and checking if it is the target
        q.pop();


        if (current->val == target)
        {
            return (level+1);
        }

        //if its not the target adding its children to the queue
        for (TreeNode* child : current->children)
        {
            q.push({child, level + 1});
        }
    }

    return -1; 
}
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
    //function that prints the students enrolled in a specific course
    void print()
    {
        string cid;
        cin>>cid;
        //checking if the course exits or not
        if(Courses[cid].co_name=="")
        {
            Courses.erase(cid);
            cout<<"Invalid Course "<<cid<<endl;
            return;
        }

        Course& c=Courses[cid];
        vector<pair<string, int>> sorted_en = c.en;
        //sorting it so i can print ids of students in order which they were enrolled
        sort(sorted_en.begin(), sorted_en.end(), [](auto& a, auto& b)
        {
            return a.second < b.second;
        });
        //printing the student ids
        cout << "Enrolled students in " << c.co_id << ":" << endl;
        for (const auto& student : sorted_en)
            cout << student.first << " ";
        cout << endl;
    }
    //func that drops a course which a student was enrolled in
    void drop()
    {
        string studid, courid;
        cin >> studid >> courid;
        //checking if the course and the student exists
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

        //checking if the student is enrolled in that course or not
        auto it = find_if(c.en.begin(), c.en.end(), [&studid](const pair<string, int>& p)
        {
            return p.first == studid;
        });

        //if he is not enrolled exiting the func
        if (it == c.en.end())
        {
            return;
        }

        //droping the course
        c.en.erase(it);
        c.curr_cnt--;
        s.enrolled.erase(c.co_id);
        s.occupied_slots.erase(c.slot);

        //adding the next student in the waitlist
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
    //func that creates a tree connecting all the prereqs to each other
    void minEligablePathlen()
    {

        string start,end;
        cin>>start>>end;
        Course& cs=Courses[start];
        Course& ct=Courses[end];
        queue<TreeNode*> q;//declares a queue to help with adding all the nodes
        TreeNode* root=new TreeNode(ct.co_id,ct.slot);//declaring the final course to reach to as the root
        TreeNode* current=root;
        q.push(root);
        if(ct.prereq.size()==0)//edge case if the final course does nto have any prereqs
        {
            cout<<"-1"<<endl;
            return;
        }

        //creating all the nodes
        while(!q.empty())
        {

            current=q.front();
            Course& curr=Courses[(q.front())->val];
            q.pop();
            for(auto itr=curr.prereq.begin();itr!=curr.prereq.end();itr++)
            {
                Course& on=Courses[itr->second];
                if(curr.slot!=on.slot)
                {
                    TreeNode* temp=new TreeNode(on.co_id,on.slot);
                    q.push(temp);
                    current->children.push_back(temp);
                }
                
            }

        }
        //calling the function which gives the distance between the initial and final course
        cout<<findNodeHeight(root,start)<<endl;
    }


};

int main()
{
    //handling all the queries
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
        if(input=="drop")
        {
            iitm.drop();
        }
        if(input=="minEligiblePathlen")
        {
            iitm.minEligablePathlen();
        }
    }
    return 0;
}