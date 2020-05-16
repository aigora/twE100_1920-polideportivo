//Polideportivo base para empezar a poner todas las funciones

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMCLIENTES 50
#define NUMINTENTOS 4

typedef struct{
	char usuario[30];
	char contrasena[30];
} entrar;

typedef struct{
	char nombre[30];
	char apellidos[30];
	int edad;
}datos;

void Presentacion(void);
void FRegistro(entrar clientes[]);//Funcion para registrarte en nuestros ficheros
void iniciarsesion(int *exito);//Funcion para iniciar sesion
void intentos(int *limite);//Intentos para poder iniciar sesion, si se pasa del numero de intentos le saldra un mensaje diciendo que saldra del programa
char menu(void); //Funcion para mostrar el menu
void pedirdatos();

int main(){
	
	datos persona[NUMCLIENTES];
	entrar clientes[NUMCLIENTES]; //Inicializo la estructura en el main
	int sesion = 0;
	char opcion1;
	
	while(sesion == 0){ //Meto un bucle infinito hasta que haya iniciado sesion dandole el valor de sesion != 0 y asi se ira a otro bucle que sera el menu
		Presentacion();
		printf("\tPara registrarte o iniciar sesion seleccione: \n\n\t\tR -- Registrarse\n\n\t\tI -- Iniciar sesion\n");
		scanf("%c", &opcion1);
		
		switch(opcion1){
			case 'R':
			case 'r':
				FRegistro(clientes);
				printf("\n\nPor favor ahora inicie sesion...\n");
				iniciarsesion(&sesion);
				getchar();
				break;
			case 'I':
			case 'i':
				iniciarsesion(&sesion);
				getchar();
				break;	
			default:
				printf("\nOpcion no valida.\n\n");	
				getchar();
				break;
		}
	}
	while(sesion == 1){
		system("cls");
		switch(menu()){
			case 'A':
			case 'a':
				//Primer caso: Deporte y ejercicios recomendados
				/*el programa te pedira una serie de datos y despues te dira que deporte seria el ideal para ti. A continuación, te preguntaran
				 el tiempo que estarás inscrito y te realizaran el cobro con tarjeta de crédito, si no te gusta la recomendación o es muy caro
				  puedes salir y volver a hacer la inscripción tu mismo. En caso contrario tendrás la opción de salir del programa.*/
				break;
			case 'B':
			case 'b':
				pedirdatos();
				//Segundo caso: Inscripción
				/* el programa te da la opción de hacer tu propia inscripción seleccionando los deportes y ejercicios que quiera
				 el usuario realizar en el  polideportivo. Después de seleccionar todo, te piden el tiempo que deseas estar y te realizan
				  el cobro con una tarjeta de crédito, sino se introducen los 12 dígitos de la tarjeta, no será válida y tendrás que repetir el pago.
				   Una vez finalizado te daran la opcion de salir del programa. */
				break;
			case 'C':
			case 'c':
				//Tercer caso: Servidores 
				/*el programa te dejará acceder siempre y cuando seas administrador. En esta opción podrás observar cuantas personas
				 se han dado de alta en nuestros servidores y dar de baja a alguna pudiendo editar el fichero desde el programa.*/
				break;
			case 'S':
			case 's':
				printf("Esperemos volver a verle pronto...\n");
				return;
				break;
			default:
				printf("\nOpcion no valida\n\n");
				break;
		}
	}
	
	return 0;
	
	
}

void Presentacion(void){
	printf("ESTA ES LA PRESENTACION, EN EL FUTURO SERA MAS BONITA \nMARIANO Y LUIS\n\n");
}
void FRegistro(entrar clientes[]){//Meto el vector de estructuras en la funcion

	FILE *pf;
	pf = fopen("usuarios.txt","a");
	
	if (pf==NULL){
		printf("El fichero no se ha abierto correctamente...\n");
		return -1;
	}
	
	else{
		printf("Fichero abierto correctamente...\n");
		fflush(stdin);
		printf("\nBienvenido, aqui podra registrarse, por favor escriba el nombre de su usuario: ");
		gets(clientes[0].usuario);   
		printf("\nEscriba su contraseña: ");
		gets(clientes[0].contrasena); 
		
		fprintf(pf, "%s ; %s\n", clientes[0].usuario, clientes[0].contrasena);
		fclose(pf);
		printf("\n\nMuchas gracias por registrarse en nuestros servidores, espero que disfrutes de nuestros servicios...\n\n");
	}

}
void iniciarsesion(int *exito){
	
	entrar clientes[NUMCLIENTES]; //Inicializo el vector de estructuras en la funcion
	
	int i = 0, usuarios = 0, limite = 0;
	char usuario[20], contrasena[20];
	
	FILE*pf;
	pf = fopen("usuarios.txt", "r"); //Modo lectura 
	
	if(pf == NULL){
		printf("Lo siento pero no hay usuarios registrados...\nDebera volver al inicio y registrarse...\n\n");
		return -1;
	}
	else{
		while(fscanf(pf, "%s ; %s", clientes[0].usuario, clientes[0].contrasena) != EOF){ //Bucle para que lea el fichero que ya se habia creado en registro
			i++;//Para que vaya leyendo uno por uno...
			usuarios++;//Para saber cuantos usuarios hay registrados...
		}
		fclose(pf);
		getchar();
		printf("Hay registrados %d usuarios en nuestros ficheros...\n", usuarios);
		
		while(limite != NUMINTENTOS){
			printf("\nPor favor, introduzca su usuario y contrasena de menos de 20 caracteres cada uno.\n");
			printf("\n\tUsuario: ");
			gets(usuario);
			printf("\n\tContrasena: ");
			gets(contrasena);
			//Comprobacion de que estas en los ficheros
			for(i = 0; i<usuarios; i++){
				if(strcmp(usuario, clientes[i].usuario)==0 && strcmp(contrasena, clientes[i].contrasena)==0){
					printf("Perfecto acaba de iniciar sesion, muchas gracias disfrute de nuestros servicios..\n");
					*exito = 1;
					limite = NUMINTENTOS;
				}
			}
			if(limite != NUMINTENTOS){
				printf("Lo siento no esta registrado, vuelva a intentarlo...\n");
				limite++;
				printf("Le quedan %d intentos...\n", NUMINTENTOS-limite);
				if(limite == NUMINTENTOS){
					printf("Lo siento pero volvera al inicio...\n\n\n");
					getchar();
					system("cls");
				}
				
			}
		}
		
		
	}
	
}
char menu(void){
	char opcion;
	
	printf("\tBienvenido, seleccione uno de nuestros servicios disponibles: \n");
	printf("\n\t\tA -- Deporte y ejercicios recomendados\n");
	printf("\t\tB -- Inscripción\n");
	printf("\t\tC -- Servidores (Solo se puede acceder si eres administrador...)\n");
	printf("\t\tS -- Salir del programa \n");
	scanf("%c", &opcion);
	
	return opcion;
}
void pedirdatos(){//esta funcion crea un fichero donde pide y guadra los datos del usuario 
	datos persona[NUMCLIENTES];
	FILE *pf;
	pf = fopen("datos.txt","a");
	if (pf==NULL){
		printf("El fichero no se ha abierto correctamente...\n");
	}else{
		printf("necesitaremos algunos de sus datos:\nintroduzca su nombre\n");
		gets(datos.nombre); 
	//	scanf("%s",datos.nombre);
		printf("ahora, sus dos apellidos\n");
		gets(datos.apellidos); 
	//	scanf("%s",datos.apellidos);
		
		
		fclose(pf);
	}


}

	
	
