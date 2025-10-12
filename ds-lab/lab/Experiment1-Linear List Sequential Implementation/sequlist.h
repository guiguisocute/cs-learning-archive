#include  <stdio.h>
#include  <stdlib.h>
/************************************/
/*顺序表的头文件，文件名sequlist.h*/
/************************************/
 #define MAXSIZE 100
 typedef int datatype;  //属于一改改所有了
 typedef struct{
   datatype a[MAXSIZE];
   int size;
 }sequence_list;        //一个开辟了数组加上数组大小的结构体，就能算作是顺序表吗

/**********************************/
/*函数名称：initseqlist()         */
/*函数功能：初始化顺序表          */
/**********************************/
void initseqlist(sequence_list *L)
{	L->size=0;
}
/**********************************/
/*函数名称：input()               */
/*函数功能：输入顺序表            */
/**********************************/
void input(sequence_list *L)  //终端扫描的版本
{  datatype x;
   initseqlist(L);
   printf("请输入一组数据，以0做为结束符：\n");
   scanf("%d",&x);
   while (x)
   	{	L->a[L->size++]=x;
		     scanf("%d",&x);
	     }
}
/**********************************/
/*函数名称：inputfromfile()       */
/*函数功能：从文件输入顺序表      */
/**********************************/
void inputfromfile(sequence_list *L,char *f)
{  int i,x;
   FILE *fp=fopen(f,"r");  //“r”是只读的意思，f是指向 文件名字 的字符串指针，到时候传参时f就直接写文件名就行
   L->size=0;
   if (fp)
   {   while ( ! feof(fp))    //feof：检测文件是否已经到达了末尾，如果到了末尾就返回非0，没到末尾就返回0
        {
            fscanf(fp,"%d",&L->a[L->size++]);   //从文件 fp 中读取一个整数，并将其存储到顺序表 L 的数组 a 中。L->size++ 表示每次读取一个整数后，顺序表的大小 size 增加 1
        }
        fclose(fp);
   }
}
/**********************************/
/*函数名称：print()               */
/*函数功能：输出顺序表            */
/**********************************/
void print(sequence_list *L)
{   int i;
    for (i=0;i<L->size;i++)
       {    printf("%5d",L->a[i]);     //将一个整数输出为至少占 5 个字符的宽度。如果整数的位数不足 5 位，会在左侧填充空格以补足宽度。
            if ((i+1)%10==0) printf("\n");
       }
    printf("\n");
}

