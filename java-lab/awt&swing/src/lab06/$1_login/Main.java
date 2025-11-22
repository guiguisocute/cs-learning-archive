package login;

import java.awt.*;
import java.awt.event.*;
class UserFrame extends Frame implements ActionListener ,WindowListener{
    TextField t_user,t_ps;
    Button b_ok,b_exit;
    Label tl;
    public UserFrame() {
        this.setTitle("第一个简单的界面");
        setSize(400,100);
        setLocation(400,200);
        this.setBackground(Color.lightGray);
        this.setLayout(new FlowLayout());
        this.add(new Label("userName:"));
        t_user=new TextField("unknow");
        this.add(t_user);
        this.add(new Label("password:"));
        t_ps=new TextField(5);
        this.add(t_ps);

        b_ok=new Button("OK");
        b_exit=new Button("EXIT");
        this.add(b_ok);
        this.add(b_exit);
        tl=new Label("   ");
        this.add(tl);
        b_exit.addActionListener(this);
        b_ok.addActionListener(this);
        this.addWindowListener(this);
        this.setVisible(true);
    }

    public void actionPerformed(ActionEvent e){
        if(e.getSource()==this.b_exit){System.exit(0); }
        if(e.getActionCommand()=="OK"){
            if(this.t_user.getText().equals("abc")&&(this.t_ps.getText().equals("1234")))
                this.tl.setText("welcome,abc!");
            else
                this.tl.setText("username or password is wrong!");
            this.setVisible(true);
        }
    }
    public void windowOpened(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}
    public void windowClosing(WindowEvent e) {System.exit(0); }

}
class Main{
    public static void main(String[] args){
        new UserFrame();
    }

}
