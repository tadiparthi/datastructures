#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nil 0

typedef struct linkedlist_t linkedlist_t;
struct linkedlist_t 
{
	int		data;
	linkedlist_t 	*next;
};

void
adddata(linkedlist_t **head, int data)
{
	linkedlist_t	*ptr;
	ptr = (linkedlist_t*) malloc(sizeof(linkedlist_t));
	if(!ptr) return;
	memset(ptr, 0, sizeof(linkedlist_t));
	ptr->data = data;
	ptr->next = *head;
	*head = ptr;
}

void
deletedata(linkedlist_t **head, int data)
{
	linkedlist_t	**p, *l, *tmp;

	p = head;
	for(p = head, l = *p ; l != nil ; l = tmp) {
		tmp = l->next;
		if(l->data == data) {
			*p = l->next;
			free(l);
		} else {
			p = &l->next;
		}
	}
}

void
printlist(linkedlist_t *head)
{

	if(!head) {
		printf("head is empty\n");
		return;
	}
	for(; head; head = head->next)
		printf(" %d", head->data);

	printf("\n");
}

void
reverselist(linkedlist_t **head)
{
	linkedlist_t *a, *b, *c;

	if(!head || !(*head) || !((*head)->next))
		return;
	
	a = *head;
	b = (*head)->next;
	c = nil;

	while(a) {
		b = a->next;
		a->next = c;
		c = a;
		a = b;
	}

	*head = c;
}

linkedlist_t *
reverse_helper(linkedlist_t *head, linkedlist_t *next)
{
	linkedlist_t *t;

	if(head == nil)
		return next;

	t = head->next;
	head->next = next;
	return reverse_helper(t, head);
}

linkedlist_t*
reverselist_recurse(linkedlist_t *head)
{

	return reverse_helper(head, nil);
}

linkedlist_t*
mergelists(linkedlist_t *list1, linkedlist_t *list2)
{
	linkedlist_t dummy;
	linkedlist_t *ptr, *p1, *p2;

	ptr = &dummy;
	ptr->next = nil;

	p1 = list1;
	p2 = list2;

	while(p1 && p2) {
		if(p1->data <= p2->data) {
			ptr->next = p2;
			p2 = p2->next;
		} else {
			ptr->next = p1;
			p1 = p1->next;
		}
		ptr = ptr->next;
	}

	if(p1) {
		ptr->next = p1;
	}
	if(p2) {
		ptr->next = p2;
	}

	return dummy.next;
}

     linkedlist_t* reversek_helper(linkedlist_t *pre, linkedlist_t *next){

        linkedlist_t* last=pre->next;
        linkedlist_t* cur=last->next;
        
        while (cur != next){
            
            last->next=cur->next;
            cur->next=pre->next;
            pre->next=cur;
            
            cur=last->next;
        }
        return last;
    }
    linkedlist_t* reverseKGroup(linkedlist_t* head, int k) {
        if (head == nil || k == 1){
            return head;
        }
        
        linkedlist_t dummy ;
        dummy.next=head;
        
        linkedlist_t* pre = &dummy;
        
        int i = 0;
        while (head != nil){
            i++;
            
            if (i%k==0){
                pre = reversek_helper(pre,head->next);
                head = pre->next;
            }
            else {
                head = head->next;
            }
        }
        return dummy.next;
    }


	/*
	 * insertion sort of linked list1
	 */
    linkedlist_t* insertionSortList(linkedlist_t* head) {
        if(head == nil || head->next == nil)
            return head;

        linkedlist_t* sorted = nil;
        
        while(head) {
            linkedlist_t *p = head;
            linkedlist_t **pp = &sorted;
            head = head->next;
            
            while(!(*pp == nil || p->data < (*pp)->data))
                *pp = &((*pp)->next);
            
            head->next = *pp;
            *pp = head;
        }
        
        return sorted;
    }

	
linkedlist_t* SortedMerge(linkedlist_t* a, linkedlist_t* b)
{
  linkedlist_t* result = NULL;
 
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
 
  if (a->data <= b->data)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}

void FrontBackSplit(linkedlist_t* source,
          linkedlist_t** frontRef, linkedlist_t** backRef)
{
  linkedlist_t* fast;
  linkedlist_t* slow;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}

void MergeSort(linkedlist_t** headRef)
{
  linkedlist_t* head = *headRef;
  linkedlist_t* a;
  linkedlist_t* b;
 
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
 
  FrontBackSplit(head, &a, &b); 
 
  MergeSort(&a);
  MergeSort(&b);
 
  *headRef = SortedMerge(a, b);
}
 

	
void main()
{
	int i;
	linkedlist_t *head = nil;
	linkedlist_t *list1 = nil, *list2 = nil;

#if 0
	for(i = 30; i < 40; i++) 
		adddata(&list1, i);
	for(i = 11; i < 20; i++)
		adddata(&list2, i);
#endif

	for(i = 20; i < 40; i++) {
		if(i & 1) {
			adddata(&list1, i);
		} else {
			adddata(&list2, i);
		}
	}

#if 0
	for(i = 1; i < 10; i++) {
		printlist(head);
		deletedata(&head, i);
	}
#endif

	printlist(list1);
	printlist(list2);

//	reverselist(&head);
	
//	deletedata(&head, 1);

	head = mergelists(list2, list1);

	printlist(head);

	head = reverselist_recurse(head);	
	printlist(head);
}
