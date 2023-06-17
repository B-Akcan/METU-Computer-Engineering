#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private:
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    this->head = NULL;
    this->size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    this->head = NULL;
    this->append(obj.head->data);
    Node<T> *curr = obj.head->next;
    while (curr != obj.head)
    {
        this->append(curr->data);
        curr = curr->next;
    }
    this->size = obj.size;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    if (head == NULL) return;
    else if (head->next == head)
    {
        Node<T> *curr = head;
        curr->next = NULL;
        curr->prev = NULL;
        delete curr;
        head = NULL;
    }
    else
    {
        Node<T> *curr=this->head, *tmp;
        head->prev->next = NULL;
        this->head = NULL;
        while (curr)
        {
            tmp = curr;
            curr = curr->next;
            if (tmp->next) tmp->next = NULL;
            if (tmp->prev) tmp->prev = NULL;
            if (curr) curr->prev = NULL;
            delete tmp;
        }
    }
    this->size = 0;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if (this != &rhs)
    {
        this->removeAllNodes();
        this->append(rhs.head->data);
        Node<T> *curr = rhs.head->next;
        while (curr != rhs.head)
        {
            this->append(curr->data);
            curr = curr->next;
        }
        this->size = rhs.size;
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return this->size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    if (this->head == NULL) return true;
    return false;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    if (head == NULL || node == NULL) return false;
    else if (head->data == node->data) return true;
    else
    {
        Node<T>* curr = head->next;
        while (curr != head)
        {
            if (curr->data == node->data) return true;
            curr = curr->next;
        }
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    return this->head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if (this->isEmpty()) return NULL;
    return head->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    if (head == NULL) return NULL;
    else if (head->data == data)
    {
        Node<T>* curr=head;
        return curr;
    }
    else if (size > 1)
    {
        Node<T>* curr=head->next;
        while (curr != head)
        {
            if (curr->data == data) return curr;
            curr = curr->next;
        }
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    if (head == NULL) return NULL;
    else if (index < 0 || index >= size) return NULL;
    else if (index == 0)
    {
        Node<T>* curr = head;
        return curr;
    }
    else
    {
        Node<T>* curr = head->next;
        int i=1;
        while (curr != head)
        {
            if (i == index) return curr;
            i++;
            curr = curr->next;
        }
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    if (head == NULL)
    {
        Node<T>* new_node = new Node<T>(data);
        new_node->next = new_node;
        new_node->prev = new_node;
        head = new_node;
    }
    else if (head->next == head)
    {
        Node<T>* curr = head;
        Node<T>* new_node = new Node<T>(data, curr, curr);
        curr->next = new_node;
        curr->prev = new_node;
    }
    else
    {
        Node<T>* last = head->prev, *first = head;
        Node<T>* new_node = new Node<T>(data, last, first);
        last->next = new_node;
        first->prev = new_node;
    }
    this->size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    if (head == NULL)
    {
        Node<T>* new_node = new Node<T>(data);
        new_node->next = new_node;
        new_node->prev = new_node;
        head = new_node;
    }
    else if (head->next == head)
    {
        Node<T>* curr = head;
        Node<T>* new_node = new Node<T>(data, curr, curr);
        curr->prev = new_node;
        curr->next = new_node;
        head = new_node;
    }
    else
    {
        Node<T>* second = head, *last = head->prev;
        Node<T>* new_node = new Node<T>(data, last, second);
        second->prev = new_node;
        last->next = new_node;
        head = new_node;
    }
    this->size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if (!this->containsNode(node)) return;
    
    Node<T>* new_node = new Node<T>(data);
    Node<T>* curr = this->getNode(node->data);
    Node<T>* tmp = curr->next;
    curr->next = new_node;
    new_node->prev = curr;
    new_node->next = tmp;
    tmp->prev = new_node;
    this->size++;
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    if (index > this->size) return;

    else if (index == 0 && size == 0)
    {
        Node<T> *new_node = new Node<T>(data);
        new_node->next = new_node;
        new_node->prev = new_node;
        head = new_node;
    }
    else if (index == 0 && size == 1)
    {
        Node<T> *curr = head, *new_node = new Node<T>(data, curr, curr);
        curr->next = new_node;
        curr->prev = new_node;
        head = new_node;
    }
    else if (index == 1 && size == 1)
    {
        Node<T> *curr = head, *new_node = new Node<T>(data, curr, curr);
        curr->next = new_node;
        curr->prev = new_node;
    }
    else if (index == 0 && size > 1)
    {
        Node<T> *prv = head->prev, *nxt = head;
        Node<T> *new_node = new Node<T>(data, prv, nxt);
        prv->next = new_node;
        nxt->prev = new_node;
        head = new_node;
    }
    else if (index == size && size > 1)
    {
        Node<T> *prv = getNodeAtIndex(index-1), *nxt = head;
        Node<T> *new_node = new Node<T>(data, prv, nxt);
        prv->next = new_node;
        nxt->prev = new_node;
    }
    else
    {
        Node<T> *prv = getNodeAtIndex(index-1), *nxt = getNodeAtIndex(index);
        Node<T> *new_node = new Node<T>(data, prv, nxt);
        prv->next = new_node;
        nxt->prev = new_node;
    }
    this->size++;
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    if (head->data == node->data) return 0;
    int i=1;
    Node<T>* curr = head->next;
    while (curr != head)
    {
        if (curr->data == node->data)
            return i;
        curr = curr->next;
        i++;
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (currentIndex > this->size-1 || currentIndex < 0) return;
    else if (size <= 1) return;
    else if (newIndex < 0) return;
    if (newIndex > size-1)
        newIndex = size-1;
    if (currentIndex == newIndex) return;
    
    Node<T>* node1 = getNodeAtIndex(currentIndex);
    Node<T> *node2 = getNodeAtIndex(newIndex);

    if (currentIndex == 0 && newIndex == size-1)
        head = node1->next;
    else if (currentIndex == size-1 && newIndex == 0)
        head = node1;
    else if (size == 3 && currentIndex == 0 && newIndex == 1)
    {
        Node<T> *last = node2->next;
        node1->next = last;
        last->prev = node1;
        node2->next = node1;
        node1->prev = node2;
        node2->prev = last;
        last->next = node2;
        head = node2;
    }
    else if (size == 3 && currentIndex == 1 && newIndex == 0)
    {
        Node<T> *last = node1->next;
        node1->next = node2;
        node2->prev = node1;
        node2->next = last;
        last->prev = node2;
        node1->prev = last;
        last->next = node1;
        head = node1;
    }
    else if (size == 3 && currentIndex == 1 && newIndex == 2)
    {
        Node<T> *first = head;
        first->next = node2;
        node2->prev = first;
        node1->prev = node2;
        node2->next = node1;
        node1->next = first;
        first->prev = node1;
    }
    else if (size == 3 && currentIndex == 2 && newIndex == 1)
    {
        Node<T> *first = head;
        first->next = node1;
        node1->prev = first;
        node1->next = node2;
        node2->prev = node1;
        node2->next = first;
        first->prev = node2;
    }
    else if (size == 4 && currentIndex == 0 && newIndex == 2)
    {
        Node<T> *last = node2->next, *middle = node1->next;
        node2->next = node1;
        node1->prev = node2;
        node1->next = last;
        last->prev = node1;
        middle->prev = last;
        last->next = middle;
        head = middle;
    }
    else if (size == 4 && currentIndex == 1 && newIndex == 3)
    {
        Node<T> *first = head, *middle = node1->next;
        first->next = middle;
        middle->prev = first;
        node2->next = node1;
        node1->prev = node2;
        node1->next = first;
        first->prev = node1;
    }
    else if (size == 4 && currentIndex == 2 && newIndex == 0)
    {
        Node<T> *middle = node2->next, *last = node1->next;
        node1->next = node2;
        node2->prev = node1;
        middle->next = last;
        last->prev = middle;
        node1->prev = last;
        last->next = node1;
        head = node1;
    }
    else if (size == 4 && currentIndex == 3 && newIndex == 1)
    {
        Node<T> *first = head, *middle = node1->prev;
        first->next = node1;
        node1->prev = first;
        node1->next = node2;
        node2->prev = node1;
        first->prev = middle;
        middle->next = first;
    }
    else if (currentIndex == 0 && newIndex == size-2)
    {
        Node<T> *last = node1->prev, *n1_n = node1->next;
        node2->next = node1;
        node1->prev = node2;
        node1->next = last;
        last->prev = node1;
        n1_n->prev = last;
        last->next = n1_n;
        head = n1_n;
    }
    else if (currentIndex == size-2 && newIndex == 0)
    {
        Node<T> *last = node1->next, *n1_p = node1->prev;
        node1->next = node2;
        node2->prev = node1;
        n1_p->next = last;
        last->prev = n1_p;
        last->next = node1;
        node1->prev = last;
        head = node1;
    }
    else if (currentIndex == 1 && newIndex == size-1)
    {
        Node<T> *first = head, *n1_n = node1->next;
        first->next = n1_n;
        n1_n->prev = first;
        node2->next = node1;
        node1->prev = node2;
        first->prev = node1;
        node1->next = first;
    }
    else if (currentIndex == size-1 && newIndex == 1)
    {
        Node<T> *n1_p = node1->prev, *first = head;
        first->next = node1;
        node1->prev = first;
        node1->next = node2;
        node2->prev = node1;
        n1_p->next = first;
        first->prev = n1_p;
    }
    else if (currentIndex+1 == newIndex)
    {
        Node<T> *n1_p = node1->prev, *n2_n = node2->next;
        node2->next = node1;
        node1->prev = node2;
        node1->next = n2_n;
        n2_n->prev = node1;
        node2->prev = n1_p;
        n1_p->next = node2;
        if (currentIndex == 0)
            head = node2;
    }
    else if (currentIndex-1 == newIndex)
    {
        Node<T> *n1_n = node1->next, *n2_p = node2->prev;
        node1->next = node2;
        node2->prev = node1;
        node1->prev = n2_p;
        n2_p->next = node1;
        node2->next = n1_n;
        n1_n->prev = node2;
        if (newIndex == 0)
            head = node1;
    }
    else if (currentIndex+2 == newIndex)
    {
        Node<T> *n1_p = node1->prev, *middle = node1->next, *n2_n = node2->next;
        node2->next = node1;
        node1->prev = node2;
        node1->next = n2_n;
        n2_n->prev = node1;
        middle->prev = n1_p;
        n1_p->next = middle;
        if (currentIndex == 0)
            head = middle;
    }
    else if (currentIndex-2 == newIndex)
    {
        Node<T> *n1_n = node1->next, *middle = node1->prev, *n2_p = node2->prev;
        node1->next = node2;
        node2->prev = node1;
        middle->next = n1_n;
        n1_n->prev = middle;
        node1->prev = n2_p;
        n2_p->next = node1;
        if (newIndex == 0)
            head = node1;
    }
    else if (currentIndex < newIndex)
    {
        Node<T> *n1_n = node1->next, *n1_p = node1->prev, *n2_n = node2->next;
        n1_p->next = n1_n;
        n1_n->prev = n1_p;
        node2->next = node1;
        node1->prev = node2;
        node1->next = n2_n;
        n2_n->prev = node1;
        if (currentIndex == 0)
            head = n1_n;
    }
    else if (currentIndex > newIndex)
    {
        Node<T> *n1_n = node1->next, *n1_p = node1->prev, *n2_p = node2->prev;
        n2_p->next = node1;
        node1->prev = n2_p;
        node1->next = node2;
        node2->prev = node1;
        n1_p->next = n1_n;
        n1_n->prev = n1_p;
        if (newIndex == 0)
            head = node1;
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if (this->isEmpty()) return;
    else if (!this->containsNode(node)) return;
    else if (this->getSize() == 1)
    {
            delete head;
            head = NULL;
            this->size--;
    }
    else if (this->getSize() == 2 && head->data == node->data && head->prev->data == node->prev->data && head->next->data == node->next->data)
    {
        Node<T> *nxt = head->next, *tmp=head;
        nxt->prev = nxt;
        nxt->next = nxt;
        head = nxt;
        delete tmp;
        this->size--;
    }
    else if (this->getSize() == 2)
    {
        Node<T> *tmp=head->next;
        head->next = head;
        head->prev = head;
        delete tmp;
        this->size--;
    }
    else if (this->getSize() > 2 && head->data == node->data && head->prev->data == node->prev->data && head->next->data == node->next->data)
    {
        Node<T> *nxt = head->next, *prv = head->prev, *tmp=head;
        nxt->prev = prv;
        prv->next = nxt;
        head = nxt;
        delete tmp;
        this->size--;
    }
    else if (this->getSize() > 2)
    {
        Node<T>* curr = head->next;
        while (curr != head)
        {
            if (curr->data == node->data && curr->prev->data == node->prev->data && curr->next->data == node->next->data)
            {
                Node<T>* prv = curr->prev, *nxt = curr->next;
                prv->next = nxt;
                nxt->prev = prv;
                delete curr;
                this->size--;
                break;
            }
            else
                curr = curr->next;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    if (!this->getNode(data)) return;
    else if (this->size == 1)
    {
        delete head;
        head = NULL;
        this->size--;
    }
    else if (this->size == 2 && head->data == data)
    {
        Node<T> *curr = head->next, *tmp = head;
        curr->next = curr;
        curr->prev = curr;
        delete tmp;
        head = curr;
        this->size--;
    }
    else if (this->size == 2)
    {
        Node<T> *tmp = head->next, *curr = head;
        curr->next = curr;
        curr->prev = curr;
        delete tmp;
        this->size--;
    }
    else if (this->size > 2 && head->data == data)
    {
        Node<T> *tmp = head, *prv = head->prev, *nxt = head->next;
        nxt->prev = prv;
        prv->next = nxt;
        delete tmp;
        head = nxt;
        this->size--;
    }
    else
    {
        Node<T> *curr = this->getNode(data);
        Node<T> *prv = curr->prev, *nxt = curr->next;
        prv->next = nxt;
        nxt->prev = prv;
        delete curr;
        this->size--;
    }
    removeNode(data);
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if (this->isEmpty()) return;
    else if (index > this->size-1) return;
    else if (index == 0 && this->size == 1)
    {
        delete head;
        head = NULL;
        this->size--;
    }
    else if (index == 0 && this->size == 2)
    {
        Node<T> *curr = head->next, *tmp = head;
        curr->next = curr;
        curr->prev = curr;
        delete tmp;
        head = curr;
        this->size--;
    }
    else if (index == 1 && this->size == 2)
    {
        Node<T> *curr = head, *tmp = head->next;
        curr->next = curr;
        curr->prev = curr;
        delete tmp;
        this->size--;
    }
    else if (index == 0 && this->size > 2)
    {
        Node<T> *tmp = head, *prv = head->prev, *nxt = head->next;
        prv->next = nxt;
        nxt->prev = prv;
        delete tmp;
        head = nxt;
        this->size--;
    }
    else if (this->size > 2)
    {
        Node<T> *curr = getNodeAtIndex(index);
        Node<T> *prv = curr->prev, *nxt = curr->next;
        prv->next = nxt;
        nxt->prev = prv;
        delete curr;
        this->size--;
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    if (head == NULL) return;
    else if (head->next == head)
    {
        Node<T> *curr = head;
        curr->next = NULL;
        curr->prev = NULL;
        delete curr;
        head = NULL;
    }
    else
    {
        Node<T> *curr=this->head, *tmp;
        head->prev->next = NULL;
        this->head = NULL;
        while (curr)
        {
            tmp = curr;
            curr = curr->next;
            if (tmp->next) tmp->next = NULL;
            if (tmp->prev) tmp->prev = NULL;
            if (curr) curr->prev = NULL;
            delete tmp;
        }
    }
    this->size = 0;
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif