package lab06.$2_lightControl;

import java.awt.*;
import java.awt.event.*;

//TODO:要求用两种方法实现：1.一般方法;2.界面与事件处理者相分离的方法

class lamp extends Frame  {
    Label lb1,lb2;
    Button b_open,b_close;
    Deal d;
    public void setDeal(Deal d1){
        this.d=d1;
        b_close.addActionListener(d);
        b_open.addActionListener(d);
        this.addWindowListener(d);
    }
    public lamp(){
        this.setSize(300,100);
        this.setLocation(300,300);
        this.setLayout(new FlowLayout());
        Font f=new Font("ËÎÌå",Font.PLAIN,16);
        lb1=new Label("µÆ×´Ì¬:");
        lb1.setFont(f);
        this.add(lb1);
        lb2=new Label("    ");
        lb2.setBackground(Color.black);
        this.add(lb2);
        b_open=new Button("open");
        this.add(b_open);
        b_close=new Button("close");
        b_close.setEnabled(false);
        this.add(b_close);

        this.setVisible(true);
    }
}
class Deal implements ActionListener,WindowListener{
    lamp lp;
    public  void setService(lamp lp)
    { this.lp=lp;     }
    public void windowOpened(WindowEvent e) {}
    public void windowClosing(WindowEvent e) {System.exit(0); }
    public void windowClosed(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}
    public void actionPerformed(ActionEvent e){
        if(e.getSource()== lp.b_open){
            lp.lb2.setBackground(Color.red);
            lp.b_open.setEnabled(false);
            lp.b_close.setEnabled(true);
        }
        if(e.getSource()== lp.b_close){
            lp.lb2.setBackground(Color.black);
            lp.b_close.setEnabled(false);
            lp.b_open.setEnabled(true);
        }
    }
}
class Main{
    public static void main(String[] args){
        lamp lp=new lamp();
        Deal d=new Deal();
        lp.setDeal(d);
        d.setService(lp);

    }
}
