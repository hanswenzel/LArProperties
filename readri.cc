// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <utility>
#include <algorithm>
#include <vector>
#include <sstream>      // std::stringstream

using namespace std;
std::vector<std::string>& split(const std::string& s, char delim,
                                             std::vector<std::string>& elems)
{
  std::stringstream ss(s);
  std::string item;
  while(std::getline(ss, item, delim))
  {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string& s, char delim)
{
  std::vector<std::string> elems;
  return split(s, delim, elems);
}

 
  
int main () {
  const double c   = 299.792458;// speed of light in mm/ns
  string line;
  char seperator = ' '; // space  
  ifstream myfile ("rindex.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      //      cout << line << '\n';
      std::vector<std::string> y = split(line, ' ');
      cout<<y.size()<<endl;
      int dim=y.size()*0.5;
      cout <<"double  rienergy["<<dim<<"]={"<<endl;  
      unsigned int counter=0;
      for(auto & elem : y)
	{
	 
	  if ( counter % 2 == 0)
	    {
	      double energy = std::stod(elem)*1e6;
	    cout<<energy<<", ";
	    }
	  counter++;
	}
      cout <<"};"<<endl;
      cout <<"double  ri["<<dim<<"]={"<<endl;  
      counter=0;
      for(auto & elem : y)
	{
	 
	  if ( counter % 2 != 0)
	    {
	      double ri = 1/std::stod(elem);
	    cout<<ri<<", ";
	    }
	  counter++;
	}
      cout <<"};"<<endl; 
    }
    myfile.close();
  }
  
  else cout << "Unable to open file"; 

  return 0;
}
