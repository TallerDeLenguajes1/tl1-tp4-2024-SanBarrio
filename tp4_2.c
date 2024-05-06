#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indexID = 1000;
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
void mostrarLista(Nodo *nodito);
Tarea seleccionarTarea(Nodo **nodito);
void eliminarNodo(Nodo **nodito);

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

    } while (seguir != 0);
    printf("\n----------------- SE FINALIZÓ LA CARGA DE TAREAS -----------------");
    mostrarLista(tareasPendientes);

    Tarea tareaTransferida = seleccionarTarea(&tareasPendientes);

    // Si el ID de la tarea devuelta es distinto de -1, quiere decir que se seleccionó una tarea existente
    if (tareaTransferida.TareaID != -1){
        insertarNodo(&tareasRealizadas, crearNodo(tareaTransferida));
    }
    mostrarLista(tareasRealizadas);

    return 0;
}

Nodo *crearListaVacia()
{
    return NULL;
}

Tarea crearTarea()
{
    printf("\n-------------INSERTANDO UNA NUEVA TAREA-------------");

    Tarea nuevaTarea;

    nuevaTarea.TareaID = indexID++;

    nuevaTarea.Descripcion = (char *)malloc(MAX_LARGO * sizeof(char));
    printf("\nIngrese la descripcion: ");
     fflush(stdin);
    gets(nuevaTarea.Descripcion);

    fflush(stdin);
    printf("\nIngrese la duración: ");
    scanf("%d", &nuevaTarea.Duracion);

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

void mostrarLista(Nodo *nodito)
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

Tarea seleccionarTarea(Nodo **nodito)
{
    printf("\n------------------ SELECCIONANDO UNA TAREA PARA TRANSFERIR ------------------");

    Nodo **aux = nodito;
    int idSeleccionado = 0;
    Tarea tareaSeleccionada;

    printf("\n- Digite el ID de la tarea a transferir: ");
    fflush(stdin);
    scanf("%d", &idSeleccionado);

    // Recorro las tareas hasta encontrar la seleccionada o llegar al final de la lista
    while ((*aux != NULL) && ((*aux)->T.TareaID != idSeleccionado))
    {
        aux = &(*aux)->Siguiente;
    }

    // Si aux NO es null, quiere decir que encontré una tarea con el ID indicado
    if ((*aux) != NULL)
    {
        // Almaceno los datos de la tarea seleccionada en una nueva Tarea
        tareaSeleccionada.TareaID = (*aux)->T.TareaID;
        tareaSeleccionada.Descripcion = (char *)malloc((strlen((*aux)->T.Descripcion) + 1) * sizeof(char));
        strcpy(tareaSeleccionada.Descripcion, (*aux)->T.Descripcion);
        tareaSeleccionada.Duracion = (*aux)->T.Duracion;

        // Elimino el nodo correspondiente a la tarea que será transferida
        eliminarNodo(aux);
    }
    else
    {
        printf("\n\n[!] El ID ingresado no corresponde a ninguna tarea [!]\n\n");
        tareaSeleccionada.TareaID = -1;
    }

    return tareaSeleccionada;
}

void eliminarNodo(Nodo **nodito)
{
    Nodo *temp = (*nodito);
    (*nodito) = (*nodito)->Siguiente;
    free(temp->T.Descripcion);
    free(temp);
}