/********************************************************************
 Source file 	: list.c
      Author 	: Leam Delaney

     Purpose	: Provide functionality for linked-lists
     Version	: 0.0.1
********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

void list_initialize(linkedList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}

void 
list_destroy(linkedList *list)
{
    void * data;

    /* Loop to remove each element from the list */
    while (list_get_size(list) > 0)
    {
        if (list_remove_next(list, NULL, (void**)&data) == 0 &&
            list->destroy != NULL)
        {
            /* Call the function that the user defines for destroy */
            list->destroy(data);
        }
    }
    /* No more operations can be performed on this list now. As a
     * precaution, the structure should be cleared anyway. */
    memset(list, 0, sizeof(linkedList));
    return;
}

int 
list_insert_next(linkedList *list, 
                 listElement *element,
                 const void  *data)
{
    listElement *newElement;
    
    /* Attempt to allocate the memory for the new element */    
    if ((newElement = (listElement *)malloc(sizeof(listElement))) == NULL)
    {
        printf("list_insert_next : failed to create new element\n");
        return -1;
    }
    
    newElement->data = (void*)data;
    
    if (element == NULL)
    {
        /* Add the new element at the HEAD of the list */
        if (list_get_size(list) == 0)
        {
            list->tail = newElement;
        }
        
        newElement->next = list->head;
        list->head=newElement;
    }    
    else
    {
        if (element->next == NULL)
        {
            list->tail = newElement;
        }
    
        newElement->next = element->next;
        element->next = newElement;
    }
    
    list->size++;
    return 0;
}

int
list_remove_next(linkedList *list, listElement *element, void **data)
{
    listElement* oldElement;

    /* Can't remove from an empty list */
    if ( list_get_size(list) == 0 )
    {
        printf("list_remove_next : cannot remove element from empty list.\n");
        return -1;
    }

    /* Continue to remove element from list */
    if ( element == NULL )
    {
        /* Remove element at head of list */
        *data = list->head->data;
        oldElement = list->head;
        list->head = list->head->next;

        if ( list_get_size(list) == 1 )
        {
            list->tail = NULL;
        }
    }
    else
    {
        /* Remove element from anywhere else in the list */
        if ( element->next == NULL )
        {
            /*If there is no element after the current one, fail */
            printf("list_remove_next : no element after tail\n");
            return -1;
        }
        *data = element->data;
        oldElement = element->next;
        element->next = element->next->next;

        if ( element->next == NULL )
        {
            /* Setting new tail of list */
            list->tail = element;
        }
    }
    
    /* Free the storage which was allocated in the list for old element. */
    free(oldElement);
    
    list->size--;
    return 0;
}

/* The following section of code is used to get values associated with
 * the list, or the elements inside it.
 * They are pretty simple to understand.*/
int 
list_get_size(linkedList* list)
{
    return (int)list->size;
}

listElement* 
list_head(linkedList* list)
{
    return list->head;
}

listElement* 
list_tail(linkedList* list)
{
    return list->tail;
}

int 
list_is_head(linkedList* list, listElement* element)
{
    if( element == list->head )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int 
list_is_tail(linkedList* list, listElement* element)
{
    if( element == list->tail )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void* 
list_data(listElement* element)
{
    return element->data;
}

listElement* 
list_next(listElement* element)
{
    return element->next;
}
