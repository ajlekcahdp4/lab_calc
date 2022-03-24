#include "mnk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>


struct mnk_linear {
    int     N;
    double* x;
    double* y;
    double  a;
    double  b;
    double  ad;
    double  bd;
};

struct input {
    int N;
    double *x;
    double *y;
};

struct mnk_pol {
    int N;
    double *a;
};


//==================================================================================================
//=============================================INPUT================================================
//==================================================================================================

double *InputRow (FILE *file, int N)
{
    double *row = calloc (N, sizeof(double));
    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%lf", row + i);
    }
    return row;
}

struct input *Input ()
{
    struct input * INP = calloc (1, sizeof (struct input));

    char* input_name = calloc (100, sizeof(char));
    printf ("Enter the name of file with data for mnk calculation:\n");
    scanf ("%s", input_name);
    FILE* inputfile = fopen (input_name, "r");
    assert (inputfile);

    
    fscanf(inputfile, "%d", &INP->N);
    INP->x = InputRow (inputfile, INP->N);
    INP->y = InputRow (inputfile, INP->N);

    fclose (inputfile);
    return INP;
}


//==================================================================================================
//===========================================LINEAR=LSM=============================================
//==================================================================================================
double Sum (double* a, int N)
{
    double S = 0;
    for (int i = 0; i < N; i++)
        S += a[i];
    return S;
}

double SumMul (double* a, double* b, int N)
{
    double S = 0;
    for (int i = 0; i < N; i++)
        S += a[i] * b[i];
    return S;
}

double SumSq (double* a, int N)
{
    double S = 0;
    for (int i = 0; i < N; i++)
        S += a[i] * a[i];
    return S;
}

double Get_a (double* x, double* y, int N)
{
    double a = (N*SumMul(x, y, N) - Sum(x, N)*Sum(y, N))/(N*SumSq(x, N) - (Sum(x, N) * Sum(x, N)));
    return a;
}

double Get_b (double* x, double* y, int N)
{
    double b = (Sum(y, N) - Get_a(x, y, N)*Sum(x, N))/N;
    return b;
}
double Get_ad (double*x, double* y, int N)
{
    double a = Get_a (x, y, N);
    double ad = (1/sqrt(N)) * sqrt( N*(SumSq(y, N) - (Sum(y, N)) * Sum(y, N))/(N*(SumSq(x, N) - (Sum(x, N)) * Sum(x, N)) - (a * a)));
    return ad;
}

double Get_bd (double*x, double* y, int N)
{
    double bd = Get_ad (x, y, N) * (1/(double)N) * sqrt(N*SumSq(x, N) - (Sum (x, N) * Sum (x, N)));
    return bd;
}


struct mnk_linear *LinearCalc (struct input *INP)
{
    struct mnk_linear *MNK = calloc (1, sizeof (struct mnk_linear));
    assert (MNK);

    MNK->N = INP->N;
    MNK->x = calloc (MNK->N, sizeof(double));
    MNK->y = calloc (MNK->N, sizeof(double));
    assert (MNK->y);
    assert (MNK->x);

    memcpy (MNK->x, INP->x, MNK->N * sizeof(double));
    memcpy (MNK->y, INP->y, MNK->N * sizeof(double));

    MNK->a  = Get_a   (MNK->x, MNK->y, MNK->N);
    MNK->b  = Get_b   (MNK->x, MNK->y, MNK->N);
    MNK->ad = Get_ad  (MNK->x, MNK->y, MNK->N);
    MNK->bd = Get_bd  (MNK->x, MNK->y, MNK->N);

    return MNK;
}


void LinearMnkCalc ()
{
    struct input *INP = Input();

    struct mnk_linear *MNK = LinearCalc (INP);

    MnkPrint (MNK);

    free (MNK->x);
    free (MNK->y);
    free (MNK);
}

//==================================================================================================
//==========================================POLINOM=LSM=============================================
//==================================================================================================






//==================================================================================================
//============================================OUTPUT================================================
//==================================================================================================

void MnkPrint (struct mnk_linear* MNK)
{
    FILE* out = fopen ("data/data_mnk.txt", "w");

    fprintf (out, "%d\n", MNK->N);
    for (int i = 0; i < MNK->N; i++)
        fprintf (out, "%.4g ", MNK->x[i]);
    fprintf (out, "\n");

    for (int i = 0; i < MNK->N; i++)
        fprintf (out, "%.4g ", MNK->y[i]);
    fprintf (out, "\n");

    fprintf (out, "%.4g\n", MNK->a);
    fprintf (out, "%.4g\n", MNK->b);
    fprintf (out, "%.4g\n", MNK->ad);
    fprintf (out, "%.4g\n", MNK->bd);

    fclose (out);

}