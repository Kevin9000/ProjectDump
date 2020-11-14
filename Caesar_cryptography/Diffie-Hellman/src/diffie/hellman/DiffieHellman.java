/*
 *  Realizzare due applicativi, in un linguaggio a scelta, che realizzino una comunicazione cifrata con chiave simmetrica generata
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
package diffie.hellman;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Random;

/**
 *
 * @author Chry
 */
public class DiffieHellman {//server

    /**
     * @param args the command line arguments
     */
    //ALICE
    public static void main(String[] args) {

        //variabili
        //stream
        OutputStreamWriter osw;
        BufferedWriter bw;
        InputStreamReader isr;
        BufferedReader br;
        PrintWriter pw;
        ServerSocket server;
        Socket s;

        //interi
        final int port = 5555;
        int p;
        int g;
        int segreto_a;
        int B;
        int kb;//kb=(g^a mod p)^b % p = A^b %p

        //stringhe
        String messaggioUtente;
        String parolaDecriptata = "";
        
        //char
        char supp;

        //random
        Random r = new Random();

        //creo il server
        try {
            server = new ServerSocket(port);
            System.out.println("Server Online sulla porta numero:" + port + "...");
            while (true) {
                //attendo connessione al client
                s = server.accept();

                //connessione avvenuta con successo
                System.out.println("Connesso al client");

                //ricevo i numeri primi
                isr = new InputStreamReader(s.getInputStream());
                br = new BufferedReader(isr);
                p = Integer.parseInt(br.readLine());
                g = Integer.parseInt(br.readLine());
                System.out.println("numeri ricevuti " + p + "," + g);

                //genero numero segreto
                //segreto_a = r.nextInt(50);//scegliamo un range basso per prova
                segreto_a = 6;
                System.out.println("segreto a scelto:" + segreto_a);

                //invio codice segreto al client
                osw = new OutputStreamWriter(s.getOutputStream());
                bw = new BufferedWriter(osw);
                pw = new PrintWriter(bw, true);
                pw.println((g ^ segreto_a) % p);
                System.out.println("codice segreto a: " + (g ^ segreto_a) % p);

                //ricevo codice segreto del client
                B = Integer.parseInt(br.readLine());
                System.out.println("B: " + B);

                //calcolo la costante kb=(g^a % p)^b % p = A^b %p
                kb = (B ^ segreto_a) % p;
                System.out.println("Kb:" + kb);

                //ricevo il messaggio cripatato
                messaggioUtente = br.readLine();
                System.out.println("Messaggio ricevuto: " + messaggioUtente);

                //decripto il messaggio
                System.out.println("Decripto il messaggio.....");
                
                for (int j = 0; j < messaggioUtente.length(); j++) {
                    supp = messaggioUtente.charAt(j);
                    supp -= kb;
                    parolaDecriptata = parolaDecriptata.substring(0, j) + supp;
                }
                
                System.out.println("Messaggio decriptato: " + parolaDecriptata);
            }
        } catch (IOException ex) {
        }
    }

}
