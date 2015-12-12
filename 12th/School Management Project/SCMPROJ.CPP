#include<fstream.h>
#include<process.h>
#include<graphics.h>
#include <conio.h>
#include <stdio.h>
#include<stdlib.h>
#include  <math.h>
#include<string.h>
#include <ctype.h>
#include   <dos.h>

void start();                  //Project Intro ******
void cover();                  //For background ******
void melody();                 //Sound         ******

struct dates                    // Date Structure *******
{ int dd,mm,yy;
};

// ****************** Student Class *********************
//--------------------------------------------------------

class student
{ private:
  static int count;
  char dadname[25];
  char dadocc[20];
  char dadinc[10];
  int subject[5];
  int fee;

  protected:
  char name[25];
  char address[60];
  char phno[11];
  char password[25];
  int age,id,cls;
  dates dob;
  int datechk();

  public:

  student()                         // Constructor ***********
  { strcpy(name,"Null");
    strcpy(dadname,"Null");
    strcpy(dadocc,"Null");
    strcpy(dadinc,"Null");
    strcpy(address,"Null");
    subject[0]=0;
    subject[1]=0;
    subject[2]=0;
    subject[3]=0;
    subject[4]=0;
    strcpy(phno,"Null");
    fee=0;

  }

  static int dispcount()
   { return count;
    }

  int retcls()
   { return cls;
    }
  void retname(char* outnm);
  void getstud();
  void dispstud();
  void acadmrec();
  void dispstu4cls();
  void change();
  void submitfee();

}s1;

 int student::count=0;

int student::datechk()              // Guard code to verify dates ******
{   	struct date d;
	getdate(&d);

       if( dob.yy<0 || (dob.yy>(d.da_year-6)) )
	return -1;
  else if( dob.mm<0 || dob.mm>12)
	return -1;
  else if( dob.dd<0 || dob.dd>31||(dob.dd>=28&&dob.mm==2&&dob.yy%4!=0)||(dob.dd>=29&&dob.mm==2&&dob.yy%4==0) )
	return -1;
  else
    {   if(dob.mm<d.da_mon)
	age=(d.da_year-dob.yy);
	else
	age=(d.da_year-dob.yy-1);

	return 0;
     }
}

void student::retname(char* outnm)
{ for(int i=0; i<25; i++)
    { outnm[i] = name[i];
    }
}

