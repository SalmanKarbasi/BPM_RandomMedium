////////////////////////////////////////////////////////
////*********Transparent boundary condition ********* ////
////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>
#include<omp.h>
#include <string.h>
#include <sysexits.h>

//#define RANDGEN()   (rand() < RAND_MAX / 2 ? 0.0 : 1.0)
double randgen()
{
double r, R, t, b;
r=rand();
R=RAND_MAX;
t=r/R;
if (t>=0.5)
	{
	b=1;
	}
	else
	{
	b=0;
	}
return(b);
}

/*****************************************************/
main()
{
    srand((unsigned)time(NULL));
    char            buffer [1];
    long int        a ,
		    jj       ,
		    ii       ,
		    gg       ,
		    ff       ,
		    mm       ,
		    Nx       ,
		    Ny       ,
		    Nz       ,
		    Ncw      ,
		    nc;
    double          x0  ,
		    y0       ,
		    pi       ,
		    lam      ,
		    k0       ,
		    w0       ,
		    w        ,
		    wc       ,
		    dx       ,
		    dy       ,
		    dc       ,
		    n0       ,
		    dz       ,
		    na       ,
		    ng       ,
		    rnd      ,
		    Nsites   ,
		    Px = 0,
		    Py = 0,
		    Ps = 0,
		    N = 0,
		    nn = 1;

    /*****************************************************/
    lam = 0.405;                /* wavelength */
    w0 = 2.4;               /* Gaussian pulse width */
    w = 250;
    dc = 0.9;
    //Nsites = w / dc;
    Nsites = 1008; //(int)Nsites;
    dx = 0.3;                    /* step size in X direction */
    nc = 3; //dc / dx;
    //nc = (int)nc;
    dy = dx;
    //w = Nsites * nc * dx;       /* simulation window width */
    Nx = 1008;//(int)(w / dx);         /* n number of samples in "x" direction */
    Ny = 1008;
    //Ncw = (int)(wc / dx);
    printf("Nx = %ld, dc = %f, dx = %f, Nsites = %f, w = %f\n", Nx, dc, dx, Nsites, w);
    //double          (*n)[Nx] = malloc(Nx * sizeof(double[Nx]));
    int ggN=0,ffN=0;
    int rows=1008; 
    int colum=1008;		
    float E0[rows][rows];	
    double          complex(*k1)[Nx] = malloc(2 * Nx * sizeof(double[Nx]));
    double          complex(*k2)[Nx] = malloc(2 * Nx * sizeof(double[Nx]));
    double          complex(*k3)[Nx] = malloc(2 * Nx * sizeof(double[Nx]));
    double          complex(*k4)[Nx] = malloc(2 * Nx * sizeof(double[Nx]));
    //FILE    *fp;
    //fp = fopen("Source.dat","r");
    //for (ggN = 0; ggN < 400; ggN++){
//	for (ffN = 0; ffN < 400; ffN++)
  //        {	  fscanf(fp,"%f", &n[ggN][ffN]);
	          //printf("%f\n",A[gg][ff]);
		  //printf("salman\n");	
	//	}}
    //fclose(fp);	


   double (*n)[Nx] = malloc(Nx*sizeof(double[Nx]));
    if (n == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    if (k1 == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    if (k2 == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    if (k3 == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    if (k4 == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    double complex  kx1,
		    ky1;
    //double          (*E0)[Nx] = malloc(Nx * sizeof(double[Nx]));
    if (E0 == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    double          complex(*E1)[Nx] = malloc(2 * Nx * sizeof(double[Nx]));
    if (E1 == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    double          complex(*E2)[Nx] = malloc(2 * Nx * sizeof(double[Nx]));
    if (E2 == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }

    /*******************************************************/
    na = 1.49;                  /* refractive index of Air */
    ng = 1.59;                  /* refractive index of core */
    /* define  the incident boundary condition */
    x0 = 502;         /* center of Gaussian pulse */
    y0 = 502;

//    for (ii = 0; ii <= Nx - 1; ii++)
//	for (jj = 0; jj <= Ny - 1; jj++)
//	    E0[ii][jj] = exp(-(pow((ii + 1) * dx - x0, 2) + pow((jj + 1) * dy - y0, 2)) / pow(w0, 2));

    FILE    *fp;
    fp = fopen("Source.dat","r");
    for (ggN = 0; ggN < 1008; ggN++){
	for (ffN = 0; ffN < 1008; ffN++)
          {	  fscanf(fp,"%f", &E0[ggN][ffN]);
	          //printf("%f\n",A[gg][ff]);
		  //printf("salman\n");	
		}}
    fclose(fp);	



for (gg=0;gg<Nsites;gg++)
	{
		for (ff=0;ff<Nsites;ff++)
			{
		rnd=randgen();
		for (ii=0;ii<=nc-1;ii++)
			     {   
				   for(jj=0;jj<=nc-1;jj++)   
				    	{
			        	        n[ii+nc*gg][jj+nc*ff]=ng+rnd*(na-ng);
				    	}
			     }
			}
	}

    /********************************************************/
 /*
     for (ii=0;ii<=Nx-1;ii++){

      for (jj=0;jj<=Ny-1;jj++){
		if (pow(ii-x0,2)+pow(jj-x0,2)<pow(150,2))
		{  n[ii][jj]=n[ii][jj];}
		else 
		  {n[ii][jj]=1;} 	
	}
	}
    //
    /*********************************************************/
/***************************Ref Index Profile******************************/
    FILE           *g3;
        g3 = fopen("RefIndex.dat","w");
        for (ii=0;ii<=Nx-1;ii++)
            {
             fprintf(g3,"\n");   
            for(jj=0;jj<=Ny-1;jj++)
            {
                fprintf(g3,"%f", n[ii][jj]);
               // fprintf(f,"%f", cabs(E2[ii][jj]));
                fprintf(g3,"  ");
            }
            }   
    fclose(g3);


    FILE           *f;

    f = fopen("TestSEMout.dat", "w");
    for (ii = 0; ii <= Nx - 1; ii++)
    {
	fprintf(f, "\n");
	for (jj = 0; jj <= Ny - 1; jj++)
	{
	    fprintf(f, "%f", E0[ii][jj]);
	    fprintf(f, "  ");
	}
    }
    fclose(f);

    /*
     * parallel for for (jj=0;jj<=Ny-1;jj++){ if
     * (pow(ii-Nx/2,2)+pow(jj-Nx/2,2)<pow(15,2)) {  n[ii][jj]=ng;} else
     * {n[ii][jj]=na;}  } } /********************************************************
     */
    pi = 4 * atanl(1);          /* pi */
    k0 = 2 * pi / lam;          /* wavevector */
    n0 = 0.5 * ng + 0.5* na;       /* effective refractive index of media */
    dz = 0.02 * k0 * pow(dx, 2) * n0;
    printf("dz=%f\n", dz);
    Nz = (int)(500000 / dz);     /* number of samples in "z" direction */
    double         *SigmaS = malloc(Nz * sizeof(double));
    if (SigmaS == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    double         *Sigmax = malloc(Nz * sizeof(double));
    if (Sigmax == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    double         *Sigmay = malloc(Nz * sizeof(double));
    if (Sigmay == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    double         *power = malloc(Nz * sizeof(double));
    if (power == NULL)
    {
	fputs("Failed to malloc() array n.\n", stderr);
	exit(EX_UNAVAILABLE);
    }

    /***********************************************************/
//#pragma omp parallel for
    for (ii = 0; ii <= Nx - 1; ii++)
	for (jj = 0; jj <= Ny - 1; jj++)
	    E1[ii][jj] = E0[ii][jj];
    /***********************************************************/

#if 0
#pragma omp parallel for
    for (ii = 0; ii <= Nx - 1; ii++)
    {
	for (jj = 0; jj <= Ny - 1; jj++)
	{
	    k1[ii][jj] = 0;
	    k2[ii][jj] = 0;
	    k3[ii][jj] = 0;
	    k4[ii][jj] = 0;
	}
    }
#endif

    /****************************************************************/
    /********************Runge-Kutta method**************************/
    /****************************************************************/


    for (mm = 1; mm <= Nz; mm++)
    {
	Px = 0;
	Py = 0;
	Ps = 0;
	N = 0;
	power[mm - 1] = 0;
	SigmaS[mm - 1] = 0;
	Sigmax[mm - 1] = 0;
	Sigmay[mm - 1] = 0;

#pragma omp parallel for
	for (ii = 1; ii <= Nx - 2; ii++)
#pragma omp parallel for
	    for (jj = 1; jj <= Ny - 2; jj++)
		k1[ii][jj] =
			(-I * nn / n0 / k0 / 2) * ((E1[ii + 1][jj] - 2 * E1[ii][jj] + E1[ii - 1][jj]) / (dx * dx) + (E1[ii][jj + 1] - 2 * E1[ii][jj] + E1[ii][jj - 1]) / (dy * dy) + ((n[ii][jj] * n[ii][jj]) - n0 * n0) * k0 * k0 * E1[ii][jj]);

#pragma omp parallel for
	for (ii = 0; ii <= Nx - 1; ii++)
#pragma omp parallel for
	    for (jj = 0; jj <= Ny - 1; jj++)
		E2[ii][jj] = E1[ii][jj] + 0.5 * dz * k1[ii][jj];

#pragma omp parallel for
	/***********************************************/
	for (ii = 1; ii <= Nx - 2; ii++)
#pragma omp parallel for
	    for (jj = 1; jj <= Ny - 2; jj++)
		k2[ii][jj] = (-I * nn / n0 / k0 / 2) *
			((E2[ii + 1][jj] - 2 * E2[ii][jj] + E2[ii - 1][jj]) / (dx * dx) + (E2[ii][jj + 1] - 2 * E2[ii][jj] + E2[ii][jj - 1]) / (dy * dy) + (n[ii][jj] * n[ii][jj] - n0 * n0) * k0 * k0 * E2[ii][jj]);

#pragma omp parallel for
	for (ii = 0; ii <= Nx - 1; ii++)
#pragma omp parallel for
	    for (jj = 0; jj <= Ny - 1; jj++)
		E2[ii][jj] = E1[ii][jj] + 0.5 * dz * k2[ii][jj];

#pragma omp parallel for
	/***********************************************/
	for (ii = 1; ii <= Nx - 2; ii++)
#pragma omp parallel for
	    for (jj = 1; jj <= Ny - 2; jj++)
		k3[ii][jj] = (-I * nn / n0 / k0 / 2) *
			((E2[ii + 1][jj] - 2 * E2[ii][jj] + E2[ii - 1][jj]) / (dx * dx) + (E2[ii][jj + 1] - 2 * E2[ii][jj] + E2[ii][jj - 1]) / (dy * dy) + (n[ii][jj] * n[ii][jj] - n0 * n0) * k0 * k0 * E2[ii][jj]);

#pragma omp parallel for
	for (ii = 1; ii <= Nx - 2; ii++)
#pragma omp parallel for
	    for (jj = 1; jj <= Ny - 2; jj++)
		E2[ii][jj] = E1[ii][jj] + dz * k3[ii][jj];

#pragma omp parallel for
	/***********************************************/
	for (ii = 1; ii <= Nx - 2; ii++)
#pragma omp parallel for
	    for (jj = 1; jj <= Ny - 2; jj++)
		k4[ii][jj] = (-I * nn / n0 / k0 / 2) *
			((E2[ii + 1][jj] - 2 * E2[ii][jj] + E2[ii - 1][jj]) / (dx * dx) + (E2[ii][jj + 1] - 2 * E2[ii][jj] + E2[ii][jj - 1]) / (dy * dy) + ((n[ii][jj] * n[ii][jj]) - (n0 * n0)) * k0 * k0 * E2[ii][jj]);

#pragma omp parallel for
	for (ii = 1; ii <= Nx - 2; ii++)
#pragma omp parallel for
	    for (jj = 1; jj <= Ny - 2; jj++)
		E2[ii][jj] = E1[ii][jj] + (k1[ii][jj] + 2 * k2[ii][jj] + 2 * k3[ii][jj] + k4[ii][jj]) * dz / 6;


	/*************TBC Upper**************************/
	for (jj = 0; jj <= Ny - 1; jj++)
	{
	    if (E2[2][jj] != 0)
	    {
		kx1 = I / dx * clog(E2[1][jj] / E2[2][jj]);
		if (creal(kx1) < 0)
		{
		    kx1 = 0;
		}
		E2[0][jj] = E2[1][jj] * cexp(-I * kx1 * dx);
	    }
	}


	/*************TBC Lower*************************/
	for (jj = 0; jj <= Ny - 1; jj++)
	{
	    if (E2[Nx - 3][jj] != 0)
	    {
		kx1 = I / dx * clog(E2[Nx - 2][jj] / E2[Nx - 3][jj]);
		if (creal(kx1) < 0)
		{
		    kx1 = 0;
		}
		E2[Nx - 1][jj] = E2[Nx - 2][jj] * cexp(-I * kx1 * dx);
	    }
	}


	/*************TBC Left**************************/
	for (ii = 0; ii <= Nx - 1; ii++)
	{
	    if (E2[ii][2] != 0)
	    {
		ky1 = I / dy * clog(E2[ii][1] / E2[ii][2]);
		if (creal(ky1) < 0)
		{
		    ky1 = 0;
		}
		E2[ii][0] = E2[ii][1] * cexp(-I * ky1 * dx);
	    }
	}

	/******************TBC Right**************************/
	for (ii = 0; ii <= Nx - 1; ii++)
	{
	    if (E2[ii][Ny - 3] != 0)
	    {
		ky1 = I / dy * clog(E2[ii][Ny - 2] / E2[ii][Ny - 3]);
		if (creal(ky1) < 0)
		{
		    ky1 = 0;
		}
		E2[ii][Ny - 1] = E2[ii][Ny - 2] * cexp(-I * ky1 * dx);
	    }
	}
	/***********************************************/
//	#pragma omp parallel for 
        for (ii=0;ii<=Nx-1;ii++)

            for (jj=0;jj<=Ny-1;jj++)
                E1[ii][jj]=E2[ii][jj];

	/**************************************************/

	if ( mm == 1 || mm % 10000 == 0 )
	{
	    sprintf(buffer, "%ld.dat", mm);
	    FILE           *f;

	    f = fopen(buffer, "w");
	    for (ii = 0; ii <= Nx - 1; ii++)
	    {
		fprintf(f, "\n");
		for (jj = 0; jj <= Ny - 1; jj++)
		    fprintf(f, "%f ", cabs(E2[ii][jj]));
	    }
	    fclose(f);
	}

	if (omp_get_thread_num() == 0)
	{
	    FILE           *fff;

	    fff = fopen("counter.dat", "w");
	    fprintf(fff, "%f\n", mm * dz);
	    fclose(fff);
	}
    }

    /***********Absolute value of the output********/

    FILE           *g1;

    g1 = fopen("SigmaS.dat", "w");
    for (mm = 1; mm <= Nz; mm++)
    {
	fprintf(g1, "%f  %f", mm * dz, SigmaS[mm - 1]);
	fprintf(g1, "\n");
    }
    fclose(g1);
    /**************************************************/
    FILE           *g2;

    g2 = fopen("Sigmax.dat", "w");
    for (mm = 1; mm <= Nz; mm++)
    {
	fprintf(g2, "%f  %f", mm * dz, 2 * sqrt(Sigmax[mm - 1]));
	fprintf(g2, "\n");
    }
    fclose(g2);
    /**************************************************/
    FILE           *H;

    H = fopen("power.dat", "w");
    for (mm = 1; mm <= Nz; mm++)
    {
	fprintf(H, "%f  %f", mm * dz, power[mm - 1]);
	fprintf(H, "\n");
    }
    fclose(H);
}
