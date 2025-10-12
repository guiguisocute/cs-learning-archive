/*假设顺序表la与lb分别存放两个整数集合，函数inter(seqlist *la,seqlist *lb,seqlist *lc)
的功能是实现求顺序表la与lb的交集存放到顺序表lc中,请将函数补充完整.  */

/**********************************/
/*文件名称：lab1_04.c                 */
/**********************************/
#include "sequlist.h"
/*请将本函数补充完整，并进行测试*/
// int search(sequence_list *l,datatype x)
// {
//         int j=l->size-1;
//         while (j>=0 && l->a[j]!=x)   //在l中查找x
//                     j--;
//         if (j>=0) return 1;
//         else return 0;
// }
int compare(const void *a, const void *b) {
    int x = *(const datatype *)a;
    int y = *(const datatype *)b;
    return (x > y) - (x < y); 
}


void inter (sequence_list *la, sequence_list *lb, sequence_list *lc) {

    qsort(la->a, la->size, sizeof(datatype), compare);
    qsort(lb->a, lb->size, sizeof(datatype), compare);

    int i = 0, j = 0, k = 0; 
    while (i < la->size && j < lb->size) {
        if (la->a[i] == lb->a[j]) {

            if(k == 0 || lc->a[k - 1] != la->a[i])      //去个重
            lc->a[k++] = la->a[i];
            i++;
            j++;
        } else if (la->a[i] < lb->a[j]) {
            i++;
        } else {
            j++;
        }               //大的“等”一下小的
    }

    lc->size = k; //最后更新一下顺序表的大小
}

int main()
{
  sequence_list la,lb,lc;
  inputfromfile(&la,"1.txt"); 		/*从文件1.txt建立顺序表*/
  inputfromfile(&lb,"2.txt");		/*从文件2.txt建立顺序表*/
  print(&la); 				 	    /*输出la*/
  print(&lb);  				        /*输出lb*/
  inter(&la,&lb,&lc);   		    /*求la与lb的交集存于lc中*/
  print(&lc); 					    /*输出lc*/
  return 0;
}
