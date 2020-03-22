#include <iostream>

using namespace std;
class Nod
{

private:
    int info;
    Nod *next;

public:
    Nod()
    {
        this->info = 0;
        this->next = this;
    }
    Nod(int x)
    {
        this->info = x;
        this->next = this;
    }
    ~Nod()
    {
        //cout<<"deconstructorul a fost apelat"<<endl;
    }

    int getInfo(){
        return this->info;
    }
    void setInfo(int x){
        this->info=x;
    }
    Nod *getNext(){
        return this->next;
    }
    void setNext(Nod *x){
        this->next=x;
    }
};

class Lista_circulara
{
    Nod *prim;

public:

    Lista_circulara(int primInfo)
    {
        prim = new Nod(primInfo);
    }

    Nod *getPrim()
    {
        return prim;
    }
    void setPrim(Nod *x)
    {
        prim = x;
    }


    void Adaugare(int k, int x)
    {
        Nod *r, *q;
        r = prim;
        for (int i=1; i<=k-2; i++)
            r=r->getNext();
        q = new Nod;
        q->setInfo(x);
        q->setNext(r->getNext());
        r->setNext(q);
    }

    void stergerek(int k)
    {
        Nod *r, *q;
        if (k == 1)
        {
            r = prim;
            while (r->getNext()!=prim)
                r = r->getNext();
            q = prim;
            prim = prim->getNext();
            r->setNext(prim);
            delete q;
        }
        else
        {
            r = prim;
            for (int i=1; i<=k-2; i++)
                r = r->getNext();
            q = r->getNext();
            r->setNext(r->getNext()->getNext());
            delete q;
        }
    }

    void inversare()
    {
        Nod *r, *q, *z;
        if(prim->getNext()->getNext() != prim && prim->getNext() != prim)
        {
            r = prim;
            q = prim->getNext();
            z = q->getNext();
            while(q != prim)
            {
                q->setNext(r);
                r = q;
                q = z;
                z = z->getNext();
            }
            q->setNext(r);
        }
    }
    void golire(int k)
    {
        Nod *z, *r, *q;
        z = prim;
        r = prim;
            while(z->getNext() != z)
            {
                for (int i=1; i<=k-2; i++)
                    r = r->getNext();
                q = r->getNext();
                r->setNext(r->getNext()->getNext());
                cout<<q->getInfo()<<" ";
                delete q;
                r = r->getNext();
                z = r;
            }
            cout<<z->getInfo()<<endl;
            delete z;
            delete prim;
            prim = NULL;
    }
    friend istream &operator >> ( istream &in, Lista_circulara &aux);
    friend ostream &operator << ( ostream &out, Lista_circulara &auxo);
    friend Lista_circulara operator + (Lista_circulara &p1, Lista_circulara &p2);
};

Lista_circulara operator + (Lista_circulara &p1, Lista_circulara &p2)
{
    Nod *u1, *u2, *r;
    u1 = p1.getPrim();
    r = u1;
    Lista_circulara Lista = Lista_circulara(u1->getInfo());
    Lista.setPrim(u1);
    while (r->getNext()!=u1)
    {
        r = r->getNext();
    }
    r->setNext(p2.getPrim());
    u2 = p2.getPrim();
    r = u2;
    while (r->getNext()!=u2)
    {
        r = r->getNext();
    }
    r->setNext(p1.getPrim());
    return Lista;
}

istream &operator >> (istream &in, Lista_circulara &aux)
{
    cout<<"Scrieti numarul de elemente: \n";
    int n, primul, x;
    in>>n;
    cout<<"Scrieti elementele separate prin 'enter' \n";
    in>>primul;
    aux.setPrim(new Nod(primul));
    for(int i=2;i<=n;i++)
    {
        in>>x;
        aux.Adaugare(i, x);
    }
    return in;
}

ostream &operator << (ostream &out, Lista_circulara &auxo)
{
    Nod *r, *prim;
    r = auxo.getPrim();
    prim = r;
    do
    {
        out<<r->getInfo()<<" ";
        r = r->getNext();
    }while(r!=prim);
    out<<prim->getInfo();
    out<<endl;
    return out;
}

int main()
{
    Lista_circulara *lista = new Lista_circulara(1);
    cin>>*lista;
    cout<<"1 -> Adaugare valorii x pe pozitia k.\n"
    <<"2 -> Stergerea elementului de pe pozitia k.\n"
    <<"3 -> Inversarea elementelor listei.\n"
    <<"4 -> Eliminarea elementelor din k in k pana la golirea listei\n"
    <<"5 -> Concatenare de liste\n"
    <<"6 -> Optiunea de oprire.\n";
    int opt, k, x;
    cout<<"Introduceti o optiune:\n";
    cin>>opt;
    while(opt!=6)
    {
        switch(opt){
        case 1:
            cout<<"k = ";
            cin>>k;
            cout<<"x = ";
            cin>>x;
            lista->Adaugare(k, x);
            cout<<*lista;
            break;
        case 2:
            cout<<"k = ";
            cin>>k;
            lista->stergerek(k);
            cout<<*lista;
            break;
        case 3:
            lista->inversare();
            cout<<*lista;
            break;
        case 4:
            cout<<"k = ";
            cin>>k;
            lista->golire(k);
            cout<<*lista;
            break;
        case 5:
            cout<<"Scrieti cea de-a doua lista: \n";
            Lista_circulara *lista1 = new Lista_circulara(1);
            cin>>*lista1;
            Lista_circulara suma = *lista + *lista1;
            cout<<suma;
            break;

        }
        cout<<"Introduceti o optiune:\n";
        cin>>opt;
    }
    return 0;
}
