#include <iostream>
#include <cstdio>
#include <cstring>
// Programa para lectura de archivos
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
    Fecha fecha; 
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
    char paisReg[56+1];
    double latitud;
    double longitud;
    float magnitud;
};

struct NodoMovSismicos{
    MovSismicos info;
    NodoMovSismicos* sgte;
};

struct ResumenPaisSismo{
    char pais[56+1];
    int cantidad;
    double sumaMagnitud;
};

struct NodoResumenSismo{
    ResumenPaisSismo info;
    NodoResumenSismo* sgte;
};

struct Caballo{
    int id; // (unico)
    int idJockey; // Clave foranea para vincular al jockey en el archivo
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
    int id;
    char nombreApellido[100+1];
    int DNI; // (unico)
    int edad;
    NodoCaballo* listaCaballos; // Sublista en memoria RAM
};

struct NodoJockey{
    Jockey info;
    NodoJockey* sgte;
};

// Prototipos
void mostrarRegistro(Clima info);
void mostrarRegistro(MovSismicos info);
void mostrarRegistro(Caballo info);
void mostrarRegistro(Jockey info, const char* archivoCaballos);
void buscarBinariaClima(const char* nombreArchivo, int idBuscado);
void buscarBinariaSismo(const char* nombreArchivo, int idBuscado);
void buscarBinariaCaballo(const char* nombreArchivo, int idBuscado);
void buscarBinariaJockey(const char* nombreArchivo, const char* archivoCaballos, int idBuscado);
void insertarClima(NodoClima*& lista, Clima nuevo);
void liberarListaClima(NodoClima*& lista);
bool esDiaCatastrofico(Clima c);
bool contieneGranizo(const char desc[]);
void listarDiasCat(const char* nombreArchivo);
void aMinuscula(char destino[], const char origen[]);
int compararTextoMinuscula(const char a[], const char b[]);
void insertarSismo(NodoMovSismicos*& lista, MovSismicos nuevo);
void ordenarSismosPorPais(NodoMovSismicos*& lista);
void liberarListaSismos(NodoMovSismicos*& lista);
void insertarResumenPais(NodoResumenSismo*& lista, ResumenPaisSismo dato);
void ordenarResumenPorCantidad(NodoResumenSismo*& lista);
void liberarResumenSismos(NodoResumenSismo*& lista);
void top3YPromedioSismos(const char* nombreArchivo);
void menuClima();
void menuSismos();
void menuCaballos();
void menuJockeys();
void menu();

int main(){
    menu();
    return 0;
}

void menu(){
    int opcion;

    do {
        cout << "\n==-== MENU PRINCIPAL DE CONSULTAS ==-==" << endl;
        cout << "1. Clima" << endl;
        cout << "2. Movimientos sismicos" << endl;
        cout << "3. Caballos" << endl;
        cout << "4. Jockeys" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion (0 para salir): ";
        cin >> opcion;

        switch(opcion){

            case 1:
                menuClima();
                break;

            case 2:
                menuSismos();
                break;

            case 3:
                menuCaballos();
                break;

            case 4:
                menuJockeys();
                break;

            case 0:
                cout << "Finalizando programa..." << endl;
                break;

            default:
                cout << "Opcion incorrecta." << endl;
        }

    } while(opcion != 0);
}

// Submenu de Clima
void menuClima(){
    int opcion;

    do {
        cout << "\n--- MENU CLIMA ---" << endl;
        cout << "1. Buscar por ID" << endl;
        cout << "2. Listar dias catastroficos" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1: {
                int idBuscado;
                cout << "Ingrese el ID de clima a buscar: ";
                cin >> idBuscado;
                buscarBinariaClima("../Archivos/clima.dat", idBuscado);
                break;
            }
            case 2: {
                listarDiasCat("../Archivos/clima.dat");
                break;
            }
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion incorrecta." << endl;
        }
    } while(opcion != 0);
}

