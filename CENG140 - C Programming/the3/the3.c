#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "the3.h"

#define MAX_SIZE 10

QueryNode *create_querynode(char query[5]);
CountNode *create_countnode(int count);
void insert_countNode_and_sort(CountNode **head, CountNode *new_node);
void insert_queryNode_and_sort(CountNode *cnode, QueryNode *new_node);
int query_exists(char query[5], CountNode *head);
int count_exists(int count, CountNode *head);
int find_count(char query[5], CountNode *head);
void print_contents(CountNode *head);

int main()
{
    CountNode *head = NULL, *count_curr, *new_cnode;
    QueryNode *new_qnode, *query_table[MAX_SIZE];
    int query_table_length, i, count;
    char query[5];
    
    scanf("%d", &query_table_length);
    for (i=0 ; i<query_table_length ; i++)
    {
        scanf("%s %d", query, &count);
        if (count_exists(count, head))
        {
            count_curr = head;
            while (count_curr -> count != count) count_curr = count_curr -> next;
            new_qnode = create_querynode(query);
            insert_queryNode_and_sort(count_curr, new_qnode);
        }
        else
        {
            new_cnode = create_countnode(count);
            insert_countNode_and_sort(&head, new_cnode);
            new_qnode = create_querynode(query);
            insert_queryNode_and_sort(new_cnode, new_qnode);
        }
        query_table[i] = new_qnode;
    }




    print_contents(head);
    return 0;
}

QueryNode *create_querynode(char query[5])
{
    QueryNode *pnode = malloc(sizeof(QueryNode));
    pnode -> query = query;
    pnode -> prev = NULL;
    pnode -> next = NULL;
    return pnode;
}

CountNode *create_countnode(int count)
{
    CountNode *pnode = malloc(sizeof(CountNode));
    pnode -> count = count;
    pnode -> prev = NULL;
    pnode -> next = NULL;
    pnode -> querylist = NULL;
    return pnode;
}

void insert_countNode_and_sort(CountNode **head, CountNode *new_node)
{
    CountNode *curr;
    if (*head == NULL) *head = new_node;
    else if ((*head) -> count >= new_node -> count)
    {
        QueryNode *temp;
        temp = *((*head) -> querylist);
        (*head) -> querylist = NULL;
        new_node -> next = *head;
        new_node -> next -> prev = new_node;
        *head = new_node;
        *(new_node -> next -> querylist) = temp;
    }
    else
    {
        QueryNode *temp;
        curr = *head;
        while (curr -> next && curr -> next -> count < new_node -> count) curr = curr -> next;
        temp = *(curr -> next -> querylist);
        *(curr -> next -> querylist) = NULL;
        new_node -> next = curr -> next;
        if (curr -> next) new_node -> next -> prev = new_node;
        curr -> next = new_node;
        new_node -> prev = curr;
        *(new_node -> next -> querylist) = temp;
    }
}

void insert_queryNode_and_sort(CountNode *cnode, QueryNode *new_node)
{
    QueryNode *curr;
    if (*(cnode -> querylist) == NULL) *(cnode -> querylist) = new_node;
    else if ((strcmp((*(cnode -> querylist)) -> query, new_node -> query)) >= 0)
    {
        new_node -> next = *(cnode -> querylist);
        new_node -> next -> prev = new_node;
        *(cnode -> querylist) = new_node;
    }
    else
    {
        curr = *(cnode -> querylist);
        while (curr -> next && (strcmp(curr -> next -> query, new_node -> query) < 0)) curr = curr -> next;
        new_node -> next = curr -> next;
        if (curr -> next) new_node -> next -> prev = new_node;
        curr -> next = new_node;
        new_node -> prev = curr;
    }
}

int query_exists(char query[5], CountNode *head)
{
    CountNode *ccurr = head;
    QueryNode *pcurr;
    while (ccurr)
    {
        pcurr = *ccurr -> querylist;
        do
        {
            if (!strcmp(pcurr -> query, query)) return 1;
            pcurr = pcurr -> next;
        } while (pcurr);
        ccurr = ccurr -> next;
    }
    return 0;
}

int count_exists(int count, CountNode *head)
{
    CountNode *ccurr;
    if (!head) return 0;
    else if (head -> count == count) return 1;
    else
    {
        ccurr = head;
        while (ccurr && ccurr -> count < count) ccurr = ccurr -> next;
        if (ccurr && ccurr -> count == count) return 1;
    } 
    return 0;
}

int find_count(char query[5], CountNode *head)
{
    CountNode *ccurr = head;
    QueryNode *pcurr;
    while (ccurr)
    {
        pcurr = *(ccurr -> querylist);
        do
        {
            if (!(strcmp(pcurr -> query, query))) return ccurr -> count;
            pcurr = pcurr -> next;
        } while (pcurr);
        ccurr = ccurr -> next;
    }
    return -1;
}

void print_contents(CountNode *head)
{
    CountNode *ccurr;
    QueryNode *qcurr;
    ccurr = head;
    while (ccurr)
    {
        printf("%d ", ccurr -> count);
        qcurr = *(ccurr -> querylist);
        while (qcurr)
        {
            printf("%s", qcurr -> query);
            if (qcurr -> next) printf(" ");
            qcurr = qcurr -> next;
        }
        printf("\n");
        ccurr = ccurr -> next;
    }
}