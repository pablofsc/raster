/*
Engenharia de Computacao - 31 de marco de 2021
Semestre 7 - Computacao Grafica

Simulador de Rasterizador
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define M_PI 3.14159265358979323846

#define tam 50
#define meio 25

#include "impressor.h" // funcoes relacionadas a impressao na tela
#include "algoritmos.h" // algoritmos de rasterizacao

int main() {
	srand(time(NULL));
	
	char op;
	
	for(;;) {
		inicializar();
		op = menu(0);
		
		int a, b, c, d, q, v, l, r;
		
		if(aleatorio == 0) {
			switch(op) {
				case '1':
					printf("\n");
					a = ler("xa");
					b = ler("ya");
					printf("\n");
					c = ler("xb");
					d = ler("yb");
					
					dda(a, b, c, d, 7);
					break;
					
				case '2':
					printf("\n");
					a = ler("xa");
					b = ler("ya");
					printf("\n");
					c = ler("xb");
					d = ler("yb");
					
					bresenham(a, b, c, d, 7);
					break;
				
				case '3':
					pol(1);
					break;
				
				case '4':
					pol(2);
					break;
					
				case '5':
					printf("\n centro da circunferencia: \n");
					a = ler("x");
					b = ler("y");
					printf("\n raio da circunferencia: \n");
					r = ler("r");
					
					pit(a, b, r, 7);
					break;
					
				case '6':
					printf("\n centro da circunferencia: \n");
					a = ler("x");
					b = ler("y");
					printf("\n raio da circunferencia: \n");
					r = ler("r");
					
					scp(a, b, r, 7);
					break;
					
				case '7':
					printf("\n centro da circunferencia: \n");
					a = ler("x");
					b = ler("y");
					printf("\n raio da circunferencia: \n");
					r = ler("r");
					
					bresc(a, b, r, 7);
					break;
			}
		}
		else { // aleatorio ativado
			printf("\n quantidade de testes = ");
			scanf(" %i", &q);
			
			printf(" limpar quadro apos cada teste? s/n >>> ");
			l = sn();
			
			for(v = 1; v <= q; v++) {
				int a = rand() % 49 - 25;
			    int b = rand() % 49 - 25;
			    int c = rand() % 49 - 25;
			    int d = rand() % 49 - 25;
			    int r = rand() % 23 + 1;
				
				switch(op) {
					case '1':
						dda(a, b, c, d, rc());
						break;
						
					case '2':
						bresenham(a, b, c, d, rc());
						break;
											
					case '5':
						pit(a, b, r, rc());
						break;
						
					case '6':
						scp(a, b, r, rc());
						break;
						
					case '7':
						bresc(a, b, r, rc());
						break;
				}
				
				imprimir();
				printf("\n teste %i de %i\n", v, q);
				usleep(500000);
				
				if(l == 1) {
					inicializar();
				}
			}
		}
		
		if(aleatorio != 1 || l != 1) {
			imprimir();
			aguardar();
		}
	}
}
