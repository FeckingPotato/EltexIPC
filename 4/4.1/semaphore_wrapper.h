#pragma once

#define CUR_PROJ 41

int semGet(int proj_id);

void semLock(int semid);

void semUnlock(int semid);

void semDestroy(int semid);
