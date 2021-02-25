#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

void allBooks();
void welcome();
void mainmenu();
void issue_book();
void receive_book();
void edit_books();
void search_borrower();
void view_borrowers();
void searchBook();
void entryBook();
void modifylibrary(char bookName[]);
void incrBook(char bookName[]);
void upperHeader(char header[]);
void headerBooks();
void printBooks(int sl,char title[],char category[],char author[],int qnt,int yAxis);
void headerBorrower();
void printBorrower(int sl,char name[],char book[],char contact[],int iDay,
                            int iMonth,int iYear,int rDay,int rMonth,int rYear,int fine,int yAxis);
void readme();
char reform_input(char exp[]);
char reform_output(char exp[]);
int countFine(int d, int m, int y);

char answer;
int target=0,found=0;

void gotoxy(int x, int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

struct borrower
{
	char b_name[200];
	char s_name[200];
	char add[150];
	int idd;
	int imm;
	int iyy;
	int rdd;
	int rmm;
	int ryy;
	int yr;
}m;

struct books
{
    char b_title[200];
    char b_cat[100];
    char b_auth[100];
    int b_qnty;
    int xr;
}x;

void main()
{
	welcome();
	mainmenu();
}
void welcome()
{
    for(int j=10;j<13;j++){
        gotoxy(33,j);
        for(int i=0;i<55;i++)printf("*");
    }
    gotoxy(47,11);
    printf(" LIBRARY MANAGEMENT SYSTEM ");
    gotoxy(33,15);
    printf("Press any key to continue...");
    getch();
}
void mainmenu(void)
{
    int choice;
    system("cls");
    printf("\n----------------------------------------------------------------------------------------------------\n");
    gotoxy(47,2);
    printf("MAIN MENU");
    printf("\n----------------------------------------------------------------------------------------------------\n\n");
    printf("1. Issue A Book\n");
    printf("2. Search Borrower\n");
    printf("3. View Borrower's list\n");
    printf("4. Receive Book\n");
    printf("5. Search Books\n");
    printf("6. See Books\n");
    printf("7. Add new books\n");
    printf("8. Read Me\n");
    printf("9. Close Application\n");
    printf("Please Enter a choice[1-9]:");
    scanf("%i",&choice);
    switch(choice)
    {
        case 1:
        issue_book();
        break;
        case 2:
        search_borrower();
        break;
        case 3:
        view_borrowers();
        break;
        case 4:
        receive_book();
        case 5:
        searchBook();
        break;
        case 6:
        allBooks();
        case 7:
        entryBook();
        case 8:
        readme();
        case 9:
        exit(0);
        break;
        default:
        mainmenu();
    }
}

void issue_book()
{
    found=0;
    int i=1,yAxis=7,days,sl;
    char srch[20];
    char title[100][100];
    time_t issue;
    time_t rtn;
    time(&issue);
    struct tm *local=localtime(&issue);
	system("cls");
	FILE *sfile;
	FILE *books;
	books=fopen("Library.txt","r");
	sfile = fopen("Borrower List.txt","a");
	upperHeader("ISSUE BOOK");
    gotoxy(33,4);
	printf("Book Name\t:");
    fflush(stdin);
    gets(srch);
    reform_input(srch);
    headerBooks();
	while(fscanf(books,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,&x.b_qnty)!=EOF)
    {
        if(strstr(x.b_title,srch)!=NULL)
        {
            found=1;
            strcpy(title[i],x.b_title);
            reform_output(x.b_title);
            reform_output(x.b_cat);
            reform_output(x.b_auth);
            printBooks(i++,x.b_title,x.b_cat,x.b_auth,x.b_qnty,yAxis++);
        }
    }
    if(found==1){
        gotoxy(33,++yAxis);
        printf("Enter SL NO: ");
        scanf("%d",&sl);
        strcpy(m.b_name,title[sl]);
        while(sl<1 || sl>=i){
            gotoxy(33,yAxis);
            printf("Enter SL NO: ");
            scanf("%d",&sl);
		}
    }
    else if(found==0)
    {
        printf("\nSorry book not found!");
        getch();
        mainmenu();
    }
    else if(x.b_qnty==0)
    {
        printf("\n\nSorry no remaining copy.");
        found=0;
        getch();
        mainmenu();
    }
    system("cls");
    upperHeader("ISSUE BOOK");
    gotoxy(33,4);
    reform_output(title[sl]);
    printf("Book\t\t\t: %s",title[sl]);
    gotoxy(33,5);
	printf("Borrower's Name\t:");
    fflush(stdin);
    gets(m.s_name);
    reform_input(m.s_name);
    gotoxy(33,6);
    printf("Contact\t\t:");
    fflush(stdin);
    gets(m.add);
    m.add[0]=toupper(m.add[0]);
    reform_input(m.add);
    gotoxy(33,7);
    printf("Enter Duration\t:");
    scanf("%d",&days);
    while(days<1 || days>45)
    {
        gotoxy(33,7);
        printf("You Cannot take more than 45 Days.Re-Enter.");
        printf("\n\t\t[1-45] Days\t:");
        scanf("%i",&days);
    }
    rtn=issue+(days*86400);
    struct tm *local1=localtime(&issue);
    m.idd=local1->tm_mday;
    m.imm=local1->tm_mon+1;
    m.iyy=local1->tm_year+1900;
    struct tm *local2=localtime(&rtn);
    m.rdd=local2->tm_mday;
    m.rmm=local2->tm_mon+1;
    m.ryy=local2->tm_year+1900;

	fprintf(sfile,"%s %s %s %d %d %d %d %d %d\n\n",m.b_name, m.s_name,m.add,m.idd,m.imm,m.iyy,m.rdd,m.rmm,m.ryy);
	fclose(books);
	fclose(sfile);
	reform_input(title[sl]);
	modifylibrary(title[sl]);
    gotoxy(33,9);
	printf("SUCCESFULLY RECORDED.\n");
	found=0;
    gotoxy(33,9);
	printf("Isuue another book?[Y/N]:");
	scanf("%s",&answer);
	while(toupper(answer)!='Y'&& toupper(answer)!='N')
	{
	    gotoxy(33,9);
		printf("Invalid!\n\tIssue another book?[Y/N]:");
		scanf("%s",&answer);
	}
	if(toupper(answer)=='Y')
	{
		issue_book();
	}
	else
	{
	    gotoxy(33,10);
		printf("Press any key to go to mainmenu.....");
		getch();
		mainmenu();
	}
}
void search_borrower()
{
	found=0;
	int i=1,yAxis=7;
	char id[40];
	FILE *sfile;
	system("cls");
	sfile=fopen("Borrower List.txt","rb");

    upperHeader("SEARCH BORROWER");
	printf("\n\nBorrower's Name:");
    fflush(stdin);
    gets(id);
    reform_input(id);
    headerBorrower();
	while(fscanf(sfile,"%s %s %s %d %d %d %d %d %d\n\n",
                m.b_name, m.s_name, m.add, &m.idd,&m.imm,&m.iyy,&m.rdd,&m.rmm,&m.ryy)!=EOF)
	{
		if(strstr(m.s_name,id)!=NULL)
		{
			found=1;
            reform_output(m.s_name);
            reform_output(m.b_name);
            printBorrower(i++,m.s_name,m.b_name,m.add,m.idd,m.imm,m.iyy,m.rdd,m.rmm,m.ryy,countFine(m.rdd,m.rmm,m.ryy)*30,yAxis++);
		}
	}

    if(!found){
        gotoxy(33,++yAxis);
        printf("No Record");
    }
    fclose(sfile);
    gotoxy(33,++yAxis);
    printf("Press any key to go to main menu.....");
    getch();
    mainmenu();
}

void view_borrowers()
{
	int i=1;
	int yAxis=7;
	FILE*sfile;
	system("cls");
	sfile=fopen("Borrower List.txt","r");
	upperHeader("BORROWER LIST");
	if(sfile==NULL)
	{
		printf("\n\n\t\t RECORD EMPTY");
		getch();
	}
	else
	{
	    headerBorrower();
		while(fscanf(sfile,"%s %s %s %d %d %d %d %d %d\n\n",m.b_name,m.s_name,m.add,&m.idd,&m.imm,&m.iyy,&m.rdd,&m.rmm,&m.ryy)!=EOF)
		{
            reform_output(m.s_name);
            reform_output(m.b_name);
            printBorrower(i++,m.s_name,m.b_name,m.add,m.idd,m.imm,m.iyy,m.rdd,m.rmm,m.ryy,countFine(m.rdd,m.rmm,m.ryy)*30,yAxis++);
		}
	}
	gotoxy(33,++yAxis);
	printf("Press any key for main menu........");
	fclose(sfile);
	getch();
	mainmenu();
}
void receive_book()
{
    int fine=0,i=1,yAxis=7,sl;
    char name[1000][100];
    char sBook[1000][100];
	char target[50];
	system("cls");
	upperHeader("RECEIVE BOOK");
	FILE *sfile,*mfile, *tempRec;
	sfile=fopen("Borrower List.txt","r");
	printf("\nEnter Borrower's name:");
	fflush(stdin);
	gets(target);
    reform_input(target);
	mfile=fopen("TempBook.txt","w+");
	tempRec=fopen("Duplicate.txt","w+");
	if(sfile==NULL)
	{
		printf("\n\tNo Record in File!");
		printf("\n\t\t\tPress any key to Main Menu..");
		getch();
		mainmenu();
	}
	else
	{
	    headerBorrower();
	    while(fscanf(sfile,"%s %s %s %d %d %d %d %d %d\n\n",m.b_name,m.s_name,m.add,&m.idd,&m.imm,&m.iyy,&m.rdd,&m.rmm,&m.ryy)!=EOF)
		{
			if((strstr(m.s_name,target))!=NULL)
			{
			    strcpy(name[i],m.s_name);
			    strcpy(sBook[i],m.b_name);
				reform_output(m.s_name);
                reform_output(m.b_name);
                printBorrower(i++,m.s_name,m.b_name,m.add,m.idd,m.imm,m.iyy,
                                    m.rdd,m.rmm,m.ryy,countFine(m.rdd,m.rmm,m.ryy)*30,yAxis++);
                reform_input(m.s_name);
                reform_input(m.b_name);
                fprintf(tempRec,"%s %s %s %d %d %d %d %d %d\n\n",m.b_name, m.s_name,m.add,m.idd,m.imm,m.iyy,m.rdd,m.rmm,m.ryy);
			}
			else{
                fprintf(tempRec,"%s %s %s %d %d %d %d %d %d\n\n",m.b_name, m.s_name,m.add,m.idd,m.imm,m.iyy,m.rdd,m.rmm,m.ryy);
			}
		}
		gotoxy(33,++yAxis);
		printf("Enter SL NO. to delete: ");
		scanf("%d",&sl);
		while(sl<1 || sl>=i){
            gotoxy(33,yAxis);
            printf("Enter SL NO. to delete: ");
            scanf("%d",&sl);
		}
		strcpy(target,name[sl]);
        fclose(tempRec);
        tempRec=fopen("Duplicate.txt","r");
		while(fscanf(tempRec,"%s %s %s %d %d %d %d %d %d\n\n",m.b_name,m.s_name,m.add,&m.idd,&m.imm,&m.iyy,&m.rdd,&m.rmm,&m.ryy)!=EOF)
		{
			if((strcmp(m.s_name,target))!=0)
			{
				fprintf(mfile,"%s %s %s %d %d %d %d %d %d\n\n",m.b_name, m.s_name,m.add,m.idd,m.imm,m.iyy,m.rdd,m.rmm,m.ryy);
			}
			else
			{
				found=1;
			}
		}
		fclose(sfile);
		remove("Borrower List.txt");
		fclose(tempRec);
		remove("Duplicate.txt");
		fclose(mfile);
		rename("TempBook.txt","Borrower List.txt");
		if(!found)
		{
			printf("\nRecord not found\n");
		}
		else
		{
		    incrBook(sBook[sl]);
			printf("\n\n\tRecord deleted successfully.....\n");
		}
	}
	printf("\tPress any key to go to main menu...");
	getch();
	mainmenu();
}
void entryBook()
{
    system("cls");
    FILE *book;
    if((book=fopen("Library.txt","a"))==NULL)
    {
        printf("Could not open file.");
    }
    else
    {
        upperHeader("ADD NEW BOOKS");
        gotoxy(33,4);
        printf("Enter Book Information");
        gotoxy(33,5);
        printf("====================================");
        gotoxy(33,6);
        printf("Book Name\t:");
        fflush(stdin);
        gets(x.b_title);
        reform_input(x.b_title);
        gotoxy(33,7);
        printf("Category\t:");
        fflush(stdin);
        gets(x.b_cat);
        reform_input(x.b_cat);
        gotoxy(33,8);
        printf("Author\t\t:");
        fflush(stdin);
        gets(x.b_auth);
        reform_input(x.b_auth);
        gotoxy(33,9);
        printf("Quantity\t:");
        fflush(stdin);
        scanf("%i",&x.b_qnty);
        fprintf(book,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,x.b_qnty);
        gotoxy(33,11);
        printf("SUCCESFULLY RECORDED.\n");
        fclose(book);
        gotoxy(33,12);
        printf("Do you want to add another book?[Y/N]:");
        scanf("%s",&answer);
        while(toupper(answer)!='Y'&& toupper(answer)!='N')
        {
            gotoxy(33,12);
            printf("Invalid! Do you want to add book?[Y/N]:");
            scanf("%s",&answer);
        }
        if(toupper(answer)=='Y')
        {
            entryBook();
        }
        else
        {
            gotoxy(33,14);
            printf("Press any key to go to main menu.....");
            getch();
            mainmenu();
        }
    }
}
void searchBook(void)
{
    int i=1,yAxis=7;
    system("cls");
    FILE *books;
    char target[20];
    upperHeader("SEARCH BOOKS");
    books=fopen("Library.txt","r");
    gotoxy(33,4);
    printf("Enter Title/Category/Author:");
    fflush(stdin);
    gets(target);
    reform_input(target);
    headerBooks();
    while(fscanf(books,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,&x.b_qnty)!=EOF)
    {
        if(strstr(x.b_title,target)!=NULL || strstr(x.b_cat,target)!=NULL || strstr(x.b_auth,target)!=NULL)
        {
            reform_output(x.b_title);
            reform_output(x.b_cat);
            reform_output(x.b_auth);
            printBooks(i++,x.b_title,x.b_cat,x.b_auth,x.b_qnty,yAxis++);
        }
    }
    fclose(books);
    gotoxy(33,++yAxis);
    printf("Press any key to go to main menu...");
    getch();
    mainmenu();
}
void allBooks()
{
    int i=1,yAxis=7;
    system("cls");
    FILE *books;
    upperHeader("ALL BOOKS");
    books=fopen("Library.txt","r");
    headerBooks();
    while(fscanf(books,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,&x.b_qnty)!=EOF)
    {
        reform_output(x.b_title);
        reform_output(x.b_cat);
        reform_output(x.b_auth);
        printBooks(i++,x.b_title,x.b_cat,x.b_auth,x.b_qnty,yAxis++);
    }
    fclose(books);
    gotoxy(33,++yAxis);
    printf("Press any key to go to main menu...");
    getch();
    mainmenu();
}

char reform_input(char exp[]){
    for(int i=0;i<strlen(exp);++i){
        exp[i]=tolower(exp[i]);
        if(exp[i]==' '){
            exp[i]='_';
        }
    }
}

char reform_output(char exp[]){
    exp[0]=toupper(exp[0]);
    for(int i=0;i<strlen(exp);++i){
        if(exp[i]=='_'){
            exp[i]=' ';
            exp[i+1]=toupper(exp[i+1]);
        }
    }
}

void upperHeader(char header[]){
    int xAxis;
    xAxis=60-(strlen(header)+2)/2;
    for(int j=0;j<3;j++){
        gotoxy(33,j);
        for(int i=0;i<55;i++)printf("*");
    }
    gotoxy(xAxis,1);
    printf(" %s ",header);
}
void headerBooks(){
    gotoxy(0,5);
    printf("SL NO.");
    gotoxy(15,5);
    printf("TITLE");
    gotoxy(50,5);
    printf("CATEGORY");
    gotoxy(75,5);
    printf("AUTHOR");
    gotoxy(110,5);
    printf("QUANTITY");
    gotoxy(0,6);
    for(int i=0;i<120;i++)printf("-");
}
void printBooks(int sl,char title[],char category[],char author[],int qnt,int yAxis){
    gotoxy(0,yAxis);
    printf("%d",sl);
    gotoxy(15,yAxis);
    printf("%s",title);
    gotoxy(50,yAxis);
    printf("%s",category);
    gotoxy(75,yAxis);
    printf("%s",author);
    gotoxy(110,yAxis);
    printf("%d",qnt);
}
void headerBorrower(){
    gotoxy(0,5);
    printf("SL NO.");
    gotoxy(10,5);
    printf("Borrower's name");
    gotoxy(35,5);
    printf("Book name");
    gotoxy(65,5);
    printf("Contact");
    gotoxy(82,5);
    printf("Issue date");
    gotoxy(97,5);
    printf("Return date");
    gotoxy(112,5);
    printf("Fine");
    gotoxy(0,6);
    for(int i=0;i<120;i++)printf("-");
}

void printBorrower(int sl,char name[],char book[],char contact[],int iDay,
                            int iMonth,int iYear,int rDay,int rMonth,int rYear,int fine,int yAxis){

    gotoxy(0,yAxis);
    printf("%d",sl);
    gotoxy(10,yAxis);
    printf("%s",name);
    gotoxy(35,yAxis);
    printf("%s",book);
    gotoxy(65,yAxis);
    printf("%s",contact);
    gotoxy(82,yAxis);
    printf("%d/%d/%d",iDay,iMonth,iYear);
    gotoxy(97,yAxis);
    printf("%d/%d/%d",rDay,rMonth,rYear);
    gotoxy(112,yAxis);
    printf("%d",fine);
}
void modifylibrary(char bookName[])
{
    FILE *books;
    FILE *tempFile;
    books=fopen("Library.txt","r");
    tempFile=fopen("tempbook.txt","w+");
    while(fscanf(books,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,&x.b_qnty)!=EOF)
    {
        if(strcmp(bookName,x.b_title)==0)
        {
            fprintf(tempFile,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,--x.b_qnty);
        }
        else
        {
            fprintf(tempFile,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,x.b_qnty);
        }
    }
    fclose(books);
    remove("Library.txt");
    fclose(tempFile);
    rename("tempbook.txt","Library.txt");
}
void incrBook(char bookName[])
{
    FILE *books;
    FILE *tempFile;
    books=fopen("Library.txt","r");
    tempFile=fopen("tempbook.txt","w+");
    while(fscanf(books,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,&x.b_qnty)!=EOF)
    {
        if(strcmp(bookName,x.b_title)==0)
        {
            fprintf(tempFile,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,++x.b_qnty);
        }
        else
        {
            fprintf(tempFile,"%s %s %s %i\n",x.b_title,x.b_cat,x.b_auth,x.b_qnty);
        }
    }
    fclose(books);
    remove("Library.txt");
    fclose(tempFile);
    rename("tempbook.txt","Library.txt");
}

int countFine(int d, int m, int y){
    time_t now,curr,ret;
    time(&now);

    struct tm *local=localtime(&now);
    curr=mktime(local);

    struct tm *deadline=localtime(&now);
    deadline->tm_year=y-1900;
    deadline->tm_mon=m-1;
    deadline->tm_mday=d;
    ret=mktime(deadline);
    if(difftime(curr,ret)>0)return (difftime(curr,ret))/86400;
    else return 0;
}
void readme(){
    system("cls");
    upperHeader("READ ME");
    int c;
    FILE *readme;

    if((readme=fopen("READ ME.txt","r"))!=NULL){
        gotoxy(0,4);
        while((c=getc(readme))!=EOF){
            putchar(c);
        }
        printf("\n");
        fclose(readme);
    }
    else{
        gotoxy(33,10);
        printf("Cannot open READ ME!");
    }
    getch();
    mainmenu();
}
// end of program
