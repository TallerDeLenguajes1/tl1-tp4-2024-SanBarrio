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

Tarea filtrarId(Nodo *lista, int id);
Tarea filtrarPalabra(Nodo *lista, char *palabraClave);
void mostrarTarea(Tarea tarea, char * tipoTarea);

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

    seguir = 1;

    do
    {

        Tarea tareaTransferida = seleccionarTarea(&tareasPendientes);
        if (tareaTransferida.TareaID != -1)
        {
            insertarNodo(&tareasRealizadas, crearNodo(tareaTransferida));
        }
        printf("¿Desea seguir transfiriendo tareas? SI(1) o NO(0):\n");
        fflush(stdin);
        scanf("%d", &seguir);
    } while (seguir != 0);
    mostrarLista(tareasRealizadas);

    printf("\nDesea filtrar por ID o por palabra Clave? ID(1) o Palabra Clave (2):\n");
    scanf("%d", &seguir);
    if(seguir==1){
        int id;
        printf("\nDigite el ID a buscar: ");
        scanf("%d", &id);


        Tarea tareaFiltrada = filtrarId(tareasPendientes, id);
            if (tareaFiltrada.TareaID == -1) // Si el ID de la tarea es -1, quiere decir que no se encontró una tarea con ese ID en la lista
            {
                tareaFiltrada = filtrarId(tareasRealizadas, id);
                if (tareaFiltrada.TareaID == -1) // Si el ID de la tarea es -1, quiere decir que no se encontró una tarea con ese ID en la lista
                {
                    printf("\n[!] NO se ha encontrado una tarea con el ID especificado [!]\n");
                }
                else
                {
                    mostrarTarea(tareaFiltrada, "TAREA REALIZADA");
                }
            }
            else
            {
                mostrarTarea(tareaFiltrada, "TAREA PENDIENTE");
            }
    }else{
            char *palabraClave;

            palabraClave = (char *)malloc( MAX_LARGO * sizeof(char) );
            printf("\nDigite la palabra clave a buscar: ");
            fflush(stdin);

            gets(palabraClave);

            Tarea tareaFiltradaB = filtrarPalabra(tareasPendientes, palabraClave);
            if (tareaFiltradaB.TareaID == -1) // Si el ID de la tarea es -1, quiere decir que no se encontró una tarea con ese ID en la lista
            {
                tareaFiltradaB = filtrarPalabra(tareasRealizadas, palabraClave);
                if (tareaFiltradaB.TareaID == -1) // Si el ID de la tarea es -1, quiere decir que no se encontró una tarea con ese ID en la lista
                {
                    printf("\n[!] NO se ha encontrado una tarea con el ID especificado [!]\n");
                }
                else
                {
                    mostrarTarea(tareaFiltradaB, "TAREA REALIZADA");
                }
            }
            else
            {
                mostrarTarea(tareaFiltradaB, "TAREA PENDIENTE");
            }
    } 

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

Tarea filtrarId(Nodo *lista, int id)
{
    Tarea tareaEncontrada;
    tareaEncontrada.TareaID = -1;
    
    while ( (lista != NULL) && (lista->T.TareaID != id) )
    {
        lista = lista->Siguiente;
    }

    if (lista != NULL)
    {
        tareaEncontrada.TareaID = lista->T.TareaID;
        tareaEncontrada.Descripcion = (char *)malloc( (strlen(lista->T.Descripcion) + 1) * sizeof(char) );
        strcpy(tareaEncontrada.Descripcion, lista->T.Descripcion);
        tareaEncontrada.Duracion = lista->T.Duracion;
    }

    return tareaEncontrada;
}


Tarea filtrarPalabra(Nodo *lista, char *palabraClave)
{
    Tarea tareaEncontrada;
    tareaEncontrada.TareaID = -1;

    while ( (lista != NULL) && (strstr(lista->T.Descripcion, palabraClave) == NULL) )
    {
        lista = lista->Siguiente;
    }

    if (lista != NULL)
    {
        tareaEncontrada.TareaID = lista->T.TareaID;
        tareaEncontrada.Descripcion = (char *)malloc( (strlen(lista->T.Descripcion) + 1) * sizeof(char) );
        strcpy(tareaEncontrada.Descripcion, lista->T.Descripcion);
        tareaEncontrada.Duracion = lista->T.Duracion;
    }

    return tareaEncontrada;
}


void mostrarTarea(Tarea tarea, char *tipoTarea)
{
    printf("\n-----------------------Tarea de ID %d (%s)-------------------", tarea.TareaID, tipoTarea);
    printf("\nDescripcion: %s", tarea.Descripcion);
    printf("\nDuracion: %d\n", tarea.Duracion);
}