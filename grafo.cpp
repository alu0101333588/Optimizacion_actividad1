 /*
 *  GRAFO.CPP - Plantilla para la implementación de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */

#include "grafo.h"

void GRAFO :: destroy()
{
	for (unsigned i=0; i< n; i++)
    {
		LS[i].clear();
		A[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}
	LS.clear();
	LP.clear();
	A.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura)
{
    ElementoLista     dummy;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open()){
		unsigned i, j, k;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.resize(n);
        A.resize(n);
        LP.resize(n);
	        // leemos los m arcos
		for (k=0;k<m;k++){
            textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
			//damos los valores a dummy.j y dummy.c
            
            dummy.j = j-1;

			//situamos en la posición del nodo i a dummy mediante push_backM
			//pendiente de hacer un segundo push_back si es no dirigido. O no.
			//pendiente la construcción de LP, si es dirigido
			//pendiente del valor a devolver en errorapertura
            

            if(dirigido == 1){

                LS[i-1].push_back(dummy);
                dummy.j = i-1;
                LP[j-1].push_back(dummy);

            } else {
                A[i-1].push_back(dummy);
            }
        }
    }

}


/*void GRAFO::ListaPredecesores()
{

}*/

GRAFO::~GRAFO()
{
	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	build (nombrefichero, errorapertura);
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido(){

    if(dirigido == 0){
        return 0;
    } else {
        return 1;
    }

}

void GRAFO::Info_Grafo(){

    std::cout << "Nodos: " << n << std::endl;
    std::cout << "Aristas: " << m << std::endl;
    if(dirigido == 0){
        std::cout << "Grafo no dirigido" << std::endl;
    } else {
        std::cout << "Grafo dirigido" << std::endl;
    }
    std::cout << std::endl;
    

}

/*void Mostrar_Lista(vector<LA_nodo> L)
{

}*/

void GRAFO :: Mostrar_Listas (int l){


    std::cout << "(Se ha sumado 1 para que se vea de manera más gráfica)" << std::endl;
    
    if(l == 1){
        for (int i=0;i<n;i++){
            int tamano = LS[i].size();
            int h = 0;
            while (h != tamano){
                std::cout << "LS[" << i+1 << "][" << h+1 << "] " << LS[i][h].j +1 << " | " << LS[i][h].c << std::endl;
                h++;
            }
        }
        std::cout << std::endl;
    } 

    if(l == 0){
        for (int i=0;i<n;i++){
            int tamano = A[i].size();
            int h = 0;
            while (h != tamano){
                std::cout << "A[" << i+1 << "][" << h+1 << "] " << A[i][h].j +1 << " | " << A[i][h].c << std::endl;
                h++;
            }
        }
        std::cout << std::endl;
    }    

    if(l == -1){
        for (int i=0;i<n;i++){
            int tamano = LP[i].size();
            int h = 0;
            while (h != tamano){
                std::cout << "LP[" << i +1<< "][" << h +1<< "] " << LP[i][h].j  +1<< " | " << LP[i][h].c << std::endl;
                h++;
            }
        }
        std::cout << std::endl;
    }

}

void GRAFO::Mostrar_Matriz() //Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes
{

}

void GRAFO::dfs_num(unsigned i, vector<LA_nodo>  L, vector<bool> &visitado, vector<unsigned> &prenum, unsigned &prenum_ind, vector<unsigned> &postnum, unsigned &postnum_ind) //Recorrido en profundidad recursivo con recorridos enum y postnum
{
	visitado[i] = true;
    prenum[prenum_ind++]=i;//asignamos el orden de visita prenum que corresponde el nodo i
    for (unsigned j=0;j<L[i].size();j++)
             if (!visitado[L[i][j].j])
                {
                dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
                };
    postnum[postnum_ind++]=i;//asignamos el orden de visita posnum que corresponde al nodo i
}

/*void GRAFO::RecorridoProfundidad()
{

}*/

void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) //vector de distancias a nodo i+1
//Recorrido en amplitud con la construcción de pred y d: usamos la cola
{
    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);  
    visitado[i] = true;

    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i] = i;
    d[i] = 0;
    
    
    queue<unsigned> cola; //creamos e inicializamos la cola
    cola.push(i);//iniciamos el recorrido desde el nodo i+1
    
    int contador = 1;
    std::cout << "Ramas de conexión en el recorrido" << std::endl;

 
    while (!cola.empty()) //al menos entra una vez al visitar el nodo i+1 y continúa hasta que la cola se vacíe
    {   

        unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
        cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
        
        if(pred[k] == i){ // Asignamos la distancia de los nodos respecto a la i, utilizando la lista de sucesores
            d[k] = 1;

            d[i] = -1; // El nodo inicial le ponemos distancia -1 para diferenciar de los que no tienen conexión que poseerían distancia 0

            //cout << "distanciados "  << k+1 << ": " << d[k] << " predecesor: " << pred[k]+1 << " ";
        } else {
            d[k] = d[(pred[k])] + 1; 
            //cout << "en distancias "  << k+1 << ": " << d[k] << " kpredecesor: " << pred[k]+1 << " ";
        }
        contador = d[k];
        //std::cout << std::endl;

        for (unsigned j=0;j<L[k].size();j++){
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no está visitado

            int vida = L[k][j].j;


            pred[vida] = k; // Asignamos su predecesor


            unsigned f = vida;

            vector<unsigned> predAlReves(pred.size());
            int b = 0;

            while(f != i){ // Recorremos toda la lista de predecesores y lo metemos en el vector predAlReves

                predAlReves[b] = pred[f];
                f = pred[f];
                b++;

            }

            int u;
            b = b -1;            
            for(u = b; u >= 0; u = u - 1){

                std::cout << predAlReves[u]+1 << " - ";
            }
            
            std::cout << vida+1 << std::endl; 

            if(visitado[vida] != true){ // Si no está visitado lo añadimos a la cola
                cola.push(vida);
            }

            //Lo visitamos
            //Lo metemos en la cola
            //le asignamos el predecesor
            //le calculamos su etiqueta distancia

        }
        visitado[k] = true; // Lo ponemos como visitado

        //Hemos terminado pues la cola está vacía

    }

    int tam1 = d.size();
    std::cout << std::endl;

    std::cout << "Nodos según distancia al nodo inicial en número de aristas" << std::endl;
    for(int w = -1; w < contador+1; w++){ // Imprimimos las distancias
        if(w == -1){ // El nodo inicial i
            std::cout << "Distancia " << 0 << " aristas";
        } else if(w == 0){ // Nodos que no conectan al nodo i
            std:cout << "";
        } else {
            std::cout << "Distancia " << w << " aristas";
        }
        for(int j = 0; j < tam1; j++){
            if(d[j] == w){
                if (w == 0){
                    std::cout;
                } else{
                    std::cout << " : " << j+1;
                }

            }
        }
        std::cout << std::endl;
        

    }
}

void GRAFO::RecorridoAmplitud(){ //Construye un recorrido en amplitud desde un nodo inicial
    int NodoInicial = 0;
    std::cout << "Dime el nodo inicial: ";
    std::cin >> NodoInicial;
    vector<unsigned> pred;
	vector<unsigned> d;
    NodoInicial = NodoInicial - 1;
    /*pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[NodoInicial] = NodoInicial;
    d[NodoInicial] = 0;*/

    //bfs_num(NodoInicial, LS, pred, d);
    
    if(dirigido == 1){
        bfs_num(NodoInicial, LS, pred, d);
    } else {
        bfs_num(NodoInicial, A, pred, d);
    }
    
    

}








