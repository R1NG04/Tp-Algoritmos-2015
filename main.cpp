#include <iostream>
#include <stdio.h>

using namespace std;

// ****************************************************** REGISTROS **********************************************

struct Cuotas{
    double valor;
    char pagaimpaga;
};
struct RegistroMaestro{
    int nrocliente;
    int cantidadcuotas;
    Cuotas cuotas[12];
};
struct RegistroCobranzas{
    int nrocliente;
    int nrocuota;
    double monto;
    int puntocobro;
};
template <typename T>
struct Nodo
{
    T info;
    Nodo* sig;
};
struct RegistroListArrays
{
    double diferencia;
    int nrocliente;
};
struct RegistroImpagas
{
    int impagas;
    int nrocliente;
};


// ****************************************************** FUNCIONES **********************************************


int criterio(int v,int c)
{
    return v-c;
}
template <typename T, typename K>
Nodo<T>* insertarOrdenado(Nodo<T>*& p, T v, int (*criterio)(K,K))
{
    Nodo<T>* nuevo = new Nodo<T>();
    nuevo->info = v;
    nuevo->sig = NULL;
    Nodo<T>* aux = p;
    Nodo<T>* ant = NULL;
    while( aux!=NULL && criterio(aux->info.nrocliente,nuevo->info.nrocliente)<=0 )
    {
        ant = aux;
        aux = aux->sig;
    }
    if( ant==NULL ) {
        p = nuevo;
    }
    else {
        ant->sig = nuevo;
    }
    nuevo->sig = aux;
    return nuevo;
}
template <typename T>
void FileToList(FILE*& f, Nodo<T>*& p, T r)
{
    T aux;
    fread(&r, sizeof(T),1,f);
    while( !feof(f) )
    {
        insertarOrdenado <T, int> (p, r,criterio);
        r= aux;
        fread(&r, sizeof(T),1,f);
    }
}
template <typename T>
void mostrarListaCobranzas(Nodo<T>*& p)
{
    Nodo<T>* aux = p;
    while( aux!=NULL )
    {
        cout <<"CLIENTE "<< aux->info.nrocliente << endl;
        cout << aux->info.puntocobro << endl;
        cout << aux->info.nrocuota << endl;
        cout << aux->info.monto << endl;
        aux = aux->sig;
    }
}
template <typename T>
void mostrarListaActualizada(Nodo<T>*& p)
{
    Nodo<T>* aux = p;
    while( aux!=NULL )
    {
        cout <<"----------------------------CLIENTE---------------------------------------------- "<< aux->info.nrocliente << endl;
        cout <<"Cantidad de cuotas" << aux->info.cantidadcuotas << endl;
        for (int i = 0; i < aux->info.cantidadcuotas; ++i) {
            cout<< "**************cuota numero*************** "<< i+1<<endl;
            cout<< "VALOR "<< aux->info.cuotas[i].valor<<endl;
            cout<< "PAGA O IMPAGA "<< aux->info.cuotas[i].pagaimpaga<<endl;
            cout<< " CAMBIO DE CUOTAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<endl;

        }
        aux = aux->sig;
    }
}
template <typename T, typename K>
Nodo<T>* insertarOrdenadoIMPAGAS(Nodo<T>*& p, T v, int (*criterio)(K,K))
{
    Nodo<T>* nuevo = new Nodo<T>();
    nuevo->info = v;
    nuevo->sig = NULL;
    Nodo<T>* aux = p;
    Nodo<T>* ant = NULL;
    while( aux!=NULL && criterio(aux->info.impagas,nuevo->info.impagas) >= 0 )    // ES MAYOR O IGUAL PORQUE ERA DE MAYOR A MENOR
    {
        ant = aux;
        aux = aux->sig;
    }
    if( ant==NULL ) {
        p = nuevo;
    }
    else {
        ant->sig = nuevo;
    }
    nuevo->sig = aux;
    return nuevo;
}
bool InsertarListaActualizada(Nodo<RegistroMaestro>*& lista, RegistroCobranzas RAnterior, Nodo<RegistroCobranzas>*& listaCobranzas ){
    Nodo<RegistroMaestro> *aux = lista;
    bool retorna = true;
    while(aux->sig!=NULL){
        aux = aux->sig;
    }

    if(listaCobranzas->info.nrocliente==RAnterior.nrocliente){
        aux->info.cuotas[listaCobranzas->info.nrocuota-1].pagaimpaga= 'p';
        retorna = false;
    } else{
        retorna = true;
    }
    return retorna;
}
void MostrarImpagos (Nodo<RegistroMaestro>* p)
{
    RegistroImpagas R;
    Nodo<RegistroImpagas>* LImpagas = new Nodo<RegistroImpagas>();
    LImpagas = NULL;
    int impagas=0;
    Nodo<RegistroMaestro>* aux = p;

    while ( aux != NULL )
    {
        impagas = 0;
        for (int i = 0; i < aux->info.cantidadcuotas; ++i)
        {

            if ( aux->info.cuotas[i].pagaimpaga == 'i')
            {
                impagas++;
            }

        }
        if ( impagas > 5)
        {
            R.nrocliente = aux->info.nrocliente;
            R.impagas = impagas;
            insertarOrdenadoIMPAGAS<RegistroImpagas, int> (LImpagas, R, criterio);
        }

        aux = aux->sig;
    }

    while ( LImpagas != NULL)
    {
        cout << "El cliente numero " << LImpagas->info.nrocliente << " tuvo " << LImpagas->info.impagas << " cuotas impagas" << endl;
        LImpagas = LImpagas->sig;
    }
}
void ListToFile (Nodo<RegistroMaestro>*& p, FILE*& f)
{
    RegistroMaestro R;
    Nodo<RegistroMaestro>* aux = p;
    while ( aux != NULL )
    {
        R = aux->info;
        fwrite (&R, sizeof(RegistroMaestro), 1, f);     // OJO EL AUX->INFO supuestamente iba un R, declarado RegistroMaestro R
        aux = aux->sig;
    }
}



