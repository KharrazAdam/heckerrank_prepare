#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
    public:
        virtual  void getdata() = 0;
        virtual  void putdata() = 0;
    
    protected :
        int age;
        std::string name;
        static int ids[2];
};

int Person::ids[2] = {0, 0};

class Professor : public Person {
    public:
        void getdata() {
            std::cin >> name >> age >> publications;
            cur_id = ++ids[1];
        };

        void putdata() {
            cout << name + ' '<< age << ' ' << publications << ' ' << cur_id << endl;
        }

    private:
        int publications;
        int cur_id;
};

class Student : public Person {
    public:
        void getdata() {
            cin >> this->name;
            cin >> this->age;
            for (size_t i = 0; i < 6; i++)
                cin >> this->marks[i];
            cur_id = ++ids[0];
        };

        void putdata() {
            cout << name + ' '<< age << ' ' << sumMarks() << ' ' << cur_id << endl;
        }

    private:
        int sumMarks() {
            int sum = 0;
            for (int i = 0; i < 6; i++)
                sum += marks[i];
            return sum;
        }
        int marks[6];
        int cur_id;
};

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){
        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
