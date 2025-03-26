/* Sistema de gestión de citas: una aplicación que permita a los pequeños negocios 
programar citas y recordatorios de citas para sus clientes, y enviar correos electrónicos 
o mensajes de texto para recordatorios. EQUIPO 7 */

#include "iostream"
#include "Empresa.h"
#include "string"

using namespace std;

int main(){
    vector<Empresa> empresas; //Creamos vector del objeto Empresa

    Empresa emp1("Apple", "apple", "123"); //Creamos un objeto y lo añadimos al vector
    empresas.push_back(emp1);
    system("cls");
    //Preguntamos Usuario y contraseña
    cout << " ---- Inicio Sesion ----" << endl;
    string user = d.capTxt("Usuario: ");
    string contra = d.capTxt("Password: ");
    int Borrar;
    for (int i = 0; i < empresas.size(); i++)
    {
        if (user == empresas[i].getUser() && contra == empresas[i].getPassword()) // Comparacion con todos los datos de las empresas
        {
            empresas[i].RecuperarInfoClientes(); //Recuperamos informacion de clientes y citas 
            empresas[i].RecuperarInfoCitas();
            empresas[i].menu(); //Desplegamos el menu
        }
        Borrar = i;
    }
    empresas[Borrar].~Empresa(); //Utilizamos el destructor 
    return 0;
}