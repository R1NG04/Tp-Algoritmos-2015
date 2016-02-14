#include <iostream>
#include <stdio.h>

using namespace std;

// Programa Generador de Archivo Cobranzas

struct RegistroCobranzas
{
    int nrocliente;
    int nrocuota;
    double monto;
    int puntocobro;
};

int main() {

RegistroCobranzas RCobranzas;

FILE *f1;

    f1 = fopen("ArchivoCobranzas.dat","w+b");

    // Ingresamos los datos del archivo Maestro Cobranza
    cout<<"Para finalizar el ingreso de datos, ingrese 0 en el numero de cliente."<<endl;
    cout<<"Ingrese numero de cliente del archivo Cobranza"<<endl;
    cin>>RCobranzas.nrocliente;

    while( RCobranzas.nrocliente!=0 )
    {
        cout<<"Ingrese numero de cuota del cliente"<<endl;
        cin>>RCobranzas.nrocuota;
        cout<<"Ingrese monto de cuota del cliente"<<endl;
        cin>>RCobranzas.monto;
        cout<<"Ingrese punto de cobro donde abona el cliente"<<endl;
        cin>>RCobranzas.puntocobro;

    fwrite(&RCobranzas, sizeof(RegistroCobranzas),1,f1);
    cout<< "Ingrese numero de cliente del archivo Maestro Cobranza"<< endl;
    cin>> RCobranzas.nrocliente;
    }

    fclose(f1);
    return 0;
}