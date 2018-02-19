#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include <math.h>

#ifndef min
    #define min(a,b) ((a) < (b) ? (a) : (b))
#endif

double get_cur_time();

void block_MM (int n, int bsize, double *A, double *B, double *C);
void block_MMR (int n, int bsize, double *A, double *B, double *C);

void block_MM_un2(int n, int bsize, double* A, double* B, double* C);
void block_MM_un4(int n, int bsize, double* A, double* B, double* C);
void block_MM_un8(int n, int bsize, double* A, double* B, double* C);
void block_MM_un16(int n, int bsize, double* A, double* B, double* C);

void block_MMR_un4(int n, int bsize, double* A, double* B, double* C);
void block_MMR_un8(int n, int bsize, double* A, double* B, double* C);
void block_MMR_un16(int n, int bsize, double* A, double* B, double* C);

void naive1 (int n, double *A, double *B, double *C);
void naive2 (int n, double *A, double *B, double *C);
void naive3 (int n, double *A, double *B, double *C);
void naive4 (int n, double *A, double *B, double *C);
void naive5 (int n, double *A, double *B, double *C);
void naive6 (int n, double *A, double *B, double *C);

int main(int argc, char** argv)
{
  double btime, etime;
  int i, z, j, x, n, y, narr[6] = {64, 128, 256, 512, 1024, 2048}, bsize[5] = {2, 4, 8, 16, 32}, b_size;
  const char *sstr[6];
  sstr[0] = "IJK";
  sstr[1] = "IKJ";
  sstr[2] = "JIK";
  sstr[3] = "JKI";
  sstr[4] = "KIJ";
  sstr[5] = "KJI";
  long long counters1[2],counters2[2], counters3[2], counters4[2], counters5[2], counters6[2], counters7[2], counters8[2], counters9[2], counters10[2], counters11[2],
           counters12[2], counters13[2], counters14[2], counters15[2], counters16[2], counters17[2], counters18[2], counters19[2], counters20[2], counters21[2], counters22[2], counters23[2];

  int PAPI_events1[] = {
                PAPI_L1_DCM,
                PAPI_L1_DCA};
  int PAPI_events2[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events3[] = {
                PAPI_L1_DCM,
                PAPI_L1_DCA};
  int PAPI_events4[] = {PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events5[] = {
                PAPI_L1_DCM,
                PAPI_L1_DCA};
  int PAPI_events6[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events7[] = {
                PAPI_L1_DCM,
                PAPI_L1_DCA};
  int PAPI_events8[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events9[] = {
                PAPI_L1_DCM,
                PAPI_L1_DCA};
  int PAPI_events10[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events11[] = {
                PAPI_L1_DCM,
                PAPI_L1_DCA};
  int PAPI_events12[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events13[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events14[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events15[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events16[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events17[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events18[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events19[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events20[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events21[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events22[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  int PAPI_events23[] = {
                PAPI_L2_DCM,
                PAPI_L2_DCA};
  if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
     exit(1);

  srand((unsigned)time(NULL));

 printf("\nNAIVE MATRIX MULTIPLICATION\n");
 for(j = 0; j < 6; j++)
  {
        n = narr[j];
        double *A = malloc(n*n*sizeof(double));
        double *B = malloc(n*n*sizeof(double));
        double *C = malloc(n*n*sizeof(double));
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(int x = 0; x < 6; x++)
        {
                int r = x + 1;
                printf("\nLoop-%s information\n",sstr[x]);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                switch(r)
                {
                        case 1:
                                PAPI_start_counters(PAPI_events1, 2);
                                PAPI_start_counters(PAPI_events2, 2);
                                btime = get_cur_time();
                                naive1(n,A,B,C);
                                etime = get_cur_time();
                                PAPI_read_counters(counters1, 2);
                                PAPI_read_counters(counters2, 2);
                                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters1[0] / (double)counters1[1]);
                                printf("L2 cache misses\t: \t%.3lf%% misses\n",100*(double)counters2[0] / (double)counters2[1]);
                                break;
                        case 2:
                                PAPI_start_counters(PAPI_events3, 2);
                                PAPI_start_counters(PAPI_events4, 2);
                                btime = get_cur_time();
                                naive2(n,A,B,C);
                                etime = get_cur_time();
                                PAPI_read_counters(counters3, 2);
                                PAPI_read_counters(counters4, 2);
                                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters3[0] / (double)counters3[1]);
                                printf("L2 cache misses\t: \t%.3lf%% misses\n",100*(double)counters4[0] / (double)counters4[1]);
                                break;
                        case 3:
                                PAPI_start_counters(PAPI_events5, 2);
                                PAPI_start_counters(PAPI_events6, 2);
                                btime = get_cur_time();
                                naive3(n,A,B,C);
                                etime = get_cur_time();
                                PAPI_read_counters(counters5, 2);
                                PAPI_read_counters(counters6, 2);
                                printf("Elapsed time\t: %16.9f seconds\n",(etime-btime));
                                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters5[0] / (double)counters5[1]);
                                printf("L2 cache misses\t: \t%.3lf%% misses\n",100*(double)counters6[0] / (double)counters6[1]);
                                break;
                        case 4:
                                PAPI_start_counters(PAPI_events7, 2);
                                PAPI_start_counters(PAPI_events8, 2);
                                btime = get_cur_time();
                                naive4(n,A,B,C);
                                etime = get_cur_time();
                                PAPI_read_counters(counters7, 2);
                                PAPI_read_counters(counters8, 2);
                                printf("Elapsed time\t: %16.9f seconds\n",(etime-btime));
                                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters7[0] / (double)counters7[1]);
                                printf("L2 cache misses\t: \t%.3lf%% misses\n",100*(double)counters8[0] / (double)counters8[1]);
                                break;
                        case 5:
                                PAPI_start_counters(PAPI_events9, 2);
                                PAPI_start_counters(PAPI_events10, 2);
                                btime = get_cur_time();
                                naive5(n,A,B,C);
                                etime = get_cur_time();
                                PAPI_read_counters(counters9, 2);
                                PAPI_read_counters(counters10, 2);
                                printf("Elapsed time\t: %16.9f seconds\n",(etime-btime));
                                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters9[0] / (double)counters9[1]);
                                printf("L2 cache misses\t: \t%.3lf%% misses\n",100*(double)counters10[0] / (double)counters10[1]);
                                break;
                        case 6:
                                PAPI_start_counters(PAPI_events11, 2);
                                PAPI_start_counters(PAPI_events12, 2);
                                btime = get_cur_time();
                                naive6(n,A,B,C);
                                etime = get_cur_time();
                                PAPI_read_counters(counters11, 2);
                                PAPI_read_counters(counters12, 2);
                                printf("Elapsed time\t: %16.9f seconds\n",(etime-btime));
                                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters11[0] / (double)counters11[1]);
                                printf("L2 cache misses\t: \t%.3lf%% misses\n",100*(double)counters12[0] / (double)counters12[1]);
                                break;
                }
  }

  }
*/
  printf("\n\nBLOCK MATRIX MULTIPLICATION\n");
  for(int c = 0; c < 6; c++)
  {
        n = narr[c];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = (double *)malloc(n*n*sizeof(double));
                double *B = (double *)malloc(n*n*sizeof(double));
                double *C = (double *)malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(z = 0; z < n*n; z++)
                {
                        A[z] = ((double)rand()/(double)RAND_MAX);
                        B[z] = ((double)rand()/(double)RAND_MAX);
                        C[z] = ((double)rand()/(double)RAND_MAX);
                }
                PAPI_start_counters(PAPI_events13, 2);
                btime = get_cur_time();
                block_MM(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters13, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters13[0] / (double)counters13[1]);
        }
  }

  printf("\n\nBlock Matrix Multiplication using registers\n");
  for(j = 0; j < 6; j++)
  {
        n = narr[j];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = malloc(n*n*sizeof(double));
                double *B = malloc(n*n*sizeof(double));
                double *C = malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                PAPI_start_counters(PAPI_events14, 2);
                btime = get_cur_time();
                block_MMR(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters14, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters14[0] / (double)counters14[1]);
        }
  }

  printf("\n\nBlock Matrix Multiplication with loop unrolling level-2\n");
  for(j = 0; j < 6; j++)
  {
        n = narr[j];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = malloc(n*n*sizeof(double));
                double *B = malloc(n*n*sizeof(double));
                double *C = malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                PAPI_start_counters(PAPI_events15, 2);
                btime = get_cur_time();
                block_MM_un2(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters15, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters15[0] / (double)counters15[1]);
        }
  }
  printf("\n\nBlock Matrix Multiplication with loop unrolling level-4\n");
  for(j = 0; j < 6; j++)
  {
        n = narr[j];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = malloc(n*n*sizeof(double));
                double *B = malloc(n*n*sizeof(double));
                double *C = malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                PAPI_start_counters(PAPI_events15, 2);
                btime = get_cur_time();
                block_MM_un4(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters16, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters16[0] / (double)counters16[1]);
        }
  }
  printf("\n\nBlock Matrix Multiplication with loop unrolling level-8\n");
  for(j = 0; j < 6; j++)
  {
        n = narr[j];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = malloc(n*n*sizeof(double));
                double *B = malloc(n*n*sizeof(double));
                double *C = malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                PAPI_start_counters(PAPI_events17, 2);
                btime = get_cur_time();
                block_MM_un8(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters17, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters17[0] / (double)counters17[1]);
        }
  }
  printf("\n\nBlock Matrix Multiplication with loop unrolling level-16\n");
  for(j = 0; j < 6; j++)
  {
        n = narr[j];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = malloc(n*n*sizeof(double));
                double *B = malloc(n*n*sizeof(double));
                double *C = malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                PAPI_start_counters(PAPI_events18, 2);
                btime = get_cur_time();
                block_MM_un16(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters18, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters18[0] / (double)counters18[1]);
        }
  }


  printf("\n\nBlock Matrix Multiplication with loop unrolling level-4, and using register\n");
  for(j = 0; j < 6; j++)
  {
        n = narr[j];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = malloc(n*n*sizeof(double));
                double *B = malloc(n*n*sizeof(double));
                double *C = malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                PAPI_start_counters(PAPI_events19, 2);
                btime = get_cur_time();
                block_MMR_un4(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters19, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters19[0] / (double)counters19[1]);
        }
  }
  printf("\n\nBlock Matrix Multiplication with loop unrolling level-8, and using registers\n");
  for(j = 0; j < 6; j++)
  {
        n = narr[j];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = malloc(n*n*sizeof(double));
                double *B = malloc(n*n*sizeof(double));
                double *C = malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                PAPI_start_counters(PAPI_events20, 2);
                btime = get_cur_time();
                block_MMR_un8(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters20, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters20[0] / (double)counters20[1]);
        }
  }

  printf("\n\nBlock Matrix Multiplication with loop unrolling level-16, and using registers\n");
  for(j = 0; j < 6; j++)
  {
        n = narr[j];
        printf("\n========================================================================================\n");
        printf("Input size N = %d\n",n);
        for(x = 0; x < 5; x++)
        {
                b_size = bsize[x];
                double *A = malloc(n*n*sizeof(double));
                double *B = malloc(n*n*sizeof(double));
                double *C = malloc(n*n*sizeof(double));
                printf("\nBlock size B = %d\n",b_size);
                for(i = 0; i < n*n; i++)
                {
                        A[i] = rand();
                        B[i] = rand();
                        C[i] = rand();
                }
                PAPI_start_counters(PAPI_events22, 2);
                btime = get_cur_time();
                block_MMR_un16(n,b_size,A,B,C);
                etime = get_cur_time();
                PAPI_read_counters(counters22, 2);
                printf("Elapsed time\t:  %16.9f seconds\n",(etime-btime));
                printf("L1 cache misses\t: \t%.3lf%% misses\n",100*(double)counters22[0] / (double)counters22[1]);
        }
  }
  return 0;
}

double get_cur_time()
{
  return PAPI_get_real_usec() / 1000000.0;
}

void block_MM(int n, int bsize, double* A, double* B, double* C)
{
        for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i++){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j++){
                                        double temp = 0;
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++){
                                                temp += A[i*n+k]*B[k*n+j];
                                        }
                                        C[i*n+j] += temp;
                        }
                }
        }
}
}

