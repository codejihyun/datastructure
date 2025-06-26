#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Student{
    long id;
    string name;
    int midScore;
    int finalScore;
    Student(long _id, string _name, float mScore, float fScore)//constructor
        :id(_id),name(_name),midScore(mScore),finalScore(fScore){}
    
    float totalScore() const{
        return (midScore+finalScore)*0.5;
    }
    friend ostream& operator << (ostream& os, const Student& s){
        os<<"["<<s.id<<","<<s.name<<","<<s.totalScore()<<"] ";
        return os;

    }
};

void print(const vector<Student> &v){
    for(const auto &s:v){
        cout<<s<<" ";
    }
    cout<<endl;
    
}

int main(){
    vector<Student> students;
    bool termination=false;
    while(!termination){
        int operationCode = 0;
        cout<<"Enter operation code: ";
        cin>>operationCode;

        switch(operationCode){
            case 1: {
                long id=0;
                string name=" ";
                float score1=0, score2=0;
                cin>>id>>name>>score1>>score2;
                auto it=find_if(students.begin(),students.end(),
                [id](const auto &a){return a.id==id;});//iterator가 가리키는a.id와 입력력받은 id 비교
                if(it!=students.end())
                    cout<<"The student already exists."<<endl;
                else
                    students.emplace_back(id,name,score1,score2);
            }break;//학생정보 입력받아서 뒤에 추가
            
            case 2:{
                long id=0;
                cin>>id;
                //erase->iterator받아야함
                auto it=find_if(students.begin(),students.end(),
                [id](const auto &a){return a.id==id;});
               if(it!=students.end())
                  students.erase(it);
               else
                cout<<"No such student"<<endl;
            }break;//id입력받고 해당 학생 지우기

            case 3:{
                long id=0;
                int score1=0;
                cin>>id>>score1;
                auto it=find_if(students.begin(),students.end(),
                [id](const auto &a){return a.id==id;});
                if(it!=students.end()){
                    it->midScore=score1;
                }
                else
                cout<<"No such student"<<endl;
            }break;//중간고사 성적적 바꾸기

            case 4:{
                long id=0;
                int score2=0;
                cin>>id>>score2;
                auto it=find_if(students.begin(),students.end(),
                [id](const auto &a){return a.id==id;});
                if(it!=students.end()){
                    it->finalScore=score2;
                }
                else
                cout<<"No such student"<<endl;
            }break;//기말고사 성적 바꾸기

            case 5:{
                sort(students.begin(),students.end(),
                [&](const auto &a,const auto &b) {return a.id<b.id;});
            }break;//학번순(오름차순)정렬

            case 6:{
                sort(students.begin(),students.end(),
                [&](const auto &a,const auto &b){return a.totalScore()>b.totalScore();});
            }break;//최종성적순(내림차순)정렬

            case 7:{
                string name=" ";
                cin>>name;
                for(auto &s:students){
                if(s.name==name)
                    cout<<s.id<<" ";
                else
                    cout<<" ";
                }
                cout<<endl;
            }break;//이름 입력받아 학번 출력(동명이인 있으면 여러명 학번 출력)

            case 8:{
                termination=true;
            }break;

            default:{
                cout<<"Wrong code"<<endl;
            }
        }
        print(students);//실행코드 입력받을때마다 결과 출력
    }
}