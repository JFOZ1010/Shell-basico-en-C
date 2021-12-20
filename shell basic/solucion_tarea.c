#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "leercadena.h"


int main(int argc, char *argv[]) {

  //instanciar vector de cadenas
  char *vector_command[argc];
  //instanciar varible del proceso
  pid_t pid;
 
   //verificar si se ingreso un comando
  if (argc == 1) {
  printf("Indique el comando que quiere que se ejecute!!!!\n");
  }
  else {
    //inicirar proceso hijo
    pid = fork();
 
    //verificar si se pudo crear el proceso y quien es
    if (pid < 0) {
      perror("No se pudo crear un proceso\n");
      exit(1);
    } else if (pid == 0) {

      //insertar comando en el vector
      for (int i = 0 ; i < (argc-1)  ; i++) {
      vector_command[i] = argv[i+1];    
      }
      //insertar el final del vector
      vector_command[argc-1] = NULL;
      
      //ejecutar el comando con execvp
      execvp(vector_command[0],vector_command);
      perror("Return from execlp() not expected");

      //limpiar memoria del vector
      free(vector_command);

      exit(EXIT_FAILURE);
    } else {
      //esperar al que hijo termine
      wait(NULL);
    }
 
  }
 
  return 0;
}

