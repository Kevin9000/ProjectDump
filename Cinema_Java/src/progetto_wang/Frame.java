package progetto_wang;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class Frame extends JFrame implements ActionListener 
{
    JPanel panel1 = new JPanel(new GridLayout(1,3));
    JPanel panel2 = new JPanel(new GridLayout(5,1));
    JPanel panel3 = new JPanel(new GridLayout(6,1));
    
    JLabel label1 = new JLabel("<html>Si prega di selezionare il film desiderato <br> al quale corrisponderà una sala<br>Si ricorda che una volta comprato dei biglietti <br> non esisterà nessun rimborso<html>");
    
    JLabel labelPrezzo = new JLabel("Prezzo: ???");
    JLabel labelNumeroBiglietti = new JLabel("N.Biglietti che si vuole aquistare: ");
    JLabel labelNumeroBigliettiRimanenti = new JLabel("N.Biglietti rimanenti: ???");
    JLabel messaggioUtente = new JLabel("Msg : Si prega di selezionare un film");
    
    JTextField numeroBiglietti = new JTextField();
    
    JButton bottoneAquista = new JButton("Aquista");

    Info bottoni [] = new Info[5];
    
    int numeroBottoneSelezionato = 10;
    
    salaBottoni sala [] = new salaBottoni [5];
    
    public Frame() 
    {
        for(int cont = 0; cont < 5; cont++)
        {
            sala[cont] = new salaBottoni();
        }
        
        setVisible(true);
        setSize(800, 500);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        add(panel1);
        
        panel1.add(label1);
        
        panel1.add(panel2);
        
        bottoni [0] = new Info((float) 3.5, "Star Wars");
        bottoni[0].bottone.addActionListener(this);
        bottoni [1] = new Info((float) 4.5, "Tolo Tolo");
        bottoni[1].bottone.addActionListener(this);
        bottoni [2] = new Info((float) 5.5, "Mad Max");
        bottoni[2].bottone.addActionListener(this);
        bottoni [3] = new Info((float) 6.5, "Blade Runner");
        bottoni[3].bottone.addActionListener(this);
        bottoni [4] = new Info((float) 7.5, "Il Miglio Verde");
        bottoni[4].bottone.addActionListener(this);
        
        panel2.add(bottoni[0].bottone);
        panel2.add(bottoni[1].bottone);
        panel2.add(bottoni[2].bottone);
        panel2.add(bottoni[3].bottone);
        panel2.add(bottoni[4].bottone);
        
        panel1.add(panel3);
        
        panel3.add(labelPrezzo);
        panel3.add(labelNumeroBigliettiRimanenti);
        panel3.add(labelNumeroBiglietti);
        panel3.add(numeroBiglietti);
        panel3.add(bottoneAquista);
        panel3.add(messaggioUtente);
        
        bottoneAquista.addActionListener(this);
    }
    
    
    @Override
    public void actionPerformed(ActionEvent e) 
    {
        int supp;
        
        for(int cont = 0; cont < 5; cont++)
        {
            if(e.getSource().equals(bottoni[cont].bottone))
            {
                labelPrezzo.setText("Prezzo: "+bottoni[cont].prezzo);
                labelNumeroBigliettiRimanenti.setText("N.Biglietti rimanenti: "+bottoni[cont].posti);
                numeroBottoneSelezionato = cont;
            }
        }
        
        if(e.getSource().equals(bottoneAquista) && numeroBottoneSelezionato != 10)
        {
            try
            {
                supp = Integer.parseInt(numeroBiglietti.getText());
                
                if(supp > bottoni[numeroBottoneSelezionato].posti)
                {
                    messaggioUtente.setText("Msg : Non ci sono Posti!!!");
                }                
                else
                {
                    int supp1 = JOptionPane.showConfirmDialog(null, "Lei sta comprando: "+numeroBiglietti.getText()+"\nal prezzo di: "+bottoni[numeroBottoneSelezionato].prezzo+" euro ciascuno \nè sicuro?", "Exit Program Message Box",JOptionPane.YES_NO_OPTION);
                    if (supp1 == JOptionPane.YES_OPTION) 
                    {
                        bottoni[numeroBottoneSelezionato].posti -= supp;
                        labelNumeroBigliettiRimanenti.setText("N.Biglietti rimanenti: "+bottoni[numeroBottoneSelezionato].posti);

                        sala[numeroBottoneSelezionato].visualizza(Integer.parseInt(numeroBiglietti.getText()));
                    }
                }
            }
            catch(NumberFormatException exc)
            {
                messaggioUtente.setText("Msg : Si prega di inserire un numero");
            }
        }
    }

    
    
}