void student::getstud()
{   char pass[25],dd[2],mm[2],yy[4];
    int ctr=0;

    ofstream fout("student",ios::app|ios::binary);

    while(ctr<6)
    { cout<<"\n\t ---Enter Student Details--- ";
      cout<<"\n\n\tStudent Name: ";
      gets(name);
      if(strlen(name)==0)
      { cout<<"\n\tName:field can't be empty!\n";
	ctr++;
	continue;
      }
      cout<<"\tClass: ";
      cin>>cls;
      if(cls<1||cls>12)
      { ctr++;
	cout<<"\n\tWrong class! Enter again\n";
	continue;
      }
      cout<<"\tD.O.B->dd:";
      gets(dd); dob.dd=atoi(dd);
      cout<<"\tD.O.B->mm:";
      gets(mm); dob.mm=atoi(mm);
      cout<<"\tD.O.B->yyyy:";
      gets(yy); dob.yy=atoi(yy);
      if(s1.datechk()!=0)
      { ctr++;
	cout<<"\n\tD.O.B incorrect!Enter again...\n";
	continue;
      }
      cout<<"\tAddress(upto city): ";
      gets(address);
      if(strlen(address)==0)
      { cout<<"\n\tAddress:field can't be empty!\n";
	ctr++;
	continue;
      }
      cout<<"\tPhone no.: ";
      gets(phno);
	if(strlen(phno)==0||strlen(phno)<8)
      { cout<<"\n\tPhone no.:field can't be empty!\n";
	ctr++;
	continue;
      }

      cout<<"\tFather's Name: ";
      gets(dadname);
      if(strlen(dadname)==0)
      { cout<<"\n\tFather's name:field can't be empty!\n";
	ctr++;
	continue;
      }
      cout<<"\tFather's Occupation: ";
      gets(dadocc);
      if(strlen(dadocc)==0)
      { cout<<"\n\n\tFather's Occupation:field can't be empty!\n";
	ctr++;
	continue;
      }
      cout<<"\tFather's Annual Income: ";
      gets(dadinc);
       if(strlen(dadinc)==0)
      { cout<<"\n\tFather's Income:field can't be empty!\n";
	ctr++;
	continue;
      }
      randomize();
      for(int i=0;i<5;i++)
     { pass[i]=random(26)+65;
      }
       pass[i]='\0';
       strcpy(password,pass);
       fee=0;
       count++;
       randomize();
       id=random(5555)+2670;

     break;
    }

    if(ctr>=6)
    { cout<<"\n\tToo many erroneous entries!Issue a new form";
      getch();
      return;
    }

    fout.write((char*)&s1,sizeof(s1));
    fout.close();
    closegraph();

    clrscr();
    cover();
    cout<<"\n\n\n\n\n\n\n\tSuccessfully registered!!";
    cout<<"\n\tYour ID is: "<<id;
    cout<<"\n\tYour password is : "<<pass;
    cout<<"\n\n\tNow pay the following fees after logging in";
    cout<<"\n\tto your account to complete the admission-";
    cout<<"\n\t\tAdmission fee: 1000  ";
    cout<<"\n\t\tV.V.N :        4600 ";
    cout<<"\n\t\tMedical fund:   400 ";
    cout<<"\n\t\tComputer fund:  650 ";
    cout<<"\n\t\tLibrary fund:   200 ";
    cout<<"\n\n\t\tTotal :     Rs 6850 ";
    getch();

}

void student::dispstud()
{
    int id,flag=0;
    char pass[25];
    ifstream fin("student",ios::in|ios::binary);
    if(!fin)
    { cout<<"\nFile missing!!";
      exit(0);
    }
     cout<<"\n\t\t\tEnter Student ID: ";
     cin>>id;
     cout<<"\n\t\t\tEnter Password: ";
     gets(pass);

    while(fin.read((char*)&s1,sizeof(s1)))
    {
       if((s1.id==id) && !(strcmp(s1.password,pass))  )
      {
       cout<<"\n\n\t ---Student Details--- ";
       cout<<"\n\n\tStudent Name: "<<name;
       cout<<"\n\tClass: "<<cls;
       cout<<"\n\tD.O.B: "<<dob.dd<<"/"<<dob.mm<<"/"<<dob.yy;
       cout<<"\n\tAge: "<<age;
       cout<<"\n\tAddress: "<<address;
       cout<<"\n\tPhone no.: "<<phno;
       cout<<"\n\tFather's Name: "<<dadname;
       cout<<"\n\tFather's Occupation: "<<dadocc;
       cout<<"\n\tFather's Annual Income: "<<dadinc;
       cout<<"\n\tFee: "<<fee;
       flag=1;
       break;
      }
    }
    fin.close();
    if(!flag)
    cout<<"\n\n\tStudent not found!!";
    getch();
}
void student::acadmrec()
{
    int id,flag=0;
    char pass[25];
    ifstream fin("student",ios::in|ios::binary);
    if(!fin)
    { cout<<"\nFile missing!!";
      exit(0);
    }
     cout<<"\n\t\t\tEnter Student ID: ";
     cin>>id;
     cout<<"\n\t\t\tEnter Password: ";
     gets(pass);

    while(fin.read((char*)&s1,sizeof(s1)))
    {
       if((s1.id==id) && !(strcmp(s1.password,pass))  )
      {
       cout<<"\n\n\t ---Student's Academic Details--- ";
       cout<<"\n\n\tStudent Name: "<<name;
       cout<<"\n\tClass: "<<cls;
       cout<<"\n\tMarks in:\n";

       for(int i=0; i<5; i++)
       {
	 if(i==0)
	  cout<<"\n\tPhysics: "<<subject[0];
	 else if(i==1)
	  cout<<"\n\tChemistry: "<<subject[1];
	 else if(i==2)
	  cout<<"\n\tMaths: "<<subject[2];
	 else if(i==3)
	  cout<<"\n\tComputer Science: "<<subject[3];
	 else if(i==4)
	  cout<<"\n\tEnglish: "<<subject[4];
       }
       flag=1;
       break;
      }
    }
    fin.close();
    if(!flag)
    cout<<"\n\n\tStudent not found!!";
    getch();
}

