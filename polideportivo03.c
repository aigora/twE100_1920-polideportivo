// polideportivo version 01

#include <stdio.h>
#include <string.h>

void fpresentacion();
void fregistro();
void fisesion();



int main(){
	fpresentacion();
	char ele;
	while(ele!='s' && ele!='S'){
		
		
	
		printf("\n\nque desea hacer?\n\nA.registrarse\nB.iniciar sesion\nS.salir\n");
		fflush(stdin);
		scanf("%c",&ele);
		printf("la opcion elegida es %c\n\n",ele);
		
		
		switch(ele){
			case 'a':
			case 'A':
				fregistro();
				break;
			
			case 'B':
			case 'b':
				fisesion();
				break;
			case 's':
			case 'S':
				printf("muchas gracias, saliendo....");
				break;
			
			default: 
			printf("eleccion no valida");
		}
	}
}

void fpresentacion(){
	printf("ESTA ES LA PRESENTACION, EN EL FUTURO SERA MAS BONITA \nMARIANO Y LUIS\n\n");
}
void fregistro(){
	char name[20];
	char c1[30],c2[30];
	int i,z;
	i=1;
	FILE *f;
	f=fopen("usuarios.txt","a");
	if (f==NULL){
		printf("no se ha podido abrir el fichero");
	}
	
	//pedida de nombre
	fflush(stdin);
	printf("escriba su nombre\n");
	scanf("%s",&name);
	fprintf(f,"%s ",name);
	printf("%s ha quedado registrado como nuevo nombre\n",name);
						
			while (i!=0){
			printf ("escribir una contrase\244a\n");
			fflush(stdin);
			fgets(c1,30,stdin);
			fflush(stdin);
			printf ("volver a escribir la contrase\244a\n");
			fgets(c2,30,stdin);
		
		
			//vamos a comparar las frases
			
			if (strcmp(c1,c2)==0){
			printf("contrase\244a correcta");
			i=0;
				
			}
			else{
			printf("\n\ncontrase\244a incorrecta, intentalo otra vez\n");
			}
				
			
			}

	fprintf(f,"%s",c1);
	
	fclose(f);
	
	
	
}
void fisesion(){
	
	char name[20],aux[20],pword[20],contra[20];
	int z=0;
	FILE *f;
	f=fopen("usuarios.txt","r");
	
	
	fflush(stdin);
	printf("escriba su nombre de usuario\n");
	scanf("%s",&name);
		while(!feof(f) && z==0){
			fscanf(f,"%s",&aux);
		//	printf("%s",aux);
			if(strcmp(name,aux)==0){
				z=1;
				fscanf(f,"%s",&pword);
				
			}
		}
		

	fclose(f);
		
	if(z==1){
		printf("el nombre esta registrado\nintroducir contrase\244a ");
		fflush(stdin);
		scanf("%s",&contra);
		
		if (strcmp(contra,pword)==0){
			printf("contrase\244a correcta");
				
			}
			else{
			printf("\n\ncontrase\244a incorrecta, intentalo otra vez\n");
			}
	}/*else{
		printf("el nombre no esta registrado\n\n1.volver a iniciar sesion \n2.crear un usuario");
		
	}*/
		


	
	
}