// Submenu de Movimientos Sismicos
void menuSismos(){
    int opcion;

    do {
        cout << "\n--- MENU MOVIMIENTOS SISMICOS ---" << endl;
        cout << "1. Buscar por ID" << endl;
        cout << "2. Top 3 paises con mas sismos y promedio de magnitud" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1: {
                int idBuscado;
                cout << "Ingrese el ID sismico a buscar: ";
                cin >> idBuscado;
                buscarBinariaSismo("../Archivos/sismos.dat", idBuscado);
                break;
            }
            case 2: {
                top3YPromedioSismos("../Archivos/sismos.dat");
                break;
            }
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion incorrecta." << endl;
        }
    } while(opcion != 0);
}

// Submenu de Caballos
void menuCaballos(){
    int opcion;

    do {
        cout << "\n--- MENU CABALLOS ---" << endl;
        cout << "1. Buscar por ID" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1: {
                int idBuscado;
                cout << "Ingrese el ID del caballo a buscar: ";
                cin >> idBuscado;
                buscarBinariaCaballo("../Archivos/caballos.dat", idBuscado);
                break;
            }
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion incorrecta." << endl;
        }
    } while(opcion != 0);
}

// Submenu de Jockeys
void menuJockeys(){
    int opcion;

    do {
        cout << "\n--- MENU JOCKEYS ---" << endl;
        cout << "1. Buscar por ID" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1: {
                int idBuscado;
                cout << "Ingrese el ID del jockey a buscar: ";
                cin >> idBuscado;
                buscarBinariaJockey("../Archivos/jockeys.dat", "../Archivos/caballos.dat", idBuscado);
                break;
            }
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion incorrecta." << endl;
        }
    } while(opcion != 0);
}

// Muestra un registro de Clima
void mostrarRegistro(Clima info){
    cout << "\n--- Clima encontrado ---\n";
    cout << "ID Clima: " << info.id << endl;
    cout << "Fecha: " << info.fecha.dia << "/" << info.fecha.mes << "/" << info.fecha.anio << endl;
    cout << "Temperaturas: " << info.temperaturas[0] << ", " << info.temperaturas[1] << ", " << info.temperaturas[2] << endl;
    cout << "Descripcion: " << info.descripcion << endl;
    cout << "Agua caida: " << info.mmAguaCaida << " mm" << endl;
    cout << "-----------------------------------" << endl;
}

// Sobrecarga
void mostrarRegistro(MovSismicos info){
    cout << "\n--- Movimiento Sismico encontrado ---\n";
    cout << "ID Sismico: " << info.id << endl;
    cout << "Fecha: " << info.fechaReg.dia << "/" << info.fechaReg.mes << "/" << info.fechaReg.anio << endl;
    cout << "Pais: " << info.paisReg << endl;
    cout << "Latitud: " << info.latitud << " | Longitud: " << info.longitud << endl;
    cout << "Magnitud: " << info.magnitud << endl;
    cout << "-----------------------------------" << endl;
}

// Sobrecarga
void mostrarRegistro(Caballo info){
    cout << "\n--- Caballo encontrado ---\n";
    cout << "ID Caballo: " << info.id << " | ID Jockey Vinculado: " << info.idJockey << endl;
    cout << "Nombre: " << info.nombre << endl;
    cout << "ID Matricula Caballo: " << info.idCaballo << endl;
    cout << "Velocidad Maxima: " << info.velocidadMaxima << " Km/h" << endl;
    cout << "Peso: " << info.peso << endl;
    cout << "Tamano herradura: " << info.tamanoHerradura << endl;

    int h = info.ultimaCarrera.tiempo.hora;
    int min = info.ultimaCarrera.tiempo.minuto;
    int seg = info.ultimaCarrera.tiempo.segundo;
    const char* ampm = (h >= 12) ? "PM " : "AM ";
    int hora12 = h % 12;
    if(hora12 == 0) hora12 = 12;
    cout << "Ultima carrera: "
         << info.ultimaCarrera.fecha.dia << "/"
         << info.ultimaCarrera.fecha.mes << "/"
         << info.ultimaCarrera.fecha.anio << " "
         << hora12 << ":"
         << (min < 10 ? "0" : "") << min << ":"
         << (seg < 10 ? "0" : "") << seg << " "
         << ampm << "GMT -3" << endl;
    cout << "-----------------------------------" << endl;
}

