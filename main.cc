// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 1月  1 20:04:15 2017 (+0800)
// Last-Updated: 日 1月  1 20:34:44 2017 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn 

#include "MainFrame.hh"

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char **argv)
{
  TRint *theApp = new TRint("Rint", &argc, argv);

  MainFrame mainWindow(gClient->GetRoot());

  theApp->Run();

  return 0;
}

// 
// main.cc ends here
