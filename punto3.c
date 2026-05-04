#include <stdio.h>
#include <string.h>
#include <stdlib.h> // ACORDATE QUE ESTA LIBRERIA TENES QUE PONER PARA EL SRAND, MALLOC y free
#include <time.h>

char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

// ESTRUCTURAS

typedef struct
{
    int ProductoID;       // Numerado en ciclo iterativo
    int Cantidad;         // entre 1 y 10
    char *TipoProducto;   // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
} Producto;

// -----------------------------------------------------------------

typedef struct
{
    int ClienteID;               // Numerado en el ciclo iterativo
    char *NombreCliente;         // Ingresado por usuario
    int CantidadProductosAPedir; // (aleatorio entre 1 y 5)
    Producto *Productos;         // El tamaño de este arreglo depende de la variable  “CantidadProductosAPedir”
} Cliente;
// ------------------------------------ FUNCIONES ---------------------------------------
float costoTotalProducto(Producto p);
void mostrarListaDeClientes(Cliente *listaClientes, int cantClientes);
// ------------------------------------ ACA EMPIEZA EL MAIN --------------------------------

int main() // Cada preventista puede visitar hasta 5 clientes, los cuales por cuestiones operativas solo puede pedir hasta 10 productos.
{
    int cantClientes;
    float totalPorProducto;
    char buffer[100];
    srand(time(NULL));
    printf("Ingrese la cantidad de clientes: ");
    scanf("%d", &cantClientes);
    Cliente *listaClientes = (Cliente *)malloc(cantClientes * sizeof(Cliente)); // necesito un puntero para cargar los datos de todos los clientes
    for (int i = 0; i < cantClientes; i++)
    {
        listaClientes[i].ClienteID = i + 1; // aca asigno ID a los clientes
        // PIDO EL NOMBRE DEL CLIENTE
        printf("Ingrese nombre del cliente: ");
        scanf("%s", buffer);
        listaClientes[i].NombreCliente = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(listaClientes[i].NombreCliente, buffer); // cargo el nombre del cliente
        // cantidad de productos que supuestamente desea pedir el cliente
        listaClientes[i].CantidadProductosAPedir = rand() % 5 + 1;
        // aca hago una reserva de memoria para cargar los productos del cliente
        listaClientes[i].Productos = (Producto *)malloc(listaClientes[i].CantidadProductosAPedir * sizeof(Producto));
        // necesito otro for para cargar los datos de los productos
        for (int j = 0; j < listaClientes[i].CantidadProductosAPedir; j++)
        {
            listaClientes[i].Productos[j].ProductoID = j + 1;
            listaClientes[i].Productos[j].Cantidad = rand() % 10 + 1;                 // 1 a 10
            listaClientes[i].Productos[j].TipoProducto = TiposProductos[rand() % 5];  // ya esta definido los tipos de procutos con los cuales va a trabajar el usuario
            listaClientes[i].Productos[j].PrecioUnitario = (float)(rand() % 91 + 10); // 10 a 100
            
        }
    }
    mostrarListaDeClientes(listaClientes, cantClientes);
    for (int i = 0; i < cantClientes; i++)
    {
        free(listaClientes[i].NombreCliente);
    }
    free(listaClientes);
    return 0;
}

// ---------------------------------------- DESARROLLO DE FUNCIONES -------------------------------------------
float costoTotalProducto(Producto p)
{ // hago pasaje por valor
    return p.Cantidad * p.PrecioUnitario;
}

// float costoTotalProducto(Producto *p){ // hago pasaje por referencia
//    return p->Cantidad*p->PrecioUnitario;
// }

void mostrarListaDeClientes(Cliente *listaClientes, int cantClientes)
{
    for (int i = 0; i < cantClientes; i++)
    {
        float costoTotal = 0;
        printf("\n-----------------------------------------------------------------");
        printf("\nID del cliente: %d", listaClientes[i].ClienteID);
        printf("\nNombre del cliente: %s", listaClientes[i].NombreCliente);
        printf("\nCantidad de Productos a pedir: %d", listaClientes[i].CantidadProductosAPedir);
       for (int j = 0; j< listaClientes[i].CantidadProductosAPedir; j++)
       {
        printf("\n********************************************");
           printf("\nID del producto: %d", listaClientes[i].Productos[j].ProductoID);
           printf("\nCantidad: %d", listaClientes[i].Productos[j].Cantidad);
           printf("\nTipo de producto: %s", listaClientes[i].Productos[j].TipoProducto);
           printf("\nPrecio unitario: %.2f", listaClientes[i].Productos[j].PrecioUnitario);
           float totalPorProducto = costoTotalProducto(listaClientes[i].Productos[j]); // ahora es sin punteros
           costoTotal +=totalPorProducto;
           printf("\nCosto total por producto: %.2f", totalPorProducto);
    }
        printf("\nEl total a pagar por los productos es: %.2f", costoTotal);
    }
}