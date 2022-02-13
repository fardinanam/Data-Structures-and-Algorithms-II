#include<bits/stdc++.h>

using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;

    if (n <= 3)
        return true;

    if (n%2 == 0 || n%3 == 0)
        return false;

    for (int i=5; i*i<=n; i=i+6)
    {
        if (n%i == 0 || n%(i+2) == 0)
           return false;
    }

    return true;
}

int nextPrime(int N)
{
    if (N <= 1)
        return 2;

    bool found = false;

    while (!found) {
        if (isPrime(N))
            found = true;
        N++;
    }

    return --N;
}

string generateWord(int len)
{
    string word;

    for(int i = 0; i < len; i++)
    {
        char c = 'a' + rand() % 26;
        word.push_back(c);
    }

    return word;
}

class HashTable
{
protected:
    int m;
    int lastValue;
    int numberOfCollisions;
    int numberOfProbes;

public:
    HashTable()
    {
        this->lastValue = 0;
        this->numberOfCollisions = 0;
        this->numberOfProbes = 0;
    }
    HashTable(int N) : HashTable()
    {
        this->m = nextPrime(N);
    }

    int hash1(string key)
    {
        int hashCode = 0, p = 1;
        int len = key.length();

        for(int i = 0; i < len; i++)
        {
            hashCode = (hashCode + (key[i] - 'a' + 1) * p) % m;
            p = (p * 31) % m;
        }

        return hashCode;
    }

    int hash2(string key)
    {
        int len = key.length();

        int hashCode = 7;
        for (int i = 0; i < len; i++) {
            hashCode = (hashCode*31 + key[i]) % m;
        }

        return hashCode;
    }

    int auxHash(string key)
    {
        int hashCode = 0;
        int len = key.length();
        int auxM = m - 1;

        for(int i = 0; i < len; i++)
        {
            hashCode = 1 + (hashCode + key[i]) % auxM;
        }

        return hashCode;
    }

    int getNumberOfCollisions()
    {
        return numberOfCollisions;
    }

    int getNumberOfProbes()
    {
        return numberOfProbes;
    }

    void resetNumberOfProbes()
    {
        numberOfProbes = 0;
    }

    virtual void insertKey(string key) = 0;
    virtual int searchKey(string key) = 0;
    virtual void deleteKey(string key) = 0;
};

class SeparateChainingHashTable : public HashTable
{
protected:
    vector<pair<string, int> > **hashTable;
public:
    SeparateChainingHashTable(int N) : HashTable(N)
    {
        hashTable = new vector<pair<string, int> >*[m];
        for(int i = 0; i < m; i++)
        {
            hashTable[i] = NULL;
        }
    }

    virtual void insertKey(string key)
    {
        int idx = hash1(key);
//        cout << "in sc insertKey for " << key;
        if(hashTable[idx] == NULL)
        {
//            cout << " null found\n";
            hashTable[idx] = new vector<pair<string, int> >();
        }

        else
            numberOfCollisions++;

        int len = hashTable[idx]->size();

        for(int i = 0; i < len; i++)
        {
            if(hashTable[idx]->at(i).first == key)
                return;
        }


        hashTable[idx]->push_back(make_pair(key, ++lastValue));
    }

    virtual int searchKey(string key)
    {
        int idx = hash1(key);
        numberOfProbes++;
        int len = 0;

        if(hashTable[idx] != NULL)
            len = hashTable[idx]->size();

        for(int i = 0; i < len; i++)
        {
            if(hashTable[idx]->at(i).first == key)
                return idx;
            numberOfProbes++;
        }


        return -1;
    }

    virtual void deleteKey(string key)
    {
        int idx = hash1(key);

        if(hashTable[idx] == NULL)
            return;

        int len = hashTable[idx]->size();

        for(auto it = hashTable[idx]->begin(); it != hashTable[idx]->end(); ++it)
        {
            if(it->first == key)
                hashTable[idx]->erase(it);
        }

        if(hashTable[idx]->size() == 0)
        {
            delete hashTable[idx];
            hashTable[idx] = NULL;
        }
    }

    ~SeparateChainingHashTable()
    {
        for(int i = 0; i < m; i++)
            delete hashTable[i];

        delete[] hashTable;
    }
};

class SeparateChainingHashTable2 : public SeparateChainingHashTable
{
public:
    SeparateChainingHashTable2(int N) : SeparateChainingHashTable(N)
    {

    }

