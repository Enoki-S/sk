#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

int main() {
  std::chrono::system_clock::time_point  startall, endall;
  startall = std::chrono::system_clock::now();
  //以下4つが入力格納
  std::vector<int> nodep;
  std::vector<int> var;
  std::vector<int> zeroeda;
  std::vector<int> oneeda;
  
  std::string s;
  int nodenum=0;//node数
  //int itemnum=0;//item数
  while(std::getline(std::cin, s)) {
    std::istringstream iss(s);
    int a,b;
    std::string c, d; 
    iss >> a >> b >> c >> d;
    a = a + 2;
    nodep.push_back(a);
    var.push_back(b);
    /*if(itemnum == 0){
      itemnum = b;
    }
    */
    int cc;
    int dd;
    if(c == "T"){
      cc = 1;
    }else if(c == "B"){
      cc = 0;
    }else{
      cc = std::stoi(c); // 3
      cc = cc + 2;
    }
    if(d == "T"){
      dd = 1;
    }else{
      dd = std::stoi(d);
      dd = dd + 2;
    }
    cc = cc << 1;
    //std::cout << cc << std::endl;
    dd = dd << 1;
    zeroeda.push_back(cc);
    oneeda.push_back(dd);
    nodenum++;
  }
  int cha1;
  int cha2;
  //nodep_back()と同じ値があるならそれをnodenumber*2+1した値にする
  for(int i = 0;i < nodenum ;i++){
    cha1 = nodep.at(i);
    cha1 = cha1 << 1;
    cha2 = (nodenum + 1 - i);
    nodep.at(i) = cha2;
    for(int j = i + 1;j < nodenum;j++){
      if(cha1 == oneeda.at(j)){
	oneeda.at(j) = (cha2 << 1)+ 1;
      }
      if(cha1 == zeroeda.at(j)){
	zeroeda.at(j) = (cha2 << 1) + 1;
      }
    }
  }
  const char *fileName = "knuthzddoutput.dlx";

    std::ofstream ofs(fileName);
    if (!ofs)
    {
        std::cout << "ファイルが開けませんでした。" << std::endl;
        std::cin.get();
        return 0;
    }
    //int item = itemnum;
    int nowitem;
    int nodenumber = 2;
    int zero;
    int one;
    while(var.begin() != var.end()){
      ofs <<"#"<< var.back() << std::endl;
      nowitem = var.back();
      while(nowitem == var.back()){
	var.pop_back();
	zero  = (zeroeda.back() >> 1);
	one = (oneeda.back() >> 1);
	ofs << nodep.back() << ":" << zero << "," << one << std::endl;
	nodep.pop_back();
	zeroeda.pop_back();
	oneeda.pop_back();
	nodenumber = nodenumber + 1;
      }
    }
    std::cout << fileName << "に書き込みました。" << std::endl;

    std::cin.get();
    endall = std::chrono::system_clock::now();
  printf("alltime: %llu msecs\n",std::chrono::duration_cast<std::chrono::milliseconds>(endall - startall).count());
}
