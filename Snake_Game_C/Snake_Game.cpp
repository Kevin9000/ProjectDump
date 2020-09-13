#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#define MAP 16

/*info:
51=bordi mappa
50=cibo
>0=presenza del serpente(corpo)
0=spazio percorribile dal serpente
*/

//comando simile al clr ma più efficiente per vedere il perchè vada nella stringa 142
void gotoxy(short x,short y)
{
	//COORD è tipo particolare di struttura che consente solo 2 valori di tipo short al suo interno, che definiranno le coordinate della cella nel cmd
	COORD pos={x,y};
	//mette il cursore in una posizione definita nel cmd
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
int main()
{
	int mappa[MAP][MAP];
	int i,j;
	for(i=0;i<MAP;i++)
	{
		for(j=0;j<MAP;j++)
		{
			//bordi mappa (colonne/righe : 0-15)
			if(j==0 || j==(MAP-1) || i==0 || i==(MAP-1))
			{
				//51 sta per i bordi
				mappa[i][j]=51;
			}
			//spazio percorribile per serpente
			else
			{
				mappa[i][j]=0;
			}
		}
	}
	
	//serpente
	char testa='d';
	int lunghezza=5;
	//0=il serpente è in posizione orizzontale e può muoversi SOLO su o giù e viceversa con 1
	int direzione=1;
	//controlla l'ammissibilità della direzione inserita
	char supporto_direzione;
	
	//posizione spawn serpente
	int i1=1;
	int j1=1;
	
	//variabile di controllo presenza cibo
	int cibo=0;
	//inizializzazione generatore di posizioni casuali per spawning cibo
	srand((unsigned)time(NULL));
	
	//timer per segnare quanto tempo è trascorso
	int timer=0;
	float tick=0;
	//supporto per aumento di livello
	float tick1=0;
	
	//input: difficoltà (predefinito difficoltà 2 a velocitò 250ms)
	int difficolta=2;
	float velocita=250;
	
	//punteggio ottenuto
	int punteggio=0;
	//maggiore è la difficolta maggiore sarà il punteggio ottenuto mangiando ogni cibo
	float punti_multiplier=1;
	//maggiore è il livello maggiore sarà la velocita e il punteggio, il livello sale ogni 20s
	int livello=1;
	
	//input:variabile di supporto
	int scelta=0;
	int scelta1=0;
	int ciclo=0;
	
	while(ciclo==0)
	{
		//menu principale
		printf("Benvenuto sul gioco Snake\n\ncomandi principali:\n-per muoversi usare i classici comandi 'wasd'\n-per uscire dal gioco premere il tasto escape\n-inoltre ogni 20 secondi si salira di livello comportando aumento di velocita'e punteggio\n\nVi auguro buon Game\n\ndifficolta' impostata:%d\nVelocita'serpente: %.1fms\nMultiplier punteggio: %.1fx\n\n------------------------------------------\npremere il tasto:\n1 - per modificare la difficolta'\n2 - per giocare\n",difficolta,velocita,punti_multiplier);
	    scanf("%d",&scelta);
	    
	    //selezione della difficoltà
	    if(scelta==1)
    	{
    		scelta1=0;
    		while(scelta1==0)
    		{
    			printf("scegliere una delle seguenti difficolta':\n1-Facile:400ms , Multiplier 0.5x\n2-Normale:300ms , Multiplier 1x\n3-Difficile:200ms , Multiplier 2x\n4-Molto Difficile:100ms , Multiplier 4x\n");
    	    	scanf("%d",&scelta1);
    	    	switch(scelta1)
    	    	{
    	    		case 1:
    	    			difficolta=scelta1;
    	    			velocita=400;
    	    			punti_multiplier=0.5;
    	    	    	scelta1=1;
    	    			break;
    	    			
    	    		case 2:
    	    			difficolta=scelta1;
    	    			velocita=300;
    	    			punti_multiplier=1;
    	    	    	scelta1=1;
    	    			break;
    	    			
    	    		case 3:
    	    			difficolta=scelta1;
    	    			velocita=200;
    	    			punti_multiplier=2;
    	    	    	scelta1=1;
    	    			break;
    	    			
    	    		case 4:
    	    			difficolta=scelta1;
    	    			velocita=100;
    	    			punti_multiplier=4;
    	    	    	scelta1=1;
    	    			break;
    	    		//ripeti il ciclo
    	    		default:
    	    			printf("hai inserito una difficolta'non valida si prega di riprovare\n");
		    		    scelta1=0;
    	    			break;
				}
			}
    	}
    	if(scelta==2)
    	{
    		ciclo=1;
		}
		fflush(stdin);
		system("cls");
	}
	ciclo=0;
	while(ciclo==0)
	{
		//ho usato questo comando questa "funzione" che ho chiamato gotoxty va molto più fluido rispetto al clear e anche perchè ti accieca di meno, se vuole provare e diventare più miope provi lei stessa :-P
		//system("cls");
		//sovvrascrive le celle
		gotoxy(0,0);
		
		//se testa del serpente mangia del cibo
		if(mappa[i1][j1]==50)
		{
			lunghezza++;
			punteggio=punteggio+(1000*punti_multiplier*(livello*0.8));
			cibo--;
		}
		//se la testa del serpente si scontra contro il proprio corpo o bordi
		else if(mappa[i1][j1]>0)
		{
			ciclo=1;
		}
		//assegna un "timer" che indica per quanti "loop"/"turni" il blocco avrà la presenza del corpo del serpente
		mappa[i1][j1]=lunghezza;
		
		//spawning cibo
		while(cibo==0)
		{
			//posizione randomica da 1 a 14
			i=rand()%(MAP-2)+1;
			j=rand()%(MAP-2)+1;
			if(mappa[i][j]==0)
			{
				//50 = posizione del cibo
			    mappa[i][j]=50;
			    cibo++;
			}
		}
		//stampa la mappa
		for(i=0;i<MAP;i++)
    	{
    		for(j=0;j<MAP;j++)
    		{
    			//posizione cibo
    			if(mappa[i][j]==50)
    			{
    				printf("%2c",15);
				}
				//bordi mappa
				else if(mappa[i][j]==51)
				{
					printf("%2c",220);
				}
				//se >0 vuol dire che c'è la presenza del serpente
    			else if(mappa[i][j]>0)
    			{
    				if(mappa[i][j]==lunghezza)
    				{
    					printf("%2c",2);
					}
					else
					{
						printf("%2c",219);
					}
    				mappa[i][j]--;
				}
				//campo mappa
    			else
    			{
    				printf("%2c",45);
				}
    		}
    		if(i==0)
    		{
    			printf("    INDICE:");
			}
    		else if(i==1)
    		{
    			printf("    -Lunghezza: %d",lunghezza);
			}
			else if(i==2)
			{
				printf("    -Tempo trascorso: %ds",timer);
			}
			else if(i==3)
			{
				printf("    -Difficolta': %d (%.2fms)",difficolta,velocita);
			}
			else if(i==4)
			{
				printf("    -PUNTEGGIO: %d",punteggio);
			}
			else if(i==5)
			{
				printf("    -LIVELLO: %d",livello);
			}
			else if(i==6)
			{
				printf("    -Velocita: %.2fms",velocita);
			}
    		printf("\n");
    	}
    	printf("\npremere esc per uscire dalla pertita\n");
    	//blocca il ciclo di istruzioni per N secondi (dipende dal valore della variabile velocita)
    	Sleep(velocita);
    	
    	tick=tick+velocita;
    	tick1=tick1+velocita;
    	//al raggiungimento del secondo 
    	if(tick>1000)
    	{
    		timer++;
    		tick=tick-1000;
		}
		//al raggiungimento di 20 sec
    	if(tick1>20000)
    	{
    		livello++;
    		//aumento di velocità
    		velocita=velocita*0.90;
    		tick1=tick1-10000;
		}
    	//controllo se un tasto è stato premuto per cambiare direzione
    	if(kbhit())
    	{
    		//'mette'il tasto premuto nella variabile
    		supporto_direzione=getch();
    		//27 sta per il tasto escape
    		if(supporto_direzione==27)
    		{
    			testa=supporto_direzione;
			}
    		else if(direzione==0)
    		{
    			//controllo amissibilità della direzione inserita
    			if(supporto_direzione=='w' || supporto_direzione=='s')
    			{
    				testa=supporto_direzione;
				}
			}
			else if(direzione==1)
			{
				//controllo amissibilità della direzione inserita
				if(supporto_direzione=='a' || supporto_direzione=='d')
				{
					testa=supporto_direzione;
				}
			}
		}
		
    	switch(testa)
    	{
    		case 'a':
    			j1--;
    			direzione=0;	
    			break;
    		case 's':
    			i1++;
    			direzione=1;
    			break;
    		case 'd':
    			j1++;
    			direzione=0;
    			break;
    		case 'w':
    			i1--;
    			direzione=1;
    			break;
    		//per uscire dal gioco (tasto escape)
    		case 27:
    			ciclo=1;
    			break;
		}
	}
	printf("--------------------------------------\nPartita finita.\n\nCONGRATULAZIONI hai finito la partita con un punteggio di %d",punteggio);
	return 0;
}
