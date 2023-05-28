#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
#include<locale.h>
#include<windows.h>
#include<ctype.h>

using namespace std;

//Registros y TDA
struct Localidad{
    string nombre;
    string coorx;
    string coory;
};
struct Ruta{
    string distancia;
    string tiempo;
    string tipo;
};
struct NodoArbol{
    Localidad dato;
    NodoArbol *der;
    NodoArbol *izq;
    NodoArbol *padre;
};
struct NodoCola{
    Localidad dato;
    NodoCola *siguiente;
};
struct NodoGrafo{
    Localidad dato;
    NodoGrafo *siguiente;
    struct Arista *adyacente;
};
struct Arista{
    NodoGrafo *destino;
    Arista *siguiente;
    Ruta rutas;
};
typedef struct Arista *Tarista;
struct ArrayList{
    NodoGrafo *array[50];
};
//Fin Registros y TDA

//Variables Globales
int r=0,t=0,h=0; 
//Fin Variables Globales


//Declaracion Funciones
void menuPrincipal();
void menuAgregarInformacion();
void menuEliminarInformacion();
void menuBuscaryListar();
void menuMostrarRespaldo();
void leerArchivo(int &, int &, bool &);
string quitarAcentos(string );
void leerLocalidadesArchivo(Localidad *&, int);
void leerRutasArchivo(NodoGrafo *&, Arista *&, Ruta &, int, int, Localidad *);
void insertarNodoGrafo(NodoGrafo *&, Localidad );
void insertarRelacionesInicio(NodoGrafo *&, Arista *&, Localidad *, string , string , Ruta , int);
void agregarArista(NodoGrafo *&, NodoGrafo *&, Arista *&);
void insertarArista(NodoGrafo *, Arista *&, string , string , Ruta );
NodoArbol *crearNodoArbol(Localidad ,NodoArbol *);
void insertarAlArbol(NodoArbol *&, Localidad *, int & , NodoArbol *);
void mostrarCiudadesAdyacentes(NodoGrafo *, NodoArbol *);
bool existeLocalidad(NodoArbol *, string );
void separarLocalidad(string , string &, string &, string &);
bool validarFormatoLocalidad(string , string , string );
void agregarRelacion(NodoGrafo *&,Arista *&, NodoArbol *, Ruta );
void agregarLocalidad(NodoArbol *);
void eliminarLocalidad(NodoArbol *&, NodoGrafo *&);
void eliminarNodoArbol(NodoArbol *);
void destruirNodo(NodoArbol *);
void reemplazar(NodoArbol *, NodoArbol *);
NodoArbol *minimo(NodoArbol *);
void acentos(NodoArbol *&);
void consultarLocalidad(NodoArbol *);
void listadoLocalidadesEliminadas();
void listadoLocalidadesExistentes(NodoArbol *, Localidad *, int L);
void listadoLocalidadesAlfabetico(NodoArbol *, NodoCola *&, NodoCola *&);
void buscarRutas(NodoGrafo *, NodoArbol *, int);
void eliminarRuta(NodoGrafo *&, NodoArbol *, int );
void listadoRutasEliminadas();
//Fin Declaracion Funciones

