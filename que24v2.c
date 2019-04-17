/********************************************************************************************************************************************************************************
Ques 24. Design a scheduling program to implements a Queue with two levels:
Level 1 : Fixed priority preemptive Scheduling
Level 2 : Round Robin Scheduling
For a Fixed priority preemptive Scheduling (Queue 1), the Priority 0 is highest priority. If one process P1 is scheduled
and running, another process P2 with higher priority comes. The New process (high priority) process P2 preempts currently
running process P1 and process P1 will go to second level queue. Time for which process will strictly execute must be
considered in the multiples of 2.
All the processes in second level queue will complete their execution according to round
robin scheduling.
Consider: 1. Queue 2 will be processed after Queue 1 becomes empty.
          3. Priority of Queue 2 has lower priority than in Queue 1.
********************************************************************************************************************************************************************************/

#include <stdio.h>
#include <string.h>

	char p[10][5],temp[5];
    	int i,j,b_time[10],w_time[10],totw_time=0,prior[10],temp1,n;
    	float avgw_time;

//Impementation Selection sort to sort the processes based on their Priority.
void sort_prior(){
	for(i=0;i<n-1;i++) {
        	for(j=i+1;j<n;j++) {
            		if(prior[i]>prior[j]) {
                		temp1=prior[i];
                		prior[i]=prior[j];
                		prior[j]=temp1;

				temp1=b_time[i];
                		b_time[i]=b_time[j];
                		b_time[j]=temp1;

                		strcpy(temp,p[i]);
                		strcpy(p[i],p[j]);
                		strcpy(p[j],temp);
            		}
        	}
    	}
}

void main(){

    	printf("Enter no of processes:");
    	scanf("%d",&n);

    	for(i=0;i<n;i++){

        	printf("\nEnter process id: :");
        	scanf("%s",&p[i]);
        	printf("Enter Burst time:");
        	scanf("%d",&b_time[i]);
        	printf("Enter Priority:");
        	scanf("%d",&prior[i]);

    	}
	//Using Selection sort to arrange processes based on their priority
    	sort_prior();

    	w_time[0]=0;
    	for(i=1;i<n;i++)
    	{
        	w_time[i]=w_time[i-1]+b_time[i-1];
        	totw_time=totw_time+w_time[i];
    	}

    	avgw_time=(float)totw_time/n;

    	printf("p_name\t p_time\t priority\t w_time\n");

	for(i=0;i<n;i++) {

       		printf(" %s\t %d\t %d\t %d\n" ,p[i],b_time[i],prior[i],w_time[i]);

    	}
   	printf("Total Waiting time = %d\nAvg Waiting time = %f\n\n",totw_time,avgw_time);

    	int ts,pid[10],r_time[10],w_time1[10],tat[10],i1,j1,n2,n1;
    	int bt[10],flag[10],ttat=0,tw_time=0;
    	float aw_time,atat;

    	printf("\nEnter the number of Processes : ");
    	scanf("%d",&n);
    	n1=n;
    	printf("\n Enter the Timeslice : ");
    	scanf("%d",&ts);

    	for(i=1;i<=n;i++ ){

        	printf("\n Enter the process ID : ");
        	scanf("%d",&pid[i]);
        	printf("\n Enter the Burst Time for the process: ");
        	scanf("%d",&bt[i]);
        	r_time[i]=bt[i];
    	}

    	for(i=1;i<=n;i++){

        	flag[i]=1;
        	w_time[i]=0;

    	}

	//Algo for ROUND-ROBIN Scheduling Queue
    	while(n!=0){

        for(i=1;i<=n;i++){

            	if(r_time[i]>=ts){

                	for(j=1;j<=n;j++){

                    		if((i!=j)&&(flag[i]==1)&&(r_time[j]!=0))
                   	 		w_time[j]+=ts;
                	}
                	r_time[i]-=ts;
                	if(r_time[i]==0){

                    		flag[i]=0;
                    		n--;

                	}
            	}else {

                	for(j=1;j<=n;j++){

                    		if((i!=j)&&(flag[i]==1)&&(r_time[j]!=0))
                    			w_time[j]+=r_time[i];
                	}
                	r_time[i]=0;
                	n--;
                	flag[i]=0;
            		}
        	}
    	}

    	for(i=1;i<=n1;i++)
    	{

        	tat[i]=w_time[i]+bt[i];
        	tw_time=tw_time+w_time[i];
        	ttat=ttat+tat[i];

    	}

    	aw_time=(float)tw_time/n1;
    	atat=(float)ttat/n1;

    	printf("\n\n Process \t Process ID  \t BurstTime \t Waiting Time \t TurnaroundTime \n ");

	for(i=1;i<=n1;i++){

        	printf("\n %5d \t\t %5d \t\t %5d \t\t %5d \t\t %5d \n", i,pid[i],bt[i],w_time[i],tat[i]);

    	}

	printf("\n The average Waiting Time=%4.2f",aw_time);
    	printf("\n The average Turn around Time=%4.2f\n",atat);

}
