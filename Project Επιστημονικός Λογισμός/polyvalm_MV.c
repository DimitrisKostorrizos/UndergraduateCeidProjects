#include "stdio.h"
#include "mex.h"
#include "matrix.h"
#include "stdlib.h"


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double *poly = mxGetDoubles(prhs[0]);
	double *matrix = mxGetDoubles(prhs[1]);
	double *vector = mxGetDoubles(prhs[2]);
	mwSize ncols = mxGetN(prhs[1]);           /* size of matrix */
	mwSize polylen = mxGetN(prhs[0]);           /* size of poly */

	double p;
	double sum;
	double *outMatrix;
	double *vec = (double*)malloc(ncols * sizeof(double)); 
	double *coefficient = (double*)calloc(ncols, sizeof(double)); 
	double *tempvec = (double*)malloc(ncols * sizeof(double)); 
	memcpy(vec, vector, ncols * sizeof(double));
	
	for(mwSize k = 0; k < polylen; k++)
	{
		p = poly[4 - k];
		for (mwSize index = 0; index < ncols; index++)
		{
			coefficient[index] += vec[index] * p; 
		}
		if(k != polylen - 1) //Avoid calculation during the last coefficient
		{
			for (mwSize index = 0; index < ncols; index++)//Matrix Vector Multiplication
			{
				sum = 0;
				for (mwSize counter = 0; counter < ncols; counter++)
				{
					sum += matrix[index + counter*ncols] * vec[counter];
				}
				tempvec[index] = sum;
			}

			memcpy(vec, tempvec, ncols * sizeof(double));
		}
	}
	
	plhs[0] = mxCreateDoubleMatrix(ncols,1,mxREAL);
	memcpy(mxGetDoubles(plhs[0]), coefficient, ncols * sizeof(double));
}