#include <stdio.h>

void banner(void);
void leDado(int *ptr);
char casa(int);
int peao(int c,int f,int map[8][8]);
int cav(int c,int f,int map[8][8]);
int bis(int c,int f,int map[8][8]);
int tor(int c,int f,int map[8][8]);
int rai(int c,int f,int map[8][8]);
int rei(int c,int f,int map[8][8]);
int vali(int c);
int est(int b);
int comp(int b,int est);

int main(void){
	int mesa[8][8] = {0};
	int f,c;
	char q;
	while(1){
		fil:
		printf("Informe a coluna (1 - 8) [nao use letras] :");
		scanf("%d",&c);
		if(c >=0 && c >= 9){
			puts("Erro : informe um numero de 1 a 8");
			goto fil;
		}
		col:
		printf("Informe a fileira (1 - 8) :");
		scanf("%d",&f);
		if(f >=0 && f >= 9){
			puts("Erro : informe um numero de 1 a 8");
			goto col;
		}
		printf("Digite a peça para casa %c%d\n",casa(c),f);
		banner();
		c--;
		f--;
		printf("Sua opção :");
		leDado(&mesa[c][f]);
		printf("Quer continuar [s/n] :");
		scanf("%c",&q);
		if(q == 'n') break;
	}	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(mesa[i][j] == 1 || mesa[i][j] == -1)
				printf("Total %d movimentos\n",peao(i, j, mesa));
			else if(mesa[i][j] == 2 || mesa[i][j] == -2)
				printf("Total %d movimentos\n",cav(i, j, mesa));
			else if(mesa[i][j] == 3 || mesa[i][j] == -3)
				printf("Total %d movimentos\n",bis(i, j, mesa));
			else if(mesa[i][j] == 4 || mesa[i][j] == -4)
				printf("Total %d movimentos\n",tor(i, j, mesa));
			else if(mesa[i][j] == 5 || mesa[i][j] == -5)
				printf("Total %d movimentos\n",rai(i, j, mesa));
		}
	}
}

void leDado(int *ptr){
	int dado;
	cima:
	scanf("%d",&dado);
	if(dado <= -7 || dado >= 7){
		printf("Dado invalido \n" );
		banner();
		goto cima;
	}
	*ptr = dado;
}

void banner(void){
	puts("- para negras + para brancas");
	puts("1 - para peao");
	puts("2 - para cavalo");
	puts("3 - para bispo");
	puts("4 - para torre");
	puts("5 - para rainha");
	puts("6 - para rei");
}

char casa(int b){
	return 96 + b;
}

int peao(int c,int f,int map[8][8]){
	char ca = casa(c+1);
	printf("Movimentos do peão em %c%d \n",ca,f+1);
	int sum=0;
	int estado = est(map[c][f]);
	if(estado==1){
		if(map[c][f+1] == 0){
			printf("\tPeao branco de %c%d para %c%d\n",ca,f+1,ca,f+2);
			sum++;
		}
		if(f == 1 && map[c][f+1] == 0 && map[c][f+2] == 0){
			printf("\tPeao branco de %c%d para %c%d\n",ca,f+1,ca,f+3);
			sum++;
		}
		
		if(f + 1 <= 7 && c  + 1 <= 7 && map[c+1][f+1] < 0){
			printf("\tPeao branco de %c%d captura %c%d\n",ca,f+1,ca+1,f+2);
			sum++;
		}
		if(f + 1 < 7 && c - 1 >= 0 && map[c-1][f+1] < 0){
			printf("\tPeao branco de %c%d captura %c%d\n",ca-1,f+1,ca+1,f+2);
			sum++;
		}
	}
	else{
		if(map[c][f-1] == 0){
			printf("\tPeao preto de %c%d para %c%d\n",ca,f+1,ca,f);
			sum++;
		}
		if(f == 6 && map[c][f-1] == 0 && map[c][f-2] == 0){
			printf("\tPeao preto de %c%d para %c%d\n",ca,f+1,ca,f+1-2);
			sum++;
		}
		if(f - 1 >= 0 && c - 1 >= 0 && map[c-1][f-1] > 0){
			printf("\tPeao preto de %c%d captura %c%d\n",ca,f+1,ca-1,f-2+1);
			sum++;
		}
		if(f - 1 < 7 && c + 1 >= 0 && map[c-1][f-1] > 0){
			printf("\tPeao preto de %c%d captura %c%d\n",ca,f+1,ca-1,f+2+1);
			sum++;
		}
	}
	return sum;
}

