// PB5.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 一 1月  2 19:31:36 2017 (+0800)
// Last-Updated: 二 1月  3 14:08:45 2017 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 43
// URL: http://wuhongyi.cn 

#include "PB5.hh"

#include "TString.h"

#include <iostream>
#include <ctime>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PB5::PB5()
{


}

PB5::~PB5()
{


}

int PB5::GetTriggerMode()
{
  if(buffstring.find("Trigger Source is Internal Clock",0) != std::string::npos) return 0;
  if(buffstring.find("Trigger Source is External Trigger",0) != std::string::npos) return 1;
  if(buffstring.find("Trigger Source is External Gate",0) != std::string::npos) return 2;
  if(buffstring.find("Trigger Source is 1 Pulse Key",0) != std::string::npos) return 3;
}

int PB5::GetAttenuation()
{
  pos0 = buffstring.find("Attenuation :");
  pos1 = buffstring.find('\n',pos0+13);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;

  TString tempstring(tempchar);
  Attenuation = tempstring.Atoi();
  return Attenuation;
}

double PB5::GetThreshold()
{
  pos0 = buffstring.find("Trigger Threshold is");
  pos1 = buffstring.find('\n',pos0+20);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-20,pos0+20);
  // std::cout<<"Copy: "<<tempchar<<std::endl;

  TString tempstring(tempchar);
  Threshold = tempstring.Atof();
  return Threshold;
}