void block_MMR(int n, int bsize, double* A, double* B, double* C)
{

      for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i++){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j++){
                                        register double temp = 0;
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++){
                                                temp += A[i*n+k]*B[k*n+j];
                                        }
                                        C[i*n+j] += temp;
                        }
                }
        }
}
}

void block_MM_un2(int n, int bsize, double* A, double* B, double* C)
{

        for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i++){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j += 2){
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++ ){
                                                C[i*n+j] += A[i*n+k]*B[k*n+j];
                                                C[i*n+j+1] += A[i*n+k]*B[k*n+j+1];
                                        }

                        }
                }
        }
}
}

void block_MM_un4(int n, int bsize, double* A, double* B, double* C)
{
        for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i += 2){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j += 2){
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++ ){
                                                C[i*n+j] += A[i*n+k]*B[k*n+j];
                                                C[i*n+j+1] += A[i*n+k]*B[k*n+j+1];
                                                C[(i+1)*n+j] += A[(i+1)*n+k]*B[k*n+j];
                                                C[(i+1)*n+j+1] += A[(i+1)*n+k]*B[k*n+j+1];
                                        }

                        }
                }
        }
}
}

void block_MM_un8(int n, int bsize, double* A, double* B, double* C)
{

        for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i += 2){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j += 4){
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++ ){
                                                C[i*n+j] += A[i*n+k]*B[k*n+j];
                                                C[i*n+j+1] += A[i*n+k]*B[k*n+j+1];
                                                C[i*n+j+2] += A[i*n+k]*B[k*n+j+2];
                                                C[i*n+j+3] += A[i*n+k]*B[k*n+j+3];
                                                C[(i+1)*n+j] += A[(i+1)*n+k]*B[k*n+j];
                                                C[(i+1)*n+j+1] += A[(i+1)*n+k]*B[k*n+j+1];
                                                C[(i+1)*n+j+2] += A[(i+1)*n+k]*B[k*n+j+2];
                                                C[(i+1)*n+j+3] += A[(i+1)*n+k]*B[k*n+j+3];
                                        }

                        }
                }
        }
}
}