/*INTEGRANTES:
 *  Santiago Illi
 *  Martin Gonzalez
 *  Sol Ottaviani
 *  Matias Veron Peralta
 *  Maximiliano Avalle
 *\



 /* PRECONDICIONES:
 *      Se asume que no se pagan cuotas que ya se encuentran saldadas.
 *      No se toma en cuenta el caso para los puntos de cobro en el cual la cuota es pagada con el monto justo.
 *      Es decir que no se listara con ninguna leyenda ese tipo de caso.
 *      Se asume que las cuotas no tienen valores negativos, asi como los pagos.
 * */


int main() {

    //************************************DEFINICION DE VARIABLES, ARREGLOS Y LISTAS **********************************

    RegistroMaestro RMaestro;
    RegistroCobranzas RCobranza;
    RegistroCobranzas RAnterior;
    Nodo<RegistroCobranzas>* listaCobranza = new Nodo<RegistroCobranzas>();
    listaCobranza=NULL;
    Nodo<RegistroMaestro>* listaACT = new Nodo<RegistroMaestro>();
    listaACT=NULL;
    Nodo<RegistroListArrays>* PuntoCobro[5];        // Array de punteros, la posicion indica cada puntocobro de cobro
    RegistroListArrays RVector;

    // LISTAS DEL ARRAY

    PuntoCobro[0] = new Nodo<RegistroListArrays>();
    PuntoCobro[0]=NULL;
    PuntoCobro[1]  = new Nodo<RegistroListArrays>();
    PuntoCobro[1]=NULL;
    PuntoCobro[2]  = new Nodo<RegistroListArrays>();
    PuntoCobro[2]=NULL;
    PuntoCobro[3]  = new Nodo<RegistroListArrays>();
    PuntoCobro[3]=NULL;
    PuntoCobro[4]  = new Nodo<RegistroListArrays>();
    PuntoCobro[4]=NULL;

    FILE *ArchivoMaestro, *ArchivoCobranzas, *ArchivoMaestroActualizado;
    ArchivoMaestro = fopen("ArchivoMaestro.dat", "r+b");
    ArchivoCobranzas = fopen("ArchivoCobranzas.dat", "r+b");
    ArchivoMaestroActualizado = fopen("ArchivoMaestroActualizado.dat", "w+b");
    FileToList<RegistroCobranzas>(ArchivoCobranzas, listaCobranza, RCobranza);

  //  mostrarListaCobranzas<RegistroCobranzas>(listaCobranza); Esto lo usamos para probar

    fread (&RMaestro, sizeof(RegistroMaestro), 1, ArchivoMaestro);
    while(!feof(ArchivoMaestro) && listaCobranza!= NULL){

        if(RMaestro.nrocliente == listaCobranza->info.nrocliente){
            if(listaCobranza->info.monto >= RMaestro.cuotas[listaCobranza->info.nrocuota-1].valor){
                if(InsertarListaActualizada(listaACT, RAnterior,listaCobranza)){
                    RMaestro.cuotas[listaCobranza->info.nrocuota-1].pagaimpaga = 'p';
                    insertarOrdenado<RegistroMaestro, int> (listaACT, RMaestro, criterio);
                }
                if (listaCobranza->info.monto > RMaestro.cuotas[listaCobranza->info.nrocuota-1].valor)
                {
                    RVector.diferencia = (listaCobranza->info.monto - RMaestro.cuotas[listaCobranza->info.nrocuota-1].valor );
                    RVector.nrocliente = listaCobranza->info.nrocliente;
                    insertarOrdenado <RegistroListArrays, int> (PuntoCobro[listaCobranza->info.puntocobro - 1], RVector, criterio);
            }
            }
            else if (listaCobranza->info.monto < RMaestro.cuotas[listaCobranza->info.nrocuota-1].valor )
            {
                RVector.diferencia = (listaCobranza->info.monto - RMaestro.cuotas[listaCobranza->info.nrocuota-1].valor );
                RVector.nrocliente = listaCobranza->info.nrocliente;
                insertarOrdenado <RegistroListArrays> (PuntoCobro[listaCobranza->info.puntocobro - 1], RVector, criterio);
                if(RMaestro.nrocliente != RAnterior.nrocliente){
                    insertarOrdenado<RegistroMaestro, int> (listaACT, RMaestro, criterio);
                }
            }
            RAnterior = listaCobranza->info;
            listaCobranza = listaCobranza->sig;
        }
        else if( listaCobranza->info.nrocliente > RMaestro.nrocliente )
        {
            if(RMaestro.nrocliente != RAnterior.nrocliente){
                insertarOrdenado<RegistroMaestro, int> (listaACT, RMaestro, criterio);
            }
            fread (&RMaestro, sizeof(RegistroMaestro), 1, ArchivoMaestro);
        }
        else if( listaCobranza->info.nrocliente < RMaestro.nrocliente  )
        {
            RAnterior = listaCobranza->info;
            listaCobranza = listaCobranza->sig;
        }

    }
    while (!feof(ArchivoMaestro)){
        if(RMaestro.nrocliente != RAnterior.nrocliente){
            insertarOrdenado<RegistroMaestro, int> (listaACT, RMaestro, criterio);
        }
        fread (&RMaestro, sizeof(RegistroMaestro), 1, ArchivoMaestro);
    }

    ListToFile(listaACT, ArchivoMaestroActualizado);

//    mostrarListaActualizada<RegistroMaestro>(listaACT); esto tambien lo usamos para probar

    for (int i = 0; i < 5; i++)
    {
        cout << "Punto de cobro " << i+1 << endl;
        while( PuntoCobro[i]!=NULL )
        {
            if ( PuntoCobro[i]->info.diferencia < 0)
            {
                cout << "El cliente " << PuntoCobro[i]->info.nrocliente << " realizo un pago con monto INSUFICIENTE" << endl;
            }
            else
            {
                cout << "El cliente " << PuntoCobro[i]->info.nrocliente << " realizo un pago con monto EXCEDENTE de " <<PuntoCobro[i]->info.diferencia << endl;
            }

            PuntoCobro[i] =  PuntoCobro[i]->sig;
        }

        cout << " --------------------------------------------- " << endl;
    }
    MostrarImpagos(listaACT);
    fclose(ArchivoCobranzas);
    fclose(ArchivoMaestro);
    fclose(ArchivoMaestroActualizado);

    return 0;
}