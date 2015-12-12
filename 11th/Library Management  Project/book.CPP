#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>

int count_book;  //Global variable to count number of book

class book      //class book
{
	  int bookno;
          char bookname[50];
	  char author[50];
          char publisher[50];
	  int pages;
	  int copies;
          float price;

	  public:
	  int getno() {return bookno;}
          char * getname() {return bookname;}
	  void getbook();
	  void displaybook();
	  void mod_book();
};

void book::getbook()   //read book details
{
cout<<"\nRecord#"<<(++count_book)<<endl;
cout<<"\nEnter book number...";
cin>>bookno;
cout<<"Enter bookname...";
gets(bookname);
cout<<"Enter author...";
gets(author);
cout<<"Enter publisher..";
cin>>publisher;
cout<<"Enter pages...";
cin>>pages;
cout<<"Enter number of copies available...";
cin>>copies;
cout<<"Enter price:";
cin>>price;
}

void book::displaybook()  //display book details
{ cout<<"\n-------------------------------\n";
cout<<"\nBook number:"<<bookno;
cout<<"\nBook name:"<<bookname;
cout<<"\nAuthor:"<<author;
cout<<"\nPublisher:"<<publisher;
cout<<"\nPages:"<<pages;
cout<<"\nNumber of copies:"<<copies;
cout<<"\nPrice:"<<price;
}

void book::mod_book()     //modify book details
{ clrscr();
char nm[50],auth[50],publ[50];
int num,page,noc;
float pr;

cout<<"\nCurrent details\n";
cout<<"\nBookno:"<<bookno<<"\nBookName:"<<bookname;
cout<<"\nAuthor:"<<author<<"\nPublisher:"<<publisher<<"\nPages:"<<pages;
cout<< "\nCopies:"<<copies<<"\nPrice:"<<price;

cout<<"\nEnter new details";

cout<<"\nEnter Book number (press 0 to retain old):";
cin>>num;
if(num!=0)
bookno=num;
cout<<"\nEnter Book name (press '*' to retain old):";
gets(nm);
 if(strcmp(nm,"*")!=0)
strcpy(bookname,nm);
cout<<"\nEnter Author (press '*' to retain old):";
gets(auth);
if(strcmp(auth,"*")!=0)
strcpy(author,auth);

cout<<"\nEnter Publisher (press '*' to retain old):";
gets(publ);
if(strcmp(publ,"*")!=0)
strcpy(publisher,publ);

cout<<"\nEnter pages (press 0 to retain old): ";
cin>>page;
if(page!=0)
pages=page;
cout<<"\nEnter Number of copies (press 0 to retain old):";
cin>>noc;
if(noc!=0)
copies=noc;

cout<<"\nEnter Book price (press 0 to retain old):";
cin>>pr;
if(pr!=0)
price=pr;

}
//non member function for menu function
void read_book(void)   //read all book details from file
{
book b2;
fstream fin("book",ios::in|ios::out|ios::binary);

if(!fin)
{ cout<<"Error in opening file.."; }

cout<<"\nAll Books in library are \n\n";
while(fin.read((char*)&b2,sizeof(book)))
b2.displaybook();
getch();
fin.close();
}

void write_book(book b1)  //append one book record to file
{
fstream fout("book",ios::out|ios::in|ios::binary);

if(!fout)
{ cout<<"Error in opening file.."; }

fout.seekp(((count_book-1)*sizeof(book)),ios::beg);
fout.write((char *)& b1,sizeof(b1));
cout<<"\nBook is added to list...";
getch();
fout.close();
}

void search_book(int no)   //search book as per bookno
{
book b1;
int flag=0;
fstream fin("book",ios::in|ios::out|ios::binary);
	if(!fin)
	{ 	cout<<"Error in opening file.."; 	}

while(fin.read((char*)&b1,sizeof(book)))
{
	if(no==b1.getno())            //bookno is private datamember so accessor function is used
	{
	cout<<"\nRecord is found";
	b1.displaybook();
	flag=1;
	break;
	}
}

if(flag==0)
{cout<<"Book corrosponding to entered book number doesnot exist"; 	}
getch();
fin.close();
}

void search_bookname(char nm[])   //search book as per bookname
{
book b1;
int flag=0;
fstream fin("book",ios::in|ios::out|ios::binary);
	if(!fin)
	{ 	cout<<"Error in opening file.."; 	}

while(fin.read((char*)&b1,sizeof(book)))
{
	if(strcmp(b1.getname(),name)==0)            //bookname is private datamember so accessor function is used
	{
	cout<<"\nRecord is found";
	b1.displaybook();
	flag=1;
	break;
	}
}

if(flag==0)
{cout<<"Book corrosponding to entered book name doesnot exist"; 	}
getch();
fin.close();
}

