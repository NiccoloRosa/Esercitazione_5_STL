//POLYGONAL MESH 
#pragma once

#include <iostream> //includo la libreria per le operazioni di input/output
#include "Eigen/Eigen" //includo la libreria per le operazioni con matrici

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary {

struct PolygonalMesh 
{
	unsigned int NumCell0Ds; //numero di punti (celle 0D)
    unsigned int NumCell1Ds; //numero di spigoli(celle 1D)
    unsigned int NumCell2Ds; //numero di poligoni(celle 2D)    


	//definisco i vettori che memorizzano gli ID univoci associati a ciascun tipo di cella. Gli ID sono unsigned int
    vector<unsigned int> Cell0DsId;  //Vettore  ID dei punti  
    vector<unsigned int> Cell1DsId;  //Vettore ID degli spigoli 
    vector<unsigned int> Cell2DsId; //Vettore ID dei Poligono

    //definisco le matrici che memorizzano le coordinate dei punti e gli estremi degli spigoli
    Eigen::MatrixXd Cell0DsCoordinates; //Matrice che memorizza le coordinate dei punti (matrice 3x n°punti: 3 = coordinate x,y,id))
    Eigen::MatrixXi Cell1DsExtrema; //Matrice che memorizza gli estremi degli spigoli (matrice 2x n°spigoli: 2 = estremi di ogni spigolo)    

    //definisco dei vettori di vettori per rappresentare i poligoni
    vector<vector<unsigned int>> Cell2DsVertices; // vettore di vettori, dove ogni vettore contiene gli ID dei vertici di un poligono con un numero di lati variabile
    vector<vector<unsigned int>> Cell2DsEdges; // vettore di vettori, dove ogni vettore contiene gli ID degli spigoli di un poligono con un numero di lati variabile  
    
    map<unsigned int, list<unsigned int>> Cell0Ds_markers;
    map<unsigned int, list<unsigned int>> Cell1Ds_markers;
    map<unsigned int, list<unsigned int>> Cell2Ds_markers;
};
}	