// Sobrecarga
void mostrarRegistro(Jockey info, const char* archivoCaballos){
    cout << "\n--- Jockey encontrado ---\n";
    cout << "ID Jockey: " << info.id << endl;
    cout << "Nombre y Apellido: " << info.nombreApellido << endl;
    cout << "DNI: " << info.DNI << endl;
    cout << "Edad: " << info.edad << endl;
    cout << "Caballos asignados:" << endl;

    FILE* fC = fopen(archivoCaballos, "rb");
    bool tieneCaballos = false;
    if(fC != NULL){
        Caballo c;
        while(fread(&c, sizeof(Caballo), 1, fC) == 1){
            if(c.idJockey == info.id){
                tieneCaballos = true;
                cout << "   - ID Caballo: " << c.id << " | Nombre: " << c.nombre
                     << " (Vel. Max: " << c.velocidadMaxima << " Km/h)" << endl;
            }
        }
        fclose(fC);
    }
    if(!tieneCaballos){
        cout << "   (Sin caballos asignados)" << endl;
    }
    cout << "-----------------------------------" << endl;
}

// Busqueda binaria sobre archivo binario ordenado por id
void buscarBinariaClima(const char* nombreArchivo, int idBuscado){
    Clima modelo;
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL){
        cout << "Archivo no encontrado: " << nombreArchivo << endl;
        return;
    }

    fseek(f, 0, SEEK_END);
    long totalRegistros = ftell(f) / (long)sizeof(Clima);
    long izq = 0;
    long der = totalRegistros - 1;
    bool encontrado = false;

    while(izq <= der){
        long medio = izq + (der - izq) / 2;
        fseek(f, medio * (long)sizeof(Clima), SEEK_SET);
        if(fread(&modelo, sizeof(Clima), 1, f) != 1) break;

        if(modelo.id == idBuscado){
            encontrado = true;
            break;
        } else if(modelo.id < idBuscado){
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }

    fclose(f);

    if(encontrado){
        mostrarRegistro(modelo);
    } else {
        cout << "No se encontro ningun registro de clima con ID " << idBuscado << "." << endl;
    }
}

void buscarBinariaSismo(const char* nombreArchivo, int idBuscado){
    MovSismicos modelo;
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL){
        cout << "Archivo no encontrado: " << nombreArchivo << endl;
        return;
    }

    fseek(f, 0, SEEK_END);
    long totalRegistros = ftell(f) / (long)sizeof(MovSismicos);
    long izq = 0;
    long der = totalRegistros - 1;
    bool encontrado = false;

    while(izq <= der){
        long medio = izq + (der - izq) / 2;
        fseek(f, medio * (long)sizeof(MovSismicos), SEEK_SET);
        if(fread(&modelo, sizeof(MovSismicos), 1, f) != 1) break;

        if(modelo.id == idBuscado){
            encontrado = true;
            break;
        } else if(modelo.id < idBuscado){
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }

    fclose(f);

    if(encontrado){
        mostrarRegistro(modelo);
    } else {
        cout << "No se encontro ningun movimiento sismico con ID " << idBuscado << "." << endl;
    }
}

void buscarBinariaCaballo(const char* nombreArchivo, int idBuscado){
    Caballo modelo;
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL){
        cout << "Archivo no encontrado: " << nombreArchivo << endl;
        return;
    }

    fseek(f, 0, SEEK_END);
    long totalRegistros = ftell(f) / (long)sizeof(Caballo);
    long izq = 0;
    long der = totalRegistros - 1;
    bool encontrado = false;

    while(izq <= der){
        long medio = izq + (der - izq) / 2;
        fseek(f, medio * (long)sizeof(Caballo), SEEK_SET);
        if(fread(&modelo, sizeof(Caballo), 1, f) != 1) break;

        if(modelo.id == idBuscado){
            encontrado = true;
            break;
        } else if(modelo.id < idBuscado){
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }

    fclose(f);

    if(encontrado){
        mostrarRegistro(modelo);
    } else {
        cout << "No se encontro ningun caballo con ID " << idBuscado << "." << endl;
    }
}

