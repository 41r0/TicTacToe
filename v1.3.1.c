#include <stdio.h>
#include <string.h>
#include <time.h>//time_tt
#include <stdlib.h>

int seed;//randomizer seed;
int response=0;
char wynik[3][3]; /* Tabela dostępna globalnie, by funkcje wincond, ruch oraz
printer mogły jej używać*/
char p1[20]; /*Nazwa pierwszego gracza */
char p2[20];/*Nazwa drugiego gracza */
char buffer[20];
char small_buffer[3];
typedef enum bool {false=0, true=1} bool;
	bool ruc=false;


void printer(void);
int ruch(char, bool);
int wincond(void);
int pvp(int choice);
int analyze();


int main()
{
	int choice;
printf("Chcesz zagrać przeciw komputerowi(1) czy przeciw człowiekowi(2)?(1/2)");
do{
	fgets(small_buffer, sizeof small_buffer, stdin);
	choice= strtol(small_buffer,NULL,10);
		pvp(choice);
}
while(choice!=1 && choice!=2);
return 0;
}



int pvp(int choice){
	time_t tt;//sprawdzamy czas od 01.01.1970
	int i,p;
int new_game=0;
	int input=0;
	int ai_move=0;
	while(new_game<1){
		seed = time(&tt);
		srand(seed); /* Zmienna bez określonej wartości przyjmuje losowe wartości*/
		if(choice==1)
		strncpy(p2,"Komputer", sizeof(p2)-1);
		for(i=0;i<3;i++){
			for(p=0;p<3;p++)
				wynik[i][p]='#';}
		printf("Cześć! Podaj swoje imię:\nImię:");
		fgets(p1, sizeof p1, stdin);
		p1[strcspn(p1, "\n")] = 0; /*Usuwa newline z stdin w p1*/
		if(choice==2){
		printf("%s, jak ma na imię Twój przeciwnik?\nImię:", p1);
		fgets(p2, sizeof p2, stdin);
		p2[strcspn(p2, "\n")] = 0;/*Usuwa newline z stdin w p2*/}
		printf("Oto plansza! Zapoznajcie się z nią.\n\n");
		printer();/*Pokaz planszę na ekranie - plansza to zwykła tablica, którą będziemy modyfikować*/
		if(seed%2==0){
			printf("Zaczyna %s!\n", p2);
			ruc=false;
		}/*Januszowo zrobiona funkcja random-jeśli zmienna, której nie nadaliśmy wartości
		jest parzysta to zaczyna p2*/
		else{
			printf("Zaczyna %s!\n", p1);
			ruc=true;/*W przeciwnym wypadku zaczyna p1. Zmieniamy ruc na wartość przeciwną
			ponieważ ruc definiuje aktualnie działającego gracza*/
		}
		for(i=0;i<9;i++)/*Można wykonać maksymalnie 9 ruchów by zapełnić planszę, dlatego i<9*/
		{
			if(choice==2){
			printf("%s, które pole chcesz zapełnić?\n", ruc==true?p1:p2);
			fgets(buffer, sizeof buffer, stdin);
			input= strtol(buffer,NULL,10);
			response = ruch(input, ruc);/*Przechowujemy odpowiedź funkcji ruch w zmiennej response*/
			while(response == 0) { /*Funkcja response zwraca 0 jeśli wprowadzono znak spoza dozwolonego zakresu.
				Prosimy wtedy zawodnika o powtórzenie jego ruchu.*/
				printf("Wprowadzono złą liczbę lub pole jest już zajęte!\n");
				fgets(buffer, sizeof buffer, stdin);
				input= strtol(buffer,NULL,10);
				response = ruch(input, ruc);}}
				else if(ruc==true && choice==1){
				printf("%s, które pole chcesz zapełnić?\n",p1);
				fgets(buffer, sizeof buffer, stdin);
				input= strtol(buffer,NULL,10);
				response = ruch(input, ruc);/*Przechowujemy odpowiedź funkcji ruch w zmiennej response*/
				while(response == 0) { /*Funkcja response zwraca 0 jeśli wprowadzono znak spoza dozwolonego zakresu.
					Prosimy wtedy zawodnika o powtórzenie jego ruchu.*/
					printf("Wprowadzono złą liczbę lub pole jest już zajęte!\n");
					fgets(buffer, sizeof buffer, stdin);
					input= strtol(buffer,NULL,10);
					response = ruch(input, ruc);}}
			else if(ruc==false){
				input=analyze();
				printf("Komputer wybrał pole %d!\n",input);
				response = ruch(input, ruc);/*Przechowujemy odpowiedź funkcji ruch w zmiennej response*/
				while(response == 0) { /*Funkcja response zwraca 0 jeśli wprowadzono znak spoza dozwolonego zakresu.
					Prosimy wtedy zawodnika o powtórzenie jego ruchu.*/
				input=analyze();
				response = ruch(input, ruc);}}
			printer();/*Pokaż planszę*/
			ruc = !ruc;/*Zmiana wartości ruc pozwala przeciwnikowi na ruch w następnej turze(następnym obrocie pętli)*/
			if(i>=4 && (wincond()==1 || wincond()==2)){
				printf("Wygrywa %s!\n", wincond()==1?p1:p2);
				break;
			}/*Wincond sprawdza warunek wygranej - jeśli któryś z graczy go spełni,
			zwraca identyfikator gracza i przerywa pętlę*/
		}
		if(wincond()==0 && i==8)
			printf("Remis!\n");/*Jeśli na końcu gry nikt nie wygrał, wyświetl odpowiedni komunikat*/

			printf("Czy chcesz zagrać jeszcze raz?(T/n)\n");
			fgets(small_buffer, sizeof small_buffer, stdin);
			small_buffer[strcspn(small_buffer, "\n")] = 0;
			if(small_buffer[0]=='T'||small_buffer[0]=='t'){
			continue;
			}
			if(small_buffer[0]=='N'||small_buffer[0]=='n'){
			new_game++;
			}
			else{return 0;}
}
return 0;

}

