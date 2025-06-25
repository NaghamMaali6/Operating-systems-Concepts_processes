/*
  Name: Nagham Maali.
  ID: 1212312.
  Sec.: 2.
*/

//needed libraries:
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

//our table:
struct process
{
    int ID ;
    int AT ;   //Arrival Time
    int BT ;   //Burst Time
    int CBA ;  //Come Back Again Time
    int Py ;   //priority
};

//functions definition:
/*1*/void FCFS(struct process p[] , int n) ;
/*2*/void SJF(struct process p[] , int n) ;
/*3*/void SRTF(struct process p[] , int n) ;
/*4*/void RR(struct process p[] , int n , int q) ;
/*5*/void pP(struct process p[] , int n) ;
/*6*/void NpP(struct process p[] , int n) ;
/***/void GanttChart(struct process p[] , int CT[] , int n) ;
/***/double Avg_TAT(struct process p[] , int CT[] , int n) ;
/***/double Avg_WT(struct process p[] , int CT[] , int n) ;

int main()
{
    struct process p[7] ;
    p[0] = (struct process){1 , 0 , 10 , 2 , 3} ;   //p1
    p[1] = (struct process){2 , 1 , 8 , 4 , 2} ;    //p2
    p[2] = (struct process){3 , 3 , 14 , 6 , 3} ;   //p3
    p[3] = (struct process){4 , 4 , 7 , 8 , 1} ;    //p4
    p[4] = (struct process){5 , 6 , 5 , 3 , 0} ;    //p5
    p[5] = (struct process){6 , 7 , 4 , 6 , 1} ;    //p6
    p[6] = (struct process){7 , 8 , 6 , 9 , 2} ;    //p7

    //print to check
    printf("%-10s  %-15s  %-15s%-26s%-15s\n" , "Process" , "Arrival Time" , "Burst Time" , "Come Back Again Time" , "Priority") ;
    for(int i = 0 ; i < 7 ; i++)
    {
        printf("  P%-12d  %-14d  %-14d      %-20d%-15d\n" , p[i].ID , p[i].AT , p[i].BT , p[i].CBA , p[i].Py) ;
    }

    printf("\n#The Gantt chart , The Average Waiting Time and The Average Turnaround Time for each of the following scheduling Algorithms:\n") ;

    printf("\n 1- First Come First Served(FCFS).\n") ;
    FCFS(p , 7) ;

    printf("\n 2- Shortest Job First(SJF).\n") ;
    SJF(p , 7) ;

    printf("\n 3- Shortest Remaining Time First(SRTF).\n") ;
    SRTF(p , 7) ;

    printf("\n 4- Round Robin(RR) , with q = 5.\n") ;
    int q ;
    RR(p , 7 , 5) ;

    printf("\n 5- Preemptive Priority Scheduling , with aging ; where priority is decremented by 1 , if the process remains in the ready queue for 5 time units. \n") ;
    pP(p , 7) ;

    printf("\n 6- Non-preemptive Priority Scheduling , with aging ; where priority is decremented by 1 if , the process remains in the ready queue for 5 time units.\n") ;
    NpP(p , 7) ;

    return 0 ;
}

void FCFS(struct process p[] , int n)
{
    //sort according to the arrival time
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = (i + 1) ; j < n ; j++)
        {
            if(p[i].AT > p[j].AT)
            {
                struct process temp = p[i] ;
                p[i] = p[j] ;
                p[j] = temp ;
            }
        }
    }

    //find completion times
    int CT[n] ;
    CT[0] = p[0].BT ;

    for(int k = 0 ; k < n ; k++)
    {
        for(int x = (k + 1) ; x < n ; x++)
        {
            CT[x] = CT[k] + p[x].BT ;
        }
    }

    //print the Gantt Chart
    GanttChart(p , CT , n) ;
}

