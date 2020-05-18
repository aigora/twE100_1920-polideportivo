//Polideportivo base para empezar a poner todas las funciones

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMCLIENTES 50 //Tamaño para la capacidad del vector de estructuras de clientes que se registren
#define NUMINTENTOS 4 //Intentos-1 para iniciar sesion
#define TAM 40 //Tamaño para los vectores
#define TAMTARJETA 13
#define TAMDNI 10

typedef struct{
	char usuario[TAM];
	char contrasena[TAM];
} entrar;

typedef struct{
	char tipo[TAM];
	float precio;
	int numero;
}sport;

typedef struct{
	char nombre[TAM];
	char apellidos[TAM];
	int edad;
	float altura;
	int vida;//Para saber si la persona que se registra ha tenido una vida sedentaria o activa
	char sexo[TAM];
}datos;


void Presentacion(void);
void FRegistro(entrar clientes[]);//Funcion para registrarte en nuestros ficheros
void iniciarsesion(int *exito);//Funcion para iniciar sesion
char menu(void); //Funcion para mostrar el menu
void pedirdatos(void);
void MostrarSports(char nombrefichero[], sport vector[], int *ndepor);
void PagoTarjeta(float *pagofinal);

int main(){
	
	datos persona;
	sport deporte[TAM];
	entrar clientes[NUMCLIENTES]; //Inicializo la estructura en el main
	sport carrito[TAM];
	
	int sesion = 0, confirmacion = 1;
	char opcion1;

	
	while(sesion == 0){ //Meto un bucle infinito hasta que haya iniciado sesion dandole el valor de sesion != 0 y asi se ira a otro bucle que sera el menu
		Presentacion();
		system("cls");
		printf("\n\n\tPara registrarte o iniciar sesion seleccione: \n\n\t\tR -- Registrarse\n\n\t\tI -- Iniciar sesion\n");
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
				pedirdatos();
				// Inscripción:
				/* el programa te da la opción de hacer tu propia inscripción seleccionando los deportes y ejercicios que quiera
				 el usuario realizar en el  polideportivo. Después de seleccionar todo, te piden el tiempo que deseas estar y te realizan
				  el cobro con una tarjeta de crédito, sino se introducen los 12 dígitos de la tarjeta, no será válida y tendrás que repetir el pago.
				   Una vez finalizado te daran la opcion de salir del programa. */
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
	printf("\n\n\n\t\t\t\t***BIENVENIDO AL MEJOR POLIDEPORTIVO DE LA HISTORIA***\n\n\n");
	printf("\tEn este programa se podra dar de alta en nuestro polideportivo, apuntandose a cualquier tipo de deporte\n" 
	"\tindividual, o de equipo, aunque si lo prefiere, se puede apuntar a nuestro prestigioso gimnasio \n\tuna vez se haya registrado e iniciado sesion...\n\n");
	printf("\n\n\t\t\t\t\tESPERAMOS QUE SEA DE SU AGRADO :)\n\n");
	printf("\n\n\n\n\nPrograma realizado por: MARIANO JIMENEZ BOHORQUEZ Y LUIS HERNANDEZ OSORO\n\n");
	getchar();
	
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
	char usuario[TAM], contrasena[TAM];
	
	FILE*pf;
	pf = fopen("usuarios.txt", "r"); //Modo lectura 
	
	if(pf == NULL){
		printf("Lo siento pero no hay usuarios registrados...\nDebera volver al inicio y registrarse...\n\n");
		getchar();
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
		fflush(stdin);
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
	printf("\n\t\tA -- Inscripción\n");
	printf("\t\tS -- Salir del programa \n");
	scanf("%c", &opcion);
	
	return opcion;
}
void pedirdatos(void){//esta funcion crea un fichero donde pide y guadra los datos del usuario 

	datos persona;
	sport carrito[TAM];
	sport deporte[TAM];
	
	char nfichero[TAM];
	int confirmacion, opcion2;
	int nelemento, ndepor, opcion;
	int i;
	float pagofinal;
	
	fflush(stdin);
	printf("\nEscribe el nombre del fichero con el que se te guardaran los datos de la siguiente forma : luis_hernandez.txt\n");
	gets(nfichero); 
	
	FILE *pf;
	pf = fopen(nfichero,"w");
	if (pf==NULL){
		printf("El fichero no se ha abierto correctamente...\n");
		return -1;
	}
	else{
		
		do{
			printf("\nNecesitaremos algunos de sus datos...(Presione si es necesario una tecla para continuar)");
			getchar();
			printf("\n\nIntroduzca su nombre: ");
			gets(persona.nombre); 
			fflush(stdin);
			printf("\nAhora, sus dos apellidos: ");
			gets(persona.apellidos);
			fflush(stdin);
			printf("\nAhora su edad: ");
			scanf("%d",&persona.edad);
			fflush(stdin);
			printf("\nIntroduzca su altura en metros: ");
			scanf("%f", &persona.altura);
			fflush(stdin);
			printf("\nIntroduzca su estilo de vida, si ha tenido una vida sedentaria pulse (1) en caso contrario (2): ");
			scanf("%d", &persona.vida);
			fflush(stdin);
			printf("\nIntroduzca su sexo: ");
			gets(persona.sexo);
			fflush(stdin);
			printf("\nY por último introduzca que deporte desea practicar: ");
			printf("\n\t\t\t1 -- Deportes de individuales(gimnasio incluido)\n\t\t\t2 -- Deportes de equipo\n");
			scanf("%d", &opcion2);
			fflush(stdin);
			//Enseñar deportes con MostrarSports
			switch(opcion2){
				case 1:
					
					while(1){
						system("cls");
						MostrarSports("deportes_individuales.txt", carrito, &ndepor);
						printf("\n\nIntroduzca el numero del deporte que desea: ");
						scanf("%d", &nelemento);
						fflush(stdin);
						if (nelemento > ndepor || nelemento < 1) {
							printf("Opcion no valida.\n");
							getchar();
						}
						else {
							fflush(stdin);
							deporte[0].numero = nelemento;
							strcpy(deporte[0].tipo, carrito[nelemento-1].tipo);
							deporte[0].precio = carrito[nelemento-1].precio;
							
							printf("\nHa seleccionado: ");
							printf("%d -- %s = %.2f\n\n", deporte[0].numero, deporte[0].tipo, deporte[0].precio);
						}
						break;
					}
					break;
				case 2:
					while(1){
						system("cls");
						MostrarSports("deportes_equipo.txt", carrito, &ndepor);
						printf("\n\nIntroduzca el numero del deporte que desea: ");
						scanf("%d", &nelemento);
						
						if (nelemento > ndepor || nelemento < 1) {
							printf("Opcion no valida.\n");
							system("pause");
						}
						else {
							deporte[0].numero = nelemento;
							strcpy(deporte[0].tipo, carrito[nelemento - 1].tipo);
							deporte[0].precio = carrito[nelemento - 1].precio;
							
							printf("\nHa seleccionado: ");
							printf("%d -- %s = %.2f\n\n", deporte[0].numero, deporte[0].tipo, deporte[0].precio);
						}
						break;
					}
					break;
				default:
					printf("Opcion no valida...\n");
					break;
			}
			
			
			fprintf(pf, "Nombre: %s \nApellidos: %s \nEdad: %d \nAltura: %.2f \nVida(1,sedentaria; 2,activa): %d \nSexo: %s \nDeporte: %d -- %s = %.2f ", 
			persona.nombre, persona.apellidos, persona.edad, persona.altura, persona.vida, persona.sexo, deporte[0].numero, 
			deporte[0].tipo, deporte[0].precio);
			fclose(pf);
			
			getchar();	
			system("cls");
			printf("\n\nLos datos han quedado guardados de la siguiente manera:\n");
			printf( "\n\n\tNombre:%s\n\tApellidos:%s\n\tEdad:%d\n\tAltura: %.2f\n\tVida(1,sedentaria; 2,activa): %d\n\tSexo: %s\n\tDeporte: %d -- %s = %.2f\n", 
			persona.nombre,persona.apellidos,persona.edad, persona.altura, persona.vida, persona.sexo, deporte[0].numero, 
			deporte[0].tipo, deporte[0].precio);
			
			printf("\nSi esta de acuerdo con los datos, pulse el numero 0, en caso contrario pulsa cualquier otro numero: ");
			scanf("%d", &confirmacion);
			
		}while(confirmacion != 0 );
		getchar();
		
		pagofinal = deporte[0].precio;
		printf("\n\n****AHORA SE LE REALIZARA EL COBRO CON TARJETA****\n\n");
		PagoTarjeta(&pagofinal);
	}
}
void MostrarSports(char nombrefichero[], sport vector[], int *ndatos){
	
	int i = 0;
	
	FILE*pf;
	
	pf=fopen(nombrefichero, "r");
	
	if (pf==NULL){
		printf("El fichero no se ha abierto correctamente...\n");
		return -1;
	}
	else{
		printf("\t\t\t**ESTOS SON LOS DEPORTES DISPONIBLES JUNTO A SUS RESPECTIVOS PRECIOS**\n\n");
		while(fscanf(pf, "%d%s%f", &vector[i].numero, vector[i].tipo, &vector[i].precio)!=EOF){
			printf("\t%d -- %s = %.2f \n", vector[i].numero, vector[i].tipo, vector[i].precio);
			i++;
		}
		fclose(pf);
		*ndatos = i;
	}
	
}
void PagoTarjeta(float *pagofinal){
	
	datos persona;
	sport deporte[TAM];
	sport carrito[TAM];
	
	int ncarrito;
	
//	sport individuales[TAM];
//	sport colectivo[TAM];
	
	int tarjeta[TAMTARJETA];
	char opcion;
	int  longitud, confirmacion;
	do{
		//CargarFichero("deportes_individuales.txt", individuales);
		//CargarFichero("deportes_equipo.txt", colectivo);
		
		printf("\n\t Por favor, introduzca el numero de su tarjeta de credito: \n");
		scanf("%s", tarjeta, TAMTARJETA);
		fflush(stdin);
		longitud = strlen(tarjeta);//medimos la longitud para que cumpla que es una tarjeta de credito con 12 numeros
		printf("Esta tarjeta tiene %d caracteres\n", longitud);
		if(longitud == 12){
			printf("\nEl numero de su tarjeta es: %s \n", tarjeta, TAMTARJETA);
			printf("Se le realizara el cobro de %.2f al mes...\n", *pagofinal);
			getchar();
			return;
			
		}
		else{
			printf("Lo siento, pero no se ha podido reconocer la tarjeta. Intentelo de nuevo...\n");
			getchar();
		}
	}while(confirmacion != 1);
}

