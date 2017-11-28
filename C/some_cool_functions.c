

int DamePosicion ( char nombre[20] , TlistaConectados *lista)
//Retorna -1 si no esta
{
int encontrat = 0;
int i=0;
    while ( encontrado == 0 && i<lista.num)
    {
        if (strcmp(lista[i].nombre,nombre)!=0){i++;}
        
        else {encontrado =1;}    
}
    if (encontrado=1){return i;}
    else {return -1;}


 int AñadeConectados (TlistaConectados *lista , char nuevos[100])
{
    // n,nombre,s1,nombre2,s2,nombren,sn
    
    char *p = strtok( nuevos, ",");
    int n = atoi(p);
    char nombre;
    int socket;
    int resultado;
    
    for (int i = 0 ; i<n ; i++)
    {
        p = strtok(NULL, ",");
        strcpy (nombre, p);
        p = strtok(NULL, ",");
        socket = atoi (p);
        
        resultado = AñadeConectado (nombre,socket);
         
         if (resultado==-1){printf("No xuta");
         returb -1;}
         else { printf("Se ha añadido a %s",nombre);}
    }
    return 0
    
}








int EliminaConectado ( char nombre[20] , TlistaConectados *lista)
{
    int p = DamePosicion (nombre , lista);
    
    if (p == -1) {return -1}
    else
    {
        int i;
        for (i=p ; i<lista.num-1 ; i++)
        {
            lista->conectado[i].socket = lista->conectado[i+1].socket;
            strcpy(lista->conectado[i].nombre,lista->conectado[i+1].nombre);
            lista->num=lista->num-1;
        }
        return 0;
    }
}



void DameConectados (Tlistaconectados *lista , char resultado[100])
{
    int i;
    sprintf(resultado, "%d,",lista->num);
    
    for (i=0 ; i<lista->num ; i++)
    {
        sprintf (resultado, "%s%s, ", resultado , lista->conectados[i.nombre])
    }
}


