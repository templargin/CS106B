#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "vector.h"

using namespace std;

int maxElementIndex(Vector<int> v)
{
    if (v.size() == 1) return 0;

    int max = v[0];
    int num = 0;
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] > max)
        {
            max = v[i];
            num = i;
        }
    }
    return num;
}

Vector<int> newVec(Vector<int> v, int index)
{
    return v.subList(0, index) + v.subList(index+1, v.size()-index-1);
}

int CutStock(Vector<int> & requests, int stockLength, int count)
{
    if (requests.size() == 0)
    {
        if (stockLength <= 0) return 1;
                else return 0;
    }

    Vector<int> current = newVec(requests, maxElementIndex(requests));

    if (requests[maxElementIndex(requests)] < stockLength)
       return CutStock(current, stockLength - requests[maxElementIndex(requests)], count);
    else
        return CutStock(current, stockLength, count);
}

int canMakeSum(Vector<int> &v, int n)
{

    if (v.isEmpty())
    {
        if (n <= 0) return 1;
        else return 0;
    }
    else
    {
       int sum = v.get(0);
       Vector<int> current = v.subList(1, v.size()-1);

       return canMakeSum(current, n - sum) + canMakeSum(current, n);
    }
}

int main() {


   Vector<int> requests {4, 3, 4, 8, 7, 1};
   Vector<int> r1 {8, 7, 3};
   Vector<int> check;


   cout << canMakeSum(r1, 10);

   return 0;

}



