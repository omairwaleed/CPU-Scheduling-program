#include "scheduling_algoritms.h"
#include<stdio.h>
#include<iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
//in aging policy process time is initial priority for simplicity and there is aditional attribute called current priority used in aging only
Process::Process(char name , int arrival_time,int process_time )
{
	this->name=name;
    this->arrival_time=arrival_time;
    this->process_time=process_time;
    this->current_priority=process_time;
}

struct SortByArrivalTime
{
  bool operator()(const Process& x, const Process& y) const
  {
    return x.arrival_time > y.arrival_time;
  }
};

struct SortByPriority
{
  bool operator()(const Process& x, const Process& y) const
  {
    if(x.current_priority == y.current_priority){
        return x.enterqueue  > y.enterqueue;
    }else{
        return x.current_priority < y.current_priority;
    }
    
  }
};

struct SortByProcessTime
{
  bool operator()(const Process& x, const Process& y) const
  {
    if(x.process_time == y.process_time){
        return x.arrival_time > y.arrival_time;
    }
    else{
        return x.process_time > y.process_time;
    }
    
  }
};

void print_stats(string schedule,vector<Process>processes,vector<int>finish,vector<int>turnaround,vector<float>norm_turn,float mean_turnaround,float mean_normturn,int no_processes){
    cout << schedule << endl;
    printf("Process    |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("  %c  |",processes[i].name);
        }
        printf("\n");

        printf("Arrival    |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%3d  |",processes[i].arrival_time);
        }
        printf("\n");

        printf("Service    |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%3d  |",processes[i].process_time);
        }
        printf(" Mean|\n");

        printf("Finish     |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%3d  |",finish[i]);
        }
        printf("-----|\n");
        
        printf("Turnaround |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%3d  |",turnaround[i]);
        }
        printf("%5.2f|\n",mean_turnaround);

        printf("NormTurn   |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%5.2f|",norm_turn[i]);
        }
        printf("%5.2f|\n",mean_normturn);
        printf("\n");



}
void fcfs (vector<Process>processes,int no_processes,string action,int instant){
    
     priority_queue<Process, vector<Process>, SortByArrivalTime> processes_queue;
     for(int i=0 ; i< no_processes; i++){
         processes_queue.push(processes[i]);
     }
   

    if ( action == "trace")
    {
        printf("FCFS  ");
        for (int i = 0; i < instant+1; i++)
        {
            if(i<10){
                printf("%d ",i);
            }
            else{
                printf("%d ",i%10);
            }
        }
        printf("\n");
        printf("------------------------------------------------\n");
        int running=-1;
        bool flag=false;
        while (!processes_queue.empty()) {
            
            Process p = processes_queue.top();
            processes_queue.pop();
            printf("%c     |",p.name);
            for (int i = 0; i < instant; i++)
            {   
                if(i == p.arrival_time){
                        flag=true;
                }
                if (flag && p.process_time>0 && i>running )
                {
                    printf("*|");
                    p.process_time--;
                    running++;
                }
                else if (flag && p.process_time>0 && i<=running )
                {
                    printf(".|");
        
                }else{
                    printf(" |");
                }
            }
            flag=false;
            printf(" \n");
         }
         printf("------------------------------------------------\n");
         printf("\n");
    }
    else{
        float sum_turnaround=0;
        float sum_normturn=0;
        float mean_turnaround;
        float mean_normturn;
        vector<int>waiting_time(no_processes);
        vector<int>turnaround_time(no_processes);
        vector<int>finish_time(no_processes);
        vector<float>norm_turn(no_processes);
        
        waiting_time[0]=0;
        for (int i = 1; i < no_processes; i++)
        {
            waiting_time[i] =  processes[i-1].process_time + waiting_time[i-1];
        }
        for (int i = 0; i < no_processes; i++)
        {
            finish_time[i] =  processes[i].process_time + waiting_time[i];
        }
        for (int i = 0; i < no_processes; i++)
        {
            turnaround_time[i] = finish_time[i]- processes[i].arrival_time ;
            sum_turnaround += turnaround_time[i];
        }
        mean_turnaround =sum_turnaround/no_processes;
        for (int i = 0; i < no_processes; i++)
        {
            norm_turn[i] = float(turnaround_time[i])/ float(processes[i].process_time) ;
            sum_normturn += norm_turn[i];
        }
        mean_normturn =sum_normturn/no_processes;
    
        printf("FCFS\n");
        printf("Process    |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("  %c  |",processes[i].name);
        }
        printf("\n");

        printf("Arrival    |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%3d  |",processes[i].arrival_time);
        }
        printf("\n");

        printf("Service    |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%3d  |",processes[i].process_time);
        }
        printf(" Mean|\n");

        printf("Finish     |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%3d  |",finish_time[i]);
        }
        printf("-----|\n");
        
        printf("Turnaround |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%3d  |",turnaround_time[i]);
        }
        printf("%5.2f|\n",mean_turnaround);

        printf("NormTurn   |");
        for (int i = 0; i < no_processes; i++)
        {
            printf("%5.2f|",norm_turn[i]);
        }
        printf("%5.2f|\n",mean_normturn);
        printf("\n");


    }
}
void print(vector<Process>processes,int no_processes,int instant,vector<char>running_processe,string schedule){
    cout << schedule;
    for (int i = 0; i < instant+1; i++)
    {
        if(i<10){
            printf("%d ",i);
        }
        else{
             printf("%d ",i%10);
        }
    }
    printf("\n");
    for (int i = 0; i <= 2*instant+7; i++)
    {
        printf("-");
    }
    
    printf("\n");
    for (int i = 0; i < no_processes; i++)
    {
        bool flag=false;
        bool continue_flag=false;
        int process_remaining_time=processes[i].process_time;
        printf("%c     |",processes[i].name);
        for (int j = 0; j < instant; j++){
            if (running_processe[j] == processes[i].name)
            {
                continue_flag=true;
                process_remaining_time--;
                flag=false;
                printf("*|");
            }
            
            else if(j == processes[i].arrival_time){
                
                flag=true;
                printf(".|");
            }
            else if(flag==true){
                printf(".|");
            }
            else if (continue_flag==true && process_remaining_time>0)
            {
                printf(".|");
            }
            else{
                printf(" |");
            }
            
        }
        printf(" \n");
    }
        for (int i = 0; i <= 2*instant+7; i++)
    {
        printf("-");
    }
    
    printf("\n");
    printf("\n");
}
void printaging(vector<Process>processes,int no_processes,int instant,vector<char>running_processe,string schedule){
    cout << schedule;
    for (int i = 0; i < instant+1; i++)
    {
        if(i<10){
            printf("%d ",i);
        }
        else{
             printf("%d ",i%10);
        }
    }
    printf("\n");
    for (int i = 0; i <= 2*instant+7; i++)
    {
        printf("-");
    }
    
    printf("\n");
    for (int i = 0; i < no_processes; i++)
    {
        bool flag=false;
        printf("%c     |",processes[i].name);
        for (int j = 0; j < instant; j++){
            if (running_processe[j] == processes[i].name)
            {
                flag=true;
                printf("*|");
            }
            
            else if(j == processes[i].arrival_time){
                
                flag=true;
                printf(".|");
            }
            else if(flag==true){
                printf(".|");
            }
            else{
                printf(" |");
            }
            
        }
        printf(" \n");
    }
        for (int i = 0; i <= 2*instant+7; i++)
    {
        printf("-");
    }
    
    printf("\n");
    printf("\n");
}
void SPN (vector<Process>processes,int no_processes,string action,int instant){
        vector<char>running_processe;
    
        vector<int>finish_time(no_processes);
        vector<Process> temp_processes;
        priority_queue<Process, vector<Process>, SortByProcessTime> ready_queue;

        bool flag =false;
        int temp_index=0;
        for (int j = 0; j < instant; j++)
        {
            for(int k=0 ; k< no_processes; k++ ){
                if((processes[k].arrival_time == j) && (flag==false)){
                    ready_queue.push(processes[k]);
                }
                else if((processes[k].arrival_time == j) && (flag==true)){
                    temp_processes.push_back(processes[k]);
                }
            }
            if(!ready_queue.empty()){   

                flag=true;
                Process p = ready_queue.top();
                running_processe.push_back(p.name);
                p.process_time--;
                ready_queue.pop();
                ready_queue.push(p);
                //printf("%d\n",p.process_time);
                if(p.process_time == 0){
                    flag=false;
                    ready_queue.pop();
                    int i;
                    for( i = temp_index ; i< temp_processes.size() ; i++){
                        ready_queue.push(temp_processes[i]);
                    } 
                    temp_index=i;  
                    
                    
                    for (int m = 0; m < no_processes; m++)
                    {
                        if (p.name == processes[m].name)
                        {
                            finish_time[m]=j+1;
                        }
                        
                    }
                }   
            }
            /*else{
                for(int i = 0 ; i< temp_processes.size() ; i++){
                    ready_queue.push(temp_processes[i]);
                }
                flag=true;
                Process p = ready_queue.top();
                running_processe.push_back(p.name);
                p.process_time--;
                ready_queue.pop();
                ready_queue.push(p);
                if(p.process_time == 0){
                    flag=false;
                    ready_queue.pop();
                    for (int m = 0; m < no_processes; m++)
                    {
                        if (p.name == processes[m].name)
                        {
                            finish_time[m]=j+1;
                        }
                        
                    }
                }

            }*/
        }
        /*for (int i = 0; i < running_processe.size(); i++)
        {
            printf("%c-",running_processe[i]);
        }*/
        if ( action == "trace"){
            print(processes,no_processes,instant,running_processe,"SPN   ");
        }
        else{
        
            vector<int>turnaroundv;
            vector<float>norm_turn;
            float mean_turnaround=0;
            float mean_normturn=0;
            for(int i=0; i<no_processes; i++)
            {
                turnaroundv.push_back(finish_time[i]-processes[i].arrival_time);
                float temp=(float)turnaroundv[i]/(float)processes[i].process_time;
                norm_turn.push_back(temp);
                mean_normturn+=temp;
                mean_turnaround+=turnaroundv[i];
            }
            mean_normturn/=no_processes;
            mean_turnaround/=no_processes;
            
            print_stats("SPN",processes,finish_time,turnaroundv,norm_turn,mean_turnaround,mean_normturn, no_processes);
        }
        
       
    
    
    
}
void roundrobbin (vector<Process>processes ,int no_processes ,string action,int instant,int q){

        vector<char>running_processe;
        vector<int>finish_time(no_processes);
        queue<Process> ready_queue;

        for(int i = 0 ;i < no_processes; i++)
        {
            if(processes[i].arrival_time == 0){
                ready_queue.push(processes[i]);
            }
        }
        int counter=q;
        for(int i = 0 ;i < instant; i++)
        {
            bool flag=false;
            bool process_flag=false;
            Process p = ready_queue.front();
            counter--;
            if(counter==0){
                ready_queue.pop();
                counter = q;
                process_flag=true;
                p.process_time--;
            }
            else{
                ready_queue.pop();
                p.process_time--;
                if(p.process_time != 0){
                    ready_queue.push(p);
                    for (int k = 0; k < ready_queue.size()-1; k++)
                    {
                        Process temp=ready_queue.front();
                        ready_queue.pop();
                        ready_queue.push(temp);
                    }    
                }
               // p.process_time++;
            }
            running_processe.push_back(p.name);
            
            if(p.process_time == 0)
            {   
                counter=q;
                flag = true;
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                
            }
            for(int j =0; j < no_processes; j++)
            {
                if(processes[j].arrival_time == i+1){
                    ready_queue.push(processes[j]);
                }
                    
            }
            if (flag == false && process_flag == true)
            {
                //printf(".%d.",p.process_time);
                ready_queue.push(p);
            }
            
            
        }
        /*for (int i = 0; i < running_processe.size(); i++)
        {
            printf("%c-",running_processe[i]);
        }*/

        if (action== "trace")
        {
            char character=char(q+48);
            char x[]={'R','R','-',character,' ',' ','\0'};
            string schedule = x;
            print(processes,no_processes,instant,running_processe,schedule);
        }else
        {
            vector<int>turnaroundv;
            vector<float>norm_turn;
            float mean_turnaround=0;
            float mean_normturn=0;
            for(int i=0; i<no_processes; i++)
            {
                turnaroundv.push_back(finish_time[i]-processes[i].arrival_time);
                float temp=(float)turnaroundv[i]/(float)processes[i].process_time;
                norm_turn.push_back(temp);
                mean_normturn+=temp;
                mean_turnaround+=turnaroundv[i];
            }
            mean_normturn/=no_processes;
            mean_turnaround/=no_processes;
            char character=char(q+48);
            char x[]={'R','R','-',character,'\0'};
            string schedule = x;
            print_stats(schedule,processes,finish_time,turnaroundv,norm_turn,mean_turnaround,mean_normturn, no_processes);
        }
        
        
        
        
    
}
void SRT (vector<Process>processes,int no_processes,string action,int instant){
    vector<char>running_processe;
    if ( action == "trace"){
        
        
        priority_queue<Process, vector<Process>, SortByProcessTime> ready_queue;
             
        for (int j = 0; j < instant; j++)
        {
            for(int k=0 ; k< no_processes; k++ ){
                if((processes[k].arrival_time == j) ){
                    ready_queue.push(processes[k]);
                }
            }
               
            Process p = ready_queue.top();
            running_processe.push_back(p.name);
            p.process_time--;
            if(p.process_time == 0){
                ready_queue.pop();
            }
            else{
                ready_queue.pop();
                ready_queue.push(p);
            }   
            

        }
        /*for (int i = 0; i < running_processe.size(); i++)
        {
            printf("%c-",running_processe[i]);
        }*/
        
        print(processes,no_processes,instant,running_processe,"SRT   ");
       
    }
    else{
        int a[no_processes],s[10],x[no_processes];
        int turnaround[no_processes],finish[no_processes];
        int i,j,smallest,count=0,time,n;
        double end;

        n=no_processes;
        for(i=0; i<n; i++)
        {
            a[i]=processes[i].arrival_time;
        }
        for(i=0; i<n; i++)
        {
            s[i]=processes[i].process_time;;
        }
        for(i=0; i<n; i++)
            x[i]=s[i];

        s[9]=9999;
        for(time=0; count!=n; time++)
        {
            smallest=9;
            for(i=0; i<n; i++)
            {
                if(a[i]<=time && s[i]<s[smallest] && s[i]>0 )
                    smallest=i;
            }
            s[smallest]--;

            if(s[smallest]==0)
            {
                count++;
                end=time+1;
                finish[smallest] = end;
                turnaround[smallest] = end - a[smallest];
            }
        }
        vector<int>turnaroundv;
        vector<int>finishv;
        vector<float>norm_turn;
        float mean_turnaround=0;
        float mean_normturn=0;
        for(i=0; i<n; i++)
        {
            turnaroundv.push_back(turnaround[i]);
            finishv.push_back(finish[i]);
            float temp=(float)turnaround[i]/(float)processes[i].process_time;
            norm_turn.push_back(temp);
            mean_normturn+=temp;
            mean_turnaround+=turnaround[i];
        }
        mean_normturn/=n;
        mean_turnaround/=n;
        print_stats("SRT",processes,finishv,turnaroundv,norm_turn,mean_turnaround,mean_normturn, no_processes);
        

    }
}
void HRRN (vector<Process>processes,int no_processes,string action,int instant){
 
        struct Process out('?',0,0);
        vector<int>finish_time(no_processes);
        vector<char>running_processe;
        vector<Process> ready;
        int finish_flag =1;
        queue<Process> temp1;
        int index;
        

        for (int i = 0; i < instant; i++)
        {
            for(int k=0 ; k< no_processes; k++ ){
                if((processes[k].arrival_time == i) ){
                    ready.push_back(processes[k]);
                }
            } 
            if(finish_flag==1){
                finish_flag=0;
                vector<float>ratio;
                for (int j = 0; j < ready.size(); j++)
                {
                    if (ready[j].name!='?')
                    {
                         float waiting_time = i-ready[j].arrival_time;
                         float temp = (waiting_time+ready[j].process_time)/ready[j].process_time;
                         ratio.push_back(temp);
                        
                    }
                    else{
                        ratio.push_back(0);
                    }
                    
                   
                }
               
                float max=ratio[0];
                for (int j = 0; j < ratio.size(); j++)
                {
                    if (ratio[j]>=max)
                    {
                        index=j;
                        max=ratio[j];   
                    }
                }

                
                running_processe.push_back(ready[index].name);
                ready[index].process_time--;
                if (ready[index].process_time==0)
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (ready[index].name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                } 
                finish_flag=1;
                ready[index]=out;
                }
                else{
                temp1.push(ready[index]);
                }
                
            }
            else{
                Process p =temp1.front();
                temp1.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                if (p.process_time==0){
                    finish_flag=1;
                    ready[index]=out;

                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }
                else{
                    temp1.push(p);
                }
            }
        }
        /*for (int i = 0; i < running_processe.size(); i++)
        {
            printf("%c-",running_processe[i]);
        }*/
        if ( action == "trace"){
        print(processes,no_processes,instant,running_processe,"HRRN  ");
        }
        else{
            vector<int>turnaroundv;
            vector<float>norm_turn;
            float mean_turnaround=0;
            float mean_normturn=0;
            for(int i=0; i<no_processes; i++)
            {
                turnaroundv.push_back(finish_time[i]-processes[i].arrival_time);
                float temp=(float)turnaroundv[i]/(float)processes[i].process_time;
                norm_turn.push_back(temp);
                mean_normturn+=temp;
                mean_turnaround+=turnaroundv[i];
            }
            mean_normturn/=no_processes;
            mean_turnaround/=no_processes;
            
            print_stats("HRRN",processes,finish_time,turnaroundv,norm_turn,mean_turnaround,mean_normturn, no_processes);          
            
        }
   
    }
    