int cav(int c,int f,int map[8][8]){
	char ca = casa(c+1);
	printf("Movimentos do cavalo em %c%d \n",ca,f+1);
	int sum=0,aux;
	int estado = est(map[c][f]);
		for(int i=2;i>0;i--){
			if(i == 2) aux = 1;
			else aux = 2;
			c1:
			if(vali(c+i) && vali(f+aux) && comp(map[c+i][f+aux],estado)){
				printf("\tCavalo %c%d para %c%d\n",ca,f+1,ca+i,f+1+aux);
				sum++;
			}
			if(aux > 0){
				aux *= -1;
				 goto c1;
			}
		}
		for(int i=-2;i<=-1;i++){
			if(i == -2) aux = 1;
			else aux = 2;
			c2:
			if(vali(c+i) && vali(f+aux) && map[c+i][f+aux] <= 0){
				printf("\tCavalo %c%d para %c%d\n",ca,f+1,ca+i,f+1+aux);
				sum++;
			}
			if(aux > 0){
				aux *= -1;
				 goto c2;
			}
		}
	return sum;
}
int est(int b){
	if(b > 0) return 1;
	else return -1;
}

int vali(int c){
	if((c >= 0) && (c <= 7)) return 1;
	return 0;
}

int comp(int b,int est){
	if(est == 1) return b <= 0;
	else return b >= 0;
}

int bis(int c,int f,int map[8][8]){
	char ca = casa(c+1);
	printf("Movimentos do bispo em %c%d \n",ca,f+1);
	int sum=0, estado = est(map[c][f]);
	int i,j;
	for(i=c+1,j=f+1;i<= 7 && j<= 7;i++,j++){
		if(map[i][j] == 0){
			printf("\tBispo em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tBispo em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c,j=f;i>= 0 && j>= 0;i--,j--){
		if(map[i][j] == 0){
			printf("\tBispo em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tBispo em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
	}
	for(i=c-1,j=f+1;i>= 0 && j<= 7;i--,j++){
		if(map[i][j] == 0){
			printf("\tBispo em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tBispo em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c+1,j=f-1;i<= 7 && j>= 0;i++,j--){
		if(map[i][j] == 0){
			printf("\tBispo em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tBispo em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	
	return sum;
}

int tor(int c,int f,int map[8][8]){
	char ca = casa(c+1);
	printf("Movimentos da Torre em %c%d \n",ca,f+1);
	int sum=0, estado = est(map[c][f]);
	int i,j;
	for(i=c+1,j=f;i<=7;i++)	{
		if(map[i][j] == 0){
			printf("\tTorre em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tTorre em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c-1,j=f;i>=0;i--)	{
		if(map[i][j] == 0){
			printf("\tTorre em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tTorre em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c,j=f+1;j<=7;j++)	{
		if(map[i][j] == 0){
			printf("\tTorre em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tTorre em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c,j=f-1;j>=0;j--)	{
		if(map[i][j] == 0){
			printf("\tTorre em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tTorre em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	return sum;
}


int rai(int c,int f,int map[8][8]){
	char ca = casa(c+1);
	printf("Movimentos do rainha em %c%d \n",ca,f+1);
	int sum=0, estado = est(map[c][f]);
	int i,j;
	for(i=c+1,j=f;i<=7;i++)	{
		if(map[i][j] == 0){
			printf("\tRainha em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tRainha em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c-1,j=f;i>=0;i--)	{
		if(map[i][j] == 0){
			printf("\tRainha em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tRainha em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c,j=f+1;j<=7;j++)	{
		if(map[i][j] == 0){
			printf("\tRainha em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tRainha em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c,j=f-1;j>=0;j--)	{
		if(map[i][j] == 0){
			printf("\tRainha em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tRainha em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c+1,j=f+1;i<= 7 && j<= 7;i++,j++){
		if(map[i][j] == 0){
			printf("\tRainha em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tRainha em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c,j=f;i>= 0 && j>= 0;i--,j--){
		if(map[i][j] == 0){
			printf("\tRainha em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tRainha em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
	}
	for(i=c-1,j=f+1;i>= 0 && j<= 7;i--,j++){
		if(map[i][j] == 0){
			printf("\tRainha em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tRainha em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	for(i=c+1,j=f-1;i<= 7 && j>= 0;i++,j--){
		if(map[i][j] == 0){
			printf("\tRainha em %c%d para %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
		}
		else if(comp(map[i][j],estado)) {
			printf("\tRainha em %c%d captura %c%d\n",ca,f+1,casa(i+1),j+1);
			sum++;
			break;
		}
		else break;
	}
	
	return sum;
}
