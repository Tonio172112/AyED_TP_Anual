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
void liberarLista(NodoClima*& lista);
void liberarLista(NodoMovSismicos*& lista);
void liberarLista(NodoCaballo*& lista);
void liberarLista(NodoJockey*& lista);
void llenarConDatos(NodoClima*& lista);
void llenarConDatos(NodoMovSismicos*& lista);
void llenarConDatos(NodoCaballo*& lista);
void llenarConDatos(NodoJockey*& listaJockeys, NodoCaballo*& listaCaballos);
bool buscarId(NodoClima*& lista, int id, bool fecha=false, Fecha fechaBuscada={0,0,0});
bool buscarId(NodoMovSismicos*& lista, int id);
bool buscarId(NodoCaballo*& lista, int id, bool porIdCaballo=false);
bool buscarId(NodoJockey*& lista, int id);
void actualizarJockeyEnArchivoCaballos(int idCaballo, int idJockeyNuevo);
void mostrarMenu();


int main(){

    mostrarMenu();

    return 0;
}

void mostrarMenu(){
    NodoClima* listaClima = NULL;
    NodoMovSismicos* listaSismos = NULL;
    NodoCaballo* listaCaballos = NULL;
    NodoJockey* listaJockeys = NULL;
    int opcion;

    do {
        cout << "\n==-== MENU DE RECOPILACION ==-==" << endl;
        cout << "1. Ingresar datos del clima" << endl;
        cout << "2. Ingresar movimientos sismicos" << endl;
        cout << "3. Ingresar datos de caballos" << endl;
        cout << "4. Ingresar datos de jockeys" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion (0 para salir): ";
        cin >> opcion;

        switch(opcion){

            case 1:
                llenarConDatos(listaClima);
                guardarEnArchivo(listaClima, "../Archivos/clima.dat");
                liberarLista(listaClima); // Evitar duplicados en la misma ejecución
                break;

            case 2:
                llenarConDatos(listaSismos);
                guardarEnArchivo(listaSismos, "../Archivos/sismos.dat");
                liberarLista(listaSismos);
                break;

            case 3:
                llenarConDatos(listaCaballos);
                guardarEnArchivo(listaCaballos, "../Archivos/caballos.dat");
                liberarLista(listaCaballos);
                break;

            case 4:
                llenarConDatos(listaJockeys, listaCaballos);
                guardarEnArchivo(listaJockeys, "../Archivos/jockeys.dat");
                liberarLista(listaJockeys);
                liberarLista(listaCaballos);
                break;

            case 0:
                cout << "Finalizando programa..." << endl;
                break;

            default:
                cout << "Opcion incorrecta." << endl;
        }

    } while(opcion != 0);
}

// Guardar datos individuales en archivo
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

void guardarDato(FILE* f, Jockey info) {
    // Limpiamos el puntero antes de guardarlo en disco para evitar basura de memoria
    Jockey infoAux = info;
    infoAux.listaCaballos = NULL; 
    fwrite(&infoAux, sizeof(Jockey), 1, f);
}

// Guardar listas completas
void guardarLista(FILE* f, NodoClima*& lista) {
    NodoClima* aux = lista;
    while(aux != NULL) {
        guardarDato(f, aux->info);
        aux = aux->sgte; 
    }
}

void guardarLista(FILE* f, NodoMovSismicos*& lista) {
    NodoMovSismicos* aux = lista;
    while(aux != NULL) {
        guardarDato(f, aux->info);
        aux = aux->sgte; 
    }
}

void guardarLista(FILE* f, NodoCaballo*& lista) {
    NodoCaballo* aux = lista;
    while(aux != NULL) {
        guardarDato(f, aux->info);
        aux = aux->sgte; 
    }
}

void guardarLista(FILE* f, NodoJockey*& lista) {
    NodoJockey* aux = lista;
    while(aux != NULL) {
        guardarDato(f, aux->info);
        aux = aux->sgte; 
    }
}

void guardarEnArchivo(NodoClima*& lista, const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "ab");
    if(f != NULL) {
        guardarLista(f, lista);
        fclose(f);
    }
}

void guardarEnArchivo(NodoMovSismicos*& lista, const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "ab");
    if(f != NULL) {
        guardarLista(f, lista);
        fclose(f);
    }
}

void guardarEnArchivo(NodoCaballo*& lista, const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "ab");
    if(f != NULL) {
        guardarLista(f, lista);
        fclose(f);
    }
}

void guardarEnArchivo(NodoJockey*& lista, const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "ab");
    if(f != NULL) {
        guardarLista(f, lista);
        fclose(f);
    }
}

// Funciones para liberar memoria RAM de las listas
void liberarLista(NodoClima*& lista) {
    while(lista != NULL) {
        NodoClima* aux = lista;
        lista = lista->sgte;
        delete aux;
    }
}

