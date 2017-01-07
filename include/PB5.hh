// PB5.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 一 1月  2 19:31:19 2017 (+0800)
// Last-Updated: 二 1月  3 14:04:16 2017 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 14
// URL: http://wuhongyi.cn 

#ifndef _PB5_H_
#define _PB5_H_

#include <sstream>
#include <cstring>
#include <string>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PB5
{
public:
  PB5();
  virtual ~PB5();

  void SetBufferData(std::string s) {buffstring = s;}

  void Print();

  int GetPulseOn();//
  int GetTriggerMode();//
  double GetThreshold();//
  double GetAmplitude();//
  double GetRepRate();//
  int GetWidth();//Flat
  int GetDelay();//
  int GetRiseTime();//Flat unit ns us ms
  int GetFallTime();//==unit
  int GetTailPulse();//
  int GetPolarityPositive();//
  int GetAttenuation();//
  int GetClampBaseline();//
  
  int GetDisplaykeV();//
  int GetEquivalentkeV();//
  double GetRampStartV();
  double GetRampStopV();
  double GetRampStartkeV();
  double GetRampStopkeV();
  int GetRampTime();
  int GetRampCycles();


private:
  std::string buffstring;
  std::string::size_type pos0,pos1;

  int PulseOn;//0-off,1-on
  int TriggerMode;// 0-internal,1-external,2-gated,3-onepulse
  double Threshold;//0.0-3.5
  double Amplitude;//0.0-10.0
  double RepRate;//2.5-500000 Hz
  int Width;//250-1000000 ns
  int Delay;//250-10000000 ns
  int RiseTime;//50,100,200,500,1000,2000,5000,10000
  int FallTime;//500,1000,2000,5000,10000,20000,50000,100000,200000,500000,1000000
  int TailPulse;// 0-Flat,1-Tail
  int PolarityPositive;// 0-Neg,1-Pos
  int Attenuation;// 0,2,5,10,20,50,100,200,500,1000
  int DisplaykeV;// 0-Volts,1-keV
  int EquivalentkeV;//100-9999
  int ClampBaseline;// 0-noclamp 1-clamp

  double RampStartV,RampStopV;//0.0-10.0
  double RampStartkeV,RampStopkeV;//100.0-9999
  int RampTime;//30-900s
  int RampCycles;//1-100
};

#endif /* _PB5_H_ */
// 
// PB5.hh ends here
