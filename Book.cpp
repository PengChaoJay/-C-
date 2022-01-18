#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#define N sizeof(struct BOOK)
#define M sizeof(struct STU)
#define H sizeof(struct READ)

struct BOOK        //图书信息 
{
	char number[10];   //登录号 
	char name[20];     //书名 
	char author[20];    //作者名  
	int num;       //总数量 
	int x;
	struct BOOK *next;   //指针域 
};
typedef struct BOOK Book;
typedef Book *book;	

struct READ        //图书信息 
{
	char name[20];     //书名   
	char reader[30];    //借阅人学号
	int nownum;        //图书库存量
	int readnum;       //图书借阅量
	int x;
	struct READ *next;   //指针域 
};
typedef struct READ Read;
typedef Read *read;	

struct STU        //图书信息 
{
	char number[10];   //学号
	char name[20];    //书名
	int num;         //图书借阅总次数
	int x;
	struct STU *next;   //指针域 
};
typedef struct STU Stu;
typedef Stu *stu;	

void HideCursor();    //隐藏光标
void toxy(int x, int y);    //将光标移动到X,Y坐标处
void color();     //设置颜色
void juese();//选择角色
void library();//管理员登录
void menubook();//图书管理菜单
void menustudent();//借阅人管理菜单
void menu();   //菜单
void menu2();  //借阅人菜单
void input_book();     //图书入库 
void book_rendjy(char _name[],char _reader[]);  //借书-图书借阅情况文件
void stuborrow(char _name[],char _reader[]);   //借书-学生借阅情况文件
void book_rend();  //借书
void save_book(book p);//将图书信息存入文件
void changebook();//修改图书信息
void student();//借阅人登录界面
void find_book();//查询图书
void find_student();//个人借阅图书情况查询
void jyqk();  //借阅情况查询
void input_stu();     //借阅人信息入库 
void save_stu(stu p);//将学生学号存入文件
stu ss();
read aa();
book bb();


void HideCursor()     //隐藏光标
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void color()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);//将输出句柄定义颜色
} 

void toxy(int x, int y)      //将光标移动到X,Y坐标处
{
	COORD pos = { x , y };
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out, pos); 
}

void roles()
{
	char t;
	do
	{
		system("cls");
		HideCursor();  //隐藏光标 
		color();    //设置一个颜色
		printf(" 图书信息管理系统-登录");
		toxy(50,5);//将光标移动到（50，5）坐标处
		toxy(48,8);//打印菜单
		printf("1.管理员");
		toxy(48,10);
		printf("2.借阅人");
		toxy(48,16);
		printf("请选择：");
		t=getchar();
		switch(t)
		{
			case '1':library();break;
			case '2':student();break;
			default :break;
		}
	}while(1);
}

void menu()    //菜单 
{
	char a;
	do
	{
		system("cls");  //清屏 
		HideCursor();  //隐藏光标 
		color();    //设置一个颜色 
		toxy(50,5);//将光标移动到（50，5）坐标处
		printf(" 图书信息管理系统-管理员");
		toxy(48,8);//打印菜单
		printf("|     1.图书管理      |");
		toxy(48,10);
		printf("|     2.借阅人管理    |");
		toxy(48,12);
		printf("|     3.退出系统      |");
		toxy(48,18);
		printf("请选择：");
		a=getchar();
		switch(a)
		{
			case '1':menubook();break;
			case '2':menustudent();break;
			case '3':juese();break;
		}
	}while(1);
} 

void menu2()
{
	char c;
	do
	{
		system("cls");  //清屏 
		HideCursor();  //隐藏光标 
		color();    //设置一个颜色 
		toxy(50,5);//将光标移动到（50，5）坐标处
		printf(" 图书信息管理系统-借阅人");
		toxy(48,8);//打印菜单
		printf("|     1.图书查询      |");
		toxy(48,10);
		printf("|     2.个人信息      |");
		toxy(48,12);
		printf("|     3.退出系统      |");
		toxy(48,18);
		printf("请选择：");
		c=getchar();
		switch(c)
		{
			case '1':find_book();break;
			case '2':find_student();break;
			case '3':juese();break;
		}
	}while(1);
}