void del_book(int no)            //delete book which bookno is provided
{book b1;
int flag=0;
fstream fin("book",ios::in|ios::out|ios::binary);
if(!fin)
{  cout<<"Error in opening file.."; }

fstream fout("temp",ios::in|ios::out|ios::binary);
while(fin.read((char*)&b1,sizeof(book)))
{
	if(no!=b1.getno())
	fout.write((char*)&b1,sizeof(book));
	else
	{
	cout<<"\nRecord is found";
	b1.displaybook();
	flag=1;
	}
}

fin.close();
fout.close();

if(flag==0)
{cout<<"\nBook corrosponding to entered book number doesnot exist";
getch();
}
else
{
cout<<"\nRecord successfully deleted...";
getch();
}
remove("book");
rename("temp","book");
}

void modify_book(int no)   //modify record in file as per bookno
{book b1;
int flag=0;
fstream fin("book",ios::in|ios::out|ios::binary);
if(!fin)
{ cout<<"Error in opening file.."; }
char ans;
long pos;
while(fin.read((char*)&b1,sizeof(book)))
{
	pos=fin.tellg();

	if(no==b1.getno())            //bookno is public datamember
	{	cout<<"\nRecord is found";
		b1.displaybook();
		flag=1;
		cout<<"\n\nModify this record?";
		cin>>ans;

		if(ans=='y'||ans=='Y')
		{
		cout<<"\n\nEnter new details\n";
		b1.mod_book();
		fin.seekp((pos-sizeof(book)),ios::beg);
		fin.write((char *)&b1,sizeof(book));
		cout<<"\nRecord is modified";
		}
	getch();
	break;
	}
}

if(flag==0)
{ cout<<"\nBook corrosponding to entered book number doesnot exist";
getch();
}
fin.close();
}

int main()
{ clrscr();
void read_book(void);
void write_book(book);
void search_book(int);
void search_bookname(char []);
void del_book(int);
void modify_book(int);

	 	int choice2;
		char name[];
		do
		{
		book b1;
		fstream f2;
		f2.open("book",ios::in|ios::out|ios::binary);
		if(!f2)
		{	cout<<"\nCannot open file";
			return 1;
		}
		f2.seekp(0,ios::end);
		count_book=(f2.tellp()/sizeof(book));
		f2.close();

		clrscr();
		cout<<"\nBook Processing Menu";
		cout<<"\n********************************************";
		cout<<"\n1.Add Book";
		cout<<"\n2.Search Book by book number";
		cout<<"\n3.Search Book by book name";
         		cout<<"\n4.Modify Book data";
		cout<<"\n5.Delete Book record";
		cout<<"\n6.Display Book list";
		cout<<"\n7.Exit";
		cout<<"\n\nEnter your choice...";
		cin>>choice2;

		int no;
		switch(choice2)
		{	case 1:
			clrscr();
			b1.getbook();
			write_book(b1);
			break;

			case 2:
			clrscr();
			if(count_book==0)
			{ cout<<"\nNo record exist\n";
			cout<<"\nPlease run option 1 first";
			getch();
			break;
			}
			cout<<"\nDisplay Which record enter book no:";
			cin>>no;
			search_book(no);
			break;

			case 3:
			clrscr();
			if(count_book==0)
			{ cout<<"\nNo record exist\n";
			cout<<"\nPlease run option 1 first";
			getch();
			break;
			}
			cout<<"\nEnter book name to search:";
			fflush(stdin);
                        		gets(name);
			search_bookname(name);
			break;


			case 4:
			 clrscr();
			 if(count_book==0)
			{ cout<<"\nNo record exist\n";
			cout<<"\nPlease run option 1 first";
			getch();
			break;
			}
			cout<<"\nModify which record enter book no:";
			cin>>no;
			modify_book(no);
			break;

			case 5:
			clrscr();
			if(count_book==0)
			{ cout<<"\nNo record exist\n";
			cout<<"\nPlease run option 1 first";
			getch();
			break;
			}
			cout<<"\nEnter book number of the book you wish to delete...";
			cin>>no;
			del_book(no);
			break;

			case 6:
			clrscr();
			if(count_book==0)
			{ clrscr();
			cout<<"\nNo book Yet";
			cout<<"\nPlease run option 1 first";
			getch();
			break;
			}
			read_book();
			break;

			case 7:
			cout<<"\nExiting from Program....";
			getch();
			break;

			default:
			clrscr();
			cout<<"Wrong choice";
			cout<<"\nPress any key to continue";
			getch();
		}
		}while(choice2!=7);
	return 0;
}
