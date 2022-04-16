/*
Engenharia de Computacao - 31 de marco de 2021
Semestre 7 - Computacao Grafica

Simulador de Rasterizador
*/

#ifdef _WIN64
void limpar() {
	system("CLS");
}
#endif

#ifdef linux
void limpar() {
	system("clear");
}
#endif

int buffer[tam][tam]; // buffer de quadro
int aleatorio = 0; // modo aleatorio (0/1)
int eixos = 1; // mostrar eixos (0/1)

void inicializar() { // zera o plano cartesiano
	for(int j = 0; j < tam; j++) {
		for(int i = 0; i < tam; i++) {
			if((j == meio || i == meio) && eixos == 1) {
				buffer[i][j] = 100;
			}
			else {
				buffer[i][j] = 0;
			}
		}
	}
}

void imprimir() { // imprime o plano cartesiano
	limpar();
	printf("\n");
	for(int j = tam - 1; j > 0; j--) {
		printf("  ");
		for(int i = 1; i < tam; i++) {
			printf("\e[%im" "  " "\e[0m", buffer[i][j]);
		}
		printf("\n");
	}
}

int atr(int x, int y, int valor) { // atribui uma cor ao ponto x, y
	if(abs(x) < meio && abs(y) < meio) {
		buffer[x + meio][y + meio] = valor;
	}
	else {
		//imprimir();
		//printf("ERRO NA FUNCAO ATR: tentou-se acessar (%i, %i)\n", x, y);
		//aguardar();
		return(1);
	}
	
	return(0);
}

int ler(char c[]) { // le uma coordenada do usuario
	int x;
	do {
		printf(" %s = ", c);
		scanf(" %i", &x);
	} while(x >= meio || x <= -meio);
	
	return(x);
}

int sn() { // le um sim ou nao do usuario
	char op;
	
	do {
		scanf(" %c", &op);
	} while(op != 's' && op != 'n');
	
	switch(op) {
		case 'n':
			return(0);
			
		case 's':
			return(1);
	}
	
	return(-1);
}

void aguardar() { // equivalente ao system("PAUSE") mas compativel com linux
	while(getchar() != '\n');
	ungetc('\n', stdin);
	
	getchar();
	
	while(getchar() != '\n');
	ungetc('\n', stdin);
}

int rc() { // gera e retorna uma cor aleatoria
	if(rand() % 2 == 0) {
		return(rand() % 6 + 41);
	}
	else {
		return(rand() % 6 + 101);
	}
}

int menu() { // imprime o menu e recebe a selecao do usuario
	char op;
	
	limpar();
	printf("\n               SIMULADOR DE RASTERIZACAO\n");
	printf("\n                        OPCOES\n\n");
	printf("\t1. Reta (Algoritmo DDA)\n");
	printf("\t2. Reta (Algoritmo de Bresenham)\n");
	if(aleatorio == 0) {
		printf("\t3. Polilinhas formando um poligono (DDA)\n");
		printf("\t4. Polilinhas formando um poligono (Bresenham)\n");
	}
	else {
		printf("\e[%im" "\t3. Polilinhas formando um poligono (DDA)\n" "\e[0m", 90);
		printf("\e[%im" "\t4. Polilinhas formando um poligono (Bresenham)\n" "\e[0m", 90);
	}
	printf("\t5. Tracado de circulo (Teorema de Pitagoras)\n");
	printf("\t6. Tracado de circulo (Sistema de Coordenadas Polares)\n");
	printf("\t7. Tracado de circulo (Algoritmo de Bresenham)\n");
	printf("\n\t8. Aleatorio: ");
	
	switch(aleatorio) {
		case 0:
			printf("\e[%im" "desativado" "\e[0m", 90);
			break;
			
		case 1:
			printf("ativado");
			break;
	}
	
	printf("\n\t9. Mostrar eixos: ");
	
	switch(eixos) {
		case 0:
			printf("\e[%im" "desativado" "\e[0m", 90);
			break;
			
		case 1:
			printf("ativado");
			break;
	}
	
	do {
		printf("\n\n >>> ");
		scanf(" %c", &op);
	} while(((op < '1' || op > '9') && (printf(" Opcao invalida."))) || ((op == '3' || op == '4') && aleatorio == 1 && printf(" Opcao indisponivel no modo aleatorio")));
	
	if(op == '8') {
		if(aleatorio == 0) {
			aleatorio = 1;
			op = menu();
		}
		else {
			aleatorio = 0;
			op = menu();
		}
	}
	
	else if(op == '9') {
		if(eixos == 0) {
			eixos = 1;
			inicializar();
			op = menu();
		}
		else {
			eixos = 0;
			inicializar();
			op = menu();
		}
	}
	
	while(getchar() != '\n');
	ungetc('\n', stdin);
	
	return(op);
}
