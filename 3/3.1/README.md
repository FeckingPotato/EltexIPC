# CMake projects:

- 3.1 - prints its internal counter, which increments every second, to stdout and log.txt, syntax:
  - ./3.1

# Signal tests

### SIGINT, SIGQUIT, SIGABRT, SIGKILL, SIGTERM

These signals cause the program to exit with the corresponding exit code

![sigint.png](img%2Fsigint.png)
![sigint.png](img%2Fsigquit.png)
![sigint.png](img%2Fsigabrt.png)
![sigint.png](img%2Fsigkill.png)
![sigint.png](img%2Fsigterm.png)

### SIGTSTP

Does nothing (called at the 5th and 10th sceonds)

![sigtstp.png](img%2Fsigtstp.png)

### SIGSTOP

Pauses the execution of the program

![sigstop.png](img%2Fsigstop.png)

### SIGCONT

Continues of the execution of the program paused by SIGSTOP

![sigcont.png](img%2Fsigcont.png)
