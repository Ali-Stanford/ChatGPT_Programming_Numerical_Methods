#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <triangle.h>

int main() {
    // Define the domain as a rectangle
    double xmin = -1.0;
    double xmax = 1.0;
    double ymin = -1.0;
    double ymax = 1.0;
    
    // Define the mesh size
    double h = 0.1;
    
    // Define the input for Triangle library
    triangulateio in, out;
    in.numberofpoints = 4;
    in.numberofpointattributes = 0;
    in.numberofsegments = 4;
    in.numberofholes = 0;
    in.pointlist = (REAL*) malloc(in.numberofpoints * 2 * sizeof(REAL));
    in.segmentlist = (int*) malloc(in.numberofsegments * 2 * sizeof(int));
    
    // Define the coordinates of the points and segments
    in.pointlist[0] = xmin;
    in.pointlist[1] = ymin;
    in.pointlist[2] = xmin;
    in.pointlist[3] = ymax;
    in.pointlist[4] = xmax;
    in.pointlist[5] = ymax;
    in.pointlist[6] = xmax;
    in.pointlist[7] = ymin;
    
    in.segmentlist[0] = 0;
    in.segmentlist[1] = 1;
    in.segmentlist[2] = 1;
    in.segmentlist[3] = 2;
    in.segmentlist[4] = 2;
    in.segmentlist[5] = 3;
    in.segmentlist[6] = 3;
    in.segmentlist[7] = 0;
    
    // Call the Triangle library
    std::string options = "p";
    options += "q";
    options += "a";
    std::vector<std::string> args;
    args.push_back(const_cast<char*>(options.c_str()));
    triangulate(args, &in, &out, NULL);
    
    // Print the mesh
    std::cout << "Mesh points:" << std::endl;
    for (int i = 0; i < out.numberofpoints; i++) {
        std::cout << out.pointlist[2*i] << " " << out.pointlist[2*i+1] << std::endl;
    }
    std::cout << "Mesh elements:" << std::endl;
    for (int i = 0; i < out.numberoftriangles; i++) {
        std::cout << out.trianglelist[3*i] << " " << out.trianglelist[3*i+1] << " " << out.trianglelist[3*i+2] << std::endl;
    }
    
    // Free memory
    free(in.pointlist);
    free(in.segmentlist);
    free(out.pointlist);
    free(out.segmentlist);
    free(out.trianglelist);
    
    return 0;
}
