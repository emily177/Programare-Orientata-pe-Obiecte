#include <iostream>
#include <cstring>
#include <time.h>
#include <vector>
using namespace std;

class Data
{
    int an,luna,zi;
public:
    void setData(int a,int l, int z)//metoda set (1)
    {
        an=a;
        luna=l;
        zi=z;
    }
    int getData_an()
    {
        return an;
    }
    int getData_luna()
    {
        return luna;
    }
    int getData_zi()
    {
        return zi;
    }
    string getData()//metoda get(1)
    {
        string s= to_string(zi)+"."+ to_string(luna) +"."+ to_string(an);
        if (zi%10==0 && zi/10==0 && luna%10==0 && luna/10==0 && an/10==0 && an/100==0 && an/1000==0)
            s="-- -- ----";
        return s;
    }
    friend class Perioada;
};
class Perioada
{
    Data data_inceput;//clasa corelata prin compunere (1)
    Data data_sfarsit;
public:
    void setPerioada(int di_an,int di_luna,int di_zi,int ds_an,int ds_luna,int ds_zi)//metoda set (2)
    {
        data_inceput.setData(di_an,di_luna,di_zi);
        data_sfarsit.setData(ds_an,ds_luna,ds_zi);
    }
    string getPerioada()//metoda get(2)
    {
        string o_perioada =data_inceput.getData() + "~" + data_sfarsit.getData() ;
        return o_perioada;
    }
    friend class Autor;
};
class Vector_carti
{
    string* carti;
    int lungime;
    int capacitate;
public:
    Vector_carti(int n)
    {
        capacitate=n;
        lungime=0;
        carti= new string[capacitate];
    }
    ~Vector_carti()//destructor netrivial
    {
        delete[] carti;
    }
    void adaug_carte(string titlu)
    {
        if(lungime < capacitate)
        {
            carti[lungime]=titlu;
            lungime++;
        }
        else
        {
            string * temp= new string[capacitate*2];
            for(int i=0; i<lungime; i++)
                temp[i] = carti[i];
            delete[] carti;
            carti=temp;
            capacitate*=2;
            carti[lungime]=titlu;
            lungime++;
        }
    }
    string get_carte(int pozitie)
    {
        if (pozitie>=0 && pozitie<lungime)
            return carti[pozitie];
        else
            return "";
    }
    int Lungime()
    {
        return lungime;
    }
    Vector_carti(Vector_carti &t)//constructor de copiere
    {
        lungime=t.lungime;
        capacitate=t.capacitate;
        carti=new string[t.capacitate];
        for(int i=0; i<t.lungime; i++)
            carti[i]=t.carti[i];
    }
    Vector_carti& operator=(const Vector_carti &a)
    {
        if(this == &a) return *this;
        delete carti;
        carti = new string[a.capacitate];
        for(int i=0; i<a.lungime; i++)
            carti[i]=a.carti[i];
        return *this;
    }
};
class Autor
{
    string nume_autor;
    Vector_carti opere;//clasa corelata prin compunere (2)
public:
    Autor(string nume) :nume_autor(nume),opere(2) {}
    void adauga_carte(string titlu)
    {
        opere.adaug_carte(titlu);
    }
    void afiseaza()
    {
        cout<<"~clasa Autor~\n";
        cout<<"Nume autor: "<<nume_autor<<endl;
        cout<<"Opere: ";
        for (int i=0; i<opere.Lungime(); ++i)
            cout<<opere.get_carte(i)<<",";
        cout<<endl;
    }

};
class Editura
{
    string nume_editura;
    string site;
    string locatie_sediu;
    string numar_telefon;
public:
    Editura()//constructor fara parametrii(2)
    {
        nume_editura="Editura standard";
        site="www.editura.ro";
        locatie_sediu="Bucuresti";
        numar_telefon="0755552222";
    }
    Editura(string nume,string _site,string _loc,string nr)//constructor cu parametri (2)
    {
        nume_editura=nume;
        site=_site;
        locatie_sediu=_loc;
        numar_telefon=nr;
    }
    Editura(Editura &a)//constructor de copiere(2)
    {
        nume_editura=a.nume_editura;
        site=a.site;
        locatie_sediu=a.locatie_sediu;
        numar_telefon=a.numar_telefon;
    }
    Editura &operator =(const Editura &a)//supraincarcarea operatorului = (2)
    {
        nume_editura=a.nume_editura;
        site=a.site;
        locatie_sediu=a.locatie_sediu;
        numar_telefon=a.numar_telefon;
        return *this;
    }
    void afisare()
    {
        cout<<"Nume editura: "<<nume_editura<<"\n";
        cout<<"Site: "<<site<<"\n";
        cout<<"Locatia sediului: "<<locatie_sediu<<"\n";
        cout<<"Numar de telefon: "<<numar_telefon<<"\n";
    }
};
class Carte
{
protected:
    string nume_carte;
    string nume_autor;
    string isbn;
    string editura_carte;
    static int nr_carti;
    static int apel_destructor;
public:
    Carte(string nume="-", string autor="-", string i="-",string editura="-")
        :nume_carte{nume},nume_autor{autor},isbn{i},editura_carte{editura}
    {
        nr_carti++;
    }
    Carte()
    {
        nume_autor="-";
        nume_carte="-";
        isbn="-";
        editura_carte="-";
        nr_carti++;
    }
    void setcarte(string nc,string na,string i,int da,int dl,int dz,string editura);//metoda set (4)
    //metode get (5 metode) (4):
    string Nume_carte()
    {
        return nume_carte;
    }
    string Autor_carte()
    {
        return nume_autor;
    }
    string Cod_carte()
    {
        return isbn;
    }
    //string DataPublicare()
    //{
    //   return data_publicare.getData();
    //}
    string EdituraCarte()
    {
        return editura_carte;
    }
    friend ostream & operator<<(ostream&,Carte&);
    virtual ~Carte()
    {
       apel_destructor++;
    }
    virtual string referinta()
    {
        cout<<"Referinta carte\n";
    }
    virtual string afisare() {}
    static void Numar_carti()
    {
        cout<<"Au fost inregistrate "<<nr_carti<<" tipuri de carti\n";
    }
    static void Destructori()
    {
        cout<<"Destructorul carte a fost apelat de "<<apel_destructor<<" ori\n";
    }
};
int Carte::nr_carti=0;
int Carte::apel_destructor=0;
class Abonamente
{
protected:
    static int numar_abonamente;
    int id_abonat;
    string nume_abonat;
    string numar_de_telefon;
    int pret;
    Perioada perioada_abonamet;//clasa corelata prin compunere (4)
protected:
    Abonamente()//constructor fara parametrii(3)
    {
        id_abonat=0000;
        nume_abonat="Nume standard";
        numar_de_telefon="Numar standard";
        pret=30;
        perioada_abonamet.setPerioada(0,0,0,0,0,0);
    }
    Abonamente(int id,string n_ab,string nr_t,int pret_ab, int pi_an,int pi_luna,int pi_zi,int ps_an,int ps_luna,int ps_zi)
    //constructor cu parametrii(3)
    {
        id_abonat=id;
        nume_abonat=n_ab;
        numar_de_telefon=nr_t;
        pret=pret_ab;
        perioada_abonamet.setPerioada(pi_an,pi_luna,pi_zi,ps_an,ps_luna,ps_zi);
    }
    void afisare() //metoda fisare
    {
        cout<<"id_abonat: "<<id_abonat;
        cout<<"\nnume_abonat: "<<nume_abonat;
        cout<<"\nnumar_de_telefon: "<<numar_de_telefon;
        cout<<"\npret: "<<pret;
        cout<<"\nperioada_abonament: "<<perioada_abonamet.getPerioada()<<endl;
    }
    void reduceri(int reducere)//metoda de logica business(1)
    {
        int pret_nou=pret - pret*reducere/100;
        cout<<"Abonatul "<<id_abonat<<" a primit o reducere la abonamentul sau de "<<reducere<<"% . Pret nou: "<<pret_nou<<" lei (pret vechi: "<<pret<<" )\n";
    }
    static int Numar_abonamente()
    {
        return numar_abonamente;
    }
};
int Abonamente::numar_abonamente=0;
class Imprumuturi
{
    string carte_imprumutata;
    string isbn_carte;
    int id_abonat_imprumut;
    Data data_imprumut;//clasa corelata prin compunere (5)
    Data data_retur;
public:
    void setImprumuturi(string,string,int,int,int,int,int,int,int);// declarare metoda set (5)
    //metode get (5)
    string CarteImp()
    {
        return carte_imprumutata;
    }
    string IsbnImp()
    {
        return isbn_carte;
    }
    int Id_Imp()
    {
        return id_abonat_imprumut;
    }
    string DataImp()
    {
        return data_imprumut.getData();
    }
    string DataRet()
    {
        return data_retur.getData();
    }
    friend ostream & operator<<(ostream &,Imprumuturi& );
    void calcul_returnari();
    ~Imprumuturi()
    {
        cout<<"\n Destructor Imprumuturi executed \n";
    }
};

