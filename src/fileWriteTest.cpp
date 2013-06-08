#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main () {
  string line;
  fstream myfile ("example.txt");
  fstream *my_file;
  if (myfile.is_open())
  {
	my_file=&myfile;
    while ( myfile.good() )
    {
      getline (*my_file,line);
      cout << line << endl;
    }
    myfile.close();
    my_file->close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
