#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }
	map<unsigned int, list<unsigned int>>& m_0Ds_markers = mesh.Cell0Ds_markers;
	map<unsigned int, list<unsigned int>>& m_1Ds_markers = mesh.Cell01s_markers;
	map<unsigned int, list<unsigned int>>& m_2Ds_markers = mesh.Cell02s_markers;
	
	for(auto& [marker, list_id] : m_0Ds_markers)
     {
        cout<<"Marker0D: "<<marker<<"  IDs = [";
        for(auto& id : list_id)
            cout<<' '<<id;
        cout<<" ]"<<endl;
     }

     cout<<endl;
     for(auto& [marker, list_id] : m_1Ds_markers)
     {
        cout<<"Marker1D: "<<marker<<"  IDs = [";
        for(auto& id : list_id)
            cout<<' '<<id;
        cout<<" ]"<<endl;
     }

     cout<<endl;
     for(auto& [marker, list_id] : m_2Ds_markers)
     {
        cout<<"Marker2D: "<<marker<<"  IDs = [";
        for(auto& id : list_id)
            cout<<' '<<id;
        cout<<" ]"<<endl;
     }

	
	Gedim::UCDUtilities utilities;
    utilities.ExportPoints("./Cell0Ds.inp",
                           mesh.Cell0DsCoordinates);

    utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema);

	return 0
}
