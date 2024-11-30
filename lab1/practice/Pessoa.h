#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
using namespace std;

class Pessoa{
    string name;
    string age;

    public:
    
        void setName(string name){
            this->name = name;
        }

        string getName(){
            return name;
        }

        void setAge(string age){
            this->age = age;
        }

        string getAge(){
            return age;
        }
        
};

#endif