package lab.lab05.p3;

import java.util.Scanner;

class App {

    public static void main(String[] x) {

        BinTree t = new BinTree('#');

        // System.out.print("请输入二叉树建树字符，#表示null：\n");
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        sc.close();
        ReaderChar r = new ReaderChar(s);

        t = t.createBinTree(r);
        System.out.print("pre=");
        t.pre(); // 输出递归前序

        System.out.print("\npreN=");
        t.preN(); // 输出非递归前序

        System.out.print("\nin=");
        t.in(); // 输出递归中序

        System.out.print("\ninN=");
        t.inN(); // 输出非递归中序

        System.out.print("\npost=");
        t.post(); // 输出递归后序

        System.out.print("\npostN=");
        t.postN(); // 输出非递归后序

    }

}

class ReaderChar {

    String createBinTreeStr;
    int pos;

    ReaderChar(String s) {
        createBinTreeStr = s;
    }

    char getChar() { // 就是创建这个新类的意义，每次getChar一次，位置也会保存下来，可以重复复用
        char x = createBinTreeStr.charAt(pos);
        pos++;
        return x;
    }

}

class BinTree {
    char root_data;
    BinTree L_chid;
    BinTree R_chid;

    BinTree createBinTree(ReaderChar data_in) {
        char c = data_in.getChar();
        if (c != '#') {
            BinTree T = new BinTree(c);
            T.L_chid = createBinTree(data_in);
            T.R_chid = createBinTree(data_in);
            return T;
        }
        return null;
    }

    BinTree(char single_char_in) {
        root_data = single_char_in;
    }

    void pre() {
        System.out.print(root_data + " ");
        if (this.L_chid != null) {
            this.L_chid.pre();
        }
        if (this.R_chid != null) {
            this.R_chid.pre();
        }
    }

    void preN() { // 非递归前序遍历
        Stack stack = new Stack();
        BinTree current = this;

        while (!stack.isEmpty() || current != null) {
            while (current != null) {
                System.out.print(current.root_data + " ");
                stack.push(current);
                current = current.L_chid;
            }
            if (!stack.isEmpty()) {
                current = stack.pop();
                current = current.R_chid;
            }
        }
    }

    void inN() { // 非递归中序左根右
        Stack stack = new Stack();
        BinTree current = this;

        while (!stack.isEmpty() || current != null) {
            while (current != null) {
                stack.push(current);
                current = current.L_chid; // 先压，没左孩子了再弹
            }
            if (!stack.isEmpty()) {
                current = stack.pop();
                System.out.print(current.root_data + " ");
                current = current.R_chid;
            }
        }
    }

    void in() {
        if (this.L_chid != null) {
            this.L_chid.in();
        }
        System.out.print(root_data + " ");
        if (this.R_chid != null) {
            this.R_chid.in();
        }
    }

    void post() {
        if (this.L_chid != null) {
            this.L_chid.post();
        }
        if (this.R_chid != null) {
            this.R_chid.post();
        }
        System.out.print(root_data + " ");
    }

    void postN() { // 非递归后序,之前都是用两个栈去处理非二叉树的非递归后序遍历，还没正式写过一个栈处理二叉树的，这次写个详细注释理解一下

        // 如果刚从左边回来，必须（把它重新压栈）然后去探索它的右边。如果刚从右边回来，那才说明左右都搞定了，终于可以打印这个根了。

        Stack stack = new Stack();
        BinTree current = this;

        while (!stack.isEmpty() || current != null) {
            while (current != null) {
                stack.push(current);
                stack.tag[stack.top - 1] = 0; // 标记为左子树未访问，意思是：我刚被你（push）进栈，你现在应该去探索我的左边。
                current = current.L_chid;
            }
            if (!stack.isEmpty()) {
                current = stack.pop();
                int t = stack.tag[stack.top];
                if (t == 0) { // 如果左子树未访问
                    stack.push(current); // 重新压入当前节点
                    stack.tag[stack.top - 1] = 1; // 标记为右子树未访问,意思是：“你（pop）了我，发现我的 tag=0。这说明我的左边刚处理完。把我重新压栈，把我的 tag
                                                  // 设为1，然后去探索我的右边。”
                    current = current.R_chid; // 转向右子树
                } else { // 右子树已访问
                    System.out.print(current.root_data + " ");
                    current = null; // 设置为null以继续弹栈
                }
            }
        }
    }

    class Stack { // 话又说回来，不考虑满栈的情况吗？

        BinTree[] s = new BinTree[200];
        int[] tag = new int[200];// 用于非递归后序
        int top;

        boolean isEmpty() {
            return top == 0;
        }

        void push(BinTree x) {
            s[top] = x;
            top++;
        }

        BinTree pop() {
            top--;
            return s[top];
        }

    }

}
