fcntl

# HOW TO USE

```shell
make build
./main & ./deamon &
```

# RESULT

```
[3] 29006
[5] 29007
main try to lock, start 20 end 40 type 3
main fcntl result 0
main lock success start 20 end 40 pid -1 type 3 whence 0
deamon try to lock, start 20 end 40 type 1
deamon fcntl result -1
deamon get lock failed start 20 end 40 pid -1 type 1 whence 0
[5]    29007 done       ./deamon
[3]    29006 done       ./main
```