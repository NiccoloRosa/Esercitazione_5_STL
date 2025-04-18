//POLY

#include "Utils.hpp"
#include <iostream>
#include <fstream> //libreria per la gestione dei file
#include <sstream> //libreria per manipolare le stringhe

namespace PolygonalLibrary 
{
bool ImportMesh(PolygonalMesh& mesh) //funzione che importa una mesh poligonale. se ci sono errori e una funzione fallisce viene restituito false
{

    if(!ImportCell0Ds(mesh)) //importo la funzione per i dati relativi ai PUNTI 
        return false;
    if(!ImportCell1Ds(mesh)) //importo la funzione per i dati relativi agli SPIGOLI
        return false;

    if(!ImportCell2Ds(mesh)) //importo la funzione per i dati relativi ai POLIGONI
        return false;

    return true;
}

// ***************************************************************************

bool ImportCell0Ds(PolygonalMesh& mesh) //implemento la funzione che deve raccogliere i dati relativi ai PUNTI 
{
    ifstream file("./Cell0Ds.csv"); //il file da cui leggiamo i dati 

    if(file.fail()) //gestiamo l'apertura del file
        return false;

    list<string> listLines; //creo una lista di stringhe 

    string line; //creo una stringa che conterrà le righe del file
    while (getline(file, line)) //leggo il file linea per linea
        listLines.push_back(line); //aggiungo ogni linea del file come elemento della lista

    file.close(); //chiudo il file 

    // rimuovo l'header della lista 
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size(); //imposto il numero di punti uguale alla dimensione della lista

    if (mesh.NumCell0Ds == 0) //nel caso la dimensione sia nulla gestisco l'errore
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    //Alloco memoria per gli ID e le coordinate dei punti 
    mesh.Cell0DsId.reserve(mesh.NumCell0Ds); //creo un vettore di dimensione numero di punti in cui salvare l'id di ogni punto 
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds); //creo una matrice di dimensione 3x numero di punti in cui salvare le coordinate e gli id di ogni punto

    for (const string& line : listLines)
    {
        istringstream converter(line); //oggetto istringstream che mi permette di manipolare le righe di stringhe 

        unsigned int id; //definisco la variabile id 
        unsigned int marker; //definisco il marker
        Vector2d coord; //definisco un vettore di dimensione 2x1 per le coordinate

        converter >>  id;
        converter.ignore(1, ';'); //ignoro il separatore ';' per facilitare la lettura della riga
        converter >> marker;
        converter.ignore(1, ';');
        converter >> mesh.Cell0DsCoordinates(0, id); /*coordinata x*/ 
        converter.ignore(1, ';');
        converter >> mesh.Cell0DsCoordinates(1, id)/*coordinata x*/; 
        //ogni >> legge ordinatamente un valore dal csv del converter e lo memorizza nella destinazione scritta (es: valore 1 --> id, valore 2 --> marker, ecc)
        mesh.Cell0DsId.push_back(id); //aggiungo all'ultima posizione del vettore Cell0DsId l'id del punto 

        map<unsigned int, list<unsigned int>>& m = mesh.Cell0Ds_markers; //creo una mappa in cui la chiave è un intero e il valore è una lista di interi
        auto[itor, bool_val] = m.try_emplace(marker); //provo ad inserire un elemento nella mappa, se non esiste già        
        itor->second.push_back(id); //aggiungo l'id del segmento alla lista di id associata al marker
    }

    return true;
}

// ***************************************************************************

bool ImportCell1Ds(PolygonalMesh& mesh) //implemento la funzione che deve raccogliere i dati relativi agli SPIGOLI
{
    ifstream file("./Cell1Ds.csv"); //apro il file da cui leggiamo i dati

    if(file.fail()) //gestiamo l'apertura del file
        return false;

    list<string> listLines; //creo una lista di stringhe

    string line;
    while (getline(file, line)) //leggo il file linea per linea
        listLines.push_back(line); //aggiungo ogni linea del file come elemento della lista

    file.close(); //chiudo il file

    // rimuovo l'header della lista
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size(); //imposto il numero di spigoli uguale alla dimensione della lista 

    if (mesh.NumCell1Ds == 0) //nel caso la dimensione sia nulla gestisco l'errore
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    // Alloco memoria per gli ID e le coordinate dei punti
    mesh.Cell1DsId.reserve(mesh.NumCell1Ds); //vettore di dimensione numero di spigoli per salvare gli spigoli 
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds); //matrice di dimensione 2x numero di spigoli per salvare gli estremi 

    for (const string& line : listLines) //per ogni riga della lista, presa per riferimento 
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;        
        Vector2i vertices; //definisco un vettore di dimensione 2x1 per gli estremi

        converter >>  id;
        converter.ignore(1, ';'); //ignoro il separatore ';' per facilitare la lettura della riga
        converter >> marker;
        converter.ignore(1, ';');
        converter >>  mesh.Cell1DsExtrema(0, id) /*coordinatax*/;
        converter.ignore(1, ';');
        converter >>  mesh.Cell1DsExtrema(1, id) /*coordinatay*/;
        mesh.Cell1DsId.push_back(id); //aggiungo id all'ultima posizione del vettore Cell1DsId

        map<unsigned int, list<unsigned int>>& m = mesh.Cell1Ds_markers; //creo una mappa in cui la chiave è un intero e il valore è una lista di interi
        auto[itor, bool_val] = m.try_emplace(marker); //provo ad inserire un elemento nella mappa, se non esiste già        
        itor->second.push_back(id); //aggiungo l'id del segmento alla lista di id associata al marker
    }
    return true;
}

bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv"); //apro il file da cui leggiamo i dati

    if(file.fail()) //gestiamo l'apertura del file
        return false;

    list<string> listLines; //creo una lista di stringhe in cui salvare le linee del file 
     
    string line;
    while (getline(file, line))
        listLines.push_back(line); //leggo il file linea per linea e la aggiungo ogni volta in ultima posizione della lista
         
    file.close(); //chiudo il file
     
    // rimuovo l'header della lista
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size(); //imposto il numero di poligoni uguale alla dimensione della lista

    if (mesh.NumCell2Ds == 0) //nel caso la dimensione sia nulla gestisco l'errore
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    // Alloco memoria per gli ID e le coordinate dei punti
    //vettore id dei poligoni
    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);    
    //vettori di array dove ogni array contiene gli ID dei VERTICI e SPIGOLI di un poligoni
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds); //riservo lo spazio pari al numero totale di poligoni
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds); //riservo lo spazio pari al numero totale di poligoni


    for (const string& line : listLines)
    {
        istringstream converter(line); //oggetto istringstream che mi permette di manipolare le righe di stringhe

        unsigned int id;
        unsigned int marker;
        unsigned int NumVertices; //definisco la variabile NumVertices
        unsigned int NumEdges; //definisco la variabile NumEdges
        vector<unsigned int> vertices; //definisco un vettore di dimensione variabile per gli id dei vertici
        vector<unsigned int> edges; //definisco un vettore di dimensione variabile per gli id degli spigoli

        converter >>  id; //leggo e memorizzo il primo valore di converter in id 
        converter.ignore(1, ';'); //ignoro il separatore ';' per facilitare la lettura della riga
        converter >>  marker; //leggo e memorizzo il secondo valore di converter in marker
        converter.ignore(1, ';');
        converter >> NumVertices; //leggo e memorizzo il secondo valore di converter in NumVertices        
        //Alloco la memoria per gli id dei vertici
        vertices.reserve(NumVertices);
        for(unsigned int i = 0; i < NumVertices; i++)
        {            
            converter.ignore(1, ';');
            converter >> vertices[i]; //leggo e salvo i valori dei vertici (di quantità pari a NumVertices)            
        }        
        converter.ignore(1, ';');
        converter >> NumEdges; //leggo e memorizzo il secondo valore di converter in NumEdges
        //Alloco la memoria per gli id degli spigoli
        edges.reserve(NumEdges);
        for(unsigned int i = 0; i < NumEdges; i++)
        {
            converter.ignore(1, ';');
            converter >> edges[i]; //leggo e salvo i valori degli spigoli (di quantità pari a NumEdges)            
        }
            
        mesh.Cell2DsId.push_back(id); //aggiungo l'id del poligono all'ultima posizione del vettore Cell2DsId
        mesh.Cell2DsVertices.push_back(vertices); //aggiungo un vettore vertices all'ultima posizione del vettore di vettori Cell2DsVertices
        mesh.Cell2DsEdges.push_back(edges); //aggiungo un vettore edges all'ultima posizione del vettore di vettori Cell2DsEdges

        //memorizzo i marker
        map<unsigned int, list<unsigned int>>& m = mesh.Cell2Ds_markers; //creo una mappa in cui la chiave è un intero e il valore è una lista di interi
        auto[itor, bool_val] = m.try_emplace(marker); //provo ad inserire un elemento nella mappa, se non esiste già
        //Il metodo try_emplace cerca di inserire un elemento nella mappa con la chiave marker e il valore una lista di interi vuota, se invece
        //il marker esiste già, non viene inserito nulla. Il metodo restituisce la coppia [iteratore, bool_val], dove l'iteratore punta alla coppia [marker, lista]. 
        //L'iteratore itor punta alla coppia chiave-valore appena inserita o già esistente. bool_val è true se l'elemento è stato inserito, false se era già esistente.
        //con itor->first posso accedere alla chiave e con itor->second posso accedere al valore associato alla chiave, che in questo caso è una lista, 
        //dunque uso poi pushback per aggiungere un elemento al fondo di tale lista: il codice id associato al marker
        itor->second.push_back(id); //aggiungo l'id del poligono alla lista associata al marker
    }

    return true;
}

}

