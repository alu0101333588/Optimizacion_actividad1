 /*
 *  Programa principal.
 *
 *
 *               Autores : Antonio Sedeno Noda, Sergio Alonso.
 *               Cursos  : 2012-2021
 */

#include <string.h>
#include "grafo.h"


void menu (unsigned dirigido, char &opcion)
//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
{
    cout << endl;
    cout << "////////////////////////////////////////////////////////////" << endl;
    cout << "Optimiza!ción en Grafos, 2020-2021, por Andrés Hernández Ortega" << endl;
    cout << "c. [c]argar grafo desde fichero" << endl;
    if (dirigido == 0) //Grafo no dirigido
            {
            cout << "i. Mostrar [i]nformación básica del grafo" << endl;
            cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
	    //Aquí se añaden más opciones al menú del grafo no dirigido
            }
    else
            {
            cout << "i. Mostrar [i]nformación básica del grafo" << endl;
            cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
            cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
	    //Aquí se añaden más opciones al menú del grafo dirigido
            };
    cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo por sucesores" << endl;
    cout << "f. Algoritmo de [F]loydWarshall" << endl;
    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
    cout << endl;
};


// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un menú inicial si no hay un grafo cargado
int main(int argc, char *argv[])
{
    int error_apertura;
    char nombrefichero[85], opcion;
    //clrscr();
    //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
    if (argc > 1)
    {
	cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    }
    else
    {
        cout << "Introduce el nombre completo del fichero de datos" << endl;
        cin >> nombrefichero;
    };
    GRAFO G(nombrefichero, error_apertura);
    if (error_apertura == 1)
    {
        cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
        //pressanykey();
        //clrscr();
    }
    else
    {
        cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
        //pressanykey();
        //clrscr();
        do
        {
            menu(G.Es_dirigido(), opcion);
            switch (opcion)
            {
                case 'c' :
                    //clrscr();
         	        cout << "Introduce el nombre completo del fichero de datos" << endl;
                    cin >> nombrefichero;
                    G.actualizar(nombrefichero, error_apertura);
                    if (error_apertura == 1)
                    {
                        cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
                    }
                    else
                    {
                        cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
                    };
                    //pressanykey();
                    //clrscr();
                    break;

                case 'i' :
                    //clrscr();
		            cout << "Grafo cargado desde " << nombrefichero << endl;
                    G.Info_Grafo();
                    //pressanykey();
                    //clrscr();
                    break;

                case 'm' :
                    G.RecorridoAmplitud();
                    break;

                case 'f':
                    G.FloydWarshall();
                    break;

		 //Situar aquí el resto de opciones del menú
            }

        if (G.Es_dirigido() == 0){
            switch(opcion){
                case 'a': 
                    G.Mostrar_Listas(0);
                    break;
            }

        } else {

            switch(opcion){
                case 's': 
                    G.Mostrar_Listas(1);
                    break;

                case 'p':
                    G.Mostrar_Listas(-1);
                    break;

            }
            
        }
    }
    while (opcion != 'q');
    }
    cout << "Fin del programa" << endl;
	return(0);
};