double PB5::GetAmplitude()
{
  pos0 = buffstring.find("Amplitude   :");
  pos1 = buffstring.find("Volts",pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  Amplitude = tempstring.Atof();
  return Amplitude;
}

double PB5::GetRepRate()
{
  pos0 = buffstring.find("Rep Rate    :");
  pos1 = buffstring.find("hZ",pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  RepRate = tempstring.Atof();
  return RepRate;
}

int PB5::GetDelay()
{
  pos0 = buffstring.find("Delay       :");
  pos1 = buffstring.find("ns",pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  Delay = tempstring.Atof();
  return Delay;
}

int PB5::GetWidth()
{
  pos0 = buffstring.find("Width       :");
  if(pos0 == std::string::npos)
    {
      Width = -1;
    }
  else
    {
      pos1 = buffstring.find("ns",pos0);
      // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
      char tempchar[128];
      buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
      // std::cout<<"Copy: "<<tempchar<<std::endl;
      TString tempstring(tempchar);
      Width = tempstring.Atof();
    }

  return Width;
}


int PB5::GetRiseTime()
{
  pos0 = buffstring.find("Rise Time   :");
  if(pos0 == std::string::npos)
    {
      RiseTime = -1;
    }
  else
    {
      pos1 = buffstring.find('\n',pos0+13);

      char tempchar[128];
      buffstring.copy(tempchar,pos1-pos0-13-3,pos0+13);
      // std::cout<<"Copy: "<<tempchar<<std::endl;
      TString tempstring(tempchar);
      double tempdouble = tempstring.Atof();

      if(buffstring[pos1-3] == 'n')
	{
	  RiseTime = tempdouble;
	}
      else
	{
	  if(buffstring[pos1-3] == 'u')
	    {
	      RiseTime = tempdouble*1000;
	    }
	  else// 'm'
	    {
	      RiseTime = tempdouble*1000000;
	    }
	}
    }
  
  return RiseTime;
}


int PB5::GetFallTime()
{
  pos0 = buffstring.find("Fall Time   :");
  pos1 = buffstring.find('\n',pos0+13);

  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13-3,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  double tempdouble = tempstring.Atof();

  if(buffstring[pos1-3] == 'n')
    {
      FallTime = tempdouble;
    }
  else
    {
      if(buffstring[pos1-3] == 'u')
	{
	  FallTime = tempdouble*1000;
	}
      else// 'm'
	{
	  FallTime = tempdouble*1000000;
	}
    }

  return FallTime;
}


int PB5::GetEquivalentkeV()
{
  pos0 = buffstring.find("Equivalent keV is :");
  pos1 = buffstring.find('\n',pos0+19);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-19,pos0+19);
  // std::cout<<"Copy: "<<tempchar<<std::endl;

  TString tempstring(tempchar);
  EquivalentkeV = tempstring.Atof();
  return EquivalentkeV;
}

double PB5::GetRampStartV()
{
  pos0 = buffstring.find("Ramp Start at");
  pos1 = buffstring.find("Volts",pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  RampStartV = tempstring.Atof();
  return RampStartV;
  
}

double PB5::GetRampStopV()
{
  pos0 = buffstring.find("Ramp Stop  at");
  pos1 = buffstring.find("Volts",pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  RampStopV = tempstring.Atof();
  return RampStopV;
}

double PB5::GetRampStartkeV()
{
  pos0 = buffstring.rfind("Ramp Start at");
  pos1 = buffstring.find("keV",pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  RampStartkeV = tempstring.Atof();
  return RampStartkeV;
}

double PB5::GetRampStopkeV()
{
  pos0 = buffstring.rfind("Ramp Stop  at");
  pos1 = buffstring.find("keV",pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  RampStartkeV = tempstring.Atof();
  return RampStartkeV;
}

int PB5::GetRampTime()
{
  pos0 = buffstring.rfind("Ramp Time  is");
  pos1 = buffstring.find("seconds",pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-13,pos0+13);
  // std::cout<<"Copy: "<<tempchar<<std::endl;
  TString tempstring(tempchar);
  RampTime = tempstring.Atoi();
  
  return RampTime;
}

int PB5::GetRampCycles()
{
  pos0 = buffstring.find("# Ramp Cycles is");
  pos1 = buffstring.find('\n',pos0);
  // std::cout<<"Pos: "<<pos0<<"  "<<pos1<<std::endl;
  char tempchar[128];
  buffstring.copy(tempchar,pos1-pos0-16,pos0+16);
  // std::cout<<"Copy: "<<tempchar<<std::endl;

  TString tempstring(tempchar);
  RampCycles = tempstring.Atoi();
  return RampCycles;
}

int PB5::GetPulseOn()
{
  if(buffstring.find("Pulse is ON",0) != std::string::npos)
    PulseOn = 1;
  else
    PulseOn = 0;
  
  return PulseOn;
}

int PB5::GetPolarityPositive()
{
  if(buffstring.find("Negative",0) == std::string::npos)
    PolarityPositive = 1;
  else
    PolarityPositive = 0;
  
    return PolarityPositive;
}

int PB5::GetDisplaykeV()
{
  if(buffstring.find("Display is  : Volts",0) == std::string::npos)
    DisplaykeV = 1;
  else
    DisplaykeV = 0;
  
  return DisplaykeV;
}

int PB5::GetClampBaseline()
{
  if(buffstring.find("Clamped",0) != std::string::npos)
    ClampBaseline = 1;
  else
    ClampBaseline = 0;
  
  return ClampBaseline;
}

int PB5::GetTailPulse()
{
  if(buffstring.find("Tail",0) != std::string::npos)
    TailPulse = 1;
  else
    TailPulse = 0;

  return TailPulse;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PB5::Print()
{
  switch(GetTriggerMode())
    {
    case 0:
      std::cout<<"Find Trigger Source is Internal Clock "<<std::endl;
      break;

    case 1:
      std::cout<<"Find Trigger Source is External Trigger "<<std::endl;
      break;

    case 2:
      std::cout<<"Find Trigger Source is External Gate "<<std::endl;
      break;

    case 3:
      std::cout<<"Find Trigger Source is 1 Pulse Key "<<std::endl;
      break;

    default:
      break;
    }

  std::cout<<"Attenuation: "<<GetAttenuation()<<std::endl;
  std::cout<<"Pulse is ON: "<<GetPulseOn()<<std::endl;
  std::cout<<"Find Pos/Neg: "<<GetPolarityPositive()<<std::endl;
  std::cout<<"Find Clamped: "<<GetClampBaseline()<<std::endl;
  std::cout<<"Find Tail: "<<GetTailPulse()<<std::endl;
  
  std::cout<<"Find Threshold: "<<GetThreshold()<<std::endl;
  std::cout<<"Find Amplitude: "<<GetAmplitude()<<std::endl;
  std::cout<<"Find RepRate: "<<GetRepRate()<<std::endl;
  std::cout<<"Find Delay: "<<GetDelay()<<std::endl;
  std::cout<<"Find FallTime: "<<GetFallTime()<<std::endl;
  // std::cout<<"Find : "<<<<std::endl;
  if(TailPulse == 0)
    {
      std::cout<<"Find Width: "<<GetWidth()<<std::endl;
      std::cout<<"Find RiseTime: "<<GetRiseTime()<<std::endl;
    }

  std::cout<<"Find Display is  : Volts : "<<GetDisplaykeV()<<std::endl;
  std::cout<<"Find EquivalentkeV: "<<GetEquivalentkeV()<<std::endl;
  std::cout<<"Find RampStartV: "<<GetRampStartV()<<std::endl;
  std::cout<<"Find RampStopV: "<<GetRampStopV()<<std::endl;
  std::cout<<"Find RampStartkeV: "<<GetRampStartkeV()<<std::endl;
  std::cout<<"Find RampStopkeV: "<<GetRampStopkeV()<<std::endl;
  std::cout<<"Find RampTime: "<<GetRampTime()<<std::endl;
  std::cout<<"Find RampCycles: "<<GetRampCycles()<<std::endl;
 
  
  
  // 
  // std::cout<<buffstring[pos]<<" "<<buffstring[pos+1]<<" "<<buffstring[pos+2]<<" "<<buffstring[pos+3]<<" "<<buffstring[pos+4]<<" "<<buffstring[pos+5]<<" "<<buffstring[pos+6]<<" "<<buffstring[pos+7]<<" "<<buffstring[pos+8]<<" "<<buffstring[pos+9]<<" "<<buffstring[pos+10]<<" "<<std::endl;
  // 
  // 



  // if(pos == std::string::npos) std::cout<<"PPPPP"<<std::endl;
}

// 
// PB5.cc ends here
