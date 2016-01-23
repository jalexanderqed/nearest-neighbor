#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <cmath>

using namespace std;

template <class S, class T>
struct Tuple{
  S x;
  T y;

  Tuple(){}

  Tuple(S a, T b){
    x = a;
    y = b;
  }
};

double calcDist(Tuple<double, double> a, Tuple<double, double> b){
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// if ret = 1, a > b
// if ret = 0, a == b
// if ret = -1, a < b
int compareDoubles(double a, double b){
  double diff = a - b;
  if(diff >= 1e-7) return 1;
  if(diff <= -1e-7) return -1;
  return 0;
}

int comparePoints(Tuple<double, double> a, Tuple<double, double> b){
  int resX = compareDoubles(a.x, b.x);
  if(resX != 0) return resX;
  return compareDoubles(a.y, b.y);
}

int comparePairs(Tuple<Tuple<double, double>, Tuple<double, double>> a,
		 Tuple<Tuple<double, double>, Tuple<double, double>> b){
  int resX = comparePoints(a.x, b.x);
  if(resX != 0) return resX;
  return comparePoints(a.y, b.y);
}

bool pointComp(Tuple<double, double> a,
	       Tuple<double, double> b){
  int res = compareDoubles(a.x, b.x);
  if(res == -1) return true;
  if(res == 1) return false;
  res = compareDoubles(a.y, b.y);
  if(res == -1) return true;
  return false;
}

bool pairComp(Tuple<Tuple<double, double>, Tuple<double, double>> a,
	      Tuple<Tuple<double, double>, Tuple<double, double>> b){
  int res = comparePoints(a.x, b.x);
  if(res == -1) return true;
  if(res == 1) return false;
  res = comparePoints(a.y, b.y);
  if(res == -1) return true;
  return false;
}

bool xComp(Tuple<double, double> a, Tuple<double, double> b){
  int res = compareDoubles(a.x, b.x);
  if(res == -1) return true;
  if(res == 1) return false;
  return a.y < b.y;
}

bool yComp(Tuple<double, double> a, Tuple<double, double> b){
  int res = compareDoubles(a.y, b.y);
  if(res == -1) return true;
  if(res == 1) return false;
  return a.x < b.x;
}

#endif