void Imprumuturi::setImprumuturi(string c,string i,int id,int di_an,int di_luna,int di_zi,int dr_an,int dr_luna,int dr_zi)//definire metoda set inafara clasei
{
    carte_imprumutata=c;
    isbn_carte=i;
    id_abonat_imprumut=id;
    data_imprumut.setData(di_an,di_luna,di_zi);
    data_retur.setData(dr_an,dr_luna,dr_zi);
}
void Carte::setcarte(string nc,string na,string i,int da,int dl,int dz,string editura)//definire metoda set inafara clasei
{
    nume_carte=nc;
    nume_autor=na;
    isbn=i;
    // data_publicare.setData(da,dl,dz);
    editura_carte=editura;
    //tip_carte=c;
}
ostream & operator<<(ostream &out,Imprumuturi &x)//supraincarcarea operatorului << pentru a face afisarea clasei
{
    out<<"-Clasa Imprumuturi-"<<"\n";
    out<<"Numele cartii imprumutate: "<<x.CarteImp()<<"\n";
    out<<"Codul cartii: "<<x.IsbnImp()<<"\n";
    out<<"Id-ul abonatului: "<<x.Id_Imp()<<"\n";
    out<<"Data imprumutului: "<<x.DataImp()<<"\n";
    out<<"Data cand s a returnat: "<<x.DataRet()<<"\n";
    return out;
}
ostream & operator<<(ostream &out, Carte &o_carte)
{
    out<<"-Clasa carte-"<<"\n";
    out<<"Titlul cartii: "<<o_carte.Nume_carte()<<"\n";
    out<<"Autor: "<<o_carte.Autor_carte()<<"\n";
    out<<"Id-ul cartii(ISBN):"<<o_carte.Cod_carte()<<"\n";
    //out<<"Data publicarii: "<<o_carte.DataPublicare()<<"\n";
    out<<"Editura: "<<o_carte.EdituraCarte()<<"\n";
    return out;
}
void Imprumuturi:: calcul_returnari() //metoda de logica business(2)
{
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

    int day = aTime->tm_mday;
    int month = aTime->tm_mon + 1; // Month este 0 - 11, adaugam 1 ca sa obtinem ianuarie-decembrie 1-12
    int year = aTime->tm_year + 1900;

    if(data_retur.getData_an() != 0 && data_retur.getData_luna() != 0 && data_retur.getData_zi() != 0)
    {
        cout<<"Abonatul "<<id_abonat_imprumut<<" a returnat cartea cu succes pe data de. ";

        int intarziere_retur_an = data_retur.getData_an() - data_imprumut.getData_an();
        int intarziere_retur_luna = data_retur.getData_luna()- data_imprumut.getData_luna() ;
        int intarziere_retur_zi = data_retur.getData_zi() - data_imprumut.getData_zi() ;

        if(intarziere_retur_an !=0 || intarziere_retur_luna>1 || (intarziere_retur_luna==1 && intarziere_retur_zi>0))
        {
            cout<<"Predata cu intarziere (peste 30 de zile) :";
            if(intarziere_retur_zi>0)
                cout<<intarziere_retur_zi<<" zile ";
            if(intarziere_retur_zi>0 && intarziere_retur_luna>0)
                if(intarziere_retur_an!=0)
                    cout<<", ";
                else    cout<<"si ";
            if(intarziere_retur_luna>0)
                cout<<intarziere_retur_luna<<" luni ";
            if(intarziere_retur_luna>0 && intarziere_retur_an!=0)
                cout<<"si ";
            if(intarziere_retur_an !=0)
                cout<<intarziere_retur_an<<" ani ";
        }
        else cout<<"(Predata la timp.)";
    }
    else
    {
        cout<<"Abonatul "<<id_abonat_imprumut<<" NU a returnat cartea cu codul "<<isbn_carte<< "\n";
        cout<<"Data realizarii imprumutului:"<<data_imprumut.getData_zi()<<" "<<data_imprumut.getData_luna()<<" "<<data_imprumut.getData_an()<<"\n";
        cout<<"Data curenta: "<<day<<" "<<month<<" "<<year<< endl;

        int intarziere_an = year - data_imprumut.getData_an();
        int intarziere_luna = month - data_imprumut.getData_luna();
        int intarziere_zi = day - data_imprumut.getData_zi();

        if(intarziere_an !=0 || intarziere_luna>1 || (intarziere_luna==1 && intarziere_zi>0))
        {
            cout<<"A FOST DEPASIT TERMENUL DE RETUNARE (de 30 de zile) cu: ";
            if(intarziere_zi>0)
                cout<<intarziere_zi<<" zile ";
            if(intarziere_zi>0 && intarziere_luna>0)
                if(intarziere_an!=0)
                    cout<<", ";
                else    cout<<"si ";
            if(intarziere_luna>0)
                cout<<intarziere_luna<<" luni ";
            if(intarziere_luna>0 && intarziere_an!=0)
                cout<<"si ";
            if(intarziere_an !=0)
                cout<<intarziere_an<<" ani ";
        }
        else
        {
            cout<<"Limita pentru returnare inca nu a fost depasita. Timp ramas: ";
            if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
                cout<<31 - day + data_imprumut.getData_zi()<< " zile";
            if(month==4 || month==6 || month==9 || month==11)
                cout<<30 - day + data_imprumut.getData_zi()<< " zile";
            if(month==2)
                if(year%4==0)
                    cout<<29 - day + data_imprumut.getData_zi()<< " zile";
                else cout<<28 - day + data_imprumut.getData_zi()<< " zile";

        }

    }
    cout<<endl;
}

