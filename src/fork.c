#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {

  // crea un nuevo proceso
  int pid = fork();
  int var = 21;
  int status;

  if (pid > 0) {
    sleep(2);
    var = 7;
    printf("Soy el papa!! %d PROCESS ID = %d\n", var, pid);
    pid = wait(&status);
    printf("Soy el papa!! %d PROCESS ID = %d y regresa %d\n", var, pid, status);
  }else {
    printf("Soy el hijo!! %d -> PROCESS ID = %d\n", var, pid);

    // ejecuta un ejecutable
    status = execl("/bin/ls", "ls", "-l", (char*)0);
    sleep(2);
  }
  return 0;
}