void block_MM_un16(int n, int bsize, double* A, double* B, double* C)
{
        for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i += 4){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j += 4){
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++ ){
                                                C[i*n+j] += A[i*n+k]*B[k*n+j];
                                                C[i*n+j+1] += A[i*n+k]*B[k*n+j+1];
                                                C[i*n+j+2] += A[i*n+k]*B[k*n+j+2];
                                                C[i*n+j+3] += A[i*n+k]*B[k*n+j+3];
                                                C[(i+1)*n+j] += A[(i+1)*n+k]*B[k*n+j];
                                                C[(i+1)*n+j+1] += A[(i+1)*n+k]*B[k*n+j+1];
                                                C[(i+1)*n+j+2] += A[(i+1)*n+k]*B[k*n+j+2];
                                                C[(i+1)*n+j+3] += A[(i+1)*n+k]*B[k*n+j+3];
                                                C[(i+2)*n+j] += A[(i+2)*n+k]*B[k*n+j];
                                                C[(i+2)*n+j+1] += A[(i+2)*n+k]*B[k*n+j+1];
                                                C[(i+2)*n+j+2] += A[(i+2)*n+k]*B[k*n+j+2];
                                                C[(i+2)*n+j+3] += A[(i+2)*n+k]*B[k*n+j+3];
                                                C[(i+3)*n+j] += A[(i+3)*n+k]*B[k*n+j];
                                                C[(i+3)*n+j+1] += A[(i+3)*n+k]*B[k*n+j+1];
                                                C[(i+3)*n+j+2] += A[(i+3)*n+k]*B[k*n+j+2];
                                                C[(i+3)*n+j+3] += A[(i+3)*n+k]*B[k*n+j+3];
                                        }

                        }
                }
        }
}
}

