file lock

# HOW TO USE

```shell
make build
./main & ./deamon &
```

# RESULT

```
[3] 29006
[5] 29007
A
A wait for lock
B
B get lock
A get lock
B finished
[5]    29007 done       ./deamon
A finished
[3]    29006 done       ./main
```