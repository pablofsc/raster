/*
Engenharia de Computacao - 31 de marco de 2021
Semestre 7 - Computacao Grafica

Simulador de Rasterizador
*/

void dda(int xa, int ya, int xb, int yb, int cor) { // reta DDA
	atr(xa, ya, cor);
	
	int passo;
	if(abs(xb - xa) >= abs(yb - ya)) {
		passo = abs(xb - xa);
	}
	else {
		passo = abs(yb - ya);
	}
	
	float incx = (float) (xb - xa)/passo;
	float incy = (float) (yb - ya)/passo;
	
	float plotx = xa, ploty = ya;
	
	while(round(plotx) != xb || round(ploty) != yb) {
		plotx += incx;
		ploty += incy;
				
		atr(round(plotx), round(ploty), cor);
	}
}

void bresenham(int xa, int ya, int xb, int yb, int cor) { // reta bresenham
	atr(xa, ya, cor);
	
	int varx;
	if(xb - xa < 0) 
		varx = -1;
	else 
		varx = 1;
	
	int vary;
	if(yb - ya < 0) 
		vary = -1;
	else 
		vary = 1;
	
	int err = abs(xa - xb) - abs(ya - yb);
	
	int saidax = xa, saiday = ya;
	while(saidax != xb || saiday != yb) {
		int err2 = err*2;
		
		if(err2 >= -abs(yb - ya)) {
			err += -abs(yb - ya);
			saidax += varx;
		}
		
		if(err2 <= abs(xb - xa)) {
			err += abs(xb - xa);
			saiday += vary;
		}
		
		atr(saidax, saiday, cor);
	}
}

void pol(int tipo) { // polilinhas dos dois tipos
	int q = 1, xa, xb, ya, yb;
	
	imprimir();
	
	printf("\n DADOS DO PONTO 1\n\n");
	
	xa = ler("x");
	ya = ler("y");
	
	atr(xa, ya, 101);
	
	int xv[256], yv[256];
	
	xv[0] = xa;
	yv[0] = ya;
	
	for(;;) {
		imprimir();
		printf("\n ");
		
		for(int i = 0; i < q; i++) {
			printf("(%i, %i) -> ", xv[i], yv[i]);
		}
		
		q++;
		printf("\n\n DADOS DO PONTO %i\n\n", q);
	
		xb = ler("x");
		yb = ler("y");
		
		switch(tipo) {
			case 1:
				dda(xa, ya, xb, yb, 7);
				imprimir();
				break;
			
			case 2:
				bresenham(xa, ya, xb, yb, 7);
				imprimir();
				break;
		}
		
		xv[q - 1] = xb;
		yv[q - 1] = yb;
		
		xa = xb;
		ya = yb;
		
		printf("\n ");
		for(int i = 0; i < q; i++) {
			printf("(%i, %i) -> ", xv[i], yv[i]);
		}
		
		printf("\n\n adicionar outro ponto? s/n >>> ");
		if(sn() == 0) break;
	}
	
	printf(" pressione qualquer tecla para voltar ao menu\n");
	aguardar();
}

void pit(int xc, int yc, int r, int cor) { // circunferencia por pitagoras
	int x, y;
	
	for(x = r; x >= -r; x--) {
		y = round(sqrt(r*r - x*x));
		
		atr(xc + x, yc + y, cor);
		atr(xc + x, yc - y, cor);
	}
	
	for(y = r; y >= -r; y--) {
		x = round(sqrt(r*r - y*y));
		
		atr(xc + x, yc + y, cor);
		atr(xc - x, yc + y, cor);
	}
}

void scp(int xc, int yc, int r, int cor) { // circunferencia por sistema de coordenadas polares
	int x, y;
	double a;
	
	for(a = 0; a <= 2*M_PI; a += M_PI/100) {
		x = round(r*cos(a));
		y = round(r*sin(a));
		
		atr(xc + x, yc + y, cor);
	}
}

void bresc(int xc, int yc, int r, int cor) { // circunferencia por bresenham
	int d = 3 - 2*r;
	int x = 0, y = r;
	
	atr(x + xc, y + yc, cor);
	atr(y + xc, x + yc, cor);
	atr(-y + xc, x + yc, cor);
	atr(-x + xc, y + yc, cor);
	atr(-x + xc, -y + yc, cor);
	atr(-y + xc, -x + yc, cor);
	atr(y + xc, -x + yc, cor);
	atr(x + xc, -y + yc, cor);
	
	while(x <= y) {
		if(d <= 0) {
			d = d + 4*x + 6;
		}
		else {
			d = d + 4*x - 4*y + 10;
			y -= 1;
		}
		
		x += 1;
		
		atr(x + xc, y + yc, cor);
		atr(y + xc, x + yc, cor);
		atr(-y + xc, x + yc, cor);
		atr(-x + xc, y + yc, cor);
		atr(-x + xc, -y + yc, cor);
		atr(-y + xc, -x + yc, cor);
		atr(y + xc, -x + yc, cor);
		atr(x + xc, -y + yc, cor);
	}
}
