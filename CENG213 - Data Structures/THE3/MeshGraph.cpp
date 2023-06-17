#include "MeshGraph.h"
#include "BinaryHeap.h"

#include <fstream>
#include <iostream>
#include <sstream>
#define DOUBLE_MAX 999999999999

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    for (unsigned long int i=0; i<vertexPositions.size(); i++)
    {
        Vertex v = {(int) i, vertexPositions[i]};
        vertices.push_back(v);
    }
    adjList.resize(vertices.size());
    for (unsigned long int i=0; i<edges.size(); i++)
    {
        Vertex *v0 = new Vertex();
        v0->id = edges[i].vertexId0;
        v0->position3D = vertices[edges[i].vertexId0].position3D;
        adjList[edges[i].vertexId1].push_back(v0);
        Vertex *v1 = new Vertex();
        v1->id = edges[i].vertexId1;
        v1->position3D = vertices[edges[i].vertexId1].position3D;
        adjList[edges[i].vertexId0].push_back(v1);
    }
}

MeshGraph::~MeshGraph()
{
    for (unsigned long int i=0; i<adjList.size(); i++)
    {
        std::list<Vertex*>::const_iterator it;
        for (it = adjList[i].begin(); it != adjList[i].end(); it++)
            delete *it;
    }
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    double total=0;
    for (unsigned long int i=0; i<adjList.size(); i++)
    {
        std::list<Vertex*>::const_iterator it;
        for (it = adjList[i].begin(); it != adjList[i].end(); it++)
            total += Double3::Distance(vertices[i].position3D, (*it)->position3D);
    }
    return total / (TotalEdgeCount()*2);
}

double MeshGraph::AverageEdgePerVertex() const
{
    double sum=0;
    for (unsigned long int i=0; i<adjList.size(); i++)
        sum += adjList[i].size();
    return sum / (TotalVertexCount()*2);
}

