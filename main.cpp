#include <iostream>
#include <conio.h>
#include <iomanip>
#include <math.h>
#include <windows.h>
using namespace std;
//-------------------------------------------------------------------------------------------
int MetodaWprowadzaniaDanych()
{
    system("cls");
    int wyb;
    cout<<"Wybierz:"<<endl<<"1.Wczytaj swoje dane"<<endl<<"2.Gotowy zestaw danych"<<endl;
    cin>>wyb;
    return wyb;
}
//---------------------------------------------------------------------------------------------------------
void ZestawPodst(double **&X,double *&Y)
{
    X[0][0]=-2;  X[0][1]=-2;  X[0][2]=-2;  X[0][3]=0;       Y[0]=5;
    X[1][0]=-2;  X[1][1]=1;   X[1][2]=-3;  X[1][3]=-3;      Y[1]=2;
    X[2][0]=-2;  X[2][1]=-2;  X[2][2]=-4;  X[2][3]=-2;      Y[2]=6;
    X[3][0]=-1;  X[3][1]=2;   X[3][2]=-3;  X[3][3]=-2;      Y[3]=1;
}
//---------------------------------------------------------------------------------------------------------
void ZestawWybKolumn(double **&X,double *&Y)
{
    X[0][0]=2;  X[0][1]=3;   X[0][2]=-4;    Y[0]=9;
    X[1][0]=1;  X[1][1]=2;   X[1][2]=-2;    Y[1]=7;
    X[2][0]=4;  X[2][1]=-2;  X[2][2]=5;     Y[2]=-5;
}
//----------------------------------------------------------------------------------------------------------
void ZestawWybPelny(double **&X,double *&Y)
{
    X[0][0]=0;  X[0][1]=1;   X[0][2]=2;   X[0][3]=3;      Y[0]=8;
    X[1][0]=1;  X[1][1]=0;   X[1][2]=1;   X[1][3]=2;      Y[1]=4;
    X[2][0]=1;  X[2][1]=2;   X[2][2]=3;   X[2][3]=4;      Y[2]=10;
    X[3][0]=0;  X[3][1]=1;   X[3][2]=3;   X[3][3]=2;      Y[3]=7;
}
//----------------------------------------------------------------------------------------------------------
void WybierzZestaw(double **&X,double *&Y, int &rozmiar,int wybor)
{
    switch(wybor)
    {
    case 1:
        {
            rozmiar=4;
            X=new double*[rozmiar];
            for(int i=0;i<rozmiar;i++)
            {
                X[i]=new double[rozmiar];
            }
            Y=new double[rozmiar];
            ZestawPodst(X,Y);

        }break;
    case 2:
        {
            rozmiar=3;
            X=new double*[rozmiar];
            for(int i=0;i<rozmiar;i++)
            {
                X[i]=new double[rozmiar];
            }
            Y=new double[rozmiar];
            ZestawWybKolumn(X,Y);
        }break;
    case 3:
        {
            rozmiar=4;
            X=new double*[rozmiar];
            for(int i=0;i<rozmiar;i++)
            {
                X[i]=new double[rozmiar];
            }
            Y=new double[rozmiar];
            ZestawWybPelny(X,Y);
        }break;
    }
}
//--------------------------------------------------------------------------------------------------
void WczytajDane(double **X,double *Y,int wymiar)
{
    for(int i=0;i<wymiar;i++)
    {
        system("cls");
        for(int j=0;j<wymiar;j++)
        {
            cout<<"Podaj X["<<i+1<<"]["<<j+1<<"]: ";
            cin>>X[i][j];
        }
        cout<<"Podaj Y["<<i+1<<"]: ";
        cin>>Y[i];
    }
}
//-------------------------------------------------------------------------------------------------
void WyswietlDane(double **X,double*Y,int wymiar)
{
    for(int i=0;i<wymiar;i++)
    {
        for(int j=0;j<wymiar;j++)
        {
            cout<<"X["<<i+1<<"]["<<j+1<<"]= "<<X[i][j]<<"    ";
        }
        cout<<setw(10)<<"Y["<<i+1<<"]= "<<Y[i]<<endl;
    }
    getch();
}
//-------------------------------------------------------------------------------------------------
bool SprawdzCzyMozliwe(double **X,int krok)
{
    if(X[krok][krok]<pow(10,-10) && X[krok][krok]>(-pow(10,-10)))
    {
        return false;
    }
    else
    {
        return true;
    }
}
//------------------------------------------------------------------------------------------------
void ZerujKolumne(double **X,double *Y,int wymiar,int kolumna)
{
    double p;
    int krok=kolumna;
    int pole;
    for(int j=kolumna+1;j<wymiar;j++)
    {
        pole=j;
        while(X[pole][krok]==0 && pole<wymiar)
        {
            pole++;
            j++;
        }
        p=X[pole][krok]/X[krok][krok];
        for(int k=kolumna;k<wymiar;k++)
        {
            X[pole][k]=X[pole][k]-(p*X[krok][k]);
        }
        Y[pole]=Y[pole]-p*Y[krok];
    }
}
//--------------------------------------------------------------------------------------------------------------------------------
bool TrojkatGaussPodstawowy(double **X,double *Y,int wymiar)
{
    for(int i=0;i<wymiar-1;i++)
    {
        if(SprawdzCzyMozliwe(X,i)==false)
        {
            return false;

        }else
        {
            ZerujKolumne(X,Y,wymiar,i);
        }
    }
    return true;
}
//---------------------------------------------------------------------------
void PoliczX(double **X,double *Y,double *&XY,int wymiar)
{
    XY=new double[wymiar];
    for(int i=0;i<wymiar;i++)
    {
        XY[i]=Y[i];
    }

    XY[wymiar-1]=XY[wymiar-1]/X[wymiar-1][wymiar-1];
    for(int i=wymiar-1;i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            XY[j]=XY[j]-X[j][i]*XY[i];
        }
        XY[i-1]=XY[i-1]/X[i-1][i-1];
    }
}
//---------------------------------------------------------------------------------------
double WyswietlWynik(double *XY,int wymiar)
{
    system("cls");
    cout<<"Wyniki"<<endl;
    for(int i=0;i<wymiar;i++)
    {
        cout<<"X["<<i+1<<"]= "<<XY[i]<<endl;
    }
}
//------------------------------------------------------------------------------------------
double WybKolumna(double **X,double *Y,int wymiar,int krok)
{
    double maxi=fabs(X[krok][0]);
    int maxwiersz=0;
    for(int i=krok+1;i<wymiar;i++)
    {
        if(fabs(X[krok][i])>maxi)
        {
            maxi=fabs(X[krok][i]);
            maxwiersz=i;
        }
    }
    double *Tym=new double[wymiar];
    double tymY;
    tymY=Y[maxwiersz];
    Y[maxwiersz]=Y[krok];
    Y[krok]=tymY;
    for(int i=0;i<wymiar;i++)
    {
        Tym[i]=X[maxwiersz][i];
        X[maxwiersz][i]=X[krok][i];
        X[krok][i]=Tym[i];
    }

}
//------------------------------------------------------------------------------
void GaussWybKolumn(double **X,double *Y,int wymiar)
{
    for(int i=0;i<wymiar-1;i++)
    {
        WybKolumna(X,Y,wymiar,i);
        ZerujKolumne(X,Y,wymiar,i);
    }
}
//------------------------------------------------------------------------------
void WybPelny(double** X,double *Y,int *&KolejnoscX,int wymiar,int krok)
{
    KolejnoscX=new int(wymiar);
    for(int i=0;i<wymiar;i++)
    {
            KolejnoscX[i]=1;
    }
    double maxi=fabs(X[krok][krok]);
    int maxwiersz=krok;
    int maxkolumna=krok;
    for(int i=krok+1;i<wymiar;i++)
    {
        for(int j=krok+1;j<wymiar;j++)
        {
            if(fabs(X[i][j])>maxi)
            {
                maxi=X[i][j];
                maxwiersz=i;
                maxkolumna=j;
            }
        }
    }
    double *TymW=new double[wymiar];
    double *TymK=new double[wymiar];
    double tymY;
    int tymKolejnosc;
    tymY=Y[maxwiersz];
    Y[maxwiersz]=Y[krok];
    Y[krok]=tymY;
    for(int i=0;i<wymiar;i++)
    {
        TymW[i]=X[maxwiersz][i];
        X[maxwiersz][i]=X[krok][i];
        X[krok][i]=TymW[i];
    }
    for(int i=0;i<wymiar;i++)
    {
        TymK[i]=X[i][maxkolumna];
        X[i][maxkolumna]=X[i][krok];
        X[i][krok]=TymK[i];
    }
    tymKolejnosc=KolejnoscX[0];
    KolejnoscX[0]=KolejnoscX[maxkolumna];
    KolejnoscX[maxkolumna]=tymKolejnosc;
}
//-------------------------------------------------------------------
void GaussPelnyWybor(double **X,double *Y,int *&KolejnoscX,int wymiar)
{
    for(int i=0;i<wymiar-1;i++)
    {
        cout<<"Petelka "<<i<<endl;
        WybPelny(X,Y,KolejnoscX,wymiar,i);
        WyswietlDane(X,Y,wymiar);
        ZerujKolumne(X,Y,wymiar,i);
        WyswietlDane(X,Y,wymiar);
    }
}
//==============================================================================================================================
int main()
{
    int wybMetod,wybDane,wybMacierz,rozmiar;

    cout<<"Metoda eliminacji Gaussa"<<endl;
    cout<<"Wybierz metode:"<<endl;
    cout<<"1.Metoda podstawowa"<<endl<<"2.Metoda z wyborem elementu maksymalnego w kolumnie"<<endl<<"3.Metoda z pelnym wyborem elementu maksymalnego"<<endl;
    cin>>wybMetod;
    switch (wybMetod)
    {
    case 1:
        {
            wybDane=MetodaWprowadzaniaDanych();
            if(wybDane==1)
            {
                system("cls");
                cout<<"Jaki rozmiar macierzy kwadratowej?"<<endl;
                cin>>rozmiar;
                double *Wynik;
                double **Macierz=new double*[rozmiar];
                for(int i=0;i<rozmiar;i++)
                {
                    Macierz[i]=new double[rozmiar];
                }
                double *Wektor=new double[rozmiar];
                WczytajDane(Macierz,Wektor,rozmiar);
                system("cls");
                cout<<"Przed eliminacja: "<<endl;
                WyswietlDane(Macierz,Wektor,rozmiar);
                if(TrojkatGaussPodstawowy(Macierz,Wektor,rozmiar)==true)
                {
                    system("cls");
                    cout<<"Po eliminacji: "<<endl;
                    WyswietlDane(Macierz,Wektor,rozmiar);
                    PoliczX(Macierz,Wektor,Wynik,rozmiar);
                    WyswietlWynik(Wynik,rozmiar);
                }else
                {
                    cout<<"Koniec z powodu 0 na przekatnej"<<endl;
                    getch();
                    return 0;
                }
            }else
            {
                double **Macierz;
                double *Wektor;
                double *Wynik;
                int rozmiar;
                system("cls");
                cout<<"Ktory zestaw danych chcesz wybrac?"<<endl;
                cin>>wybMacierz;
                WybierzZestaw(Macierz,Wektor,rozmiar,wybMacierz);
                system("cls");
                cout<<"Przed eliminacja: "<<endl;
                WyswietlDane(Macierz,Wektor,rozmiar);
                if(TrojkatGaussPodstawowy(Macierz,Wektor,rozmiar)==true)
                {
                    system("cls");
                    cout<<"Po eliminacja: "<<endl;
                    WyswietlDane(Macierz,Wektor,rozmiar);
                    PoliczX(Macierz,Wektor,Wynik,rozmiar);
                    WyswietlWynik(Wynik,rozmiar);
                }else
                {
                    cout<<"Koniec z powodu 0 na przekatnej"<<endl;
                    getch();
                    return 0;
                }
            }
        }
        break;
    case 2:
        {
            wybDane=MetodaWprowadzaniaDanych();
            if(wybDane==1)
            {
                system("cls");
                cout<<"Jaki rozmiar macierzy kwadratowej?"<<endl;
                cin>>rozmiar;
                double *Wynik;
                double **Macierz=new double*[rozmiar];
                for(int i=0;i<rozmiar;i++)
                {
                    Macierz[i]=new double[rozmiar];
                }
                double *Wektor=new double[rozmiar];
                WczytajDane(Macierz,Wektor,rozmiar);
                system("cls");
                cout<<"Przed eliminacja: "<<endl;
                WyswietlDane(Macierz,Wektor,rozmiar);
                system("cls");
                cout<<"Po eliminacja: "<<endl;
                WyswietlDane(Macierz,Wektor,rozmiar);
                PoliczX(Macierz,Wektor,Wynik,rozmiar);
                WyswietlWynik(Wynik,rozmiar);
            }else
            {
                double *Wynik;
                double **Macierz;
                double *Wektor;
                int rozmiar;
                system("cls");
                cout<<"Ktory zestaw danych chcesz wybrac?"<<endl;
                cin>>wybMacierz;
                WybierzZestaw(Macierz,Wektor,rozmiar,wybMacierz);
                system("cls");
                cout<<"Przed eliminacja: "<<endl;
                WyswietlDane(Macierz,Wektor,rozmiar);
                GaussWybKolumn(Macierz,Wektor,rozmiar);
                system("cls");
                cout<<"Po eliminacja: "<<endl;
                WyswietlDane(Macierz,Wektor,rozmiar);
                PoliczX(Macierz,Wektor,Wynik,rozmiar);
                WyswietlWynik(Wynik,rozmiar);
            }
        }
        break;
    case 3:
        {
            wybDane=MetodaWprowadzaniaDanych();
            if(wybDane==1)
            {
                system("cls");
                cout<<"Jaki rozmiar macierzy kwadratowej?"<<endl;
                cin>>rozmiar;
                double **Macierz=new double*[rozmiar];
                for(int i=0;i<rozmiar;i++)
                {
                    Macierz[i]=new double[rozmiar];
                }
                double *Wektor=new double[rozmiar];
                WczytajDane(Macierz,Wektor,rozmiar);
                WyswietlDane(Macierz,Wektor,rozmiar);
            }else
            {
                double **Macierz;
                double *Wektor;
                double *Wynik;
                int *KolejnoscX;
                int rozmiar;
                cout<<"Ktory zestaw danych chcesz wybrac?"<<endl;
                cin>>wybMacierz;
                WybierzZestaw(Macierz,Wektor,rozmiar,wybMacierz);
                WyswietlDane(Macierz,Wektor,rozmiar);
                GaussPelnyWybor(Macierz,Wektor,KolejnoscX,rozmiar);
                system("cls");
                WyswietlDane(Macierz,Wektor,rozmiar);
                PoliczX(Macierz,Wektor,Wynik,rozmiar);
                WyswietlWynik(Wynik,rozmiar);
            }
        }
        break;
    }
    return 0;
}
