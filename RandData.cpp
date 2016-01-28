/* John Alexander
 * 8327934
 * CS130B
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include "Util.h"

using namespace std;

int main(int argc, char ** argv){
  cout.precision(7);
  if(argc != 2){
    cout << "Please indicate how many random points to generate." << endl;
    return 1;
  }

  double min = -10000;
  double max = 10000;

  srand(time(NULL));
  int numPoints = atoi(argv[1]);
  vector<Tuple<double, double>> points;
  
  for(int i = 0; i < numPoints; i++){
    double x = min + (max - min) * ((double)rand()) / RAND_MAX;
    double y = min + (max - min) * ((double)rand()) / RAND_MAX;
    points.push_back(Tuple<double, double>(x, y));
  }

  for(vector<Tuple<double, double>>::iterator iter = points.begin();
      iter != points.end();
      iter++){
    cout << fixed << iter->x << " " << setprecision(7) << iter->y << endl;
  }
  
  return 0;
}
