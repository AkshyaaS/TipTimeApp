#include<iomanip.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
int turn=2;
class level1{int sno;
				 char q[100];
				 char a[25];
				 public: int ret(){return sno;}
							char* ret1(){return q;}
							char* ret2(){return a;}
							void input(){
											 cout<<"Enter question number:";
											 cin>>sno;
											 cout<<"Enter riddle question:\n";
											 gets(q);
											 cout<<"Enter corresponding answer:\n";
											 cin>>a;}
				}l1;

class level2{int wno;
				 char wor[20];
				 public:int retn(){return wno;}
						  char* retw(){return wor;}
						  void input(){
											cout<<"Enter word number: ";
											cin>>wno;
											cout<<"Enter word:";
											gets(wor);
										  }
			  }l2;

class level3{int sno;
				 public:int q[5][5],a[5][5];
						  int ret(){return sno;}
						  void input();
				}l3;

void level3::input()
{
 int i,j;
 for(i=0;i<5;i++)
  for(j=0;j<5;j++)
  {
	cout<<"\nEnter for "<<(i+1)<<' '<<(j+1)<<": ";
	cin>>q[i][j];
  }
 for(i=0;i<5;i++)
	{
	 for(j=0;j<5;j++)
	  {
		if(q[i][j]==0)
		 cout<<"   ";
		else
		 cout<<q[i][j]<<"  ";
	  }
	 cout<<'\n';
	}
 for(i=0;i<5;i++)
  for(j=0;j<5;j++)
  {
	cout<<"\nEnter for "<<(i+1)<<' '<<(j+1)<<": ";
	cin>>a[i][j];
  }
 for(i=0;i<5;i++)
	{
	 for(j=0;j<5;j++)
	  {
		if(a[i][j]==0)
		 cout<<"   ";
		else
		 cout<<a[i][j]<<"  ";
	  }
	 cout<<'\n';
	}
 getch();
}



void games();

int spinthewheel(int moves)
{
 int a,b,c;
 if(moves==1)
 {
  a=random(2);
  b=random(2);
  c=random(2);
 }
  cout<<"Ready to spin the wheel?\n";
  getch();
  cout<<(a+1)<<'\t'<<(b+1)<<'\t'<<(c+1);
  getch();
  if((a==b)&&(b==c))
  return 1;
  else
  return 0;
}

int sudoku()
{
 int i,n,s,j,posx,posy,num,count=0,a[5][5],b[5][5];
 char ch;
 ifstream f3("sudoku.dat",ios::binary|ios::in);
 if(f3)
 {
  while(f3.read((char*)&l3,sizeof(l3)))
	n++;
  f3.clear();
  f3.seekg(0);
  s=random(n);
  f3.seekg(sizeof(l3)*(s+1),ios::beg);
  if(l3.ret()==(s+1))
  f3.read((char*)&l3,sizeof(l3));
  for(i=0;i<5;i++)
	 for(j=0;j<5;j++)
	 {
		b[i][j]=l3.q[i][j];
		a[i][j]=l3.a[i][j];
	 }
  do
  {
	cout<<'\n'<<"--------------------"<<'\n';
	for(i=0;i<5;i++)
	{
	 for(j=0;j<5;j++)
	  {
		if(b[i][j]==0)
		 cout<<"   "<<'|';
		else
		 cout<<b[i][j]<<"  "<<'|';
	  }
	 cout<<'\n'<<"--------------------"<<'\n';
	}

	cout<<"\nEnter row number and column number into which you want to enter a number\n";
	cin>>posx>>posy;
	cout<<"\nEnter the number to be entered in the above position\n";
	cin>>num;

	if(a[posx-1][posy-1]!=num)
	 cout<<num<<"\nWrong";//,it is "<<a[posx-1][posy-1];
	else
	{
	 //cout<<"copy\n";
	 b[posx-1][posy-1]=num;
	 cout<<"Correct!\n";
	 count++;
	}
	getch();
	clrscr();
	cout<<"If you want to continue enter 'n'. If you are done enter 'y': ";
	cin>>ch;
  }while(ch=='n');
  count=0;

  for(i=0;i<5;i++)
	for(j=0;j<5;j++)
	if(a[i][j]==b[i][j])
	count++;
	cout<<count;

  if(count==25)
  {
	turn=-10;
	cout<<"\nYou won the second level as well!";
  }

  else
  {
	turn-=1;
	cout<<"\nGAME OVER.";
	for(i=0;i<5;i++)
	{
	 for(j=0;j<5;j++)
	  {
		if(a[i][j]==0)
		 cout<<"   ";
		else
		 cout<<a[i][j]<<"  ";
	  }
	 cout<<'\n';
	}
  }
	return count;
 }
else cout<<"File not opened";
}

