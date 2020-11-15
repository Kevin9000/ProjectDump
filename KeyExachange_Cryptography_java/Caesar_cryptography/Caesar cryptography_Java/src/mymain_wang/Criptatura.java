package mymain_wang;

public class Criptatura 
{
    int chiaveCriptatura = -4;
    char supp;
    
    public Criptatura() {
    }
    
    public String cript(String parola)
    {
        String parolaCriptata = "";
        
        for(int cont = 0; cont < parola.length(); cont++)
        {
            supp = parola.charAt(cont);
            supp += chiaveCriptatura;
            parolaCriptata = parolaCriptata.substring(0, cont) + supp;
        }
        
        return parolaCriptata; 
    }
}
