#include <stdio.h>
#include <string.h>
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
// ------------------------------------ ACA EMPIEZA EL MAIN --------------------------------

int main() // Cada preventista puede visitar hasta 5 clientes, los cuales por cuestiones operativas solo puede pedir hasta 10 productos.
{
    int cantClientes;
    char buffer[100];
    srand(time(NULL));
    printf("Ingrese la cantidad de clientes: ");
    scanf("%d", cantClientes);
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
            // El símbolo '&' obtiene la dirección de memoria
        // float total = costoTotalProducto(&listaClientes[i].Productos[j]); esto seria asi con punteros
        // El símbolo '&' obtiene la dirección de memoria
        float total = costoTotalProducto(listaClientes[i].Productos[j]); // ahora es sin punteros
        }
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