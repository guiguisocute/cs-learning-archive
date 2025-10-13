package Quickverify.VSC;

import java.util.LinkedList;
import java.util.Queue;
public class testforIDK {
    // ====== 节点定义 ======
    static class Node {
        int val;
        Node left, right;
        Node(int v) { this.val = v; }
    }

    // ====== BST 实现 ======
    static class BinarySearchTree {
        private Node root;

        public void insert(int v) { root = insertRec(root, v); }
        private Node insertRec(Node n, int v) {
            if (n == null) return new Node(v);
            if (v < n.val) n.left = insertRec(n.left, v);
            else           n.right = insertRec(n.right, v);
            return n;
        }

        public boolean contains(int v) {
            Node cur = root;
            while (cur != null) {
                if (v == cur.val) return true;
                cur = (v < cur.val) ? cur.left : cur.right;
            }
            return false;
        }

        public void delete(int v) { root = deleteRec(root, v); }
        private Node deleteRec(Node n, int v) {
            if (n == null) return null;
            if (v < n.val) n.left = deleteRec(n.left, v);
            else if (v > n.val) n.right = deleteRec(n.right, v);
            else {
                // 命中要删除的节点
                if (n.left == null)  return n.right;
                if (n.right == null) return n.left;
                // 两个孩子：用右子树最小节点替换
                Node min = n.right;
                while (min.left != null) min = min.left;
                n.val = min.val;
                n.right = deleteRec(n.right, min.val);
            }
            return n;
        }

        public int height() { return height(root); }
        private int height(Node n) {
            if (n == null) return 0;
            int lh = height(n.left), rh = height(n.right);
            return 1 + (lh > rh ? lh : rh);
        }

        // 遍历
        public void inorder()  { inorder(root);  System.out.println(); }
        private void inorder(Node n) {
            if (n == null) return;
            inorder(n.left);
            System.out.print(n.val + " ");
            inorder(n.right);
        }

        public void preorder() { preorder(root); System.out.println(); }
        private void preorder(Node n) {
            if (n == null) return;
            System.out.print(n.val + " ");
            preorder(n.left);
            preorder(n.right);
        }

        public void postorder(){ postorder(root);System.out.println(); }
        private void postorder(Node n) {
            if (n == null) return;
            postorder(n.left);
            postorder(n.right);
            System.out.print(n.val + " ");
        }

        public void levelOrder() {
            if (root == null) { System.out.println(); return; }
            Queue<Node> q = new LinkedList<Node>();
            q.offer(root);
            while (!q.isEmpty()) {
                Node cur = q.poll();
                System.out.print(cur.val + " ");
                if (cur.left != null)  q.offer(cur.left);
                if (cur.right != null) q.offer(cur.right);
            }
            System.out.println();
        }
    }

    // ====== 测试 ======
    public static void main(String[] args) {
        BinarySearchTree bst = new BinarySearchTree();
        int[] data = {5, 3, 7, 2, 4, 6, 8};
        for (int x : data) bst.insert(x);

        System.out.println("中序 inorder   (应为排序序列):");
        bst.inorder();     // 2 3 4 5 6 7 8

        System.out.println("先序 preorder :");
        bst.preorder();    // 5 3 2 4 7 6 8

        System.out.println("后序 postorder:");
        bst.postorder();   // 2 4 3 6 8 7 5

        System.out.println("层序 levelOrder:");
        bst.levelOrder();  // 5 3 7 2 4 6 8

        System.out.println("高度 height = " + bst.height()); // 3

        System.out.println("contains(4) = " + (bst.contains(4))); // true
        System.out.println("contains(9) = " + (bst.contains(9))); // false

        System.out.println("删除 7 之后的中序：");
        bst.delete(7);
        bst.inorder();     // 2 3 4 5 6 8
        System.out.println("新的高度 height = " + bst.height()); // 3 或 3/2 视删除后结构
    }
}
