#ifndef LOCK_H
#define LOCK_H

extern const char* lock_name;

int lock(); 

void unlock(int fd);

int lock_p();

void unlock_p(int fd);

#endif