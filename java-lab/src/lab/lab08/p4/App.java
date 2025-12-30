package lab.lab08.p4;

//TODO:设计带头结点的单链表 ha，先将其输出。继而借助序列化机制，将该链表保存至文件 data.dat，然后从文件恢复该链表，表头名为 hb，并输出链表 hb中的所有元素。
import java.io.*;

class Node implements Serializable {
    int data;
    Node next;

    public Node(int data) {
        this.data = data;
    }
}

public class App {
    public static void main(String[] args) {
        Node ha = new Node(-1); // 头结点数据默认为-1
        Node n1 = new Node(10);
        Node n2 = new Node(20);
        Node n3 = new Node(30);
        ha.next = n1;
        n1.next = n2;
        n2.next = n3;

        System.out.println("原链表 ha 内容：");
        printList(ha);

        String fileName = "data.dat";
        serializeList(ha, fileName);

        Node hb = deserializeList(fileName);
        System.out.println("恢复后的链表 hb 内容：");
        printList(hb);
    }

    public static void printList(Node head_in) {
        Node curr = head_in.next;
        while (curr != null) {
            System.out.print(curr.data + (curr.next != null ? " -> " : ""));
            curr = curr.next;
        }
        System.out.println();
    }

    public static void serializeList(Node head_in, String fileName_in) {
        ObjectOutputStream oos = null;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(fileName_in));
            oos.writeObject(head_in);
            System.out.println("链表已成功序列化到文件: " + fileName_in);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (oos != null) {
                try {
                    oos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static Node deserializeList(String fileName_in) {
        ObjectInputStream ois = null;
        try {
            ois = new ObjectInputStream(new FileInputStream(fileName_in));
            return (Node) ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        } finally {
            if (ois != null) {
                try {
                    ois.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return null;
    }
}