void menustudent()    //菜单 
{
	char a;
	do
	{
		system("cls");  //清屏 
		HideCursor();  //隐藏光标 
		color();    //设置一个颜色 
		toxy(50,5);//将光标移动到（50，5）坐标处
		printf(" 图书信息管理系统-管理员-借阅人信息");
		toxy(48,8);//打印菜单
		printf("|   1.借阅人信息录入    |");
		toxy(48,10);
		printf("|   2.个人借阅情况查询  |");
		toxy(48,12);
		printf("|   3.退出系统          |");
		toxy(48,18);
		printf("请选择：");
		a=getchar();
		switch(a)
		{
			case '1':input_stu();break;
			case '2':find_student();break;
			case '3':juese();break;
		}
	}while(1);
} 

void input_stu()    //借阅人录入 
{
	char t;
	stu p;
	do
	{
		system("cls");
		color();
		p=(stu)malloc(N);     //申请空间 
		//输入图书信息
		toxy(48,8);
		printf("请输入学生学号：");    
		scanf("%s",p->number);getchar();
		toxy(48,10);
		printf("请输入借阅图书：");
		scanf("%s",p->name);getchar();
		toxy(48,12);
		printf("请输入图书借阅总次数：");
		scanf("%d",&p->num);getchar();
		save_stu(p);
		toxy(48,14);
		printf("正在保存....");
		Sleep(500);   //暂停0.5秒 
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("| 保存成功！是否继续？  |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)    //利用死循环可有效防止其他按键干扰 
		{
			t=getchar();
			if(t=='1')
			{
				break;
			 } 
			 else if(t=='2')
			 {
			 	menustudent();
			 }
		}
	}while(1);
	
} 

void student()
{
	do
	{
		stu head;
		stu b;
		int i=13,j=0,x=0;
		char ch;
		FILE *fp=fopen("C:\\Users\\dll\\Desktop\\stu","r");    //文件指针 
		char _number[10];
		char number[10];   //学号
		head=ss();
		b=head;
		system("cls");
		toxy(48,10);
		printf("请输入你的学号：");
		scanf("%s",_number); 
		while(b!=NULL)    //初始化p->x为0 
		{
			b->x=0;
			b=b->next;
		}
		b=head;    //让p重新指向表头 
		toxy(20,5);
		while(b!=NULL)
		{
			if(b!=NULL&&strcmp(b->number,_number)==0)
			{
				toxy(20,i);
				j++;
				printf("                             存在该学号，进入系统！");
				Sleep(500);
				menu2();
				break;
			}
			b=b->next;
		}
		if(j==0)                   //如果j=0，即没有进入前面的搜索循环，也就是没有找到相应的信息 
		{ 
			toxy(48,i);
			printf("没有找到相应的信息！(按0返回，按1重新搜索)");
			while(1)               //死循环是为了防止除0和1的其他按键干扰 
			{
				ch=getchar();
				if(ch=='0')
				{
					menu();break;
				}
				else if(ch=='1')
				{
					break;
				}
			}
			if(ch=='1')     //如果输入的ch等于1，则结束本次循环 
			   continue;
		}
		b=head;     //让p重新指向表头 
		while(b!=NULL&&b->x!=x)   //遍历链表查询符合条件的结点 
		{
			b=b->next;
		}
		system("cls");
		fclose(fp);   //关闭文件 
		break;
	}while(1);
}

void juese()
{
	char t;
	do
	{
		system("cls");
		HideCursor();  //隐藏光标 
		color();    //设置一个颜色
		printf(" 图书信息管理系统-登录");
		toxy(50,5);//将光标移动到（50，5）坐标处
		toxy(48,8);//打印菜单
		printf("1.管理员");
		toxy(48,10);
		printf("2.借阅人");
		toxy(48,16);
		printf("请选择：");
		t=getchar();
		switch(t)
		{
			case '1':library();break;
			case '2':student();break;
			default :break;
		}
	}while(1);
}

void menubook()
{
	char b;
	do
	{
		system("cls");  //清屏 
		HideCursor();  //隐藏光标 
		color();    //设置一个颜色 
		toxy(50,5);//将光标移动到（50，5）坐标处
		printf(" 图书管理界面");
		toxy(48,8);//打印菜单
		printf("|     1.图书入库        |");
		toxy(48,10);
		printf("|     2.借阅图书        |");
		toxy(48,12);
		printf("|     3.归还图书        |");
		toxy(48,14);
		printf("|     4.图书查询        |");
		toxy(48,16);
		printf("|     5.信息修改        |");
		toxy(48,18);
		printf("|     6.信息删除        |");
		toxy(48,20);
		printf("|     7.图书借阅情况查询|");
		toxy(48,22);
		printf("|     8.返回上一级菜单  |");
		toxy(48,24);
		printf("请选择：");
		b=getchar();
		switch(b)
		{
			case '1':input_book();break;
			case '2':book_rend();break;
			case '4':find_book();break;
			case '5':changebook();break;
			case '7':jyqk();break;
			case '8':menu();break;
		}
	}while(1);
} 

void library()
{
  int i,flag1,flag2;                                              //i表示输入用户名与密码的次数
  char name[20]="li",password[10]="123456";     //建立字符数组，存放管理员的用户名与密码
  char person[20],password1[10];       //建立字符数组，存放输入的用户名与密码
  for(i=1;i<4;)                                                         //输错三次后自动退出系统
  {   
	  system("cls");  //清屏 
	  HideCursor();  //隐藏光标 
	  color();    //设置一个颜色 
	  toxy(50,5);//将光标移动到（50，5）坐标处
	  printf(" 图书信息管理系统-管理员");
	  toxy(48,8);
	  printf("请输入你的用户名:\n");//提示输入用户名
	  toxy(48,10);
      scanf("%s",person);                                                     //读取用户名
      flag1=strcmp(person,name); //比较两个字符串，即比较输入的用户名与管理员的用户名是否一致，并返回结果到flag1
	  toxy(48,12);
	  printf("请输入你的密码:\n"); //提示输入密码
	  toxy(48,14);
	  scanf("%s",password1);                                                  //读取密码
	  flag2=strcmp(password,password1);                                 //比较两个字符串，即比较输入的用户名与管理员的密码是否一致，并返回结果到flag2
	  if(flag1==0&&flag2==0) 
	  {
		  toxy(48,16);
		  printf("登陆成功\n"); //用户名与密码都正确，则成功进入系统
          menu();
		  break;
	  }
	  else
	  {
		  toxy(48,16);
		  printf("用户名或密码错误!\n");       //提示用户名或密码错误
		  i++;                                                          //重新输入信息
	  }
  }
}

void jyqk()
{
	do
	{
		int k=1;
		read head;
		read h;
		int i=11,j=0,x;
		char ch;
		FILE *fp;    //文件指针 
		char _name[20];
		char readr[30];   //借阅人
		char name[20];     //书名 
		int nownum;        //图书库存量
		int readnum;       //图书借阅量
		head=aa();
		h=head;
		system("cls");
		color();
		toxy(48,10);
		printf("请输入你要查询的图书的名称：");
		gets(_name); 
		while(h!=NULL)    //初始化h->x为0 
		{
			h->x=0;
			h=h->next;
		}
		h=head;    //让h重新指向表头 
		toxy(20,5);
		printf("*************************************图书借阅情况信息**************************************");
		toxy(20,8);
		printf("------------------------------------------------------------------------------------------ ");
		toxy(20,9);
		printf("书名        借阅人        库存数量        借阅数量");
		toxy(20,10);
		printf("-------------------------------------------------------------------------------------------");
		while(h!=NULL)
		{
			if(h!=NULL&&strcmp(h->name,_name)==0)
			{
				toxy(20,i);
				j++;
				printf("%d:%s%14s%12d%12d\n",j,h->name,h->reader,h->nownum,h->readnum);
				h->x=j;    //给符合查询标准的结点标号 
				i++;
				toxy(48,18);
				printf("是否要继续查询：");
				toxy(48,20);
				printf("1.继续   2.返回上一级菜单");
				toxy(48,22);
				printf("请选择：");
				scanf("%d",&k);
				if(k==2)
				{
					menubook();
				}
			}
			h=h->next;
		}
		if(j==0)                   //如果j=0，即没有进入前面的搜索循环，也就是没有找到相应的信息 
		{ 
			toxy(48,i+6);
			printf("没有找到相应的信息！(按0返回，按1重新搜索)");
			while(1)               //死循环是为了防止除0和1的其他按键干扰 
			{
				ch=getch();
				if(ch=='0')
				{
					menu();break;
				}
				else if(ch=='1')
				{
					break;
				}
			}
			if(ch=='1')     //如果输入的ch等于1，则结束本次循环 
			   continue;
		}
	}while(1);
}

stu ss()      //将文件中的内容读出到链表中，返回值为表头地址 
{
	FILE *fp;       //文件指针 
	int n=0;
	stu head=NULL;
	stu b2,b,br=NULL;
	fp=fopen("C:\\Users\\dll\\Desktop\\stu.txt","a+");     //以只读的方式打开文件 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(fp))        //判断文件位置标志是否移动到文件末尾 
	{
	   n++;
	   	b=(stu)malloc(M); //向内存申请一段空间 
	   fscanf(fp,"%s\t%s\t%6d\n",b->number,b->name,&b->num);     //将fp所指向的文件中的内容赋给p 
	   if(n==1)
	   {
	      head=b;
	      b2=b;
	    }
	    else             //创建链表 
	    {
	    	br=b2;
	    	b2->next=b;
	    	b2=b;
		}
    }
    if(br!=NULL)
       br->next=NULL;
    else
       head=NULL;
    fclose(fp);    //关闭文件 
    return head;   //返回头指针 
}

read aa()      //将文件中的内容读出到链表中，返回值为表头地址 
{
	FILE *fp;       //文件指针 
	int n=0;
	read head=NULL;
	read h2,h,hr=NULL;
	fp=fopen("C:\\Users\\dll\\Desktop\\jyqk.txt","a+");     //以只读的方式打开文件 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(fp))        //判断文件位置标志是否移动到文件末尾 
	{
	   n++;
	   h=(read)malloc(H); //向内存申请一段空间 
	   fscanf(fp,"%s\t%s\t%6d%6d\n",h->name,h->reader,&h->nownum,&h->readnum);     //将fp所指向的文件中的内容赋给p    //将fp所指向的文件中的内容赋给p 
	   if(n==1)
	   {
	      head=h;
	      h2=h;
	    }
	    else             //创建链表 
	    {
	    	hr=h2;
	    	h2->next=h;
	    	h2=h;
		}
    }
    if(hr!=NULL)
       hr->next=NULL;
    else
       head=NULL;
    fclose(fp);    //关闭文件 
    return head;   //返回头指针 
}

book bb()      //将文件中的内容读出到链表中，返回值为表头地址 
{
	FILE *fp;       //文件指针 
	book head = NULL;
	book p, p2;

	if ((fp = fopen("C:\\Users\\dll\\Desktop\\mybook.txt", "a+")) == NULL) //以只读的方式打开文件 ，前面用了宏定义省略了路径
	{                       
		printf("cannot open file\n");
		return NULL;
	}

	while (!feof(fp)) 
	{                         //判断文件位置标志是否移动到文件末尾 
		p = (book)malloc(N); //向内存申请一段空间 
		if (fscanf(fp, "%s%s%s%d", p->number, p->name, p->author, &p->num) == 4) 
		{                        //将fp所指向的文件中的内容赋给p 
			if (head == NULL)
			{
				head = p;
			}
			else
			{
				p2->next = p;
			}
			p2 = p;
			p2->next = NULL;
			
		}
	}
	fclose(fp);    //关闭文件 
	return head;   //返回头指针 
}

void input_book()    //图书录入 
{
	char t;
	book p;
	do
	{
		system("cls");
		color();
		p=(book)malloc(N);     //申请空间 
		//输入图书信息
		toxy(48,8);
		printf("请输入图书登录号(小于10位数)：");    
		scanf("%s",p->number);getchar();
		toxy(48,10);
		printf("请输入书名(小于10位数)：");
		scanf("%s",p->name);getchar();
		toxy(48,12);
		printf("请输入作者名(小于10位数)：");
		scanf("%s",p->author);getchar();
		toxy(48,14);
		printf("请输入图书总数量：");
		scanf("%d",&p->num);getchar();
		save_book(p);
		toxy(48,20);
		printf("正在保存....");
		Sleep(500);   //暂停0.5秒 
		system("cls");
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("| 保存成功！是否继续？  |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)    //利用死循环可有效防止其他按键干扰 
		{
			t=getchar();
			if(t=='1')
			{
				break;
			 } 
			 else if(t=='2')
			 {
			 	menubook();
			 }
		}
	}while(1);
	
} 

void save_book(book p)   //将p中内容写入文件 
{
	FILE *fp;    //文件指针 
	fp=fopen("C:\\Users\\dll\\Desktop\\mybook.txt","a");   //以追加的方式打开名字为mybook的文件 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	else
	{
		fprintf(fp,"%s\t%s\t%s\t%6d\n",p->number,p->name,p->author,p->num);
	}
	fclose(fp);    //关闭文件  
 }

void save_stu(stu b)   //将p中内容写入文件 
{
	FILE *fp;    //文件指针 
	fp=fopen("C:\\Users\\dll\\Desktop\\stu.txt","a");   //以追加的方式打开名字为stu文件 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	if(fprintf(fp,"%s\t%s\t%6d\n",b->number,b->name,b->num)!=1)   //将p所指向的一段大小为N的内容存入fp所指向的文件中 
	{
		printf("write error");
	}
	fclose(fp);    //关闭文件  
 }

void find_book()
{
	do
	{
		int k=1;
		book head;
		book p;
		int i=11,j=0,x;
		char ch,t;
		FILE *fp;    //文件指针 
		char _name[20];
		char number[10];   //登录号 
		char name[20];     //书名 
		char author[20];    //作者名 
		int num;         //数量 
		head=bb();
		p=head;
		system("cls");
		color();
		toxy(48,10);
		printf("请输入你要查询的图书的名称：");
		gets(_name); 
		while(p!=NULL)    //初始化p->x为0 
		{
			p->x=0;
			p=p->next;
		}
		p=head;    //让p重新指向表头 
		toxy(20,5);
		printf("*************************************图书信息*********************************************");
		toxy(20,8);
		printf("------------------------------------------------------------------------------------------ ");
		toxy(20,9);
		printf("登录号        书名        作者名        数量");
		toxy(20,10);
		printf("-------------------------------------------------------------------------------------------");
		while(p!=NULL)
		{
			if(p!=NULL&&strcmp(p->name,_name)==0)
			{
				toxy(20,i);
				j++;
				printf("%d:%s%14s%14s%12d\n",j,p->number,p->name,p->author,p->num);
				p->x=j;    //给符合查询标准的结点标号 
				i++;
				toxy(48,18);
				printf("是否需要继续查询：");
				toxy(48,20);
				printf("1.继续    ；2.返回上一级菜单");
				toxy(48,22);
				printf("请选择：");
				scanf("%d",&k);
				if(k==2)
				{
					menubook();
				}
			}
			p=p->next;
		}
		if(j==0)                   //如果j=0，即没有进入前面的搜索循环，也就是没有找到相应的信息 
		{ 
			toxy(50,i);
			printf("没有找到相应的信息！(按0返回，按1重新搜索)");
			while(1)               //死循环是为了防止除0和1的其他按键干扰 
			{
				ch=getch();
				if(ch=='0')
				{
					menu();break;
				}
				else if(ch=='1')
				{
					break;
				}
			}
			if(ch=='1')     //如果输入的ch等于1，则结束本次循环 
			   continue;
		}
	}while(1);
}

void find_student()
{
	do
	{
		int k=1;
		stu head;
		stu b;
		int i=11,j=0,x;
		char ch,t;
		FILE *fp;    //文件指针 
		char _number[10];
		char number[10];   //登录号 
		char name[20];     //书名 
		int num;         //图书借阅总次数 
		head=ss();
		b=head;
		system("cls");
		color();
		toxy(48,10);
		printf("请输入你的学号：");
		gets(_number); 
		while(b!=NULL)    //初始化p->x为0 
		{
			b->x=0;
			b=b->next;
		}
		b=head;    //让p重新指向表头 
		toxy(20,5);
		printf("*************************************图书信息*********************************************");
		toxy(20,8);
		printf("------------------------------------------------------------------------------------------ ");
		toxy(20,9);
		printf("学号                              书名                              图书借阅总次数         ");
		toxy(20,10);
		printf("-------------------------------------------------------------------------------------------");
		while(b!=NULL)
		{
			if(b!=NULL&&strcmp(b->number,_number)==0)
			{
				toxy(20,i);
				j++;
				printf("%d:%s%20s%18d\n",j,b->number,b->name,b->num);
				b->x=j;    //给符合查询标准的结点标号 
				i++;
				toxy(48,18);
				printf("是否返回上一级菜单：");
				toxy(48,20);
				printf("1.是    2.否");
				toxy(48,22);
				printf("请选择：");
				scanf("%d",&k);
				if(k==1)
				{
					menustudent();
				}
			}
			b=b->next;
		}
	}while(1);
}

void changebook()
{
	book p;
	char ch, t;
	FILE *fp;
	char _name[20];
	book head = bb();
	int row = 11;
	int number = 0;
	char n[20];
	Book b;
	do
	{
		system("cls");
		color();
		toxy(48, 10);
		printf("请输入你要修改的图书的名称：");
		scanf("%s", _name);
		toxy(20, 5);
		printf("*************************************图书信息*********************************************");
		toxy(20, 8);
		printf("------------------------------------------------------------------------------------------ ");
		toxy(20, 9);
		printf("%14s%14s%14s%12s\n", "编号", "书名", "作者名", "数量");
		toxy(20, 10);
		printf("-------------------------------------------------------------------------------------------");
		
		for (p = head; p; p = p->next)
		{
			if (!strcmp(p->name, _name))
			{
				toxy(20, row++);
				++number;
				printf("%14s%14s%14s%12d\n", p->number, p->name, p->author, p->num);
			}
		}
		if (number == 0) 
		{       //如果number=0，即没有进入前面的搜索循环，也就是没有找到相应的信息 
			toxy(50, row);
			printf("没有找到相应的信息！(按0返回，按1重新搜索)");
			do 
			{
				ch = getchar();
			} while (ch != '0' && ch != '1');

			if (ch == '0')
			{
				return;
			}
			else
			{
				continue;
			}
		}
		while (1)
		{
			toxy(45, row);
			printf("请输入您要修改的图书的编号：");
			scanf("%s", n);

			for (p = head; p; p = p->next)
				if (!strcmp(p->number, n))
					break;
			if (!p) {
				toxy(45, row);
				printf("请输入您要修改的图书的编号：          ");
				toxy(45, row + 1);
				printf("                     ");
			}
			else {
				break;
			}
		}
		//Sleep(2000);
		//char n[20];
		//Sleep(2000);
		//Book b;
		system("cls");
		//输入要修改的信息 
		toxy(48, 8);
		printf("请输入图书登录号(小于10位数)：");
		scanf("%s", b.number);
		toxy(48, 10);
		printf("请输入书名(小于10位数)：");
		scanf("%s", b.name);
		toxy(48, 12);
		printf("请输入作者名(小于10位数)：");
		scanf("%s", b.author);
		toxy(48, 14);
		printf("请输入图书数量：");
		scanf("%d", &b.num);
        //判断是否修改
		color();
		toxy(46, 8);
		printf("-------------------------");
		toxy(46, 9);
		printf("|                       |");
		toxy(46, 10);
		printf("|     是否确认修改？    |");
		toxy(46, 12);
		printf("| 1.是             2.否 |");
		toxy(46, 13);
		printf("|                       |");
		toxy(46, 14);
		printf("-------------------------");
		do 
		{
			t = getchar();
		} while (t != '1' && t != '2');
		if (t == '2')
		{
			return;//具体的还不确定
		}
		//字符串复制函数，将源字符串复制到目标字符串中
		strcpy(p->name, b.name);
		strcpy(p->number, b.number);
		strcpy(p->author, b.author);
		p->num = b.num;
		system("cls");
		toxy(46, 10);
		printf("正在修改，请稍后....");
		fp = fopen("C:\\Users\\dll\\Desktop\\mybook.txt", "w");   //以只写的方式打开名为mybook，打开的同时清空文件中的内容 
		if (fp == NULL)
		{
			printf("cannot open file");
			return;
		}
		for (p = head; p; p = p->next)
		{
			fprintf(fp, "%s\t%s\t%s\t%6d\n", p->number, p->name, p->author, p->num);
		}
		fclose(fp);   //关闭文件 
		Sleep(500);   //暂停0.5秒 
		system("cls");
		toxy(46, 10);
		printf("修改成功！即将自动返回主菜单....");
		Sleep(500);
		break;
	} while (1);
}

void book_rendjy(char _name[],char _reader[])
{
	do
	{
		read head;
		read h;
		int j=0;
		char ch,t;
		FILE *fp;    //文件指针 
		char reader[30];   //学号
		char name[20];     //书名 
		int nownum;    //现存数量
		int readnum;         //借阅数量
		head=aa();
		/*h=head;
		while(h!=NULL)    //初始化p->x为0 
		{
			h->x=0;
			h=h->next;
		}*/
		h=head;    //让p重新指向表头 
		while(h!=NULL)
		{
			if(h!=NULL&&strcmp(h->name,_name)==0)
			{
				j++;
				system("cls");
				h->nownum=h->nownum-1;
				h->readnum=h->readnum+1;
				strcat(h->reader,_reader);
			}
			h=h->next;
		}
		if(j==0)                   //如果j=0，即没有进入前面的搜索循环，也就是没有找到相应的信息 
		{ 
			toxy(48,16);
			printf("没有找到相应的图书！(按0返回，按1重新搜索)");
			while(1)               //死循环是为了防止除0和1的其他按键干扰 
			{
				ch=getch();
				if(ch=='0')
				{
					break;
				}
				else if(ch=='1')
				{
					break;
				}
			}
			if(ch=='1')     //如果输入的ch等于1，则结束本次循环 
			   continue;
		}
		h=head;
		color();
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|     是否确认借阅？    |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)   //利用死循环防止其他按键干扰 
		{
			t=getch();
			if(t=='1')
			{
				break;
			} 
			else if(t=='2')
			{
				break;
			}
		}
		system("cls");
		toxy(46,10);
		printf("正在借阅，请稍后....");
		fp=fopen("C:\\Users\\dll\\Desktop\\jyqk.txt","w");   //以只写的方式打开名为mybook，打开的同时清空文件中的内容 
		if(fp==NULL)
		{
			printf("cannot open file"); 
		}
		if(fprintf(fp,"%s\t%s\t%6d%6d\n",h->name,h->reader,h->nownum,h->readnum)!=1)   //将head写入fp所指向的文件中 
		{
			printf("write error!"); 
		}
		fclose(fp);   //关闭文件 
		if(head!=NULL)   //如果head不为空 
		{
			h=head->next;     //让p指向第二个结点 
			fp=fopen("C:\\Users\\dll\\Desktop\\jyqk.txt","a");   //以追加的方式打开文件 
			if(fp==NULL)
			{
				printf("cannot open file");
			}
			while(h!=NULL)
			{
				if(fprintf(fp,"%s\t%s\t%6d%6d\n",h->name,h->reader,h->nownum,h->readnum)!=1)//将p写入fp所指向的文件中
				{
					printf("write error!");
				}
				h=h->next;
			}
			fclose(fp);  //关闭文件 
		}
		Sleep(500);   //暂停0.5秒 
		system("cls");
		toxy(46,10);
		printf("修改成功！即将自动返回主菜单....");
		Sleep(500);
		break;
	}while(1);
}

void stuborrow(char _name[],char _number[])
{
		do
	{
		stu head;
		stu b;
		int j=0;
		char ch,t;
		FILE *fp;    //文件指针 
		char number[30];//学号                                         
		char name[20];//已借阅的图书名
	    int num;//借阅总次数
		head=ss();
		b=head;
		while(b!=NULL)    //初始化p->x为0 
		{
			b->x=0;
			b=b->next;
		}
		b=head;     //让p重新指向表头 
		while(b!=NULL)   //遍历链表查询符合条件的结点 
		{
			if(b!=NULL&&strcmp(b->number,_number)==0)
			{
				j++;
				system("cls");
				b->num=b->num+1;
				strcpy(b->name,_name);
			}
			b=b->next;
		}
		if(j=0) //j=0,则没有找到相应的信息
		{
			toxy(48,16);
			printf("没有找到相应的图书！（按0返回，按1重新搜索）");
			while(1)
			{
				ch=getch();
				if(ch=='0')
				{
					break;
				}
				else if(ch=='1')
				{
					break;
				}
			}
			if(ch=='1')
				continue;
		}
		b=head;
		color();
		toxy(46,8);
		printf("-------------------------");
		toxy(46,9);
		printf("|                       |");
		toxy(46,10);
		printf("|     是否确认借阅？    |");
		toxy(46,12);
		printf("| 1.是             2.否 |");
		toxy(46,13);
		printf("|                       |");
		toxy(46,14);
		printf("-------------------------");
		while(1)   //利用死循环防止其他按键干扰 
		{
			t=getch();
			if(t=='1')
			{
				break;
			} 
			else if(t=='2')
			{
				break;
			}
		}
		system("cls");
		toxy(46,10);
		printf("正在借阅，请稍后....");
		fp=fopen("C:\\Users\\dll\\Desktop\\stu.txt","w");   //以只写的方式打开名为stu，打开的同时清空文件中的内容 
		if(fp==NULL)
		{
			printf("cannot open file"); 
		}
		if(fprintf(fp,"%s\t%s\t%6d\n",b->number,b->name,b->num)!=1)   //将head写入fp所指向的文件中 
		{
			printf("write error!"); 
		}
		fclose(fp);   //关闭文件 
		if(head!=NULL)   //如果head不为空 
		{
			b=head->next;     //让b指向第二个结点 
			fp=fopen("C:\\Users\\dll\\Desktop\\stu.txt","a");   //以追加的方式打开文件 
			if(fp==NULL)
			{
				printf("cannot open file");
			}
			while(b!=NULL)
			{
				if(fprintf(fp,"%s\t%s\t%6d\n",b->number,b->name,b->num)!=1)//将p写入fp所指向的文件中
				{
					printf("write error!");
				}
				b=b->next;
			}
			fclose(fp);  //关闭文件 
		}
		Sleep(500);   //暂停0.5秒 
		system("cls");
		toxy(46,10);
		printf("借阅成功！即将自动返回主菜单....");
		Sleep(500);
		break;
	}while(1);
}

void book_rend()
{
	char _name1[20];
	char _reader1[30];
	system("cls");  //清屏 
	HideCursor();  //隐藏光标 
	color();    //设置一个颜色 
	toxy(50,5);//将光标移动到（50，5）坐标处
	printf(" 借阅图书界面");
	toxy(48,10);
	printf("请输入你要借阅的图书的名称：");
	scanf("%s",_name1); 
	toxy(48,12);
	printf("请输入你的学号：");
	scanf("%s",_reader1);
	book_rendjy(_name1,_reader1);
	stuborrow(_name1,_reader1);
}

int main()
{
	int m=1;//1代表返回的是管理员的菜单，若想要返回借阅人的菜单，在子函数中提前改为m=2
	juese();
}