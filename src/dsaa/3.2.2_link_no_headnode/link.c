#include <stdio.h>
#include <stdlib.h>
// reverse algo: http://c.biancheng.net/view/8105.html

// 无头节点链表
typedef struct _link {
    int val;
    struct _link *next;
} link;

link *make_empty_link(link *head)
{
    link *tmp = NULL;

    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return head;
}

link *insert_to_front(link *head, int val)
{
    link *tmp = NULL;

    tmp = malloc(sizeof(link));
    if (tmp == NULL) {
        printf("malloc err\n");
        return head;
    }

    tmp->val = val;

    tmp->next = head;
    head = tmp;

    return head;
}

void print_link(link *head)
{
    link *tmp = head;

    while(tmp != NULL) {
        printf("%d\n", tmp->val);
        tmp = tmp->next;
    }
}

//迭代反转法，head 为无头节点链表的头指针
link * iteration_reverse(link* head) {
    link *post = NULL, *pre = NULL;
    link *cur = head;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    while (cur) {
        pre = cur->next; //save cur->next
        cur->next = post;

        post = cur;
        cur = pre;
    }
    head = post;
    return head;
}

// 头插法实现链表反转
link *head_reverse(link * head)
{
    link * new_head = NULL;
    link * temp = NULL;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    while (head != NULL)
    {
        temp = head;
        //将 temp 从 head 中摘除
        head = head->next;
        //将 temp 插入到 new_head 的头部
        temp->next = new_head;
        new_head = temp;
    }
    return new_head;
}

link *local_reverse(link * head)
{
    link *cur, *pre;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    cur = head->next;
    head->next = NULL;

    while(cur) {
        pre = cur->next;
        cur->next = head;
        head = cur;
        cur = pre;
    }

    return head;
}


int main(void)
{
   link *head = NULL;

   head = make_empty_link(head);

   head = insert_to_front(head, 4);
   head = insert_to_front(head, 3);
   head = insert_to_front(head, 2);
   head = insert_to_front(head, 1);

   print_link(head);

   //head = iteration_reverse(head);
   //head = head_reverse(head);
   head = local_reverse(head);

   printf("after reverse:\n");
   print_link(head);
   make_empty_link(head);

   return 0;
}
