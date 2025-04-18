//POLY
#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{

/* Importa la mesh poligonale e verifica se la mesh è corretta, ritorna true se la lettura è andata a buon fine, false altrimenti */
bool ImportMesh(PolygonalMesh& mesh);

/* Importa le proprietà delle celle 0D dal file Cell0Ds.csv ritorna il risultato della lettura, true se ha successo, false altrimenti */
bool ImportCell0Ds(PolygonalMesh& mesh);

/* Importa le proprietà delle celle 1D dal file Cell1Ds.csv ritorna il risultato della lettura, true se ha successo, false altrimenti */
bool ImportCell1Ds(PolygonalMesh& mesh);

/* Importa le proprietà delle celle 2D dal file Cell2Ds.csv ritorna il risultato della lettura, true se ha successo, false altrimenti */
bool ImportCell2Ds(PolygonalMesh& mesh);

}