int ruch(char pole, bool gracz){
	int i,p;
	for(i=0;i<3;i++){
		for(p=0;p<3;p++){
			if(pole-1==i*3+p)
				if (wynik[i][p] == '#') {wynik[i][p] = (gracz) ? 'X' : 'O'; return 3; }
	/*Jeśli pole jest wolne(wartość elementu tablicy to "#"), to wstaw znak. W przeciwnym wypadku zwróć komunikat błędu.*/
}}
 return 0;
}

void printer(void)
{
	printf("%c %c %c\n%c %c %c\n%c %c %c \n \n", wynik[0][0], wynik[0][1], wynik[0][2],wynik[1][0], wynik[1][1], wynik[1][2], wynik[2][0], wynik[2][1], wynik[2][2]);
	/*Pokaż na ekranie wszystkie elementy tablicy w odpowiedniej kolejności*/
}
int wincond(){
	int i,p;
	for(i=0;i<3;i++){
		for(p=0;p<3;p++){
			if((wynik[i][p]=='X' && wynik[i][p+1]=='X' && wynik[i][p+2]=='X' && p==0) || (wynik[i][p]=='X' && wynik[i+1][p]=='X' && wynik[i+2][p]=='X')||
			(wynik[i][i]=='X' && wynik[i+1][i+1]=='X' && wynik[i+2][i+2]=='X') || (wynik[2][0]=='X' && wynik[1][1]=='X' && wynik[0][2]=='X')){
				return 1;
			}
			else if((wynik[i][p]=='O' && wynik[i][p+1]=='O' && wynik[i][p+2]=='O' && p==0) || (wynik[i][p]=='O' && wynik[i+1][p]=='O' && wynik[i+2][p]=='O')||
						(wynik[i][i]=='O' && wynik[i+1][i+1]=='O' && wynik[i+2][i+2]=='O') ||  (wynik[2][0]=='O' && wynik[1][1]=='O' && wynik[0][2]=='O')){
							return 2;
						}
		}			/*Sprawdza, czy odpowiednie pola są zajęte. Jeśli któryś z graczy zapełni
					3 pola wymagane do wygranej to funkcja zwróci odpowiednią wartość, W przeciwnym wypadku
					zwraca wartość 0, świadczącą o remisie.*/
	}
				return 0;
}
int analyze(){
	int i,p,pole,x,d;
	x=0;
	d=0;
	pole=0;
	for(i=0;i<3;i++){
		for(p=0;p<3;p++){
			if((wynik[i][p-2]=='O' && wynik[i][p-1]=='O' && wynik[i][p]=='#' && p==2)||(wynik[i][p+1]=='O' && wynik[i][p+2]=='O' && wynik[i][p]=='#' && p==0)
			||(wynik[i][p-1]=='O' && wynik[i][p+1]=='O' && wynik[i][p]=='#' && p==1) || (wynik[i+1][p]=='O' && wynik[i+2][p]=='O' && wynik[i][p]=='#' && i==0)
			|| (wynik[i-1][p]=='O' && wynik[i+1][p]=='O' && wynik[i][p]=='#' && i==1) || (wynik[i-1][p]=='O' && wynik[i-2][p]=='O' && wynik[i][p]=='#' && i==2)
			|| (wynik[i][i]=='#' && wynik[i+1][i+1]=='O' && wynik[i+2][i+2]=='O' && p==i)	|| (wynik[i][i]=='#' && wynik[i-1][i-1]=='O' && wynik[i-2][i-2]=='O' && p==i)
			|| (wynik[i][i]=='#' && wynik[i-1][i-1]=='O' && wynik[i+1][i+1]=='O' && p==i)	|| (wynik[i][p]=='#' && wynik[i-1][p+1]=='O' && wynik[i-2][p+2]=='O' && i==2 && p==0)
			|| (wynik[i][p]=='#' && wynik[i+1][p-1]=='O' && wynik[i-1][p+1]=='O' && i==1 && p==1) || (wynik[i][p]=='#' && wynik[i+1][p-1]=='O' && wynik[i+2][p-2]=='O' && i==0 && p==2)	){
				pole=i*3+p+1;
				return pole;}
			}}
		for(i=0;i<3;i++){
			for(p=0;p<3;p++){
				if((wynik[i][p-2]=='X' && wynik[i][p-1]=='X' && wynik[i][p]=='#' && p==2)||(wynik[i][p+1]=='X' && wynik[i][p+2]=='X' && wynik[i][p]=='#' && p==0)
				||(wynik[i][p-1]=='X' && wynik[i][p+1]=='X' && wynik[i][p]=='#' && p==1) || (wynik[i+1][p]=='X' && wynik[i+2][p]=='X' && wynik[i][p]=='#' && i==0)
				|| (wynik[i-1][p]=='X' && wynik[i+1][p]=='X' && wynik[i][p]=='#' && i==1) || (wynik[i-1][p]=='X' && wynik[i-2][p]=='X' && wynik[i][p]=='#' && i==2)
				|| (wynik[i][i]=='#' && wynik[i+1][i+1]=='X' && wynik[i+2][i+2]=='X' && p==i)	|| (wynik[i][i]=='#' && wynik[i-1][i-1]=='X' && wynik[i-2][i-2]=='X' && p==i)
				|| (wynik[i][i]=='#' && wynik[i-1][i-1]=='X' && wynik[i+1][i+1]=='X' && p==i)	|| (wynik[i][p]=='#' && wynik[i-1][p+1]=='X' && wynik[i-2][p+2]=='X' && i==2 && p==0)
				|| (wynik[i][p]=='#' && wynik[i+1][p-1]=='X' && wynik[i-1][p+1]=='X' && i==1 && p==1) || (wynik[i][p]=='#' && wynik[i+1][p-1]=='X' && wynik[i+2][p-2]=='X' && i==0 && p==2)	 	){
					pole=i*3+p+1;
					return pole;}}}
		if(wynik[1][1]=='#'){
				return 5;}

		for(i=0;i<3;i++){
			for(p=0;p<3;p++){
				if(wynik[i][p]=='#'){
					x=rand();
					d=rand();
					d=d%3;
					x=x%3;
					if(wynik[x][d]=='#')
						return (3*x+d+1);
							}
						}}}
