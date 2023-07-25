#pragma once

#define CUR_PROJ 47

int shmGet(int proj_id, unsigned int size);

void *shmAttach(int shmfd);

void shmDetach(void *shm);

void shmRemove(int shmfd);
