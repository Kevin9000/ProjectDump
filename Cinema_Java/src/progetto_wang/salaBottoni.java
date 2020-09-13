package progetto_wang;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import javax.swing.*;

public class salaBottoni extends JFrame implements ActionListener, WindowListener
{
    int numeroBottoni = 100;
    
    int postiRichiesti;
    
    JPanel label = new JPanel(new GridLayout(10,10));
    
    JButton posto [] = new JButton[numeroBottoni];

    public salaBottoni() 
    {
        setVisible(false);
        setSize(600, 600);
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        
        add(label);
        
        for(int cont = 0; cont < numeroBottoni; cont++)
        {
            posto[cont] = new JButton(String.valueOf(cont));
            label.add(posto[cont]);
            
            posto[cont].addActionListener(this);
        }
        
        addWindowListener(this);
    }

    public void visualizza(int postiComprati)
    {
        setVisible(true);
        postiRichiesti = postiComprati;
    }
    
    @Override
    public void actionPerformed(ActionEvent e) 
    {
        if(postiRichiesti != 0)
        {
            for(int cont = 0; cont < numeroBottoni; cont++)
            {
                if(e.getSource() == posto[cont])
                {
                    postiRichiesti--;
                    posto[cont].setBackground(Color.red);
                }
            }
        }
    }

    public void windowActivated(WindowEvent arg0) {}  
    public void windowClosed(WindowEvent arg0) {}  
    public void windowDeactivated(WindowEvent arg0) {}  
    public void windowDeiconified(WindowEvent arg0) {}  
    public void windowIconified(WindowEvent arg0) {}  
    public void windowOpened(WindowEvent arg0) {}  
    
    public void windowClosing(WindowEvent arg0) 
    {  
        if(postiRichiesti > 0)
        {
            int confirmed = JOptionPane.showConfirmDialog(null, "è sicuro di voler uscire?, ci sono ancora da prenotare: "+postiRichiesti+" posti\nsi ricorda che non esiste nessun tipo di rimborso", "Exit Program Message Box",JOptionPane.YES_NO_OPTION);
            if (confirmed == JOptionPane.YES_OPTION) 
            {
                dispose();
            }
        }
        else if (postiRichiesti == 0)
        {
            dispose();
        }
    }  
}
