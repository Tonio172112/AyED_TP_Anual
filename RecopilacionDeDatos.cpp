#include <iostream>
// Programa para recopilacion archivos
using namespace std;

// Hacemos un struct para almacenar la fecha para el struct de sismos
struct Fecha{
    int dia;
    int mes;
    int anio;
};

struct Tiempo{
    int hora;
    int minuto;
    int segundo;
};

struct FechaHora{
    Fecha fecha;
    Tiempo tiempo;
};

struct Clima{
    int id; // (unico)
    Fecha fecha; // (unico)
    int temperaturas[3];
    char descripcion[256+1];
    int mmAguaCaida;
};

struct NodoClima{
    Clima info;
    NodoClima* sgte;
};

struct MovSismicos{
    int id; // (unico)
    Fecha fechaReg;
    char paisReg [56+1];
    double latitud;
    double longitud;
    float magnitud;
};

struct NodoMovSismicos{
    MovSismicos info;
    NodoMovSismicos* sgte;
};

struct Caballo{
    int idDato; // (unico)
    char nombre[100+1];
    int idCaballo; // (unico)
    float velocidadMaxima; // (Km/h)
    float peso;
    float tamanoHerradura;
    FechaHora ultimaCarrera;
};

struct NodoCaballo{
    Caballo info;
    NodoCaballo* sgte;
};

struct Jockey{
    int idDato;
    char nombreApellido[100+1];
    int DNI; // (unico)
    int edad;
    NodoCaballo* listaCaballos;
};

struct NodoJockey{
    Jockey info;
    NodoJockey* sgte;
};

void guardarDato(FILE* f, Clima info);
void guardarDato(FILE* f, MovSismicos info);
void guardarDato(FILE* f, Caballo info);
void guardarDato(FILE* f, Jockey info);
void guardarLista(FILE* f, NodoClima*& lista);
void guardarLista(FILE* f, NodoMovSismicos*& lista);
void guardarLista(FILE* f, NodoCaballo*& lista);
void guardarLista(FILE* f, NodoJockey*& lista);
void guardarEnArchivo(NodoClima*& lista, const char* nombreArchivo);
void guardarEnArchivo(NodoMovSismicos*& lista, const char* nombreArchivo);
void guardarEnArchivo(NodoCaballo*& lista, const char* nombreArchivo);
void guardarEnArchivo(NodoJockey*& lista, const char* nombreArchivo);
void llenarConDatos(NodoClima*& lista);
void llenarConDatos(NodoMovSismicos*& lista);
void llenarConDatos(NodoCaballo*& lista);
void llenarConDatos(NodoJockey*& lista);

int main(){

    NodoClima* listaClima = NULL;
    
    llenarConDatos(listaClima);
    
    guardarEnArchivo(listaClima, "../Archivos/clima.dat");
    
    return 0;
}


//Guarda el dato en el archivo 
void guardarDato(FILE* f, Clima info) {
    fwrite(&info, sizeof(Clima), 1, f);
}

// Sobrecarga 
void guardarDato(FILE* f, MovSismicos info) {
    fwrite(&info, sizeof(MovSismicos), 1, f);
}

// Sobrecarga 
void guardarDato(FILE* f, Caballo info) {
    fwrite(&info, sizeof(Caballo), 1, f);
}
// Sobrecarga
void guardarDato(FILE* f, Jockey info) {
    fwrite(&info, sizeof(Jockey), 1, f);
}

// Guarda la lista
void guardarLista(FILE* f, NodoClima*& lista) {
    NodoClima * auxLista = lista;
    while(auxLista != NULL) {
        guardarDato(f, auxLista->info);
        auxLista = auxLista->sgte; 
    }
}

void guardarLista(FILE* f, NodoMovSismicos*& lista) {
    NodoMovSismicos* auxLista= lista;
    while(auxLista != NULL) {
        guardarDato(f, auxLista->info);
        auxLista = auxLista->sgte; 
    }
}

void guardarLista(FILE* f, NodoCaballo*& lista) {
    NodoCaballo* auxLista = lista;
    while(auxLista != NULL) {
        guardarDato(f, auxLista->info);
        auxLista = auxLista->sgte; 
    }
}

void guardarLista(FILE* f, NodoJockey*& lista) {
    NodoJockey* auxLista= lista;
    while(auxLista != NULL) {
        guardarDato(f, auxLista->info);
        auxLista = auxLista->sgte; 
    }
}

void guardarEnArchivo(NodoClima*& lista, const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "wb");
    if(f != NULL) {
        guardarLista(f, lista);
        fclose(f);
    }
}

void guardarEnArchivo(NodoMovSismicos*& lista, const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "wb");
    if(f != NULL) {
        guardarLista(f, lista);
        fclose(f);
    }
}

void guardarEnArchivo(NodoCaballo*& lista, const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "wb");
    if(f != NULL) {
        guardarLista(f, lista);
        fclose(f);
    }
}

void guardarEnArchivo(NodoJockey*& lista, const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "wb");
    if(f != NULL) {
        guardarLista(f, lista);
        fclose(f);
    }
}

