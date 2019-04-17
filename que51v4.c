/****************************************************************************************************
Q51. Design a scheduler that uses a pre-emptive priority scheduling algorithm based on dynamically changing priority.
Larger number for priority indicates higher priority.
Assume that the following processes with arrival time and service time wants to execute (for reference):
Process AT      Service Time (BT)
P1              0               4
P2              1               1
P3              2               2
P4              3               1

When the process starts execution (i.e.CPU assigned) priority for that process changes at the rate of m=1. When the
process waits for CPU in the ready queue (but not yet started execution), its priority changes at a rate n=2. All the
processes are initially assigned priority value of 0 when they enter ready queue for the first time. The time slice
for each process is q=1. When two processes want to join ready queue simultaneously, the process which has not executed
recently is given priority. Calculate the average waiting time for each process. The program must be generic i.e. number
of processes, their burst time and arrival time must be entered by user.
****************************************************************************************************/
#include<stdio.h>

int i, limit, total = 0, x, counter = 0, time_quantum,j;
int wait_time = 0, turnaround_time = 0,pos,z,p[10],prio[10], a_time[10], b_time[10], temp[10],b;
float avg_wait_time = 0, avg_turnaround_time = 0;

void sort_prior(){
	for(z=0;z<limit;z++){

		int temp1;
		pos=z;
		for(j=z+1;j<limit;j++){

			if(prio[j] < prio[pos])
				pos=j;
		}

		temp1=prio[z];
		prio[z]=prio[pos];
		prio[pos]=temp1;

		temp1=b_time[z];
		b_time[z]=b_time[pos];
 		b_time[pos]=temp1;

		temp1=a_time[z];
		a_time[z]=a_time[pos];
		a_time[pos]=temp1;

		temp1=p[z];
		p[z]=p[pos];
		p[pos]=temp1;

		temp1=temp[z];
		temp[z]=temp[pos];
		temp[pos]=temp1;

	}
}

void aging_func(){
	//printf("\n");
	for(b = 0; b < limit; b++){

             	if(b == i)
                        prio[b] += 1;
               	else if(a_time[b] < total)
            		prio[b] += 2;
	//printf("%d \t %d \t", prio[b], temp[b]);

       	}
	//printf("\n");
}

void userInput_func(){

	printf("\nEnter Total Number of Processes:");

	scanf("%d", &limit);

	x = limit;
      	for(int ii = limit-1, b=0; ii >= 0; b++, ii--){

	    	p[ii]=b+1;
	    	prio[ii]=0;
            	printf("\nEnter total Details of P%d\n", b + 1);
            	printf("Arrival Time:\t");
            	scanf("%d", &a_time[ii]);
            	printf("Burst Time:\t");
            	scanf("%d", &b_time[ii]);
            	temp[ii] = b_time[ii];

     	}
      	printf("\nEnter the Time Quantum:");
      	scanf("%d", &time_quantum);

}

void calc_WTime(){

    	if(temp[i] == 0 && counter == 1) {

            	x--;
                printf("\nP%d\t\t%d\t\t %d\t\t %d\t\t%d", p[i], b_time[i], total - a_time[i], total - a_time[i] - b_time[i],prio[i]);
		avg_wait_time += total - a_time[i];
		avg_turnaround_time += total - a_time[i] - b_time[i];
                counter = 0;
		prio[i] = -99;
  	}

}


int main()
{

	//Function for taking input from user.
	userInput_func();

      	printf("\nPID\tBurst Time\t Turnaround Time\t Waiting Time\t Priority\n");
	for(total = 0, i = limit-1; x != 0;){
		printf("\n");
		for(int k=0; k < limit; k++){
		printf("'%d'%d \t %d \t", p[k], prio[k], temp[k]);
		}printf("\n");
		//For sorting processes based on the priority of the processes.
		sort_prior();

		//ith process in execution
		if(temp[i] <= time_quantum && temp[i] > 0){
                  	total = total + temp[i];
                  	temp[i] = 0;
                  	counter = 1;
            	}
		else if(temp[i] > 0){
                  	temp[i] = temp[i] - time_quantum;
                  	total = total + time_quantum;
            	}

		//Function for allocating Dynamic Prioity to the processes.
		aging_func();

		//Iteratively display Burst time and Priorities of the processes.
		calc_WTime();

      	}
	printf("\n");
	printf("The Average Waiting Time is: %.2f",(avg_wait_time/limit));
	printf("\nThe Average Turnaround Time is: %.2f\n",(avg_turnaround_time/limit));
      	return 0;
}
