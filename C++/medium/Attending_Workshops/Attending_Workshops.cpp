#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops


typedef struct Workshops {
    public:
        int start_time;
        int end_time;
        int duration;
}   Workshops;


typedef struct Available_Workshops {
    public:
        int n;
        Workshops *Workshop;    
}   Available_Workshops;

Available_Workshops* initialize (int start_time[], int duration[], int n) {
    Available_Workshops*    ret;

    ret = new Available_Workshops;
    ret->n = n;
    ret->Workshop = new Workshops[n];
    for (size_t i = 0; i < n; i++)
    {
        ret->Workshop[i].duration = duration[i];
        ret->Workshop[i].start_time = start_time[i];
        ret->Workshop[i].end_time = duration[i] + start_time[i];
    }
    return  ret;
};

bool compare(Workshops a, Workshops b) {
    return a.end_time < b.end_time;
};

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    sort(ptr->Workshop, ptr->Workshop + ptr->n, compare);

    int ret = 0;
    int schh = 0;

    for (int i = 0; i < ptr->n; i++) {
        if (ptr->Workshop[i].start_time >= schh) {
            ret++;
            schh = ptr->Workshop[i].end_time;
        }
    }
    return ret;
};

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