int riddles()
{
 randomize();
 int i,r[5],j,no=0,ct=0;
 char ans[5],ridques=0,quest[50];
 ifstream f2("riddle.dat",ios::binary|ios::in);
 while(f2.read((char*)&l1,sizeof(l1)))
  no++;
 f2.clear();
 f2.seekg(0);
 for(i=0;i<5;i++)
 {
  r[i]=random(no);
  for(j=0;j<i;j++)
  {
	while(1)
	{
	 if(r[i]==r[j])
	  r[i]=random(no);
	 else
	  break;

	}
  }
  f2.clear();
  f2.seekg(0);

	while(f2.read((char*)&l1,sizeof(l1)))
	 if(l1.ret()==r[i])
	  break;
	 strcpy(quest,l1.ret1());
	 cout<<quest<<'\n';
	gets(ans);
	cout<<'\n';
	if(strcmpi(l1.ret2(),ans)==0)
	{
	 ct++;
	}

	ridques++;
  }
 return ct;
}

void hangman()
{
 int miss=7,i,check,count=0,p,n=0,r;
 char c,word[2],quest[20],answ[20];

 ifstream f2("dictiona.dat",ios::binary|ios::in);
 if(f2)
 {
  while(f2.read((char*)&l2,sizeof(l2)))
	n++;
  f2.clear();
  f2.seekg(0);
  p=random(n)+1;
  while(f2.read((char*)&l2,sizeof(l2)))
  {
	if(l2.retn()==p)
	{
	 strcpy(quest,l2.retw());
	 break;
	}
	count++;
  }
  f2.close();
  for(i=0;i<strlen(quest);i++)
	if(quest[i]==' ')
	 answ[i]=' ';
	else
	answ[i]='_';
	answ[i]='\0';

  while(miss>0)
  {
	check=0;
	for(i=0;i<strlen(quest);i++)
	 cout<<answ[i]<<" ";
	cout<<"\n\n";
	cout<<"Guess a letter: ";
	cin>>c;
	for(i=0;i<strlen(quest);i++)
	{
	 if(quest[i]==c)
	 {
	  cout<<"Correct guess!\n";
	  getch();
	  check=1;
	  answ[i]=c;
	r=strcmpi(answ,quest);
	if(r==0)
	 break;
	 }
	if(r==0)
	break;
  }
	if(check==0)
	{
	 miss-=1;
	 cout<<"miss: "<<miss<<'\n';
	}
	if(r==0)
	 break;
  }
  if(strcmpi(quest,answ)==0)
  {
	clrscr();
	turn=-10;
	cout<<"Full correct!\n";
	cout<<"The word is ";
	for(i=0;i<strlen(quest);i++)
	 cout<<answ[i];
  }
 else
  turn-=1;
}
else
 cout<<"File not opened";
}

void main()
{
 randomize();
 char username[20],password[15];
 int choice;
 cout<<"MENU:\n1.admin\n2.user\n";
 cin>>choice;
 if(choice==1)
 {
  char word[20];
  ifstream f1("admin.txt");
  cout<<"User id: ";
  cin>>username;
  f1>>word;
  if(strcmpi(word,username)==0)
  {
	cout<<"\nPassword: ";
	cin>>password;
	f1>>word;
	if(strcmpi(word,password)!=0)
	{
	 cout<<"Check the entered password";
	 cout<<"\nPassword: ";
	 cin>>password;
	 if(strcmpi(word,password)!=0)
	 exit(0);
	 else
	 {
	  char ch;
	  cout<<"correct!";getch();
	do{
		cout<<"\n\nWhat do u want to do?";
		cout<<"\nMENU:\n1)Add words to hangman dictionary\n2)Add more riddles\n";
	 cout<<"3)Add sudoku\n4)Exit\nEnter choice:";
	cin>>ch;
	if(ch==1)
	{
	 ofstream f2("dictiona.dat",ios::binary|ios::app);
	 char ch;
	 do{
		 l2.input();
		 f2.write((char*)&l2,sizeof(l2));
		 cout<<"Do you want to enter more? Enter y for yes:";
		 cin>>ch;
		}while(ch=='Y'||ch=='y');
	}
	else if(ch==2)
	{
	 ofstream f1("riddle .dat",ios::binary|ios::app);
	 if(f1)
	 {
	  char ch;
	  do
	  {
		l1.input();
		f1.write((char*)&l1,sizeof(l1));
		cout<<"Enter y to enter more:";
		cin>>ch;
	  }while(ch=='y'||ch=='Y');
	  f1.close();
	}
  }
  else if(ch==3)
  {
	ofstream f3("sudoku.dat",ios::binary|ios::app);
	if(f3)
	{
	 char ch;
	 do{
		 l3.input();
		 f3.write((char*)&l3,sizeof(l3));
		 cout<<"Enter y to enter more:";
		 cin>>ch;
		 ch=tolower(ch);
		}while(ch=='y');
	}
  }
  else
	exit(0);
  }while(ch>=1&&ch<=3);
 }

	}
	else
  {
	int ch,num;
	cout<<"correct!";getch();
	do{
		cout<<"\n\nWhat do u want to do?";
		cout<<"\nMENU:\n1)Add words to hangman dictionary\n2)Add more riddles\n";
	 cout<<"3)Add sudoku\n4)Exit\nEnter choice:";
	cin>>ch;
	if(ch==1)
	{
	 ofstream f2("dictiona.dat",ios::binary|ios::app);
	 char ch,word[20];
	 do{
		 l2.input();
		 f2.write((char*)&l2,sizeof(l2));
		 cout<<"Do you want to enter more? Enter y for yes:";
		 cin>>ch;
		}while(ch=='Y'||ch=='y');
	}
	else if(ch==2)
	{
	 ofstream f1("riddle .dat",ios::binary|ios::app);
	 if(f1)
	 {
	  char ch;
	  do
	  {
		l1.input();
		f1.write((char*)&l1,sizeof(l1));
		cout<<"Enter y to enter more:";
		cin>>ch;
	  }while(ch=='y'||ch=='Y');
	  f1.close();
	}
  }
  else if(ch==3)
  {
	ofstream f3("sudoku.dat",ios::binary|ios::app);
	if(f3)
	{
	 char ch;
	 do{
		 l3.input();
		 f3.write((char*)&l3,sizeof(l3));
		 cout<<"Enter y to enter more:";
		 cin>>ch;
		 ch=tolower(ch);
		}while(ch=='y');
	}
  }
  else
	exit(0);
  }while(ch>=1&&ch<=3);
 }
 }
 else
  {
	cout<<"\nID not existing";
	getch();
	exit(0);
  }
 }


 games();
}

