package mymain_wang;

import java.util.ArrayList;
import java.util.Scanner;

public class MyMain_WANG 
{
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_RESET = "\u001B[0m";
    
    public static void main(String[] args) throws InterruptedException 
    {
        //creazione oggetti
        Criptatura parola = new Criptatura();
        Decriptatura convertitore = new Decriptatura();
        Intrusione irruzione = new Intrusione();
        
        String ParolaCriptata;
        ArrayList <String> SerieParoleCriptate = new ArrayList();
        
        Scanner scInt = new Scanner(System.in);
        Scanner scString = new Scanner(System.in);
        
        String [] passwordCriptate = {"dB^q","8^Li","mEv&"};
        String password;
        
        boolean ciclo = true;
        int sceltaUtente;
        int supp;
        
        while(ciclo)
        {
            System.out.println(ANSI_RED+"Scegli una delle seguenti opzioni:"+ANSI_RESET+"\n"
                    + "1)Input parola da criptare\n"
                    + "2)Inserire una parola già criptata\n"
                    + "3)Lista parole Criptate\n"
                    + "4)Decriptare una parola data una chiave (cifrario di Cesare)\n"
                    + "5)Decriptare una parola senza chiave (cifrario di Cesare)\n"
                    + "6)Irruzione Brute Force (data una password o password predefinito)\n"
                    + "7)Esci");
            sceltaUtente = scInt.nextInt();
            System.out.println("\n");
            switch(sceltaUtente)
            {
                case 1:
                    System.out.println("Inserisci la parola o frase da criptare:");
                    ParolaCriptata = parola.cript(scString.nextLine());
                    
                    System.out.println("Risultato Criptatura: "+ParolaCriptata+"\n\n");
                    
                    SerieParoleCriptate.add(new String(ParolaCriptata));
                    break;
                   
                case 2:
                    System.out.println("Inserisci la parola criptata");
                    SerieParoleCriptate.add(new String(scString.nextLine()));
                    break;
                    
                case 3:
                    for(int cont = 0; cont < SerieParoleCriptate.size(); cont++)
                    {
                        System.out.println(cont+") "+SerieParoleCriptate.get(cont));
                    }
                    System.out.println("");
                    break;
                    
                case 4:
                    if(SerieParoleCriptate.size() > 0)
                    {
                        System.out.println("Scegli quale parola De-Criptare");
                        for(int cont = 0; cont < SerieParoleCriptate.size(); cont++)
                        {
                            System.out.println(cont+") "+SerieParoleCriptate.get(cont));
                        }
                        sceltaUtente = scInt.nextInt();
                        
                        if(sceltaUtente < SerieParoleCriptate.size())
                        {
                            System.out.println("Scegliere la chiave");
                            supp = scInt.nextInt();
                            convertitore.decriptConChiave(SerieParoleCriptate.get(sceltaUtente),supp);
                        }
                        else
                        {
                            System.out.println("Scelta non valida");
                        }
                        break;
                    }
                    else
                    {
                        System.out.println("si prega prima di criptare una parola");
                    }

                case 5:
                    if(SerieParoleCriptate.size() > 0)
                    {
                        System.out.println("Scegli quale parola De-Criptare");
                        for(int cont = 0; cont < SerieParoleCriptate.size(); cont++)
                        {
                            System.out.println(cont+") "+SerieParoleCriptate.get(cont));
                        }
                        sceltaUtente = scInt.nextInt();

                        if(sceltaUtente < SerieParoleCriptate.size())
                        {
                            convertitore.decript(SerieParoleCriptate.get(sceltaUtente));
                        }
                        else
                        {
                            System.out.println("Scelta non valida");
                        }
                    }
                    else
                    {
                        System.out.println("si prega prima di criptare una parola");
                    }
                    break;
                
                case 6:
                    System.out.println("Scegliere quale password da usare come test per irrompere:\n1) "+passwordCriptate[0]+"\n2) "+passwordCriptate[1]+"\n3) "+passwordCriptate[2]+"\n4)usare una password inserita da tastiera ");
                    sceltaUtente = scInt.nextInt();
                    switch(sceltaUtente)
                    {
                        case 1:
                            irruzione.hack(passwordCriptate[0]);
                            break;
                            
                        case 2:
                            irruzione.hack(passwordCriptate[1]);
                            break;
                            
                        case 3:
                            irruzione.hack(passwordCriptate[2]);
                            break;
                            
                        case 4:
                            System.out.println("Inserisca una password di lunghezza 4 (codifica ASCII)");
                            password = scString.nextLine();
                            
                            if(password.length() == 4)
                            {
                                irruzione.hack(password);
                            }
                            else
                            {
                                System.out.println("Lunghezza non valida");
                            }
                            break;
                            
                        default:
                            System.out.println("Ha inserito un'opzione non valida");
                            break;
                            
                    }
                    break;
                
                case 7:
                    ciclo = false;
                    break; 
            }
            
            Thread.sleep(2000);
        }
    }
}
