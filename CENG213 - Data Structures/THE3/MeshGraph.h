#pragma once

#include <list>
#include <vector>
#include <string>

#include "Structs.h"

struct Color
{
    unsigned char r, g, b;
};

struct Vertex
{
    int id;
    Double3 position3D;
};

enum FilterType
{
    FILTER_BOX,      
    FILTER_GAUSSIAN    
};

class MeshGraph
{
    private:
    std::vector<Vertex>                 vertices;
    std::vector<std::list<Vertex*> >     adjList;

    double filter_box(double x, double a) const;
    double filter_gaussian(double x, double a) const;

    protected:
    public:
                        MeshGraph(const std::vector<Double3>& vertexPositions,
                                  const std::vector<IdPair>& edges);
                        ~MeshGraph();
    double              AverageDistanceBetweenVertices() const;
    double              AverageEdgePerVertex() const;
    int                 TotalVertexCount() const;
    int                 TotalEdgeCount() const;
    int                 VertexEdgeCount(int vertexId) const;

    void                ImmediateNeighbours(std::vector<int>& outVertexIds,
                                            int vertexId) const;

    void                PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                             int vertexIdFrom, int vertexIdTo,
                                             const Color& color) const;
    void                PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                             int vertexId, const Color& color,
                                             int maxDepth, FilterType type, double alpha) const;
    void                PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                              int vertexId, const Color& color,
                                              int maxDepth, FilterType type, double alpha) const;
    static void WriteColorToFile(const std::vector<Color>& colors, const std::string& fileName);
    static void PrintColorToStdOut(const std::vector<Color>& colors);
};