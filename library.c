#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<malloc.h>
#include<windows.h>
typedef struct node{char Title[30];char Author[20]; int ISBN;int Count;struct node* next;}Book;

typedef struct NODE{char Title[30];char Author[20];int ISBN;int Count;struct NODE* left;struct NODE* right;}Tbook;

typedef struct m{char Name[30];int Regno;char Book[200];int Nob;struct m* next;}Member;

Member* makeMember(char* name,int regno,char* book,int nob)
{
    Member* temp;
    temp=(Member*)malloc(sizeof(Member));
    strcpy(temp->Name,name);
    temp->Regno=regno;
    strcpy(temp->Book,book);
    temp->Nob=nob;
    temp->next=NULL;
    return temp;
}

Member* insertMember(Member* m1,char* name,int regno,char* book,int nob)
{
    if(!m1) return makeMember(name,regno,book,nob);
    Member* temp=m1;
    while(temp->next)
    {
        temp=temp->next;
    }
    temp->next=makeMember(name,regno,book,nob);
    return m1;
}

void printMembers(Member* m1)
{
    int i=1;
    printf("S.no.\tName\treg.no\tBooks\t\t\t      Number of books borrowed\n");
    printf("=============================================================================");
    while(m1)
    {
        printf("\n\n");
        printf("%d.",i);
        printf("\t%-10s",m1->Name);
        printf("%d",m1->Regno);
        printf("\t%-35s",m1->Book);
        printf("\t\t%d",m1->Nob);
        printf("\n");
        i++;
        m1=m1->next;
    }

}

Tbook* initT()
{
    return NULL;
}

Tbook* makeNode(char* title,char* author,int isbn,int count)
{
    Tbook* temp=(Tbook*)malloc(sizeof(Tbook));
    strcpy(temp->Title,title);
    strcpy(temp->Author,author);
    temp->ISBN=isbn;
    temp->Count=count;
    temp->left=NULL;
    temp->right=NULL;

    return temp;
}

Tbook* insertVal(Tbook* t1,char* title,char* author,int isbn,int count)
{
    if(!t1) return makeNode(title,author,isbn,count);
    if(strcmp(t1->Title,title)>0) t1->left=insertVal(t1->left,title,author,isbn,count);
    if(strcmp(t1->Title,title)<0) t1->right=insertVal(t1->right,title,author,isbn,count);

    return t1;

}
Tbook* search(Tbook* t1,char* title)
{
    if(!t1) {printf("\nBook not available\n");return NULL;}
    if(strcmp(t1->Title,title)==0) printf("\nThe Book is available!!\n\n\nNumber of copies available=%d\n",t1->Count);
     if(strcmp(t1->Title,title)>0) return search(t1->left,title);
      if(strcmp(t1->Title,title)<0) return search(t1->right,title);
}

void printTbook(Tbook* b1)
{
    if(b1!=NULL)
    {

    printTbook(b1->left);
    printf("\nTitle->%s\n",b1->Title);
    printf("Author->%s\n",b1->Author);
    printf("ISBN->%d\n",b1->ISBN);
    printf("Stock->%d copies left\n",b1->Count);
    printTbook(b1->right);
    }

}


Book* init()
{
    Book* temp;
    temp=NULL;
    return temp;
}

Book* makeBook(char *title,char *author,int isbn,int count)
{
    Book* temp;
    temp=(struct node*)malloc(sizeof(Book));
    strcpy(temp->Title,title);
    strcpy(temp->Author,author);
    temp->ISBN=isbn;
    temp->Count=count;
    temp->next=NULL;

    return temp;
}

Book* insertBook(Book*b1,char* title,char* author,int isbn,int count )
{
    if(!b1) return makeBook(title,author,isbn,count);
    Book* temp=b1;
    while(temp->next)
        temp=temp->next;
    temp->next=makeBook(title,author,isbn,count);

    return b1;
}

Book* removeBook(Book* b1,char *title)
{
    if(!b1) return NULL;
    if(strcmp(b1->Title,title)==0) return b1->next;
    b1->next=removeBook(b1->next,title);
    return b1;
}

/*char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}*/

