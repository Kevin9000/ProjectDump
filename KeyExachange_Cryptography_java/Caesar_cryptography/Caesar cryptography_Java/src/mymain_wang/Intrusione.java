package mymain_wang;

import java.util.ArrayList;

public class Intrusione 
{
    public Intrusione() {
    }
    
    public void hack(String passwordCriptata)
    {
        int lunghezzaPassword = 4;
        int [] contatoreLettere = new int[lunghezzaPassword];
        
        for(int cont = 0; cont < lunghezzaPassword; cont++)
        {
            contatoreLettere[cont] = 0;
        }
        
        //inizializzazione spazio della stringa (16)
        String parola = "    ";

        //inzializzazione valori iniziali della parola
        for(int cont = 0; cont < lunghezzaPassword; cont++)
        {
            parola = parola.substring(0,cont) + (char)contatoreLettere[cont] + parola.substring(cont);
        }
        
        int alfabetoASCII = 127;
        boolean ciclo = true;
        
        System.out.println("Operazione Brute Force in corso...");
        
        while(!passwordCriptata.equalsIgnoreCase(parola) && ciclo == true)
        {
            for(int cont1 = 0; cont1 < lunghezzaPassword && ciclo == true; cont1++)
            {
                if(contatoreLettere[cont1] == alfabetoASCII)
                {
                    contatoreLettere[cont1] = 0;
                    contatoreLettere[cont1+1]++;
                }
            }
            
            for(int cont = 0; cont < alfabetoASCII && ciclo == true; cont++)
            {
                for(int cont2 = 0; cont2 < lunghezzaPassword && ciclo == true; cont2++)
                {
                    parola = parola.substring(0, cont2) + (char)contatoreLettere[cont2] + parola.substring(cont2,lunghezzaPassword - 1);
                    if(passwordCriptata.equals(parola))
                    {
                        ciclo = false;
                    }
                }
                contatoreLettere[0]++;
            }
            
        }
        System.out.println("la password è: "+parola);
    }
}