void student::submitfee()
{
   int id,pos,money,flag=0;
   char pass[25];
    fstream fio("student",ios::in|ios::out|ios::binary);
    if(!fio)
    { cout<<"\n\n\tFile missing!!";
      exit(0);
    }
     cout<<"\n\t\t\tEnter Student ID: ";
     cin>>id;
     cout<<"\n\t\t\tEnter Password: ";
     gets(pass);

    while(fio.read((char*)&s1,sizeof(s1)))
    {
       if(s1.id==id && !(strcmp(s1.password,pass)) )
      {
	 flag=1;
	 if(s1.fee==6850)
	   { cout<<"\n\n\t\tFees already paid in full.";
	     break;
	   }
	 cout<<"\n\n\t\tEnter amount(Total Rs.6850): ";
	 cin>>money;
	   if(money!=6850)
	   { cout<<"\n\n\t\tMoney not equal to the required amount!!";
	     break;
	   }
	   else
	   { fee=6850;
	     pos=fio.tellg();
	     fio.seekp(pos-sizeof(s1),ios::beg);
	     fio.write((char*)&s1,sizeof(s1));
	     cout<<"\n\t\tFees paid successfully";
	     break;
	   }
      }
    }
    fio.close();
    if(!flag)
    cout<<"\n\tStudent not found!!";
    getch();

}

void student::change()
{
  cout<<"\n\tEnter Academic details: \n";
    for(int i=0; i<5; i++)
       {
	 if(i==0)
	  { cout<<"\n\tPhysics: ";
	    cin>>subject[0];
	   }
	 else if(i==1)
	  { cout<<"\tChemistry: ";
	   cin>>subject[1];
	   }
	 else if(i==2)
	  { cout<<"\tMaths: ";
	   cin>>subject[2];
	   }
	 else if(i==3)
	  { cout<<"\tComputer Science: ";
	   cin>>subject[3];
	   }
	 else if(i==4)
	  { cout<<"\tEnglish: ";
	   cin>>subject[4];
	   }
       }

}

void student::dispstu4cls()
{
  cout<<"\n\n\tStudent Name: "<<name;
  cout<<"\n\tD.O.B: "<<dob.dd<<"/"<<dob.mm<<"/"<<dob.yy;
  cout<<"\n\tAge: "<<age;
  cout<<"\n\tAddress: "<<address;
  cout<<"\n\tPhone no.: "<<phno;
  cout<<"\n\tFather's name: "<<dadname;
  cout<<"\n\tFather's occupation: "<<dadocc;
  cout<<"\n\tFather's annual income: "<<dadinc;
  cout<<"\n\tFee: "<<fee;
  cout<<"\n\tMarks in:";

       for(int i=0; i<5; i++)
       {
	 if(i==0)
	  cout<<"\n\tPhysics: "<<subject[0];
	 else if(i==1)
	  cout<<"\n\tChemistry: "<<subject[1];
	 else if(i==2)
	  cout<<"\n\tMaths: "<<subject[2];
	 else if(i==3)
	  cout<<"\n\tComputer Science: "<<subject[3];
	 else if(i==4)
	  cout<<"\n\tEnglish: "<<subject[4];
       }
}


