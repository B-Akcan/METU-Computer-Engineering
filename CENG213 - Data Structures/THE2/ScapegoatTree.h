#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public:
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private:
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    int getHeight(Node<T> *r) const;
    int getSize(Node<T> *r) const;
    const T &get(const T &element, Node<T> *r) const;
    Node<T>* find_parent(Node<T> *n) const;
    void removeAllNodes(Node<T> *&r);
    bool exists(const T &e) const;
    const T &getMin(Node<T> *r) const;
    const T &getMax(Node<T> *r) const;
    void bst_insert(Node<T> *&r, T value);
    void bst_remove(Node<T> *&r, T value);
    int inorderElemArray(Node<T> *r, T *array, int i);
    int preorderElemArray(Node<T> *r, T *array, int i);
    Node<T> *rebuild_bst(T *array, int start, int end);
    const T &getCeiling(const T &element, Node<T> *r) const;
    const T &getFloor(const T &element, Node<T> *r) const;
    const T &getNext(const T &element, Node<T> *r) const;

private:
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    this->root = NULL;
    int sz = obj.getSize();
    Node<T> *rt = obj.root;
    T *arr = new T[sz];
    preorderElemArray(rt, arr, 0);
    for (int i=0; i<sz; i++)
        this->bst_insert(root, arr[i]);
    delete [] arr;
    upperBound = obj.upperBound;
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    removeAllNodes();
}

template<class T>
int ScapegoatTree<T>::preorderElemArray(Node<T> *r, T *array, int i)
{
    if (r == NULL)
        return i;
    array[i++] = r->element;
    i = preorderElemArray(r->left, array, i);
    return preorderElemArray(r->right, array, i);
}

template<class T>
int ScapegoatTree<T>::inorderElemArray(Node<T> *r, T *array, int i)
{
    if (r == NULL)
        return i;
    i = inorderElemArray(r->left, array, i);
    array[i++] = r->element;
    return inorderElemArray(r->right, array, i);
}

template<class T>
Node<T> *ScapegoatTree<T>::rebuild_bst(T *array, int start, int end)
{
    if (start > end)
        return NULL;
    
    int mid = (start+end)/2;
    Node<T> *rt = new Node<T>(array[mid], NULL, NULL);
    rt->left = rebuild_bst(array, start, mid-1);
    rt->right = rebuild_bst(array, mid+1, end);
    return rt;
}

template<class T>
void ScapegoatTree<T>::bst_insert(Node<T> *&r, T value)
{
    if (r == NULL)
        r = new Node<T>(value, NULL, NULL);
    else if (r->element < value)
        bst_insert(r->right, value);
    else if (r->element > value)
        bst_insert(r->left, value);
}

template<class T>
void ScapegoatTree<T>::bst_remove(Node<T> *&r, T value)
{
    if (r == NULL)
        return;
    else if (r->element > value)
        bst_remove(r->left, value);
    else if (r->element < value)
        bst_remove(r->right, value);
    else
    {    
        if (r->left != NULL && r->right != NULL)
        {
            r->element = getMax(r->left);
            bst_remove(r->left, r->element);
        }
        else
        {
            Node<T> *oldNode = r;
            r = (r->left != NULL)? r->left : r->right;
            delete oldNode;
        }
    }
}

template<class T>
Node<T>* ScapegoatTree<T>::find_parent(Node<T> *n) const
{
    if (!root)
        return NULL;
    else if (n->element == root->element)
        return NULL;
    
    Node<T> *curr = root, *parent=NULL;
    while (n->element != curr->element)
    {
        if (n->element < curr->element)
        {
            parent = curr;
            curr = curr->left;
        }
        else if (n->element > curr->element)
        {
            parent = curr;
            curr = curr->right;
        }
    }
    
    return parent;
}

template<class T>
bool ScapegoatTree<T>::exists(const T &e) const
{
    Node<T> *curr = root;
    while (curr != NULL)
    {
        if (e == curr->element)
            return true;
        else if (e > curr->element)
            curr = curr->right;
        else
            curr = curr->left;
    }
    return false;
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    return root == NULL ? true : false;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    return getHeight(root);
}

