#include <windows.h>
#include <iostream>
#include <conio.h>

//codigo asic para utilizar la flechas del teclado para mover la nave
#define  IZQUIERDA 75
#define DERECHA 77

char avion_l1[]={' ',' ',' ', '*',' ',' ',' ',0};        
char avion_l2[]={' ',' ','*', '*','*',' ',' ',0};
char avion_l3[]={' ','*',' ', '*',' ','*',' ',0};

char explocion_l1[]={' ',' ','*','*',' ',' ',' ',0};      
char explocion_l2[]={' ','*','*','*','*',' ',' ',0};
char explocion_l3[]={' ',' ','*','*',' ',' ',' ',0};

char explocion_r1[]={'*',' ','*','*',' ','*',' ',0};       
char explocion_r2[]={' ','*','*','*','*',' ',' ',0};
char explocion_r3[]={'*',' ','*','*',' ','*',' ',0};

char borrar_avion[]={' ',' ',' ',' ',' ',' ',' ',0};

int Num_vidas=3;
int Corazones =3;

//Cordenadas de la nave
int ix = 40;
int iy = 19;

//cordenadas de los asteroides
int y = 8 , x = 12;
int yy = 12 , xx = 17;
int x1 = 58 , y1 = 6;
int x2 = 70 , y2 = 9;

int i,v;

//variables de la bala
int dd=0;
bool disparo = false;

//Variables para el cambio de nivel
int  repeticion = 0 , nivel = 1;
bool condicion = false;
int xb;

void gotoxy(int x , int y){
	
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X = x;
	dwPos.Y = y;
	
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);	
	SetConsoleCursorPosition(hCon, dwPos);
	
}

void vidas(int vi){
	
	gotoxy(2,1); printf("VIDAS %d", vi);
	
}

void Barra_salud(int n) {
	
	gotoxy(80,1); printf(" ");
	gotoxy(81,1); printf(" ");
	gotoxy(82,1); printf(" ");
	
	for(v = 0 ; v < n ; v++) {
		gotoxy(80+v,1); 
		printf("%c", 3);
	}
}

void Explocion(void) {
	
	gotoxy(ix,iy); puts(explocion_l1);
	gotoxy(ix,iy+1); puts(explocion_l2);
	gotoxy(ix,iy+2); puts(explocion_l3);
	
	Sleep(380);
	
	gotoxy(ix,iy); puts(explocion_r1);
	gotoxy(ix,iy+1); puts(explocion_r2);
	gotoxy(ix,iy+2); puts(explocion_r3);
		
	Sleep(380);
		
	gotoxy(ix,iy); puts(avion_l1);
	gotoxy(ix,iy+1); puts(avion_l2);
	gotoxy(ix,iy+2); puts(avion_l3);
}

