/**********************************************************
 * Header File : list.h
 * 
 * Purpose : Interface for a linked list in C
 * Author  : Leam Delaney
 * 
 * This code is not covered by any kind of warranty.
 * Please feel free to use and redistribute this code.
 *********************************************************/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/* Struct for linked list elements. */
typedef struct listElement_
{
    void			*data;
    struct listElement_		*next;
}listElement;

/* Struct for link-list data structure */
typedef struct linkedList_
{
    int		size;
    int 	(*match)(const void *key1, const void *key2);
    void	(*destroy)(void *data);
    
    /* The two elements below define the two elements
     * which must be known for a standard linked list */
    listElement	*head;
    listElement *tail;
}linkedList;

/**********************************************************
 * Public interface for link list
 *********************************************************/

/* list_initialize
 * Return type : void 
 * 
 * Description : Initializes the linked list of type linkedList.
 *  All linked lists must be initialized before any other operations
 *  can be ran on them. The destroy argument is put here as a way to
 *  free allocated data when list_destroy is used.*/
void list_initialize(linkedList *list, void (*destroy)(void *data));
/* list_destroy
 * Return type : void
 * 
 * Description : Will destroy a list which is passed to it in the
 *  form of a pointer to a linkedList pointer. When a list has been
 *  destroyed, no more operations may be carried out unless the
 *  list_initialize function is called again. The list_destroy
 *  function removes all elements from the list, and calls the
 *  function passed in as destroy during the list_initialize, once
 *  for every element during the destroy process. Destroy will not
 *  be performed if the destroy function was passed in as NULL.
 *
 * Runtime : O(n)
 */
void list_destroy (linkedList *list);

/* list_insert_next
 * Return type : int - 0 = success,
 *                     1 = failure.
 * 
 * Description : Adds an element to the list (passed as "list")
 *  AFTER the element (passed as "element"). If "element" is NULL,
 *  then the new element will be added as the head of the list.
 *  The new element will contain a pointer to "data". This means the
 *  memory referenced by "data" needs to remain valid for the lifetime
 *  of the element in the list. It is the responsibility of the developer
 *  to manage this storage. 
 * 
 * Runtime : O(1)
 */ 
int list_insert_next (linkedList  *list,
                      listElement *element,
                      const void  *data);

/* list_remove_next
 * Return type : int - 0 = success,
 *                     1 = failure.
 *
 * Description : Removes the element form the list (passed as "list")
 *  AFTER the element (passed as "element"). If "element is NULL, then
 *  the element which represents the head of the list will be removed.
 *  When this function returns, "data" will still point to the data which
 *  was stored in the element which has been removed. It is the responsibility
 *  of the programmer to manage this storage. 
 *
 * Runtime : O(1)
 */
int list_remove_next (linkedList  *list,
                      listElement *listElement,
                      void	  **data); 

/* list_get_size
 * Return type : int - The number of elements in the linked list.
 *
 * Description : Gets the value of list->size and returns it.
 *
 * Runtime : O(1)
*/
int list_get_size(linkedList* list);

/* list_head
 * Return type : listElement* - Returns a pointer to the head element.
 * 
 * Runtime : O(1)
*/
listElement* list_head(linkedList* list);


/* list_tail
 * Return type : listElement* - Returns a pointer to the tail element.
 * 
 * Runtime : O(1)
*/
listElement* list_tail(linkedList* list);

/* list_is_head
 *
 * Return type : int 1 - Yes
 *                   0 - No
 * 
 * Runtime : O(1)
*/
int list_is_head (linkedList* list, listElement* element);

/* list_is_tail
 * Return type : int 1 - Yes
 *                   0 - No
 *
 * Runtime : O(1)
*/
int list_is_tail (linkedList* list, listElement* element);


/* list_data
 * Return type : The data within the element.
 *
 * Runtime : O(1)
*/
void* list_data(listElement* element);

/* list_next
 * Return type : The next node after the specified one
 * 
 * Runtime : O(1)
*/
listElement* list_next(listElement* element);
#endif
