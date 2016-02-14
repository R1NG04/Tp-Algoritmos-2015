#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

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
int main()
{
    FILE *f1, *f2, *f3;
    f1=fopen("ArchivoMaestro.dat", "r+b");
    f2=fopen("ArchivoCobranzas.dat", "r+b");
    f3=fopen("ArchivoMaestroActualizado.dat", "r+b");
    RegistroMaestro RMaestro;
    RegistroMaestro RActualizado;
    RegistroCobranzas RCobranzas;
    fread(&RMaestro, sizeof(RegistroMaestro),1,f1);
    fread(&RCobranzas, sizeof(RegistroCobranzas),1,f2);
    fread(&RActualizado, sizeof(RegistroMaestro),1,f3);

    cout<< "**************************************************************************************"<<endl;
    cout<< "****************************Archivo Maestro: *****************************************"<<endl;
    cout<< "**************************************************************************************"<<endl;


    while ( !feof (f1) )
    {
        if (RMaestro.nrocliente!=0)
        {
            cout << "Numero de cliente " << " | " << RMaestro.nrocliente << endl;
            cout << "Cantidad de cuotas " << " | " << RMaestro.cantidadcuotas << endl;
            for (int i = 0; i < RMaestro.cantidadcuotas; i++)
            {
                cout << "Valor de la cuota " << i +1<< " | " << RMaestro.cuotas[i].valor << endl;
                cout << "Estado de pago " << " | " << RMaestro.cuotas[i].pagaimpaga << endl;
            }
            cout << " ---------------------------" << endl;
        }
        fread(&RMaestro, sizeof(RegistroMaestro),1,f1);
    }
    cout<< "**************************************************************************************"<<endl;
    cout<< "****************************Archivo Cobranzas: ***************************************"<<endl;
    cout<< "**************************************************************************************"<<endl;


    while(!feof(f2)){

        cout << "Numero de PUNTOCOBRO " << "| " << RCobranzas.puntocobro << endl;
        cout << "NUMERO DE CLIENTE " << "| " << RCobranzas.nrocliente << endl;
        cout << "Numero DE CUOTA " << "| " << RCobranzas.nrocuota << endl;
        cout << "MONTO " << "| " << RCobranzas.monto << endl;
        cout<< " ---------------------------" <<endl;
        fread(&RCobranzas, sizeof(RegistroCobranzas),1,f2);
    }

    cout<< "**************************************************************************************"<<endl;
    cout<< "******************************ArchivoMaestroActualizado: *****************************"<<endl;
    cout<< "**************************************************************************************"<<endl;

    while ( !feof (f3) )
    {
        if (RActualizado.nrocliente!=0)
        {
            cout << "Numero de cliente " << " | " << RActualizado.nrocliente << endl;
            cout << "Cantidad de cuotas " << " | " << RActualizado.cantidadcuotas << endl;
            for (int i = 0; i < RActualizado.cantidadcuotas; i++)
            {
                cout << "Valor de la cuota " << i +1<< " | " << RActualizado.cuotas[i].valor << endl;
                cout << "Estado de pago " << " | " << RActualizado.cuotas[i].pagaimpaga << endl;
            }
            cout << " ---------------------------" << endl;
        }
        fread(&RActualizado, sizeof(RegistroMaestro),1,f3);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}