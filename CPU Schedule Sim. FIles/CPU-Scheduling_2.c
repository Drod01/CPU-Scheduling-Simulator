#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>

struct PCB {
  int PID, PR;
  int numCPUBurst, numIOBurst;
  int *CPUBurst, *IOBurst;
  int cpuindex, ioindex;
  struct timespec ts_begin, ts_end, timeEnterReadyQ;
  struct PCB *prev, *next;
  int total_CPU_time;
  int totalWait;
  int arrival;
  int completeTime;
};

typedef struct LinkedList {
  struct PCB *start;
  struct PCB *end;
} LinkedList;

LinkedList ready_queue;
LinkedList io_queue;

void sortReadyQueueSJF(LinkedList *ready_queue);
void printReadyQueue(LinkedList *ready_queue);
double totaltrn = 0;
double totalWait = 0; 
double totalBurstTime = 0;
int numProc = 0;
double totalexec = 0;
int file_read_done = 0;
int cpu_busy = 0, io_busy = 0, cpu_sch_done = 0, io_sys_done = 0, totalCPU = 0;
sem_t sem_cpu, sem_io;
double elapsed = 0;
int quantum;

void sortReadyQueueSJF(LinkedList *ready_queue) {
  struct PCB *current, *nextPCB;
  int swapped;

  if (ready_queue->start == NULL) return;

  do {
    swapped = 0;
    current = ready_queue->start;

    while (current->next != NULL) {
      nextPCB = current->next;
      if (current->total_CPU_time > nextPCB->total_CPU_time) {
        struct PCB temp = *current;
        *current = *nextPCB;
        *nextPCB = temp;
        swapped = 1;
      }
      current = current->next;
    }
  } while (swapped);
}

void printReadyQueue(LinkedList *ready_queue) {
  struct PCB *current = ready_queue->start;

  if (current == NULL) {
    printf("Ready Queue is empty.\n");
    return;
  }

  printf("Printing Ready Queue:\n");
  while (current != NULL) {
    printf("PID: %d, Total CPU Time: %d\n", current->PID, current->total_CPU_time);
    current = current->next;
  }
}

void addToReadyQueue(LinkedList *ready_queue, struct PCB *pcb) {
  if (ready_queue->start == NULL) {
    ready_queue->start = pcb;
    ready_queue->end = pcb;
    pcb->next = NULL;
  } else {
    ready_queue->end->next = pcb;
    ready_queue->end = pcb;
    pcb->next = NULL;
  }
}

void addToIOQueue(LinkedList *io_queue, struct PCB *pcb) {
  if (io_queue->start == NULL) {
    io_queue->start = pcb;
    io_queue->end = pcb;
    pcb->next = NULL;
  } else {
    io_queue->end->next = pcb;
    io_queue->end = pcb;
    pcb->next = NULL;
  }
}

struct PCB *pullFromReadyQueue(LinkedList *ready_queue) {
  if (ready_queue->start == NULL) {
    return NULL; 
  }

  struct PCB *pcb = ready_queue->start;
  ready_queue->start = ready_queue->start->next;

  if (ready_queue->start == NULL) {
    ready_queue->end = NULL;
  }
  return pcb;
}

struct PCB *pullFromIOQueue(LinkedList *io_queue) {
  if (io_queue->start == NULL) {
    return NULL;
  }

  struct PCB *pcb = io_queue->start;
  io_queue->start = io_queue->start->next;

  if (io_queue->start == NULL) {
    io_queue->end = NULL;
  }
  return pcb;
}

void *file_read_thread(void *arg) {
  char *file_name = (char *)arg;
  FILE *fp;
  struct PCB *pcb = (struct PCB *)malloc(sizeof(struct PCB));
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    printf("Error opening file.\n");
    return NULL;
  }

  while (!feof(fp)) {
    char line[100];
    fgets(line, 100, fp);
    if (strncmp(line, "proc", 4) == 0) {
      // Process PCB 
    } else if (strncmp(line, "sleep", 5) == 0) {
      // Sleep
    } else if (strncmp(line, "stop", 4) == 0) {
      break;
    }
  }

  fclose(fp);
  return NULL;
}

pthread_mutex_t ready_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t io_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void *cpu_scheduler_thread(void *arg) {
  char *alg = (char *)arg;
  struct timespec atimespec;
  struct PCB *pcb = (struct PCB *)malloc(sizeof(struct PCB));

  while(cpu_sch_done == 0) {
    // CPU scheduler logic
  }

  free(pcb);
  return NULL;
}

void *io_system_thread(void *arg) {
  char *alg = (char *)arg;
  struct timespec atimespec;
  struct PCB *pcb;

  while (io_sys_done == 0) {
    // IO system logic
  }

  free(pcb);
  return NULL;  
}

int main(int argc, char *argv[]) {

  if (argc < 5) {
    printf("Usage: %s -alg <FIFO/SJF/PR/RR> -input <input_file>\n", argv[0]);
    return 1;
  }

  // Argument parsing

  // Thread creation
  
  // Join threads

  // Cleanup
  
  return 0;
}


