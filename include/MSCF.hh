// MSCF.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 1月  7 13:08:27 2017 (+0800)
// Last-Updated: 六 1月  7 14:37:16 2017 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 6
// URL: http://wuhongyi.cn 

#ifndef _MSCF_H_
#define _MSCF_H_

#include <sstream>
#include <cstring>
#include <string>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MSCF
{
public:
  MSCF();
  virtual ~MSCF();

  void SetBufferData(std::string s) {buffstring = s;}

  void Print();

  void GetGains(int *g);//
  void GetThreshold(int *th);//
  void GetPZ(int *pz);//
  void GetShts(int *st);//
  void GetMult(int *m);
  int GetMonitor();
  int GetSingleCommonMode();
  bool GetRCONOFF();
  int GetBLRThresh();
  bool GetBLRActive();
  int GetCoincidenceTime();
  
  
private:
  std::string buffstring;
  std::string::size_type pos0,pos1;

  int Gains[5];
  int Threshs[17];
  int PZ[17];
  int Shts[5];
  int Mult[2];
  int Monitor;
  int SingleCommonMode;// 0-single 1-common
  bool RCONOFF;
  int BLRthresh;
  bool BLRactive;
  int CoincidenceTime;
};

#endif /* _MSCF_H_ */
// 
// MSCF.hh ends here