void feedback_1(vector<Process>processes ,int no_processes ,string action,int instant){

        vector<char>running_processe;
        vector<int>finish_time(no_processes);
        queue<Process> queue_0;
        queue<Process> queue_1;
        queue<Process> queue_2;
        queue<Process> queue_3;
        queue<Process> queue_4;
        queue<Process> queue_5;
        queue<Process> queue_6;
        queue<Process> queue_7;
        queue<Process> queue_8;
        queue<Process> queue_9;
        for(int i = 0 ;i < no_processes; i++)
        {
            if(processes[i].arrival_time == 0){
                queue_0.push(processes[i]);
            }
        }
        for(int i = 0 ;i < instant; i++)
        {   
            
            if(queue_0.size()>0){
                Process p=queue_0.front();
                queue_0.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }

                if (p.process_time!=0 && queue_0.empty() && queue_1.empty() && queue_2.empty() && queue_3.empty()&& queue_4.empty() && queue_5.empty()&& queue_6.empty() && queue_7.empty() &&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_0.push(p);
                }
                
                else if (p.process_time!=0)
                {
                   queue_1.push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }
                
                
            }
            else if (queue_1.size()>0  )
            {
                Process p=queue_1.front();
                queue_1.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }                
                if (p.process_time!=0 && queue_0.empty()&& queue_1.empty() && queue_2.empty() && queue_3.empty()&& queue_4.empty() && queue_5.empty()&& queue_6.empty() && queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_1.push(p);
                }                
                else if (p.process_time!=0)
                {
                   queue_2.push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }
                
            }
            else if (queue_2.size()>0 )
            {
               
                Process p=queue_2.front();
                queue_2.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;

                        
                    }
                }                
                if (p.process_time!=0 && queue_0.empty() && queue_1.empty()&& queue_2.empty()  && queue_3.empty()&& queue_4.empty() && queue_5.empty()&& queue_6.empty() && queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_2.push(p);
                }                 
                else if (p.process_time!=0)
                {
                 
                   queue_3.push(p);
    
                   
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }                
            }
            else if (queue_3.size()>0  )
            {
                
                Process p=queue_3.front();
                queue_3.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;

                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }                
                if (p.process_time!=0 && queue_0.empty() && queue_1.empty() && queue_2.empty()&& queue_3.empty()&& queue_4.empty() && queue_5.empty()&& queue_6.empty() && queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_3.push(p);
                }         

                else if (p.process_time!=0)
                {
                   queue_4.push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }                
            }
            else if (queue_4.size()>0 )
            {
                
                Process p=queue_4.front();
                queue_4.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }                
                if (p.process_time!=0 && queue_0.empty() && queue_1.empty() && queue_2.empty()&& queue_3.empty()&& queue_4.empty() && queue_5.empty()&& queue_6.empty() && queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_4.push(p);
                }         

                else if (p.process_time!=0)
                {
                   queue_5 .push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }                
            }
            else if (queue_5.size()>0 )
            {
                
                Process p=queue_5.front();
                queue_5.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }                
                if (p.process_time!=0 && queue_0.empty() && queue_1.empty() && queue_2.empty()&& queue_3.empty() && queue_4.empty()&& queue_5.empty()&& queue_6.empty() && queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_5.push(p);
                }                   
                else if (p.process_time!=0)
                {
                   queue_6 .push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }                
            }
            else if (queue_6.size()>0 )
            {
                
                Process p=queue_6.front();
                queue_6.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }                
                if (p.process_time!=0 && queue_0.empty() && queue_1.empty() && queue_2.empty()&& queue_3.empty() && queue_4.empty()&& queue_5.empty()&& queue_6.empty() && queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_6.push(p);
                }                   
                else if (p.process_time!=0)
                {
                   queue_7 .push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }                
            }
            else if (queue_7.size()>0 )
            {
                
                Process p=queue_7.front();
                queue_7.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }                
                if (p.process_time!=0 && queue_0.empty() && queue_1.empty() && queue_2.empty()&& queue_3.empty() && queue_4.empty()&& queue_5.empty() && queue_6.empty()&& queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_7.push(p);
                }                  
                else if (p.process_time!=0)
                {
                   queue_8 .push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }                
            }
            else if (queue_8.size()>0 )
            {
                
                Process p=queue_8.front();
                queue_8.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }                
                if (p.process_time!=0 && queue_0.empty() && queue_1.empty() && queue_2.empty()&& queue_3.empty() && queue_4.empty()&& queue_5.empty() && queue_6.empty()&& queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_8.push(p);
                }                  
                else if (p.process_time!=0)
                {
                   queue_9 .push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }                
            }  
            else if (queue_9.size()>0 )
            {
                
                Process p=queue_9.front();
                queue_9.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }                
                if (p.process_time!=0 && queue_0.empty() && queue_1.empty() && queue_2.empty()&& queue_3.empty() && queue_4.empty()&& queue_5.empty() && queue_6.empty()&& queue_7.empty()&&queue_8.empty()&&queue_9.empty()&& flag==false)
                {
                   queue_9.push(p);
                }                  
                else if (p.process_time!=0)
                {
                   queue_0 .push(p);
                }
                else
                {
                for (int m = 0; m < no_processes; m++)
                {
                    if (p.name == processes[m].name)
                    {
                        finish_time[m]=i+1;
                    }
                    
                }
                }                
            }              

            for(int j =0; j < no_processes; j++)
            {
                if(processes[j].arrival_time == i+1){
                    queue_0.push(processes[j]);
                }
                 
            }
            /*printf("instant:%d\n",i);
            printf("queue0\n");
            printf("%ld\n",queue_0.size());
            printf("queue1\n");
            printf("%ld\n",queue_1.size());
            printf("queue2\n");
            printf("%ld\n",queue_2.size());
            printf("queue3\n");
            printf("%ld\n",queue_3.size());
            printf("queue4\n");
            printf("%ld\n",queue_4.size());
            printf("------------\n");*/
            
        }
	     

    /*for (int i = 0; i < running_processe.size(); i++)
        {
            printf("%c-",running_processe[i]);
        }*/
        if ( action == "trace"){
        print(processes,no_processes,instant,running_processe,"FB-1  ");
        }
        else
        {
            vector<int>turnaroundv;
            vector<float>norm_turn;
            float mean_turnaround=0;
            float mean_normturn=0;
            for(int i=0; i<no_processes; i++)
            {
                turnaroundv.push_back(finish_time[i]-processes[i].arrival_time);
                float temp=(float)turnaroundv[i]/(float)processes[i].process_time;
                norm_turn.push_back(temp);
                mean_normturn+=temp;
                mean_turnaround+=turnaroundv[i];
            }
            mean_normturn/=no_processes;
            mean_turnaround/=no_processes;
            
            print_stats("FB-1",processes,finish_time,turnaroundv,norm_turn,mean_turnaround,mean_normturn, no_processes);          

            
        }
        


}

