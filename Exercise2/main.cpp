//POLY

#include <iostream> 
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh; //creo un oggetto mesh di tipo PolygonalMesh

    if(!ImportMesh(mesh)) //gestisco l'errore nel caso fallisca l'implementazione 
    {
        cerr << "file not found" << endl;
        return 1;
    }

    Gedim::UCDUtilities utilities; //creo un oggetto utilities di tipo UCDUtilities che serve ad esportare i dati della mesh in file .inp
    utilities.ExportPoints("./Cell0Ds.inp",
                           mesh.Cell0DsCoordinates); //la funziona richiamata esporta i dati dei punti (celle OD) in un file.inp

    utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema); //la funziona richiamata esporta i dati degli spigoli (celle 1D) in un file.inp     

    return 0;
}