template<class T>
int ScapegoatTree<T>::getHeight(Node<T> *r) const {
    if (r == NULL)
        return -1;
    else
    {
        int lh = getHeight(r->left);
        int rh = getHeight(r->right);
        if (lh > rh)
            return 1+lh;
        else
            return 1+rh;
    }
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    return getSize(root);
}

template<class T>
int ScapegoatTree<T>::getSize(Node<T> *r) const {
    if (r == NULL)
        return 0;
    else if (!r->left && !r->right)
        return 1;
    else if (r->left && r->right)
        return 1+getSize(r->left)+getSize(r->right);
    else if (r->left)
        return 1+getSize(r->left);
    else if (r->right)
        return 1+getSize(r->right);
    return 0;
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    if (exists(element))
        return false;
        
    bst_insert(root, element);
    if (getHeight() > log(++upperBound)/log(1.5))
    {
        // Find scapegoat
        Node<T> *curr = root, *prnt;
        while (curr->element != element)
        {
            prnt = curr;
            if (curr->element < element)
                curr = curr->right;
            else if (curr->element > element)
                curr = curr->left;
        }
        while (3*getSize(prnt) <= 2*getSize(find_parent(prnt)))
            prnt = find_parent(prnt);
        Node<T> *scapegoat = find_parent(prnt);
        Node<T> *parent_of_sg = find_parent(scapegoat);
        
        // Rebuild
        int sz = getSize(scapegoat);
        T *arr = new T[sz];
        inorderElemArray(scapegoat, arr, 0);
        if (parent_of_sg == NULL)
        {
            removeAllNodes(scapegoat);
            root = rebuild_bst(arr, 0, sz-1);
        }
        else if (parent_of_sg->right == scapegoat)
        {
            removeAllNodes(scapegoat);
            parent_of_sg->right = rebuild_bst(arr, 0, sz-1);
        }
        else
        {
            removeAllNodes(scapegoat);
            parent_of_sg->left = rebuild_bst(arr, 0, sz-1);
        }
        delete [] arr;
        
    }
    return true;
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    if (!exists(element))
        return false;
    bst_remove(root, element);
    if (getSize() < upperBound/2.0 || getSize() > upperBound)
    {
        int sz = getSize();
        Node<T> *rt = root;
        T *arr = new T[sz];
        inorderElemArray(rt, arr, 0);
        removeAllNodes();
        root = rebuild_bst(arr, 0, sz-1);
        delete [] arr; 
        upperBound = getSize();
    }
    return true;
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    removeAllNodes(root);
    upperBound = 0;
}

template<class T>
void ScapegoatTree<T>::removeAllNodes(Node<T> *&r) {
    if (r != NULL)
    {
        removeAllNodes(r->left);
        removeAllNodes(r->right);
        delete r;
        r = NULL;
    }
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    return get(element, root);
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element, Node<T> *r) const {
    if (r == NULL) 
        throw NoSuchItemException();
    else if (element < r->element)
        return get(element, r->left);
    else if (element > r->element)
        return get(element, r->right);
    else
        return r->element;
}


template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        if (node == NULL)
            return;
        std::cout << "\t" << node->element;
        if (node->left)
            std::cout << "," << std::endl;
        print(node->left, preorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        
    } else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
          return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == postorder) {
        if (node == NULL)
            return;
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    if (this != &rhs)
    {
        this->removeAllNodes();
        int sz = rhs.getSize();
        Node<T> *rt = rhs.root;
        T *arr = new T[sz];
        preorderElemArray(rt, arr, 0);
        for (int i=0; i<sz; i++)
            this->bst_insert(root, arr[i]);
        
        delete [] arr;
        upperBound = rhs.upperBound;
    }
    return *this;
}