    void insertKey(string key)
    {
        int idx = hash2(key);
        if(hashTable[idx] == NULL)
        {
            hashTable[idx] = new vector<pair<string, int> >();
        }

        else
            numberOfCollisions++;

        int len = hashTable[idx]->size();

        for(int i = 0; i < len; i++)
        {
            if(hashTable[idx]->at(i).first == key)
                return;
        }


        hashTable[idx]->push_back(make_pair(key, ++lastValue));
    }

    int searchKey(string key)
    {
        int idx = hash2(key);
        numberOfProbes++;
        int len = 0;

        if(hashTable[idx] != NULL)
            len = hashTable[idx]->size();

        for(int i = 0; i < len; i++)
        {
            if(hashTable[idx]->at(i).first == key)
                return idx;
            numberOfProbes++;
        }


        return -1;
    }

    void deleteKey(string key)
    {
        int idx = hash2(key);

        if(hashTable[idx] == NULL)
            return;

        int len = hashTable[idx]->size();

        for(auto it = hashTable[idx]->begin(); it != hashTable[idx]->end(); ++it)
        {
            if(it->first == key)
                hashTable[idx]->erase(it);
        }

        if(hashTable[idx]->size() == 0)
        {
            delete hashTable[idx];
            hashTable[idx] = NULL;
        }
    }
};

class DoubleHashTable : public HashTable
{
protected:
    pair<string, int> **hashTable;
public:
    DoubleHashTable(int N) : HashTable(N)
    {
        hashTable = new pair<string, int>*[m];
        for(int i = 0; i < m; i++)
        {
            hashTable[i] = NULL;
        }
    }

    virtual int doubleHash(string key, int i)
    {
        return (hash1(key) + i * auxHash(key)) % m;
    }

    void insertKey(string key)
    {
        int i = 0;
        int idx = doubleHash(key, i++);

        while(hashTable[idx] != NULL && i < m)
        {
            numberOfCollisions++;
            if(hashTable[idx]->first == key)
                return;

            idx = doubleHash(key, i++);
        }

        if(hashTable[idx] == NULL)
        {
            hashTable[idx] = new pair<string, int>(key, ++lastValue);
        }
    }

    int searchKey(string key)
    {
        int i = 0;
        int idx = doubleHash(key, i++);
        numberOfProbes++;

        while(hashTable[idx] != NULL && i < m)
        {
            if(hashTable[idx]->first == key)
                return idx;

            numberOfProbes++;
            idx = doubleHash(key, i++);
        }

        return -1;
    }

    void deleteKey(string key)
    {
        int idx = searchKey(key);
        if(idx != -1)
        {
            delete hashTable[idx];
            hashTable[idx] = NULL;
        }
    }

    ~DoubleHashTable()
    {
        for(int i = 0; i < m; i++)
            delete hashTable[i];

        delete[] hashTable;
    }
};

class DoubleHashTable2 : public DoubleHashTable
{
public:
    DoubleHashTable2(int N) : DoubleHashTable(N)
    {

    }

    int doubleHash(string key, int i)
    {
        return (hash2(key) + i * auxHash(key)) % m;
    }
};

class CustomProbingHashTable : public HashTable
{
protected:
    pair<string, int> **hashTable;
    int c1 = 7;
    int c2 = 11;
public:
    CustomProbingHashTable(int N) : HashTable(N)
    {
        hashTable = new pair<string, int>*[m];
        for(int i = 0; i < m; i++)
        {
            hashTable[i] = NULL;
        }
    }

    virtual int customProbingHashCode(string key, int i)
    {
        return  (hash1(key) + c1 * i * auxHash(key) + c2 * i * i) % m;
    }

    void insertKey(string key)
    {
        int i = 0;
        int idx = customProbingHashCode(key, i++);

        while(hashTable[idx] != NULL && i < m)
        {
            numberOfCollisions++;
            if(hashTable[idx]->first == key)
                return;

            idx = customProbingHashCode(key, i++);
        }

        if(hashTable[idx] == NULL)
        {
            hashTable[idx] = new pair<string, int>(key, ++lastValue);
        }
    }

    int searchKey(string key)
    {
        int i = 0;
        int idx = customProbingHashCode(key, i++);
        numberOfProbes++;

        while(hashTable[idx] != NULL && i < m)
        {
            if(hashTable[idx]->first == key)
                return idx;

            numberOfProbes++;
            idx = customProbingHashCode(key, i++);
        }

        return -1;
    }

