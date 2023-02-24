#include<stdio.h>
#include<iostream>
#include <string>
#include <string.h>
#include <vector>
#include "scheduling_algoritms.h"

using namespace std;
string params[2];
void string_split(string word, char sep){
    int current = 0, i = 0; 
    int start = 0, end = 0;
    while(i<=word.length())
    {
        if(word[i]==sep || i == word.length())
        {
        end=i;
        string part="";
        part.append(word,start,end-start);
        params[current]=part;
        current+=1;
        start=end+1;
        }
    i++;
}

}   
int main() {
    string  action ;
    cin >> action;
    //cout << action<< endl;
    
    string schedule;
    cin >> schedule;
    //cout << schedule<< endl;
    size_t foundcomma = schedule.find(",");
    if(foundcomma != string::npos){
        int i =0;
        char arr[schedule.length() + 1]; 
        strcpy(arr, schedule.c_str());
        char *token = strtok(arr, ",");
        int instant;
        int no_processes;
        vector<Process> processes;
        while (token != NULL)
        {   
            schedule=token;
            //cout << schedule<< endl;
            size_t found = schedule.find("-");
            int q=0;
            
            if(found != string::npos){
                string_split(schedule,'-');
                schedule=params[0];
                q = stoi(params[1]);
                
            }
            
            if (i==0)
                {
                
                cin >> instant;
                //cout << instant<< endl;

                
                cin >> no_processes;
                //cout << no_processes<< endl;
                
                for (int i=0; i<no_processes ; i++){
                
                    int y,z;
                    char x,s1,s2;                             
                    if ( (cin >> x >> s1 >> y >> s2 >> z )      
                        && s1==',' &&  s2==',')    
                    {
                        struct Process p(x,y,z);
                        processes.push_back(p);
                        

                    }
                    else cout << "Bad input !"<<endl;    
                    
                }    
                i++;          
            }
            

            
            
            if(schedule == "1"){
                fcfs (processes ,no_processes ,action,instant);
            }
            else if(schedule == "3"){
                SPN (processes ,no_processes ,action,instant);
            }
            else if(schedule == "2"){
                roundrobbin (processes ,no_processes , action, instant, q);
            }
            else if(schedule == "4"){
                SRT (processes ,no_processes ,action,instant);
            }
            else if(schedule == "5"){
                HRRN (processes ,no_processes ,action,instant);
            }
            else if(schedule == "6"){
                feedback_1 (processes ,no_processes ,action,instant);
            }
            else if(schedule == "7"){
                feedback_2i (processes ,no_processes ,action,instant);
            }
            else if(schedule == "8"){
                aging(processes , no_processes, instant, q);
            }            
            token = strtok(NULL, ",");
       }
    }
    else{
        size_t found = schedule.find("-");
        int q=0;
        if(found != string::npos){
            vector<char> temp;
            int n = schedule.length();
            char char_array[n + 1];
            strcpy(char_array, schedule.c_str());
            char *ptr;
            ptr = strtok(char_array, "-");
            while (ptr != NULL)  
            { 
                temp.push_back(*ptr);
                ptr = strtok (NULL, "-");  
            }  
            schedule=temp[0];
            q = (int)temp[1]-48;
        }
        
        int instant;
        cin >> instant;
        //cout << instant<< endl;

        int no_processes;
        cin >> no_processes;
        //cout << no_processes<< endl;

        vector<Process> processes;
        
        
        for (int i=0; i<no_processes ; i++){
        
            int y,z;
            char x,s1,s2;                             
            if ( (cin >> x >> s1 >> y >> s2 >> z )      
                && s1==',' &&  s2==',')    
            {
                struct Process p(x,y,z);
                processes.push_back(p);
                

            }
            else cout << "Bad input !"<<endl;    
            
        }
        
        
        if(schedule == "1"){
            fcfs (processes ,no_processes ,action,instant);
        }
        else if(schedule == "3"){
            SPN (processes ,no_processes ,action,instant);
        }
        else if(schedule == "2"){
            roundrobbin (processes ,no_processes , action, instant, q);
        }
        else if(schedule == "4"){
            SRT (processes ,no_processes ,action,instant);
        }
        else if(schedule == "5"){
            HRRN (processes ,no_processes ,action,instant);
        }
        else if(schedule == "6"){
            feedback_1 (processes ,no_processes ,action,instant);
        }
        else if(schedule == "7"){
            feedback_2i (processes ,no_processes ,action,instant);
        }
        else if(schedule == "8"){
            aging(processes , no_processes, instant, q);
        }
    }
    
    return 0;
}
