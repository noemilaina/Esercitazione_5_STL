#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>

namespace PolygonalLibrary
{
bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;

    return true;

}

bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size();

    if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >>  id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);

        mesh.Cell0DsId.push_back(id);

        /// Memorizza i marker
		map<unsigned int, list<unsigned int>>& m = mesh.cell0Ds_markers;
		auto [itor, bool_val] = m.try_emplace(marker);
		itor -> second.push_back(id);
    }

    return true;
}
bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(2, mesh.NumCell1Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        char delimiter;

        converter >> id >> delimiter>> marker >> delimiter >> mesh.Cell1DsExtrema(0, id) >> delimiter >> mesh.Cell1DsExtrema(1, id);
        mesh.Cell1DsId.push_back(id);

        /// Memorizza i marker
		map<unsigned int, list<unsigned int>>& m = mesh.Cell1Ds_markers;
		auto [itor, bool_val] = m.try_emplace(marker);
		itor -> second.push_back(id);
    }

    return true;
}
bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
		unsigned int marker;
        unsigned int num_vertices;
        unsigned int num_edges;
		char delimiter;
		
        converter >> id >> delimiter >> marker >> delimiter >> num_vertices;
		
		vector<unsigned int> vec_v;
		vec_v.reserve(num_vertices);
        for(unsigned int i = 0; i < num_vertices; i++){
			unsigned int vertices
            converter >> delimiter >> vertices;
			vec_v.push_back(vertices);
		}
		mesh.Cell2DsVertices.push_back(vertices);
		
		converter >> delimiter >> num_edges;
		
		vector<unsigned int> vec_e;
		vec_e.reserve(num_edges);
        for(unsigned int i = 0; i < num_edges; i++){
			unsigned int edges
			converter >> delimiter >> edges;
			vec_e.push_back(edges);
		}
		mesh.Cell2DsEdges.push_back(edges);

        mesh.Cell2DsId.push_back(id);
        
		map<unsigned int, list<unsigned int>>& m = mesh.Cell2Ds_marker;
		auto [itor, bool_val] = m.try_emplace(marker);
		itor -> second.push_back(id);
    }

    return true;
}

}
