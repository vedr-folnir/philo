/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:52:44 by hlasota           #+#    #+#             */
/*   Updated: 2023/10/18 15:03:19 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Structure pour stocker l'ID du thread et le thread lui-même
struct ThreadData {
    pthread_t thread;
    long id;
    pthread_mutex_t mutex;
};
/*
void *threadRoutine(void *data) {
    struct ThreadData *threadData = (struct ThreadData *)data;

    // Verrouiller le mutex local pour synchroniser la sortie
    pthread_mutex_lock(&threadData->mutex);

    printf("Thread ID: %ld is good\n", threadData->id);

    // Déverrouiller le mutex local après utilisation
    pthread_mutex_unlock(&threadData->mutex);

    pthread_exit(NULL);
}*/

void *threadRoutine(void *data)
{
	struct ThreadData *threadData = (struct ThreadData *)data;


	pthread_mutex_lock(&threadData->mutex);
	printf(" %ld is eating\n", threadData->id);
	usleep(51 * 1000);
	pthread_mutex_unlock(&threadData->mutex);
	return (0);
}



void createThreads(struct ThreadData *threadData, int numThreads) {
    int i;

    i = 0;
    while (i < numThreads)
    {
        threadData[i].id = i + 1;
        pthread_mutex_init(&threadData[i].mutex, NULL); // Initialisation du mutex local
        int result = pthread_create(&threadData[i].thread, NULL, threadRoutine, &threadData[i]);
        if (result)
        {
            printf("Erreur lors de la création du thread %d\n", i);
            return;
        }
        i++;
    }
}

void joinThreads(struct ThreadData *threadData, int numThreads) {
    int i;

    i = 0;
    while (i < numThreads)
    {
        pthread_join(threadData[i].thread, NULL);
        pthread_mutex_destroy(&threadData[i].mutex); // Destruction du mutex local
        i++;
    }
}

int main(int argc, char const *argv[])
{
    int numThreads = atoi(argv[argc - 1]);

    struct ThreadData threadData[numThreads];
    createThreads(threadData, numThreads);
    joinThreads(threadData, numThreads);

    return 0;
}