class Ziar:virtual public Carte
{
    int nr_articole;
    static int destructor_ziar;
public:
    Ziar(string nume="-", string autor="-", string i="-",string editura="-",int n=0):Carte(nume,autor,i,editura),nr_articole{n} {}
    int Articole()
    {
        return nr_articole;
    }
    string referinta()
    {
        cout<<"Referinta Ziar : ";
        cout<<nume_autor<<","<<nume_carte<<" ( editura: "<<editura_carte<<" )\n";
    }
    string afisare()
    {
        cout<<"Numele ziarului : "<<nume_carte<<endl;
        cout<<"     Titlul ziarului: "<<nume_autor<<endl;
        cout<<"     Cod ziar: "<<isbn<<endl;
        cout<<"     Editura: "<<editura_carte<<endl;
        cout<<"     Numarul de articole din ziar: "<<nr_articole<<endl;
    }

};

class Carte_povesti: virtual public Carte
{
protected:
    string tip_carte;
public:
    Carte_povesti(string nume="-", string autor="-", string i="-",string editura="-", string tip="comun")
        :Carte{nume,autor,i,editura},tip_carte{tip}
    {
    }
    string get_tip_carte()
    {
        return tip_carte;
    }
    string afisare()
    {
        cout<<"Titlul Cartii : "<<nume_carte<<endl;
        cout<<"     Autor: "<<nume_autor<<endl;
        cout<<"     Cod carte: "<<isbn<<endl;
        cout<<"     Editura: "<<editura_carte<<endl;
        cout<<"     Categorie: "<<tip_carte<<endl;
    }
    string referinta()
    {
        cout<<"Referinta Carte povesti: ";
        string word="";
        for(auto x: nume_autor)
        {
            if(x==' ')
            {
                cout<<word[0]<<".";
                word="";
            }
            else
            {
                word=word+x;
            }
        }
        cout<<word<<", "<<nume_carte<<" ( editura: "<<editura_carte<<" ) , categorie: "<<tip_carte<<endl;

    }


};
class Revista: public Ziar, public Carte_povesti
{
public:
    Revista(string nume="-", string autor="-", string i="-",string editura="-", string tip="comun",int articole=0)
        :Ziar(nume,autor,i,editura,articole),Carte_povesti(nume,autor,i,editura,tip),Carte(nume,  autor,  i,editura) {}
    string referinta()
    {
        cout<<"Referinta revista: ";
        cout<<nume_carte<<", publicat de "<<editura_carte<<" in categoria "<<tip_carte<<endl;
    }
    string afisare()
    {
        cout<<"Numele revistei : "<<nume_carte<<endl;
        cout<<"     Titlul revistei: "<<nume_autor<<endl;
        cout<<"     Cod revista: "<<isbn<<endl;
        cout<<"     Editura: "<<editura_carte<<endl;
        //cout<<"     Numarul de articole din revista: "<<Articole()<<endl;
        //cout<<"     Tipul/Categoria de revista: "<<tip_carte<<endl;
    }

};


