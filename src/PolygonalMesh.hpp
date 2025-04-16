#pragma once

#include <vector>
#include <map>
#include <list>
#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
    unsigned int NumCell0Ds;
    unsigned int NumCell1Ds;
    unsigned int NumCell2Ds;

    vector<unsigned int> Cell0DsId;
    vector<unsigned int> Cell1DsId;
    vector<unsigned int> Cell2DsId;

    MatrixXd Cell0DsCoordinates;
    MatrixXi Cell1DsExtrema;
    vector<vector<unsigned int>> Cell2DsVertices;
    vector<array<unsigned int>> Cell2DsEdges;
	
	//Markers
	map<unsigned int, list<unsigned int>> Cell0DsId_markers; 
	map<unsigned int, list<unsigned int>> Cell1DsId_markers; 
	map<unsigned int, list<unsigned int>> Cell2DsId_markers; 
};

}
