/*
 * Realizzare due applicativi, in un linguaggio a scelta, che realizzino una comunicazione cifrata con chiave simmetrica generata
    tramite l'algoritmo di Diffie-Hellman.
    La comunicazione deve essere bidirezionale e si deve avere la possibilità di cambiare chiave in seguito alla richiesta di uno dei 
    due algoritmi.
    Ogni applicativo deve poter scrivere su una videata "console" il risultato dei vari passaggi in corso, in modo da poter essere 
    verificato.
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
    //variabili
    //stream
    static OutputStreamWriter osw;
    static BufferedWriter bw;
    static InputStreamReader isr;
    static BufferedReader br;
    static PrintWriter pw;
    static Socket s;

    //interi
    static final int port = 49153;
    static int p;
    static int g;
    static int segreto_b;
    static int A;
    static int ka;//KA=(g^b mod p)^a %p B^a mod p

    //stringhe
    static String parolaCriptata = "";
    static String sceltaUtente = "";

    //char
    static char supp;

    //random
    static Random r = new Random();

    public static void main(String[] args) {
        try {
            //connessione al sever
            s = new Socket("127.0.0.1", port);
            System.out.println("Client connesso..");

            generoChiave();

            //scelta del messaggio da inviare
            Scanner sc = new Scanner(System.in);
            do {
                System.out.println("Inserisci il messaggio da inviare.." + "Se vuoi concludere il programma scrivi 'e', se vuoi cambiare chiave scrivi 'c'");
                sceltaUtente = sc.nextLine();
                System.out.println("Ho scritto: " + sceltaUtente);

                if (sceltaUtente.equalsIgnoreCase("c")) {
                    System.out.println("sto generando una nuova chiave....");
                    criptoMessaggio();
                    generoChiave();
                } else {
                    criptoMessaggio();
                }

            } while (!sceltaUtente.equalsIgnoreCase("e"));

        } catch (IOException ex) {
        }
    }

    public static void generoChiave() throws IOException {
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
        segreto_b = r.nextInt(20);//scegliamo un range basso per prova
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

    }

    public static void criptoMessaggio() {
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
    }
}
