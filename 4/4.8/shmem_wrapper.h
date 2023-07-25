#pragma once

#define CUR_PROJ 47

int shmGet(int proj_id, unsigned int size);

void *shmAttach(int shmid);

void shmDetach(void *shm);

void shmRemove(int shmid);
