#include<bits/stdc++.h>

using namespace std;

int totalEarnings = 0;//global variable for storing Total Earnings over the program

class Class{//Base class for a Class
protected:
    int cls;
public:
    int getClass(){//get function of get the class value
        return this->cls;
    }
};

class Student:public Class{//Derived class Student which stores all info of a student

    string name;//student's name
    bool subject[3];//subject array
    double avgMarks;
    int totalDayTaught;
    int totalEarning;
    int factor;//extra variable for store what amount of subject a student be taught
    int examDays;//extra variable for store total exam days of a student

public:

    Student(){//default constructor;
    }
    Student(int,string,bool *,int f);//parameterized constructor for initializing the student class object


    //getter and setter functions for access the protected member variable
    string getName(){
        return this->name;
    }
    bool * getSubject(){
        return this->subject;
    }
    void setAvgMarks(double avgmrks){
        this->avgMarks=avgmrks;
    }
    double getAvgMarks(){
        return this->avgMarks;
    }
    void setTotalDayTaught(int d){
        this->totalDayTaught = d;
    }
    int getTotalDayTaught(){
        return this->totalDayTaught;
    }
    void setTotalEarning(int e){
        this->totalEarning = e;
    }
    int getTotalEarning(){
        return this->totalEarning;
    }
    int getFactor(){
        return this->factor;
    }
    void setFactor(int f){
        this->factor = f;
    }
    int getExamDays(){
        return this->examDays;
    }
    void setExamDays(int ex){
    this->examDays = ex;
    }


};

Student :: Student(int cls, string name,bool * ptr, int f){//Implementation of parameterized Student constructor
    cout<<"Initialized and Added a Student successfully."<<endl;
    this->cls = cls;
    this->name = name;
    for(int i=0; i<3; i++)
    {
        this->subject[i] = *(ptr+i);
    }
    this->avgMarks = 0;
    this->totalDayTaught = 0;
    this->totalEarning = 0;
    this->factor = f;
    this->examDays = 0;
}



vector<Student>studentList;//Global vector for store the students info as a list

void AddStudent(int cls){
    string name;
    bool arr[3];
    memset(arr,false,3);

    int factor=0;

    cout<<"Enter Name : ";
    cin>>name;
    cout<<"Enter Subject(s) Math, English, Bangla(0 as false & 1 as true): ";
    for(int i=0; i<3; i++)
    {
        cin>>arr[i];
        if(arr[i]==true)
            factor++;
    }
    studentList.push_back(Student(cls,name,arr,factor));//Initialize a student object and add them to the vector
}



void EditStudent()
{
    string name;
    int cls;
    cout<<"Enter student's class & name whose info you want to edit"<<endl;
    labelEdit: cout<<"Class : ";
    cin>>cls;
    cout<<"Name  : ";
    cin>>name;
    int n = studentList.size();
    bool flag = true;
    for(int i=0; i<n; i++)//Iterate through all over the List
    {
        Student &tem=studentList[i];
        if(tem.getClass()==cls && tem.getName()==name)//Checking the conditions
        {
            int day,mark;
            cout<<"Add day(usually 1) and Marks(-1, if exam not taken) : /n";//one day you may not take any exam only teach
            cout<<"Day  : ";
            cin>>day;
            cout<<"Mark : ";
            cin>>mark;

            //store the value of object in local variable
            int daysTaught = tem.getTotalDayTaught();
            int earnings = tem.getTotalEarning();
            int factor = tem.getFactor();
            double avgmarks = tem.getAvgMarks();
            int exmdays = tem.getExamDays();



            tem.setTotalDayTaught((daysTaught+ day));//Increasing daysTaught's value by adding day's value
            tem.setTotalEarning(( earnings+(day*factor) ));//increasing earnings's value by adding day*factor value
            totalEarnings += (day*factor);//Increasing total earning (global variable's) value

            if(mark!=-1)//if one day you taught and give marks
            {
                double totalMarks = (avgmarks*exmdays);
                totalMarks+=(double)mark;
                tem.setExamDays((exmdays+1));//exam days increases(needed for avg marks)
                tem.setAvgMarks((totalMarks/tem.getExamDays()));
            }
            cout<<"Edit Successfully."<<endl;
            flag = false;
            break;
        }
    }
    if(flag){
        cout<<"Invalid Class or Name. Please enter valid class and name."<<endl;
        goto labelEdit;
    }

}


