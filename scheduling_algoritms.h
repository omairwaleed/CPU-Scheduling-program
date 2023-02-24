#ifndef scheduling_algoritms_h
#define scheduling_algoritms_h
#include <vector>
#include <sstream>
using namespace std;

struct Process {
    char name;
    int arrival_time, process_time,current_priority,enterqueue;
    Process(char name , int arrival_time,int process_time );
};

void fcfs (vector<Process>processes ,int no_processes ,string action,int instant);
void SPN (vector<Process>processes ,int no_processes ,string action,int instant);
void roundrobbin (vector<Process>processes ,int no_processes ,string action,int instant,int q);
void print(vector<Process>processes,int no_processes,int instant,vector<char>running_processe,string schedule);
void SRT (vector<Process>processes,int no_processes,string action,int instant);
void HRRN (vector<Process>processes,int no_processes,string action,int instant);
void feedback_1(vector<Process>processes ,int no_processes ,string action,int instant);
void feedback_2i(vector<Process>processes ,int no_processes ,string action,int instant);
void print_stats(string schedule,vector<Process>processes,vector<int>finish,vector<int>turnaround,vector<float>norm_turn,float mean_turnaround,float mean_normturn,int no_processes);
void aging(vector<Process>processes ,int no_processes,int instant,int q);
void printaging(vector<Process>processes,int no_processes,int instant,vector<char>running_processe,string schedule);
#endif

