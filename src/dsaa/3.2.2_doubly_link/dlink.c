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

int main(void)
{
   dlink *head = NULL;

   head = make_empty_dlink(head);

#define TCASE 9
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

   make_empty_dlink(head);

   return 0;
}
