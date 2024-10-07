/*
 C++ program to implement an SLR shift-reduce Parser for the Expression Grammar
 Sandipan Dey
 BCSE, JU, Kolkata
 2003
*/
 
 #include <iostream.h>
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <conio.h>
 #include <dos.h>
 #include <ctype.h>
 
 const int MAX=20;
 FILE* f;
 int count;
 struct String
 {
     char s[20];
 };
 
 struct Rule                     //Data Structure For Grammar
 {
     char NT[20];
     char T[10][5];
     void (*function)();
     char fname[15];
 };
 
 int pow(int i,int n)             //Calculates Power
 {
    if(n==0)
        return 1;
    else if(n==1)
        return i;
    else
        return pow(i,n-1)*i;
 }
 
 void OutputGrammar(Rule* r,int Rno,int tr=0);
 
 void Blink(char* s,int d)            //Blinks Error Message
 {
     int x=wherex(),y=wherey(),j=0;
     while(!kbhit())
     {
        j=(j+1)%2;
        if(j)cout<<s;
        else cout<<"                                     ";
        delay(d);
        gotoxy(x,y);
        j=(j+1)%2;
        if(j)
           cout<<s;
        else
           cout<<"                                   ";
        gotoxy(x,y);
        delay(d/2);
     }
 }
 
 class Stack                              //PushDown Stack
 {
       int top;
       String el[MAX];
 
 public:
       Stack()
       {
        top=-1;
       }
       void Push(String n);
       String Pop(void);
 };
 void Stack::Push(String e)
 {
      if(top==MAX-1)
        cout<<endl<<"Stack Overflow!!";
      else
        strcpy(el[++top].s,e.s);
 }
 String Stack::Pop()
 {
      String e;
      strcpy(e.s,"\0");
      if(top==-1)
        /*cout<<endl<<"Stack Underflow!!"*/;
      else
      {
        strcpy(e.s,el[top].s);
        --top;
      }
      return(e);
 }
 
 void Show(Stack s)                       //Shows The Elements Of Stack
 {
     String ss;
     strcpy(ss.s,s.Pop().s);
     if(strcmp(ss.s,"\0"))
     {
        Show(s);
        s.Push(ss);
     }
     cout<<ss.s<<" ";
 }
 
 Stack p;
 
 class SLR                                //Class SLR
 {
    char exp[100];
    int Tno,NTno,STno,Rno,CurPos,res;
    String PTable[20][20];
    String Terminal[10],NonTerminal[10];
    Stack  s;
    Rule r[20];
    public:
    SLR(String ptbl[20][12],int,int,int,Rule*,String*);
    void InputPTable();
    void InitPTable(String ptbl[20][12],int,int,int,Rule*,String*);
    int Parser();
    void Output();
    int SearchRow(void);
    int SearchCol(char);
    int ShiftReduce(int,int);
 };
 
 void ActionPlus()                        //Action Routines
 {
    char t1[20],t2[20],temp[20];
    strcpy(t2,p.Pop().s);
    strcpy(t1,p.Pop().s);
    char s[100];
    ++count;
    if(isdigit(t2[0])){strcpy(temp,t2);strcpy(t2,"t");strcat(t2,temp);strcpy(temp,"\0");}
    if(isdigit(t1[0])){strcpy(temp,t1);strcpy(t1,"t");strcat(t1,temp);strcpy(temp,"\0");}
    sprintf(temp,"%d",count);
    printf("\n\nQuadruple Generated=>\n");
    sprintf(s,"              ( +  %s  %s  t%d )\n",t1,t2,count);
    printf("%s",s);
    fputs(s,f);
    String ss;
    strcpy(ss.s,temp);
    p.Push(ss);
    getch();
 }
 void ActionMinus()
 {
    char t1[20],t2[20],temp[20];
    strcpy(t2,p.Pop().s);
    strcpy(t1,p.Pop().s);
    char s[100];
    ++count;
    if(isdigit(t2[0])){strcpy(temp,t2);strcpy(t2,"t");strcat(t2,temp);strcpy(temp,"\0");}
    if(isdigit(t1[0])){strcpy(temp,t1);strcpy(t1,"t");strcat(t1,temp);strcpy(temp,"\0");}
    sprintf(temp,"%d",count);
    printf("\n\nQuadruple Generated=>\n");
    sprintf(s,"              ( -  %s  %s  t%d )\n",t1,t2,count);
    printf("%s",s);
    fputs(s,f);
    String ss;
    strcpy(ss.s,temp);
    p.Push(ss);
    getch();
 }
 void ActionMultiply()
 {
    char t1[20],t2[20],temp[20];
    strcpy(t2,p.Pop().s);
    strcpy(t1,p.Pop().s);
    char s[100];
    if(isdigit(t2[0])){strcpy(temp,t2);strcpy(t2,"t");strcat(t2,temp);strcpy(temp,"\0");}
    if(isdigit(t1[0])){strcpy(temp,t1);strcpy(t1,"t");strcat(t1,temp);strcpy(temp,"\0");}
    ++count;
    sprintf(temp,"%d",count);
    printf("\n\nQuadruple Generated=>\n");
    sprintf(s,"              ( *  %s  %s  t%d )\n",t1,t2,count);
    printf("%s",s);
    fputs(s,f);
    String ss;
    strcpy(ss.s,temp);
    p.Push(ss);
    getch();
 }
 void ActionDivide()
 {
    char t1[20],t2[20],temp[20];
    strcpy(t2,p.Pop().s);
    strcpy(t1,p.Pop().s);
    char s[100];
    if(isdigit(t2[0])){strcpy(temp,t2);strcpy(t2,"t");strcat(t2,temp);strcpy(temp,"\0");}
    if(isdigit(t1[0])){strcpy(temp,t1);strcpy(t1,"t");strcat(t1,temp);strcpy(temp,"\0");}
    ++count;
    sprintf(temp,"%d",count);
    printf("\n\nQuadruple Generated=>\n");
    sprintf(s,"              ( /  %s  %s  t%d )\n",t1,t2,count);
    printf("%s",s);
    fputs(s,f);
    String ss;
    strcpy(ss.s,temp);
    p.Push(ss);
    getch();
 }
 void ActionTothePower()
 {
    char t1[20],t2[20],temp[20];
    strcpy(t2,p.Pop().s);
    strcpy(t1,p.Pop().s);
    char s[100];
    if(isdigit(t2[0])){strcpy(temp,t2);strcpy(t2,"t");strcat(t2,temp);strcpy(temp,"\0");}
    if(isdigit(t1[0])){strcpy(temp,t1);strcpy(t1,"t");strcat(t1,temp);strcpy(temp,"\0");}
    ++count;
    sprintf(temp,"%d",count);
    printf("\n\nQuadruple Generated=>\n");
    sprintf(s,"              ( ^  %s  %s  t%d )\n",t1,t2,count);
    printf("%s",s);
    fputs(s,f);
    String ss;
    strcpy(ss.s,temp);
    p.Push(ss);
    getch();
 }
 void ActionNOP()
 {
    ;;;;    //NOP
 }                    //Action Routines
 
 SLR::SLR(String ptbl[20][12],int ntno,int tno,int rno,Rule* g,String* NTT)
 {
    String ss;
    InitPTable(ptbl,ntno,tno,rno,g,NTT);
    InputPTable();
    Output();
    char choice;
    do {
         CurPos=0;
         count=0;
         strcpy(exp,"\0");
         f=fopen("qudruple.cpp","w");
         char q[100];
         strcpy(q,"          Quadruples Generated For Exp. \"");
         while(strcmp(s.Pop().s,"\0")){;}
         while(strcmp(p.Pop().s,"\0")){;}
         Show(s);
         strcpy(ss.s,"0");
         s.Push(ss);
         printf("\n\nInput Arithmetic Expression : ");
         gets(exp);
         strcat(q,exp);
         strcat(q,"\"\n");
         fputs(q,f);
         fputs("             -------------------------------------------------\n",f);
         int l=strlen(exp);
         exp[l]='$';exp[l+1]='\0';
         clrscr();
         l=Parser();
         if(l==1)
         {
               printf("\n\nArithmetic Expression Accepted.");
               //exp[strlen(exp)-1]='\0';
               //cout<<endl<<endl<<exp<<"="<<;
               p.Pop();
         }
         else if(l==-1)
         {
            printf("\n\nArithmetic Expression Rejected.");
            getch();}clrscr();
            fclose(f);
            cout<<endl<<"Continue?[Y|N]:";
            cin>>choice;
       } while(choice=='y' || choice=='Y');
 }
 
 void SLR::InitPTable(String ptbl[20][12],int ntno,int tno,int rno,Rule* g,String* NTT)       //Initialize Parsing Table
 {
         clrscr();
 
         NTno=ntno;Tno=tno;Rno=rno;
         STno=17; res=0;
         for(int i=0;i<NTno;++i)
         strcpy(NonTerminal[i].s,NTT[i].s);
         for(i=NTno;i<NTno+Tno;++i)
            strcpy(Terminal[i-NTno].s,NTT[i].s);
         int j;
         for(i=0;i<Rno;++i)
            for(j=0;j<10;++j)
                strcpy(r[i].T[j],"\0");
 
         for(i=0;i<Rno;++i)
         {
            strcpy(r[i].NT,g[i].NT);
            r[i].function=g[i].function;
            for(j=0;j<10;++j)
                strcpy(r[i].T[j],g[i].T[j]);
         }
         r[0].function=::ActionNOP;strcpy(r[0].fname,"ActionNOP");
         r[1].function=::ActionPlus;strcpy(r[1].fname,"ActionPlus");
         r[2].function=::ActionMinus;strcpy(r[2].fname,"ActionMinus");
         r[3].function=::ActionNOP;strcpy(r[3].fname,"ActionNOP");
         r[4].function=::ActionMultiply;strcpy(r[4].fname,"ActionMultiply");
         r[5].function=::ActionDivide;strcpy(r[5].fname,"ActionDivide");
         r[6].function=::ActionTothePower;strcpy(r[6].fname,"ActionPower");
         r[7].function=::ActionNOP;strcpy(r[7].fname,"ActionNOP");
         r[8].function=::ActionNOP;strcpy(r[8].fname,"ActionNOP");
         r[9].function=::ActionNOP;strcpy(r[9].fname,"ActionNOP");
         cout<<"\nTranslation Grammar";
         cout<<"\n-------------------";
         OutputGrammar(r,rno,1);
         getch();
         for(int row=0;row<STno;++row)
            for(int col=0;col<Tno+NTno;++col)
                strcpy(PTable[row][col].s,"\0");
 
         for(i=0;i<20;++i)
            for(j=0;j<NTno+Tno;++j)
                strcpy(PTable[i][j].s,ptbl[i][j].s);
 }
 
 void SLR::InputPTable()          //Input Grammar
 {
         //char choice='Y';
         cout<<endl<<"Using The Parsing Table Generated For Arithmetic Expressions..."<<endl;
         //cin>>choice;
         /*if(choice!='y' && choice!='Y')
         {
          clrscr();
          cout<<endl<<"How Many Terminal Symbols?";
          cin>>Tno;
          for(int i=0;i<Tno;++i)
          {
          clrscr();
          cout<<endl<<"Input Terminal Symbol["<<i<<"]:";
          cin>>Terminal[i].s;
          }
          strcpy(Terminal[i].s,"$");
          ++Tno;
          clrscr();
          cout<<endl<<"How Many Non-Terminal Symbols?";
          cin>>NTno;
          for(i=0;i<NTno;++i)
          {
          clrscr();
          cout<<endl<<"Input Non-Terminal Symbol["<<i<<"]:";
          cin>>NonTerminal[i].s;
          }
          clrscr();
          cout<<endl<<"Input Grammar:";
          cout<<endl<<"How Many Rules?";
          cin>>Rno;
          for(i=0;i<Rno;++i)
          {
        clrscr();
        cout<<endl<<"Rule "<<i<<"=> "<<endl;
        cin>>r[i].NT;
        cout<<"->";
        int jj=0;
        do {
              cin>>r[i].T[jj++];
           }
        while(jj<10 && strcmp(r[i].T[jj-1],"\0"));
          }
         clrscr();
         cout<<endl<<"How Many States?";
         cin>>STno;
         for(int l=0;l<STno;++l)
         {
        clrscr();
        cout<<"State "<<l<<endl;
        cout<<"Action:"<<endl;
        for(i=0;i<Tno;++i)
        {
            cout<<Terminal[i].s<<" : ";
            cin>>PTable[l][i].s;
        }
            cout<<"Goto:"<<endl;
            for(int j=0;i<Tno+NTno;++i,++j)
            {
            cout<<NonTerminal[j].s<<" : ";
            cin>>PTable[l][i].s;
            }
         }
        } */
 }
 
 void SLR::Output()
 {
     clrscr();
     printf("\nState               Action                             Goto");
     printf("\n No.");
     printf("%5s",Terminal[6].s);
     for(int i=0;i<Tno;++i)
     if(i!=6)
        printf("%5s",Terminal[i].s);
     for(i=0;i<NTno;++i)
        printf("%5s",NonTerminal[i].s);
     for(int l=0;l<STno;++l)
     {
        printf("\n%2d  ",l);
        printf("%5s",PTable[l][6].s);
        for(i=0;i<Tno+NTno;++i)
        if(i!=6)
            printf("%5s",PTable[l][i].s);
     }
     getch();
     clrscr();
     cout<<endl<<"Grammar"<<endl;
     for(i=0;i<Rno;++i)
     { 
        cout<<endl<<"Rule "<<i<<" : "<<r[i].NT<<"->";
        int jj=0;
        while(jj<10 && strcmp(r[i].T[jj],"\0")){cout<<r[i].T[jj++];}
     }
 }
 
 int SLR::Parser()
 {
    cout<<endl<<"Given Expression: "<<exp;
    for(int i=0;i<strlen(exp);)//++i,++CurPos)
    {
        int row=SearchRow(),col=SearchCol(exp[i]),ret;
        char k=156;
        cout<<endl;
        //cout<<endl<<"Row="<<row<<",Col="<<col<<" "<<PTable[row][col].s;
        if(col==-1){
            if(!islower(exp[i]) && exp[i]!='+' && exp[i]!='-' && exp[i]!='*' && exp[i]!='/' && exp[i]!='^')
            {cout<<endl;Blink("Error!Only LowerCase Alphabet Allowed!!!",500);
            printf("Invalid Character '%c'!!!",exp[i]);getch();return -1;}
            char st[200];cout<<"\n\n";strcpy(st,"Error!!! Expected");
            for(int l=0;l<Tno-1;++l)if(strcmp(PTable[row][l].s,"\0"))
            {strcat(st," '");strcat(st,Terminal[l].s);strcat(st,"' OR");}
            int n=strlen(st);if(n>2 && st[n-2]=='O' && st[n-1]=='R')st[n-2]='\0';
            if(exp[i]!='$'){
                    strcat(st," Instead of '");int n=strlen(st);st[n]=exp[i];st[n+1]='\0';
                    strcat(st,"'");}cout<<endl;Blink(st,500);
                       }
        ret=ShiftReduce(row,col);
        cout<<endl<<"Stack=> "<<k;
        if(ret){++i;++CurPos;}
        Show(s);
        char* p=exp+i;
        printf("\tInput=> %s",p);
        if(!strcmp(PTable[row][col].s,"acc"))return 1;
        else if(!strcmp(PTable[row][col].s,"\0")){
                             char st[200];cout<<"\n\n";
                             strcpy(st,"Error!!! Expected");for(int l=0;l<Tno-1;++l)if(strcmp(PTable[row][l].s,"\0")){strcat(st," '");strcat(st,Terminal[l].s);strcat(st,"' OR");}int n=strlen(st);if(n>2 && st[n-2]=='O' && st[n-1]=='R')st[n-2]='\0';
                             if(exp[i]!='$'){strcat(st," Instead of '");int n=strlen(st);st[n]=exp[i];
                             st[n+1]='\0';strcat(st,"'");}cout<<endl;Blink(st,500);return -1;
                             }
        getch();
    }
    return 0;
 }
 
 int SLR::ShiftReduce(int r,int c)    //Shift & Reduce Parsing
 {
    String ss;
    String tmp;
    int ret=0;
    if(PTable[r][c].s[0]=='s' || PTable[r][c].s[0]=='S')
    {
        if(islower(exp[CurPos]))
        {
            sprintf(tmp.s,"%c",exp[CurPos]);
            p.Push(tmp);
            strcpy(ss.s,"id");
        }
        else //if(exp[CurPos]=='+' || exp[CurPos]=='-' || exp[CurPos]=='*' || exp[CurPos]=='/' || exp[CurPos]=='^')
        {
            ss.s[0]=exp[CurPos];
            ss.s[1]='\0';
        }
        //else {Blink("Only LowerCase Alphabet Allowed!!!",300);return -1;}
        s.Push(ss);
        strcpy(ss.s,"\0");
        for(int i=1;i<strlen(PTable[r][c].s);++i)
            ss.s[i-1]=PTable[r][c].s[i];
        ss.s[i-1]='\0';
        s.Push(ss);
        ret=1;
    }
    else if(PTable[r][c].s[0]=='r' || PTable[r][c].s[0]=='R')
    {
        for(int i=1;i<strlen(PTable[r][c].s);++i)
        ss.s[i-1]=PTable[r][c].s[i];ss.s[i-1]='\0';
        int index=atoi(ss.s),t1,t2;
        char str[30];
        strcpy(ss.s,SLR::r[index].NT);
        while(strcmp(strcpy(str,s.Pop().s),SLR::r[index].T[0])){
        if(!strcmp(str,"\0")){printf("\nError!");return -1;} }
        SLR::r[index].function();
        int row=SearchRow();
        s.Push(ss);
        for(i=0;i<NTno;++i)
        if(!strcmp(ss.s,NonTerminal[i].s))
        {
           strcpy(ss.s,PTable[row][i+Tno].s);
           s.Push(ss);
           break;
        }
    }
    return ret;
 }
 
 int SLR::SearchRow()
 {
    String ss;
    strcpy(ss.s,s.Pop().s);
    s.Push(ss);
    return (atoi(ss.s));
 }
 
 int SLR::SearchCol(char c)
 {
    char ss[5];
    int index=-1;
    if(islower(c))
        strcpy(ss,"id");
    else 
    {
        ss[0]=c;ss[1]='\0';
    }
    for(int i=0;i<Tno;++i)
        if(!strcmp(ss,Terminal[i].s))
           index=i;
    return index;
 }
 
 void OutputGrammar(Rule* r,int Rno,int tr)
 {
    for(int i=0;i<Rno && strcmp(r[i].NT,"\0");++i)
    {
        cout<<endl<<"Rule "<<i<<" : "<<r[i].NT<<"->";
        int j=0;
        while(j<10 && strcmp(r[i].T[j],"\0"))
        {
            cout<<r[i].T[j++];
        }
        if(tr==1)printf("  Action Routine: %s()",r[i].fname);
    }
 }
 
 void AugumentGrammar(Rule* r,int* Rno)
 {
    ++(*Rno);
    for(int i=(*Rno)-1;i>0;i--)
    {
        strcpy(r[i].NT,r[i-1].NT);
        int j=0;
        while(j<9){strcpy(r[i].T[j+1],r[i-1].T[j]);++j;}
        strcpy(r[i].T[0],".");
    }
    strcpy(r[i].T[0],".");
    strcpy(r[i].T[1],r[i].NT);
    strcpy(r[i].T[2],"\0");
    strcat(r[i].NT,"'");
 }
 
 void UnAugument(Rule* r,int Rno)
 {
    for(int i=0;i<Rno;i++)
        for(int j=0;j<9;++j)
            strcpy(r[i].T[j],r[i].T[j+1]);
 }
 
 int FindDot(Rule r)                   //Find The Position Of '.'
 {
    int index=-1;
    for(int i=0;i<10;++i)
        if(!strcmp(r.T[i],"."))
           index=i;
    return index;
 }
 
 int FindNext(Rule r,char* NT,String* NTT,int NTno,int Tno)
 {
    char s[20];
    strcpy(s,"\0");
    for(int i=0;i<9;++i)
    if(!strcmp(r.T[i],NT) && strcmp(r.T[i+1],"\0"))
        strcpy(s,r.T[i+1]);
    for(i=NTno;i<NTno+Tno;++i)
        if(!strcmp(NTT[i].s,s))return i-NTno;
    return -1;
 }
 
 void Copy(Rule* rd,Rule* rs)
 {
    strcpy(rd->NT,rs->NT);
    for(int i=0;i<10;++i)
    strcpy(rd->T[i],rs->T[i]);
 }
 
 int Equal(Rule r1,Rule r2)           //Checks If Two Grammar Rules
 {                                        //Are Equal
    int flag=1;
    if(strcmp(r1.NT,r2.NT))flag=0;
    for(int i=0;i<10;++i)
    if(strcmp(r1.T[i],r2.T[i]))
    {
        flag=0;
        if(!strcmp(r1.T[i],"\0"))break;
    }
    return flag;
 }
 
 int Equal(Rule* r1,Rule* r2)            //Check If Two States In DFA
 {                   //Are Equal
    int flag=1;
    for(int i=0;i<10;++i)
    if(!Equal(r1[i],r2[i])){flag=0;break;}
    return flag;
 }
 
 int Closure(Rule r,Rule* c,Rule* g,int Rno,int j) //Computes Closure
 {
    int index=-1;
    index=FindDot(r);
    if(index>=0)
    {
          Copy(&c[j++],&r);
          for(int i=0;i<Rno;++i)
          if(!strcmp(r.T[index+1],g[i].NT) && j<10)
          { 
            int flag=1;
            for(int k=0;k<j;++k)
            if(Equal(c[k],g[i]))flag=0;
            if(flag){Copy(&c[j],&g[i]);
            Closure(c[j],c,g,Rno,j);j++;}
          }
    }
    return j;
 }
 
 void ShrDot(Rule* r,int index)
 {
    strcpy(r->T[index],r->T[index+1]);
    strcpy(r->T[index+1],".");
 }
 
 void Goto(Rule* c,char* s,Rule* nc,Rule* g,int Rno) //Comutes GotoTable
 {
    int j;
    Rule temp[10];
    for(int i=0;i<10;++i)
    {
        strcpy(temp[i].NT,"\0");
        for(j=0;j<10;++j)
        strcpy(temp[i].T[j],"\0");
    }
    j=0;
    for(i=0;i<10 && strcmp(c[i].NT,"\0");++i)
    {
        int index=-1;
        index=FindDot(c[i]);
        if(index>=0 && !strcmp(c[i].T[index+1],s))
        {Copy(&temp[j],&c[i]);ShrDot(&temp[j],index);j++;}
    }
    int k=0;
    for(i=0;i<j;++i)
        k=Closure(temp[i],nc,g,Rno,k);
 }
 
 int SearchShift(Rule I[20][10],char* s,int i)
 {
    for(int j=0;j<10 && strcmp(I[i][j].NT,"\0");++j)
    {
     int index=-1;
     index=FindDot(I[i][j]);
     if(index>=0 && !strcmp(I[i][j].T[index+1],s))return 1;
    }
    return 0;
 }
 
 int FindActualRule(Rule r,int index,Rule* g,int Rno)
 {
    for(int i=index;i>0;--i)
        strcpy(r.T[i],r.T[i-1]);
    strcpy(r.T[0],".");
    for(i=0;i<Rno;++i)
        if(Equal(r,g[i]))return i;
    return 0;
 }
 
 int FindLastT(Rule g)
 {
    for(int i=9;i>=0 && !strcmp(g.T[i],"\0");--i);
    return i;
 }
 
 void SearchReduce(Rule I[20][10],int i,Rule* g,String a[20][12],int Rno,int NTno,int Tno,String* NTT)
 {
    for(int j=0;j<10 && strcmp(I[i][j].NT,"\0");++j)
    {
        int index=-1;
        index=FindDot(I[i][j]);
        if(index>=0 && !strcmp(I[i][j].T[index+1],"\0")){
               int found=FindActualRule(I[i][j],index,g,Rno);
               char str[5];
               sprintf(str,"r%d",found);
               if(!strcmp(I[i][j].NT,g[1].NT))
               strcpy(a[i][Tno-1].s,str);
               if(!strcmp(I[i][j].NT,"E"))
               {strcpy(a[i][0].s,str);
               strcpy(a[i][1].s,str);strcpy(a[i][7].s,str);
               strcpy(a[i][8].s,str);}
        else if(!strcmp(I[i][j].NT,"T") || !strcmp(I[i][j].NT,"F"))
        {strcpy(a[i][0].s,str);strcpy(a[i][1].s,str);
         strcpy(a[i][2].s,str);strcpy(a[i][3].s,str);
         strcpy(a[i][4].s,str);strcpy(a[i][7].s,str);
         strcpy(a[i][8].s,str);}
        /* for(int k=0;k<Rno;++k) //To Calculate FOLLOW
        {
        int indx=FindNext(g[k],I[i][j].NT,NTT,NTno,Tno);
        if(indx>=0)strcpy(a[i][indx].s,str);
        for(int l=0;l<Rno;++l)
        if(!strcmp(g[l].T[FindLastT(g[l])],I[i][j].NT))
        {indx=FindNext(g[k],g[l].NT,NTT,NTno,Tno);
        if(indx>=0)strcpy(a[i][indx].s,str);}
        } */
        }
    }
 }
 
 int SearchAccept(Rule I[20][10],int i,Rule temp)
 {
    for(int j=0;j<10 && strcmp(I[i][j].NT,"\0");++j)
        if(Equal(temp,I[i][j]))return 1;
            return 0;
 }
 
 void ConstructSetOfItems(Rule* r,Rule I[20][10],int Rno,int NTno,int Tno,String* NTT, String a[20][12])
 {
    Rule temp[10];
    int i,no=0,j=0,gototable[20][12];
    for(i=0;i<20;++i)
        for(j=0;j<NTno+Tno;++j)
            gototable[i][j]=-1;
    j=0;
    cout<<endl<<endl<<"I"<<no<<"=>"<<endl;
    cout<<"-----";
    Closure(r[0],I[0],r,Rno,j);
    //cout<<endl<<endl<<"Closure:";
    //cout<<endl<<"--------";
    OutputGrammar(I[0],10);
    getch();
    //cout<<endl<<endl<<"Goto:";
    //cout<<endl<<"--------";
    for(int t=0;t<=no;++t)     //VV IMP
        for(i=0;i<NTno+Tno;++i)
        {
            for(int ii=0;ii<10;++ii)
            {
                strcpy(temp[ii].NT,"\0");
                for(j=0;j<10;++j)
                    strcpy(temp[ii].T[j],"\0");
            }
            Goto(I[t],NTT[i].s,temp,r,Rno);
            int flag=1;
            if(!strcmp(temp[0].NT,"\0"))flag=0;
            for(int y=0;y<=no;++y)if(Equal(temp,I[y]))
            {
                gototable[t][i]=y;
                cout<<endl<<endl<<"I"<<t<<" '"<<NTT[i].s<<"' I"<<y<<endl;
                flag=0;break;
            }
            if(flag) 
            {
                 gototable[t][i]=no+1;
                 cout<<endl<<endl<<"I"<<t<<" '"<<NTT[i].s<<"' I"<<no+1<<endl;
                 cout<<endl<<"I"<<no+1<<"=>"<<endl;
                 cout<<"-----";
                 no++;for(ii=0;ii<10;++ii)Copy(&I[no][ii],&temp[ii]);
                 OutputGrammar(I[no],10);
                 getch();
            }
        }
    Rule tmp;
    strcpy(tmp.NT,r[0].NT);
    strcpy(tmp.T[0],r[1].NT);
    strcpy(tmp.T[1],".");
    for(i=2;i<10;++i)
    strcpy(tmp.T[i],"\0");
    //for(i=0;i<=no;++i)
    //{for(j=0;j<NTno+Tno;++j)
    //printf("%7d",gototable[i][j]);printf("\n");}
    for(i=0;i<=no;++i)
    for(j=NTno;j<NTno+Tno;++j)
    {
      if(SearchShift(I,NTT[j].s,i))
        sprintf(a[i][j-NTno].s,"s%d",gototable[i][j]);
      else if(SearchAccept(I,i,tmp))strcpy(a[i][Tno-1].s,"acc");
        SearchReduce(I,i,r,a,Rno,NTno,Tno,NTT);
    }
    for(i=0;i<=no;++i)
        for(j=0;j<NTno;++j)
            if(gototable[i][j]!=-1)
                sprintf(a[i][Tno+j].s,"%d",gototable[i][j]);
    getch();
    cout<<endl;
    clrscr();
    printf("\n              Generated Parsing Table");
    printf("\n-------------------------------------------------------------------\n");
    printf("State");
    printf("%5s",NTT[6].s);
    for(i=NTno;i<NTno+Tno;++i)if(i!=6)printf("%5s",NTT[i].s);
    for(i=0;i<NTno;++i)printf("%5s",NTT[i].s);
    printf("\n");
    for(i=0;i<=no;++i)
    {
         printf("%5d",i);
         printf("%5s",a[i][3].s);
         for(j=0;j<NTno+Tno;++j)
         if(j!=3)printf("%5s",a[i][j].s);printf("\n");}
         getch();
    }
 
 void FIRST(char* s,int NTno,int Tno,String* NTT,String* FirstSet)
 {
    for(int i=NTno;i<NTno+Tno;++i)
        if(!strcmp(s,NTT[i].s))
            strcpy(FirstSet[0].s,s);
 }
 
 int en(char* s)
 {
    int i,j=1;
    for(i=0;i<strlen(s);++i)
    {
         if(s[i]=='\n' || s[i]==' ' || s[i]=='(' || s[i]==')' || s[i]=='-' || (s[i]>=48 && s[i]<=57))
            printf("%c",s[i]);
         else if(s[i]>74)printf("%c",s[i]-10);
         else printf("%c",'Z'-('J'-s[i]));
    }
    return(j);
 }
 
