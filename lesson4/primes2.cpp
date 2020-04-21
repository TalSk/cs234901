//
// Created by Tal Skverer on 21/04/2020.
//
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define EPS 1e-7
typedef long long LL;
bool IsPrimeSlow (LL x)
{
  if(x<=1) return false;
  if(x<=3) return true;
  if (!(x%2) || !(x%3)) return false;
  LL s=(LL)(sqrt((double)(x))+EPS);
  for(LL i=5;i<=s;i+=6)
  {
    if (!(x%i) || !(x%(i+2))) return false;
  }
  return true;
}

bool isInGivenBase(string str, int base)
{
  // Allowed bases are till 16 (Hexadecimal)
  if (base > 16)
    return false;

    // If base is below or equal to 10, then all
    // digits should be from 0 to 9.
  else if (base <= 10)
  {
    for (int i = 0; i < str.length(); i++)
      if (!(str[i] >= '0' and
            str[i] < ('0' + base)))
        return false;
  }

    // If base is below or equal to 16, then all
    // digits should be from 0 to 9 or from 'A'
  else
  {
    for (int i = 0; i < str.length(); i++)
      if (! ((str[i] >= '0' &&
              str[i] < ('0' + base)) ||
             (str[i] >= 'A' &&
              str[i] < ('A' + base - 10))
      ))
        return false;
  }
  return true;
}

int main(){
  ull T;
  while (cin >> T){
    for (int bla = 0; bla < T; ++bla) {
      string num;
      cin >> num;
      ull num_primes = 0;
      ull num_can = 0;
      ull converted;
      // Binary
      try {
        if (isInGivenBase(num, 2)){
          num_can++;
          converted = stoull(num, 0, 2);
          if (IsPrimeSlow(converted)){
            num_primes++;
          }
        }
      }
      catch (std::exception& e){
      }
      // Octal
      try {
        if (isInGivenBase(num, 8)){
          num_can++;
          converted = stoll(num, 0, 8);
          if (IsPrimeSlow(converted)){
            num_primes++;
          }
        }
      }
      catch (std::invalid_argument& e){
      }
      // Dec
      try {
        if (isInGivenBase(num, 10)){
          num_can++;
          converted = stoll(num, 0, 10);
          if (IsPrimeSlow(converted)){
            num_primes++;
          }
        }
      }
      catch (std::invalid_argument& e){
      }
      // Hex
      try {
        if (isInGivenBase(num, 16)){
          num_can++;
          converted = stoll(num, 0, 16);
          if (IsPrimeSlow(converted)){
            num_primes++;
          }
        }
      }
      catch (std::invalid_argument& e){

      }
      if (num_primes == 0){
        cout << "0/1" << endl;
        continue;
      }
      ull reduced_top, reduced_bot;
      reduced_top = num_primes / __gcd(num_primes, num_can);
      reduced_bot = num_can / __gcd(num_primes, num_can);
      cout << reduced_top << "/" << reduced_bot << endl;


    }
  }
  return 0;
}