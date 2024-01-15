#include "the5.h"

// do not add extra libraries here

template <typename T>
class Stack {
public:
    std::vector<T> elements;

public:
    void push(const T& value) {
        elements.push_back(value);
    }

    void pop() {
        if (!empty()) {
            elements.pop_back();
        }
    }

    T top() const {
        if (!empty()) {
            return elements.back();
        } else {
            return 0;
        }
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

void run(const std::vector<std::vector<int>>& dependencyMatrix, 
         bool& isCompilable,
         std::vector<int>& compileOrder, 
         std::vector<std::vector<int>>& cyclicDependencies)
{
    int numFiles = dependencyMatrix.size();
    std::vector<int> inDegree(numFiles, 0);
    std::vector<std::vector<int>> adjList(numFiles);

    // Build the adjacency list and calculate in-degrees
    for (int i = 0; i < numFiles; ++i) {
        for (int j = 0; j < numFiles; ++j) {
            if (dependencyMatrix[i][j] == 1) {
                adjList[i].push_back(j);
                inDegree[j]++;
            }
        }
    }

    // Topological Sorting
    Stack<int> s;
    for (int i = numFiles-1; i >= 0; i--) {
        if (inDegree[i] == 0) {
            s.push(i);
        }
    }

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        compileOrder.push_back(current);

        for (int neighbor = adjList[current].size()-1; neighbor >= 0; neighbor--) {  // for each neighbor of current node
            inDegree[adjList[current][neighbor]]--;     // decrement the indegree of neighbor
            if (inDegree[adjList[current][neighbor]] == 0) {  // if the indegree of neighbor is 0
                s.push(adjList[current][neighbor]);   // push the neighbor onto the stack
            }
        }
    }

    // Check for cycles
    for (int i = 0; i < numFiles; ++i) {
        if (inDegree[i] > 0 && !adjList[i].empty()) {
            isCompilable = false;
            std::vector<int> cycle;
            int current = i;

            // Detect and store the cyclic dependencies
            while (inDegree[current] > 0) {
                cycle.push_back(current);
                inDegree[current] = 0;
                if (!adjList[current].empty()) {
                    current = adjList[current][0];
                } else {
                    break;
                }
            }

            cyclicDependencies.push_back(cycle);
        }
    }

    // Combine smaller cycles into a single big cycle, if possible
    if (!cyclicDependencies.empty()) {
        std::vector<int> combinedCycle;
        
        for (std::vector<std::vector<int>>::iterator it1 = cyclicDependencies.begin(); it1 != cyclicDependencies.end(); it1++)
        {
            for (std::vector<std::vector<int>>::iterator it2 = it1+1; it2 != cyclicDependencies.end();)
            {
                std::vector<int> cycle1 = *it1;
                std::vector<int> cycle2 = *it2;

                for (int i=0; i<cycle1.size(); i++)
                {
                    for (int j=0; j<cycle2.size(); j++)
                    {
                        if (dependencyMatrix[cycle1[i]][cycle2[j]])
                        {
                            for (int m=0; m<cycle1.size(); m++)
                            {
                                for (int n=0; n<cycle2.size(); n++)
                                {
                                    if (dependencyMatrix[cycle2[n]][cycle1[m]])
                                    {
                                        combinedCycle.insert(combinedCycle.end(), cycle1.begin(), cycle1.end());
                                        combinedCycle.insert(combinedCycle.end(), cycle2.begin(), cycle2.end());
                                        it2 = cyclicDependencies.erase(it2);
                                        it1 = cyclicDependencies.erase(it1);

                                        cyclicDependencies.push_back(combinedCycle);
                                        combinedCycle.clear();
                                        goto exit;
                                    }
                                }
                            }     
                        }
                    }
                }

                it2++;
                exit:;
            }
        }
    }

    isCompilable = cyclicDependencies.empty();
}