// ****************** Teacher Class *********************
//--------------------------------------------------------

class teacher: public student
{
  private:
  char tinc[8];
  char subject[12];

  protected: int acls;

  public:
   teacher()                         // Constructor ***********
  { strcpy(name,"Null");
    strcpy(tinc,"Null");
    strcpy(subject,"Null");
    strcpy(address,"Null");
    strcpy(phno,"Null");
  }
  int retacls()
  { return acls;
   }
  void gettechr();
  void disptechr();
  void dispclass();
  void changerec();

}t1;

void teacher::gettechr()
{   char pass[25],dd[2],mm[2],yy[4];
    int ctr=0;

    ofstream fout("teacher",ios::app|ios::binary);

    while(ctr<6)
    { cout<<"\n\t ---Enter Teacher Details--- ";
      cout<<"\n\n\tTeacher Name: ";
      gets(name);
      if(strlen(name)==0)
      { cout<<"\n\tName:field can't be empty!\n";
	ctr++;
	continue;
      }
      cout<<"\tAssigned class: ";
      cin>>acls;
      if( (acls<1) || (acls>12) )
      { ctr++;
	cout<<"\n\tWrong class! Enter again\n";
	continue;
      }
      cout<<"\tD.O.B->dd:";
      gets(dd); dob.dd=atoi(dd);
      cout<<"\tD.O.B->mm:";
      gets(mm); dob.mm=atoi(mm);
      cout<<"\tD.O.B->yyyy:";
      gets(yy); dob.yy=atoi(yy);
      if(t1.datechk()!=0)
      { ctr++;
	cout<<"\n\tD.O.B incorrect!Enter again...\n";
	continue;
      }
      cout<<"\tAddress(upto city): ";
      gets(address);
      if(strlen(address)==0)
      { cout<<"\n\tAddress:field can't be empty!\n";
	ctr++;
	continue;
      }
      cout<<"\tPhone no.: ";
      gets(phno);
	if(strlen(phno)==0||strlen(phno)<8)
      { cout<<"\n\tPhone no.:field can't be empty!\n";
	ctr++;
	continue;
      }
      cout<<"\tTeacher's subject: ";
      gets(subject);
      if(strlen(subject)==0)
      { cout<<"\n\tSubject:field can't be empty!\n";
	ctr++;
	continue;
      }
      cout<<"\tAnnual income: ";
      gets(tinc);
       if(strlen(tinc)==0)
      { cout<<"\n\tTeacher's income:field can't be empty!\n";
	ctr++;
	continue;
      }
      randomize();
      for(int i=0;i<5;i++)
     { pass[i]=random(26)+97;
      }
       pass[i]='\0';
       strcpy(password,pass);
       randomize();
       id=random(2555)+2780;

     break;
    }

    if(ctr>=6)
    { cout<<"\n\tToo many erroneous entries!Issue a new form";
      getch();
      return;
    }

    fout.write((char*)&t1,sizeof(t1));
    fout.close();

    cout<<"\n\tSuccessfully registered!!";
    cout<<"\n\tYour ID is: "<<id;
    cout<<"\n\tYour password is : "<<pass;
    getch();
}

void teacher::disptechr()
{
    int id,flag=0;
    char pass[25];
    ifstream fin("teacher",ios::in|ios::binary);
    if(!fin)
    { cout<<"\nFile missing!!";
      exit(0);
    }
     cout<<"\n\t\t\tEnter Teacher ID: ";
     cin>>id;
     cout<<"\n\t\t\tEnter Password: ";
     gets(pass);

    while(fin.read((char*)&t1,sizeof(t1)))
    {
       if((t1.id==id) && !(strcmp(t1.password,pass))  )
      {
       cout<<"\n\n\t ---Teacher's Details--- ";
       cout<<"\n\n\tTeacher name: "<<name;
       cout<<"\n\tAssigned class: "<<acls;
       cout<<"\n\tD.O.B: "<<dob.dd<<"/"<<dob.mm<<"/"<<dob.yy;
       cout<<"\n\tAge: "<<age;
       cout<<"\n\tAddress: "<<address;
       cout<<"\n\tPhone no.: "<<phno;
       cout<<"\n\tTeacher's subject: "<<subject;
       cout<<"\n\tTeacher's annual income: "<<tinc;
       flag=1;
       break;
      }
    }
    fin.close();
    if(!flag)
    cout<<"\n\n\tTeacher not found!!";
    getch();
}