void feedback_2i(vector<Process>processes ,int no_processes ,string action,int instant){
    
        vector<char>running_processe;
        vector<int>finish_time(no_processes);
        queue<Process> queue_0;
        queue<Process> queue_1;
        queue<Process> queue_2;
        queue<Process> queue_3;
        queue<Process> queue_4;
        int q_1=2;
        int q_2=4;
        int q_3=8;
        int q_4=16;
        bool flag_0=true;
        bool flag_1=true;
        bool flag_2=true;
        bool flag_3=true;
        bool flag_4=true;
        int x=q_1;
        int y=q_2;
        int z=q_3;
        int l=q_4;

        for(int i = 0 ;i < no_processes; i++)
        {
            if(processes[i].arrival_time == 0){
                queue_0.push(processes[i]);
            }
        }
        for(int i = 0 ;i < instant; i++)
        {   
            
            if(queue_0.size()>0 && flag_0 ==true){
                
                
                Process p=queue_0.front();
                queue_0.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                bool flag=false;
                for(int j =0; j < no_processes; j++)
                {
                    if(processes[j].arrival_time == i+1){
                        flag=true;
                    }
                }

                if (p.process_time!=0 && queue_1.empty() && queue_2.empty() && queue_3.empty()&& queue_4.empty() && flag==false)
                {
                   queue_0.push(p);
                }
                
                else if (p.process_time!=0)
                {
                   queue_1.push(p);
                }
                else
                {
                    for (int m = 0; m < no_processes; m++)
                    {
                        if (p.name == processes[m].name)
                        {
                            finish_time[m]=i+1;
                        }
                        
                    }
                }
                
                
            }
            else if (queue_1.size()>0 && flag_1 ==true )
            {
                

                Process p=queue_1.front();
                queue_1.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                x--;  
                
                
                if (p.process_time!=0 && x==0)
                { 
                   x=q_1; 
                   queue_2.push(p);
                    flag_0=true;
                    flag_2=true;
                    flag_3=true;
                    flag_4=true;
                
                }
                else if (p.process_time!=0)
                {
                    queue_1.push(p);
                    for (int j = 0; j < queue_1.size()-1; j++)
                    {
                        Process temp= queue_1.front();
                        queue_1.pop();
                        queue_1.push(temp);
                        flag_0=false;
                        flag_2=false;
                        flag_3=false;
                        flag_4=false;
                    }
                    
                }
                else if (p.process_time==0)
                {
                    x=q_1;
                    for (int m = 0; m < no_processes; m++)
                    {
                        if (p.name == processes[m].name)
                        {
                            finish_time[m]=i+1;
                        }
                        
                    }

                }
                
                
            }
            else if (queue_2.size()>0 && flag_2 ==true)
            {
               
                

                Process p=queue_2.front();
                queue_2.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                y--;

                if (p.process_time!=0 && y==0)
                { 
                   y=q_2; 
                   queue_3.push(p);
                    flag_0=true;
                    flag_1=true;
                    flag_3=true;
                    flag_4=true;
                }
                else if (p.process_time!=0)
                {
                    queue_2.push(p);
                    for (int j = 0; j < queue_2.size()-1; j++)
                    {
                        Process temp= queue_2.front();
                        queue_2.pop();
                        queue_2.push(temp);
                        flag_0=false;
                        flag_1=false;
                        flag_3=false;
                        flag_4=false;
                    }
                    
                }
                else if (p.process_time==0)
                {
                    y=q_2;
                    for (int m = 0; m < no_processes; m++)
                    {
                        if (p.name == processes[m].name)
                        {
                            finish_time[m]=i+1;
                        }
                        
                    }

                }
            }
            else if (queue_3.size()>0  && flag_3 ==true)
            {
                
                

                Process p=queue_3.front();
                queue_3.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                z--;

                if (p.process_time!=0 && z==0)
                { 
                   z=q_3; 
                   queue_4.push(p);
                    flag_0=true;
                    flag_2=true;
                    flag_1=true;
                    flag_4=true;
                }
                else if (p.process_time!=0)
                {
                    queue_3.push(p);
                    for (int j = 0; j < queue_3.size()-1; j++)
                    {
                        Process temp= queue_3.front();
                        queue_3.pop();
                        queue_3.push(temp);
                        flag_0=false;
                        flag_2=false;
                        flag_1=false;
                        flag_4=false;
                    }
                    
                }
                else if (p.process_time==0)
                {
                    z=q_3;
                    for (int m = 0; m < no_processes; m++)
                    {
                        if (p.name == processes[m].name)
                        {
                            finish_time[m]=i+1;
                        }
                        
                    }

                }
            }
            else if (queue_4.size()>0 && flag_4 ==true)
            {
                
                

                Process p=queue_4.front();
                queue_4.pop();
                running_processe.push_back(p.name);
                p.process_time--;
                l--;

                if (p.process_time!=0 && l==0)
                { 
                   l=q_4; 
                   queue_0.push(p);
                    flag_0=true;
                    flag_2=true;
                    flag_3=true;
                    flag_1=true;
                }
                else if (p.process_time!=0)
                {
                    queue_4.push(p);
                    for (int j = 0; j < queue_4.size()-1; j++)
                    {
                        Process temp= queue_4.front();
                        queue_4.pop();
                        queue_4.push(temp);
                        flag_0=false;
                        flag_2=false;
                        flag_3=false;
                        flag_1=false;
                    }
                    
                }
                else if (p.process_time==0)
                {
                    l=q_4;
                    for (int m = 0; m < no_processes; m++)
                    {
                        if (p.name == processes[m].name)
                        {
                            finish_time[m]=i+1;
                        }
                        
                    }

                }
            }
            for(int j =0; j < no_processes; j++)
            {
                if(processes[j].arrival_time == i+1){
                    queue_0.push(processes[j]);
                }
                 
            }
            
       }
	     

    /*for (int i = 0; i < running_processe.size(); i++)
        {
            printf("%c-",running_processe[i]);
        }*/
        if ( action == "trace"){
        
            print(processes,no_processes,instant,running_processe,"FB-2i ");
        }
       
        else
        {
            vector<int>turnaroundv;
            vector<float>norm_turn;
            float mean_turnaround=0;
            float mean_normturn=0;
            for(int i=0; i<no_processes; i++)
            {
                turnaroundv.push_back(finish_time[i]-processes[i].arrival_time);
                float temp=(float)turnaroundv[i]/(float)processes[i].process_time;
                norm_turn.push_back(temp);
                mean_normturn+=temp;
                mean_turnaround+=turnaroundv[i];
            }
            mean_normturn/=no_processes;
            mean_turnaround/=no_processes;
            
            print_stats("FB-2i",processes,finish_time,turnaroundv,norm_turn,mean_turnaround,mean_normturn, no_processes);          

            
        }
        }
        