int MeshGraph::TotalVertexCount() const
{
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    int sum=0;
    for (unsigned long int i=0; i<adjList.size(); i++)
        sum += adjList[i].size();
    return sum/2;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    if (vertexId < 0 || (unsigned long int) vertexId >= adjList.size())
        return -1;
    return adjList[vertexId].size();
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    if (vertexId < 0 || (unsigned long int) vertexId >= adjList.size())
        return;
    std::list<Vertex*>::const_iterator it;
    for (it = adjList[vertexId].begin(); it != adjList[vertexId].end(); it++)
        outVertexIds.push_back((*it)->id);
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    if (vertexIdFrom < 0 || vertexIdFrom >= vertices.size() || vertexIdTo < 0 || vertexIdTo >= vertices.size())
        return;
    // Paint each vertex to black
    outputColorAllVertex.resize(vertices.size());
    for (unsigned long int i=0; i<outputColorAllVertex.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    
    // Dijkstra's Algorithm
    BinaryHeap bh;
    bh.Add(vertexIdFrom, 0);
    std::vector<double> distance;
    distance.resize(vertices.size(), DOUBLE_MAX);
    distance[vertexIdFrom] = 0;
    std::vector<int> previous;
    previous.resize(vertices.size(), -1);
    for (unsigned long int i=0; i<vertices.size(); i++)
    {
        if (vertices[i].id != vertexIdFrom)
            bh.Add(vertices[i].id, DOUBLE_MAX);
    }
    while (bh.HeapSize())
    {
        int outUniqueId;
        double outWeight;
        bh.PopHeap(outUniqueId, outWeight);
        std::list<Vertex*>::const_iterator it;
        for (it = adjList[outUniqueId].begin(); it != adjList[outUniqueId].end(); it++)
        {
            double new_dist = outWeight + Double3::Distance(vertices[outUniqueId].position3D, (*it)->position3D);
            if (new_dist < distance[(*it)->id])
            {
                distance[(*it)->id] = new_dist;
                previous[(*it)->id] = outUniqueId;
                bh.ChangePriority((*it)->id, new_dist);
            }
        }
    }
    // Shortest path from vertexIdTo to vertexIdFrom
    std::vector<int> shortest_path;
    int prev_id = vertexIdTo;
    while (prev_id != -1)
    {
        shortest_path.push_back(prev_id);
        prev_id = previous[prev_id];
    }
    
    // Paint the vertices in the shortest path to color.
    for (unsigned long int i=0; i<shortest_path.size(); i++)
    {
        outputColorAllVertex[shortest_path[i]].r = color.r;
        outputColorAllVertex[shortest_path[i]].g = color.g;
        outputColorAllVertex[shortest_path[i]].b = color.b;
    }
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    if (vertexId < 0 || vertexId >= vertices.size())
        return;
    outputColorAllVertex.resize(vertices.size());
    for (unsigned long int i=0; i<outputColorAllVertex.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    outputColorAllVertex[vertexId].r = color.r;
    outputColorAllVertex[vertexId].g = color.g;
    outputColorAllVertex[vertexId].b = color.b;
    BinaryHeap bh;
    std::vector<bool> marked;
    marked.resize(vertices.size(), false);
    bh.Add(vertexId, 0);
    marked[vertexId] = true;
    std::vector<int> previous;
    previous.resize(vertices.size(), -1);
    std::vector<double> distance;
    distance.resize(vertices.size(), 0);
    int i=1;
    while (bh.HeapSize())
    {
        int outUniqueId;
        double outWeight;
        bh.PopHeap(outUniqueId, outWeight);
        std::list<Vertex*>::const_iterator it;
        for (it = adjList[outUniqueId].begin(); it != adjList[outUniqueId].end(); it++)
        {
            if (!marked[(*it)->id])
            {
                marked[(*it)->id] = true;
                bh.Add((*it)->id, i++);
                previous[(*it)->id] = outUniqueId;
                std::vector<int> path;
                int prev_id = (*it)->id;
                while (previous[prev_id] != -1)
                {
                    path.push_back(prev_id);
                    distance[(*it)->id] += Double3::Distance(vertices[previous[prev_id]].position3D, vertices[prev_id].position3D);
                    prev_id = previous[prev_id];
                }
                if (path.size() <= maxDepth)
                {
                    double dist = distance[(*it)->id];
                    if (type == FILTER_BOX)
                    {
                        outputColorAllVertex[(*it)->id].r = color.r * filter_box(dist, alpha);
                        outputColorAllVertex[(*it)->id].g = color.g * filter_box(dist, alpha);
                        outputColorAllVertex[(*it)->id].b = color.b * filter_box(dist, alpha);
                    }
                    else if (type == FILTER_GAUSSIAN)
                    {
                        outputColorAllVertex[(*it)->id].r = color.r * filter_gaussian(dist, alpha);
                        outputColorAllVertex[(*it)->id].g = color.g * filter_gaussian(dist, alpha);
                        outputColorAllVertex[(*it)->id].b = color.b * filter_gaussian(dist, alpha);
                    }
                }
            }
        }
    }
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    if (vertexId < 0 || vertexId >= vertices.size())
        return;
    outputColorAllVertex.resize(vertices.size());
    for (unsigned long int i=0; i<outputColorAllVertex.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    outputColorAllVertex[vertexId].r = color.r;
    outputColorAllVertex[vertexId].g = color.g;
    outputColorAllVertex[vertexId].b = color.b;
    BinaryHeap bh;
    std::vector<bool> marked;
    marked.resize(vertices.size(), false);
    bh.Add(vertexId, 0);
    marked[vertexId] = true;
    std::vector<int> previous;
    previous.resize(vertices.size(), -1);
    int i=1;
    while (bh.HeapSize())
    {
        int outUniqueId;
        double outWeight;
        bh.PopHeap(outUniqueId, outWeight);
        std::list<Vertex*>::const_iterator it;
        for (it = adjList[outUniqueId].begin(); it != adjList[outUniqueId].end(); it++)
        {
            if (!marked[(*it)->id])
            {
                marked[(*it)->id] = true;
                bh.Add((*it)->id, i++);
                previous[(*it)->id] = outUniqueId;
                std::vector<int> path;
                int prev_id = (*it)->id;
                while (prev_id != -1)
                {
                    path.push_back(prev_id);
                    prev_id = previous[prev_id];
                }
                if (path.size()-1 <= maxDepth)
                {
                    double dist = Double3::Distance(vertices[vertexId].position3D, vertices[(*it)->id].position3D);
                    if (type == FILTER_BOX)
                    {
                        outputColorAllVertex[(*it)->id].r = color.r * filter_box(dist, alpha);
                        outputColorAllVertex[(*it)->id].g = color.g * filter_box(dist, alpha);
                        outputColorAllVertex[(*it)->id].b = color.b * filter_box(dist, alpha);
                    }
                    else if (type == FILTER_GAUSSIAN)
                    {
                        outputColorAllVertex[(*it)->id].r = color.r * filter_gaussian(dist, alpha);
                        outputColorAllVertex[(*it)->id].g = color.g * filter_gaussian(dist, alpha);
                        outputColorAllVertex[(*it)->id].b = color.b * filter_gaussian(dist, alpha);
                    }
                }
            }
        }
    }
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}

double MeshGraph::filter_box(double x, double a) const
{
    if (x >= -a && x <= a)
        return 1.0;
    return 0.0;
}

double MeshGraph::filter_gaussian(double x, double a) const
{
    return std::exp(-x*x/a/a);
}


















