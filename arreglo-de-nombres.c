#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// declaro el procedimiento, siempre se hace la declaración arriba y abajo desarrollo el procedimiento o función
void mostrarPersonas(char **nombre);
int buscarNombre(char *palabraClave, char **nombres);
int main()
{
    char *nombre;   // esto no tiene que tener [] porque para eso despues reservo memoria, este solo guarda un nombre
    char **nombres; // es un puntero que apunta a otro puntero (arreglo de punteros) este va a contener los 5 nombres
    char buffer[100];
    nombres = (char **)malloc(5 * sizeof(char *)); // va apuntar a 5 direcciones de memoria del tipo char
    for (int i = 0; i < 5; i++)
    {
        printf("Ingresa el nombre: ");
        scanf("%s", buffer);                              // %s cadena de caracteres %c un caracter, no hace falta el &
        int cant = strlen(buffer);                        // cuenta la cantidad de caracteres, esto necesito para reservar memoria asi puedo hacer el malloc
        nombre = (char *)malloc(cant * sizeof(char) + 1); // aca estoy haciendo espacios para cantidad de caracteres, o sea, si tengo majo, va a reservar 4 y el +1 es para guardar el caracter de escape \0
        strcpy(nombre, buffer);                           // Esta función copia lo que hay en buffer hacia tu nueva memoria.
        nombres[i] = nombre;                              // guardo el nombre
    }
    mostrarPersonas(nombres);
    char palabraClave[100];
    printf("Ingrese la palabra clave: ");
    scanf("%s", palabraClave);
    int resultado = buscarNombre(palabraClave, nombres);
    if (resultado != -1)
    {
        printf("La palabra que buscabas es: %s", nombres[resultado]);
    }else
    {
        printf("No se encontro nada");
    }
    
    
    for (int i = 0; i < 5; i++) // aca libero el espacio de cada nombre
    {
        free(nombres[i]);
    }
    free(nombres); // y aca el del bloque completo
    return 0;
}
// defino el procedimiento
void mostrarPersonas(char **nombres)
{ // si no pongo ** no me va a mostrar nada
    for (int i = 0; i < 5; i++)
    {
        printf("Nombre %d: %s\n", i + 1, nombres[i]);
    }
}

int buscarNombre(char *palabraClave, char **nombres) // NO TE OLVIDES DEL * EN PALABRA CLAVE O EN LOS ARREGLOS CUANDO PASAS ARREGLOS PORQUE SINO NO PUEDE LEER NI HACER NADA Y SE PRODUCE UN SEGMENTATION FAULT
{
    for (int i = 0; i < 5; i++)
    {
        // strstr busca si palabraClave está dentro de nombres[i]
        if (strstr(nombres[i], palabraClave) != NULL)
        {
            return i;
        }
    }
    return -1;
}