void DeleteStudent(){
    int cls;
    string name;
    deletelabel:
    cout<<"Enter Class : ";
    cin>>cls;
    cout<<"Enter Name  : ";
    cin>>name;
    int n;
    bool flag = true;
    n=studentList.size();
    for(int i=0;i<n;i++){//iterate through the student list
        if(studentList[i].getClass() == cls && studentList[i].getName()==name){
            studentList.erase(studentList.begin() + i);
            flag = false;
            cout<<"Delete Successful."<<endl;
            break;
        }
    }
    if(flag){
        cout<<"No such Student exists. Please Enter valid class and student name"<<endl;
        goto deletelabel;
    }

}

string SubjectMerge(bool *p){//adding the subject(s) in a variable from a bool array
    string s="";
    for(int i=0; i<3; i++)
    {
        if(*(p+i)==1 && i==0)
        {
            s+="Math ";
        }
        else if(*(p+i)==1 && i==1)
        {
            s+="English ";
        }
        else if(*(p+i)==1 && i==2)
        {
            s+="Bangla ";
        }
    }
    return s;
}

void ListofStudent()
{
    int cls;
    string name;
    char ch;
    cout<<"What you want to choose: Class(press c) or Name(press n): ";
    labelCH: cin>>ch;
    if(ch=='c'||ch=='C')
    {
        cout<<"Enter a class to see students : ";
        cin>>cls;
        int n=studentList.size();
        int cnt=0;
        bool flag = true;
        for(int i=0; i<n; i++)
        {
            if(studentList[i].getClass() == cls)//checking validation through classes
            {
                cnt++;
                if(cnt==1){
                    cout<<setw(20)<<"Name"<<setw(25)<<"Subject(s)"<<setw(10)<<"Earnings"<<setw(10)<<"Average_Marks"<<setw(20)<<"Total_Taught"<<endl;
                }
                Student tem = studentList[i];
                string s = SubjectMerge(studentList[i].getSubject());
                cout<<setw(20)<<tem.getName()<<setw(25)<<s<<setw(10)<<tem.getTotalEarning()<<setw(10)<<tem.getAvgMarks()<<setw(20)<<tem.getTotalDayTaught()<<endl;
                flag = false;
            }
        }
        if(flag){
            cout<<"No student exists in class "<<cls<<endl;
        }
    }
    else if(ch=='n'||ch=='N')
    {
        cout<<"Enter the name of a student : ";
        cin>>name;
        int n=studentList.size();//determining the size of the student list
        bool flag = true;
        int cnt = 0;
        for(int i=0; i<n; i++)
        {
            if(studentList[i].getName()==name)
            {
                cnt++;
                if(cnt==1){
                    cout<<setw(5)<<"Class"<<setw(25)<<"Subject(s)"<<setw(20)<<"Average_Marks"<<setw(25)<<"Total_day_taught"<<setw(15)<<"Total_earnings"<<endl;
                }
                string subjt;
                Student tem = studentList[i];
                subjt = SubjectMerge(tem.getSubject());//get the subjects name in a string

                cout<<setw(5)<<tem.getClass()<<setw(25)<<subjt<<setw(20)<<tem.getAvgMarks()<<setw(25)<<tem.getTotalDayTaught()<<setw(15)<<tem.getTotalEarning()<<endl;
                flag = false;

            }
        }
        if(flag){
            cout<<"No student exist name as "<<name<<endl;
        }
    }
    else
    {
        cout<<"Invalid choice"<<endl;
        goto labelCH;
    }


}

