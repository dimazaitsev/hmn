#include <stdio.h>
#include <stdlib.h>

char *HELP= "Generator of canvas for Petri net models of hypertorus (or hypercube) grid\n"
             "with von-Neumann's neihbourhood ( 2*d neighbors for an internal node ).\n\n"
             "Product of Dmitry Zaitsev member.acm.org/~daze\n\n" 
             "USAGE: hn d n [m] [e] > hn_model.net \n"
             "  d - number of dimensions (d>=1),\n"
             "  n - size of hypertorus or hypercube (n>=1; for hypertorus n>=3),\n"
             "  m - number of tokens in each node (m>=0, default 1),\n"
             "  e - edge: 't' - hypertorus, 'c' - hypercube (default 't'),\n"
             "  output format - .net file of Tina www.laas.fr/tina\n\n";

// connect node i (i=i1 or i=i2) with transitions common with node i1 or i2 (i1<i2) 
void prn_tb(char c1, char c2, int d, int *i1, int *i2, int *i)
{
  int k;
  printf("pl {p"); 
  for(k=d-1;k>=0;k--) printf(".%d",i[k]);
  printf("} {t%c",c1);
  for(k=d-1;k>=0;k--) printf(".%d",i1[k]);
  printf("v");
  for(k=d-1;k>=0;k--) printf(".%d",i2[k]);
  printf("} -> {t%c",c2);
  for(k=d-1;k>=0;k--) printf(".%d",i1[k]);
  printf("v");
  for(k=d-1;k>=0;k--) printf(".%d",i2[k]);
  printf("}\n");
}

int main(int argc, char * argv[])
{
  int d, n, m=1;
  char e='t';
  int next_node = 1, next_neihbor, jlessi, k, go, edge;
  
  if(argc<3 || argc>5)
  {
    printf(HELP);
    printf("*** actually: %d arguments\n", argc);
    return 2;
  }
  d = atoi(argv[1]);
  n = atoi(argv[2]);
  if(argc>3) m = atoi(argv[3]);
  if(argc>4) e = argv[4][0];
  if(e!='c'&&e!='t' || d<1 || n<1 || m<0 || e=='t'&&n<3)
  {
    printf(HELP);
    printf("*** actually: d=%d n=%d m=%d e=%c\n", d,n,m,e);
    return 2;
  }
  
  int *i = malloc(d*sizeof(int)); // current node coordinate
  int *u = malloc(d*sizeof(int)); // coordinates' difference
  int *j = malloc(d*sizeof(int)); // neighbor node coordinate
  
  // initialize i
  for(k=0;k<d;k++) i[k]=0;
  
  while(next_node)
  {
    // initialize u
    for(k=0;k<d;k++) u[k]=0; u[0]=-1;
    next_neihbor = 1;
  
    while(next_neihbor)
    {   
      // calc j = i + u and edge condition
      edge=0;
      for(k=0;k<d;k++) { j[k]=i[k]+u[k]; if(j[k]<0 || j[k]>n-1) edge=1; }
      
      if(e!='c' || !edge )
      {
        // close edges of torus
        if(e=='t'&&edge) for(k=0;k<d;k++) { if(j[k]<0) j[k]=n-1; else if (j[k]>n-1) j[k]=0; }
        
        // calculate jlessi
        jlessi=1;
        for(k=d-1;k>=0;k--) { if(j[k]<i[k]) break; if(j[k]>i[k]){jlessi=0;break;} }
        
        // connect node i with transitions common with node j
        if(jlessi)
          prn_tb('o','i',d,j,i,i);   
        else   
          prn_tb('i','o',d,i,j,i);
       
      }    
      
      // next neihbor in von-Neumann's neighborhood (Manhatten distanse == 1)
      k=0;go=1;
      while(go)
      {
        if(u[k]==0) k++; 
        else if(u[k]==-1) {u[k]=1;go=0;}
        else {u[k]=0; k++; go=0; if(k<d) u[k]=-1; else next_neihbor=0; }
      }
      
    } /* while(next neihbour) */
    
    printf("pl {p"); 
    for(k=d-1;k>=0;k--) printf(".%d",i[k]);
    printf("} (%d)\n",m);
    
    // next node
    k=0;go=1;
    while(go)
    {
      if(++(i[k]) < n) go=0; else {i[k]=0; k++; if(k>=d) {go=0; next_node=0;}}
    }  
    
  } /* while(next_node) */
  
  printf("net hn_d%dn%dm%d%c\n",d,n,m,e);
  
} /* main */

/*
The MIT License (MIT)

Copyright (c) 2015 Dmitry Zaitsev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