void SJF(struct process p[] , int n)
{
    //sort according to the Burst Time
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = (i + 1) ; j < n ; j++)
        {
            if(p[i].BT > p[j].BT)
            {
                struct process temp = p[i] ;
                p[i] = p[j] ;
                p[j] = temp ;
            }
        }
    }

    //find completion times
    int CT[n] ;
    CT[0] = p[0].BT ;

    for(int k = 0 ; k < n ; k++)
    {
        for(int x = (k + 1) ; x < n ; x++)
        {
            CT[x] = CT[k] + p[x].BT ;
        }
    }

    //print the Gantt Chart
    GanttChart(p , CT , n) ;
}

//this function will sort them according to the Arrival time and find the completion time in SRTF algorithm and so in the Gantt chart the processes will be ordered according to the arrival time and with their completion times*/
void SRTF(struct process p[] , int n)
{
    //sort according to the arrival time
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = (i + 1) ; j < n ; j++)
        {
            if(p[i].AT > p[j].AT)
            {
                struct process temp = p[i] ;
                p[i] = p[j] ;
                p[j] = temp ;
            }
        }
    }

    int CT[n] ;  //Completion Time
    int RT[n] ;  //Remaining Time
    int t = 0 ;  //current time
    int complete = 0 ;
    int shortest ;
    int SI ;

    for(int k = 0 ; k < n ; k++)
    {
        RT[k] = p[k].BT ;  //RT = BT
    }

    //Execute until all processes r complete
    while(complete < n)
    {
        shortest = INT_MAX ;
        SI = -1 ;

        //search for p with the shortest RT
        for(int x = 0 ; x < n ; x++)
        {
            if(p[x].AT <= t && RT[x] < shortest && RT[x] > 0)
            {
                shortest = RT[x] ;
                SI = x ;
            }
        }

        if(SI == -1)  //if no process is ready
        {
            t++ ;  //move to the next time unit
            continue ;
        }

        RT[SI]-- ;
        t++ ;

        if(RT[SI] == 0)  //if RT = 0
        {
            CT[SI] = t ;
            complete++ ;  // p is complete
        }
    }

    //print the Gantt Chart
    GanttChart(p , CT , n) ;
}

 //this function will sort them according to the Arrival time and find the completion time in RR algorithm and so in the Gantt chart the processes will be ordered according to the arrival time and with their completion times*/
void RR(struct process p[] , int n , int q)
{
    //sort according to the arrival time
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = (i + 1) ; j < n ; j++)
        {
            if(p[i].AT > p[j].AT)
            {
                struct process temp = p[i] ;
                p[i] = p[j] ;
                p[j] = temp ;
            }
        }
    }

    int CT[n] ;  //Completion Time
    int RT[n] ;  //Remaining Time
    int t = 0 ;  //current time
    int f = 0 ;
    int Done ;

    for(int k = 0 ; k < n ; k++)
    {
        RT[k] = p[k].BT ;  //RT = BT
    }

    //execute until all processes r complete
    while(1)
    {
        Done = 1 ;

        for(int x = 0 ; x < n ; x++)
        {
            if(RT[x] > 0)  //if p has RT (RT != 0)
            {
                Done = 0 ;

                if(RT[x] > q)
                {
                    t += q ;
                    RT[x] -= q ;
                }
                else
                {
                    t += RT[x] ;
                    CT[x] = t ;
                    RT[x] = 0 ;
                }
            }
        }

        if(Done == 1)  //if all processes r done
        {
            break ;  //exit the loop
        }
    }

    //print the Gantt Chart
    GanttChart(p , CT , n) ;
}

