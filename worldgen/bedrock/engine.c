#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "generator.h"
#include "finders.h"
#include "util.h"
static Generator gen; static SurfaceNoise end_noise; static uint64_t seed; static int mcver, dimension;
static Pos village_strongholds[3];static int strongholds_ready;
void engine_init(int mc, uint32_t lo, uint32_t hi, int dim){mcver=mc;seed=((uint64_t)hi<<32)|lo;dimension=dim;setupGenerator(&gen,mc,0);applySeed(&gen,dim,seed);strongholds_ready=0;if(dim==DIM_END)initSurfaceNoise(&end_noise,DIM_END,seed);}
int* engine_biomes(int x,int z,int w,int h,int scale){Range r={scale,x,z,w,h,(dimension==0?320:63)/(scale==1?1:4),1};int *p=allocCache(&gen,r);if(!p)return 0;if(genBiomes(&gen,p,r)){free(p);return 0;}return p;}
int engine_biome_at(int x,int z){return getBiomeAt(&gen,1,x,dimension==0?320:63,z);}
const char *engine_biome_name(int id){return biome2str(mcver,id);}
static int adapt(int type){switch(type){case 5:return Village;case 100:return Stronghold;case 9:return Mansion;case 10:return Outpost;case 24:return Trial_Chambers;case 13:return Ancient_City;case 18:return Fortress;case 19:return Bastion;case 20:return End_City;case 21:return End_Gateway;default:return -1;}}
int engine_structures(int type,int minx,int minz,int maxx,int maxz,int *out,int cap){
 type=adapt(type);StructureConfig cfg;if(type<0||!getStructureConfig(type,mcver,&cfg)||cfg.dim!=dimension)return 0;int size=cfg.regionSize*16,n=0;
 int x0=(int)floor((double)minx/size)-1,x1=(int)floor((double)maxx/size)+1,z0=(int)floor((double)minz/size)-1,z1=(int)floor((double)maxz/size)+1;
 for(int z=z0;z<=z1;z++)for(int x=x0;x<=x1;x++){Pos p;if(!getStructurePos(type,mcver,seed,x,z,&p))continue;if(p.x<minx||p.x>maxx||p.z<minz||p.z>maxz)continue;if(!isViableStructurePos(type,&gen,p.x,p.z,0))continue;if(type==End_City&&!isViableEndCityTerrain(&gen,&end_noise,p.x,p.z))continue;if(n>=cap)return n;out[n*2]=p.x;out[n*2+1]=p.z;n++;}
 if(type==Stronghold&&dimension==DIM_OVERWORLD){if(!strongholds_ready){StrongholdIter it={0};for(int i=0;i<3;i++){nextVillageStronghold(&it,&gen);village_strongholds[i]=it.pos;}strongholds_ready=1;}for(int i=0;i<3&&n<cap;i++){Pos p=village_strongholds[i];if(p.x>=minx&&p.x<=maxx&&p.z>=minz&&p.z<=maxz){out[2*n]=p.x;out[2*n+1]=p.z;n++;}}}
 return n;
}
void engine_spawn(int*out){Pos p=estimateSpawn(&gen,0);out[0]=p.x;out[1]=p.z;}
int engine_slime(int x,int z){return isSlimeChunk(x,z);}
void *engine_alloc(int n){return malloc(n);}void engine_free(void*p){free(p);}
