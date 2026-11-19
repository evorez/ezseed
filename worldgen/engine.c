#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "generator.h"
#include "finders.h"
#include "util.h"
static Generator gen; static SurfaceNoise end_noise; static uint64_t seed; static int mcver, dimension;
void engine_init(int mc, uint32_t lo, uint32_t hi, int dim){mcver=mc;seed=((uint64_t)hi<<32)|lo;dimension=dim;setupGenerator(&gen,mc,0);applySeed(&gen,dim,seed);if(dim==DIM_END)initSurfaceNoise(&end_noise,DIM_END,seed);}
int* engine_biomes(int x,int z,int w,int h,int scale){ Range r={scale,x,z,w,h,(dimension==0 ? 320 : 63)/(scale==1?1:4),1};int *p=allocCache(&gen,r);if(!p)return 0;if(genBiomes(&gen,p,r)){free(p);return 0;}return p;}
int engine_biome_at(int x,int z){return getBiomeAt(&gen,1,x,dimension==0?320:63,z);}
const char *engine_biome_name(int id){return biome2str(mcver,id);}
int engine_structures(int type,int minx,int minz,int maxx,int maxz,int *out,int cap){
 StructureConfig cfg;if(!getStructureConfig(type,mcver,&cfg)||cfg.dim!=dimension)return 0;int size=cfg.regionSize*16,n=0;
 int x0=(int)floor((double)minx/size)-1,x1=(int)floor((double)maxx/size)+1,z0=(int)floor((double)minz/size)-1,z1=(int)floor((double)maxz/size)+1;
 for(int z=z0;z<=z1;z++)for(int x=x0;x<=x1;x++){Pos p;if(!getStructurePos(type,mcver,seed,x,z,&p))continue;if(p.x<minx||p.x>maxx||p.z<minz||p.z>maxz)continue;if(!isViableStructurePos(type,&gen,p.x,p.z,0))continue;if(type==End_City&&!isViableEndCityTerrain(&gen,&end_noise,p.x,p.z))continue;if(type==Mansion&&!isViableStructureTerrain(type,&gen,p.x,p.z))continue;if(n>=cap)return n;out[n*2]=p.x;out[n*2+1]=p.z;n++;}return n;
}
int engine_strongholds(int*out,int count){StrongholdIter it;initFirstStronghold(&it,mcver,seed);int n=0;while(n<count&&nextStronghold(&it,&gen)>0){out[2*n]=it.pos.x;out[2*n+1]=it.pos.z;n++;}return n;}
void engine_spawn(int*out){Pos p=getSpawn(&gen);out[0]=p.x;out[1]=p.z;}
int engine_slime(int x,int z){return isSlimeChunk(seed,x,z);}
void *engine_alloc(int n){return malloc(n);} void engine_free(void*p){free(p);}

// Seed-derived approximate Overworld surface (not exact block terrain).
int engine_height_samples(int x, int z, int step, int n, float *out, int *ids) {
    if (dimension != DIM_OVERWORLD || n < 1 || n > 128 || step < 4 || step % 4 != 0) return 1;
    for (int j = 0; j < n; ++j) for (int i = 0; i < n; ++i) {
        int xx = x + i*step, zz = z + j*step; float height;
        int rc=mapApproxHeight(&height, 0, &gen, 0, (int)floor((double)xx/4), (int)floor((double)zz/4), 1, 1);
        if (rc) return rc;
        out[j*n+i]=height; ids[j*n+i]=engine_biome_at(xx,zz);
    }
    return 0;
}
