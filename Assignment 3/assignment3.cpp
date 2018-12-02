#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "gwindow.h"
#include "gobjects.h"

using namespace std;

/** Print binary  */
    void printBinary(int n)
    {
        if (n < 2) cout << n;
        else
        {
            int digit = n % 2;
            int next = n / 2;
            printBinary(next);
            cout << digit;
        }
    }



/** Subset sum */
    int sum = 0;
    bool canMakeSum(Vector<int> &v, int n)
    {

       //   cout << v << " , " << "n = " << n  << ", sum = " << sum << endl;
        if (n == 0) cout << sum << endl;

        if (v.isEmpty())
        {
           // cout << "   " << (n == 0) << endl;
            return (n == 0);
        }
        else
        {
           sum = v.get(0);
           Vector<int> current = v.subList(1, v.size()-1);

           return (canMakeSum(current, n - sum)
                   || canMakeSum(current, n));
        }
    }



/** Subset sum another way */
    int canMakeSum2(Vector<int> &v, int n)
    {

      //  cout << v << " , " << "n = " << n  << ", sum = " << sum << endl;
      // if (n == 0) cout << sum << endl;

        if (v.size() == 0)
        {
            if (n == 0) return 1;
            else return 0;
        }
        else
        {
           sum = v.get(0);
           Vector<int> current = v.subList(1, v.size()-1);

           return (canMakeSum2(current, n - sum) + canMakeSum2(current, n));
        }
    }



/** 12 steps program */
    int countWays(int n)
    {
        if (n == 0) return 1;
        if (n < 2)
            return countWays(n - 1);
            else return countWays(n - 2) +
                countWays(n - 1);

    }



/** Draw Ruler */
    void drawLine(double x, double y, double w, double h, GWindow &gw)
    {
        GLine* line = new GLine(x + w/2, y, x + w/2, y+h);
        gw.add(line);
    }

    void drawRuler(double x, double y, double w, double h, GWindow &gw)
    {
        drawLine(x, y, w, h, gw);
        pause(50);
        GLine* bottom = new GLine(x, y + h, x + w, y + h);
        gw.add(bottom);
        if (h < 5)
        {
            return;
        }
        else
        {
            drawRuler(x, y + h/2, w/2, h/2, gw);
            drawRuler(x + w/2, y + h/2, w/2, h/2, gw);
        }
    }



/** Every vote counts */
    int criticalVotes(Vector<int> &v, int criticalBlock, int Alice, int Bob)
    {
        if (v.isEmpty())
        {
            if (abs(Alice - Bob) <= criticalBlock) return 1;
            else return 0;
        }
        else
        {
            int sum = v[0];
            Vector<int> current = v.subList(1, v.size()-1);
            return criticalVotes(current, criticalBlock, Alice + sum, Bob)
                    + criticalVotes(current, criticalBlock, Alice, Bob + sum);
        }
    }

    int countCriticalVotes(Vector<int> & blocks, int blockIndex)
    {
        int criticalBlock = blocks[blockIndex];
        Vector<int> current = blocks.subList(0, blockIndex) +
                blocks.subList(blockIndex + 1, blocks.size() - 1 - blockIndex);
        int Alice = 0;
        int Bob = 0;

        return criticalVotes(current, criticalBlock, Alice, Bob);

    }


int main3212() {

 //   GWindow gw(850, 600);
 //   pause(200);
 //   drawRuler(50, 100, 750, 200, gw);

      Vector<int> v {4, 2, 7, 4};

      cout << countCriticalVotes(v, 2);

    return 0;
}



