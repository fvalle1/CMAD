#include <iostream>
#include "AnalysisManager.h"

void test() {
  std::cout << "Hello, Compass!" << std::endl;

  auto cx = new TCanvas ("cx", "example plot",0, 0, 640,480);
  auto manager =  AnalysisManager();
  cx->cd();
  manager[4]->Draw();
  manager(4);

  return;
}
