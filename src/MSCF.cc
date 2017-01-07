// MSCF.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 1月  7 13:08:47 2017 (+0800)
// Last-Updated: 六 1月  7 14:33:50 2017 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 8
// URL: http://wuhongyi.cn 

#include "MSCF.hh"

#include "TString.h"

#include <iostream>
#include <ctime>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSCF::MSCF()
{

}

MSCF::~MSCF()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MSCF::GetGains(int *g)
{
  pos0 = buffstring.find("MSCF-16 rc settings:");
  pos1 = buffstring.find("gains:",pos0);
  pos0 = buffstring.find('\n',pos1);

  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos0-pos1-6,pos1+6);
  // std::cout<<"Copy: "<<tempchar<<std::endl;

  std::string tempstring(tempchar);
  std::stringstream s2i;//sstream cstring
  s2i.clear();//重复使用前一定要清空
  s2i<<tempstring;
  s2i>>Gains[0]>>Gains[1]>>Gains[2]>>Gains[3]>>Gains[4];
 
  g[0] = Gains[0];
  g[1] = Gains[1];
  g[2] = Gains[2];
  g[3] = Gains[3];
  g[4] = Gains[4];
}

void MSCF::GetShts(int *st)
{
  pos0 = buffstring.find("MSCF-16 rc settings:");
  pos1 = buffstring.find("shts:",pos0);
  pos0 = buffstring.find('\n',pos1);

  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos0-pos1-5,pos1+5);
  // std::cout<<"Copy: "<<tempchar<<std::endl;

  std::string tempstring(tempchar);
  std::stringstream s2i;//sstream cstring
  s2i.clear();//重复使用前一定要清空
  s2i<<tempstring;
  s2i>>Shts[0]>>Shts[1]>>Shts[2]>>Shts[3]>>Shts[4];
 
  st[0] = Shts[0];
  st[1] = Shts[1];
  st[2] = Shts[2];
  st[3] = Shts[3];
  st[4] = Shts[4];
}

void MSCF::GetThreshold(int *th)
{
  pos0 = buffstring.find("MSCF-16 rc settings:");
  pos1 = buffstring.find("threshs:",pos0);
  pos0 = buffstring.find('\n',pos1);

  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos0-pos1-8,pos1+8);
  // std::cout<<"Copy: "<<tempchar<<std::endl;

  std::string tempstring(tempchar);
  std::stringstream s2i;//sstream cstring
  s2i.clear();//重复使用前一定要清空
  s2i<<tempstring;
  for (int i = 0; i < 17; ++i)
    {
      s2i>>Threshs[i];
      th[i] = Threshs[i];
    }
}

void MSCF::GetPZ(int *pz)
{
  pos0 = buffstring.find("MSCF-16 rc settings:");
  pos1 = buffstring.find("pz:",pos0);
  pos0 = buffstring.find('\n',pos1);

  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos0-pos1-3,pos1+3);
  // std::cout<<"Copy: "<<tempchar<<std::endl;

  std::string tempstring(tempchar);
  std::stringstream s2i;//sstream cstring
  s2i.clear();//重复使用前一定要清空
  s2i<<tempstring;
  for (int i = 0; i < 17; ++i)
    {
      s2i>>PZ[i];
      pz[i] = PZ[i];
    }
}



void MSCF::Print()
{
  int gains[5];
  GetGains(gains);
  std::cout<<"Find Gains: "<<gains[0]<<" "<<gains[1]<<" "<<gains[2]<<" "<<gains[3]<<" "<<gains[4]<<std::endl;

  int shts[5];
  GetShts(shts);
  std::cout<<"Find Shts: "<<shts[0]<<" "<<shts[1]<<" "<<shts[2]<<" "<<shts[3]<<" "<<shts[4]<<std::endl;

  int threshs[17];
  GetThreshold(threshs);
  std::cout<<"Find Threshs: ";
  for (int i = 0; i < 17; ++i)
    {
      std::cout<<threshs[i]<<" ";
    }
  std::cout<<std::endl;

  int pz[17];
  GetPZ(pz);
  std::cout<<"Find PZ: ";
  for (int i = 0; i < 17; ++i)
    {
      std::cout<<pz[i]<<" ";
    }
  std::cout<<std::endl;


  
}

// 
// MSCF.cc ends here
