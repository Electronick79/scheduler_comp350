// Nickson DosSantos, Warren Clark, & Aman Marfatia

// Goal: create a simulation of a FCFS scheduler
//Note: be sure to read “C Structures” on BB under “Lectures”
//Step 1 (50 points): Build and test a queue and functions to maintain it
//•	Define a structure to represent a PCB as follows:
//Step 2 (50 points): Add code to step1 to:
//•	Create wait queue ‘W’
//•	Read input from the keyboard to simulate events:
//o	New process arrives: “J process_id estimated_time_cycles”
//	E.g.: JA6
//o	No event: “N90”
//o	End of simulation: “E90”

#include<stdlib.h>
typedef struct Pcb {
    char id;
    int estTime;
    int remainTime;
    int waitTime;
    struct Pcb *next; // pointer to the next Pcb in a linked list
} Pcb_t ;
typedef struct {
    char id;
    Pcb_t * first;
    Pcb_t * last;
} Queue_t;
void printPCB(Pcb_t * pcb){
    if(pcb!=NULL){
        printf("PCB ID: %c, Est. Time: %d, Remaining Time: %d, Total Wait Time: %d\n",pcb->id,pcb->estTime,pcb->remainTime,pcb->waitTime);
    }
}
void enqueue(Pcb_t * pcb, Queue_t * queue){
    pcb->next=NULL;
    if(queue->first==NULL){
        queue->first=queue->last=pcb;
        return;
    }
    queue->last->next=pcb;
    queue->last=pcb;
}
void dequeue( Queue_t * queue, Pcb_t * pcb){
    Pcb_t *temp=queue->first;
    if(temp==NULL)
        return;
    if((queue->first==queue->last) && queue->first==pcb){
        free(queue->first);
        queue->first=queue->last=NULL;
        return;
    }
    if(queue->first==pcb){
        Pcb_t *toDelete=queue->first;
        queue->first=queue->first->next;
        free(toDelete);
        return;
    }
    while(temp->next!=NULL){
        if(temp->next==pcb){
            Pcb_t *toDelete=temp->next;
            temp->next=temp->next->next;
            free(toDelete);
            return;
        }
        temp=temp->next;
    }
}
void printQ(Queue_t * queue){
    printf("--- Queue: R -------\n");
    if(queue->first==NULL){
        printf("Queue is empty\n");
        return;
    }
    Pcb_t *temp=queue->first;
    while(temp!=NULL){
        printPCB(temp);
        temp=temp->next;
    }
}
int main(){
    printf("*** Beginning Step 1 ***\n--- Create three PCBs\n");
    Pcb_t* pcb1=(Pcb_t*)malloc(sizeof(Pcb_t));
    pcb1->id='A';
    pcb1->estTime=6;
    pcb1->remainTime=6;
    pcb1->waitTime=0;

    Pcb_t* pcb2=(Pcb_t*)malloc(sizeof(Pcb_t));
    pcb2->id='B';
    pcb2->estTime=2;
    pcb2->remainTime=2;
    pcb2->waitTime=0;

    Pcb_t* pcb3=(Pcb_t*)malloc(sizeof(Pcb_t));
    pcb3->id='C';
    pcb3->estTime=3;
    pcb3->remainTime=3;
    pcb3->waitTime=0;

    printPCB(pcb1);
    printPCB(pcb2);
    printPCB(pcb3);

    printf("---- Define ready queue\n");
    Queue_t* R=(Queue_t*)malloc(sizeof(Queue_t));
    R->first=R->last=NULL;
    printQ(R);
    printf("----- enqueue PCBs\n");
    enqueue(pcb1,R);
    enqueue(pcb2,R);
    enqueue(pcb3,R);
    printQ(R);

    printf("----- Remove the middle PCB from the R queue\n");
    dequeue(R,pcb2);
    printQ(R);

    printf("----- Remove the last PCB from the R queue\n");
    dequeue(R,pcb3);
    printQ(R);

    printf("----- Remove the remaining PCB from the R queue\n");
    dequeue(R,pcb1);
    printQ(R);
    printf("*** End Step 1 ***\n");
    return 0;
}
