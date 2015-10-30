#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
  freopen ("myfile.txt","w",stdout);
  
  
  for (int i=0; i<20; i++)
  {
    std::stringstream tmp_ss;
    tmp_ss << "Esta es la linea " << i;
    cout << tmp_ss.str() << endl;
  }
  fclose (stdout);
  return 0;
  
}

//Taken from: http://stackoverflow.com/questions/574543/writing-all-program-output-to-a-txt-file-in-c



/* Best Solution
 * If you want all output in a text file you don't need to code anything extra. from the command line:
 * program > output.txt
 */