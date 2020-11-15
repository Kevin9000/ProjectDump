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
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Chry
 */
public class DiffieHellmanServer {//server

    /**
     * @param args the command line arguments
     */
    //ALICE
    //variabili
    //stream
    static OutputStreamWriter osw;
    static BufferedWriter bw;
    static InputStreamReader isr;
    static BufferedReader br;
    static PrintWriter pw;
    static ServerSocket server;
    static Socket s;

    //interi
    static final int port = 49153;
    static int p;
    static int g;
    static int segreto_a;
    static int B;
    static int kb;//kb=(g^a mod p)^b % p = A^b %p

    //stringhe
    static String messaggioUtente;
    static String parolaDecriptata = "";

    //char
    static char supp;

    //random
    static Random r = new Random();

    public static void main(String[] args) throws InterruptedException {

        //creo il server
        try {
            server = new ServerSocket(port);
            System.out.println("Server Online sulla porta numero:" + port + "...");
            //attendo connessione al client
            s = server.accept();

            //connessione avvenuta con successo
            System.out.println("Connesso al client");

            //genero la chiave
            generoChiave();
            
            do {
                //se il client decide di cambniare la chiave
                if (parolaDecriptata.equalsIgnoreCase("c")) {
                    System.out.println("sto generando una nuova chiave....");
                    generoChiave();
                    decriptoMessaggio();
                }
                else{
                    decriptoMessaggio();
                }
            } while (!parolaDecriptata.equalsIgnoreCase("e"));

            System.out.println("CONNESSIONE INTERROTTA!");
        } catch (IOException ex) {
        }
    }

    public static void generoChiave(){
        try {
            //ricevo i numeri primi
            isr = new InputStreamReader(s.getInputStream());
            br = new BufferedReader(isr);
            p = Integer.parseInt(br.readLine());
            g = Integer.parseInt(br.readLine());
            System.out.println("numeri ricevuti " + p + "," + g);
            
            //genero numero segreto
            segreto_a = r.nextInt(20);//scegliamo un range basso per prova
            //segreto_a = 6;
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
        } catch (IOException ex) {
        }
    }

    public static void decriptoMessaggio() throws IOException {
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
}
