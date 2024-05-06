#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indexID= 1000;
#define MAX_LARGO 200

typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;


typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *crearListaVacia();
Tarea crearTarea();
void insertarNodo(Nodo **nodito, Nodo *nuevaTarea);
Nodo *crearNodo(Tarea tarea);
void mostrarLista(Nodo * nodito);

int main()
{
    Nodo *tareasPendientes = crearListaVacia();
    Nodo *tareasRealizadas = crearListaVacia();

    int seguir = 1;

    do
    {
        insertarNodo(&tareasPendientes, crearNodo(crearTarea()));
        printf("¿Desea seguir cargando mas tareas? SI(1) o NO(0):\n");
        scanf("%d", &seguir);


    } while (seguir!=0);
    printf("\n----------------- SE FINALIZÓ LA CARGA DE TAREAS -----------------");
    mostrarLista(tareasPendientes);

    


    
 
    return 0;
}


Nodo *crearListaVacia(){
    return NULL;
}

Tarea crearTarea()
{
    printf("\n-------------INSERTANDO UNA NUEVA TAREA-------------");

    Tarea nuevaTarea;
    

    nuevaTarea.TareaID = indexID++;
   
    nuevaTarea.Descripcion = (char *)malloc(MAX_LARGO * sizeof(char));
    printf("\nIngrese la descripcion: ");
    gets(nuevaTarea.Descripcion);
    // Ingreso la duración verificando que sea un número entre 10 y 100
    fflush(stdin);
    printf("\nIngrese la duración: ");
    scanf("%d",&nuevaTarea.Duracion);
    
    return nuevaTarea;
}

void insertarNodo(Nodo **nodito, Nodo *nuevaTarea)
{
    if (*nodito == NULL)
    {
        nuevaTarea->Siguiente = *nodito;
        *nodito = nuevaTarea;
    }
    else
    {
        Nodo *aux = *nodito;
        while (aux->Siguiente)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nuevaTarea;
    }
}

Nodo *crearNodo(Tarea tarea)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));

    nuevoNodo->T.Descripcion = (char *)malloc((strlen(tarea.Descripcion) + 1) * sizeof(char));
    strcpy(nuevoNodo->T.Descripcion, tarea.Descripcion);
    nuevoNodo->T.TareaID = tarea.TareaID;
    nuevoNodo->T.Duracion = tarea.Duracion;

    nuevoNodo->Siguiente = NULL;

    return nuevoNodo;
}

void mostrarLista(Nodo * nodito)
{
    printf("\n------------------ MOSTRANDO LISTA ----------------------\n");

    while (nodito != NULL)
    {
        printf("\n- Tarea ID: %d", nodito->T.TareaID);
        printf("\n\t- Descripcion: %s", nodito->T.Descripcion);
        printf("\n\t- Duracion: %d", nodito->T.Duracion);
        printf("\n");

        nodito = nodito->Siguiente;
    }
}