void block_MMR_un4(int n, int bsize, double* A, double* B, double* C)
{

        for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i += 2){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j += 2){
                                        register double cij, cijj, ciij, ciijj;
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++ ){
                                                cij = A[i*n+k]*B[k*n+j];
                                                cijj = A[i*n+k]*B[k*n+j+1];
                                                ciij = A[(i+1)*n+k]*B[k*n+j];
                                                ciijj = A[(i+1)*n+k]*B[k*n+j+1];
                                                C[i*n+j] += cij;
                                                C[(i+1)*n+j] += ciij;
                                                C[i*n+j+1] += cijj;
                                                C[(i+1)*n+j+1] += ciijj;
                                        }

                        }
                }
        }
}
}

void block_MMR_un8(int n, int bsize, double* A, double* B, double* C)
{

        for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i += 2){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j += 4){
                                        register double cij, cijj, cijjj, cijjjj, ciij, ciijj, ciijjj, ciijjjj;
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++ ){
                                                cij = A[i*n+k]*B[k*n+j];
                                                cijj = A[i*n+k]*B[k*n+j+1];
                                                cijjj = A[i*n+k]*B[k*n+j+2];
                                                cijjjj = A[i*n+k]*B[k*n+j+3];
                                                ciij = A[(i+1)*n+k]*B[k*n+j];
                                                ciijj = A[(i+1)*n+k]*B[k*n+j+1];
                                                ciijjj = A[(i+1)*n+k]*B[k*n+j+2];
                                                ciijjjj = A[(i+1)*n+k]*B[k*n+j+3];
                                                C[i*n+j] +=cij;
                                                C[i*n+j+1] +=cijj;
                                                C[i*n+j+2] +=cijjj;
                                                C[i*n+j+3] +=cijjjj;
                                                C[(i+1)*n+j] +=ciij;
                                                C[(i+1)*n+j+1] +=ciijj;
                                                C[(i+1)*n+j+2] +=ciijjj;
                                                C[(i+1)*n+j+3] +=ciijjjj;
                                        }

                        }
                }
        }
}
}

