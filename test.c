#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{
    /* Variables used throughout the program */
    
    int i = 0; 				// for loop index.
    listElement *listPosition = NULL; 	//Position pointer

    linkedList myList;
    list_initialize(&myList, NULL);
    
    list_insert_next(&myList, NULL, "one");
    listPosition = list_head(&myList);
    
    list_insert_next(&myList, listPosition, "two"); 
    listPosition = list_next(listPosition);

    list_insert_next(&myList, listPosition, "three");
    listPosition = list_next(listPosition);
    
    /*-------------------------------------------------------------
     *Iterate through the list and output the data in each element
     *-----------------------------------------------------------*/    
    listPosition = list_head(&myList);

    i = 0;
    for (i; i < list_get_size(&myList); i++)
    {
        printf("Data is : %s.\n", (char*)listPosition->data);
        listPosition = list_next(listPosition);
    }

    
    printf ("Size of list BEFORE deleting an element : %d.\n", 
             list_get_size(&myList));
    
    /* Remove the node after head */
    listPosition = list_head(&myList);
    list_remove_next(&myList, listPosition, &listPosition->data);    
    
    printf ("Size of list AFTER deleting an element : %d.\n",
             list_get_size(&myList));
    /* We have had enough fun now, time to destroy the list*/    
    list_destroy(&myList); 
        
    return 0;
}