//this function will sort them according to the priority and find the completion time in pP algorithm and so in the Gantt chart the processes will be ordered according to the priority and with their completion times*/
void pP(struct process p[] , int n)
{
    struct process temp ;
    //sort according to the priority
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = (i + 1) ; j < n ; j++)
        {
            if(p[i].Py > p[j].Py)
            {
                temp = p[i] ;
                p[i] = p[j] ;
                p[j] = temp ;
            }
            else if(p[i].Py == p[j].Py) //when two processes or more have the same priority , sort according to the arrival time
            {
                if(p[i].AT > p[j].AT)
                {
                    temp = p[i] ;
                    p[i] = p[j] ;
                    p[j] = temp ;
                }
            }
        }
    }

    int CT[n] ;  //Completion Time
    int RT[n] ;  //Remaining Time
    int Done = 0 ;
    int t = 0 ;  //current time
    int HP ;
    int SelP ;

    for(int k = 0 ; k < n ; k++)
    {
        RT[k] = p[k].BT ;  //RT = BT
        CT[k] = 0 ;
    }

    //execute until all processes r complete
    while(Done < n)
    {
        HP = INT_MAX ;
        SelP = -1 ;

        //search for p with the highest priority
        for(int x = 0 ; x < n ; x++)
        {
            if(p[x].AT <= t && RT[x] > 0 && p[x].Py < HP)
            {
                HP = p[x].Py ;
                SelP = x ;
            }
        }

        if(SelP == -1)  //if no process is ready
        {
            t++ ;  //move to the next time unit
            continue ;
        }

        RT[SelP]-- ;
        t++ ;

        if(RT[SelP] == 0)
        {
            CT[SelP] = t ;
            Done++ ;  //p is done
        }
    }

    //print the Gantt Chart
    GanttChart(p , CT , n) ;
}

void NpP(struct process p[] , int n)
{
    struct process temp ;
    //sort according to the priority
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = (i + 1) ; j < n ; j++)
        {
            if(p[i].Py > p[j].Py)
            {
                temp = p[i] ;
                p[i] = p[j] ;
                p[j] = temp ;
            }
            else if(p[i].Py == p[j].Py) //when two processes or more have the same priority , sort according to the arrival time
            {
                if(p[i].AT > p[j].AT)
                {
                    temp = p[i] ;
                    p[i] = p[j] ;
                    p[j] = temp ;
                }
            }
        }
    }

    //find the completion times
    int CT[n] ;
    CT[0] = p[0].BT ;

    for(int k = 0 ; k < n ; k++)
    {
        for(int x = (k + 1) ; x < n ; x++)
        {
            CT[x] = CT[k] + p[x].BT ;
        }
    }

    //print the Gantt Chart
    GanttChart(p , CT , n) ;
}

void GanttChart(struct process p[] , int CT[] , int n)
{
    printf("//The Gantt Chart:\n") ;

    for(int i = 0 ; i < n ; i++)
    {
        printf(" |   P%d  " , p[i].ID) ;
    }
    printf("|") ;

    printf("\n 0 ") ;

    for(int j = 0 ; j < n ; j++)
    {
        printf("     %d  " , CT[j]) ;
    }

    printf("\n") ;

    double avgTAT = Avg_TAT(p , CT , n) ;
    printf("\n//The Average Turnaround Time = %lf\n" , avgTAT) ;

    double avgWT = Avg_WT(p , CT , n) ;
    printf("\n//The Average Waiting Time = %lf\n" , avgWT) ;
}

//calculate average turnaround time
double Avg_TAT(struct process p[] , int CT[] , int n)
{
    int TAT[n] ;

    for(int i = 0 ; i < n ; i++)
    {
        TAT[i] = CT[i] - p[i].AT ;  //TAT = CT - AT
    }

    int sumTAT = 0 ;
    double avgTAT ;

    for(int j = 0 ; j < n ; j++)
    {
        sumTAT = sumTAT + TAT[j] ;  //find sum of TAT
    }

    //find Average Turnaround Time:
    avgTAT = (double) sumTAT / 7 ;

    return avgTAT ;
}

//calculate average waiting time
double Avg_WT(struct process p[] , int CT[] , int n)
{
    int WT[n] ;
    int sumWT = 0 ;
    double avgWT ;

    int TAT[n] ;

    for(int i = 0 ; i < n ; i++)
    {
        TAT[i] = CT[i] - p[i].AT ;  //TAT = CT - AT
    }

    for(int j = 0 ; j < n ; j++)
    {
        WT[j] = TAT[j] - p[j].BT ;  //WT = TAT - BT
    }

    for(int k = 0 ; k < n ; k++)
    {
        sumWT = sumWT + WT[k] ;  //find sum of WT
    }

    //find Average Waiting Time:
    avgWT = (double) sumWT / 7 ;

    return avgWT ;
}
