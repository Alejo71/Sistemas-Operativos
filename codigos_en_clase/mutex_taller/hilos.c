    sleep(1);
    for(i = 0; i <= p; i++)
    {
        printf("- ");
    }
    fflush(stdout);
    pthread_mutex_unlock(&mutex);
    //--->punto crítico 2, desbloquear el mutex
   return NULL;
}

int main()
{
    int error, i;
    char* valor_devuelto;
    pthread_mutex_init(&mutex,NULL);
    /* Variables para hilos */
    struct datos_tipo hilo_datos[NUM_HILOS];
    pthread_t idhilo[NUM_HILOS];

    for(i = 0; i < NUM_HILOS; i++){
        hilo_datos[i].dato = i;
 codigos_en_clase       hilo_datos[i].p = i + 1;
    }

    /* Se lanzan los hilos */
    for(i = 0; i < NUM_HILOS; i++){
        error = pthread_create(&idhilo[i], NULL, (void*) proceso, (void*) (&hilo_datos[i]));
        if (error != 0)
        {
            perror("No puedo crear hilo");
            exit(-1);
        }
    }

    /* Esperar a que terminen */
    for(i = 0; i < NUM_HILOS; i++){
        pthread_join(idhilo[i], (void**) &valor_devuelto);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

