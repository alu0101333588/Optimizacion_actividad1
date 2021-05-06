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
    } else {
        errorapertura = 1;
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
    
 
    while (!cola.empty()) //al menos entra una vez al visitar el nodo i+1 y continúa hasta que la cola se vacíe
    {   

        unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
        cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
        
        if(pred[k] == i){ // Asignamos la distancia de los nodos respecto a la i, utilizando la lista de sucesores
            d[k] = 1;
            d[i] = -1; // El nodo inicial le ponemos distancia -1 para diferenciar de los que no tienen conexión que poseerían distancia 0

        } else {
            d[k] = d[(pred[k])] + 1; 
        }

        for (unsigned j=0;j<L[k].size();j++){
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no está visitado

            int vida = L[k][j].j;

            pred[vida] = k; // Asignamos su predecesor

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

}

void GRAFO::RecorridoAmplitud(){ //Construye un recorrido en amplitud desde un nodo inicial
    int NodoInicial = 0;
    std::cout << "¿Elija nodo de partida? [1-" << n << "] ";
    std::cin >> NodoInicial;
    vector<unsigned> pred;
	vector<unsigned> d;
    NodoInicial = NodoInicial - 1;
    
    if(dirigido == 1){
        bfs_num(NodoInicial, LS, pred, d);
    } else {

        bfs_num(NodoInicial, A, pred, d);
    }
    

    // Nodos según distancia al nodo inicial en número de aristas

    int tam1 = d.size();
    int contador = 0;  // = d[tam1-1];
    for(int i = 0; i < tam1; i++){
        if(d[i] != 0 ){
            contador = d[i];
        }
    }
    std::cout << std::endl;


    std::cout << "Nodos según distancia al nodo inicial en número de aristas" << std::endl;
    for(int w = -1; w < contador+1; w++){ // Imprimimos las distancias
        //std::cout << " w vale " << w << std::endl;
        if(w == -1){ // El nodo inicial i
            std::cout << "Distancia " << 0 << " aristas";
        } else if(w == 0){ // Nodos que no conectan al nodo i
            std::cout;
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
        if (w == 0){
            std::cout;
        } else{
            std::cout << std::endl;
        }
    }
    
    std::cout << std::endl;
    std::cout << "Ramas de conexión en el recorrido" << std::endl;
    int b = 0, j;

    for(int i = 0; i < n; i++){
        j = i;
        if(d[i] == 0 || d[i] == -1){
            std::cout;
        } else {
            b = 0;
            vector<unsigned> predAlReves(pred.size());
            predAlReves[b] = pred[j];
            while(j != NodoInicial){ // Recorremos toda la lista de predecesores y lo metemos en el vector predAlReves

                j = pred[j];
                b++;
                predAlReves[b] = pred[j];
            }
        

            b = b -1;            
            for(int u = b; u >= 0; u = u - 1){
                std::cout << predAlReves[u]+1 << " - ";
            }
            
            std::cout << i+1 << std::endl; 

        }
    }



}


void GRAFO::FloydWarshall(){ //Algoritmo de FW paracaminos mínimos entre cualquier par de nodos
    vector<LA_nodo> P;
    //Usaremos la misma estructura de datos de LS para guardar P y D
    //Inicializamos P y D en P
    //Creamos P
    P.resize(n); //Ya tenemos las posiciones P[0]a P[n-1]

    for (unsigned i=0; i<n; i++) P[i].resize(n); //Ya tenemos la matriz cuadrada
    for (unsigned i=0;i<n;i++){
        for (unsigned j=0;j<n;j++){
            if (i != j){ //Inicialización base
                P[i][j].j = -1; //en el campo .j ponemos el predecesor
                P[i][j].c = maxint; // en el campo .c ponemos el coste
            } else { //Inicializamos los bucles
                P[i][j].c = 0; //El coste en el caso de un bucle
                P[i][j].j = i; //El predecesor en el casode un bucle
            }

        }
    }
    
    //Recorremos LS para inicializar P, su predecesor en .j y su distancia en .c
    for (unsigned i=0;i<n;i++){
        for (unsigned j=0;j<LS[i].size();j++){
            P[i][LS[i][j].j].j = i;
            P[i][LS[i][j].j].c= LS[i][j].c;
        }
        //Con las matrices ya inicializadas, vamos ahora a realizar las k comparativas...
        //Bien, ya tenemos D y P, mostremos las matrices y los caminos mínimos...
    }


    for(int k= 0; k < n; k++){
        for(int i = 0; i < n; i++){
            if(i != k){
                for(int j=0; j < n; j++){
                    if(j != k){
                        if(P[i][j].c > P[i][k].c + P[k][j].c){
                            P[i][j].c = P[i][k].c + P[k][j].c;
                            P[i][j].j = P[k][j].j;
                        }
                    }
                }
            }
        }
    }

    //std::cout << "--------- d ---------------- P --------------" << std::endl;
    //std::cout << "    1 2 3 4 | 1 2 3 4" << std::endl;

    //IMPRESIÓN POR PANTALLA:

    //PARTE ESTÉTICA DE LA TABLA DE COSTES Y PREDECESORES
    std::cout << std::endl << "_____";
    int tam = n/2;

    for(int y = 0; y < n; y++){
        if(y == tam){
            std::cout << "d";
        }
        std::cout << "__";
    }
    std::cout << "|";
    for(int y = 0; y < n; y++){
        if(y == tam){
            std::cout << "pred";
        }
        std::cout << "__";
    }

    std::cout << std::endl << "  || ";
    for(int z = 1; z <= n; z++){
        std::cout << z << " ";
    }

    std::cout << " | ";
    for(int z = 1; z <= n; z++){
        std::cout << z << " ";
    }

    std::cout << std::endl;


    // IMPRESIÓN POR PANTALLA DE LOS VALORES NUMÉRICOS
    int espaciado = 0;
    for (unsigned i=0;i<n;i++){
        std::cout << i +1 << " || ";
        for (unsigned j=0;j<P[i].size();j++){
            if(P[i][j].c >= maxint){
                std::cout << "∞ ";
            } else {

            //std::cout << P[i][LS[i][j].j].c << " ";
            /*if(P[i][j].c == -1){
                std::cout << 0 << " ";
            } else{
                std::cout << P[i][j].c << " ";
            }*/

            std::cout << P[i][j].c << " ";
            espaciado = P[i][j].c;

            }
        }

        if(espaciado >= 10){
            std::cout << "| ";
        } else{
            std::cout << " | ";
        }

        for (unsigned j=0;j<P[i].size();j++){
            if(P[i][j].j == -1){
                std::cout << 0 << " ";
            } else{
                std::cout << P[i][j].j +1 << " ";
            }
        }
        std::cout << std::endl;
        
    }

    //Ruta de caminos mínimos posibles
    std::cout << std::endl << "Ruta de caminos mínimos posiles para cada para de nodos i y j (y su coste): " << std::endl;
    
    for(int i=0; i < n; i++){
        for(int z=0; z < n; z++){
            std::cout << i+1 << " ⮞ " << z+1 << " || ";
            if(P[i][z].c == maxint){
                std::cout << "No existen caminos" << std::endl;
            } else {
                int x = -1, l = 0;
                l = z;
                int repe = 0;

                int b = -1;
                vector<unsigned> predAlReves(n);

                while(x != i){
                    
                    if(z == i){
                        std::cout << "No existen caminos" << std::endl;
                        repe = 1;
                    }

                    b++;
                    x = P[i][l].j;
                    predAlReves[b] = P[i][l].j + 1;
                    //std::cout << " # i: " << i+1 << " l: " << l+1 << ": " << P[i][l].c << " | ";
                    l = l - 1;
                    
                }

                if (repe == 0) {
                    for(int i= b; i >= 0; i = i - 1){
                        std::cout << predAlReves[i] << " → ";
                    }

                    std::cout << z+1;
                    std::cout << " (" << P[i][z].c << ")";
                    std::cout << std::endl;
                }

            }
        }
        std::cout << std::endl;
    }


}