void buscarBinariaJockey(const char* nombreArchivo, const char* archivoCaballos, int idBuscado){
    Jockey modelo;
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL){
        cout << "Archivo no encontrado: " << nombreArchivo << endl;
        return;
    }

    fseek(f, 0, SEEK_END);
    long totalRegistros = ftell(f) / (long)sizeof(Jockey);
    long izq = 0;
    long der = totalRegistros - 1;
    bool encontrado = false;

    while(izq <= der){
        long medio = izq + (der - izq) / 2;
        fseek(f, medio * (long)sizeof(Jockey), SEEK_SET);
        if(fread(&modelo, sizeof(Jockey), 1, f) != 1) break;

        if(modelo.id == idBuscado){
            encontrado = true;
            break;
        } else if(modelo.id < idBuscado){
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }

    fclose(f);

    if(encontrado){
        mostrarRegistro(modelo, archivoCaballos);
    } else {
        cout << "No se encontro ningun jockey con ID " << idBuscado << "." << endl;
    }
}

// Verifica si la descripcion del clima contiene "granizo" 
bool contieneGranizo(const char desc[]){
    char descMin[257];
    aMinuscula(descMin, desc);
    return strstr(descMin, "granizo") != NULL;
}

bool esDiaCatastrofico(Clima c){
    for(int i = 0; i < 3; i++){
        if(c.temperaturas[i] > 40 || c.temperaturas[i] < -10) return true;
    }
    if(c.mmAguaCaida > 100) return true;
    if(contieneGranizo(c.descripcion)) return true;
    return false;
}

void insertarClima(NodoClima*& lista, Clima nuevo){
    NodoClima* nodo = new NodoClima;
    nodo->info = nuevo;
    nodo->sgte = lista;
    lista = nodo;
}

void liberarListaClima(NodoClima*& lista){
    while(lista != NULL){
        NodoClima* aux = lista;
        lista = lista->sgte;
        delete aux;
    }
}

void listarDiasCat(const char* nombreArchivo){
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL){
        cout << "Archivo no encontrado: " << nombreArchivo << endl;
        return;
    }

    NodoClima* listaCat = NULL;
    Clima reg;
    while(fread(&reg, sizeof(Clima), 1, f) == 1){
        if(esDiaCatastrofico(reg)){
            insertarClima(listaCat, reg);
        }
    }
    fclose(f);

    if(listaCat == NULL){
        cout << "\nNo se registraron dias catastroficos." << endl;
        return;
    }

    int cantDias = 0;
    long sumaTemp = 0;
    int cantValores = 0;
    NodoClima* aux = listaCat;

    cout << "\n=== DIAS CATASTROFICOS ===" << endl;
    while(aux != NULL){
        mostrarRegistro(aux->info);
        for(int i = 0; i < 3; i++){
            sumaTemp += aux->info.temperaturas[i];
            cantValores++;
        }
        cantDias++;
        aux = aux->sgte;
    }

    double promedio = 0.0;
    if(cantValores > 0){
        promedio = (double)sumaTemp / cantValores;
    }
    cout << "Total de dias catastroficos: " << cantDias << endl;
    cout << "Promedio de temperatura en dias catastroficos: " << promedio << " C" << endl;

    liberarListaClima(listaCat);
}

void aMinuscula(char destino[], const char origen[]){
    strcpy(destino, origen);
    for(int i = 0; destino[i] != '\0'; i++){
        if(destino[i] >= 'A' && destino[i] <= 'Z'){
            destino[i] = destino[i] + ('a' - 'A');
        }
    }
}

int compararTextoMinuscula(const char a[], const char b[]){
    char minA[57];
    char minB[57];
    aMinuscula(minA, a);
    aMinuscula(minB, b);
    return strcmp(minA, minB);
}

void insertarSismo(NodoMovSismicos*& lista, MovSismicos nuevo){
    NodoMovSismicos* nodo = new NodoMovSismicos;
    nodo->info = nuevo;
    nodo->sgte = lista;
    lista = nodo;
}

