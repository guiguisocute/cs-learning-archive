package Quickverify;

public class Testsel {
    public static void main(String[] args) {
        sellTicket[] st = new sellTicket[10];
        final TicketOfifice to = new TicketOfifice(100);
        for (int i = 0; i < 10; i++) {
            st[i] = new sellTicket(to, "窗口" + (i + 1));
            st[i].start();
        }
    }
}

class TicketOfifice{
    int ticket_num;

    TicketOfifice(int ticket_num_in){
        this.ticket_num = ticket_num_in;
    }

    public void sell(){
        if(ticket_num > 0){
            System.out.println(Thread.currentThread().getName() + "尝试卖出第" + (ticket_num--) + "张票");
            if(ticket_num >= 0){
                System.out.println("卖出成功！");
            }else{
                System.out.println("票已售完，卖出失败！");
        }
    }
}


}

class sellTicket extends Thread{
    private TicketOfifice to;

    sellTicket(TicketOfifice to_in, String name){
        super(name);
        this.to = to_in;
    }
    public void run(){
        
        while(to.ticket_num > 0){
            synchronized (to){
            to.sell();
            }
        }
    }
}
