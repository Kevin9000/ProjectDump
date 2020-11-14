package mymain_wang;

public class Decriptatura 
{
    int alfabetoASCII = 128;
                
    char letteraDecriptata;
        
    String parolaNonScriptata = "";
    
    
    public Decriptatura() {
    }
    
    public void decript(String parolaCriptata)
    {
        for(int chiave = 1; chiave < alfabetoASCII; chiave++)
        {    
            for(int cont = 0; cont < parolaCriptata.length(); cont++)
            {
                letteraDecriptata = parolaCriptata.charAt(cont);
                letteraDecriptata -= chiave;
                parolaNonScriptata = parolaNonScriptata.substring(0, cont) + letteraDecriptata;
            }
            System.out.println(parolaNonScriptata + "      Chiave di criptatura usata: +"+chiave);
        }
        
        for(int chiave = 1; chiave < alfabetoASCII; chiave++)
        {    
            for(int cont = 0; cont < parolaCriptata.length(); cont++)
            {
                letteraDecriptata = parolaCriptata.charAt(cont);
                letteraDecriptata += chiave;
                parolaNonScriptata = parolaNonScriptata.substring(0, cont) + letteraDecriptata;
            }
            System.out.println(parolaNonScriptata + "      Chiave di criptatura usata: -"+chiave);
        }
    }
    
    public void decriptConChiave(String parolaCriptata, int chiave)
    {
        for(int cont1 = 0; cont1 < parolaCriptata.length(); cont1++)
        {
            letteraDecriptata = parolaCriptata.charAt(cont1);
            letteraDecriptata -= chiave;
            parolaNonScriptata = parolaNonScriptata.substring(0, cont1) + letteraDecriptata;
        }
        System.out.println(parolaNonScriptata + "      Chiave di criptatura usata: +"+chiave);
        
        for(int cont1 = 0; cont1 < parolaCriptata.length(); cont1++)
        {
            letteraDecriptata = parolaCriptata.charAt(cont1);
            letteraDecriptata += chiave;
            parolaNonScriptata = parolaNonScriptata.substring(0, cont1) + letteraDecriptata;
        }
        System.out.println(parolaNonScriptata + "      Chiave di criptatura usata: -"+chiave);
    }
}
