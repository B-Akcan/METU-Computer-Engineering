#include "BinaryHeap.h"
#include "MeshGraph.h"
#include "ObjLoader.h"
using namespace std;

int main(int argv, const char* argc[])
{
    ObjLoader a;
    string m = "C:\\Users\\batuh\\OneDrive\\Belgeler\\Dersler\\CENG213\\THE3\\facem-low2.obj";
    a.LoadObjFile(m);
    Color red{255,0,0};
    vector<Color> out;
    vector<IdPair> edges = a.GetEdges();
    vector<Double3> vertexPositions = a.GetVertexPos();
    MeshGraph g(vertexPositions, edges);
    g.PaintInRangeGeodesic(out, 15, red, 3, FILTER_BOX, 5);
    g.WriteColorToFile(out, "outputs.txt");
    // After compiling, type "./ObjViewer facem-low2.obj outputs.txt q" in console.
}