#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main () {
  ofstream file2;
  file2.open("/home/jarvis/example.txt", std::ios_base::app);
  if(!file2)
{ 
printf("error");
}
  file2<<"hellos23"<<endl;
  file2.close();

 

  return (0);
}