void aging(vector<Process>processes ,int no_processes,int instant,int q){

    vector<char>running_processe;
    priority_queue<Process, vector<Process>, SortByPriority> ready_queue;
    queue<Process> current_process;
    queue<Process> tempqueue;
    for(int i = 0 ;i < no_processes; i++)
    {
        if(processes[i].arrival_time == 0){
            processes[i].enterqueue=0;
            ready_queue.push(processes[i]);
            current_process.push(processes[i]);
        }
    }
   
    for(int i = 0 ;i < instant; i++)
    {

            bool flag =true;
            Process p =current_process.front();
            current_process.pop();
            p.current_priority=p.process_time;
            int tempsize=ready_queue.size();
            for (int j = 0; j < tempsize ; j++)
            {
                Process temp=ready_queue.top();
                ready_queue.pop();
                if (temp.name==p.name)
                {
                    flag=false;
                }
            
                temp.current_priority+=1;
                tempqueue.push(temp);
            }

            int tempsize1=tempqueue.size();
            for (int j = 0; j < tempsize1; j++)
            {
                Process temp1=tempqueue.front();
                tempqueue.pop();

                ready_queue.push(temp1);
            }

            if (flag == true)
            {
                p.enterqueue=i;
                ready_queue.push(p);
            }
            Process highest=ready_queue.top();
            ready_queue.pop();
            for (int j = 0; j < q; j++)
            {
            running_processe.push_back(highest.name);
            }
            
            
            current_process.push(highest);

            for(int j =0; j < no_processes; j++)
            {   
                if(processes[j].arrival_time == i+1){
                    processes[j].enterqueue=i+1;
                    ready_queue.push(processes[j]);
                }                   
            }
     
    }
        /*for (int i = 0; i < running_processe.size(); i++)
        {
            printf("%c-",running_processe[i]);
        }*/
         printaging(processes,no_processes,instant,running_processe,"Aging ");

} 
