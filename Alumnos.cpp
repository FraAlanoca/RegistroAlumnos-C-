#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;


//Structuras
struct Registro
{
    int legajo;
    string nombre;
    float nota; //promedios de los examenes finales y trabajo final
    string materia;//nombre del curso o asignatura que cursan
    short fecha;//año en el cual cursó la materia
};


//Prototipos
void obtenerDiscreta(Registro reg, Registro vector2015[], Registro vector2016[], int t, int s);
void ordenarPorLegajoAsc(Registro vector2015[], int tam);
void ordenarPorNotaDes(Registro vector2016[], int tam2);
int calcularPromedio(Registro vector[], int tam);
void promedioMayor(int prom2015, int prom2016);
int cantidadDesaprobados(Registro vector[], int tam, int desaprobados);
void menosDesaprobados(int des2015, int des2016);
void busquedaNota(Registro vector[], int tam, int legajo);
int notaAltaDiscreta(Registro reg, int max);
void guardarNotaDiscreta(Registro reg, Registro reg1, int max);
void eliminarQuimica(Registro reg);



int main (){
    
    FILE* arch = fopen("alumnos.bin","rb");
    FILE* arch1 = fopen("MejoresNotas.bin","wb");
    int t = 0, s = 0;
    
    Registro reg;
    Registro reg1;
    Registro vector2015[t];
    Registro vector2016[s];

    int tam = sizeof(vector2015);
    int tam2 = sizeof(vector2016);
    int prom2015 = 0;
    int prom2016 = 0;
    int desaprobados = 0;
    int des2015 = 0;
    int des2016 = 0;
    int legajo = 0;
    cout<<"ingrese numero de legajo a buscar"<<endl;
    cin>>legajo;
    int max = 0;


    while (!feof(arch)==0){
        obtenerDiscreta(reg, vector2015, vector2016, t, s);
        ordenarPorLegajoAsc(vector2015, tam);
        ordenarPorNotaDes(vector2016, tam2);
        prom2015 = calcularPromedio(vector2015, tam);
        prom2016 = calcularPromedio(vector2016, tam2);
        promedioMayor(prom2015, prom2016);
        des2015 = cantidadDesaprobados(vector2015, tam, desaprobados);
        des2016 = cantidadDesaprobados(vector2016, tam, desaprobados);
        menosDesaprobados(des2015, des2016);
        busquedaNota(vector2015, tam, legajo);
        notaAltaDiscreta(reg, max);
        guardarNotaDiscreta(reg, reg1, max);
        eliminarQuimica(reg);
    }
    
    fclose(arch);
    fclose(arch1);
    return 0;
}



//Funciones
//Parte A
//1)
void obtenerDiscreta(Registro reg, Registro vector2015[], Registro vector2016[], int t, int s){
    if(reg.materia == "Matematica Discreta"){
            if (reg.fecha == 2015){
                vector2015[t] = reg;
                t++;
            }if (reg.fecha == 2016){
                vector2016[s] = reg;
                s++;
            }
        }

}



//Parte B
//2)
void ordenarPorLegajoAsc(Registro vector2015[], int tam){
    Registro aux1;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam - 1; j++)
        {
            if(vector2015[j].legajo > vector2015[j+1].legajo){
                aux1 = vector2015[j];
                vector2015[j] = vector2015[j+1];
                vector2015[j+1] = aux1;
            }
        }
        
    }
    
}


void ordenarPorNotaDes(Registro vector2016[], int tam2){
    Registro aux2;
    for (int a = 0; a < tam2; a++)
    {
        for (int b = 0; b < tam2 - 1; b++)
        {
            if(vector2016[b].nota < vector2016[b+1].nota){
                aux2 = vector2016[b];
                vector2016[b] = vector2016[b+1];
                vector2016[b+1] = aux2;
            }
        }
        
    }

}


//3)
int calcularPromedio(Registro vector[], int tam){
    int cont1 = 0;
    int cantidad = 0;
    int promedio = 0;
    for (int x = 0; x < tam; x++)
    {
        cont1 = vector[x].nota + cont1;
        cantidad++;
    }
    promedio = cont1 / cantidad;
    return promedio;
}


void promedioMayor(int prom2015, int prom2016){
    if (prom2015 > prom2016)
    {
        cout<<"Ele promedio del año 2015 fue mayor"<<endl; 
    }
    if (prom2015 != prom2016)
    {
        cout<<"El promedio del año 2016 fue mayor"<<endl;
    }
    
}


//4)
int cantidadDesaprobados(Registro vector[], int tam, int desaprobados){
    int d = 0;
    for (int i = 0; i < tam; i++)
    {
        if(vector[i].nota < 4){
            d++;
        }
    }
    desaprobados = d;
    return desaprobados;
}

void menosDesaprobados(int des2015, int des2016){
    if (des2015 < des2016)
    {
        cout<<"Hubo menos desaprobados en 2015"<<endl;
    }if (des2015 != des2016)
    {
        cout<<"Hubo menos desaprobados en 2016"<<endl;
    }
    
}

//5)
void busquedaNota(Registro vector[], int tam, int legajo){
    for (int i = 0; i < tam; i++)
    {
        if (vector[i].legajo == legajo)
        {
            cout<<vector[i].materia<<endl;
            cout<<vector[i].nota<<endl;
        }
        
    }
    
}

//6)
/*
Sí, es posible buscar por nota, utilizando un método similar al empleado en el punto 5) (habría que 
realizar cambios en el algoritmo). Sin embargo el campo nota posee un valor similar en distintos 
registros del vector, es decir que no es único, por lo que la búsqueda no será precisa.
*/


//7)
int notaAltaDiscreta(Registro reg, int max){
    
    if(reg.materia == "Matematica Discreta"){
        if (reg.nota > max)
        {
            max = reg.nota;
        }
    }
    return max;
}

void guardarNotaDiscreta(Registro reg, Registro reg1, int max){
    if(reg.materia == "Matematica Discreta"){
        if (reg.nota == max)
        {
            cout<<reg1.nota;
        }
    }
}

//8)
void eliminarQuimica(Registro reg){
    if (reg.materia == "Quimica")
    {
        reg.materia = "";
        reg.nombre = "";
        reg.legajo = 0;
        reg.nota = 0;
        reg.fecha = 0;

    }
    
}