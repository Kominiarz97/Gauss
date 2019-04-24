#include <iostream>
#include<conio.h>
#include<windows.h>
#include<math.h>
using namespace std;

void Wczytaj(double *tabx,double *taby,int ilosc)
{

    int spr;
    for(int i=0;i<ilosc;i++)
    {
        cout<<"Podaj "<<ilosc<<" x i y"<<endl;
        cout<<"x["<<i<<"]: ";
        cin>>tabx[i];
        cout<<"y["<<i<<"]: ";
        cin>>taby[i];
        system("cls");
        spr=0;
        for(int j=0;j<i;j++)
        {
            if(tabx[i]==tabx[j])
            {
                cout<<"Istnieje juz taki punkt, podaj inny"<<endl;
                spr=1;
            }
        }
        if(spr==1)
        {
            i--;
        }
    }
    system("cls");

}
double SumaX(double *tabx,int ilosc)
{
    double suma=0;
    for(int i=0;i<ilosc;i++)
    {
        suma+=tabx[i];
    }
    return suma;
}
double SumaY(double *taby,int ilosc)
{
    double suma=0;
    for(int i=0;i<ilosc;i++)
    {
        suma+=taby[i];
    }
    return suma;
}
double SumaXY(double *tabx,double *taby,int ilosc)
{
    double suma=0;
    for(int i=0;i<ilosc;i++)
    {
        suma+=tabx[i]*taby[i];
    }
    return suma;
}
double SumaXKwadrat(double *tabx,int ilosc)
{
    double suma=0;
    for(int i=0;i<ilosc;i++)
    {
        suma+=tabx[i]*tabx[i];
    }
    return suma;
}
double Wyznaczniki(double *tabx,double *taby,int ilosc,double *A0,double *A1)
{
    double WyznGlowny=(ilosc*SumaXKwadrat(tabx,ilosc))-(SumaX(tabx,ilosc)*SumaX(tabx,ilosc));
    double WyznA0=(SumaY(taby,ilosc)*SumaXKwadrat(tabx,ilosc))-(SumaX(tabx,ilosc)*SumaXY(tabx,taby,ilosc));
    double WyznA1=(ilosc*SumaXY(tabx,taby,ilosc))-(SumaY(taby,ilosc)*SumaX(tabx,ilosc));
    //cout<<WyznGlowny<<"           "<<WyznA0<<"             "<<WyznA1<<endl;//test
    *A0=WyznA0/WyznGlowny;
    *A1=WyznA1/WyznGlowny;
}
double Logarytmuj(double*taby,int ilosc)
{
    for(int i=0;i<ilosc;i++)
    {
        taby[i]=log(taby[i]);
    }
}
//---------------------------------------------------------------------------------------------------------------------------
int main()
{
    int zadanie,wyb1,wyb2,ilosc;
    cout<<"Metoda najmniejszych kwadratow"<<endl<<"Wybierz dla jakiej funkcji: "<<endl<<"1.Funkcja liniowa (zad 2)"<<endl<<"2.Funkcja wykaldnicza (zad 4)"<<endl;
    cin>>zadanie;
    if(zadanie==1)
    {
        system("cls");
        cout<<"Wybierz:"<<endl<<"1.Dane z zadania 2"<<endl<<"2.Wlasne dane"<<endl;
        cin>>wyb1;
        if(wyb1==1)
        {
            system("cls");
            ilosc=4;
            system("cls");
            double *tabx=new double[ilosc];
            double *taby=new double[ilosc];
            tabx[0]=0;
            taby[0]=-3;
            tabx[1]=1;
            taby[1]=4;
            tabx[2]=2;
            taby[2]=15;
            tabx[3]=3;
            taby[3]=30;
            cout<<"x | "<<0<<"  | "<<1<<"  | "<<2<<"  | "<<3<<endl;
            cout<<"----------------------"<<endl;
            cout<<"y | "<<-3<<" | "<<4<<"  | "<<15<<" | "<<30<<endl<<endl;
            double A0,A1;
            Wyznaczniki(tabx,taby,ilosc,&A0,&A1);
            cout<<"Wzor funkcji: g(x)="<<A0<<"+"<<A1<<"x"<<endl;
        }else
        {
            system("cls");
            cout<<"Podaj ilosc punktow: ";
            cin>>ilosc;
            system("cls");
            double *tabx=new double[ilosc];
            double *taby=new double[ilosc];
            Wczytaj(tabx,taby,ilosc);
            double A0,A1;
            Wyznaczniki(tabx,taby,ilosc,&A0,&A1);
            cout<<"Wzor funkcji: g(x)="<<A0<<"+"<<A1<<"x"<<endl;
        }

    }else
    {
        system("cls");
        cout<<"Wybierz:"<<endl<<"1.Dane z zadania 4"<<endl<<"2.Wlasne dane"<<endl;
        cin>>wyb2;
        if(wyb2==1)
        {
            system("cls");
            ilosc=3;
            system("cls");
            double *tabx=new double[ilosc];
            double *taby=new double[ilosc];
            tabx[0]=3;
            taby[0]=1;
            tabx[1]=5;
            taby[1]=7;
            tabx[2]=9;
            taby[2]=3;
            cout<<"x | "<<3<<" | "<<5<<" | "<<9<<endl;
            cout<<"----------------"<<endl;
            cout<<"y | "<<1<<" | "<<7<<" | "<<3<<endl<<endl;
            double A0,A1;
            Logarytmuj(taby,ilosc);
            Wyznaczniki(tabx,taby,ilosc,&A0,&A1);
            cout<<"Wzor funkcji: g(x)="<<A0<<"+"<<A1<<"x"<<endl;
            double A,B;
            A=pow(M_E,A0);
            B=pow(M_E,A1);
            cout<<"y="<<A<<"+"<<B<<"^x"<<endl;
        }else
        {
            system("cls");
            cout<<"Podaj ilosc punktow: ";
            cin>>ilosc;
            system("cls");
            double *tabx=new double[ilosc];
            double *taby=new double[ilosc];
            Wczytaj(tabx,taby,ilosc);
            double A0,A1;
            Logarytmuj(taby,ilosc);
            Wyznaczniki(tabx,taby,ilosc,&A0,&A1);
            system("cls");
            double A,B;
            A=pow(M_E,A0);
            B=pow(M_E,A1);
            cout<<"y="<<A<<"+"<<B<<"^x"<<endl;

        }

    }
    return 0;
}