void liberarLista(NodoMovSismicos*& lista) {
    while(lista != NULL) {
        NodoMovSismicos* aux = lista;
        lista = lista->sgte;
        delete aux;
    }
}

void liberarLista(NodoCaballo*& lista) {
    while(lista != NULL) {
        NodoCaballo* aux = lista;
        lista = lista->sgte;
        delete aux;
    }
}

void liberarLista(NodoJockey*& lista) {
    while(lista != NULL) {
        NodoJockey* aux = lista;
        NodoCaballo* auxSub = aux->info.listaCaballos;
        while(auxSub != NULL) {
            NodoCaballo* borrarSub = auxSub;
            auxSub = auxSub->sgte;
            delete borrarSub;
        }
        lista = lista->sgte;
        delete aux;
    }
}

// Carga de Clima
void llenarConDatos(NodoClima*& lista){
    bool continuar = true;
    while(continuar){
        Clima nuevo;
        bool error = false;
        do{
            error = false;
            cout << " Ingrese el ID del clima (Ingrese 0 para salir): ";
            cin >> nuevo.id;
            if(nuevo.id < 1) return;
            if(buscarId(lista, nuevo.id, false, nuevo.fecha)){
                cout << "\n------------------Error------------------" << endl;
                cout << " El ID ingresado ya se encuentra registrado, ingrese nuevamente. . ." << endl;
                error = true;
            }
        }while(error);
        
        do{
        error = false;
        cout << "Ingrese el dia del clima: "; cin >> nuevo.fecha.dia;
        cout << "Ingrese el mes del clima: "; cin >> nuevo.fecha.mes;
        cout << "Ingrese el anio del clima: "; cin >> nuevo.fecha.anio;
         
        if(buscarId(lista, nuevo.id, true, nuevo.fecha)){
                cout << "\n------------------Error------------------" << endl;
                cout << " Ya existe un registro para esa fecha, ingrese nuevamente. . ." << endl;
                error = true;
            }
        }while(error);    

        cout << "Ingrese las temperaturas (3 valores): ";
        for(int i = 0; i < 3; i++){
            cin >> nuevo.temperaturas[i];
        }
        //ORDENAMIENTO ADCENDETE
        float aux;
        if(nuevo.temperaturas[0]>nuevo.temperaturas[1]){
            aux=nuevo.temperaturas[0];
            nuevo.temperaturas[0]=nuevo.temperaturas[1];
            nuevo.temperaturas[1]=aux;
        }
        if(nuevo.temperaturas[1]>nuevo.temperaturas[2]){
            aux=nuevo.temperaturas[1];
            nuevo.temperaturas[1]=nuevo.temperaturas[2];
            nuevo.temperaturas[2]=aux;

        }
        if(nuevo.temperaturas[0]>nuevo.temperaturas[1]){
            aux=nuevo.temperaturas[0];
            nuevo.temperaturas[0]=nuevo.temperaturas[1];
            nuevo.temperaturas[1]=aux;

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

// Carga de Movimientos Sísmicos
void llenarConDatos(NodoMovSismicos*& lista){
    bool continuar = true;
    while(continuar){
        MovSismicos nuevo;
        bool error = false;
        do{
            error = false;
            cout << " Ingrese el ID del movimiento sismico (Ingrese 0 para salir): ";
            cin >> nuevo.id;
            if(nuevo.id < 1) return;
            if(buscarId(lista, nuevo.id)){
                cout << "\n------------------Error------------------" << endl;
                cout << " El ID ingresado ya se encuentra registrado, ingrese nuevamente. . ." << endl;
                error = true;
            }
        }while(error);

        cout << "Ingrese el dia de la fecha: "; cin >> nuevo.fechaReg.dia;
        cout << "Ingrese el mes de la fecha: "; cin >> nuevo.fechaReg.mes;
        cout << "Ingrese el anio de la fecha: "; cin >> nuevo.fechaReg.anio;
        cout << "Ingrese el pais de registro: ";
        cin.ignore();
        cin.getline(nuevo.paisReg, 56);
        cout << "Ingrese la latitud: "; cin >> nuevo.latitud;
        cout << "Ingrese la longitud: "; cin >> nuevo.longitud;
        cout << "Ingrese la magnitud: "; cin >> nuevo.magnitud;

        NodoMovSismicos* nuevoNodo = new NodoMovSismicos;
        nuevoNodo->info = nuevo;
        nuevoNodo->sgte = lista;
        lista = nuevoNodo;

        cout << "Desea ingresar otro dato? (1 para si, 0 para no): ";
        cin >> continuar;
    }
}

// Carga de Caballos
void llenarConDatos(NodoCaballo*& lista){
    bool continuar = true;
    while(continuar){
        Caballo nuevo;
        bool error = false;
        do{
            error = false;
            cout << " Ingrese el ID del caballo (Ingrese 0 para salir): ";
            cin >> nuevo.id;
            if(nuevo.id < 1) return;
            if(buscarId(lista, nuevo.id, 0)){
                cout << "\n------------------Error------------------" << endl;
                cout << " El ID ingresado ya se encuentra registrado, ingrese nuevamente. . ." << endl;
                error = true;
            }
        }while(error);

        nuevo.idJockey = 0; 
        cout << "Ingrese el nombre del caballo: ";
        cin.ignore();
        cin.getline(nuevo.nombre, 100);
        do{
            error=false;
            cout << "Ingrese la identificacion del caballo: "; cin >> nuevo.idCaballo;
                if(buscarId(lista, nuevo.idCaballo, 1)){
                    cout << "\n------------------Error------------------" << endl;
                    cout << " El ID ingresado ya se encuentra registrado, ingrese nuevamente. . ." << endl;
                    error = true;
                }
        }while(error);
        cout << "Ingrese la velocidad maxima (Km/h): "; cin >> nuevo.velocidadMaxima;
        cout << "Ingrese el peso: "; cin >> nuevo.peso;
        cout << "Ingrese el tamano de herradura: "; cin >> nuevo.tamanoHerradura;
        cout << "Ingrese el dia de la ultima carrera: "; cin >> nuevo.ultimaCarrera.fecha.dia;
        cout << "Ingrese el mes de la ultima carrera: "; cin >> nuevo.ultimaCarrera.fecha.mes;
        cout << "Ingrese el anio de la ultima carrera: "; cin >> nuevo.ultimaCarrera.fecha.anio;
        cout << "Ingrese la hora de la ultima carrera: "; cin >> nuevo.ultimaCarrera.tiempo.hora;
        cout << "Ingrese el minuto de la ultima carrera: "; cin >> nuevo.ultimaCarrera.tiempo.minuto;
        cout << "Ingrese el segundo de la ultima carrera: "; cin >> nuevo.ultimaCarrera.tiempo.segundo;

        NodoCaballo* nuevoNodo = new NodoCaballo;
        nuevoNodo->info = nuevo;
        nuevoNodo->sgte = lista;
        lista = nuevoNodo;

        cout << "Desea ingresar otro dato? (1 para si, 0 para no): ";
        cin >> continuar;
    }
}

// Función auxiliar para actualizar el idJockey directamente en el archivo binario de caballos
void actualizarJockeyEnArchivoCaballos(int idCaballo, int idJockeyNuevo) {
    FILE* f = fopen("../Archivos/caballos.dat", "r+b");
    if(f == NULL) return;

    Caballo c;
    while(fread(&c, sizeof(Caballo), 1, f) == 1) {
        if(c.id == idCaballo) {
            c.idJockey = idJockeyNuevo;
            fseek(f, -sizeof(Caballo), SEEK_CUR);
            fwrite(&c, sizeof(Caballo), 1, f);
            break;
        }
    }
    fclose(f);
}

// Carga de Jockeys utilizando buscarId para verificar el caballo
void llenarConDatos(NodoJockey*& listaJockeys, NodoCaballo*& listaCaballos){
    bool continuar = true;
    while(continuar){
        Jockey nuevo;
        bool error = false;
        do{
            error = false;
            cout << " Ingrese el ID del jockey (Ingrese 0 para salir): ";
            cin >> nuevo.id;
            if(nuevo.id < 1) return;
            if(buscarId(listaJockeys, nuevo.id)){
                cout << "\n------------------Error------------------" << endl;
                cout << " El ID ingresado ya se encuentra registrado, ingrese nuevamente. . ." << endl;
                error = true;
            }
        }while(error);

        cout << "Ingrese el nombre y apellido del jockey: ";
        cin.ignore();
        cin.getline(nuevo.nombreApellido, 100);
        cout << "Ingrese el DNI del jockey: "; cin >> nuevo.DNI;
        cout << "Ingrese la edad del jockey: "; cin >> nuevo.edad;
        
        nuevo.listaCaballos = NULL; 

        char agregarCaballo;
        cout << "Desea asignarle un caballo existente a este jockey? (s/n): ";
        cin >> agregarCaballo;

        while(agregarCaballo == 's' || agregarCaballo == 'S'){
            int idCab;
            cout << "Ingrese el ID del caballo a asignar: ";
            cin >> idCab;

            // Utilizamos buscarId para validar si el caballo existe (en RAM o en archivo)
            if(buscarId(listaCaballos, idCab, 0)){
                Caballo caballoAsignado;
                bool encontradoEnRam = false;

                // Buscamos el struct completo en la lista en RAM
                NodoCaballo* auxC = listaCaballos;
                while(auxC != NULL){
                    if(auxC->info.id == idCab){
                        auxC->info.idJockey = nuevo.id;
                        caballoAsignado = auxC->info;
                        encontradoEnRam = true;
                        break;
                    }
                    auxC = auxC->sgte;
                }

                // Si no estaba en RAM, lo leemos directamente desde el archivo binario
                if(!encontradoEnRam){
                    FILE* f = fopen("../Archivos/caballos.dat", "rb");
                    if(f != NULL){
                        while(fread(&caballoAsignado, sizeof(Caballo), 1, f) == 1){
                            if(caballoAsignado.id == idCab){
                                caballoAsignado.idJockey = nuevo.id;
                                break;
                            }
                        }
                        fclose(f);
                    }
                    // Actualizamos su clave foránea en el archivo físico
                    actualizarJockeyEnArchivoCaballos(idCab, nuevo.id);
                }

                // Agregamos el caballo a la sublista del jockey en memoria RAM
                NodoCaballo* nuevoNodoSub = new NodoCaballo;
                nuevoNodoSub->info = caballoAsignado;
                nuevoNodoSub->sgte = nuevo.listaCaballos;
                nuevo.listaCaballos = nuevoNodoSub;

                cout << "Caballo asignado correctamente al jockey." << endl;
            } else {
                cout << "No se encontro un caballo con ese ID en memoria ni en el archivo." << endl;
            }

            cout << "Desea agregar otro caballo a este jockey? (s/n): ";
            cin >> agregarCaballo;
        }

        NodoJockey* nuevoNodo = new NodoJockey;
        nuevoNodo->info = nuevo;
        nuevoNodo->sgte = listaJockeys;
        listaJockeys = nuevoNodo;

        cout << "Desea ingresar otro jockey? (1 para si, 0 para no): ";
        cin >> continuar;
    }
}


bool buscarId(NodoClima*& lista, int id, bool fecha, Fecha fechaBuscada){
    NodoClima* aux = lista;

    while(aux != NULL){
        if(fecha){
            if(aux->info.fecha.dia == fechaBuscada.dia &&
               aux->info.fecha.mes == fechaBuscada.mes &&
               aux->info.fecha.anio == fechaBuscada.anio){
                return true;
            }
        }
        else{
            if(aux->info.id == id){
                return true;
            }
        }

        aux = aux->sgte;
    }

    Clima datos;
    FILE* f = fopen("../Archivos/clima.dat", "rb");

    if(f == NULL) return false;

    while(fread(&datos, sizeof(Clima), 1, f) == 1){
        if(fecha){
            if(datos.fecha.dia == fechaBuscada.dia &&
               datos.fecha.mes == fechaBuscada.mes &&
               datos.fecha.anio == fechaBuscada.anio){
                fclose(f);
                return true;
            }
        }
        else{
            if(datos.id == id){
                fclose(f);
                return true;
            }
        }
    }

    fclose(f);
    return false;
}

bool buscarId(NodoMovSismicos*& lista, int id){
    NodoMovSismicos* aux = lista;
    while(aux != NULL){
        if(aux->info.id == id) return true;
        aux = aux->sgte;
    }
    MovSismicos datos;
    FILE* f = fopen("../Archivos/sismos.dat", "rb");
    if(f == NULL) return false;
    while(fread(&datos, sizeof(MovSismicos), 1, f) == 1) {
        if(datos.id == id){ fclose(f); return true; }
    }
    fclose(f);
    return false;
}

bool buscarId(NodoCaballo*& lista, int id, bool porIdCaballo){
    NodoCaballo* aux = lista;
    while(aux != NULL){
        if(porIdCaballo){
            if(aux->info.idCaballo == id) return true;
        } else {
            if(aux->info.id == id) return true;
        }
        aux = aux->sgte;
    }

    Caballo datos;
    FILE* f = fopen("../Archivos/caballos.dat", "rb");
    if(f == NULL) return false;

    while(fread(&datos, sizeof(Caballo), 1, f) == 1) {
        if(porIdCaballo){
            if(datos.idCaballo == id){ fclose(f); return true; }
        } else {
            if(datos.id == id){ fclose(f); return true; }
        }
    }
    fclose(f);
    return false;
}


bool buscarId(NodoJockey*& lista, int id){
    NodoJockey* aux = lista;
    while(aux != NULL){
        if(aux->info.id == id) return true;
        aux = aux->sgte;
    }
    Jockey datos;
    FILE* f = fopen("../Archivos/jockeys.dat", "rb");
    if(f == NULL) return false;
    while(fread(&datos, sizeof(Jockey), 1, f) == 1) {
        if(datos.id == id){ fclose(f); return true; }
    }
    fclose(f);
    return false;
}