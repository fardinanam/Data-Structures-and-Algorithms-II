#include<bits/stdc++.h>
#include "binomialheap.h"
using namespace std;

int main()
{
    MaxBinomialHeap<int> h;

    while(1)
    {
        string s;

        cin >> s;


        if(s == "INS")
        {
            int key;
            cin >> key;
            h.insert(key);
        }
        else if(s == "INC")
        {
            int prevKey, newKey;
            cin >> prevKey >> newKey;
            h.increaseKey(prevKey, newKey);
        }
        else if(s == "FIN")
        {
            cout << "FindMax returned " << h.findMax()->getKey() << endl;
        }
        else if(s == "EXT")
        {
            cout << "ExtractMax returned " << h.extractMax()->getKey() << endl;
        }
        else if(s == "PRI")
        {
            h.print();
        }
        else if(s == "EXIT")
        {
            break;
        }
    }
}
