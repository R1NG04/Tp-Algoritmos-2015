#include <iostream>
#include <stdio.h>

using namespace std;
// Programa Generador de Archivo Maestro


struct Cuotas{
    double valor;
    char pagaimpaga;
};

struct RegistroMaestro{
    int nrocliente;
    int cantidadcuotas;
    Cuotas cuotas[12];
};

int main() {

    RegistroMaestro RMaestro;

    FILE *f1;

    f1 = fopen("ArchivoMaestro.dat","w+b");

    // Ingresamos los datos del archivo Maestro Cobranza
    cout<<"Para finalizar el ingreso de datos, ingrese 0 en el numero de cliente."<<endl;
    cout<<"Ingrese numero de cliente del archivo Maestro Cobranza"<<endl;
    cin>>RMaestro.nrocliente;

    while( RMaestro.nrocliente!=0 )
    {
        cout<<"Ingrese cantidad de cuotas del Registro"<<endl;
        cin>>RMaestro.cantidadcuotas;
        for (int i = 0; i < (RMaestro.cantidadcuotas); i++)
        {
            cout<< "Ingrese el valor de la cuota" << endl;
            cin>> RMaestro.cuotas[i].valor;
            cout << "Si la cuota esta impaga ingrese i, sino ingrese p" << endl;
            cin>> RMaestro.cuotas[i].pagaimpaga;
        }

        fwrite(&RMaestro, sizeof(RegistroMaestro),1,f1);

        cout<< "Ingrese numero de cliente del archivo Maestro Cobranza"<< endl;
        cin>> RMaestro.nrocliente;

    }

    fclose(f1);
    return 0;
}