Book* borrowBook(Book* b1,char* title)
{


    if(!b1) return NULL;
    Book* temp=b1;


    while(temp)
    {
        if(strcmp(temp->Title,title)==0)
        {

         if(temp->Count<=0) {printf("\nBook not availabe\n\n");return b1;}
         temp->Count=temp->Count-1;
         return b1;
        }
        temp=temp->next;
    }
    return b1;
}
Member* borrowMember(Member* m1,char* title,int regno,Book* b1)
{
    if(!m1) return NULL;
    Member* memb=m1;
while(b1)
{
    if(strcmp(b1->Title,title)==0)
    {
        if(b1->Count==0)
        {
            printf("\nCopies not available\n\n");
            return m1;
        }

      while(memb)
{
    if(memb->Regno==regno)
    {

        if(strcmp(memb->Book,"NoBooksborrowed")==0)
     strcpy(memb->Book,title),
     strcat(memb->Book,",");

     else
        strcat(memb->Book,title),
        strcat(memb->Book,",");
            //printf("%s",memb->Book);
      memb->Nob++;
      printf("\nBook borrowed Successfully\n\n\n");

      return m1;
      break;
    }

    memb=memb->next;
}}
b1=b1->next;

}
return m1;
}


int isIn(char* a,int x,char* b)
{
    int i,j;
    int l1=strlen(a),l2=strlen(b);
    for(i=0;i<l2;i++)
    {
        if(a[x++]!=b[i])
            return 0;
    }
    return 1;
}


Member* deleteBook(Member* m1,int regno,char* title)
{
    Member* c=m1;
    while(c)
    {
        if(c->Regno==regno)
        {
            if(c->Nob==0)
            {
                printf("\nNo books borrowed\n");
                return m1;
            }
            if(c->Nob==1)

            {
                title=strcat(title,",");

                if(strcmp(title,c->Book)==0)
                {
                    strcpy(c->Book,"NoBooksborrowed");
                    c->Nob=0;
                    printf("\nBook returned successfully\n\n");
                    return m1;
                }
                else
                {
                    printf("\nBook not found\n");
                    return m1;
                }

            }
            int i=0;
            int l=strlen(title);
            char b[20];
            while(c->Book[i]!='\0')
            {
                if(c->Book[i]==title[0])
                {
                    if(isIn(c->Book,i,title))
                    {
                        strcpy(b,c->Book+i+l+1);
                        c->Book[i]='\0';
                        strcat(c->Book,b);
                        c->Nob--;
                        printf("\nBook returned successfully\n\n");
                        return m1;
                    }
                }
                i++;
            }
            break;
        }
        c=c->next;
    }
printf("\n Book not found\n");

    return m1;
}

Book* addstocks(Book* b1,char* title,int count)
{
    if(!b1) return NULL;
    Book* temp=b1;
    while(temp)
    {


        if(strcmp(temp->Title,title)==0){ temp->Count=temp->Count+count;printf("\nStock updated successfully\n\n\n");return b1;}
        //if(temp->Count<=0) {temp->next=temp->next->next;return b1;}
        temp=temp->next;
    }
    printf("\nBook not Found in library\n");
    return b1;
}