void main()
 {
    String NTT[15];
    String Action[20][12];
    Rule r[20],I[20][10];
    int Rno=9,NTno=3,Tno=9;
 
    strcpy(NTT[3].s,"+");
    strcpy(NTT[4].s,"-");
    strcpy(NTT[5].s,"*");
    strcpy(NTT[6].s,"/");
    strcpy(NTT[7].s,"^");
    strcpy(NTT[8].s,"(");
    strcpy(NTT[9].s,"id");
    strcpy(NTT[10].s,")");
    strcpy(NTT[11].s,"$");
 
    strcpy(NTT[0].s,"E");
    strcpy(NTT[1].s,"T");
    strcpy(NTT[2].s,"F");
 
    for(int i=0;i<Rno;++i)
    for(int j=0;j<10;++j)
    {strcpy(r[i].T[j],"\0");
    r[i].function=NULL;}
 
    for(i=0;i<20;++i)
    for(j=0;j<10;++j)
    {
        strcpy(I[i][j].NT,"\0");
        for(int k=0;k<10;++k)
            strcpy(I[i][j].T[k],"\0");
    }
 
    strcpy(r[0].NT,"E");strcpy(r[0].T[0],"E");
    strcpy(r[0].T[1],"+");strcpy(r[0].T[2],"T");
    strcpy(r[1].NT,"E");strcpy(r[1].T[0],"E");
    strcpy(r[1].T[1],"-");strcpy(r[1].T[2],"T");
    strcpy(r[2].NT,"E");strcpy(r[2].T[0],"T");
    strcpy(r[3].NT,"T");strcpy(r[3].T[0],"T");
    strcpy(r[3].T[1],"*");strcpy(r[3].T[2],"F");
    strcpy(r[4].NT,"T");strcpy(r[4].T[0],"T");
    strcpy(r[4].T[1],"/");strcpy(r[4].T[2],"F");
    strcpy(r[5].NT,"T");strcpy(r[5].T[0],"T");
    strcpy(r[5].T[1],"^");strcpy(r[5].T[2],"F");
    strcpy(r[6].NT,"T");strcpy(r[6].T[0],"F");
    strcpy(r[7].NT,"F");strcpy(r[7].T[0],"(");
    strcpy(r[7].T[1],"E");strcpy(r[7].T[2],")");
    strcpy(r[8].NT,"F");strcpy(r[8].T[0],"id");
 
    clrscr();
    char str1[100];
    strcpy(str1,"\n\n CKXNSZKX NOI\n \n LMCO-SF\n BYVV-99710");
    if(en(str1))
    {
        delay(2000);
        clrscr();
        cout<<endl<<"Grammar";
        cout<<endl<<"-------";
        OutputGrammar(r,Rno);
        getch();
        cout<<endl<<endl<<"Augumented Grammar";
        cout<<endl<<"------------------";
        AugumentGrammar(r,&Rno);
        OutputGrammar(r,Rno);
        getch();
        cout<<endl<<endl<<"Generating Parsing Table";
        for(i=0;i<10;++i)
        {
            delay(500);
            cout<<".";
        }
        for(i=0;i<20;++i)
            for(j=0;j<NTno+Tno;++j)
                strcpy(Action[i][j].s,"\0");
        ConstructSetOfItems(r,I,Rno,NTno,Tno,NTT,Action);
        clrscr();
        UnAugument(r,Rno);
        SLR a(Action,NTno,Tno,Rno,r,NTT);
    }
 }