int main(){;

    //Inicio del Programa se carga en el sistema el archivo
    //Funciones usadas para usar acentos en Windows
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    //Variables
    int L, R, opc, cont=0, i=0, j=0;
    bool flag = false;
    NodoGrafo *grafo = NULL;
    Arista *arista = NULL;
    NodoArbol *arbol = NULL;
    NodoCola *primero = NULL;
    NodoCola *ultimo = NULL;
    Ruta rutas;

    //Comenzamos a cargar el archivo al programa
    leerArchivo(L, R, flag);
    if(flag){
        //Si incumple algun valor se termina el programa
        cout<<endl;
        cout<<"ERROR: Cantidad de localidades o relaciones mayor al establecido"<<endl;
        cout<<endl;
        return 0;
    }
    Localidad *localidades = new Localidad[L]; //Arreglo de Localidades
    leerLocalidadesArchivo(localidades, L);
    leerRutasArchivo(grafo, arista, rutas, R, L, localidades);
    while(i < L){
        insertarAlArbol(arbol, localidades, i, NULL);
        i++;
    }
    //Se termina de cargar todo el archivo localidades.dat

    //Se borran los archivos de alguna ejecucion anterior
    remove("localidades_resp.dat");
    remove("rutas_resp.dat");
    remove("resultados.out");

    //Menu del programa
    do{
        menuPrincipal();
        cout<<"Opcion: "; cin>>opc;
        cout<<endl;

        switch(opc){
            //Agregar Informacion
            case 1: 
                do{
                    menuAgregarInformacion();
                    cout<<"Opcion: "; cin>>opc;
                    switch(opc){
                        case 1: agregarLocalidad(arbol);
                        break;

                        case 2: agregarRelacion(grafo, arista, arbol, rutas);
                        break;

                        case 4: cout<<"Saliendo..."; opc = 3; return 0;

                    }
                }while(opc != 3);
            break;
            //Eliminar Informacion
            case 2:
                do{
                    menuEliminarInformacion();
                    cout<<"Opcion: "; cin>>opc;
                    switch(opc){
                        case 1: eliminarLocalidad(arbol, grafo);
                        break;

                        case 2: eliminarRuta(grafo, arbol, L);
                        break;

                        case 4: cout<<"Saliendo..."; return 0;
                    }
                }while(opc != 3); 
            break;
            //Buscar y Listar Informacion
            case 3:
                do{
                    menuBuscaryListar();
                    cout<<"Opcion: "; cin>>opc;
                    switch(opc){
                        case 1: consultarLocalidad(arbol);
                        break;

                        case 2: listadoLocalidadesAlfabetico(arbol, primero, ultimo);
                        break;

                        case 3: buscarRutas(grafo, arbol, L);
                        break;

                        case 4: mostrarCiudadesAdyacentes(grafo, arbol);
                        break;

                        case 6: cout<<"Saliendo..."; return 0;
                    }
                }while(opc != 5); 
            break;
            // Respaldar Informacion
            case 4:
                do{
                    menuMostrarRespaldo();
                    cout<<"Opcion: "; cin>>opc;
                    switch(opc){
                        case 1: listadoLocalidadesExistentes(arbol, localidades, L);
                        break;

                        case 2: listadoLocalidadesEliminadas();
                        break;

                        case 3: listadoRutasEliminadas();
                        break;

                        case 5: cout<<"Saliendo..."; return 0;
                    }
                }while(opc != 4);
            break;

            case 5:
            break;

            case 6: cout<<"Saliendo..."<<endl; break;
            default: cout<<"Opcion no encontrada"<<endl; break;
        }
        
    }while(opc != 6);

    return 0;
}
void menuPrincipal(){
    /// @brief menu principal del programa
    cout<<"1. Agregar informacion"<<endl;
    cout<<"2. Eliminar informacion"<<endl;
    cout<<"3. Buscar y Listar"<<endl;
    cout<<"4. Mostrar Respaldos"<<endl;
    cout<<endl;
    cout<<"5. Creditos"<<endl;
    cout<<"6. Salir de la aplicacion"<<endl;
}
void menuAgregarInformacion(){
    /// @brief menu de la opcion agregar informacion
    cout<<"1. Agregar localidad"<<endl;
    cout<<"2. Agregar relacion o ruta"<<endl;
    cout<<endl;
    cout<<"3. Volver a principal"<<endl;
    cout<<"4. Salir de la aplicacion"<<endl;
}
void menuEliminarInformacion(){
    /// @brief menu de la opcion eliminar informacion
    cout<<"1. Eliminar localidad"<<endl;
    cout<<"2. Eliminar relacion o ruta"<<endl;
    cout<<endl;
    cout<<"3. Volver a principal"<<endl;
    cout<<"4. Salir de la aplicacion"<<endl;
}
void menuBuscaryListar(){
    /// @brief Menu de la opcion buscar y listar
    cout<<"1. Consultar localidad"<<endl;
    cout<<"2. Listado de localidades"<<endl;
    cout<<"3. Buscar ruta"<<endl;
    cout<<"4. Ciudades adyacentes"<<endl;
    cout<<endl;
    cout<<"5. Volver a principal"<<endl;
    cout<<"6. Salir de la aplicacion"<<endl;
}
void menuMostrarRespaldo(){
    /// @brief Menu de la opcion mostrar respaldo
    cout<<"1. Listado de localidades existentes"<<endl;
    cout<<"2. Listado de localidades eliminadas"<<endl;
    cout<<"3. Listados de rutas eliminadas"<<endl;
    cout<<endl;
    cout<<"4. Volver a principal"<<endl;
    cout<<"5. Salir de la aplicacion"<<endl;
}
void clean_stdin(void){

    /**
     * @brief Limpiar buffer de la memoria
     * 
    */
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
void leerArchivo(int &l, int &r, bool &flag){

    /**
     * @brief Lee las cantidades de localidades y relaciones del archivo localidades.dat
     * @param l Cantidad total de localidades en el archivo
     * @param r Cantidad total de rutas en el archivo
     * @param flag Bandera que nos ayuda con el control de la cantidad total de localidades y relaciones
    */
    
    int cont=0;
    char L[10];
    char R[10];
    string linea;
    ifstream leerL;
    leerL.open("localidades.dat",ios::in);  //Abrimos el archivo

    if(leerL.is_open()){

        while(getline(leerL, linea)) {

            if(cont == 0) {
                    
                leerL.getline(L, 10);  //Leemos la cantidad de localidades del archivo
            }
            cont++;
        }
    }
    else{
        cout<<"No se abrio el archivo"<<endl;
    }

    l = atoi(L); //atoi: Transforma un string a int

    cont = 0;
    string linea2;
    leerL.close();

    leerL.open("localidades.dat",ios::in); 

    if(leerL.is_open()){

        while(getline(leerL, linea2)) {

            if(cont == l+2) {
                    
                leerL.getline(R, 10);   //Leemos la cantidad de relaciones del archivo
            }
            cont++;
        }
    }
    else{
        cout<<"No se abrio el archivo"<<endl;
    }
    r = atoi(R);

    if((l < 1 || l > 1000) || (r < 1 || r > 500)){  //Si alguna de las dos cantidades no se encuentra dentro de los limites
        flag = true;
        return;
    }

}
void leerLocalidadesArchivo(Localidad *&local, int L){

    /**
     * @brief Leemos cada linea de localidades y guardamos cada atributo en su campo respectivo, despues guardamos cada localidad en el arreglo
     * @param local Arreglo de localidades
     * @param L Numero total de localidades
    */

    int cont=0;
    string nombre, coorx, coory, linea;
    ifstream leerL;
    leerL.open("localidades.dat",ios::in);

    if(leerL.is_open()){
    int i=0;
        while((getline(leerL, linea)) && (cont != L+2)){

            if(cont >= 2){
                stringstream atributo(linea); //stringstream usado para leer la linea y guardar en cada variable un atributo mediante limitadores, en este caso la coma
                                            // Este tipo de dato se usara durante todo el proyecto
                getline(atributo, nombre, ',' );
                getline(atributo, coorx, ',');
                getline(atributo, coory, '\n');

                coorx.erase(remove_if(coorx.begin(), coorx.end(), ::isspace), coorx.end());  //Borra espacios
                coory.erase(remove_if(coory.begin(), coory.end(), ::isspace), coory.end());  //Borra espacios

                //Guardamos cada atributo dentro de su correspondiente en el arreglo
                local[i].nombre = nombre; 
                local[i].coorx = coorx;
                local[i].coory = coory;
                i++;
            }
            cont++;
        }    
    }
    else{
        cout<<"No se abrio el archivo"<<endl;
    }

    leerL.close();
}
NodoArbol *crearNodoArbol(Localidad localidades, NodoArbol *padre){
    /**
    * @brief Se crea el nodo con la informacion de la localidad para insertarlo al Arbol Binario
    * 
    * @param localidades Arreglo de localidades
    * @param padre Nodo padre del nuevo nodo
    * @return NodoArbol* Nodo que sera ingresado al Arbol Binario
    */
    NodoArbol *nuevo;
    nuevo = new NodoArbol();
    nuevo->dato = localidades;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    nuevo->padre = padre;

    return nuevo;
}
void insertarAlArbol(NodoArbol *&arbol, Localidad *localidades, int &i, NodoArbol *padre){  

    /**
    * @brief Se inserta cada nodo al abrol binario de busqueda donde con respecto al nodo raiz quedan a la derecha los mayores y a la izquierda los menores
    * 
    * @param arbol Estructura Arbol
    * @param localidades Arreglo de localidades
    * @param i inidice del arreglo de localidades
    * @param padre Nodo padre del nodo a ingresar al arbol
    */
    
    if(arbol == NULL){  //Si el arbol esta vacio

        NodoArbol *nuevo;
        nuevo = crearNodoArbol(localidades[i], padre);
        arbol = nuevo;
    }else{
        
        string DatoRaiz = arbol->dato.nombre;  //se guarda el dato del nodo raiz

        if(localidades[i].nombre == DatoRaiz){  //Si ya existe la localidad simplemente retornamos
            return;
        }
        else if(localidades[i].nombre < DatoRaiz){

            insertarAlArbol(arbol->izq, localidades, i, arbol);
        }else{

            insertarAlArbol(arbol->der, localidades, i, arbol);
        }
    }
}
void agregarArista(NodoGrafo *&aux, NodoGrafo *&aux2, Arista *&nuevo){

    /**
    * @brief Se agrega una arista como relacion entre dos localidades dentro del grafo
    * 
    * @param aux Primer nodo del grafo (Localidad Origen)
    * @param aux2 Segundo nodo del grafo (Localidad Destino)
    * @param nuevo Nueva arista que se crea
    */
    Arista *q;
    
    if(aux->adyacente == NULL){ //Si la lista esta vacia
        
        aux->adyacente = nuevo;
        nuevo->destino = aux2;
    }
    else{

        q = aux->adyacente;

        while(q->siguiente != NULL){

            q = q->siguiente;
        }

        nuevo->destino = aux2;
        q->siguiente = nuevo;
    }
}
void insertarArista(NodoGrafo *grafo, Arista *&arista, string loc1, string loc2, Ruta rutas){

    /**
    * @brief Busca las posiciones de memoria de los nodos de las localidades dentro del grafo para insertar la relacion entre ellos mediante una arista
    * 
    * @param grafo Estructura grafo
    * @param arista Estructura arista
    * @param loc1 Primera localidad a relacionar (Origen)
    * @param loc2 Segunda localidad a relacionar (Destino)
    * @param rutas Atributos de las rutas
    */
    
    Arista *nuevo= new Arista();
    NodoGrafo *aux, *aux2;
    nuevo->siguiente = NULL;
    nuevo->rutas = rutas;
    aux = grafo;
    aux2 = grafo;
    //Se hace bucles para recorrer el grafo y encontrar el dato buscado
    while(aux2 != NULL){
    
        if(aux2->dato.nombre == loc2){   //Se busca la localidad destino dentro del grafo, principalmente para su posicion dentro del mismo
            break;
        }

        aux2=aux2->siguiente;
    }
    while(aux != NULL){
    
        if(aux->dato.nombre == loc1){  

            agregarArista(aux, aux2, nuevo);   //Una vez encontrado la localidad origen
            return;
        }

        aux = aux->siguiente;
    }
}
void insertarNodoGrafo(NodoGrafo *&grafo, Localidad local){

    /**
    * @brief Se inserta el nodo de la localidad dentro del grafo
    * 
    * @param grafo Estructura grafo
    * @param local Arreglo de las localidades
    */
    
    NodoGrafo *nuevo = new NodoGrafo();
    NodoGrafo *aux;
    nuevo->dato = local;
    nuevo->siguiente = NULL;
    nuevo->adyacente = NULL;

    if(grafo==NULL){      //Si el grafo esta vacio

        grafo = nuevo;    
    }else{

        aux = grafo;
        
        while(aux->siguiente != NULL){    //si ya existe un nodo dentro del grafo
            
            if(aux->siguiente->dato.nombre == nuevo->dato.nombre || aux->dato.nombre == nuevo->dato.nombre){  //Ya esa localidad se encuentra en el grafo
                return;
            }
            else{
                aux = aux->siguiente;
            }
        }
        aux->siguiente = nuevo;
    }
}
void insertarRelacionesInicio(NodoGrafo *&grafo, Arista *&arista, Localidad *local, string loc1, string loc2, Ruta rutas, int L){
    
    /**
    * @brief Se agregan todas las relaciones del archivo inicial con sus respectivas caracteristicas dentro de un grafo con lista de adyacencia
    * 
    * @param grafo Estructura grafo
    * @param arista Estructura arista
    * @param local Arreglo de las localidades
    * @param loc1 Primera localidad a relacionar (Origen)
    * @param loc2 Segunda localidad a relacionar (Destino)
    * @param rutas Atributos de cada ruta
    * @param L Cantidad de localidades en el archivo
    */

    bool flag, flag2;
    Localidad aux[2];

    for(int i=0; i < L; i++){

        if(loc1 == local[i].nombre){

            flag = false;
            insertarNodoGrafo(grafo, local[i]);
            break;
        }
        else{

            flag = true;
        }
    }
    for(int i=0; i < L; i++){

        if(loc2 == local[i].nombre){

            flag2 = false;
            insertarNodoGrafo(grafo, local[i]);
            break;
        }
        else{

            flag2 = true;
        }
    }
    if(flag){  //Si la localidad origen no esta dentro del arreglo

        aux[0].nombre = loc1;
        insertarNodoGrafo(grafo, aux[0]);
    }
    if(flag2){ //Si la localidad destino no esta dentro del arreglo

        aux[1].nombre = loc2;
        insertarNodoGrafo(grafo, aux[1]);
    }

    //Se llama la accion para insertar las aristas;
    insertarArista(grafo, arista, loc1, loc2, rutas); 
    insertarArista(grafo, arista, loc2, loc1, rutas);
}
void leerRutasArchivo(NodoGrafo *&grafo, Arista *&arista, Ruta &rutas, int R, int L, Localidad *local){

    /**
    * @brief Se lee cada linea del archivo al inicio del programa para separar cada relacion en sus diferentes atributos, es decir, 
    *       las localidades que se relacionan y sus caracteristicas
    * 
    * @param grafo Estructura grafo
    * @param arista Estructura arista
    * @param rutas Registro de las caracteristicas de cada ruta
    * @param R Cantidad de relaciones en el archivo
    * @param L Cantidad de localidades en el archivo
    * @param local Arreglo de localidades
    */

    int cont = 0;
    string linea, loc1, loc2, distancia, tiempo, tipo;
    ifstream leerR;

    leerR.open("localidades.dat",ios::in);
    if(leerR.is_open()){
    int i=0;
        while((getline(leerR, linea))){
    
            if(cont >= L + 4){
                stringstream atributo(linea);
                getline(atributo, loc1, ',' );
                getline(atributo, loc2, ',');
                getline(atributo, distancia, ',');
                getline(atributo, tiempo, ',');
                getline(atributo, tipo, '\n');

                //Borras espacios de cada atributo
                loc2.erase(loc2.begin()); 
                distancia.erase(remove_if(distancia.begin(), distancia.end(), ::isspace), distancia.end());  
                tiempo.erase(remove_if(tiempo.begin(), tiempo.end(), ::isspace), tiempo.end()); 
                tipo.erase(remove_if(tipo.begin(), tipo.end(), ::isspace), tipo.end());  

                rutas.distancia = distancia;
                rutas.tiempo = tiempo;
                rutas.tipo = tipo;
                
                //Llamamos a la funcion insertarRelacionesInicio para llenar el grafo despues de cada linea leida
                insertarRelacionesInicio(grafo, arista, local, loc1, loc2, rutas, L);
            }
            cont++;
        }
    }
    else{
        cout<<"No se abrio el archivo"<<endl;
    }

    leerR.close();
}
NodoGrafo *buscarNodoGrafo(NodoGrafo *grafo, string loc){

    /**
     * @brief Se busca la localidad dentro del grafo
     * 
     * @param grafo Estructura grafo
     * @param loc nombre de la localidad a buscar
     * @return NodoGrafo* Nodo dentro del grafo
    */

    while(grafo != NULL){

        if(grafo->dato.nombre == loc){

            return grafo;
        }
        grafo = grafo->siguiente;
    }
    return grafo;
}
bool existeLocalidad(NodoArbol *arbol, string loc){

    /**
    * @brief Se busca la localidad dentro del arbol
    * 
    * @param arbol Estructura Arbol
    * @param loc nombre de la localidad a buscar
    * @return true Si se encontro la localidad
    * @return false Si no se encontro la localidad
    */

    if(arbol == NULL){
        return false;
    }
    else if(arbol->dato.nombre == loc){
        return true;
    }
    else if(loc < arbol->dato.nombre){
        return existeLocalidad(arbol->izq, loc);
    }
    else{
        return existeLocalidad(arbol->der, loc);
    }
}
void encontrarLocalidad(NodoArbol *arbol, NodoArbol *&aux, string loc, string coorx, string coory){

    /**
    * @brief Se recorre el arbol de forma PostOrden para encontrar la localidad y mostrar su informacion
    * 
    * @param arbol Estructura arbol
    * @param loc Localidad a buscar
    * @param coorx Coordenada X a buscar
    * @param coory Coordenada Y a buscar
    */

    if(arbol == NULL){
        return;
    }
    else{
        encontrarLocalidad(arbol->izq, aux, loc, coorx, coory);
        encontrarLocalidad(arbol->der, aux, loc, coorx, coory);
        if(arbol->dato.nombre == loc || (arbol->dato.coorx == coorx && arbol->dato.coory == coory)){
            aux = arbol;
            return;
        }
    }
}
void separarLocalidad(string linea, string &nombre, string &coorx, string &coory){

    /**
    * @brief Se separa lo ingresado por el usuario en nombre, coordenada x, coordenada y
    * 
    * @param linea Linea del formato que ingreso el usuario
    * @param nombre Nombre de la localidad
    * @param coorx  Coordenada x de la localidad
    * @param coory  Coordenada y de la localidad
    */

    stringstream atributo(linea);
    getline(atributo, nombre, ',' );
    getline(atributo, coorx, ',');
    getline(atributo, coory, '\n');

    coorx.erase(remove_if(coorx.begin(), coorx.end(), ::isspace), coorx.end());  //Borra espacios
    coory.erase(remove_if(coory.begin(), coory.end(), ::isspace), coory.end());  //Borra espacios

}
void agregarLocalidad(NodoArbol *arbol){

    /**
    * @brief Agrega una localidad al sistema mediante un arbol binario de busqueda
    * 
    * @param arbol Estructura arbol
    */

    string linea, nombre, coorx, coory;
    int i=0;
    Localidad local[1];
    //Archivo resultados.out
    ofstream archivo;
    archivo.open("resultados.out", ios::app);

    clean_stdin();
    fflush(stdin);
    cout<<"Digite la Localidad a agregar: "; getline(cin, linea);

    separarLocalidad(linea, nombre, coorx, coory);
    if(validarFormatoLocalidad(nombre, coorx, coory)){
        cout<<endl;
        cout<<"FORMATO INCORRECTO"<<endl;
        cout<<endl;
        return;
    }

    local[0].nombre = nombre;
    local[0].coorx = coorx;
    local[0].coory = coory;

    if(existeLocalidad(arbol, nombre)){

        //Escribir en  resultados.out
        archivo<<"0"<<endl;
        archivo.close();
        
        cout<<endl;
        cout<<"La localidad "<<nombre<<" ya esta registrada en el sistema."<<endl;
    }
    else{

        insertarAlArbol(arbol, local, i, NULL);

        //Escribir en  resultados.out
        archivo<<"1"<<endl;
        archivo.close();

        cout<<endl;
        cout<<"La localidad "<<nombre<<" ha sido agregada."<<endl;
    }
}
bool validarFormatoLocalidad(string nombre, string coorx, string coory){

    /**
    * @brief Valida que el formato ingresado por el usuario sea correcto, usamos isalpha como metodo para saber si el string es de letras o numeros
    * 
    * @param nombre Nombre de la localidad ingresada
    * @param coorx Coordenada X de la localidad ingresada
    * @param coory Coordenada Y de la localidad ingresada
    * @return true Si el formato no es correcto
    * @return false Si el formato es el correcto
    */
    
    if(coorx.empty() || coory.empty()){
        
        return true;
    }
    else if(!(isalpha(nombre[0]))){
        
        return true;
    }
    else if((isalpha(coorx[0]))){
        
        return true;
    }
    else if((isalpha(coory[0]))){
        
        return true;
    }
    return false;
}
NodoArbol *minimo(NodoArbol *arbol){

    /**
    * @brief Se busca el nodo mas a la izquierda posible del nodo pasado por parametro
    * 
    * @param arbol Estructura arbol (Posicion dentro del arbol especifica)
    * @return NodoArbol* Nodo deseado
    */

    if(arbol == NULL){ //Si esta vacio
        return NULL;
    }
    else if(arbol->izq){ //Tiene hijo izquierdo

        return minimo(arbol->izq);  
    }
    else{  //Si no tiene mas hijos izquierdos

        return arbol;  //Retornamos el arbol en el que ya estamos
    }
}
void reemplazar(NodoArbol *arbol, NodoArbol *nuevoNodo){

    /**
    * @brief Reemplazamos el nodo que queremos eliminar por el nuevo nodo en su posicion en el arbol
    * 
    * @param arbol Nodo que se va a eliminar
    * @param nuevoNodo Nuevo nodo que tomara su posicion
    */

    if(arbol->padre){

        //Si el nodo tiene padre entonces hay que asignarle un nuevo hijo
        if(arbol->padre->izq){
            if(arbol->dato.nombre == arbol->padre->izq->dato.nombre){  //Si el elemento es el hijo izquierdo
                arbol->padre->izq = nuevoNodo;
            }
        }
        if(arbol->padre->der){
            if(arbol->dato.nombre == arbol->padre->der->dato.nombre){   //Si es el hijo derecho
                arbol->padre->der = nuevoNodo;
            }
        }
    }
    if(nuevoNodo){
        //Asignamos el nuevo padre del nodo
        nuevoNodo->padre = arbol->padre;
    }
}
void destruirNodo(NodoArbol *nodo){

    /**
    * @brief Se Elimina el nodo de la memoria
    * 
    * @param nodo Nodo a eliminar
    */

    nodo->izq = NULL;
    nodo->der = NULL;

    delete nodo;
}
void eliminarNodoArbol(NodoArbol *nodoEliminar){
    /**
     * @brief Se hace uso de las funciones y acciones reemplazar, minimo y destruirNodo eliminar el nodo especificado del arbol binario de busqueda
     * 
     * @param nodoEliminar Nodo que se va a eliminar del arbol
    */

    //Si el nodo tiene los dos hijos
    if(nodoEliminar->izq && nodoEliminar->der){

        NodoArbol *menor = minimo(nodoEliminar->der);
        nodoEliminar->dato = menor->dato;  // se cambian los datos del eliminado por el menor encontrado
        eliminarNodoArbol(menor);

    //Si el nodo tiene un solo hijo
    }else if(nodoEliminar->izq){ //Si el nodo tiene un hijo izquierdo
          
        reemplazar(nodoEliminar, nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    
    }else if(nodoEliminar->der){  //Si el nodo tiene un hijo derecho

        reemplazar(nodoEliminar, nodoEliminar->der);
        destruirNodo(nodoEliminar);

    //Si el nodo no tiene hijos
    }else{
        reemplazar(nodoEliminar, NULL);
        destruirNodo(nodoEliminar);
    }
}
void eliminarArista(NodoGrafo *&grafo, string org, string dest){

    /**
     * @brief Se elimina la relacion (Arista que une los nodos) entre el la localidad origen y la localidad destino
     * 
     * @param grafo Estructura grafo
     * @param org Nombre de la localidad origen
     * @param dest Nombre de localidad destino
    */

    NodoGrafo *aux, *aux2;
    Arista *q, *r;
    aux = grafo;
    aux2 = grafo;

    while(aux2!=NULL){
        if(aux2->dato.nombre == dest){
            break;
        }
        else{
            aux2=aux2->siguiente;
        }
    }

    while(aux!=NULL){

        if(aux->dato.nombre==org){

            q = aux->adyacente;
            while(q!=NULL){
                if(q->destino==aux2){

                    if(q==aux->adyacente){
                        aux->adyacente = aux->adyacente->siguiente;
                    }
                    else{
                        r->siguiente = q->siguiente;
                    }
                    delete(q);
                    return;
                }
                r=q;
                q=q->siguiente;
            }
        }
        aux = aux->siguiente;
    }
}
void vaciarRelaciones(NodoGrafo *&aux){

    /**
     * @brief Se eliminan todas las relaciones de la localidad
     * 
     * @param aux Nodo que tiene el dato de la localidad a eliminar
    */

    Arista *ar, *q;

    ar = aux->adyacente;
    while(ar->siguiente != NULL){
        
        q = ar;
        ar =ar->siguiente;
        delete(q);
    }
}
void eliminarNodoGrafo(NodoGrafo *&grafo, string loc){

    /**
     * @brief Se busca y se elimina el nodo dentro del grafo que contiene el dato de la localidad a eliminar
     * 
     * @param grafo Estructura grafo
     * @param loc Nombre de la localidad a eliminar
    */

    NodoGrafo *aux, *ant;
    aux = grafo;

    while(aux != NULL){

        if(aux->dato.nombre == loc){

            if(aux->adyacente != NULL){
                vaciarRelaciones(aux);
            }
            if(aux == grafo){

                grafo = grafo->siguiente;
                delete (aux);
                return;
            }
            else{
                ant->siguiente = aux->siguiente;
                delete(aux);
                return;
            }
        }else{
            ant = aux;
            aux = aux->siguiente;
        }
    }

}
void buscarLocalidadAEliminar(NodoArbol *arbol, NodoGrafo *&grafo, string loc){

    /**
     * @brief Se busca dentro del arbol la localidad a eliminar y comienza el proceso de eliminacion mediante otras funciones y acciones,
     *         ademas se busca el nodo dentro del grafo para tambien eliminarlo y sus respectivas relaciones
     * 
     * @param arbol Estructura arbol
     * @param grafo Estructura grafo
     * @param loc Nombre de la localidad a eliminar
    */

    NodoGrafo *aux;
    Arista *ar;

    if(arbol == NULL){
        return;

    }else if(loc < arbol->dato.nombre){
    
        buscarLocalidadAEliminar(arbol->izq, grafo, loc);

    }else if(loc > arbol->dato.nombre){

        buscarLocalidadAEliminar(arbol->der, grafo, loc);

    }else if(loc == arbol->dato.nombre){

        aux = buscarNodoGrafo(grafo, loc);
        ar = aux->adyacente;

        while(ar != NULL){

            eliminarArista(grafo, ar->destino->dato.nombre, loc);
            ar = ar->siguiente;
        }

        eliminarNodoArbol(arbol);
        eliminarNodoGrafo(grafo, loc);
        return;
    }

}
void eliminarLocalidad(NodoArbol *&arbol, NodoGrafo *&grafo){

    /**
     * @brief Se ingresa la localidad a eliminar se llama a una funcion que busca la localidad dentro del arbol para comenzar su eliminacion
     * 
     * @param arbol Estructura arbol
     * @param grafo Estructura grafo
    */

    string linea, nombre, coorx, coory;
    NodoArbol *aux = NULL;
    //Archivo resultados.out
    ofstream archivo;
    archivo.open("resultados.out", ios::app);

    clean_stdin();
    fflush(stdin);
    cout<<"Que localidad desea eliminar?: "; getline(cin, linea);

    separarLocalidad(linea, nombre, coorx, coory);

    encontrarLocalidad(arbol, aux, nombre, coorx, coory);
    
    if(aux == NULL){
        archivo<<"0"<<endl;
        archivo.close();

        cout<<endl;
        cout<<"La localidad no esta en el sistema"<<endl;
    }else{  
        
        ofstream respaldo;
        string localidad_resp;
        //Se respalda la localidad en un archivo
        respaldo.open("localidades_resp.dat", ios::app);

        localidad_resp = aux->dato.nombre + ", " + aux->dato.coorx + ", " + aux->dato.coory;
        respaldo<<localidad_resp<<endl;

        respaldo.close();
        cout<<endl;
        archivo<<"1"<<endl;
        archivo.close();

        buscarLocalidadAEliminar(arbol, grafo, nombre);
        cout<<"La Localidad "<<nombre<<" fue eliminada del sistema"<<endl;
    }
}
void separarRuta(string linea, string &loc1, string &loc2, string &dist, string &tiempo, string &tipo){

    /**
     * @brief Se separa lo ingresado por el usuario en nombre de la localidad origen, nombre de la localidad destino, distancia, tiempo y tipo
     * 
     * @param linea Linea ingresada por el usuario
     * @param loc1 Nombre de la localidad origen
     * @param loc2 Nombre de la localidad destino
     * @param dist Caracteristica distancia de la ruta
     * @param tiempo Caracteristica tiempo de la ruta
     * @param tipo Caracteristica tipo de la ruta
    */

    stringstream atributo(linea);
    getline(atributo, loc1, ',' );
    getline(atributo, loc2, ',');
    getline(atributo, dist, ',');
    getline(atributo, tiempo, ',');
    getline(atributo, tipo, '\n');

    loc2.erase(loc2.begin());  //Borra espacios
    dist.erase(remove_if(dist.begin(), dist.end(), ::isspace), dist.end());  //Borra espacios
    tiempo.erase(remove_if(tiempo.begin(), tiempo.end(), ::isspace), tiempo.end());  //Borra espacios
    tipo.erase(remove_if(tipo.begin(), tipo.end(), ::isspace), tipo.end());  //Borra espacios
}
bool validarFormatoRelacion(string loc1, string loc2, string dist, string tiempo, string tipo){

    /**
     * @brief Valida que el formato ingresado por el usuario sea correcto, usamos isalpha como metodo para saber si el string es de letras o numeros
     * 
     * @param loc1 Nombre de la localidad origen
     * @param loc2 Nombre de la localidad destino
     * @param dist Caracteristica distancia de la ruta
     * @param tiempo Caracteristica tiempo de la ruta
     * @param tipo Caracteristica tipo de la ruta
     * @return true Si hay un error en el formato
     * @return false Si el formato es correcto
    */

    if(dist.empty() || tiempo.empty() || tipo.empty()){
        
        return true;
    }
    else if(!(isalpha(loc1[0]))){
        
        return true;
    }
    else if(!(isalpha(loc2[0]))){
        
        return true;
    }
    else if((isalpha(dist[0]))){
        
        return true;
    }
    else if((isalpha(tiempo[0]))){
        
        return true;
    }
    else if(!(isalpha(tipo[0]))){
        
        return true;
    }
    return false;
}
NodoArbol *encontrarNodo(NodoArbol *arbol, string loc){

    /**
     * @brief Encontrar un nodo dentro del arbol que tenga como dato la localidad buscada
     * 
     * @param arbol Estructura arbol
     * @param loc Nombre de la localidad a buscar
     * @return NodoArbol* Nodo dentro del arbol
    */

    if(arbol == NULL){
        return arbol;
    }
    else if((arbol->dato.nombre == loc)){
        return arbol;
    }
    else if(loc < arbol->dato.nombre){
        return encontrarNodo(arbol->izq, loc);
    }
    else{
        return encontrarNodo(arbol->der, loc);
    }
}
bool existeRuta(NodoGrafo *grafo, string loc){

    /**
     * @brief Verificar si existe una ruta entre una localidad de del grafo y una localidad especificada
     * 
     * @param grafo Nodo dentro del grafo que contiene la localidad origen
     * @param loc Nombre de la localidad destino
     * @return true Existe la ruta
     * @return false No existe la ruta
    */

    Arista *ar;

    if(grafo == NULL){
        return false;
    }
    else{
        ar = grafo->adyacente;

        while(ar != NULL){
            if(ar->destino->dato.nombre == loc){
                return true;
            }
            ar = ar->siguiente;
        }
        return false;
    }
}
void agregarRelacion(NodoGrafo *&grafo,Arista *&arista, NodoArbol *arbol, Ruta rutas){

    /**
     * @brief Se agrega una ruta entre dos localidades, mediante uso del grafo y las aristas
     * 
     * @param grafo Estructura grafo
     * @param arista Estructura arista
     * @param arbol Estructura arbol
     * @param rutas Registro con las caracterisitcas de cada ruta
    */

    string linea, loc1, loc2, tiempo, distancia, tipo;
    Localidad local[2];
    ofstream archivo;
    archivo.open("resultados.out", ios::app);

    clean_stdin();
    fflush(stdin);
    cout<<"Ingrese la relacion o ruta: "; getline(cin, linea);

    separarRuta(linea, loc1, loc2, distancia, tiempo, tipo);
    if(validarFormatoRelacion(loc1, loc2, distancia, tiempo, tipo)){

        cout<<endl;
        cout<<"FORMATO INCORRECTO"<<endl;
        cout<<endl;
        return;
    }
    else{

        rutas.distancia = distancia;
        rutas.tiempo = tiempo;
        rutas.tipo = tipo;
        
        NodoArbol *aux = encontrarNodo(arbol, loc1);
        NodoArbol *aux2 = encontrarNodo(arbol, loc2);
        if(aux == NULL){

            //Escribir en  resultados.out
            archivo<<"-3"<<endl;
            archivo.close();

            cout<<endl;
            cout<<"La localidad "<<loc1<<" no esta en el sistema"<<endl;
            return;
        }
        else if(aux2 == NULL){

            //Escribir en  resultados.out
            archivo<<"-2"<<endl;
            archivo.close();

            cout<<endl;
            cout<<"La localidad "<<loc2<<" no esta en el sistema"<<endl;
            return;
        }else{

            local[0] = aux->dato;
            local[1] = aux2->dato;
    
            NodoGrafo *auxg = buscarNodoGrafo(grafo, loc1);


            if(existeRuta(auxg, loc2)){

                //Escribir en  resultados.out
                archivo<<"0"<<endl;
                archivo.close();

                cout<<endl;
                cout<<"Ya existe una ruta entre las localidades"<<endl;
                return;
            }

            insertarNodoGrafo(grafo, local[0]);
            insertarNodoGrafo(grafo, local[1]);

            insertarArista(grafo, arista, loc1, loc2, rutas);
            insertarArista(grafo, arista, loc2, loc1, rutas);


            //Escribir en  resultados.out
            archivo<<"1"<<endl;
            archivo.close();

            cout<<endl;
            cout<<"Se agrego una ruta entre "<<loc1<<" y "<<loc2<<endl;
        }
    }
}
void consultarLocalidad(NodoArbol *arbol){

    /**
     * @brief Se introduce nombre o coordenadas de una localidad para mostrar su respectiva informacion buscandola dentro del arbol
     * 
     * @param arbol Estructura arbol
    */

    int opc=0;
    string loc, coorx, coory, linea;
    bool flag = false;

    cout<<"De que forma buscara la Localidad?"<<endl;
    cout<<"1.Nombre"<<endl;
    cout<<"2.Coordenadas"<<endl;
    cout<<"Opcion: ";
    cin>>opc;
    switch(opc){
        //Eligio Busqueda por Nombre
        case 1:
            clean_stdin();
            fflush(stdin);
            cout<<"Ingrese el nombre de la Localidad: ";
            getline(cin, loc);
        break;
        //Eligio Busqueda por Coordenadas
        case 2: flag = true;
        break;

        default: cout<<"OPCION NO VALIDA"<<endl; break;
    }
    if(flag){
        //Si eligio busqueda por coordenadas entra en este if
        clean_stdin();
        fflush(stdin);
        cout<<"Ingrese las Coordenadas de la localidad: ";
        getline(cin, linea);

        stringstream atributo(linea);
        getline(atributo, coorx, ',');
        getline(atributo, coory, '\n');
        coorx.erase(remove_if(coorx.begin(), coorx.end(), ::isspace), coorx.end());  //Borra espacios
        coory.erase(remove_if(coory.begin(), coory.end(), ::isspace), coory.end());  //Borra espacios
    }

    NodoArbol *aux = NULL;
    encontrarLocalidad(arbol, aux, loc, coorx, coory);
    if(aux == NULL){
        cout<<endl;
        cout<<"La localidad no esta en el sistema"<<endl;
    }else{

        cout<<endl;
        cout<<"Localidad: "<<aux->dato.nombre<<", "<<aux->dato.coorx<<", "<<aux->dato.coory<<endl;
    }
}
void mezclar(Localidad *&array, int ini, int mitad, int fin){

    /**
     * @brief Se mezcla y ordena el arreglo de localidades
     * 
     * @param array Arreglo de localidades
     * @param ini Primera posicion del arreglo
     * @param mitad Posicion de la mitad del arreglo
     * @param fin Ultima posicion del arreglo
    */
    
    Localidad *aux = new Localidad[1000];
    int i, j, k;

    k=0;
    i = ini;
    j = mitad+1;
    while(i <= mitad && j <= fin){
        k++;
        if(array[i].nombre < array[j].nombre){
            aux[k] = array[i];
            i++;
        }
        else{
            aux[k] = array[j];
            j++;
        }
    }

    for(int t = i; t <= mitad; t++){
        k++;
        aux[k]= array[t];
    }
    for(int t = j; t <= fin; t++){
        k++;
        aux[k]= array[t];
    }
    for(int t = 1; t <= k; t++){
        array[ini+t-1] = aux[t];
    }

    delete[] aux;
}
void mergeSort(Localidad *&array, int ini, int fin){

    /**
     * @brief Se utiliza el metodo MergeSort para ordenar el arreglo, separando en mitades cada vez mas peque�as
     * 
     * @param array Arreglo de localidades
     * @param ini Pimera posicion del arreglo
     * @param fin Ultima posicion del arreglo
    */

    int mitad;

    if(ini < fin){
        mitad = (ini + fin)/2;  
        mergeSort(array, ini, mitad);
        mergeSort(array, mitad +1 , fin);
        mezclar(array, ini, mitad, fin);
    }
}
void contarLocalidades(NodoArbol *arbol, int &cont){
    
    /**
     * @brief Cantidad de localidades en el arbol
     * 
     * @param arbol Estructura arbol
     * @param cont Contador
    */

    if(arbol == NULL){
        return;
    }
    else{
        cont++;
        contarLocalidades(arbol->izq, cont);
        contarLocalidades(arbol->der, cont);
    }
}
void agregarAlArreglo(NodoArbol *arbol, Localidad *array, int &i){

    /**
     * @brief Se agregan a un arreglo todas las localidades existentes en el arbol mediante un recorrido PreOrden
     * 
     * @param arbol Estructura arbol
     * @param array Arreglo de localidades
     * @param i Indice del arreglo
    */

    if(arbol == NULL){
        return;
    }
    else{
        array[i] = arbol->dato;
        i++;
        agregarAlArreglo(arbol->izq, array, i);
        agregarAlArreglo(arbol->der, array, i);
    }
}
void insertarCola(NodoCola *&primero, NodoCola *&ultimo, Localidad *array, int cont){
    
    /**
     * @brief Se insertan a la cola el arreglo de localidades ordenado de forma alfabetica ascendete
     * 
     * @param primero Primero nodo de la cola
     * @param ultimo Ultimo nodo de la cola
     * @param array Arreglo ordenado de localidades
     * @param cont Cantidad total de localidades en el arreglo
    */

    for(int i=0; i<cont; i++){

        NodoCola *nuevo = new NodoCola();
        nuevo->dato = array[i];
        nuevo->siguiente = NULL;

        if(primero == NULL && ultimo==NULL){

            primero = nuevo;
        }
        else{
            ultimo->siguiente = nuevo;
        }
        ultimo = nuevo;
    }
}
void mostrarCola(NodoCola *&primero, NodoCola *&ultimo){

    /**
     * @brief Se recorre y muestra toda la estructura cola
     * 
     * @param primero Primero nodo de la cola
     * @param ultimo Ultimo nodo de la cola
    */

    while(primero != NULL){

        Localidad n;
        NodoCola *aux;
        aux = primero;

        n = primero->dato;

        if(primero==ultimo){
            
            primero = NULL;
            ultimo = NULL;
        }
        else{

            primero = primero->siguiente;
        }

        delete aux;

        cout<<n.nombre<<", "<<n.coorx<<", "<<n.coory<<endl;
    }
}
void listadoLocalidadesAlfabetico(NodoArbol *arbol, NodoCola *&primero, NodoCola *&ultimo){

    /**
     * @brief Accion en la que mostramos alfabeticamente las localidades del sistema, mediante un arreglo auxiliar de localidades, el cual ordenamos
     *       e insertamos dentro de una cola para despues recorrerla y mostrarla
     * 
     * @param arbol Estructura arbol
     * @param primero Primer nodo de la estrctura cola
     * @param ultimo Ultimo nodo de la estructura cola
    */

    int cont=0, i=0;
    contarLocalidades(arbol, cont);

    Localidad *array = new Localidad[cont];

    agregarAlArreglo(arbol, array, i); 
    mergeSort(array, 0, cont-1); 

    insertarCola(primero, ultimo, array, cont);
    delete[] array; 

    cout<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"\tLISTADO"<<endl;
    mostrarCola(primero, ultimo);
    cout<<"----------------------------"<<endl;
}
void listadoLocalidadesEliminadas(){

    /// @brief Se muestra el contenido del archivo localidades_resp (localidades eliminadas del sistema)
    
    string localidad;
    ifstream archivo;

    archivo.open("localidades_resp.dat", ios::in);
    cout<<endl;
    cout<<"\tLISTADO LOCALIDADES ELIMINADAS "<<endl;
    while(getline(archivo, localidad)){
        cout<<localidad<<endl;
    }
    cout<<endl;
    archivo.close();
}
void compararExistentes(NodoArbol *arbol, Localidad *loc, Localidad *&aux, int L, int &cont){

    /**
     * @brief Se comparan las localidades actuales del programa y las localidades originales del archivo localidades.dat para guardar las coincidentes
     *          en un arreglo auxiliar mendiante un recorrido PostOrden del arbol
     * 
     * @param arbol Estructura arbol
     * @param loc Arreglo original de localidades
     * @param aux Arreglo auxiliar de localidades
     * @param L Cantidad de arreglos
     * @param cont Cantidad de localidades existentes
    */

    if(arbol == NULL){
        return;
    }else{
        compararExistentes(arbol->izq, loc, aux, L, cont);
        compararExistentes(arbol->der, loc, aux, L, cont);
        for(int i=0; i<L; i++){
            if(arbol->dato.nombre == loc[i].nombre){
                aux[cont] = arbol->dato;
                cont++;
            }
        }
    }
}
void listadoLocalidadesExistentes(NodoArbol *arbol, Localidad *loc, int L){

    /**
     * @brief Se comparan las localidades dentro del sistema con las originales del archivo localidades.dat, se guardan dentro de un arreglo el cual es ordenado
     *          de manera alfabetica ascedente para luego mostrarlo por pantalla
     * 
     * @param arbol Estructura arbol
     * @param loc Arreglo original de localidades
     * @param L Cantidad de localidades en el archivo localidades.dat
    */

    int cont = 0;
    Localidad *aux = new Localidad[L];
    compararExistentes(arbol, loc, aux, L, cont);
    mergeSort(aux, 0, cont-1);
    
    cout<<endl;
    cout<<"\tLISTADO LOCALIDADES EXISTENTES"<<endl;
    cout<<endl;
    for(int i=0; i<cont; i++){

        cout<<aux[i].nombre<<", "<<aux[i].coorx<<", "<<aux[i].coory<<endl;
    }
    delete[] aux;
}
Arista *buscarArista(NodoGrafo *grafo, string loc){

    /**
     * @brief Se busca la primer arista de una localidad dentro del grafo
     * 
     * @param grafo Estructura grafo
     * @param loc Nombre de la localidad
     * @return Arista* primera arista con respecto al nodo de la localidad buscada
    */

    Arista *ar;
    while(grafo != NULL){

        ar = grafo->adyacente;
        while(ar != NULL){  

            if(ar->destino->dato.nombre == loc){
                return ar;
            }
            ar = ar->siguiente;
        }
        grafo = grafo->siguiente;
    }
    return ar;
}
void mostrarCiudadesAdyacentes(NodoGrafo *grafo, NodoArbol *arbol){

    /**
    * @brief Se muestran las localidades adyacentes (relaciones directas) de una localidad a eleccion del usuario
    * 
    * @param grafo Estructura grafo con lista de adyacencia
    * @param arbol Estructura arbol binario de busqueda
    */
    NodoArbol *aux;
    NodoGrafo *aux2;
    Arista *ar;
    int opc, cont=0;
    bool flag = false;
    string coorx, coory, locaux, linea;

    cout<<"De que forma buscara la ciudad?"<<endl;
    cout<<"1.Nombre"<<endl;
    cout<<"2.Coordenadas"<<endl;
    cout<<"Opcion: ";
    cin>>opc;

    switch(opc){
        //Eligio busqueda por nombre
        case 1: clean_stdin(); fflush(stdin); cout<<"Ingrese el nombre de la localidad: ";getline(cin, locaux); break;

        //Eligio busqueda por Coordenadas
        case 2: flag = true; break;
            
        default: cout<<"ERROR"<<endl; break;
    }

    if(flag){

        //Eligio busqueda por Coordenadas
        clean_stdin();
        fflush(stdin);
        cout<<"Ingrese las Coordenadas de la localidad: ";
        getline(cin, linea);

        stringstream atributo(linea);
        getline(atributo, coorx, ',');
        getline(atributo, coory, '\n');

        coory.erase(remove_if(coory.begin(), coory.end(), ::isspace), coory.end());  //Borra espacios
    }

    encontrarLocalidad(arbol, aux, locaux, coorx, coory);

    if(aux == NULL){
        cout<<endl;
        cout<<"La localidad no se encuentra en el sistema"<<endl;
        return;
    }

    aux2 = buscarNodoGrafo(grafo, aux->dato.nombre);  //Nodo de la localidad en el grafo
    Arista *ady = buscarArista(aux2, aux->dato.nombre); //Arista de la localidad

    if(aux2 == NULL || ady == NULL){
        
        cout<<endl;
        cout<<"La localidad "<<aux->dato.nombre<<" no tiene ciudades adyacentes"<<endl;

    }
    else{

        cout<<endl;
        cout<<"Las ciudades adyacentes a "<<aux2->dato.nombre<<" son: "<<endl;
        cout<<endl;

        ar = aux2->adyacente;

        while(ar != NULL){

            if(existeLocalidad(arbol, ar->destino->dato.nombre)){

                cout<<ar->destino->dato.nombre<<", "<<ar->rutas.distancia<<", "<<ar->rutas.tiempo<<", "<<ar->rutas.tipo<<endl;
                cont++;
            }
            ar = ar->siguiente;
        }

        cout<<endl;
        cout<<"Total de ciudades adyacentes: "<<cont<<endl;
    }
}
bool verificarVisitados(string loc, string *visitados){

    /**
     * @brief Se recorre el arreglo de localidades visitadas en nuestra busqueda de las rutas
     * 
     * @param loc Nombre de la localidad a buscar dentro del arreglo
     * @param visitados Arreglo de localidades ya visitadas
     * @return true Si se encontro la localidad en el arreglo
     * @return false Si no se encontro la localidad
    */

    int i=0;
    while(visitados[i] != ""){

        if(visitados[i] == loc){
            return true;
        }
        i++;
    }
    return false;
}
void caminos(NodoGrafo *grafo, NodoGrafo *origen, string dest, ArrayList *&roads, string *&visitados, NodoArbol *arbol){

    /**
     * @brief Se exploran los diferentes caminos posibles dentro del grafo y sus aristas donde estos se van guardando en un arreglo
     *         El proceso se hace de manera recursiva
     * 
     * @param grafo Estructura grafo
     * @param origen Nodo origen (donde comienza a buscar)
     * @param dest Nombre de la localidad destino
     * @param roads Arreglo de los posibles caminos
     * @param visitados Arreglo de localidades ya visitadas
     * @param arbol Estructura arbol
    */

    visitados[r] = origen->dato.nombre;
    r++;

    Arista *vecinos = origen->adyacente;

    while(vecinos != NULL){
   
        if(!existeLocalidad(arbol, vecinos->destino->dato.nombre)){
            //Si un vecino no esta dentro del sistema este se salta
            vecinos = vecinos->siguiente;
            continue;
        }
        if(!verificarVisitados(vecinos->destino->dato.nombre, visitados)){
       
            roads[t].array[h] = origen;
            roads[t].array[h+1] = NULL;
           
            if(vecinos->destino->dato.nombre == dest){
                
                NodoGrafo *find = buscarNodoGrafo(grafo, vecinos->destino->dato.nombre);

                roads[t].array[h+1] = find;
                roads[t].array[h+2] = NULL;
                t++;
        
                vecinos = vecinos->siguiente;
            }
            else{
                h++;
                roads[t+1] = roads[t]; //Se hace una copia del arreglo en otra posicion para no perder el control

                NodoGrafo *aux = buscarNodoGrafo(grafo, vecinos->destino->dato.nombre);

                caminos(grafo, aux, dest, roads, visitados, arbol);
                vecinos = vecinos->siguiente;
                h--;
            }
        }
        else{
            vecinos = vecinos->siguiente;
        }
    }
}
void guardarCaminos(ArrayList *roads, string origen, string dest, ArrayList *&ways, int &cont){

    /**
     * @brief Los caminos del arreglo roads que van desde la localidad origen hasta la localidad destino se guardan en el arreglo ways
     * 
     * @param roads Arreglos de caminos posibles
     * @param origen Nombre de la localidad origen
     * @param dest Nombre de la localidad destino
     * @param ways Arreglo de las rutas deseadas
     * @param cont Cantidad de rutas deseadas encontrdas
    */

    int i=0, j=0;
    bool flag = false;
 
    while(roads[i].array[0] != NULL){

        if(roads[i].array[0]->dato.nombre == origen){ //El arreglo comienza por la localidad origen

            flag = true;
        }
        while((flag && (roads[i].array[j]->dato.nombre != dest)) && (roads[i].array[j+1] != NULL)){

            if(roads[i].array[j+1]->dato.nombre == dest){

                ways[cont] = roads[i];
                cont++;
                break;
            }
            else{
                j++;
            }
        }
        i++;
        j=0;
    }
}
void escribirRutaArchivo(ArrayList *ways, int cont){

    /**
     * @brief Se escriben las rutas encontradas en el archivo resultados.out
     * 
     * @param ways Arreglo de rutas encontradas
     * @param cont Cantidad de rutas encontradas
    */

    ofstream archivo;
    archivo.open("resultados.out", ios::app);
    int j=0;
    string ruta;

    for(int i=0; i<cont; i++){

        while(ways[i].array[j] != NULL){

            if(ways[i].array[j+1] == NULL){

                ruta = ruta + ways[i].array[j]->dato.nombre;

            }else{

                ruta = ruta + ways[i].array[j]->dato.nombre + ", ";
            }
            j++;     
        }
        archivo<<ruta<<endl;
        ruta = "";
        j=0;
    }
    archivo.close();
}
void mostrarCaminos(NodoGrafo *grafo, string origen, string dest, ArrayList *ways, int cont, int opc){

    /**
     * @brief Se muestran por pantalla las rutas encontradas o las rutas que se van a eliminar del sistema
     * 
     * @param grafo Estructura grafo
     * @param origen Nombre de la localidad origen
     * @param dest Nombre de la localidad destino
     * @param ways Arreglo de las rutas encontradas deseadas
     * @param cont Cantidad total de rutas encontradas
     * @param opc numero de la operacion que se hizo, ya sea eliminar rutas o solo buscarlas
    */

    // Opc == 1 -> Mostrar rutas
    // Opc == 0 -> Mostrar rutas eliminadas
    if(opc == 1){

        cout<<endl;
        cout<<"Entre las ciudades "<<origen<<" y "<<dest<<" existen estas rutas"<<endl;
        cout<<endl;
    }
    else{

        cout<<endl;
        cout<<"Entre las ciudades "<<origen<<" y "<<dest<<" se eliminaron estas rutas"<<endl;
        cout<<endl;
    }

    int f=0;
    Arista *ar;

    //Preparar las variables para respaldar la informacion eliminadas
    ofstream respaldo;
    string rutas_resp;
    if(opc == 0){
        respaldo.open("rutas_resp.dat", ios::app);
    }

    for(int c=0; c<cont; c++){

        cout<<"Ruta "<<c+1<<endl;
        while(ways[c].array[f+1] != NULL){

            NodoGrafo *aux = grafo;
    
            while(aux != NULL){

                if(aux->dato.nombre == ways[c].array[f]->dato.nombre){

                    ar = aux->adyacente;

                    while(ar != NULL){
    
                        if (ways[c].array[f+1] != NULL){

                            if(ar->destino->dato.nombre == ways[c].array[f+1]->dato.nombre){

                                cout<<aux->dato.nombre<<", "<<ar->destino->dato.nombre<<", "<<ar->rutas.distancia<<", "<<ar->rutas.tiempo<<", "<<ar->rutas.tipo<<endl;

                                if(opc ==0){

                                    //Guardamos las rutas eliminadas en el archivo rutas_resp.dat
                                    rutas_resp = aux->dato.nombre + ", " + ar->destino->dato.nombre + ", " + ar->rutas.distancia + ", " + ar->rutas.tiempo + ", " + ar->rutas.tipo;
                                    respaldo<<rutas_resp<<endl;
                                }
                                f++;
                                break;
                            }
                        }
                        ar = ar->siguiente;
                    }
                }
                aux = aux->siguiente;
            }
        }
        f=0;
        respaldo.close();
    }
    cout<<endl;
    cout<<"Total de rutas encontradas: "<<cont<<endl;
}
void buscarRutas(NodoGrafo *grafo, NodoArbol *arbol, int L){

    /**
     * @brief Se buscan mediante una serie de acciones y funciones las rutas entre las dos localidades ingresadas por el usuario,
     *        ya sea por nombre o por coordenadas de las dos localidades
     * 
     * @param grafo Estructura grafo
     * @param arbol Estructura arbol
     * @param L Cantidad de localidades en el archivo localidades.dat
    */

    string linea, loc1, loc2, coorx1, coory1, coorx2, coory2;
    NodoArbol *aux = new NodoArbol();
    NodoArbol *aux2 = new NodoArbol();
    bool flag = false;
    int cont=0, opc=0, n=1;

    ofstream archivo;
    archivo.open("resultados.out", ios::app);

    cout<<"De que forma buscara la ruta?"<<endl;
    cout<<"1.Nombre"<<endl;
    cout<<"2.Coordenadas"<<endl;
    cout<<"Opcion: ";
    cin>>opc;

    clean_stdin();
    fflush(stdin);
    cout<<"Digite la ruta a buscar: "; getline(cin, linea);
    stringstream atributo(linea);

    switch(opc){
        //Eligio busqqueda por nombres
        case 1:
            getline(atributo, loc1, ',' );
            getline(atributo, loc2, '\n');
            if(loc2.empty()){
                return;
            }
            loc2.erase(loc2.begin());  //Borra espacios
        break;
        //Eligio busqueda por coordenadas
        case 2:
            getline(atributo, coorx1, ',');
            getline(atributo, coory1, ',');
            getline(atributo, coorx2, ',');
            getline(atributo, coory2, '\n');

            coory1.erase(remove_if(coory1.begin(), coory1.end(), ::isspace), coory1.end());  //Borra espacios
            coorx2.erase(remove_if(coorx2.begin(), coorx2.end(), ::isspace), coorx2.end());  //Borra espacios
            coory2.erase(remove_if(coory2.begin(), coory2.end(), ::isspace), coory2.end());  //Borra espacios

            //Buscamos los nombres de las localidades con sus respectivas coordenadas
            encontrarLocalidad(arbol, aux, loc1, coorx1, coory1);
            encontrarLocalidad(arbol, aux2, loc2, coorx2, coory2);
            loc1 = aux->dato.nombre;
            loc2 = aux2->dato.nombre;
        break;

        default: break;
    }

    if(!existeLocalidad(arbol, loc1) && !existeLocalidad(arbol, loc2)){

        archivo<<"-1"<<endl;
        archivo.close();

        cout<<endl;
        cout<<"No existen ambas localidades"<<endl;
        delete aux;
        delete aux2;
        return;
    }
    if(existeLocalidad(arbol, loc1)){

        if(existeLocalidad(arbol, loc2)){

            NodoGrafo *origen = buscarNodoGrafo(grafo, loc1);
            NodoGrafo *destino = buscarNodoGrafo(grafo, loc2);
            if((origen != NULL) && (destino != NULL)){
                if((origen->adyacente != NULL) && (destino->adyacente != NULL)){

                    ArrayList *roads = new ArrayList[100];
                    string *visitados = new string[L];
                    ArrayList *ways = new ArrayList[50];

                    caminos(grafo, origen, loc2, roads, visitados, arbol);
                    guardarCaminos(roads, loc1, loc2, ways, cont);
                    escribirRutaArchivo(ways, cont);
                    mostrarCaminos(grafo, loc1, loc2, ways, cont, n);
        
                    r=0;
                    t=0;
                    h=0;
                    delete[] roads;
                    delete[] visitados;
                    delete[] ways;
                }else{

                    archivo<<"0"<<endl;
                    archivo.close();

                    cout<<endl;
                    cout<<"No existen rutas entre las localidades"<<endl;
                }
            }else{

                archivo<<"0"<<endl;
                archivo.close();

                cout<<endl;
                cout<<"No existen rutas entre las localidades"<<endl;
            }
        }else{

            archivo<<"-2"<<endl;
            archivo.close();

            cout<<endl;
            cout<<"La localidad "<<loc2<<" no se encuentra en el sistema"<<endl;
        }
    }else{

        archivo<<"-3"<<endl;
        archivo.close();

        cout<<endl;
        cout<<"La localidad "<<loc1<<" no se encuentra en el sistema"<<endl;
    }
}
void actualizarGrafo(NodoGrafo *&grafo, ArrayList *ways, int cont){

    /**
     * @brief Se actualiza el grafo de acuerdo a las rutas que fueron eliminadas
     * 
     * @param grafo Estructura grafo
     * @param ways Arreglo de las rutas deseadas
     * @param cont Cantidad total de rutas encontradas
    */

    int i=0, j=0;
    NodoGrafo *aux, *aux2;
    Arista *q, *r;

    while(i < cont){

        while(ways[i].array[j] != NULL){
            
            //Es el comienzo del arreglo por lo que se elimina la relacion con la localidad siguiente
            if(j==0){

                aux = grafo;
                aux2 = grafo;

                while(aux2 != NULL){

                    if(aux2->dato.nombre == ways[i].array[j+1]->dato.nombre){
                        break;
                    }else{
                        aux2 = aux2->siguiente;
                    }
                }
                while(aux != NULL){

                    if(aux->dato.nombre == ways[i].array[j]->dato.nombre){

                        q = aux->adyacente;

                        while(q != NULL){

                            if(q->destino == aux2){

                                if(q == aux->adyacente){
                                    aux->adyacente = aux->adyacente->siguiente;

                                }else{
                                    r->siguiente = q->siguiente;
                                }
                                delete(q);
                                break;
                            }
                            r = q;
                            q = q->siguiente;
                        }
                    }
                    aux = aux->siguiente;
                }
                j++;
            }
            //Se elimina la relacion con la localidad anterior en el arreglo y la localidad siguiente
            else if(ways[i].array[j+1] == NULL){
                
                aux = grafo;
                aux2 = grafo;

                while(aux2 != NULL){

                    if(aux2->dato.nombre == ways[i].array[j-1]->dato.nombre){
                        break;
                    }else{
                        aux2 = aux2->siguiente;
                    }
                }
                while(aux != NULL){

                    if(aux->dato.nombre == ways[i].array[j]->dato.nombre){

                        q = aux->adyacente;

                        while(q != NULL){

                            if(q->destino == aux2){

                                if(q == aux->adyacente){
                                    aux->adyacente = aux->adyacente->siguiente;

                                }else{
                                    r->siguiente = q->siguiente;
                                }
                                delete(q);
                                break;
                            }
                            r = q;
                            q = q->siguiente;
                        }
                    }
                    aux = aux->siguiente;
                }
                j++;
            }
            //Es la ultima posicion del arreglo por lo que solo se elimina la relacion con la localidad anterior
            else{
                aux = grafo;
                aux2 = grafo;

                while(aux2 != NULL){

                    if(aux2->dato.nombre == ways[i].array[j-1]->dato.nombre){
                        break;
                    }else{
                        aux2 = aux2->siguiente;
                    }
                }
                while(aux != NULL){

                    if(aux->dato.nombre == ways[i].array[j]->dato.nombre){

                        q = aux->adyacente;

                        while(q != NULL){

                            if(q->destino == aux2){

                                if(q == aux->adyacente){
                                    aux->adyacente = aux->adyacente->siguiente;

                                }else{
                                    r->siguiente = q->siguiente;
                                }
                                delete(q);
                                break;
                            }
                            r = q;
                            q = q->siguiente;
                        }
                    }
                    aux = aux->siguiente;
                }
                aux = grafo;
                aux2 = grafo;

                while(aux2 != NULL){

                    if(aux2->dato.nombre == ways[i].array[j+1]->dato.nombre){
                        break;
                    }else{
                        aux2 = aux2->siguiente;
                    }
                }
                while(aux != NULL){

                    if(aux->dato.nombre == ways[i].array[j]->dato.nombre){

                        q = aux->adyacente;

                        while(q != NULL){

                            if(q->destino == aux2){

                                if(q == aux->adyacente){
                                    aux->adyacente = aux->adyacente->siguiente;

                                }else{
                                    r->siguiente = q->siguiente;
                                }
                                delete(q);
                                break;
                            }
                            r = q;
                            q = q->siguiente;
                        }
                    }
                    aux = aux->siguiente;
                }
                j++;
            }
            
        }
        j=0;
        i++;
    }
}
void eliminarRuta(NodoGrafo *&grafo, NodoArbol *arbol, int L){

    /**
     * @brief Se buscan mediante una serie de acciones y funciones las rutas entre las dos localidades ingresadas por el usuario,
     *        ya sea por nombre o por coordenadas de las dos localidades, para despues eliminarlas del sistema,
     *        funciona de la misma manera que buscar rutas solo que se eliminan
     * 
     * @param grafo Estructura grafo
     * @param arbol Estructura arbol
     * @param L Cantidad total de localidades en el archivo localidades.dat
    */

    NodoArbol *aux = new NodoArbol();
    NodoArbol *aux2 = new NodoArbol();
    string linea, loc1, loc2, coorx1, coory1, coorx2, coory2;
    int cont=0, opc=0, n=0;

    ofstream archivo;
    archivo.open("resultados.out", ios::app);

    cout<<"De que forma buscara la ruta a eliminar?"<<endl;
    cout<<"1.Nombres"<<endl;
    cout<<"2.Coordenadas"<<endl;
    cout<<"Opcion: ";
    cin>>opc;

    clean_stdin();
    fflush(stdin);
    cout<<"Digite la ruta a buscar: "; getline(cin, linea);
    stringstream atributo(linea);

    switch(opc){

        case 1:
            getline(atributo, loc1, ',' );
            getline(atributo, loc2, '\n');
            if(loc2.empty()){
                return;
            }
            loc2.erase(loc2.begin());  //Borra espacios
        break;

        case 2:
            getline(atributo, coorx1, ',');
            getline(atributo, coory1, ',');
            getline(atributo, coorx2, ',');
            getline(atributo, coory2, '\n');

            coorx1.erase(remove_if(coorx1.begin(), coorx1.end(), ::isspace), coorx1.end());  //Borra espacios
            coory1.erase(remove_if(coory1.begin(), coory1.end(), ::isspace), coory1.end());  //Borra espacios
            coorx2.erase(remove_if(coorx2.begin(), coorx2.end(), ::isspace), coorx2.end());  //Borra espacios
            coory2.erase(remove_if(coory2.begin(), coory2.end(), ::isspace), coory2.end());  //Borra espacios
        
            encontrarLocalidad(arbol, aux, loc1, coorx1, coory1);
            encontrarLocalidad(arbol, aux2, loc2, coorx2, coory2);
            loc1 = aux->dato.nombre;
            loc2 = aux2->dato.nombre;
        break;

        default: break;
    }

    if(!existeLocalidad(arbol, loc1) && !existeLocalidad(arbol, loc2)){

        archivo<<"-1"<<endl;
        archivo.close();

        cout<<endl;
        cout<<"No existen ambas localidades"<<endl;
        delete aux;
        delete aux2;
        return;
    }
    if(existeLocalidad(arbol, loc1)){

        if(existeLocalidad(arbol, loc2)){

            NodoGrafo *origen = buscarNodoGrafo(grafo, loc1);
            NodoGrafo *destino = buscarNodoGrafo(grafo, loc2);

            if((origen != NULL) && (destino != NULL)){
                if((origen->adyacente != NULL) && (destino->adyacente != NULL)){
        
                    ArrayList *roads = new ArrayList[100];
                    string *visitados = new string[L];
                    ArrayList *ways = new ArrayList[50];
          
                    caminos(grafo, origen, loc2, roads, visitados, arbol);
                    guardarCaminos(roads, loc1, loc2, ways, cont);
                    mostrarCaminos(grafo, loc1, loc2, ways, cont, n);
                    actualizarGrafo(grafo, ways, cont);

                    archivo<<"1"<<endl;
                    archivo.close();

                    r=0;
                    t=0;
                    h=0;

                    delete[] roads;
                    delete[] visitados;
                    delete[] ways;
                }else{

                    archivo<<"0"<<endl;
                    archivo.close();

                    cout<<endl;
                    cout<<"No existen rutas entre las localidades"<<endl;
                }
            }else{

                archivo<<"0"<<endl;
                archivo.close();

                cout<<endl;
                cout<<"No existen rutas entre las localidades"<<endl;
            }
        }else{

            archivo<<"-2"<<endl;
            archivo.close();

            cout<<endl;
            cout<<"La localidad "<<loc2<<" no se encuentra en el sistema"<<endl;
        }
    }else{

        archivo<<"-3"<<endl;
        archivo.close();

        cout<<endl;
        cout<<"La localidad "<<loc1<<" no se encuentra en el sistema"<<endl;
    }

    delete aux;
    delete aux2;
}
void listadoRutasEliminadas(){

    /// @brief Se muestran el listado de rutas eliminadas dentro del archivo rutas_resp.dat

    string ruta;
    ifstream archivo;

    archivo.open("rutas_resp.dat", ios::in);
    cout<<endl;
    cout<<"\tLISTADO RUTAS ELIMINADAS "<<endl;

    while(getline(archivo, ruta)){
        cout<<ruta<<endl;
    }
    archivo.close();
}