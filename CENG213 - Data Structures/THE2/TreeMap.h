#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "ScapegoatTree.h"

template<class K, class V>
class TreeMap {
public:
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    bool pop(const K &key);

    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &floorEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();

    void pollLastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

private:

private:
    ScapegoatTree<KeyValuePair<K, V> > stree;
};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    stree.removeAllNodes();
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    return stree.get(key).getValue();
}

template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) {
    return stree.remove(key);
}

template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) {
    KeyValuePair<K,V> nw(key, value);
    return stree.insert(nw);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    return stree.getCeiling(key);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) {
    return stree.getFloor(key);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    return stree.getMin();
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    return stree.getMax();
}

template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() {
    stree.remove(stree.getMin());
}

template<class K, class V>
void TreeMap<K, V>::pollLastEntry() {
    stree.remove(stree.getMax());
}

template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const {
    std::vector<KeyValuePair<K, V> > v;
    K curr = fromKey;
    while (curr != toKey)
    {
        v.push_back(stree.get(curr));
        curr = stree.getNext(stree.get(curr)).getKey();
    }
    v.push_back(stree.get(toKey));
    return v;
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# ScapegoatTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

#endif //TREEMAP_H
