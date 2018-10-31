#include <bits/stdc++.h>
using namespace std;
class symbolInfo
{
public:
    char name[40];
    char type[40];
    class symbolInfo *next;
};

class symbolTable
{
    symbolInfo **arr;
    int arrsize;
public:
    symbolTable(int a);
    int myhash(char *p);
    int search(char *p);
    int insert(char *n,char *t);
    int mydelete(char *p);
    void print();
    ~symbolTable();
};
symbolTable::symbolTable(int a)
{
    arr=(symbolInfo **)malloc(a*sizeof(symbolInfo *));
    for(int i=0;i<a;i++) arr[i]=0;
    arrsize=a;
}

int symbolTable::myhash(char *p)
{
    int s=0;
    int l=strlen(p);
    for(int i=0;i<l;i++){
        int temp=(int) p[i];
        s+=temp;
    }
    return (s%arrsize);
}
int symbolTable::search(char *p)
{
    int j=0,i=myhash(p);
    symbolInfo *h=arr[i];
    while(1){
        if(h==0) break;
        if(strcmp(h->name,p)==0) {
            return j;
        }
        h=h->next;
        j++;
    }
    return -1;
}

int symbolTable::insert(char *n,char *t)
{
    if(search(n)!=-1){
        return -1;
    }
    else{
        int j=0,i=myhash(n);
        symbolInfo *nw;
        nw=new symbolInfo;
        strcpy(nw->name,n);
        strcpy(nw->type,t);
        nw->next=0;
        if(arr[i]==0){
            arr[i]=nw;
        }
        else{
            j++;
            struct symbolInfo *h=arr[i];
            while(h->next!=0) {
                h=h->next;
                j++;
            }
            h->next=nw;
        }
        return j;
    }
}

int symbolTable::mydelete(char *p)
{
	if(search(p)==-1){
        return -1;
	}
	else{
        symbolInfo *temp, *prev ;
        int j=0,i=myhash(p);
        temp = arr[i];
        while (temp != 0)
        {
            if (strcmp(temp->name,p)==0) break;
            prev = temp;
            temp = temp->next ;
            j++;
        }
        if (temp == arr[i])
        {
            arr[i]=arr[i]->next;
            delete temp ;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
        }
        return j ;
	}
}

void symbolTable::print()
{
    cout<<"P"<<endl;
    for(int i=0;i<arrsize;i++){
        cout<<i<<"-> ";
        symbolInfo *h=arr[i];
        while(h!=0){
            cout<<"<"<<h->name<<","<<h->type<<"> ";
            h=h->next;
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}
symbolTable::~symbolTable()
{
    free(arr);
}

int main()
{
    freopen("input.txt","r",stdin);
    int t;
    cin>>t;
    symbolTable ob(t);
    char a,b[40],c[40];
    while(cin>>a){
        if(a=='P') ob.print();
        else if(a=='I'){
            int x,y;
            cin>>b>>c;
            x=ob.myhash(b);
            y=ob.insert(b,c);
            if(y==-1) cout<<b<<" already exists"<<endl;
            else cout<<b<<" Inserted at position "<<x<<","<<y<<endl;
            cout<<endl<<endl;
        }
        else if(a=='D'){
            cin>>b;
            int x,y;
            x=ob.myhash(b);
            y=ob.mydelete(b);
            if(y==-1) cout<<b<<" not found"<<endl;
            else cout<<b<<" deleted from position "<<x<<","<<y<<endl;
            cout<<endl<<endl;
        }
        else if(a=='L'){
            cin>>b;
            int y=ob.search(b);
            if(y==-1) cout<<b<<" not found"<<endl;
            else cout<<b<<" found at "<<ob.myhash(b)<<","<<y<<endl;
            cout<<endl<<endl;
        }
    }
    return 0;
}