class Abonament_premiu: private Abonamente
{
    string email;
public:
    Abonament_premiu(int id=0,string n_ab="-",string nr_t="-",int pret_ab=0, int pi_an=0,int pi_luna=0,int pi_zi=0,int ps_an=0,int ps_luna=0,int ps_zi=0,string n_email="")
        :Abonamente(id,n_ab,nr_t, pret_ab, pi_an, pi_luna, pi_zi, ps_an, ps_luna, ps_zi),email{n_email} {}
    void reduceri(int reducere)
    {
        int pret_nou=pret - pret*reducere/100 -pret*20/100;
        cout<<"Abonatul "<<nume_abonat<<" are abonament premiu si i se aplica 20% reducere peste reducerea standard\n";
        cout<<"     Pretul vechi este "<<pret<<". I se aplica o reducere standard de "<<reducere<<" % . Noul pret este "<<pret_nou<<endl;
    }

};
class Cladire
{
public:
    virtual double suprafata()=0;
    virtual double perimetru()=0;
    virtual ~Cladire()=0;
};
Cladire::~Cladire()
{
    cout<<"Destructor Cladire\n";
}
class Stoc
{
    int numar_stocat;
public :
    virtual long long capacitate()=0;
    virtual ~Stoc()=0;
};
Stoc::~Stoc()
{
    cout<<"Destructor Stoc\n";
}