void SeeOverall()
{
    int n = studentList.size();

    //initialize local variable for computing all info
    int totalDayTaught_allClasses=0;
    int totalDayTaught_class8=0,totalDayTaught_class9=0,totalDayTaught_class10=0;
    int indvEarning_class8=0,indvEarning_class9=0,indvEarning_class10=0;
    int indvEarning_math=0,indvEarning_english=0,indvEarning_bangla=0;
    double avgMarks_allStudent=0;

    for(int i=0; i<n; i++)//iterate through the student list to get the values
    {
        Student tem = studentList[i];
        totalDayTaught_allClasses += tem.getTotalDayTaught();
        avgMarks_allStudent += tem.getAvgMarks();
        if(tem.getClass()==8)//if class of a student is 8
        {
            totalDayTaught_class8 += tem.getTotalDayTaught();
            indvEarning_class8 += tem.getTotalEarning();
        }
        else if(tem.getClass()==9)//if class of a student is 9
        {
            totalDayTaught_class9 += tem.getTotalDayTaught();
            indvEarning_class9 += tem.getTotalEarning();
        }
        else if(tem.getClass()==10)//if class of a student is 10
        {
            totalDayTaught_class10 += tem.getTotalDayTaught();
            indvEarning_class10 += tem.getTotalEarning();
        }
        bool *p = tem.getSubject();//pointer type variable for store first element of subject array
        for(int j=0; j<3; j++)//checking individual earning for a student on subject array
        {
            if(*(p+j)==true&&j==0)
                indvEarning_math += (tem.getTotalEarning()/tem.getFactor());
            else if(*(p+j)==true && j==1)
                indvEarning_english += (tem.getTotalEarning()/tem.getFactor());
            else if(*(p+j)==true && j==2)
                indvEarning_bangla += (tem.getTotalEarning()/tem.getFactor());
        }

    }

    cout<<"Total days taught across all classes : "<<totalDayTaught_allClasses<<endl;
    cout<<endl;

    cout<<setw(50)<<"Individual days taught in each class"<<endl;
    cout<<setw(30)<<"Class_8"<<setw(10)<<"Class_9"<<setw(10)<<"Class_10"<<endl;
    cout<<setw(30)<<totalDayTaught_class8<<setw(10)<<totalDayTaught_class9<<setw(10)<<totalDayTaught_class10<<endl;

    cout<<endl;
    cout<<"Total Earnings : "<<totalEarnings<<endl;
    cout<<endl;

    cout<<setw(50)<<"Individual Earnings of each class"<<endl<<endl;
    cout<<setw(30)<<"Class_8"<<setw(10)<<"Class_9"<<setw(10)<<"Class_10"<<endl;
    cout<<setw(30)<<indvEarning_class8<<setw(10)<<indvEarning_class9<<setw(10)<<indvEarning_class10<<endl;
    cout<<endl;

    cout<<setw(50)<<"Individual Earnings of each subject"<<endl<<endl;
    cout<<setw(30)<<"Math"<<setw(10)<<"English"<<setw(10)<<"Bangla"<<endl;
    cout<<setw(30)<<indvEarning_math<<setw(10)<<indvEarning_english<<setw(10)<<indvEarning_bangla<<endl;
    cout<<endl;

    cout<<setw(50)<<"Average marks of all students"<<endl<<endl;

    cout<<setw(20)<<"Class"<<setw(20)<<"Name"<<setw(20)<<"Average_marks"<<endl;
    for(int i=0; i<n; i++)
    {
        Student tem = studentList[i];
        cout<<setw(20)<<tem.getClass()<<setw(20)<<tem.getName()<<setw(20)<<tem.getAvgMarks()<<endl;
    }


}

int main(){

    int test;
    cout<<"Press ....\n1 for AddStudent\n2 for Edit\n3 for Delete\n4 for getting individual list of Student\n5 for See overall Info\n0 for EXIT."<<endl;

    do{
        labelchoice: cout<<"Enter Case : ";
        cin>>test;
        switch (test)
        {
        case 1:
        {
                int cls;
                cout<<"Enter Class: ";
                cin>>cls;
                class_level:
                if(cls==8||cls ==9 || cls == 10)
                {
                    AddStudent(cls);
                }
                else
                {
                    cout<<"Invalid Class. Please enter valid class(8,9 or 10)"<<endl;
                    cout<<"Enter Class: ";
                    cin>>cls;
                    goto class_level;
                }
                break;
        }
        case 2:
            {
                EditStudent();
                break;
            }
        case 3:
            {
                DeleteStudent();
                break;
            }
        case 4:
            {
                ListofStudent();
                break;
            }
        case 5:
            {
                SeeOverall();
                break;
            }
        case 0:
            {
                return 0;
            }
        default:
            {
                cout<<"Invalid Choice. Please enter valid Choice code."<<endl;
                goto labelchoice;
            }
        }

    }
    while(test!=0);

    return 0;
}
