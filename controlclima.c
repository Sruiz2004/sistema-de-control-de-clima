#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getrandom();        //calcular numero aleatorio
int getsetpoint();      //obtener el setpoint
int calcdelta(int s, int r, int *frio, int *calor);     //calculamos el deta y a demas si necesitamos frio o calor

int a = 0;      //valor del for
int b = 0;      //valor de fin de for

int valrandom = 0;     //valor de temperatura actual(10-40)
int setpoint = 0;       //valor de temperatura de consigna(15-35)
int delta =0;       //diferencia entre temperatura actual y temperatura de consigna(0-10)
int frio = 0;       //estado de frio(0-1)
int calor = 0;       //estado de calor(0.1)
int condensador = 0;        //estado del condensador(0-100)
int compresor = 0;      //estado del compresor(0-3)
int bomba = 0;      //estado de la bomba(0-100)
int ressistencia = 0;       //estado de la resistencia(0-3)
int evaporador = 0;     //estado del evaporador(10-100)

int main(void)
{
    FILE *archivo;      //creamos archivo
    archivo = fopen("datos.json", "w");     //creamos el json en modo write

    fprintf(archivo, "{\n");        //escribimos

    if (archivo == NULL)        //comprobamso que se creo correctamente
    {
        printf("No se pudo abrir el archivo.\n");       //avisamos al usuario
        return 1;       //devolvemos 1
    }

    fclose(archivo);        //cerramos archivo

    setpoint = getsetpoint();       //output del usuario
    printf("ingresa la cantidad de simulaciones: ");       //aviso al usuario del valor a ingresar
    scanf("%d", &b);      //input del teclado
    for(a = 1 ; a <= b ; a++)       //repetimos el proceso b veces
    {
    valrandom = getrandom();       //output del numero random   
    int temp_frio = 0;      // Variable temporal para frio
    int temp_calor = 0;     // Variable temporal para calor
    delta = calcdelta(setpoint, valrandom, &temp_frio, &temp_calor);    //output del delta
    frio = temp_frio;       //rescatamos el valor de frio
    calor = temp_calor;     //rescatamos el valor de calor
    printf("frio %d, calor %d\n", frio, calor);     //comprobacion del numero
    if (frio == 1)      //si entro en modo frio
    {
        condensador = ((delta*100)/10);     //definimos la velocidad del condensador
        printf("condensador al %d\n", condensador);     //comprobacion del numero
        if (delta>=0 && delta<=3)       //si el delta es del 33%
        {
            compresor = 1;
            printf("compresor en LOW\n");       //compresor en low
        }
        else if (delta>=4 && delta<=6)      //si el delta es del 66%
        {
            compresor = 2;
            printf("compresor en MID\n");       //compresor en mid
        }
        else if (delta>=7 && delta<=10)     //si el delta es del 100%
        {
            compresor = 3;
            printf("compresor en HIGH\n");      //compresor en high
        }
        else        //si no se da ningun caso
        {
            compresor = 0;
            printf("compresor en OFF\n");       //compresor apagado
        }
        bomba = 0;      //bomba apagado
        printf("bomba al %d\n", bomba);       //comprobacion del numero
        ressistencia = 0;       //resistencia apagado
        printf("resistencia en OFF\n");       //comprobacion del numero
        evaporador = ((delta*100)/10);      //definimos la velocidad del evaporador
        if (evaporador<10)      //si evaporador esta por debajo de 10
        {
            evaporador = 10;        //le forzamos a estar en 10
        }
        printf("evaporador al %d\n", evaporador);       //comprobacion del numero
    }
    else if (calor == 1)        //si entro en modo calor
    {
        condensador = 0;     //condensador apagado
        printf("condensador al %d\n", condensador);     //comprobacion del numero
        compresor = 0;      //compresor apagado
        printf("compresor en OFF\n");       //comprobacion del numero
        bomba = ((delta*100)/10);       //definimos la velocidad de la bomba
        printf("bomba al %d\n", bomba);       //bomba apagado
        if (delta>=0 && delta<=3)       //si el delta es del 33%
        {
            ressistencia = 1;
            printf("resistencia en LOW\n");       //compresor en low
        }
        else if (delta>=4 && delta<=6)      //si el delta es del 66%
        {
            ressistencia = 2;
            printf("resistencia en MID\n");       //compresor en mid
        }
        else if (delta>=7 && delta<=10)     //si el delta es del 100%
        {
            ressistencia = 3;
            printf("resistencia en HIGH\n");      //compresor en high
        }
        else        //si no se da ningun caso
        {
            ressistencia = 0;
            printf("resistencia en OFF\n");       //compresor apagado
        }
        evaporador = ((delta*100)/10);      //definimos la velocidad del evaporador
        if (evaporador<10)      //si eaporador esta por debajo de 10
        {
            evaporador = 10;        //lo forzamos a 10
        }
        printf("evaporador al %d\n", evaporador);       //definimos la velocidad del evaporador
    }
    else
    {
        condensador = 0;     //condensador apagado
        printf("condensador al %d\n", condensador);     //comprobacion del numero
        compresor = 0;      //compresor apagado
        printf("compresor en OFF\n");       //comprobacion del numero
        bomba = 0;      //bomba apagado
        printf("bomba al %d\n", bomba);       //comprobacion del numero
        ressistencia = 0;       //resistencia apagado
        printf("resistencia en OFF\n");       //comprobacion del numero
        evaporador = ((delta*100)/10);      //definimos la velocidad del evaporador
        if (evaporador<10)      //si el evaporador esta por debajo de 10
        {
            evaporador = 10;        //lo forzamos a 10
        }
        printf("evaporador al %d\n", evaporador);       //comprobacion del numero
    }
     
    archivo = fopen("datos.json", "a");     //abrimos el archibo en modo añadir

    if (archivo == NULL)        //comprobamso que se creo correctamente
    {
        printf("No se pudo abrir el archivo.\n");       //avisamos al usuario
        return 1;       //devolvemos 1
    }

    fprintf(archivo, "{\n");        //escribimos en el json
    fprintf(archivo, "  \"caso_numero\": %d,\n", a);        //escribimos en el json
    fprintf(archivo, "  \"temperatura_actual\": %d,\n", valrandom);        //escribimos en el json
    fprintf(archivo, "  \"temperatura_consigna\": %d,\n", setpoint);        //escribimos en el json
    fprintf(archivo, "  \"delta\": %d,\n", delta);        //escribimos en el json
    fprintf(archivo, "  \"condensador\": %d,\n", condensador);        //escribimos en el json
    fprintf(archivo, "  \"compresor\": %d,\n", compresor);        //escribimos en el json
    fprintf(archivo, "  \"bomba\": %d,\n", bomba);        //escribimos en el json
    fprintf(archivo, "  \"resistencia\": %d,\n", ressistencia);        //escribimos en el json
    fprintf(archivo, "  \"evaporador\": %d\n", evaporador);        //escribimos en el json

    if (a==b)       //si hemos acabado
    {
        fprintf(archivo, "}\n");        //escribimos en el json
        fprintf(archivo, "}\n");               //escribimos en el json
    }
    else        //si no hemos acabado
    {
        fprintf(archivo, "},\n");        //escribimos en el json
    }

    fclose(archivo);        //cerramos archivo    

    printf("Valores guardados en datos.json\n");        //avisamos al usuario
    } 
}

