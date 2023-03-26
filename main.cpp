#include <iostream>
#include <cstring>
#include <time.h>
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
    int getData_an(){return an;}
    int getData_luna(){return luna;}
    int getData_zi(){return zi;}
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
                for(int i=0;i<lungime;i++)
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
        int Lungime(){return lungime;}
        Vector_carti(Vector_carti &t)//constructor de copiere
        {
            lungime=t.lungime;
            capacitate=t.capacitate;
            carti=new string[t.capacitate];
            for(int i=0;i<t.lungime;i++)
                    carti[i]=t.carti[i];
        }
        Vector_carti& operator=(const Vector_carti &a)
        {
            if(this == &a) return *this;
            delete carti;
            carti = new string[a.capacitate];
            for(int i=0;i<a.lungime;i++)
                carti[i]=a.carti[i];
            return *this;
        }
};
class Autor
{
    string nume_autor;
    Vector_carti opere;//clasa corelata prin compunere (2)
public:
    Autor(string nume) :nume_autor(nume),opere(2){}
    void adauga_carte(string titlu)
    {
        opere.adaug_carte(titlu);
    }
    void afiseaza()
    {
        cout<<"~clasa Autor~\n";
        cout<<"Nume autor: "<<nume_autor<<endl;
        cout<<"Opere: ";
        for (int i=0;i<opere.Lungime();++i)
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
    string nume_carte;
    string nume_autor;
    string isbn;
    Data data_publicare;//clasa corelata prin compunere (3)
    string editura_carte;
public:
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
    string DataPublicare()
    {
        return data_publicare.getData();
    }
    string EdituraCarte()
    {
        return editura_carte;
    }
    friend ostream & operator<<(ostream&,Carte&);
    ~Carte(){cout<<"\n Destrustor Carte executed \n";}

};

class Abonamente
{
    int id_abonat;
    string nume_abonat;
    string numar_de_telefon;
    int pret;
    Perioada perioada_abonamet;//clasa corelata prin compunere (4)
public:
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
    ~Abonamente()
    { cout<<"\n Destructor Abonamente executed"<<"\n";}//destructor trivial
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
        cout<<"Abonatul "<<id_abonat<<" a primit o reducere la abonamentul sau de "<<reducere<<"% . Pret nou: "<<pret_nou<<" lei\n";
    }
};
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
    string CarteImp(){return carte_imprumutata;}
    string IsbnImp(){return isbn_carte;}
    int Id_Imp(){return id_abonat_imprumut;}
    string DataImp(){return data_imprumut.getData();}
    string DataRet(){return data_retur.getData();}
    friend ostream & operator<<(ostream &,Imprumuturi& );
    void calcul_returnari();
    ~Imprumuturi(){cout<<"\n Destructor Imprumuturi executed \n";}
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
    data_publicare.setData(da,dl,dz);
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
    out<<"Data publicarii: "<<o_carte.DataPublicare()<<"\n";
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

