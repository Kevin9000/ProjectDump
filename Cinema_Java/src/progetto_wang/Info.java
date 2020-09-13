package progetto_wang;

import javax.swing.JButton;
import javax.swing.JFrame;

public class Info extends JFrame
{
    JButton bottone;
    
    int posti = 100;
    float prezzo;

    public Info(float prezzo, String nomeBottone) {
        this.prezzo = prezzo;
        bottone = new JButton(nomeBottone);
    }

}
