#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

void servicioAsignacionDeRecursos(void);
void servicioDeManejoDeProcesos(void);
void servicoManejoDeErores(int status, const char *mensaje);
void servicioManejoDeArchivos(void);
void servicioDeContabilidad(void);

int main() {

  servicioAsignacionDeRecursos();
  servicioDeManejoDeProcesos();
  servicioManejoDeArchivos();
  servicioDeContabilidad();
  servicoManejoDeErores(1, "prueba de error");
}

void servicioAsignacionDeRecursos(void) {
  printf("Servcio de asigncion de memoria es la funcion 'malloc', esa funcion "
         "pide memoria al sistema operativo\n");
  sleep(2);
  int *arreglo = malloc(sizeof(int) * 10);
  free(arreglo);
}

void servicioDeManejoDeProcesos(void) {
  printf("Servcio de manejo de procesos lafuncion 'fork', crea un proceso "
         "nuevo.\n");
  int proceso_id = fork();

  if (proceso_id > 0) {
    printf("Soy el papa [id = %d]", proceso_id);
    sleep(2);
  } else {
    printf("Soy el hijo [id = %d]", proceso_id);
    sleep(2);
  }
}

void servicoManejoDeErores(int status, const char *mensaje) {

  printf("Servcio de manejo de error la funcion 'perror', produce un mensaje "
         "de error.\n");
  sleep(2);
  if (status > 0) {
    perror(mensaje);
  }
}

void servicioManejoDeArchivos(void) {

  printf("Servcio de manejo de archivos la funcion 'chmod', permite cambiar "
         "los permisos de accesos.\n");
  sleep(2);
  const char *nombreArchivo = "datos.txt";
  int status = chmod(nombreArchivo, S_IRUSR | S_IWUSR);
  servicoManejoDeErores(status, "Error al establecer permisos");
}

void servicioDeContabilidad(void) {
  printf("Servcio de manejo de contabilidad la funcion 'getrusage', permite "
         "ver la recursos usados.\n");
  sleep(2);
  struct rusage uso;
  int status = getrusage(RUSAGE_SELF, &uso);
  printf("Tiempo de CPU usado: %ld.%06ld segundos\n", uso.ru_utime.tv_sec,
         uso.ru_utime.tv_usec);
  servicoManejoDeErores(status, "Error al obtener recursos");
}
