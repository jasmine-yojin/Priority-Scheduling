//This program uses singly linkedlist to store the processes
/*===============================================================
gcc JKim_schd.c -o JKim_thd.exe					                                                  
./JKim_thd.exe 1 > JKimResultNonpreemptive.txt                                                                                          
./JKim_thd.exe 2 > JKimResultPreemptive.txt                                                                        
================================================================*/

#include<stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


struct node{
	int pNumber;
	int priority;
	int burst;
	int arrival;
	int waitTime;
	int timeRan;
		
	struct node *next;
};

struct node *head = NULL;
int size=0;
int currentTime;

bool isEmpty(){
	return head == NULL;
}


void addNode(int pn, int p, int b, int a){
	
	struct node *link= (struct node*) malloc (sizeof(struct node));
	link->pNumber = pn;
	link->priority = p;
	link->burst = b;
	link->arrival = a;
	link->waitTime=0;
	link->timeRan=0;
	link->next=NULL;
	
	if(isEmpty()){
		head=link;
		
	}else{
		struct node *ptr=head;
		while(ptr->next!=NULL){
			ptr=ptr->next;
		}
			
		ptr->next=link;
		
	}
	
	size++;	
}

void printList(){
	struct node *ptr = head;
	
	//printf("size: %d\n", size);
	printf("Process\tPriority\tBurst\tArrival\n");

	while(ptr!=NULL){
		printf("%d\t%d\t%d\t%d\n", ptr->pNumber, ptr->priority, ptr->burst, ptr->arrival);
		ptr = ptr->next;
	}
}

int main (int argc, char* argv[]){
	
	if (argc < 2){
		printf("Wrong number of command line arguments. To run nonpreemptive scheduling, enter 1. For preemptive, enter 2 in addition to JKim_schd.exe file.");
		return 1;
    }
	
	//input decides whether to run preemptive or nonpreemptive priority scheduling.
	int input= atoi(argv[1]);
		
	//Read from File
	int pNumber;
	int priority;
	int burst;
	int arrival;
	char buffer[256];
	FILE* in= fopen("Project3InputFile.txt.txt","r");
	if (in ==NULL){
		perror("unable to open file!");
		exit(1);
	}
	//forget the first line
	fgets(buffer, sizeof(buffer), in);
	while(fgets(buffer, sizeof(buffer), in) != NULL){// fgets() reads a line from a file. 
		sscanf(buffer, "%d\t%d\t%d\t%d", &pNumber, &priority, &burst, &arrival);
		addNode(pNumber, priority, burst, arrival);//store each process in the LinkedList
	}
	fclose(in);
	printf("Original List:\n");
	printList();
	
	//Scheduling
	bool duplicate= false;
	int hpriority=20;
	int cpriority;
	int remaining=size;
	struct node *ptr = head;
	int count;
	int upriority=0;
	
	//print out the process time table
	printf("\nTime\tProcess\n");
	printf("---------------\n");
	
	//nonpreemptive scheduling
	if(input==1){
	
		while (remaining>0){
			//search for the process with the highest priority
			ptr= head;
			while(ptr!=NULL){
				cpriority=ptr->priority;
				if ((cpriority<=hpriority) && (ptr->arrival<=currentTime)){
					hpriority= ptr->priority;
				}
				ptr = ptr->next;
			} 
			
			//Search for the process that match the current highest priority then work on them. 
				ptr=head;
				while(ptr!=NULL){
					if((ptr->priority == hpriority)&& (ptr->arrival<=currentTime)){
						printf("%d\t%d\n", currentTime, ptr->pNumber);
						currentTime+=ptr->burst;
						ptr->waitTime= currentTime - ptr->arrival - ptr->burst;
						ptr->priority=100;//once a process is complete, give a very low priority value. 
						remaining--;
					}
					
					ptr = ptr->next;
				}
			hpriority=20;//reset the highest priority value below 100 so the program can find the next highest priority number.
	}
		//pring out the wait time table
		ptr = head;
		printf("\nProcess\tWait Time\n");
		printf("---------------------\n");
		while(ptr!=NULL){
			printf("%d\t%d\n", ptr->pNumber, ptr->waitTime);
			ptr = ptr->next;
		}
		
	//preemptive scheduling
	}else{
			while (remaining>0){
		//search for the process with the highest priority
		ptr= head;
		while(ptr!=NULL){
			cpriority=ptr->priority;
			if ((cpriority<=hpriority) && (ptr->arrival<=currentTime)){
				if(cpriority==hpriority)duplicate=true;
				hpriority= ptr->priority;
				
			}
			ptr = ptr->next;
		} 
		
		
		//Run the process- No Duplicate
		if (duplicate==false){
			ptr=head;
			while(ptr!=NULL){
				if(ptr->priority == hpriority){
					printf("%d\t%d\n", currentTime, ptr->pNumber);
					ptr->waitTime= currentTime - ptr->arrival;
					ptr->priority=100;
					currentTime+=ptr->burst;
					remaining--;
					break;
					
				}
				
				ptr = ptr->next;
			}
		}else{//Run the process- Duplicate
			ptr=head;
			while(ptr!=NULL){
				
				if((ptr->priority == hpriority)&&(ptr->arrival<=currentTime)){
					ptr->pNumber;
					printf("%d\t%d\n", currentTime, ptr->pNumber);
					
					
					if(ptr->burst>=10){
						ptr->burst-= 10;
						currentTime+=10;
						ptr->timeRan+=10;
						
					}else{
						ptr->waitTime= currentTime - ptr->arrival - ptr->timeRan;
						currentTime+=ptr->burst;
						ptr->burst=0;
						ptr->priority=100;
						remaining--;
						
					}
				}
				
				ptr= ptr->next;
			
			}
			
			//Equal priority processes finished running. Reset duplicate variable.
			duplicate=false;
			
	
		}
		
		hpriority=hpriority+1;

		
	
		}
		
		//print out the preemptive table
		ptr = head;
		printf("\nProcess\tWait Time\n");
		printf("---------------------\n");
	
		while(ptr!=NULL){
			printf("%d\t%d\n", ptr->pNumber, ptr->waitTime);
			ptr = ptr->next;
		}
	}
	return 0;
}
