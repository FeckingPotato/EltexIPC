#pragma once
#include <semaphore.h>

#define CUR_PROJ 46

sem_t * semGet(int proj_id);

void semLock(sem_t *sem);

void semUnlock(sem_t *sem);

int semValue(sem_t *sem);

void semDestroy(sem_t *sem);
