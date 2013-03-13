/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include"cyberfoodLib3.h"
#include<time.h>

static int x_n = 429619; // initial seed
static int my_rand(void)
{
    const int A = 1664525;
    const int C = 1013904223;
    x_n = A*x_n + C;

    return (x_n & 0x3FFFFFFF);
}

#define TREES 10
#define LEAVES 100
#define FORESTS 10000

static double p[TREES];
static double t[LEAVES];
static double s[LEAVES];
static double m[LEAVES];
static int index;

static void create_forest(){
  int i;
	for (i=0; i<TREES; i++)
		p[i] = (1 + my_rand()%999) / 1000.0;
	for (i=0; i<LEAVES; i++)
		t[i] = (1 + my_rand()%999) / 1000.0;
	index = 0;
}

static void oracle(){
	int d=0;
        int i;
	for (i=1; i<TREES; i++)
		d = ( p[i] > p[d] ) ? i : d;
	for (i=0; i<LEAVES; i++)
		m[i] += ( t[i] < p[d] );
} 

int eat(int id){
	if (index>LEAVES){
		printf("No leaves left on the tree\n");
		exit(0);
	}
	s[index] += ( t[index] < p[id-1] );
	return t[index++] < p[id-1];
}

int main() {
  int f, i;
	for (f=0; f<FORESTS; f++){
		create_forest();
		happy_meal();
		oracle();
	}
	for (i=0; i<LEAVES; i++){
		s[i] = s[i]/FORESTS + (i ? s[i-1] : 0);
		m[i] = m[i]/FORESTS + (i ? m[i-1] : 0);
	}
        int ok = s[LEAVES-1]/m[LEAVES-1] >= 0.9;

        if(ok) {
          printf("CORRECT - b35b997444a2da663d387a90bdb52e73\n");
        } else {
          printf("%.1lf%% optimal\n", s[LEAVES-1]/m[LEAVES-1]*100);
          printf("INCORRECT\n");
        }

	return 0;
}
