#ifndef LOCK_H
#define LOCK_H

extern const char* lock_name;

int lock(); 

void unlock(int fd);

#endif