/*
 * Realizzare due applicativi, in un linguaggio a scelta, che realizzino una comunicazione cifrata con chiave simmetrica generata
    tramite l'algoritmo di Diffie-Hellman.
    La comunicazione deve essere bidirezionale e si deve avere la possibilità di cambiare chiave in seguito alla richiesta di uno dei 
    due algoritmi.
    Ogni applicativo deve poter scrivere su una videata "console" il risultato dei vari passaggi in corso, in modo da poter essere 
    verificato.
    Occorre mostrare nella console anche il testo de
    Occorre mostrare nella console anche il testo del messaggio criptato ricevuto e la decodifica effettuata.
    Il messaggio da inviare deve poter essere scelto al momento e deve consistere in lettere maiuscole presenti nella codifica ASCII a 7 bit.
    Per la criptatura scegliere fra: operatore XOR, sostituzione della lettera stile cifrario di Cesare
 */
package diffiehellmanclient;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;

/**
 *
 * @author Chry
 */
public class DiffieHellmanClient {

    /**
     * @param args the command line arguments
     */
    //BOB
    public static void main(String[] args) {
        //variabili

        //stream
        OutputStreamWriter osw;
        BufferedWriter bw;
        InputStreamReader isr;
        BufferedReader br;
        PrintWriter pw;
        Socket s;

        //interi
        final int port = 5555;
        int p;
        int g;
        int segreto_b;
        int A;
        int ka;//KA=(g^b mod p)^a %p B^a mod p
       
        //stringhe
        String parolaCriptata = "";
        
        //char
        char supp;

        //random
        Random r = new Random();

        try {
            //connessione al sever
            s = new Socket("127.0.0.1", port);
            System.out.println("Client connesso..");

            //scelgo i due numeri primi
            p = 23;
            g = 5;
            System.out.println("I numeri primi sono: " + p + "," + g + "...");

            //mando i numeri al server
            osw = new OutputStreamWriter(s.getOutputStream());
            bw = new BufferedWriter(osw);
            pw = new PrintWriter(bw, true);
            pw.println(p);
            pw.println(g);
            pw.flush();

            //genero numero segreto
            //segreto_b = r.nextInt(50);//scegliamo un range basso per prova
            segreto_b = 15;
            System.out.println("segreto b scelto: " + segreto_b);

            //ricevo codice segreto del server
            isr = new InputStreamReader(s.getInputStream());
            br = new BufferedReader(isr);
            A = Integer.parseInt(br.readLine());
            System.out.println("A: " + A);
            System.out.println("codice segreto b: " + (g ^ segreto_b) % p);

            //invio codice segreto al server
            pw.println((g ^ segreto_b) % p);

            //calcolo la costante KA=(g^b mod p)^a %p = B^a mod p
            ka = (A ^ segreto_b) % p;
            System.out.println("KA:" + ka);

            //scelta del messaggio da inviare
            Scanner sc = new Scanner(System.in);
            System.out.println("Inserisci il messaggio da inviare..");
            String sceltaUtente = sc.nextLine();
            System.out.println("Ho scritto: " + sceltaUtente);
            
            //cripto il messaggio con i cifrario Cesare
            for (int j = 0; j < sceltaUtente.length(); j++) {
                supp = sceltaUtente.charAt(j);
                supp += ka;
                parolaCriptata = parolaCriptata.substring(0, j) + supp;
            }
            System.out.println("invio il messaggio: " + parolaCriptata);
            
            //invio il messaggio criptato
            pw.flush();
            pw.println(parolaCriptata);
            pw.flush();

        } catch (IOException ex) {

        }
    }

}