void printBooks(Book* b1)
{
    if(!b1) printf("\nNo books available!!\n");
    int i=1;
    printf("S.no.\tTitle\t\t\tAuthor\t\tISBN\t\tStock\n");
    printf("=============================================================================");
    while(b1)
    {


        printf("\n%d.",i);
        printf(" \t%-20s\t",b1->Title);
        printf("%-15s\t",b1->Author);
        printf("%d\t",b1->ISBN);
        printf("    %d copies left\t",b1->Count);
        i++;
        printf("\n");
        b1=b1->next;
    }
}
int main()
{
    Tbook* t1=initT();
    Book* b1;
    Member* m1=NULL;
    b1=init();
    char title[30],author[30],name[30],book[30],t[30],a[30],dum;
     //title=(char*)malloc(sizeof(char)*30);
    //author=(char*)malloc(sizeof(char)*30);
    int isbn,count,s,i=0,is,c,reg;
    FILE* ft;
    FILE* fa;
    FILE* fi;
    FILE* fc;
    FILE* fr;
    printf("\n*****************************LIBRARY********************************************");
    printf("\n");
    printf("\n\t\t\t1.Register\n\n\t \t\t2.Add book to library\n\n\t \t\t3.search a Book\n\n\t \t\t4.Borrow a book\n\n\t \t\t5.Add stocks\n\n\t\t \t6.Display all books\n\n\t \t\t7.Return a book\n\n\t\t \t8.Display student list\n\n\t\t \t9.Terminate\n");
    printf("\nEnter your choice: ");
scanf("%d",&s);
system("cls");
fr=fopen("member.txt","r");
while(fscanf(fr,"%s %d %d %s \n",name,&reg,&count,book)!=-1)
{
    m1=insertMember(m1,name,reg,book,count);
}
fclose(fr);
while(s!=9)
{
    switch(s)
    {
    case 1:
        printf("\nEnter your name: ");
        scanf("%s",name);
        printf("\nEnter your register number:");
        scanf("%d",&reg);
        Member* temp3;
        temp3=m1;
        while(temp3)
        {
            if(temp3->Regno==reg)
            {
                printf("\nYou are already a member\n");
                goto B;
            }
            temp3=temp3->next;
        }
        m1=insertMember(m1,name,reg,"NoBooksborrowed",0);
        fr=fopen("member.txt","a");
        fprintf(fr,"%s %d %d %s\n",name,reg,0,"NoBooksborrowed");
        fclose(fr);
        printf("\nRegistered successfully\n");
        scanf("%c",&dum);
        B:
        Sleep(2000);
        system("cls");
        break;
     case(2):

    printf("\nEnter title:");
    scanf("%s",title);
    printf("\nEnter ISBN:");
    scanf("%d",&isbn);
    printf("\nEnter author:");
     scanf("%s",author);
    printf("\nEnter the number of Books:");
    scanf("%d",&count);
    ft=fopen("book.txt","a");
    fa=fopen("author.txt","a");
    fi=fopen("isbn.txt","a");
    fc=fopen("count.txt","a");

     fwrite(strlwr(title),sizeof(title),1,ft);
     fwrite(strlwr(author),sizeof(author),1,fa);
     fwrite(&isbn,sizeof(int),1,fi);
     fwrite(&count,sizeof(int),1,fc);

    fclose(ft);
    fclose(fa);
    fclose(fi);
    fclose(fc);

    ft=fopen("book.txt","r");
    fa=fopen("author.txt","r");
    fi=fopen("isbn.txt","r");
    fc=fopen("count.txt","r");


     while(fread(t,sizeof(title),1,ft)&&
        fread(a,sizeof(author),1,fa)&&
        fread(&is,sizeof(int),1,fi)&&
        fread(&c,sizeof(int),1,fc))
{
       b1=insertBook(b1,t,a,is,c);
           }
    fclose(ft);
    fclose(fa);
    fclose(fi);
    fclose(fc);
b1=NULL;
printf("\nBook inserted successfully!!\n");
      Sleep(2000);
        system("cls");
      break;


case 3:
    ft=fopen("book.txt","r");
    fa=fopen("author.txt","r");
    fi=fopen("isbn.txt","r");
    fc=fopen("count.txt","r");


     while(fread(t,sizeof(title),1,ft)&&
        fread(a,sizeof(author),1,fa)&&
        fread(&is,sizeof(int),1,fi)&&
        fread(&c,sizeof(int),1,fc))
{
       t1=insertVal(t1,t,a,is,c);
           }
    printf("\nEnter the name of the Book to search::");
    scanf("%s",t);
    t1=search(t1,strlwr(t));

    fclose(ft);
    fclose(fa);
    fclose(fi);
    fclose(fc);
    Sleep(5000);
        system("cls");
break;

case 4:
    b1=NULL;
    ft=fopen("book.txt","r");
    fa=fopen("author.txt","r");
    fi=fopen("isbn.txt","r");
    fc=fopen("count.txt","r");


     while(fread(t,sizeof(title),1,ft)&&
        fread(a,sizeof(author),1,fa)&&
        fread(&is,sizeof(int),1,fi)&&
        fread(&c,sizeof(int),1,fc))
{
            b1=insertBook(b1,t,a,is,c);

    }
    fclose(ft);
    fclose(fa);
    fclose(fi);
    fclose(fc);

printBooks(b1);

printf("\nEnter your register number: ");
    scanf("%d",&s);

    fr=fopen("member.txt","r");

    while(fscanf(fr,"%s %d\n",name,&reg)!=-1)
    {
        if(reg==s) {break;}

    }
    if(reg!=s) {printf("\n\nPlease register first\n");break;}
    fclose(fr);
    Member* temp=m1;
    while(temp)
    {
        if(temp->Regno==s&&temp->Nob>=3)
        {
            printf("\nName:%s\n",temp->Name);
            printf("\nBorrow limit exceeded\n\n");
            goto A;
        }
        temp=temp->next;
    }
    printf("\nEnter the name of the Book to be borrowed::");
    scanf("%s",title);

b1=borrowBook(b1,title);

m1=borrowMember(m1,title,s,b1);


ft=fopen("book.txt","w");
    fa=fopen("author.txt","w");
    fi=fopen("isbn.txt","w");
    fc=fopen("count.txt","w");
while(b1)
{
     fwrite(&(b1->Title),sizeof(title),1,ft);
     fwrite(&(b1->Author),sizeof(author),1,fa);
     fwrite(&(b1->ISBN),sizeof(int),1,fi);
     fwrite(&(b1->Count),sizeof(int),1,fc);

     b1=b1->next;
     }
    fclose(ft);
    fclose(fa);
    fclose(fi);
    fclose(fc);
b1=NULL;
A:
Sleep(2000);
        system("cls");
break;
case 5:
    b1=NULL;
    ft=fopen("book.txt","r");
    fa=fopen("author.txt","r");
    fi=fopen("isbn.txt","r");
    fc=fopen("count.txt","r");


     while(fread(t,sizeof(title),1,ft)&&
        fread(a,sizeof(author),1,fa)&&
        fread(&is,sizeof(int),1,fi)&&
        fread(&c,sizeof(int),1,fc))
    {
        b1=insertBook(b1,t,a,is,c);
    }
    fclose(ft);
    fclose(fa);
    fclose(fi);
    fclose(fc);

printf("\nEnter the name of the Book::");
scanf("%s",t);
printf("Enter the number of books to add to stock::");
scanf("%d",&c);
b1=addstocks(b1,t,c);


ft=fopen("book.txt","w");
    fa=fopen("author.txt","w");
    fi=fopen("isbn.txt","w");
    fc=fopen("count.txt","w");
while(b1)

{
        fwrite(&(b1->Title),sizeof(title),1,ft);
     fwrite(&(b1->Author),sizeof(author),1,fa);
     fwrite(&(b1->ISBN),sizeof(int),1,fi);
     fwrite(&(b1->Count),sizeof(int),1,fc);
     b1=b1->next;
     }
    fclose(ft);
    fclose(fa);
    fclose(fi);
    fclose(fc);

b1=NULL;
Sleep(2000);
        system("cls");
break;

case 6:
    b1=NULL;
    ft=fopen("book.txt","r");
    fa=fopen("author.txt","r");
    fi=fopen("isbn.txt","r");
    fc=fopen("count.txt","r");


     while(fread(t,sizeof(title),1,ft)&&
        fread(a,sizeof(author),1,fa)&&
        fread(&is,sizeof(int),1,fi)&&
        fread(&c,sizeof(int),1,fc))
        {

        b1=insertBook(b1,t,a,is,c);
           }
    fclose(ft);
    fclose(fa);
    fclose(fi);
    fclose(fc);
    printBooks(b1);

    break;
case 7:
    printf("\nEnter your register number: ");
    scanf("%d",&s);

    fr=fopen("member.txt","r");

    while(fscanf(fr,"%s %d\n",name,&reg)!=-1)
    {
        if(reg==s) {break;}

    }
    if(reg!=s) {printf("\nregister number not found!!\nPlease register first\n");break;}
    fclose(fr);

     Member* temp1;
     temp1=m1;
     while(temp1)
     {
         if(temp1->Regno==s)
         {
             if(strcmp(temp1->Book,"NoBooksborrowed")==0)
             {
                 printf("\nYou haven't borrowed any books\n");
                 goto C;
             }
             printf("\nName:%s\n",temp1->Name);
             printf("\nYou have borrowed the following books:%s\n",temp1->Book);
         }
         temp1=temp1->next;
     }

    printf("\nEnter the name of the book to return:");
    scanf("%s",title);
    char chan[100];
    strcpy(chan,title);


    m1=deleteBook(m1,s,title);

    b1=addstocks(b1,chan,1);
    C:
Sleep(3000);
        system("cls");
    break;
case 8:

    printMembers(m1);
    break;
    }
Member* temp=m1;
fr=fopen("member.txt","w");

    while(temp)
    {
        fprintf(fr,"%s %d %d %s\n",temp->Name,temp->Regno,temp->Nob,temp->Book);
        temp=temp->next;
    }
    fclose(fr);
    printf("\n*****************************LIBRARY********************************************");
    printf("\n");
    printf("\n\t\t\t1.Register\n\n\t \t\t2.Add book to library\n\n\t \t\t3.search a Book\n\n\t \t\t4.Borrow a book\n\n\t \t\t5.Add stocks\n\n\t\t \t6.Display all books\n\n\t \t\t7.Return a book\n\n\t\t \t8.Display student list\n\n\t\t \t9.Terminate\n");
    printf("\nEnter your choice: ");
scanf("%d",&s);
    system("cls");
}

    return 0;
}



