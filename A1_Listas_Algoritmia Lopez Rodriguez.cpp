#include<iostream>
#include<stdio.h>
#include<fstream>
#include <string>
#include <sstream>

using namespace std;

class Paquete
{
private:
    Paquete* pSig;
    int Id;
    string Origen;
    string Destino;
    int Peso;
    friend class Paqueteria;
public:
    Paquete(int,string,string,int);
    void InsertarInicio(int,string,string,int);
    void EliminarInicio();
    void Mostrar();
    void Recuperar();
};

class Paqueteria
{
private:
    Paquete* Lista;
    Paquete* Inicio;
    friend class Paquete;
public:
    Paqueteria();
    void InsertarInicio(int,string,string,int);
    void EliminarInicio();
    void Mostrar();
    void Guardar();
    void Recuperar();
};

Paquete::Paquete(int id,string origen,string destino,int peso)
{
    Id = id;
    Origen = origen;
    Destino = destino;
    Peso = peso;
    pSig = NULL;

}

void Paquete::InsertarInicio(int id,string origen,string destino,int peso)
{
        if(pSig == 0)
        {

            pSig = new Paquete(id,origen,destino,peso);
        }
        else if(pSig != 0)
        {
            pSig->InsertarInicio(id,origen,destino,peso);
        }

}

Paqueteria::Paqueteria()
{
    Lista = NULL;
    Inicio = NULL;
}

void Paqueteria::InsertarInicio(int id,string origen,string destino,int peso)
{

    if(Lista == NULL)
    {
        Lista = new Paquete(id,origen,destino,peso);
    }
    else
    {
        Lista->InsertarInicio(id,origen,destino,peso);
    }

}

void Paquete::Mostrar()
{
    Paquete* Pnn = this;

    while(Pnn != NULL)
    {
        cout << Pnn->Id << "| ";
        cout << Pnn->Origen << " ";
        cout << Pnn->Destino << " ";
        cout << Pnn->Peso << " ";
        Pnn = Pnn->pSig;
    }

}

void Paqueteria::EliminarInicio()
{
    Lista->EliminarInicio();
}

void Paquete::EliminarInicio()
{

    Paquete* Pnn = this->pSig->pSig;
    Paquete* Aux = this;

	delete this->pSig;

	this->pSig = Pnn;
}

void Paqueteria::Mostrar()
{

    Lista->Mostrar();

}

void Paqueteria::Guardar()
{
    char cadena[10];
    char peso[5];
    char* origen;
    char* destino;

    ofstream File("Paqueteria.txt");


    if (!File)
    {
         cout <<"Error de apertura "<<endl;
    }

    while(Lista != NULL)
    {
         sprintf(cadena,"%d",Lista->Id);
         sprintf(peso,"%d",Lista->Peso);
         File.write(cadena,5);
         File.write(",",1);
         origen = &*Lista->Origen.begin();
         File.write(origen,11);
         File.write(",",1);
         destino = &*Lista->Destino.begin();
         File.write(destino,10);
         File.write(",",1);
         File.write(peso,5);
         File.write("|",1);
         Lista = Lista->pSig;
    }
    File.close();

}

void Paqueteria::Recuperar()
{
    ifstream File("Paqueteria.txt");


    if(File.is_open())
    {

    while(!File.eof())
    {
    int id = 0;
    string origen;
    string oracion;
    string destino;
    int peso = 0;
    stringstream ss;
    stringstream ss2;

        std::getline(File,oracion,',');
        ss << oracion;
        ss >> id;

        std::getline(File,oracion,',');
        origen = oracion;

        std::getline(File,oracion,',');
        destino = oracion;

        std::getline(File,oracion,'|');
        ss2 << oracion;
        ss2 >> peso;


            Lista->InsertarInicio(id,origen,destino,peso);

        if(File.eof())
        {
            break;
        }
      }
    }
    File.close();
}

int main()
{
    string origen = {"Guadalajara"};
    string destino = {"Puebla"};

    string origen1 = {"China"};
    string destino1 = {"Tokio"};

    Paqueteria P;
    cout <<"\nInsertamos 2 veces..."<<endl;
    P.InsertarInicio(2180,origen,destino,3);
    P.InsertarInicio(7569,origen1,destino1,5);

    P.Mostrar();

    cout <<"\nEliminamos..."<<endl;
    P.EliminarInicio();
    P.Mostrar();

    string origen2 = {"Caelid"};
    string destino2 = {"Limgrave"};

    string origen3 = {"Kakariko"};
    string destino3 = {"Ciudadela"};

    cout <<"\nInsertando..."<<endl;
    P.InsertarInicio(44980,origen2,destino2,11);
    P.InsertarInicio(56890,origen3,destino3,6);

    cout <<"\n";
    P.Mostrar();
    P.Guardar();
    P.Recuperar();

    cout <<"\nRecuperar: "<<endl;
    cout <<"\n";
    P.Mostrar();

    system("pause");
    return 0;
}