void teacher::dispclass()
{
    int id,acls,ctr=1,flag=0;
    char pass[25];
    ifstream fin("teacher",ios::in|ios::binary);
    if(!fin)
    { cout<<"\nFile missing!!";
      exit(0);
    }
     cout<<"\n\t\t\tEnter Teacher ID: ";
     cin>>id;
     cout<<"\n\t\t\tEnter Password: ";
     gets(pass);

    while(fin.read((char*)&t1,sizeof(t1)))
    {
       if((t1.id==id) && !(strcmp(t1.password,pass))  )
      { flag=1;
	acls=t1.retacls();
	break;
       }
    }
    fin.close();

      if(!flag)
       cout<<"\n\n\tTeacher not found!!";
      else
       {  student s2;
	  ifstream fin2("student",ios::in|ios::binary);
	   while(fin2.read((char*)&s2,sizeof(s2)))
	  {
	   if(s2.retcls()==acls)
	   {
	    s2.dispstu4cls();
	    ctr++;
	   }
	   if(ctr%2==0)
	    { getch();
	      closegraph();
	      cover();
	      cout<<"\n\n\n\n\n\n\n";
	     }
	  }
	 fin2.close();

       }
   getch();
}

void teacher::changerec()
{
    int id,acls,pos,flag=0,flag2=0;
    char pass[25],nm[25],outstr[25];
    ifstream fin("teacher",ios::in|ios::binary);
    if(!fin)
    { cout<<"\nFile missing!!";
      exit(0);
    }
     cout<<"\n\t\t\tEnter Teacher ID: ";
     cin>>id;
     cout<<"\t\t\tEnter Password: ";
     gets(pass);

    while(fin.read((char*)&t1,sizeof(t1)))
    {
       if((t1.id==id) && !(strcmp(t1.password,pass))  )
      { flag=1;
	acls=t1.retacls();
	break;
       }
    }
    fin.close();
  if(!flag)
    cout<<"\n\n\tTeacher not found!!";
  else
   { cout<<"\n\tName of student(of your class) to edit record:";
     gets(nm);
     student s2;
     fstream fio("student",ios::in|ios::out|ios::binary);
      while(fio.read((char*)&s2,sizeof(s2)))
       { s2.retname(outstr);
	 if( (strcmpi(nm,outstr)==0) && s2.retcls()==acls)
	  { cout<<"\tStudent found:";
	    s2.dispstu4cls();
	    getch();  closegraph();
	    clrscr(); cover();
	    cout<<"\n\n\n\n\n\n\n";
	    s2.change();
	    pos=fio.tellg();
	    fio.seekp( pos-sizeof(s2), ios::beg );
	    fio.write( (char*)&s2, sizeof(s2) );
	    flag2=1;
	    cout<<"\n\tAcademic record modified";
	    break;
	   }
       }
      fio.close();
      if(!flag2)
       cout<<"\n\n\tStudent not found/not in your class!";
   }
  getch();
}


