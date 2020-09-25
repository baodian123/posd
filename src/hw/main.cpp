#include "terminal.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
      std::ifstream ifile(argv[1]);
      if(!ifile) return -1;
      std::string content((std::istreambuf_iterator<char>(ifile)), (std::istreambuf_iterator<char>()));
      ifile.close();

      string compose_string = content + " " + (string)argv[3] + " " +(string)argv[4];
      Terminal* terminal = new Terminal(compose_string);
      string result = terminal->showResult();

      std::ofstream ofile(argv[2]);
      if(!ofile) return -1;
      ofile << result;
      ofile.close();

      return 0;
}
