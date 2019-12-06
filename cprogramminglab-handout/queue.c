/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  (queue_t*)malloc(sizeof(queue_t));
    if(q == NULL)
	return NULL;
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->num = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *temp;
    list_ele_t *del;
    if(q == NULL)
       return;
    temp = q->head;
    del = temp;
    while(temp)
    {
	    temp = temp->next;
	    free(del->value);
	    free(del);
	    del = temp;
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
 /* What should you do if the q is NULL? */
    if(q == NULL)
      return false;   

    newh = (list_ele_t*)malloc(sizeof(list_ele_t));
    if(newh==NULL) return false;

    newh->value = (char*)malloc(strlen(s)+1);
    if(newh->value == NULL)
	{
	   free(newh);
	   return false;
	} 

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if(q->tail == NULL)
       q->tail = newh;
    strcpy( newh->value, s );
    q->num += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    if(q)
    {
	if( q->tail == NULL ) return q_insert_head(q, s);
        newt = (list_ele_t*)malloc(sizeof(list_ele_t));

    if(newt)
    	{

		 newt->value = (char*)malloc(strlen(s)+1);
		 if(newt->value)
		 {
		   newt->next = NULL;
		   q->tail->next = newt;
		   q->tail = newt;
		   strcpy( newt->value, s );
		   q->num += 1;
		   return true;
		 }
		 else free(newt);
    	}
    }
    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if(q == NULL || q->head ==NULL )
	    return false;

    list_ele_t *del;
    del = q->head;
    if(q->head == q->tail)
	q->tail = NULL;
    q->head = q->head->next;
    if(sp)
    {
	    if( strlen(del->value) >= bufsize )
		    del->value[bufsize-1] = '\0';
	    strcpy( sp, del->value );
    }
    free(del->value);
    free(del);
    q->num -= 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if( q == NULL )
	    return 0;
    return q->num;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
	list_ele_t *temp1;
	list_ele_t *temp2;
	list_ele_t *temp3;
	if( q && q->num > 0 )
	{
		/*First change the head and tail*/
		temp1 = q->head;
		q->head = q->tail;
		q->tail = temp1;
		temp2 = temp1->next;
		while( temp1 !=  q->head )
		{

			if(temp1 == q->tail) temp1->next = NULL;
			temp3 = temp2->next;
			temp2->next = temp1;
			temp1 = temp2;
			temp2 = temp3;
		}
	}
}