void llenarConDatos(NodoClima*& lista){
    bool continuar=true;
    while(continuar){
        Clima nuevo;
        cout << "Ingrese el ID del clima: ";
        cin >> nuevo.id;
        cout << "Ingrese el dia del clima: ";
        cin >> nuevo.fecha.dia;
        cout << "Ingrese el mes del clima: ";
        cin >> nuevo.fecha.mes;
        cout << "Ingrese el anio del clima: ";
        cin >> nuevo.fecha.anio;
        cout << "Ingrese las temperaturas (3 valores): ";
        for(int i=0; i<3; i++){
            cin >> nuevo.temperaturas[i];
        }
        cout << "Ingrese la descripcion del clima: ";
        cin.ignore();
        cin.getline(nuevo.descripcion, 256);
        cout << "Ingrese los mm de agua caida: ";
        cin >> nuevo.mmAguaCaida;

        NodoClima* nuevoNodo = new NodoClima;
        nuevoNodo->info = nuevo;
        nuevoNodo->sgte = lista;
        lista = nuevoNodo;

        cout << "Desea ingresar otro dato? (1 para si, 0 para no): ";
        cin >> continuar;
    }
}

void llenarConDatos(NodoMovSismicos*& lista){
    bool continuar=true;
    while(continuar){
        MovSismicos nuevo;
        cout << "Ingrese el ID del movimiento sismico: ";
        cin >> nuevo.id;
        cout << "Ingrese el dia de la fecha: ";
        cin >> nuevo.fechaReg.dia;
        cout << "Ingrese el mes de la fecha: ";
        cin >> nuevo.fechaReg.mes;
        cout << "Ingrese el anio de la fecha: ";
        cin >> nuevo.fechaReg.anio;
        cout << "Ingrese el pais de registro: ";
        cin.ignore();
        cin.getline(nuevo.paisReg, 56);
        cout << "Ingrese la latitud: ";
        cin >> nuevo.latitud;
        cout << "Ingrese la longitud: ";
        cin >> nuevo.longitud;
        cout << "Ingrese la magnitud: ";
        cin >> nuevo.magnitud;

        NodoMovSismicos* nuevoNodo = new NodoMovSismicos;
        nuevoNodo->info = nuevo;
        nuevoNodo->sgte = lista;
        lista = nuevoNodo;

        cout << "Desea ingresar otro dato? (1 para si, 0 para no): ";
        cin >> continuar;
    }
}

void llenarConDatos(NodoCaballo*& lista){
    bool continuar=true;
    while(continuar){
        Caballo nuevo;
        cout << "Ingrese el ID del dato del caballo: ";
        cin >> nuevo.idDato;
        cout << "Ingrese el nombre del caballo: ";
        cin.ignore();
        cin.getline(nuevo.nombre, 100);
        cout << "Ingrese la identificacion del caballo: ";
        cin >> nuevo.idCaballo;
        cout << "Ingrese la velocidad maxima (Km/h): ";
        cin >> nuevo.velocidadMaxima;
        cout << "Ingrese el peso: ";
        cin >> nuevo.peso;
        cout << "Ingrese el tamano de herradura: ";
        cin >> nuevo.tamanoHerradura;
        cout << "Ingrese el dia de la ultima carrera: ";
        cin >> nuevo.ultimaCarrera.fecha.dia;
        cout << "Ingrese el mes de la ultima carrera: ";
        cin >> nuevo.ultimaCarrera.fecha.mes;
        cout << "Ingrese el anio de la ultima carrera: ";
        cin >> nuevo.ultimaCarrera.fecha.anio;
        cout << "Ingrese la hora de la ultima carrera: ";
        cin >> nuevo.ultimaCarrera.tiempo.hora;
        cout << "Ingrese el minuto de la ultima carrera: ";
        cin >> nuevo.ultimaCarrera.tiempo.minuto;
        cout << "Ingrese el segundo de la ultima carrera: ";
        cin >> nuevo.ultimaCarrera.tiempo.segundo;

        NodoCaballo* nuevoNodo = new NodoCaballo;
        nuevoNodo->info = nuevo;
        nuevoNodo->sgte = lista;
        lista = nuevoNodo;

        cout << "Desea ingresar otro dato? (1 para si, 0 para no): ";
        cin >> continuar;
    }
}

void llenarConDatos(NodoJockey*& lista){
    bool continuar=true;
    while(continuar){
        Jockey nuevo;
        cout << "Ingrese el ID del dato del jockey: ";
        cin >> nuevo.idDato;
        cout << "Ingrese el nombre y apellido del jockey: ";
        cin.ignore();
        cin.getline(nuevo.nombreApellido, 100);
        cout << "Ingrese el DNI del jockey: ";
        cin >> nuevo.DNI;
        cout << "Ingrese la edad del jockey: ";
        cin >> nuevo.edad;
        nuevo.listaCaballos = NULL;

        NodoJockey* nuevoNodo = new NodoJockey;
        nuevoNodo->info = nuevo;
        nuevoNodo->sgte = lista;
        lista = nuevoNodo;

        cout << "Desea ingresar otro dato? (1 para si, 0 para no): ";
        cin >> continuar;
    }
}