class Biblioteca: public Cladire, public Stoc
{
    int lungime;
    int latime;
public:
    double suprafata()
    {
        return lungime*latime;
    }
    double perimetru()
    {
        return 2*(lungime+latime);
    }
    long long capacitate()
    //calculam pentru cate carti avem spatiu presupunand ca pe 30m2 putem depozita 500 de carti
    {
        long long m=((lungime*latime)/30)*500;
        cout<<"capacitatea bibliotecii este de "<<m<<" carti \n";

    }
    Biblioteca(int l,int L)
    {
        latime=l;
        lungime=L;
    }
    Biblioteca()
    {
        cout<<"Constructor Biblioteca\n";
    }
    int get_latime()
    {
        return latime;
    }
    int get_lungime()
    {
        return lungime;
    }
};
class Exceptie : public exception
{
public:
    char * what ()
    {
        return "Custom C++ Exception";
    }
};


int main()
{
    cout<<"     Verificare constructor cu lista de initializare:\n";
    Carte_povesti x("Harry Potter","J.K.Rowling","02398","Arthur","fantezie");
    cout<<x.Nume_carte()<<"\n";
    cout<<x.Autor_carte()<<endl;
    cout<<x.Cod_carte()<<endl;
    cout<<x.EdituraCarte()<<endl;
    cout<<x.get_tip_carte()<<endl;

    cout<<"\n   Verificare metoda virtuala:\n";
    Biblioteca b(100,783);
    b.capacitate();

    cout<<"\n   Vector de referinte la diferite clase:\n";
    vector <Carte*> vec;
    vec.push_back(new Carte_povesti("Craiasa Zapezii","Hans Cristian Anderson","0934","Arthur","poveste"));
    vec.push_back (new Ziar("News","ziar","234","Antena 1",10));
    vec.push_back(new Revista("Mondana","revista","1234","Amelia","fashion",9));

    for(auto i=vec.begin(); i!= vec.end(); ++i)
    {
        (*i)->referinta();
    }

    for(auto i=vec.begin(); i!= vec.end(); ++i)
    {
        delete *i;
    }
    vec.clear();
    cout<<endl;

    Abonament_premiu a(1023,"Emma Mincu", "0731228390", 50, 2022,03,12,2023,05,19,"mincu@gmail.com");
    a.reduceri(30.2);
     cout<<"\n   Aplicare metode statice :\n";
    x.Numar_carti();
    x.Destructori();
    cout<<endl;

    return 0;
}
