#include<iostream>
#include<string>

using namespace std;

string getToken(istream& is){
        string s;
        is>>s;
        return s;
    }
    
bool isNumber(const string& s) {
    return s[0]>='0'&& s[0]<='9';
}

struct Node{
       virtual int result() const =0;
    };

struct NumberNode:Node{
    int value;
    NumberNode(int v):value(v){}
    virtual int result() const override{
        return value;
    }
};

struct Operation:Node{
    Node* left = nullptr;
    Node* right = nullptr;
};

struct Addition:Operation{
    virtual int result() const override{
        return left->result()+right->result();
    }
};

struct Substraction:Operation{
    virtual int result() const override{
        return left->result()-right->result();
    }
};

struct Multiplication:Operation{
    virtual int result() const override{
        return left->result()*right->result();
    }
};

Node* buildTree(istream& is){
        auto s = getToken(is);
        
        if(isNumber(s)){
            return new NumberNode(stoi(s));
        }

        Operation* op = nullptr;
        
        if(s[0]=='+'){
            op = new Addition();
        }
        else if(s[0]=='-'){
            op = new Substraction();
        }
        else if(s[0]=='*'){
            op = new Multiplication();
        }
        else{ 
            cout<<"Wrong token"<<endl;
            return 0;
        }
        op->left = buildTree(is);
        op->right = buildTree(is);
        return op;
    }
int main(){
    Node* root = buildTree(cin);
    cout<<root->result()<<endl;
}