int getsetpoint()       //input del usuario
{
    while (setpoint<18 || setpoint>30)      //si el usuario ingresa un valor fuera del rango se repite
    {
        printf("Ingresa el valor de consigna(18/30): ");       //aviso al usuario del valor a ingresar
        scanf("%d", &setpoint);      //input del teclado
    } 
    printf("el valor de consigna es: %d grados\n",setpoint);       //comprobacion del numero
    return setpoint;        //lo enviamos al main
}

int getrandom()     //calcular numero aleatorio
{
    int min = 14; // Valor mínimo del rango
    int max = 34; // Valor máximo del rango

    srand(time(NULL) * a);      //semilla del numero aleatorio
    int valrandom = rand() % (max - min + 1) + min;        //calculo numero aleatorio
    printf("la temperatura actual es: %d grados\n",valrandom);     //comprobacion del numero
    return valrandom;      //lo enviamos al main
}

int calcdelta(int s, int r, int *frio, int *calor)     //calcular el delta de temperatura actual y temperatura de consigna
{
    int z = (s - r);        //calculamos la diferencia

    if (z<0)        //si el setpoint es menor a la temperatura ambiente
    {
        z = (r - s);        //si sale negativo invertimos el calculo
        *frio = 1;       //necesitamos frio
    } 
    else if (z>0)       //si el setpoint es mayor a la temperatura ambiente
    {
        *calor = 1;      //necesitamos calor
    }       
    else        //si el setpoint es igual a la temperatura ambiente
    {
        *frio = 0;       //no necesitamos frio       
        *calor = 0;       //no necesitamos calor
    }
    if (z>10)       //si supera los 10
    {
        z=10;       //el delta no puede ser mayor a 10
    }        
    printf("el delta es de: %d\n",z);       //comprobamos el numero
    return z;       //lo enviamos al main
}
