/* John Alexander
 * 8327934
 * CS130B
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iomanip>
#include "Util.h"

using namespace std;

vector<Tuple<Tuple<double, double>, Tuple<double, double>>> OptimalFindNearestNeighbors(
											vector<Tuple<double, double>>::iterator xBegin,
											vector<Tuple<double, double>>::iterator xEnd,
											vector<Tuple<double, double>>::iterator yBegin,
											vector<Tuple<double, double>>::iterator yEnd){
  size_t size;
  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> ret;
  if((size = (xEnd - xBegin)) != (yEnd - yBegin)){
    cout << "Logic error, " << (xEnd - xBegin) << " x points and " <<
      (yEnd - yBegin) << " y points." << endl;
    return ret;
  }


  if(size == 2){
    ret.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*xBegin, *(xBegin + 1)));
    return ret;
  }
  else if(size == 3){
    double d1 = calcDist(*xBegin, *(xBegin + 1));
    double d2 = calcDist(*(xBegin + 1), *(xBegin + 2));
    double d3 = calcDist(*xBegin, *(xBegin + 2));
    double minD = min(d1, min(d2, d3));

    if(compareDoubles(minD, d1) == 0){
      ret.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*xBegin, *(xBegin + 1)));
    }
    if(compareDoubles(minD, d3) == 0){
      ret.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*xBegin, *(xBegin + 2)));
    }
    if(compareDoubles(minD, d2) == 0){
      ret.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*(xBegin + 1), *(xBegin + 2)));
    }
    
    return ret;
  }

  size_t mid = (size / 2);
  double xBound = (xBegin + mid)->x;
  double tieBound = (xBegin + mid)->y;
  vector<Tuple<double, double>> yLeft;
  vector<Tuple<double, double>> yRight;

  for(vector<Tuple<double, double>>::iterator i = yBegin; i != yEnd; i++){
    if(compareDoubles(i->x, xBound) == -1){
      yLeft.push_back(*i);
    }
    else if(compareDoubles(i->x, xBound) == 0){
      if(compareDoubles(i->y, tieBound) == -1)
	yLeft.push_back(*i);
      else
	yRight.push_back(*i);
    }
    else{
      yRight.push_back(*i);
    }
  }

  if(yRight.size() != yLeft.size()){ // Handle corner case where comparisons mis-sort y values
    yRight.clear();
    yLeft.clear();
    for(vector<Tuple<double, double>>::iterator i = xBegin; i != xBegin + mid; i++){
      yLeft.push_back(*i);
    }
    for(vector<Tuple<double, double>>::iterator i = xBegin + mid; i != xEnd; i++){
      yRight.push_back(*i);
    }

    sort(yLeft.begin(), yLeft.end(), yComp);
    sort(yRight.begin(), yRight.end(), yComp);
  }

  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> leftRes = OptimalFindNearestNeighbors(xBegin, xBegin + mid,
											   yLeft.begin(), yLeft.end());
  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> rightRes = OptimalFindNearestNeighbors(xBegin + mid, xEnd,
											    yRight.begin(), yRight.end());
  double leftDist = calcDist(leftRes[0].x, leftRes[0].y);
  double rightDist = calcDist(rightRes[0].x, rightRes[0].y);
  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> smallestVec;
  
  double minDist;
  if(compareDoubles(leftDist, rightDist) == -1){ // Left is smaller
    smallestVec = leftRes;
    minDist = leftDist;
  }
  else if(compareDoubles(leftDist, rightDist) == 1){
    smallestVec = rightRes;
    minDist = rightDist;
  }
  else{ // Distances are equal
    smallestVec = leftRes;
    minDist = min(rightDist, leftDist);
    for(vector<Tuple<Tuple<double, double>, Tuple<double, double>>>::iterator i = rightRes.begin();
	i != rightRes.end();
	i++){
      smallestVec.push_back(*i);
    }
  }

  vector<Tuple<double, double>> mustCheck;
  for(vector<Tuple<double, double>>::iterator i = yBegin;
      i != yEnd;
      i++){
    if(abs(i->x - xBound) < (minDist + 1e-6)){
      mustCheck.push_back(*i);
    }
  }
  
  for(vector<Tuple<double, double>>::iterator i = mustCheck.begin();
      i != mustCheck.end();
      i++){
    for(vector<Tuple<double, double>>::iterator j = i + 1;
	j != mustCheck.end() && (j->y < (i->y + minDist + 1e-6));
	j++){
      double cDist = calcDist(*i, *j);
      
      if(compareDoubles(cDist, minDist) == -1){ // New lowest value
	smallestVec.clear();
	smallestVec.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*i, *j));
	minDist = cDist;
      }
      else if(compareDoubles(cDist, minDist) == 0 &&
	      !(compareDoubles(i->x, j->x) == 0 && compareDoubles(i->y, j->y) == 0)){
	smallestVec.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*i, *j));
      }
    }
  }
  
  return smallestVec;
}

vector<Tuple<Tuple<double, double>, Tuple<double, double>>> BasicFindNearestNeighbors(
											vector<Tuple<double, double>>::iterator xBegin,
											vector<Tuple<double, double>>::iterator xEnd){
  size_t size;
  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> ret;
  size = xEnd - xBegin;
  
  if(size == 2){
    ret.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*xBegin, *(xBegin + 1)));
    return ret;
  }
  else if(size == 3){
    double d1 = calcDist(*xBegin, *(xBegin + 1));
    double d2 = calcDist(*(xBegin + 1), *(xBegin + 2));
    double d3 = calcDist(*xBegin, *(xBegin + 2));
    double minD = min(d1, min(d2, d3));

    if(compareDoubles(minD, d1) == 0){
      ret.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*xBegin, *(xBegin + 1)));
    }
    if(compareDoubles(minD, d3) == 0){
      ret.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*xBegin, *(xBegin + 2)));
    }
    if(compareDoubles(minD, d2) == 0){
      ret.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*(xBegin + 1), *(xBegin + 2)));
    }
    
    return ret;
  }

  size_t mid = (size / 2);
  double xBound = (xBegin + mid)->x;
  double tieBound = (xBegin + mid)->y;
  
  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> leftRes = BasicFindNearestNeighbors(xBegin, xBegin + mid);
  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> rightRes = BasicFindNearestNeighbors(xBegin + mid, xEnd);
  
  double leftDist = calcDist(leftRes[0].x, leftRes[0].y);
  double rightDist = calcDist(rightRes[0].x, rightRes[0].y);
  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> smallestVec;
  
  double minDist;
  if(compareDoubles(leftDist, rightDist) == -1){ // Left is smaller
    smallestVec = leftRes;
    minDist = leftDist;
  }
  else if(compareDoubles(leftDist, rightDist) == 1){
    smallestVec = rightRes;
    minDist = rightDist;
  }
  else{ // Distances are equal
    smallestVec = leftRes;
    minDist = min(rightDist, leftDist);
    for(vector<Tuple<Tuple<double, double>, Tuple<double, double>>>::iterator i = rightRes.begin();
	i != rightRes.end();
	i++){
      smallestVec.push_back(*i);
    }
  }

  vector<Tuple<double, double>> mustCheck;
  for(vector<Tuple<double, double>>::iterator i = xBegin;
      i != xEnd;
      i++){
    if(abs(i->x - xBound) < (minDist + 1e-6)){
      mustCheck.push_back(*i);
    }
    //if((i->x - xBound) > (minDist + 1e-6)) break;
  }

  sort(mustCheck.begin(), mustCheck.end(), yComp);
  
  for(vector<Tuple<double, double>>::iterator i = mustCheck.begin();
      i != mustCheck.end();
      i++){
    for(vector<Tuple<double, double>>::iterator j = i + 1;
	j != mustCheck.end() && (j->y < (i->y + minDist + 1e-6));
	j++){
      double cDist = calcDist(*i, *j);
      
      if(compareDoubles(cDist, minDist) == -1){ // New lowest value
	smallestVec.clear();
	smallestVec.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*i, *j));
	minDist = cDist;
      }
      else if(compareDoubles(cDist, minDist) == 0 &&
	      !(compareDoubles(i->x, j->x) == 0 && compareDoubles(i->y, j->y) == 0)){
	smallestVec.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*i, *j));
      }
    }
  }
  
  return smallestVec;
}

vector<Tuple<Tuple<double, double>, Tuple<double, double>>> BruteFindNearestNeighbors(vector<Tuple<double, double>> points){
  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> bestPoints;
  double bestSquareDist = DBL_MAX / 2.0;
  
  for(vector<Tuple<double, double>>::iterator i = points.begin();
      i != points.end();
      i++){
    for(vector<Tuple<double, double>>::iterator j = i + 1;
	j != points.end();
	j++){
      double sd = calcDist(*i, *j);
      double comp = compareDoubles(bestSquareDist, sd);
      if(comp == 1){
	bestPoints.clear();
	bestPoints.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*i, *j));
	bestSquareDist = sd;
      }
      else if(comp == 0){
	  bestPoints.push_back(Tuple<Tuple<double, double>, Tuple<double, double>>(*i, *j));
      }
    }	
  }

  return bestPoints;
}

string trim(string& str){
  if(str.length() <= 0) return str;
  if(str.length() == 1 && str.at(0) == ' ') return str.substr(0, 0);
  size_t fPos = str.find_first_not_of(' ');
  size_t lPos = str.find_last_not_of(' ');
  return str.substr(fPos, (lPos - fPos + 1));
}

int main(int argc, char ** argv){
  cout.precision(7);
  if(argc != 2){
    cout << "Please specify either 'brute', 'basic', or 'optimal'" << endl;
    return 1;
  }

  string command(argv[1]);

  string currentLine;
  vector<Tuple<double, double>> xPoints;
  vector<Tuple<double, double>> yPoints;
  
  while(!cin.eof()){
    getline(cin, currentLine);
    if(cin.eof()) break;
    
    currentLine = trim(currentLine);
    const char* cStr = currentLine.c_str();
    
    char* xEnd;
    double x = strtod(cStr, &xEnd);
    if(*xEnd != ' '){
      continue;
    }

    char* yEnd;
    double y = strtod(xEnd, &yEnd);
    if(*yEnd){
      continue;
    }

    xPoints.push_back(Tuple<double, double>(x, y));
  }

  sort(xPoints.begin(), xPoints.end(), xComp); // Necessary for removing duplicates
  for(vector<Tuple<double, double>>::iterator iter = xPoints.begin(); // This loop removes duplicates
      iter != xPoints.end() - 1;
      iter++){
    if(comparePoints(*iter, *(iter+1)) == 0){
      xPoints.erase(iter + 1);
      iter--;
    }
  }

  if(xPoints.size() <= 2){
    cout << "Insufficient number of points entered." << endl;
    return 1;
  }

  vector<Tuple<Tuple<double, double>, Tuple<double, double>>> bestPoints;

  if(command == "brute"){
    bestPoints = BruteFindNearestNeighbors(xPoints);
  }

  if(command == "basic"){
    bestPoints = BasicFindNearestNeighbors(xPoints.begin(), xPoints.end());
    if(bestPoints.size() < 1){
      cout << "Error: basic algorithm produced no output." << endl;
      return 1;
    }
  }

  for(vector<Tuple<double, double>>::iterator iter = xPoints.begin();
      iter != xPoints.end();
      iter++){
    yPoints.push_back(Tuple<double, double>(iter->x, iter->y));
  }
  sort(yPoints.begin(), yPoints.end(), yComp);
  
  if(command == "optimal"){
    bestPoints = OptimalFindNearestNeighbors(xPoints.begin(), xPoints.end(), yPoints.begin(), yPoints.end());
    if(bestPoints.size() < 1){
      cout << "Error: optimal algorithm produced no output." << endl;
      return 1;
    }
  }

  for(vector<Tuple<Tuple<double, double>, Tuple<double, double>>>::iterator iter = bestPoints.begin();
      iter != bestPoints.end();
      iter++){
    if(comparePoints(iter->x, iter->y) == 1){
      Tuple<double, double> tempX = iter->x;
      iter->x = iter->y;
      iter->y = tempX;
    }
  }
  sort(bestPoints.begin(), bestPoints.end(), pairComp);
  
  for(vector<Tuple<Tuple<double, double>, Tuple<double, double>>>::iterator iter = bestPoints.begin();
      iter != bestPoints.end() - 1;
      iter++){
    if(comparePairs(*iter, *(iter+1)) == 0){
      bestPoints.erase(iter + 1);
      iter--;
    }
  }

  cout << "closest pair distance: " << fixed << calcDist(bestPoints[0].x, bestPoints[0].y) << endl;
  for(vector<Tuple<Tuple<double, double>, Tuple<double, double>>>::iterator iter = bestPoints.begin();
      iter != bestPoints.end();
      iter++){
    cout << "(" << iter->x.x << ", " << iter->x.y <<
      ") (" << iter->y.x << ", " << iter->y.y << ")" << endl;
  }
  
  return 1;
}