int main()
{
    string clasa;
    while(true)
    {
        cout<<"(Clase disponibile: Vector_carti, Autor, Editura, Carte, Abonamente, Imprumuturi)"<<endl;
        cout<<"(Clase cu metode pe langa afisare: Vector_carti, Abonamente, Imprumuturi)"<<endl;
        cout<<"Introduceti numele clasei sau 'exit' pentru a iesi: ";
        cin>>clasa;

        if(clasa == "exit")
            break;
        if(clasa=="Vector_carti")
        {
            Vector_carti carti(2);
            carti.adaug_carte("Punguta cu doi bani");
            carti.adaug_carte("Soacra cu trei nurori");
            carti.adaug_carte("Ursul pacalit de vulpe");
            carti.adaug_carte("Pacala");
            cout<<carti.get_carte(0)<<endl;
            cout<<carti.get_carte(1)<<endl;
            cout<<carti.get_carte(2)<<endl;
            cout<<carti.get_carte(3)<<endl;

            cout<<endl<<"La aceasta clasa avem si un constructor de copiere.\nVreti sa il verificati?(Da/Nu)";
            string ok;
            cin>>ok;
            if (ok=="Da")
            {
                int i;
                cout<<"Dati al catelea element din vector vreti sa afisati: ";
                cin>>i;
                Vector_carti carti2 = carti;
                if ( i<carti.Lungime())
                    cout<<"carti2:"<<carti2.get_carte(i)<<endl;
                else
                    cout<<"Ny exista pozitia a "<<i<<"-a in vector! ";
                cout<<endl;
            }
            else
                break;

        }
        if(clasa=="Autor")
        {
            Autor autor("Ion Creanga");
            autor.adauga_carte("Capra cu trei iezi");
            autor.adauga_carte("Danila Prepeleac");
            autor.adauga_carte("Povestea lui Harap-Alb");
            autor.afiseaza();
            cout<<endl;
        }
        if(clasa== "Editura")
            {
                Editura editura("Curtea Veche","www.curteaveche.ro","str.Aurel Vlaicu nr.35,Bucuresti,020091","0744554763");
                editura.afisare();
            }
        if(clasa=="Carte")
        {
            Carte c;
            c.setcarte("Capra cu trei iezi","Ion Creanga","9789736790133",2003,11,04,"Humanitas");
            cout<<c;
            cout<<endl;
        }
        if(clasa=="Abonamente")
        {
            Abonamente a(1023,"Emma Mincu", "0731228390", 50, 2022,03,12,2023,05,19);
            a.afisare();
            cout<<endl<<"La aceasta clasa avem si o metoda de logica business care aplica reduceri la abonamnet.\nVreti sa o aplicati?(Da/Nu)";
            string ok;
            cin>>ok;
            if (ok=="Da")
            {
                int o;
                cout<<"Introduceti un numar pentru marimea reducerii (ex: 50):";
                cin>>o;
                a.reduceri(o);
                cout<<endl;
            }
            else
                break;
        }
        if(clasa=="Imprumuturi")
        {
            Imprumuturi i;
            i.setImprumuturi("Capra cu trei iezi","9786068863283",1023,2023,03,01,0,0,0);
            cout<<i;
            cout<<endl;
            cout<<endl<<"La aceasta clasa avem si o metoda de logica business care verifica returnarile.\nVreti sa o aplicati?(Da/Nu) :";
            string ok;
            cin>>ok;
            if (ok=="Da")
            {
                cout<<endl;
                i.calcul_returnari();
                cout<<endl;
            }
            else
                break;
        }


    }
/*
    cout<<"----afisarea a doua clase\n";
    Carte c;
    c.setcarte("Capra cu trei iezi","Ion Creanga","9789736790133",2003,11,04,"Humanitas");
    cout<<c;
    cout<<endl;
    Imprumuturi i;
    i.setImprumuturi("Capra cu trei iezi","9786068863283",1023,2023,03,01,0,0,0);
    cout<<i;

    //metode de logica business:
    Abonamente a(1023,"Emma Mincu", "0731228390", 50, 2022,03,12,2023,05,19);
    a.reduceri(10);
    cout<<endl;


    i.calcul_returnari();
    cout<<endl;

    Vector_carti carti(2);
    carti.adaug_carte("Punguta cu doi bani");
    carti.adaug_carte("Soacra cu trei nurori");
    carti.adaug_carte("Ursul pacalit de vulpe");
    carti.adaug_carte("Pacala");
    cout<<carti.get_carte(0)<<endl;
    cout<<carti.get_carte(1)<<endl;
    cout<<carti.get_carte(2)<<endl;
    cout<<carti.get_carte(3)<<endl;
    cout<<endl;

    Vector_carti carti2 = carti;
    cout<<"carti2:"<<carti2.get_carte(1)<<endl;
    carti.~Vector_carti();
    cout<<endl;

    Autor autor("Ion Creanga");
    autor.adauga_carte("Capra cu trei iezi");
    autor.adauga_carte("Danila Prepeleac");
    autor.adauga_carte("Povestea lui Harap-Alb");
    autor.afiseaza();
    cout<<endl;

    Carte c;
    c.setcarte("Capra cu trei iezi","Ion Creanga","9789736790133",2003,11,04,"Humanitas");
    cout<<c;
    cout<<endl;

    //afisare clasa imprumuturi
    Imprumuturi i;
    i.setImprumuturi("Capra cu trei iezi","9786068863283",1023,2023,03,01,0,0,0);
    cout<<i;
    cout<<endl;
    i.calcul_returnari();
    cout<<endl;

    Perioada p;
    p.setPerioada(1981,03,01,1998,07,11);
    cout<<p.getPerioada()<<endl;
    cout<<endl;

    Editura editura("Curtea Veche","www.curteaveche.ro","str.Aurel Vlaicu nr.35,Bucuresti,020091","0744554763");
    editura.afisare();
    */
}
