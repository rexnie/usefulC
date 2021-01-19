#include <stdio.h>
#include <stdlib.h>
// https://www.dotcpp.com/course/98

// 双向链表
typedef struct _dlink {
    int val;
    struct _dlink *pre, *next;
} dlink;

dlink *make_empty_dlink(dlink *head)
{
    dlink *tmp = NULL;

    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return head;
}

/* find first node with value x
 * return pointer to node, null if not found or empty dlink
 **/
dlink *find_x_node(dlink *head, int x)
{
    dlink *tmp = head;

    while (tmp) {
        if (tmp->val == x)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}

dlink *insert_after_pre(dlink *head, dlink *pre, dlink *p)
{
    if (p == NULL) {
        printf("insert null to dlink\n");
        return head;
    }

    if (head == NULL) { /* insert to empty dlink */
        p->next = NULL;
        p->pre = NULL;
        head = p;
        return head;
    }

    if (pre == NULL) { /* insert to head of dlink */
        p->next = head;
        head->pre = p;
        p->pre = NULL;
        head = p; /* head changed */
    } else if (pre->next == NULL) { /* insert to tail of dlink */
        pre->next = p;
        p->pre = pre;
        p->next = NULL;
    } else { /* insert middle of dlink */
        pre->next->pre = p;
        p->next = pre->next;
        pre->next = p;
        p->pre = pre;
    }

    return head;
}

dlink *insert_to_head_of_dlink(dlink *head, int val)
{
    dlink *tmp = NULL;

    tmp = malloc(sizeof(dlink));
    if (tmp == NULL) {
        printf("malloc err\n");
        return head;
    }

    tmp->val = val;

    return insert_after_pre(head, NULL, tmp);
}

dlink *insert_after_x_node(dlink *head, int x, int val)
{
    dlink *px= NULL, *tmp = NULL;

    px = find_x_node(head, x);
    if (px == NULL) {
        printf("not found, or empty dlink, DO NOT insert\n");
        return head;
    }

    tmp = malloc(sizeof(dlink));
    if (tmp == NULL) {
        printf("malloc err\n");
        return head;
    }

    tmp->val = val;

    return insert_after_pre(head, px, tmp);
}

dlink *insert_before_x_node(dlink *head, int x, int val)
{
    dlink *px = NULL, *tmp = NULL;

    px = find_x_node(head, x);
    if (px == NULL) {
        printf("not found, or empty dlink, DO NOT insert\n");
        return head;
    }

    tmp = malloc(sizeof(dlink));
    if (tmp == NULL) {
        printf("malloc err\n");
        return head;
    }

    tmp->val = val;

    return insert_after_pre(head, px->pre, tmp);
}

dlink *delete_x_node(dlink *head, int x)
{
    dlink *px = NULL, *tmp = NULL;

    px = find_x_node(head, x);
    if (px == NULL) {
        printf("not found, or empty dlink, CAN NOT delete\n");
        return head;
    }

    if (px->pre == NULL && px->next == NULL) { /* only one node */
        head = NULL;
    } else if (px->pre == NULL) { /* px is head */
        head = px->next;
        head->pre = NULL;
    } else if (px->next == NULL) { /* px is tail */
        px->pre->next = NULL;
    } else {
        px->next->pre = px->pre;
        px->pre->next = px->next;
    }

    free(px);
    px = NULL;

    return head;
}

void print_dlink(dlink *head)
{
    dlink *tmp = head;

    while(tmp != NULL) {
        printf("%d\n", tmp->val);
        tmp = tmp->next;
    }
}

#define no_duplicated_inner

static int delete_node_by_pattern(dlink **pHead, int pattern)
{
    int ret = 0;
    dlink *pNode = *pHead, *tmp;

    if(NULL == *pHead)   return 0;

    while(NULL != pNode)
    {
        if(pNode->val == pattern) {
            tmp = pNode->next;
            if(NULL == pNode->pre && NULL == pNode->next) { /* only one node to delete */
                *pHead = NULL;
                tmp = NULL;
            } else if (NULL == pNode->pre) { /* first node */
                *pHead = pNode->next;
                (*pHead)->pre = NULL;
            } else if(NULL == pNode->next) { /* tail node */
                pNode->pre->next = NULL;
            } else {
                pNode->pre->next = pNode->next;
                pNode->next->pre = pNode->pre;
            }
            free (pNode);
            ret = 1;

#ifdef no_duplicated_inner
            break; /*如果指明了B中的节点值都唯一，可以break; 如果B中的节点值有相同的，应该删除break; */
#else
            pNode = tmp;
#endif
        } else {
                pNode = pNode->next;
        }
    }
    return ret;
}


void delete_duplicated_between_linked_lists(dlink **pHeadA, dlink **pHeadB)
{
    dlink *pNode = *pHeadA, *pNextNode;
    if ( ( NULL == *pHeadA) || (NULL == *pHeadB) ) return;

    while(NULL != pNode)
    {
        if(delete_node_by_pattern(pHeadB, pNode->val))
        {
            if(NULL == pNode->pre && NULL == pNode->next) { /* only one node */
                *pHeadA = NULL;
                free(pNode);
                return;
            } else if(NULL == pNode->pre){ /* first node */
                *pHeadA = pNode->next;
                (*pHeadA)->pre = NULL;
            } else if (NULL == pNode->next) { /* tail node */
                pNode->pre->next = NULL;
            } else {
                pNode->pre->next = pNode->next;
                pNode->next->pre = pNode->pre;
            }
#ifdef no_duplicated_inner
            pNextNode = pNode->next;
            free (pNode);  /*如果指明了A链表中的节点值都唯一*/
            pNode = pNextNode;
#else
            delete_node_by_pattern(pHeadA, pNode->val);
#endif
        } else {
                pNode = pNode->next;
        }
    }
}

int main(void)
{
   dlink *head = NULL;
   dlink *headA = NULL, *headB = NULL;

   head = make_empty_dlink(head);

   headA = make_empty_dlink(headA);
   headB = make_empty_dlink(headB);

#define TCASE 10
#if TCASE == 1
   /* 头插法建立双链表
    * 4 3 2 1
    */
   head = insert_to_head_of_dlink(head, 4);
   head = insert_to_head_of_dlink(head, 3);
   head = insert_to_head_of_dlink(head, 2);
   head = insert_to_head_of_dlink(head, 1);

   print_dlink(head);
#endif

#if TCASE == 2
   /* 在指定值x节点后插入新节点
    * 4 3 2 1
    */
   head = insert_to_head_of_dlink(head, 4);
   head = insert_after_x_node(head, 4, 3);
   head = insert_after_x_node(head, 3, 2);
   head = insert_after_x_node(head, 2, 1);

   print_dlink(head);
#endif

#if TCASE == 3
   /* 在指定值x节点前插入新节点
    * 1 2 3 4
    */

   head = insert_to_head_of_dlink(head, 4);
   head = insert_before_x_node(head, 4, 3);
   head = insert_before_x_node(head, 3, 2);
   head = insert_before_x_node(head, 2, 1);

   print_dlink(head);
#endif

#if TCASE == 4
   /* 在指定值x节点前插入新节点
    * 1 2 3 4
    */
   head = insert_to_head_of_dlink(head, 4);
   head = insert_before_x_node(head, 4, 3);
   head = insert_before_x_node(head, 3, 2);
   head = insert_before_x_node(head, 2, 1);

   print_dlink(head);
#endif

#if TCASE == 5
   /* 删除只有一个节点
    */
   head = insert_to_head_of_dlink(head, 4);
   print_dlink(head);
   head = delete_x_node(head, 3); /* not exist */
   head = delete_x_node(head, 4);

   printf("after delete:\n");
   print_dlink(head);
#endif

#if TCASE == 6
   /* 删除只有一个节点
    */
   head = insert_to_head_of_dlink(head, 4);
   print_dlink(head);
   head = delete_x_node(head, 3); /* not exist */
   head = delete_x_node(head, 4);

   printf("after delete:\n");
   print_dlink(head);
#endif

#if TCASE == 7
   /* 删除头节点
    * 4
    */
   head = insert_to_head_of_dlink(head, 4);
   head = insert_to_head_of_dlink(head, 3);
   print_dlink(head);
   head = delete_x_node(head, 3);

   printf("after delete:\n");
   print_dlink(head);
#endif

#if TCASE == 8
   /* 删除尾节点
    * 3
    */
   head = insert_to_head_of_dlink(head, 4);
   head = insert_to_head_of_dlink(head, 3);
   print_dlink(head);
   head = delete_x_node(head, 4);

   printf("after delete:\n");
   print_dlink(head);
#endif

#if TCASE == 9
   /* 删除中间节点
    * 2 4
    */
   head = insert_to_head_of_dlink(head, 4);
   head = insert_to_head_of_dlink(head, 3);
   head = insert_to_head_of_dlink(head, 2);
   print_dlink(head);
   head = delete_x_node(head, 3);

   printf("after delete:\n");
   print_dlink(head);
#endif

#if TCASE == 10
   /* 删除两个链表中具有相同值的节点
    */
   headA = insert_to_head_of_dlink(headA, 4);
   headA = insert_to_head_of_dlink(headA, 3);
   headA = insert_to_head_of_dlink(headA, 2);

   headB = insert_to_head_of_dlink(headB, 2);
   headB = insert_to_head_of_dlink(headB, 5);
   headB = insert_to_head_of_dlink(headB, 1);

   printf("A:\n");
   print_dlink(headA);
   printf("B:\n");
   print_dlink(headB);

   delete_duplicated_between_linked_lists(&headA, &headB);

   printf("after delete\n");
   printf("A:\n");
   print_dlink(headA);
   printf("B:\n");
   print_dlink(headB);
#endif

   make_empty_dlink(head);

   make_empty_dlink(headA);
   make_empty_dlink(headB);

   return 0;
}
