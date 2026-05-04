#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// declaro el procedimiento, siempre se hace la declaración arriba y abajo desarrollo el procedimiento o función
void mostrarPersonas(char **nombre);
void buscarNombre(int ID, char ** nombres);
int main()
{
    char *nombre; // esto no tiene que tener [] porque para eso despues reservo memoria, este solo guarda un nombre
    char **nombres; // es un puntero que apunta a otro puntero (arreglo de punteros) este va a contener los 5 nombres
    char buffer[100];
    nombres = (char **) malloc(5 * sizeof(char *)); // va apuntar a 5 direcciones de memoria del tipo char
    for (int i = 0; i < 5; i++)
    {
        printf("Ingresa el nombre: ");
        scanf("%s", buffer); // %s cadena de caracteres %c un caracter, no hace falta el &
        int cant = strlen(buffer); // cuenta la cantidad de caracteres, esto necesito para reservar memoria asi puedo hacer el malloc
        nombre = (char*)malloc(cant*sizeof(char)+1); // aca estoy haciendo espacios para cantidad de caracteres, o sea, si tengo majo, va a reservar 4 y el +1 es para guardar el caracter de escape \0
        strcpy(nombre, buffer); // Esta función copia lo que hay en buffer hacia tu nueva memoria.
        nombres [i] = nombre; // guardo el nombre
    }
    mostrarPersonas(nombres);
    int ID;
    printf("Ingrese el ID de la persona que desea buscar: ");
    scanf("%d", &ID);
    buscarNombre(ID, nombres);
    return 0;
}
// defino el procedimiento
void mostrarPersonas(char **nombres){ //si no pongo ** no me va a mostrar nada
    for (int i = 0; i < 5; i++)
    {
        printf("Nombre %d: %s\n", i + 1, nombres[i]);
    }
}
void buscarNombre(int ID, char **nombres){
    if ((ID >= 1) && (ID<=5)  )
    {
                printf("Nombre %d: %s\n",ID, nombres[ID-1]);
    }else
    {
        printf("No se encontró el valor buscado, ingrese otro");
    }
    
    
}