    void deleteKey(string key)
    {
        int idx = searchKey(key);
        if(idx != -1)
        {
            delete hashTable[idx];
            hashTable[idx] = NULL;
        }
    }
};

class CustomProbingHashTable2 : public CustomProbingHashTable
{
public:
    CustomProbingHashTable2(int N) : CustomProbingHashTable(N)
    {

    }

    int customProbingHashCode(string key, int i)
    {
        return  (hash2(key) + c1 * i * auxHash(key) + c2 * i * i) % m;
    }
};

int main()
{
    srand(time(0));

    int n = 10000, lengthOfAWord = 7,  numberOfSearches = 1000;
//    cin >> n >> lengthOfAWord;

    string words[n];
    SeparateChainingHashTable2 sc3(n);
    SeparateChainingHashTable sc(n);
    SeparateChainingHashTable2 sc2(n);
    DoubleHashTable dh(n);
    DoubleHashTable2 dh2(n);
    CustomProbingHashTable cp(n);
    CustomProbingHashTable2 cp2(n);

    for(int i = 0; i < n; i++)
    {
        words[i] = generateWord(lengthOfAWord);
        sc.insertKey(words[i]);
        sc2.insertKey(words[i]);
        dh.insertKey(words[i]);
        dh2.insertKey(words[i]);
        cp.insertKey(words[i]);
        cp2.insertKey(words[i]);
    }



    cout << "\t\t\tHash1\t\t\t\t\t\tHash2\n";
    cout << "\t\t\tNo of Collisions\tAverage Probes\t\tNo of Collisions\tAverage Probes\n";
    cout << "Separate Chaining\t" << sc.getNumberOfCollisions() << "\t\t\t";

    float averageProbes = 0.0;
    for(int i = 0; i < 1000; i++)
    {
        int idx = rand() % n;

        sc.searchKey(words[idx]);
        averageProbes = averageProbes + sc.getNumberOfProbes();
        sc.resetNumberOfProbes();
    }

    cout << (averageProbes / 1000) << "\t\t\t" << sc2.getNumberOfCollisions() << "\t\t\t";

    float averageProbes2 = 0.0;
    for(int i = 0; i < 1000; i++)
    {
        int idx = rand() % n;

        sc2.searchKey(words[idx]);
        averageProbes2 = averageProbes2 + sc2.getNumberOfProbes();
        sc2.resetNumberOfProbes();
    }
    cout << (averageProbes2 / 1000) << endl;


    cout << "Double Hashing\t\t" << dh.getNumberOfCollisions() << "\t\t\t";

    float averageProbes3 = 0.0;
    for(int i = 0; i < 1000; i++)
    {
        int idx = rand() % n;

        dh.searchKey(words[idx]);
        averageProbes3 = averageProbes3 + dh.getNumberOfProbes();
        dh.resetNumberOfProbes();
    }
    cout << (averageProbes3 / 1000) << "\t\t\t" << dh2.getNumberOfCollisions() << "\t\t\t";

    float averageProbes4 = 0.0;
    for(int i = 0; i < 1000; i++)
    {
        int idx = rand() % n;

        dh2.searchKey(words[idx]);
        averageProbes4 = averageProbes4 + dh2.getNumberOfProbes();
        dh2.resetNumberOfProbes();
    }
    cout << (averageProbes4 / 1000) << endl;


    cout << "Custom Probing\t\t" << cp.getNumberOfCollisions() << "\t\t\t";

    float averageProbes5 = 0.0;
    for(int i = 0; i < 1000; i++)
    {
        int idx = rand() % n;

        cp.searchKey(words[idx]);
        averageProbes5 = averageProbes5 + cp.getNumberOfProbes();
        cp.resetNumberOfProbes();
    }
    cout << (averageProbes5 / 1000) << "\t\t\t" << cp2.getNumberOfCollisions() << "\t\t\t";

    float averageProbes6 = 0.0;
    for(int i = 0; i < 1000; i++)
    {
        int idx = rand() % n;

        cp2.searchKey(words[idx]);
        averageProbes6 = averageProbes6 + cp2.getNumberOfProbes();
        cp2.resetNumberOfProbes();
    }
    cout << (averageProbes6 / 1000) << endl;
}