//**************************** Main function *****************************
//------------------------------------------------------------------------

 void main()
{
  char ch,choice;
  clrscr();
  start();
  cover();
  melody();
  closegraph();

   do
  { clrscr();
    cover(); 				      //****** Main menu ******
    cout<<"\n\n\n\n\n\n\n\t\t\t---Main menu---";
    cout<<"\n\t\t\t1.Student's section";
    cout<<"\n\t\t\t2.Teacher's section";
    cout<<"\n\t\t\t3.Exit";
    cout<<"\n\t\t\tEnter option:";
    cin>>ch;
    closegraph();

    if(ch=='1')
    { do                                      //***** Student menu ******
      { clrscr();
	cover();
       cout<<"\n\n\n\n\n\n\n\t\t\t---Student Section---";
       cout<<"\n\t\t\t1.Admission form";
       cout<<"\n\t\t\t2.View student info";
       cout<<"\n\t\t\t3.View student academic info";
       cout<<"\n\t\t\t4.Submit fees";
       cout<<"\n\t\t\t5.Exit";
       cout<<"\n\t\t\tEnter your choice: ";
       cin>>choice;
       closegraph();

	switch(choice)
	{
	  case '1': clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    s1.getstud();
		    closegraph();
		    break;

	  case '2': clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    s1.dispstud();
		    closegraph();
		    break;

	  case '3': clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    s1.acadmrec();
		    closegraph();
		    break;

	  case '4': clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    s1.submitfee();
		    closegraph();
		    break;

	  case '5': break;

	  default:  clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    cout<<"\n\t\t\tInvlaid choice!";
		    closegraph();
		    break;

	}
      }while(choice!='5');
    }
   else if(ch=='2')
   {  do                                      //****** Teacher menu ******
      {clrscr();
       cover();
       cout<<"\n\n\n\n\n\n\n\t\t\t---Teacher Section---";
       cout<<"\n\t\t\t1.Teacher app form";
       cout<<"\n\t\t\t2.View teacher info";
       cout<<"\n\t\t\t3.View class info";
       cout<<"\n\t\t\t4.Edit student's academic record";
       cout<<"\n\t\t\t5.Exit";
       cout<<"\n\t\t\tEnter your choice: ";
       cin>>choice;
       closegraph();

	switch(choice)
	{
	  case '1': clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    t1.gettechr();
		    closegraph();
		    break;

	  case '2': clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    t1.disptechr();
		    closegraph();
		    break;

	  case '3': clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    t1.dispclass();
		    closegraph();
		    break;

	  case '4': clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    t1.changerec();
		    closegraph();
		    break;

	  case '5': break;

	  default:  clrscr(); cover();
		    cout<<"\n\n\n\n\n\n\n";
		    cout<<"\n\t\t\tInvlaid choice!";
		    closegraph();
		    break;

	}
      }while(choice!='5');
   }
   else continue;
   closegraph();

 }while(ch!='3');

  cover();
  cout<<"\n\n\n\n\n\n\n\t\t\tThank you for using the program \\/";
  cout<<"\n\t\t\tExiting........";
  getch();
  closegraph();

}


//******************** Background Cover and Sound functions *****************
//---------------------------------------------------------------------------