template<class T>
void ScapegoatTree<T>::balance() {
    int sz = getSize();
    Node<T> *rt = root;
    T *arr = new T[sz];
    inorderElemArray(rt, arr, 0);
    removeAllNodes();
    root = rebuild_bst(arr, 0, sz-1);
    delete [] arr;
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    if (isEmpty() || element > getMax())
        throw NoSuchItemException();
    else if (exists(element))
    {
        Node<T> *curr = root;
        while (curr != NULL)
        {
            if (element == curr->element)
                return curr->element;
            else if (element > curr->element)
                curr = curr->right;
            else
                curr = curr->left;
        }
    }
    else
        return getCeiling(element, root);
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element, Node<T> *r) const
{
    if (!r->left && !r->right)
    {
        if (r->element > element)
            return r->element;
        else
        {
            Node<T> *prnt = find_parent(r);
            while (prnt->element < element)
                prnt = find_parent(prnt);
            return prnt->element;
        }
    }
    else if (!r->left && r->element > element)
        return r->element;
    else if (r->right && r->element < element)
        return getCeiling(element, r->right);
    else if (!r->right && r->element < element)
    {
        Node<T> *prnt = find_parent(r);
        while (prnt->element < element)
            prnt = find_parent(prnt);
        return prnt->element;
    }
    else if (r->left && r->element > element)
        return getCeiling(element, r->left);
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    if (isEmpty() || element < getMin())
        throw NoSuchItemException();
    else if (exists(element))
    {
        Node<T> *curr = root;
        while (curr != NULL)
        {
            if (element == curr->element)
                return curr->element;
            else if (element > curr->element)
                curr = curr->right;
            else
                curr = curr->left;
        }
    }
    else
        return getFloor(element, root);
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element, Node<T> *r) const
{
    if (!r->left && !r->right)
    {
        if (r->element < element)
            return r->element;
        else
        {
            Node<T> *prnt = find_parent(r);
            while (prnt->element > element)
                prnt = find_parent(prnt);
            return prnt->element;
        }
    }
    else if (!r->right && r->element < element)
        return r->element;
    else if (!r->left && r->element > element)
    {
        Node<T> *prnt = find_parent(r);
        while (prnt->element > element)
            prnt = find_parent(prnt);
        return prnt->element;
    }
    else if (r->right && r->element < element)
        return getFloor(element, r->right);
    else if (r->left && r->element > element)
        return getFloor(element, r->left);
}

template<class T>
const T &ScapegoatTree<T>::getMin() const 
{
    return getMin(root);
}

template<class T>
const T &ScapegoatTree<T>::getMin(Node<T> *r) const {
    if (r == NULL)
        throw NoSuchItemException();
    Node<T> *curr = r;
    Node<T> *leaf;
    while (curr)
    {
        leaf = curr;
        curr = curr->left;
    }
    return leaf->element;
}

template<class T>
const T &ScapegoatTree<T>::getMax() const 
{
    return getMax(root);
}


template<class T>
const T &ScapegoatTree<T>::getMax(Node<T> *r) const {
    if (r == NULL)
        throw NoSuchItemException();
    Node<T> *curr = r;
    Node<T> *leaf;
    while (curr)
    {
        leaf = curr;
        curr = curr->right;
    }
    return leaf->element;
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    if (element >= getMax())
        throw NoSuchItemException();
    else
        return getNext(element, root);
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element, Node<T> *r) const
{
    if (!r->left && !r->right)
    {
        if (r->element > element)
            return r->element;
        else
        {
            Node<T> *prnt = find_parent(r);
            while (prnt->element <= element)
                prnt = find_parent(prnt);
            return prnt->element;
        }
    }
    else if (!r->left && r->element > element)
        return r->element;
    else if (!r->right && r->element <= element)
    {
        Node<T> *prnt = find_parent(r);
        while (prnt->element <= element)
            prnt = find_parent(prnt);
        return prnt->element;
    }
    else if (r->right && r->element <= element)
        return getNext(element, r->right);
    else if (r->left && r->element > element)
        return getNext(element, r->left);
}
    
