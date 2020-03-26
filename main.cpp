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
    ~Nod() {}

    int getInfo()
    {
        return this->info;
    }
    void setInfo(int x)
    {
        this->info = x;
    }
    Nod *getNext()
    {
        return this->next;
    }
    void setNext(Nod *x)
    {
        this->next=x;
    }
};

class ListaCirculara
{
    Nod *prim;

public:

    ListaCirculara()
    {
        prim = NULL;
    }

    ~ListaCirculara()
    {
        Nod *temp, *p = prim->getNext();
        while(p!=prim)
        {
            temp = p;
            p=p->getNext();
            delete temp;
        }
        delete prim;
    }

    ListaCirculara(const ListaCirculara &lista)
    {
        Nod *listaPrim = lista.getPrim();
        prim = new Nod();
        prim->setInfo(listaPrim->getInfo());

        Nod *p = listaPrim->getNext();
        Nod *copie, *anterior = prim;
        while (p != listaPrim)
        {
            copie = new Nod();
            copie->setInfo(p->getInfo());

            anterior->setNext(copie);

            anterior = copie;
            p = p->getNext();
        }
        anterior->setNext(prim);
    }

    Nod *getPrim() const
    {
        return prim;
    }

    void setPrim(Nod *x)
    {
        prim = x;
    }

    void adaugare(int k, int x)
    {
        if (prim == NULL)
        {
            prim = new Nod();
            prim->setInfo(x);
            prim->setNext(prim);
        }
        else
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
    }

    void stergere(int k)
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

            if (q == prim)
            {
                prim = q -> getNext();
            }

            r->setNext(r->getNext()->getNext());
            cout<<q->getInfo()<<" ";
            delete q;
            r = r->getNext();
            z = r;
        }
        cout<<z->getInfo()<<endl;
        delete z;
        prim = NULL;
    }

    friend istream &operator >> ( istream &in, ListaCirculara &aux);
    friend ostream &operator << ( ostream &out, ListaCirculara &auxo);
    friend ListaCirculara operator + (ListaCirculara &p1, ListaCirculara &p2);
};

ListaCirculara operator + (ListaCirculara &p1, ListaCirculara &p2)
{
    ListaCirculara lista = ListaCirculara();
    Nod *listaPrim = p1.prim;
    Nod *prim = new Nod();
    prim->setInfo(listaPrim->getInfo());
    lista.prim = prim;

    Nod *p = listaPrim->getNext();
    Nod *copie, *anterior = prim;
    while (p != listaPrim)
    {
        copie = new Nod();
        copie->setInfo(p->getInfo());
        anterior->setNext(copie);
        anterior = copie;
        p = p->getNext();
    }
    anterior->setNext(prim);

    Nod *listaPrim2 = p2.prim;
    Nod *prim2 = new Nod();
    prim2->setInfo(listaPrim2->getInfo());
    anterior->setNext(prim2);


    p = listaPrim2->getNext();
    anterior = prim2;
    while (p != listaPrim2)
    {
        copie = new Nod();
        copie->setInfo(p->getInfo());
        anterior->setNext(copie);
        anterior = copie;
        p = p->getNext();
    }
    anterior->setNext(prim);
    return lista;
}

istream &operator >> (istream &in, ListaCirculara &aux)
{
    cout<<"Scrieti numarul de elemente: \n";
    int n, primul, x;
    in>>n;
    cout<<"Scrieti elementele separate prin 'enter' \n";
    in>>primul;
    Nod *prim = new Nod();
    prim->setInfo(primul);
    aux.prim = prim;
    for(int i=2; i<=n; i++)
    {
        in>>x;
        aux.adaugare(i, x);
    }
    return in;
}

ostream &operator << (ostream &out, ListaCirculara &auxo)
{
    Nod *r, *prim;
    r = auxo.prim;
    prim = r;
    if (prim != NULL)
    {
        do
        {
            out<<r->getInfo()<<" ";
            r = r->getNext();
        }
        while(r!=prim);
    }
    out<<prim->getInfo();
    out<<endl;
    return out;
}

int main()
{
    ListaCirculara lista = ListaCirculara();
    cin>>lista;
    int opt, k, x;
    do
    {
        cout<<"1 -> Adaugarea valorii x pe pozitia k\n"
            <<"2 -> Stergerea elementului de pe pozitia k\n"
            <<"3 -> Inversarea elementelor listei\n"
            <<"4 -> Eliminarea elementelor din k in k pana la golirea listei\n"
            <<"5 -> Concatenare de liste\n"
            <<"6 -> Optiunea de oprire\n";

        cout<<"Introduceti o optiune:\n";
        cin>>opt;
        switch(opt)
        {
        case 1:
            cout<<"k = ";
            cin>>k;
            cout<<"x = ";
            cin>>x;
            lista.adaugare(k, x);
            cout<<lista;
            break;
        case 2:
            cout<<"k = ";
            cin>>k;
            lista.stergere(k);
            cout<<lista;
            break;
        case 3:
            lista.inversare();
            cout<<lista;
            break;
        case 4:
            cout<<"k = ";
            cin>>k;
            lista.golire(k);
            break;
        case 5:
            cout<<"Scrieti cea de-a doua lista: \n";
            ListaCirculara lista1 = ListaCirculara();
            cin>>lista1;
            ListaCirculara suma = lista + lista1;
            cout<<suma;
            break;

        }
    }
    while(opt!=6);
    return 0;
}
