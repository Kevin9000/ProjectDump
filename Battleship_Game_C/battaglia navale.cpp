// Programmare "battaglia navale".
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAP 11
//1 sta per dimensione
#define NAVI1 5
#define NAVI2 3
#define NAVI3 2

/*info generali:
0=quadrato che non è stato ancora colpito
1=colpo andato a vuoto
2=posizione delle navi
3=colpito
*/

struct alfabeto
{
	int posizione;
	char lettera;
};

int main()
{
	system("color 0c");
	
	int mappa[MAP][MAP];
	alfabeto lettere[MAP];
	int mappa1[MAP][MAP];
	
	//input:variabili di supporto per riempimento riga lettere
	int cont=0;
	char riempimento_lettere='a';
	
	//riempimento riga lettere
	while(cont<MAP)
	{
		//il primo quadrato della mappa è vuoto
		if(cont==0)
	    {
	    	//in codice ascii 0 vale quadrato vuoto
	    	lettere[cont].lettera=0;
		}
		else
		{
			lettere[cont].posizione=cont;
	    	lettere[cont].lettera=riempimento_lettere;
	    	riempimento_lettere++;
		}
		cont++;
	}
	
	int i,j;
	cont=0;
	int cont1=0;
	
	//riempimento mappa
    for(i=0;i<MAP;i++)
	{
		for(j=0;j<MAP;j++)
		{
			//riempimento riga orizzontale
			if(i==0)
			{
				mappa[i][j]=cont;
				mappa1[i][j]=cont;
				cont++;
			}
			//riempimento riga verticale
			if(j==0)
			{
				mappa[i][j]=cont1;
				mappa1[i][j]=cont1;
				cont1++;
			}
			if(i!=0 && j!=0)
			{
				//spazi disponibili per navi
				mappa[i][j]=0;
				mappa1[i][j]=0;
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	//spawning navi
	
	srand((unsigned)time(NULL));
	//controllo che non ci siano più navi nello stesso quadrato
	int sovrapposizione=0;
	//supporto variabile per scelta randomica orizzontale o verticale
	int direzione;
	
	//posizionamento navi di dim 3
	int sottomarini=NAVI3;
	
	for(cont=0;cont<sottomarini;cont++)
	{
		sovrapposizione=0;
		while(sovrapposizione==0)
		{
			i=rand()%9+1;
    		j=rand()%9+1;
    		//posizione nella prima mappa
	    	if(mappa[i][j]==0)
	    	{
	    		direzione=rand()%2+1;
	    		//-1 per orizzontale
	    		if(direzione==1)
	    		{
	    			j++;
	    			if(mappa[i][j]==0)
	    			{
	    				j++;
	    				if(mappa[i][j]==0)
	    				{
	    					mappa[i][j]=5;
	    		    		j--;
	    			    	mappa[i][j]=5;
	    			    	j--;
	    			    	mappa[i][j]=5;
	    	            	sovrapposizione=1;
						}
					}
				}
	    		//-2 per verticale
	    		if(direzione==2)
	    		{
	    			i++;
	    			if(mappa[i][j]==0)
	    			{
	    				i++;
	    				if(mappa[i][j]==0)
	    				{
	    					mappa[i][j]=5;
	    		    		i--;
	    			    	mappa[i][j]=5;
	    			    	i--;
	    			    	mappa[i][j]=5;
	    	            	sovrapposizione=1;
						}
					}
				}	
			}
		}
		while(sovrapposizione==1)
		{
			i=rand()%9+1;
    		j=rand()%9+1;
    		//posizione nella prima mappa
	    	if(mappa1[i][j]==0)
	    	{
	    		direzione=rand()%2+1;
	    		//-1 per orizzontale
	    		if(direzione==1)
	    		{
	    			j++;
	    			if(mappa1[i][j]==0)
	    			{
	    				j++;
	    				if(mappa1[i][j]==0)
	    				{
	    					mappa1[i][j]=5;
	    		    		j--;
	    			    	mappa1[i][j]=5;
	    			    	j--;
	    			    	mappa1[i][j]=5;
	    	            	sovrapposizione=2;
						}
					}
				}
	    		//-2 per verticale
	    		if(direzione==2)
	    		{
	    			i++;
	    			if(mappa1[i][j]==0)
	    			{
	    				i++;
	    				if(mappa1[i][j]==0)
	    				{
	    					mappa1[i][j]=5;
	    		    		i--;
	    			    	mappa1[i][j]=5;
	    			    	i--;
	    			    	mappa1[i][j]=5;
	    	            	sovrapposizione=2;
						}
					}
				}	
			}
		}
	}
	
	//posizionamento navi di dim 2
	int incrociatori=NAVI2;
	for(cont=0;cont<incrociatori;cont++)
	{
		sovrapposizione=0;
		while(sovrapposizione==0)
		{
			i=rand()%9+1;
    		j=rand()%9+1;
    		//posizione nella prima mappa
	    	if(mappa[i][j]==0)
	    	{
	    		direzione=rand()%2+1;
	    		//-1 per orizzontale
	    		if(direzione==1)
	    		{
	    			j++;
	    			if(mappa[i][j]==0)
	    			{
	    				mappa[i][j]=4;
	    				j--;
	    				mappa[i][j]=4;
	    	        	sovrapposizione=1;
					}
				}
	    		//-2 per verticale
	    		if(direzione==2)
	    		{
	    			i++;
	    			if(mappa[i][j]==0)
	    			{
	    				mappa[i][j]=4;
	    				i--;
	    				mappa[i][j]=4;
	    	        	sovrapposizione=1;
					}
				}	
			}
		}
		while(sovrapposizione==1)
		{
			i=rand()%9+1;
    		j=rand()%9+1;
    		//posizione nella prima mappa
	    	if(mappa1[i][j]==0)
	    	{
	    		direzione=rand()%2+1;
	    		//-1 per orizzontale
	    		if(direzione==1)
	    		{
	    			j++;
	    			if(mappa1[i][j]==0)
	    			{
	    				mappa1[i][j]=4;
	    				j--;
	    				mappa1[i][j]=4;
	    	        	sovrapposizione=0;
					}
				}
	    		//-2 per verticale
	    		if(direzione==2)
	    		{
	    			i++;
	    			if(mappa1[i][j]==0)
	    			{
	    				mappa1[i][j]=4;
	    				i--;
	    				mappa1[i][j]=4;
	    	        	sovrapposizione=0;
					}
				}	
			}
		}
	}
	
	//posizionamento navi di dim 1
	int cacciatorpediniere=NAVI1;
	for(cont=0;cont<cacciatorpediniere;cont++)
	{
		sovrapposizione=0;
		while(sovrapposizione==0)
		{
			i=rand()%9+1;
    		j=rand()%9+1;
    		//posizione nella prima mappa
	    	if(mappa[i][j]==0)
	    	{
	    		mappa[i][j]=2;
	    		sovrapposizione=1;
			}
		}
		while(sovrapposizione==1)
		{
			i=rand()%9+1;
    		j=rand()%9+1;
    		//posizione nella seconda mappa
	    	if(mappa1[i][j]==0)
	    	{
	    		mappa1[i][j]=2;
	    		sovrapposizione=0;
			}
		}
	}
	//mappa
	int navi_tot;
	navi_tot=cacciatorpediniere+incrociatori+sottomarini;
	//mappa 1
	int navi_tot1=navi_tot;
	
	//----------------------------------------------------------------------------------------------------------------------------------
	//battaglia tra 2 player
	
	char scelta_lettere;
	int turno=0;
	while(navi_tot!=0 && navi_tot1!=0)
	{
		system("cls");
		//supporto per stampo per prima riga numeri
		cont=1;
		cont1=1;
		//stampa le 2 mappe
    	for(i=0;i<MAP;i++)
	    {
	    	//mappa player 1
		    for(j=0;j<MAP;j++)
    		{
    			if(i==0)
    			{
    				printf("%2c",lettere[j].lettera);
				}
	    		else
	    		{
	    			//j!=0 perchè il primo 1 è solo dimostrativo
	    			if(mappa[i][j]==1 && j!=0)
	    			{
	    				printf("%2c",35);
	    			}
	    			else if(mappa[i][j]==3 && j!=0)
	    			{
	    				printf("%2c",219);
	    			}
	    			else
	    			{
	    				if(turno==1)
	    				{
	    					if(j==0)
	    					{
	    						printf("%2d",cont1);
	    						cont1++;
							}
	    					else
	    					{
	    						printf("%2d",0);
							}
						}
	    				else
	    				{
	    					printf("%2d",mappa[i][j]);
						}
					}
				}
	    	}
	    	printf("        |       ");
	    	//mappa player 2
	    	for(j=0;j<MAP;j++)
	    	{
	    		if(i==0)
    			{
    				printf("%2c",lettere[j].lettera);
				}
	    		else
	    		{
	    			if(mappa1[i][j]==1 && j!=0)
	    			{
	    				printf("%2c",35);
	    			}
	    			else if(mappa1[i][j]==3 && j!=0)
	    			{
	    				printf("%2c",219);
	    			}
	    			else
	    			{
	    				if(turno==0)
	    				{
	    					if(j==0)
	    					{
	    						printf("%2d",cont);
	    						cont++;
							}
	    					else
	    					{
	    						printf("%2d",0);
							}
						}
	    				else
	    				{
	    					printf("%2d",mappa1[i][j]);
						}
					}
				}
	    	}
	    	printf("\n");
	    }  
	    printf("-------------------------------------------------------------\n");
	    
	    //cont=1 perchè il primo quadrato è vuoto
	    cont=1;
	    
		fflush(stdin);
		switch(turno)
		{
			
			//player 1
			case 0:
				printf("turno player 1\n\n");
				printf("dammi la lettera\n");
				scanf("%c",&scelta_lettere);
				
				while(cont<MAP)
				{
					if(lettere[cont].lettera == scelta_lettere)
					{
						//posizione lettera
						j=lettere[cont].posizione;
					}
					cont++;
				}
				fflush(stdin);
				
				printf("dammi il numero\n");
				scanf("%d",&i);
			
				//bersaglio
				if(mappa1[i][j]==0)
				{
					mappa1[i][j]=1;
				}
				if(mappa1[i][j]==2)
				{
					navi_tot1--;
					mappa1[i][j]=3;
				}
				
				turno=1;
				break;
				
			//player 2
			case 1:
				printf("turno player 2\n\n");
				printf("dammi la lettera\n");
				scanf("%c",&scelta_lettere);
				
				while(cont<MAP)
				{
					if(lettere[cont].lettera == scelta_lettere)
					{
						//posizione lettera
						j=lettere[cont].posizione;
					}
					cont++;
				}
				fflush(stdin);
				
				printf("dammi il numero\n");
				scanf("%d",&i);
			
				//bersaglio
				if(mappa[i][j]==0)
				{
					mappa[i][j]=1;
				}
				if(mappa[i][j]==2)
				{
					navi_tot--;
					mappa[i][j]=3;
				}
				turno=0;
				break;
				
		}
	}
	//ristampa esito partita (prof lo so è bruttissimo ma sono troppo pigro per ottimizzare :-) 
    	for(i=0;i<MAP;i++)
	    {
		    for(j=0;j<MAP;j++)
    		{
    			if(i==0)
    			{
    				printf("%2c",lettere[j].lettera);
				}
	    		else
	    		{
	    			//j!=0 perchè il primo 1 è solo dimostrativo
	    			if(mappa[i][j]==1 && j!=0)
	    			{
	    				printf("%2c",35);
	    			}
	    			else if(mappa[i][j]==3 && j!=0)
	    			{
	    				printf("%2c",219);
	    			}
	    			else
	    			{
	    				printf("%2d",mappa[i][j]);
					}
				}
	    	}
	    	printf("        |       ");
	    	for(j=0;j<MAP;j++)
	    	{
	    		if(i==0)
    			{
    				printf("%2c",lettere[j].lettera);
				}
	    		else
	    		{
	    			if(mappa1[i][j]==1 && j!=0)
	    			{
	    				printf("%2c",35);
	    			}
	    			else if(mappa1[i][j]==3 && j!=0)
	    			{
	    				printf("%2c",219);
	    			}
	    			else
	    			{
	    				printf("%2d",mappa1[i][j]);
					}
				}
	    	}
	    	printf("\n");
	    } 
	if(navi_tot==0)
	{
		printf("il player 1 ha perso\n");
	}
	if(navi_tot1==0)
	{
		printf("il player 2 ha perso\n");
	}
	return 0;
}
