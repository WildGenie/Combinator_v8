/*
 * =============================================================
 * Calculation of spectral data
 * =============================================================
 */



#include "mex.h"

void SpecMe(double *wnum, double *abroad, double *sbroad,double *intCrossSection, double Ptotal, double Pself, double T, int Lower, int Upper, double *g, double instrGaussianFWHM, double instrLorentzianFWHM)

{
   int i=0,j=0,indh=0, temp = 0;
   double gammaPT = 0,gammaPT2 = 0;
   double nu=0,h=0;
   
   
   
   for (i=0;i<((Upper-Lower+20)*100+1);i++)
      g[i]=0;
   
   
   
   for (i=0;i<L;i++)
    {
      gammaPT=(296/T)*(abroad[i]*(Ptotal-Pself)+sbroad[i]*Pself);
      gammaPT2=gammaPT*gammaPT;
      temp = (wnum[i]-10)*100;
      
      for(j=0;j<2001;j++)
       {
          nu =(temp/100.00)+(j*0.01);
          h	= inte[i] *gammaPT /3.1416/(gammaPT2 + (nu-wnum[i]) * (nu-wnum[i]));
       	  //indh =  temp-99000+j;
          indh = temp-(Lower-10)*100+j;
          //g[indh] = wnum[i];
          g[indh]  = g[indh] + h;
       }
    }      
    
   
    
}

/* The gateway routine */
void mexFunction(int nlhs, mxArray *plhs[], 
                 int nrhs, const mxArray *prhs[])
{
  double *wnum, *abroad, *sbroad, *inte, *g;
  double P, Pa, T;
  int mrows,ncols,L,Lower,Upper;
  
  
  /*  Check for proper number of arguments. */
  /* NOTE: You do not need an else statement when using 
     mexErrMsgTxt within an if statement. It will never 
     get to the else statement if mexErrMsgTxt is executed. 
     (mexErrMsgTxt breaks you out of the MEX-file.) 
  */ 
  if (nrhs != 10) 
    mexErrMsgTxt("Ten inputs required.");
  if (nlhs != 1) 
    mexErrMsgTxt("One output required.");
  
  /* Check to make sure the first input argument is a scalar. 
  if (!mxIsDouble(prhs[0]) || mxIsComplex(prhs[0]) ||
      mxGetN(prhs[0])*mxGetM(prhs[0]) != 1) {
    mexErrMsgTxt("Input x must be a scalar.");
  }
  */
  
  /* Get the scalar input x. */
  P = mxGetScalar(prhs[4]);
  Pa = mxGetScalar(prhs[5]);
  T = mxGetScalar(prhs[6]);
  L = mxGetScalar(prhs[7]);
  Lower = mxGetScalar(prhs[8]);
  Upper = mxGetScalar(prhs[9]);
  
  /* Create a pointer to the input matrix y. */
  wnum = mxGetPr(prhs[0]);
  abroad = mxGetPr(prhs[1]);
  sbroad = mxGetPr(prhs[2]);
  inte = mxGetPr(prhs[3]);
  
  
  /* Get the dimensions of the matrix input y. */
  mrows = 1; // mxGetM(prhs[1]);
  ncols = (mxGetScalar(prhs[9])-mxGetScalar(prhs[8])+20)*100+1; //mxGetN(prhs[1]);
  
  /* Set the output pointer to the output matrix. */
  plhs[0] = mxCreateDoubleMatrix(mrows,ncols, mxREAL);
  //plhs[0] = mxCreateNumericArray(ncols, mxREAL);
  
  /* Create a C pointer to a copy of the output matrix. */
  g = mxGetPr(plhs[0]);
  
  /* Call the C subroutine. */
  SpecMe(wnum,abroad,sbroad,inte,P,Pa,T,L,Lower,Upper,g);
}