void ordenarSismosPorPais(NodoMovSismicos*& lista){
    if(lista == NULL) return;
    bool huboCambio;
    do{
        huboCambio = false;
        NodoMovSismicos* actual = lista;
        while(actual->sgte != NULL){
            if(compararTextoMinuscula(actual->info.paisReg, actual->sgte->info.paisReg) > 0){
                MovSismicos temp = actual->info;
                actual->info = actual->sgte->info;
                actual->sgte->info = temp;
                huboCambio = true;
            }
            actual = actual->sgte;
        }
    } while(huboCambio);
}

void liberarListaSismos(NodoMovSismicos*& lista){
    while(lista != NULL){
        NodoMovSismicos* aux = lista;
        lista = lista->sgte;
        delete aux;
    }
}

void insertarResumenPais(NodoResumenSismo*& lista, ResumenPaisSismo dato){
    NodoResumenSismo* nodo = new NodoResumenSismo;
    nodo->info = dato;
    nodo->sgte = lista;
    lista = nodo;
}

void ordenarResumenPorCantidad(NodoResumenSismo*& lista){
    if(lista == NULL) return;
    bool huboCambio;
    do{
        huboCambio = false;
        NodoResumenSismo* actual = lista;
        while(actual->sgte != NULL){
            if(actual->info.cantidad < actual->sgte->info.cantidad){
                ResumenPaisSismo temp = actual->info;
                actual->info = actual->sgte->info;
                actual->sgte->info = temp;
                huboCambio = true;
            }
            actual = actual->sgte;
        }
    } while(huboCambio);
}

void liberarResumenSismos(NodoResumenSismo*& lista){
    while(lista != NULL){
        NodoResumenSismo* aux = lista;
        lista = lista->sgte;
        delete aux;
    }
}

void top3YPromedioSismos(const char* nombreArchivo){
    FILE* f = fopen(nombreArchivo, "rb");
    if(f == NULL){
        cout << "Archivo no encontrado: " << nombreArchivo << endl;
        return;
    }

    NodoMovSismicos* listaSismos = NULL;
    MovSismicos reg;
    while(fread(&reg, sizeof(MovSismicos), 1, f) == 1){
        insertarSismo(listaSismos, reg);
    }
    fclose(f);

    if(listaSismos == NULL){
        cout << "\nNo hay registros de movimientos sismicos." << endl;
        return;
    }

    ordenarSismosPorPais(listaSismos);

    NodoResumenSismo* listaResumen = NULL;
    NodoMovSismicos* aux = listaSismos;

    cout << "\n=== PROMEDIO DE MAGNITUDES POR PAIS ===" << endl;
    // Corte de control implementado 
    while(aux != NULL){
        char paisActual[56+1];
        strcpy(paisActual, aux->info.paisReg);
        int cantPais = 0;
        double sumaMag = 0.0;

        while(aux != NULL && compararTextoMinuscula(aux->info.paisReg, paisActual) == 0){
            cantPais++;
            sumaMag += aux->info.magnitud;
            aux = aux->sgte;
        }

        double prom = 0.0;
        if(cantPais > 0){
            prom = sumaMag / cantPais;
        }

        cout << "Pais: " << paisActual
             << " | Sismos: " << cantPais
             << " | Promedio magnitud: " << prom << endl;

        ResumenPaisSismo res;
        strcpy(res.pais, paisActual);
        res.cantidad = cantPais;
        res.sumaMagnitud = sumaMag;
        insertarResumenPais(listaResumen, res);
    }

    ordenarResumenPorCantidad(listaResumen);

    cout << "\n=== TOP 3 LUGARES CON MAS MOVIMIENTOS SISMICOS ===" << endl;
    int pos = 1;
    NodoResumenSismo* auxRes = listaResumen;
    while(auxRes != NULL && pos <= 3){
        double prom = 0.0;
        if(auxRes->info.cantidad > 0){
            prom = auxRes->info.sumaMagnitud / auxRes->info.cantidad;
        }
        cout << pos << ". " << auxRes->info.pais
             << " - " << auxRes->info.cantidad << " movimientos"
             << " (Promedio magnitud: " << prom << ")" << endl;
        auxRes = auxRes->sgte;
        pos++;
    }

    liberarListaSismos(listaSismos);
    liberarResumenSismos(listaResumen);
}