void block_MMR_un16(int n, int bsize, double* A, double* B, double* C)
{

        for(int jj=0;jj<n;jj+= bsize){
                for(int kk=0;kk<n;kk+= bsize){
                        for(int i=0;i<n;i += 4){
                                for(int j = jj; j<((jj+bsize)>n?n:(jj+bsize)); j += 4){
                                        register double cij, cijj, cijjj, cijjjj, ciij, ciijj, ciijjj, ciijjjj, ciiij, ciiijj, ciiijjj, ciiijjjj, ciiiij, ciiiijj, ciiiijjj, ciiiijjjj;;
                                        for(int k = kk; k<((kk+bsize)>n?n:(kk+bsize)); k++ ){
                                                cij = A[i*n+k]*B[k*n+j];
                                                cijj = A[i*n+k]*B[k*n+j+1];
                                                cijjj = A[i*n+k]*B[k*n+j+2];
                                                cijjjj = A[i*n+k]*B[k*n+j+3];
                                                ciij = A[(i+1)*n+k]*B[k*n+j];
                                                ciijj = A[(i+1)*n+k]*B[k*n+j+1];
                                                ciijjj = A[(i+1)*n+k]*B[k*n+j+2];
                                                ciijjjj = A[(i+1)*n+k]*B[k*n+j+3];
                                                ciiij = A[(i+2)*n+k]*B[k*n+j];
                                                ciiijj = A[(i+2)*n+k]*B[k*n+j+1];
                                                ciiijjj = A[(i+2)*n+k]*B[k*n+j+2];
                                                ciiijjjj = A[(i+2)*n+k]*B[k*n+j+3];
                                                ciiiij = A[(i+3)*n+k]*B[k*n+j];
                                                ciiiijj = A[(i+3)*n+k]*B[k*n+j+1];
                                                ciiiijjj = A[(i+3)*n+k]*B[k*n+j+2];
                                                ciiiijjjj = A[(i+3)*n+k]*B[k*n+j+3];
                                                C[i*n+j] +=cij;
                                                C[i*n+j+1] +=cijj;
                                                C[i*n+j+2] +=cijjj;
                                                C[i*n+j+3] +=cijjjj;
                                                C[(i+1)*n+j] +=ciij;
                                                C[(i+1)*n+j+1] +=ciijj;
                                                C[(i+1)*n+j+2] +=ciijjj;
                                                C[(i+1)*n+j+3] +=ciijjjj;
                                                C[(i+2)*n+j] +=ciij;
                                                C[(i+2)*n+j+1] +=ciijj;
                                                C[(i+2)*n+j+2] +=ciijjj;
                                                C[(i+2)*n+j+3] +=ciijjjj;
                                                C[(i+3)*n+j] +=ciij;
                                                C[(i+3)*n+j+1] +=ciijj;
                                                C[(i+3)*n+j+2] +=ciijjj;
                                                C[(i+3)*n+j+3] +=ciijjjj;
                                        }

                        }
                }
        }
}
}

