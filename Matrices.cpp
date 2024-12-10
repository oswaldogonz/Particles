#include "Matrices.h"


Matrix::Matrix(int _rows, int _cols)
{
    a=vector<vector<double>>(_rows,vector<double>(_cols,0));
    rows=_rows;
    cols=_cols;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
    if(a.getRows()!=b.getRows()||a.getCols()!=b.getCols())
    {
        throw runtime_error("Error: dimensions must agree");
    }
    Matrix c(a.getRows(),a.getCols());
    for(int i=0;i<a.getRows();i++)
    {
        for(int j=0;j<a.getCols();j++)
        {
            c(i,j)=a(i,j)+b(i,j);
        }
    }
    return c;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
    if(a.getCols()!=b.getRows())
    {
        throw runtime_error("Error: dimensions must agree");
    }
    Matrix c(a.getRows(),b.getCols());
    for(int i=0;i<a.getRows();i++)
    {
        for(int k=0;k<b.getCols();k++)
        {
            c(i,k)=0;
            for(int j=0;j<a.getCols();j++)
            {
                c(i,k)+=a(i,j)*b(j,k);
            }
        }
    }
    return c;
}

bool operator==(const Matrix& a, const Matrix& b)
{
    if(a.getRows()!=b.getRows()||a.getCols()!=b.getCols())
    {
        return false;
    }
    for(int i=0;i<a.getRows();i++)
    {
        for(int j=0;j<a.getCols();j++)
        {
            if(abs(a(i,j)-b(i,j))>=0.001)
            {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& a, const Matrix& b)
{
    if(a.getRows()!=b.getRows()||a.getCols()!=b.getCols())
    {
        return true;
    }
    for(int i=0;i<a.getRows();i++)
    {
        for(int j=0;j<a.getCols();j++)
        {
            if(abs(a(i,j)-b(i,j))>=0.001)
            {
                return true;
            }
        }
    }
    return false;
}

ostream& operator<<(ostream& os, const Matrix& a)
{
    for(int i=0;i<a.getRows();i++)
    {
        for(int j=0;j<a.getCols();j++)
        {
            os<<setw(10)<<a(i,j);
        }
        os<<"\n";
    }
    return os;
}


RotationMatrix::RotationMatrix(double theta):Matrix(2,2)
{
    a[0][0]=cos(theta);
    a[0][1]=-sin(theta);
    a[1][0]=sin(theta);
    a[1][1]=cos(theta);
}

ScalingMatrix::ScalingMatrix(double scale):MAtrix(2,2)
{
    a[0][0]=scale;
    a[0][1]=0;
    a[1][0]=0;
    a[1][1]=scale;
}

TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols):MAtrix(2,nCols)
{
    for(int i=0;i<nCols;i++)
    {
      a[0][i]=xShift;
      a[1][i]=yShift;
    }
}


