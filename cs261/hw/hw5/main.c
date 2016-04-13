#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
  char cmd = ' ';
  char *strptr = NULL;
  char str[20];
  char *mode = "r";
  int prio = 0;
  FILE *file;
  DynArr* mainList = createDynArr(10);
  TaskP task;

  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do
    {
      printf("Press:\n"
             "'l' to load to-do list from a file\n"
             "'s' to save to-do list to a file\n"
             "'a' to add a new task\n"
             "'g' to get the first task\n"
             "'r' to remove the first task\n"
             "'p' to print the list\n"
             "'e' to exit the program\n"
             );
      /* get input command (from the keyboard) */
      cmd = getchar();
      /* clear the trailing newline character. FILE NAME IS todo.txt */
      while (getchar() != '\n');

	  switch (cmd){

	  case 'l':
		  printf("please enter the filename \n");
		  strptr = NULL;
		  if (fgets(str, sizeof(str), stdin) != NULL){  //gets char stream of size str into str from 'stdin' = keyboard input
			  strptr = strchr(str, '\n');		//strchr returns pointer to first char
			  if (strptr){
				  *strptr = '\0';
			  }
		  }
		  file = fopen(str, "r");
		  loadList(mainList, file);



		  //scanf("%s", strptr);
		  //while (getchar() != '\n');
		  //file = fopen("todo.txt", "r");
		  //if (file == NULL) {
			 // perror("Error");
		  //}
		  //loadList(mainList,file);
		  break;
	  case 's':
		  printf("Enter filename: \n");
		  strptr = NULL;
		  if (fgets(str, sizeof(str), stdin) != NULL){
			  strptr = strchr(str, '\n');
			  if (strptr){
				  *strptr = '\0';
			  }
		  }
		  file = fopen(str, "w");
		  saveList(mainList, file);
		  break;
	  case 'a':
	      printf("What is the task? \n");
		  strptr = NULL;
		  if (fgets(str, sizeof(str), stdin) != NULL){
			  strptr = strchr(str, '\n');
			  if (strptr){
				  *strptr = '\0';
			  }
		  }
		  printf("What is the priority? \n");
		  scanf("%d", &prio);
		  addHeap(mainList, createTask(prio,str), compare);
		  break;
	  case 'g':
		  if (isEmptyDynArr(mainList)){
			  printf("List is empty! \n");
			  break;
		  }
		  task = getMinHeap(mainList);

		  printf("%d:  %s\n\n", task->priority, task->description);
		  break;
	  case 'r':
		  removeMinHeap(mainList,compare);
		  break;

	  case 'p':
		  printList(mainList);
		  break;
	  
	  }
      /* Note: We have provided functions called printList(), saveList() and loadList() for you
         to use.  They can be found in toDoList.c */
    }
  while(cmd != 'e');
  /* delete the list */
  deleteDynArr(mainList);

  return 0;
}