void naive1(int n, double* A, double* B, double* C)
{
  int i = 0, j = 0, k = 0;
  for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            double cij = C[i*n+j];
            for(k = 0; k < n; k++ )
                cij += A[i*n+k] * B[k*n+j];
            C[i*n+j] = cij;
        }
}

void naive2(int n, double* A, double* B, double* C)
{
  int i = 0, j = 0, k = 0;
  double cij;
  for (i = 0; i < n; ++i)
      for (k = 0; k < n; ++k)
        for(j = 0; j < n; ++j)
        {
            cij = C[i*n+j];
            cij += A[i*n+k] * B[k*n+j];
            C[i*n+j] = cij;
        }
}

void naive3(int n, double* A, double* B, double* C)
{
  int i = 0, j = 0, k = 0;
  double cij;
  for (j = 0; j < n; j++)
   {
    for (i = 0; i < n; i++)
    {
        cij = C[n*i+j];
        for (k = 0; k < n; k++)
        {
            cij += A[n*i+k] * B[n*k+j];
            C[n*i+j] = cij;
        }
    }
}
}
void naive4(int n, double* A, double* B, double* C)
{
int i = 0, j = 0, k = 0;
  double cij;
  for (j = 0; j < n; ++j)
    for (k = 0; k < n; ++k)
        for(i = 0; i < n; ++i)
        {
            cij = C[i*n+j];
            cij += A[i*n+k] * B[k*n+j];
            C[i*n+j] = cij;
        }
}

 void naive5(int n, double* A, double* B, double* C)
{
  int i = 0, j = 0, k = 0;
  double cij;
  for (k = 0; k < n; ++k)
    for (i = 0; i < n; ++i)
        for(j = 0; j < n; ++j)
        {
            cij = C[i*n+j];
            cij += A[i*n+k] * B[k*n+j];
            C[i*n+j] = cij;
        }
}

void naive6(int n, double* A, double* B, double* C)
{
  int i = 0, j = 0, k = 0;
  double cij;
  for (k = 0; k < n; ++k)
    for (j = 0; j < n; ++j)
        for(i = 0; i < n; ++i)
        {
            cij = C[i*n+j];
            cij += A[i*n+k];
            C[i*n+j] = cij;
        }
}

                                                                                                                                                                    