void start()
 {   int gd = DETECT, gm;
     initgraph(&gd, &gm, "C:\\TC\\BGI");

     delay(500);
     setcolor(9);
     settextstyle(4,0,5);
     outtextxy(70,15,"School Management Project");
     delay(30);
     setcolor(15);
     settextstyle(7,0,2);
     outtextxy(210,80,"Presented To ");
     delay(30);
     setcolor(4);
     settextstyle(7,0,3);
     outtextxy(150,100,"Madam Meena Rawat");
     delay(30);
     setcolor(15);
     settextstyle(7,0,3);
     outtextxy(210,140,"Presented By");
     delay(30);
     setcolor(4);
     settextstyle(7,0,3);
     outtextxy(160,190,"Vivek Patel");
     setcolor(11);
     settextstyle(2,0,5);
     outtextxy(370,200,"Roll no.=25");
     delay(30);
     setcolor(4);
     settextstyle(7,0,3);
     outtextxy(155,230,"XII-B");
     setcolor(11);
     settextstyle(2,0,5);
     outtextxy(370,240,"Session 2013-14");
     delay(30);
     setcolor(7);
     settextstyle(7,0,3);
     outtextxy(155,270,"K.V. ONGC Chandkheda");
     delay(30);
     setcolor(7);
     settextstyle(7,0,3);
     outtextxy(220,310,"Ahmedabad");
     delay(30);
     setcolor(2);
     settextstyle(7,0,2);
     outtextxy(120,400,"Press Any Key To Continue . . . . ");
     getch();
     setcolor(0);
     settextstyle(4,0,5);
     outtextxy(70,15,"School Management Project");
     delay(30);
     setcolor(0);
     settextstyle(7,0,2);
     outtextxy(210,80,"Presented To ");
     delay(30);
     setcolor(0);
     settextstyle(7,0,3);
     outtextxy(150,100,"Madam Meena Rawat");
     delay(30);
     setcolor(0);
     settextstyle(7,0,3);
     outtextxy(210,140,"Presented By");
     delay(30);
     setcolor(0);
     settextstyle(7,0,3);
     outtextxy(160,190,"Vivek Patel");
     setcolor(0);
     settextstyle(2,0,5);
     outtextxy(370,200,"Roll no.=25");
     delay(30);
     setcolor(0);
     settextstyle(7,0,3);
     outtextxy(155,230,"XII-B");
     setcolor(0);
     settextstyle(2,0,5);
     outtextxy(370,240,"Session 2013-14");
     delay(30);
     setcolor(0);
     settextstyle(7,0,3);
     outtextxy(155,270,"K.V. ONGC Chandkheda");
     delay(30);
     setcolor(0);
     settextstyle(7,0,3);
     outtextxy(220,310,"Ahmedabad");
     delay(30);
     setcolor(0);
     settextstyle(7,0,2);
     outtextxy(120,400,"Press Any Key To Continue . . . . ");

 }

void cover()
 {
   int gd = DETECT, gm;
   initgraph(&gd, &gm, "C:\\TC\\BGI");
   int midx=getmaxx()/2;
   setbkcolor(1);                                //Background
   setcolor(4);
   rectangle(0,0,639,479);
   rectangle(3,3,636,476);
   rectangle(4,4,635,475);
   rectangle(5,5,634,474);
   setcolor(9);
   settextstyle(4,0,1);
   outtextxy(7,-5,"*********");
   outtextxy(7,8,"*******");
   outtextxy(7,21,"******");
   outtextxy(7,34,"*****");
   outtextxy(7,47,"*******");
   outtextxy(7,60,"*********");
   outtextxy(570,-5,"*********");
   outtextxy(585,8,"*******");
   outtextxy(592,21,"******");
   outtextxy(598,34,"*****");
   outtextxy(585,47,"*******");
   outtextxy(570,60,"*********");

   setcolor(10);
   settextstyle(4,HORIZ_DIR,5);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy(midx,25,"KV ONGC Chandkheda");      //Heading
   setcolor(15);
   setlinestyle(2,0,2);
   line(midx-210, 50,midx+210, 50);
   setcolor(12);
   settextstyle(7,HORIZ_DIR,1);
   outtextxy(midx,65,"By Vivek Patel");          //Sub-heading
   setcolor(11);
   setlinestyle(1,0,2);                          //Seperator
   line(6,90,633,90);

 }

void melody()
 {
   setcolor(15);
   int midx=getmaxx()/2;
   settextstyle(1,HORIZ_DIR,7);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy(midx,240,"<<<Welcome!>>>");

   for(int v=0;v<10;v++)
    {
      sound(v*50);
     if(v%4==0)
      delay(500);
     else
      delay(200);
    }
   for(v=12;v>0;v--)
    {
      sound(v*50);
     if(v%4==0)
      delay(500);
     else
      delay(200);
    }

   nosound();
 }