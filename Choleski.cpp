#include <iostream>
#include <conio.h>
#include <windows.h>
#include <math.h>
using namespace std;

void Wczytaj(double** Macierz,double *Wektor,int wymiar);
void Wyswietl(double **Macierz,double *Wektor,int wymiar);
void TrojkatGora(double **A,double *b,double **&L,int wymiar);
double Suma(double **A,int i,int j,int ilosc);
void Transpozycja(double **L,int wymiar);
void ObliczWektorY(double **L,double *b,double *&wY,int wymiar);
void ObliczWektorX(double **L,double *wY,double *&wX,int wymiar);

int main()
{
    int wybor,wymiar;
    cout<<"Rozklad Choleskiego"<<endl;
    cout<<"Wybierz:"<<endl;
    cout<<"1.Podaj swoje dane"<<endl<<"2.Wybierz gotowy zesaw danych"<<endl;
    cin>>wybor;
    if(wybor==1)
    {
        system("cls");
        cout<<"Podaj wymiar macierzy: ";
        cin>>wymiar;
        system("cls");
        double **MacierzL,*WektorY,*WektorX;
        double *Wektor=new double[wymiar];
        double **Macierz=new double*[wymiar];
        for(int i=0;i<wymiar;i++)
        {
            Macierz[i]=new double[wymiar];
        }
        Wczytaj(Macierz,Wektor,wymiar);
        system("cls");
        TrojkatGora(Macierz,Wektor,MacierzL,wymiar);
        ObliczWektorY(MacierzL,Wektor,WektorY,wymiar);
        Transpozycja(MacierzL,wymiar);
        ObliczWektorX(MacierzL,WektorY,WektorX,wymiar);
    }
    else
    {
        wymiar=4;
        double **MacierzL,*WektorY,*WektorX;
        double *Wektor=new double[wymiar];
        double **Macierz=new double*[wymiar];
        for(int i=0;i<wymiar;i++)
        {
            Macierz[i]=new double[wymiar];
        }
        Macierz[0][0]=1;  Macierz[1][0]=-2; Macierz[2][0]=3;  Macierz[3][0]=1; Wektor[0]=1;
        Macierz[0][1]=-2; Macierz[1][1]=5;  Macierz[2][1]=-8; Macierz[3][1]=1; Wektor[1]=-1;
        Macierz[0][2]=3;  Macierz[1][2]=-8; Macierz[2][2]=17; Macierz[3][2]=-7; Wektor[2]=3;
        Macierz[0][3]=1;  Macierz[1][3]=1; Macierz[2][3]=-7; Macierz[3][3]=18; Wektor[3]=-4;
        Wyswietl(Macierz,Wektor,wymiar);
        TrojkatGora(Macierz,Wektor,MacierzL,wymiar);
        ObliczWektorY(MacierzL,Wektor,WektorY,wymiar);
        Transpozycja(MacierzL,wymiar);
        ObliczWektorX(MacierzL,WektorY,WektorX,wymiar);
    }
    return 0;
}

void Wczytaj(double** Macierz,double *Wektor,int wymiar)
{
    for(int i=0;i<wymiar;i++)
        {
            for(int j=0;j<wymiar;j++)
            {
                cout<<"Podaj element ["<<i+1<<"]["<<j+1<<"]: ";
                cin>>Macierz[i][j];
            }
        }
    for(int i=0;i<wymiar;i++)
    {
        cout<<"Podaj element ["<<i<<"] wektora: ";
        cin>>Wektor[i];
    }
}
void Wyswietl(double **Macierz,double *Wektor,int wymiar)
{
    for(int i=0;i<wymiar;i++)
        {
            cout<<"|   ";
            for(int j=0;j<wymiar;j++)
            {
                cout<<Macierz[i][j]<<"    ";
            }
            cout<<"|       | "<<Wektor[i]<<" |"<<endl;
        }
}
void TrojkatGora(double **A,double *b,double **&L,int wymiar)
{
        L=new double*[wymiar];
        for(int i=0;i<wymiar;i++)
        {
            L[i]=new double[wymiar];
        }
        for(int i=0;i<wymiar;i++)
        {
            for(int j=0;j<wymiar;j++)
            {
                L[i][j]=0;
            }
        }
    int ilosc;
    for(int i=0;i<wymiar;i++)
    {
        ilosc=i;
        L[i][i]=sqrt(A[i][i]-Suma(L,i,i,ilosc));
        for(int j=i+1;j<wymiar;j++)
        {
            L[j][i]=((A[j][i]-Suma(L,j,i,ilosc))/L[i][i]);
            if(L[j][i]>pow(10,10))
            {
                L[j][i]=0;
            }
        }
    }
}
double Suma(double **L,int i,int j,int ilosc)
{
    double suma=0;
    if(ilosc>0)
    {
        for(int k=0;k<ilosc;k++)
        {
                suma=suma+(L[i][k]*L[j][k]);
        }
    }
    return suma;
}
void Transpozycja(double **L,int wymiar)
{
    double tym;
    for(int i=0;i<wymiar;i++)
    {
        for(int j=i+1;j<wymiar;j++)
        {
            tym=L[i][j];
            L[i][j]=L[j][i];
            L[j][i]=tym;
        }
    }
}
void ObliczWektorY(double **L,double *b,double *&wY,int wymiar)
{
    wY=new double[wymiar];
    double suma,temp=0 ;
    wY[0]= b[0]/L[0][0];
    for(int i=1; i<wymiar; i++)
    {
        suma=0;
        for(int j=0; j<wymiar; j++)
        {
            suma+=wY[j]*L[i][j];
        }
        wY[i] = (b[i]-suma)/L[i][i];
    }
    cout<<"Wektor Y"<<endl;
    for(int i=0;i<wymiar;i++)
    {
        cout<<wY[i]<<endl;
    }
}
void ObliczWektorX(double **L,double *wY,double *&wX,int wymiar)
{
    wX=new double[wymiar];
    double suma;
    wX[wymiar-1]= wY[wymiar-1]/L[wymiar-1][wymiar-1];
    for(int i=wymiar-2;i>=0;i--)
    {
        suma=0;
        for(int j=i+1;j<wymiar;j++)
        {
            suma+=wX[j]*L[i][j];
        }

        wX[i]=(wY[i]-suma)/L[i][i];
    }
    cout<<"Wektor X"<<endl;
    for(int i=0;i<wymiar;i++)
    {
        cout<<wX[i]<<endl;
    }
}