void games()
{
 cout<<"Welcome to";
 cout<<'\n'<<'\n'<<'\n'<<'\t'<<'\t'<<'\t';
 cout<<"E-CARNIVAL";
 clrscr();
 int result,spin=1,r;
 randomize();
  cout<<"LEVEL 1:\n";
 cout<<"\t\t\tRIDDLES\n";
 getch();
 clrscr();
 do
 {
  r=riddles();
  if(r>=4)
  {
	turn=-10;
	cout<<"You won the first level of the game!\n";//Points: "<<r<<" /5\n";
	getch();
	break;
  }
  else if(r<4)
  {
	cout<<"lost\n";
	turn-=1;
  }

  getch();
  clrscr();
  if(turn==1)
  {
	cout<<"Try again:):\n";
	r=riddles();
	if(r>=4)
	{
	 turn=-10;
	 cout<<"Won ";//with points: "<<r<<"in second attempt";
	}
	else
	{
	 cout<<"\nOOOPS!Looks like you lost again!";
	 turn=0;
	}
	 break;
  }
 }while(turn==1);
  clrscr();

 if(turn==0)
  {
	cout<<"\nSpinning the wheel of luck.....\n";
	result=spinthewheel(spin);
	if(result==1)
	{
	 cout<<"\nWon moves from spinning the wheel!";
	 riddles();
	}
	else
	{
	 cout<<"\nTough luck.No moves. Better luck next time!:(";
	 exit(0);
	}
  }
  getch();
  clrscr();
  turn=2;
  r=0;
  cout<<"LEVEL 2\n";
  cout<<"\n\n\n\t\t\tSUDOKU\n";
  getch();
  clrscr();

  do
  {
	if(turn==1)
	cout<<"Ooops.. Try again.:)\n";
	r=sudoku();
  }while(turn>0);

  if(turn==0)
  {
	cout<<"spin\n";
	spin=1;
	result=spinthewheel(spin);
	if(result==1)
	{
	 cout<<"You won 1 chance more from spinning the wheel!:)\n";
	 clrscr();
	 sudoku();
	 if(turn==-10)
	 cout<<"You made it! You completed the second level as well!\n";
	}
	else
	 cout<<"Tough luck.You didnt win any moves from spinning the wheel.\n";
	 cout<<"Better luck next time.\n";
	 exit(0);
  }

  cout<<"LEVEL 3, the final level is....:";
  cout<<"\n\n\n\n\t\t\tHANGMAN";
  getch();
  clrscr();
  hangman();
  do
  {
	if(turn==1)
	{
	 clrscr();
	 cout<<"1 chance more\n";
	 hangman();
	}
  }while(turn>0);

  if(turn==-10)
  {
	clrscr();
	cout<<"\n\n\n\tYou made it! You are the Winner!";
	cout<<"You won all three levels!";
	cout<<"\nCongrats and thank you for playing our game!\n";
	exit(0);
  }

  if(turn==0)
  {
	cout<<"Spinning the wheel of luck.....\n";
	spin=1;
	result=spinthewheel(spin);
	if(result==0)
	{
	 cout<<"\nNo moves\nGAME OVER\n";
	 exit(0);
	}
	else
	{
	 cout<<"Won moves from spin the wheel. You can play again!\n";
	 clrscr();
	 hangman();
	 if(turn==-10)
	 cout<<"Finally you made it! You are the Winner!";
	 getch();
	}
  }

}






