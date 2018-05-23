fork

# HOW TO USE

```shell
make
./main
```

# RESULT

```
main pid: 8036
I am parent, pid: 8036 fork: 8037
I am parent, pid: 8036 fork: 8037
wait for child
I am child, pid: 8037 fork: 0
I am child, pid: 8037 fork: 0
I am child, pid: 8037 fork: 0
I am child, pid: 8037 fork: 0
I am child, pid: 8037 fork: 0
catch child, pid: 8037
child exit code is 37
```