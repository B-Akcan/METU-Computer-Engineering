#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    theSize=0;
    elements.resize(1);
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    HeapElement he = {uniqueId, weight};
    
    for (unsigned long int i=1; i<elements.size(); i++)
    {
        if (elements[i].uniqueId == he.uniqueId)
            return false;
    }
    
    elements[0] = he;
    if (theSize+1 == elements.size())
        elements.resize(elements.size()*2+1);
    
    int hole = ++theSize;
    while (he.weight < elements[hole/2].weight)
    {
        elements[hole] = elements[hole/2];
        hole /= 2;
    }
    elements[hole] = he;
    return true;
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    if (!theSize)
        return false;
    HeapElement tmp = elements[1];
    elements[1] = elements[theSize--];
    bubbleDown(1);
    outUniqueId = tmp.uniqueId;
    outWeight = tmp.weight;
    return true;
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    unsigned long int i;
    for (i=1; i<elements.size(); i++)
    {
        if (elements[i].uniqueId == uniqueId)
            break;
    }
    if (i == elements.size())
        return false;
    elements[i].weight = newWeight;
    
    HeapElement he = elements[i];
    elements[0] = he;
    int hole = i;
    while (he.weight < elements[hole/2].weight) // Bubble up
    {
        elements[hole] = elements[hole/2];
        hole /= 2;
    }
    elements[hole] = he;
    if (i*2 <= theSize)
        bubbleDown(i);
    return true;
}

int BinaryHeap::HeapSize() const
{
    return (int) theSize;
}

void BinaryHeap::bubbleDown(long unsigned int index)
{
    long unsigned int child;
    HeapElement tmp = elements[index];
    for (; index*2 <= theSize; index=child)
    {
        child = index*2;
        if (child != theSize && elements[child+1].weight < elements[child].weight)
            child++;
        if (elements[child].weight < tmp.weight)
            elements[index] = elements[child];
        else
            break;
    }
    elements[index] = tmp;
}