void jugar(void){
	
		if(!disparo) xb = ix; 
		
		//pintar bala
		gotoxy(xb+3, iy + dd); printf("*");
	
		//rutina de los ateroides
		//do{
		gotoxy(x,y); printf("%c", 2);
		gotoxy(xx,yy); printf("%c", 2);
		gotoxy(x1,y1); printf("%c", 2);
		gotoxy(x2,y2); printf("%c", 2);
		
		Sleep(70);
		
		gotoxy(x,y); printf(" ");
		gotoxy(xx,yy); printf(" ");
		gotoxy(x1,y1); printf(" ");
		gotoxy(x2,y2); printf(" ");
		
		//rutina del disparo
		gotoxy(xb+3, iy + dd); printf(" "); //borrar bala
		if(disparo == true) dd--;
		if(iy + dd < 5){
			dd = 0;
			disparo = false;
		}
		
		//volver a los asteroides arriba cuando toquen el suelo
		if(y>20 || x == xb+3 && iy + dd <= y){
			y = 4;
			x = (rand() % 70 ) + 6;
			
			if (y == 4){
				condicion = false;
			}
			
		}
		
		if(yy>20 || xx == xb+3 && iy + dd <= yy){
			yy = 4;
			xx = (rand() % 70 ) + 6;
		}
		
		if(y1>20 || x1 == xb+3 && iy + dd <= y1){
			y1 = 4;
			x1 = (rand() % 70 ) + 6;
		}
		
		if(y2>20 || x2 == xb+3 && iy + dd <= y2){
			y2 = 4;
			x2 = (rand() % 70 ) + 6;
		}
		
		//rutina para mover el avion
		
		if(kbhit()){
			unsigned char tecla = getch();
			
			switch (tecla){
				case IZQUIERDA:
					if(ix > 4){
						gotoxy(ix,iy); puts(borrar_avion);
						gotoxy(ix,iy+1); puts(borrar_avion);
						gotoxy(ix,iy+2); puts(borrar_avion);
						
						ix -=2; // velocidad con la que se desplaza hacia la IZQUIERDA
						
						gotoxy(ix,iy); puts(avion_l1);
						gotoxy(ix,iy+1); puts(avion_l2);
						gotoxy(ix,iy+2); puts(avion_l3);
						
					}
					break;
				
				case DERECHA:
					if (ix < 70){
						gotoxy(ix,iy); puts(borrar_avion);
						gotoxy(ix,iy+1); puts(borrar_avion);
						gotoxy(ix,iy+2); puts(borrar_avion);
						
						ix +=2; // velocidad con la que se desplaza hacia la derecha
						
						gotoxy(ix,iy); puts(avion_l1);
						gotoxy(ix,iy+1); puts(avion_l2);
						gotoxy(ix,iy+2); puts(avion_l3);
						
					}
					break;
					
				case 'd': 
				disparo = true;
					break;
					
			} //fin del sqitch
			
		} //fin del if de tocar tecla
		
		//rutina de la colision
		if((x > ix && x <ix + 6 && y == iy-1) || (xx > ix && xx <ix + 6 && yy == iy-1)
		 || (x1 > ix && x1 <ix + 6 && y1 == iy-1) || (x2 > ix && x2 <ix + 6 && y2 == iy-1)) {
		 
		 	Corazones --;
		 	Barra_salud(Corazones);
		 	printf("\a");
		 	
		 }
		 
		gotoxy(ix,iy); puts(avion_l1);
		gotoxy(ix,iy+1); puts(avion_l2);
		gotoxy(ix,iy+2); puts(avion_l3);
		
		if(!Corazones){
			Num_vidas--;
			vidas(Num_vidas);
			Explocion();
			Corazones = 3;
			
			Barra_salud(Corazones);
		}
		
		//Rutina cambio de nivel
		if(!condicion) {
			repeticion ++;
			condicion = true;
		}
		if(repeticion == 100)  // cantidad de veces que tocan los asteroides el piso antes de subir de nivel
		{
			nivel++;
			gotoxy(35, 1); printf("NIVEL %i",nivel);
			
			gotoxy(ix, iy); puts(borrar_avion);
			gotoxy(ix, iy+1); puts(borrar_avion);
			gotoxy(ix, iy+2); puts(borrar_avion);
			
			iy -=2;
			
			gotoxy(ix, iy); puts(avion_l1);
			gotoxy(ix, iy+1); puts(avion_l2);
			gotoxy(ix, iy+2); puts(avion_l3);
			
			repeticion = 0;
						
									
		}
		
		//Velocidad de los asteroides
		y++;
		yy++;
		y1++;
		y2++; //}while(1);
		
				
}


int main (){
	
	vidas(Num_vidas);
	Barra_salud(Corazones);
	gotoxy(35,1); printf("NIVEL %i", nivel);
	
	gotoxy(ix,iy); puts(avion_l1);
	gotoxy(ix,iy+1); puts(avion_l2);
	gotoxy(ix,iy+2); puts(avion_l3);

	while(Num_vidas > 0 && nivel <= 6)
	{jugar();}
	
	
	Sleep(200);
	gotoxy(20,15); printf("GAME OVER");
	
	getch();
	return 0;
	
}







