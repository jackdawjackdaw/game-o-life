#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/time.h>
#include <gsl/gsl_rng.h>

#define WDEFAULT 16
#define HDEFAULT 16

void printGrid(int grid[][HDEFAULT]);
void randomInit(int grid[][HDEFAULT], double onProp, gsl_rng * r);
unsigned long int get_seed_noblock(void);
void updateGrid(int grid_prev[][HDEFAULT], int grid_next[][HDEFAULT]);
int nsumPoint(int grid[][HDEFAULT], int i, int j);

int main (int argc, char* argv[]){

  int nsteps = 2;
  int g1[WDEFAULT][HDEFAULT], g2[WDEFAULT][HDEFAULT];

  for(int i = 0; i < WDEFAULT; i++)
    for(int j = 0; j < HDEFAULT; j++){
      g1[i][j] = 0;
      g2[i][j] = 0;
    }
  
  const gsl_rng_type *T;
  gsl_rng *rand;

  gsl_rng_env_setup();
  T = gsl_rng_default;
  rand = gsl_rng_alloc(T);

  gsl_rng_set(rand, get_seed_noblock());
  randomInit(g1, 0.55, rand);

  /* a block */
  /* g1[2][2] = 1; */
  /* g1[3][2] = 1; */
  /* g1[2][3] = 1;   */
  /* g1[3][3] = 1; */

  printGrid(g1);

  updateGrid(g1,g2);

  printf("# updated \n");
  printGrid(g2);

  for(int i = 0; i < nsteps; i++){
    // blit g2 back into g1
    memcpy(g1, g2, sizeof(int)*WDEFAULT*HDEFAULT);
    // now update g1
    updateGrid(g1,g2);
    printGrid(g2);
  }
  

  gsl_rng_free(rand);
  return EXIT_SUCCESS;
}

void randomInit(int grid[][HDEFAULT], double onProp, gsl_rng * r)
{
  int i, j;

  for(i = 0; i < WDEFAULT; i++)
    for(j = 0; j < HDEFAULT; j++){
      if(gsl_rng_uniform(r) <= onProp){
        grid[i][j] = 1;
      } else {
        grid[i][j] = -1;
      }
    }
  
}


int nsumPoint(int grid[][HDEFAULT], int i, int j)
{
  /** compute the total around the given point
   *
   *   A B C 
   *   D X E  where x is our actual point
   *   F G H
   *
   * nsum = A + B + ... + H
   * 
   * first lets define some wrapping index offests
   */
  int leftX = (i - 1 + WDEFAULT) % WDEFAULT;
  int rightX = (i + 1) % WDEFAULT;
  int upY = (j - 1 + HDEFAULT) % HDEFAULT;
  int downY = (j + 1 ) % HDEFAULT;

  /* return the sum following the alphabetical ordering 
   * in the diagram*/
  return( grid[i][j]+ 
          grid[leftX][upY] + 
          grid[i][upY] +
          grid[rightX][upY] + 
          grid[leftX][j] + 
          grid[rightX][j] +
          grid[leftX][downY] +
          grid[i][downY] +
          grid[rightX][downY] );
  
}

void updateGrid(int grid_prev[][HDEFAULT], int grid_next[][HDEFAULT])
{
  int i,j;
  int nsum;
  
  /** for each point x = grid[i][j] if
   *  nsum(x) = 3 -> life
   *  nsum(x) = 4 -> current state
   *  otherwise -> death
   */
  for(i = 0; i < WDEFAULT; i++){
    for(j = 0; j < HDEFAULT; j++){
      nsum = nsumPoint(grid_prev, i, j);
      switch(nsum){
      case 3:
        /* always alive */
        grid_next[i][j] = 1;
        break;
      case 4:
        /* toggle the state */
        grid_next[i][j] = grid_prev[i][j];
        break;
      default: 
        grid_next[i][j] = 0;
        break;
      }
    }
  }

}

void printGrid(int grid[][HDEFAULT])
{
  int i, j;

  setlocale (LC_ALL,"");

  // print border first
  printf(".");
  for(i = 0; i < WDEFAULT+1; i++) printf("-");
  printf(".\n");

  for(i = 0; i < HDEFAULT; i++){
    printf("|");
    for(j = 0; j < WDEFAULT+1; j++){
      
      if(grid[j][i] > 0){
        printf("o");
      } else {
        printf(" ");
      }
      //printf("%d", nsumPoint(grid, i, j));
      
    }
    printf("|\n");
  }

  printf(".");
  for(i = 0; i < WDEFAULT+1; i++) printf("-");
  printf(".\n");

}


/** RNG
 *  tries to read from /dev/random, or otherwise uses the system time
 */
unsigned long int get_seed_noblock(void)
{
  unsigned long int seed;
  struct timeval tv;
  FILE *devrandom;

  if((devrandom = fopen("/dev/urandom", "r")) == NULL){
    gettimeofday(&tv, 0);
    seed = tv.tv_sec + tv.tv_usec;
    //fprintf(stderr,"Got seed %u from gettimeofday()\n", seed);
  }
  else {
    fread(&seed, sizeof(seed), 1, devrandom);
    //fprintf(stderr, "Got seed %u from /dev/random\n", seed);
    fclose(devrandom);
  }
  return(seed);
}
