#include <stdlib.h>
#include <iostream>
#include <chrono>
#include "ZBDD.h"
#include "SBDD_helper.h"

struct header{
  int id;
  int right;
  int left;
};

int zddpre1(std::vector<header>*v,ZBDD*g,int*itemnum,int*flag){
  for(int i = (*v)[0].right;i != 0;i = (*v)[i].right){
    ZBDD g1 = (*g).OffSet(i);
    for(int j = (*v)[0].right;j != 0;j = (*v)[j].right){
      if(i != j){
	if(g1.OnSet(j)==0){//不要なアイテム発見
	  //std::cout <<"上" << i << "," << j << std::endl;//iは不要
	  *flag = 1;
	  ZBDD g2 = (*g).OnSet(j);
	  *g = g2.OnSet0(i)+g1;
	  (*v)[(*v)[i].left].right = (*v)[i].right;//アイテム集合から削除
	  (*v)[(*v)[i].right].left = (*v)[i].left;
	  *itemnum = *itemnum - 1;//アイテム数減少
	  //解なし判定
	  for(int m = (*v)[0].right;m != 0;m = (*v)[m].right){
	    if((*g).OnSet(m)==0){
	      return 1;//解なし
	    }
	  }
	  break;//継続
	}
      }
    }
  }
  return 0;
}

int zddpre(std::vector<header>*v,ZBDD*g,int*itemnum){
  int flag = 1;
  while(flag){
    flag = 0;
    if(zddpre1(v,g,itemnum,&flag)==1){
      return 1;
    }
  }
  return 0;
}

int main(int argc, char** argv)
{
  std::chrono::system_clock::time_point  startall, endall;
  startall = std::chrono::system_clock::now();
  register int i, j;

  std::ifstream ifs("knuthzddoutput.dlx");
  ZBDD z = sbddh::constructZBDDFromFileKnuth(ifs, false);
  int itemnum = z.Top();//item数
  int nodenum = z.Size();
  int elementnum = z.Card();
  int prinumcount = 0;

  std::cout << "start: element " << elementnum << " item " << itemnum << " node " << nodenum << std::endl;
  std::vector<header> v;

  header headzero = {0,1,itemnum};
  v.push_back(headzero);
  for(int i = 1;i < itemnum; i++){
    header headers = {i,i+1,i-1};
    v.push_back(headers);
  };
  header headlast = {itemnum,0,itemnum - 1};
  v.push_back(headlast);

  std::chrono::system_clock::time_point  startpre, endpre;
  startpre = std::chrono::system_clock::now();
  if(zddpre(&v,&z,&itemnum)==1){
    endpre = std::chrono::system_clock::now();
    printf("pretime: %llu msecs\n",std::chrono::duration_cast<std::chrono::milliseconds>(endpre - startpre).count());
    std::cout << "B" << std::endl;
    nodenum = z.Size();
    elementnum = z.Card();
    std::cout << "Bend: element " << elementnum << " item " << itemnum << " node " << nodenum << std::endl;
    endall = std::chrono::system_clock::now();
    printf("alltime: %llu msecs\n",std::chrono::duration_cast<std::chrono::milliseconds>(endall - startall).count());
    return 0;
  }
  endpre = std::chrono::system_clock::now();
  for(i = 1,j = last_itm - 1 ; i != j && i < j; i = i + 1, j = j - 1){
    z = z.Swap(i,j);
  }
  sbddh::ElementIteratorHolder eih(z);
  sbddh::ElementIterator itor = eih.begin();
  ////sbddh::writeZBDDToFileD3x(stdout, zdd, false);
  nodenum = z.Size();
  elementnum = z.Card();
  std::cout << "end: element " << elementnum << " item " << itemnum << " node " << nodenum << std::endl;
  sbddh::writeZBDDToFileD3x(stdout, z, false);//4pair putput
  endall = std::chrono::system_clock::now();
  printf("pretime: %llu msecs\n",std::chrono::duration_cast<std::chrono::milliseconds>(endpre - startpre).count());
  printf("alltime: %llu msecs\n",std::chrono::duration_cast<std::chrono::milliseconds>(endall - startall).count());
  return 0;
}
