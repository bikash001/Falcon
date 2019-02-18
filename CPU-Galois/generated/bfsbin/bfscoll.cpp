#include "bfscoll.h"
HGraph  hgraph ;

Galois::InsertBag<struct node>  pred ;

template<typename Pusher0 >
void   relaxEdge ( int & p ,HGraph & hgraph ,int  & p1 ,int   weight ,Pusher0 &pred ) 
{
int   changed =0;
int   ddata =((struct struct_hgraph  *)(hgraph.extra))->dist[p];
int   newdist =((struct struct_hgraph  *)(hgraph.extra))->dist[p1]+weight;

if( newdist<((struct struct_hgraph  *)(hgraph.extra))->dist[p]  )
{
((struct struct_hgraph  *)(hgraph.extra))->dist[p]=newdist; 
struct node   tt1 ;
tt1.w=newdist; 
tt1.n1=p; 
pred.push(tt1); 
}
}

template<typename Pusher0 >
void   relaxNode1 ( struct node  req ,HGraph & hgraph ,Pusher0 &pred ) 
{
int p1;
struct node   temp ;
temp=req; 
p1=temp.n1; 

int falcft0=hgraph.index[p1+1]-hgraph.index[p1];
int falcft1=hgraph.index[p1];
for(int falcft2=0;falcft2<falcft0;falcft2++){
int ut0=2*(falcft1+falcft2);
int ut1=hgraph.edges[ut0].ipe;
int ut2=hgraph.edges[ut0+1].ipe;
int t=ut1;
if( ((struct struct_hgraph  *)(hgraph.extra))->dist[ut1]>(((struct struct_hgraph  *)(hgraph.extra))->dist[p1]+1)  )
{
((struct struct_hgraph  *)(hgraph.extra))->dist[ut1]=((struct struct_hgraph  *)(hgraph.extra))->dist[p1]+1; 
struct node   tt1 ;
tt1.w=((struct struct_hgraph  *)(hgraph.extra))->dist[ut1]; 
tt1.n1=t; 
pred.push(tt1); 
}
}
}

struct nodeIndexer:public std::unary_function<struct node,unsigned int> {
unsigned int operator()(const struct node &val)const {
unsigned int t=val.w/4;
return t;
}
};

using namespace Galois::WorkList;
typedef dChunkedFIFO<64> Chunk;
typedef OrderedByIntegerMetric<struct nodeIndexer,Chunk,10> OBIM;

struct Process1 {
Process1(){}
template <typename Pusher > 
void operator()(struct node &req,Pusher &pred ){
relaxNode1(req,hgraph,pred);
}
};

void falctfun0(int &id,HGraph &hgraph){
if (id < hgraph.npoints) {
((struct struct_hgraph  *)(hgraph.extra))->dist[id]=1234567890;
}
}

int   main ( int   argc ,char    *  argv [ ] ) 
{
  int argct1= argc > 4 ?4:argc;
  LonestarStart(argct1,argv,name,desc,url);
  if(argc>2)FALC_THREADS=atoi(argv[2]);
  int p;
  
  if( argc<4  )
  {
    printf("exec -t theads input");
    return 1;
  }

  hgraph.read2(argv[3]);
  int hosthgraph=0;
  alloc_extra_hgraph(hgraph,hosthgraph,hgraph.npoints);
  double   rt1 =rtclock();

  #pragma omp parallel for   num_threads(FALC_THREADS)
  for(int id=0;id<hgraph.npoints;id++)falctfun0( id,hgraph);

  p=0; 
  ((struct struct_hgraph  *)(hgraph.extra))->dist[p]=0; 

  int falcft3=hgraph.index[p+1]-hgraph.index[p];
  int falcft4=hgraph.index[p];
  
  for(int falcft5=0;falcft5<falcft3;falcft5++){
    int ut3=2*(falcft4+falcft5);
    int ut4=hgraph.edges[ut3].ipe;
    int ut5=hgraph.edges[ut3+1].ipe;
    int t=ut4;
    relaxEdge(ut4,hgraph,p,1,pred);
  }

  Galois::for_each_local(pred,Process1(),Galois::wl<OBIM>());

  double   rt2 =rtclock();
  printf("TIME =%f\n",(rt2-rt1)*1000);
  int   maxdist =0;

  for (int   i =0;i<hgraph.npoints;i++) {
    if( ((struct struct_hgraph  *)(hgraph.extra))->dist[i]>maxdist  )
      maxdist=((struct struct_hgraph  *)(hgraph.extra))->dist[i]; 
  }

  printf("MAX DIST=%d \n",maxdist);
}
