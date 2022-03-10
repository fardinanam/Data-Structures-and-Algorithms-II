#include<iterator>
#include<list>
#include "node.h"

template <typename T>
class MaxBinomialHeap
{
private:
    std::list<Node<T>*> treeRoots;

public:
    MaxBinomialHeap()
    {
    }

    void heapifyBinomialTrees()
    {
        if (treeRoots.size() <= 1)
            return;

        auto it1 = treeRoots.begin(), it2 = treeRoots.begin(), it3 = treeRoots.begin();

        if (treeRoots.size() == 2)
        {
            it2++;
            it3 = treeRoots.end();
        }
        else
        {
            it2++;
            it3=it2;
            it3++;
        }
        while (it1 != treeRoots.end())
        {
            if (it2 == treeRoots.end())
                it1++;

            else if ((*it1)->getDegree() < (*it2)->getDegree())
            {
                it1++;
                it2++;
                if(it3 != treeRoots.end())
                    it3++;
            }

            else if (it3 != treeRoots.end() && (*it1)->getDegree() == (*it2)->getDegree() && (*it1)->getDegree() == (*it3)->getDegree())
            {
                it1++;
                it2++;
                it3++;
            }

            else if ((*it1)->getDegree() == (*it2)->getDegree())
            {
                *it1 = mergeTrees(*it1,*it2);
                it2 = treeRoots.erase(it2);

                if(it3 != treeRoots.end())
                    it3++;
            }
        }
    }

    void unionHeap(MaxBinomialHeap h)
    {
        std::list<Node<T>*> newTreeRoot;
        auto it = treeRoots.begin();
        auto ot = h.treeRoots.begin();
        while (it != treeRoots.end() && ot != h.treeRoots.end())
        {
            if((*it)->getDegree() <= (*ot)->getDegree())
            {
                newTreeRoot.push_back(*it);
                it++;
            }

            else
            {
                newTreeRoot.push_back(*ot);
                ot++;
            }
        }

        while (it != treeRoots.end())
        {
            newTreeRoot.push_back(*it);
            it++;
        }

        while (ot != h.treeRoots.end())
        {
            newTreeRoot.push_back(*ot);
            ot++;
        }
        treeRoots = newTreeRoot;
        heapifyBinomialTrees();
    }

    void insertTree(Node<T> *tree)
    {
        MaxBinomialHeap h;
        h.treeRoots.push_back(tree);
        this->unionHeap(h);
    }

    MaxBinomialHeap removeMaxFromTreeReturnHeap(Node<T> *tree)
    {
        MaxBinomialHeap h;
        Node<T> *temp = tree->getChild();
        Node<T> *lo;

        while (temp)
        {
            lo = temp;
            temp = temp->getSibling();
            lo->setSibling(NULL);
            h.treeRoots.push_front(lo);
        }

        return h;
    }

    void insert(T key)
    {
        Node<T> *node = new Node<T>(key);
        insertTree(node);
        std::cout << "Inserted " << key << std::endl;
    }

    Node<T>* findMax()
    {
        if(treeRoots.size() == 0)
        {
            std::cout << "Heap underflow." << std::endl;
            return NULL;
        }
        auto it = treeRoots.begin();

        Node<T> *temp = *it;
        while (it != treeRoots.end())
        {
            if ((*it)->getKey() > temp->getKey())
                temp = *it;
            it++;
        }
        return temp;
    }

    Node<T>* extractMax()
    {
        if(treeRoots.size() == 0)
        {
            std::cout << "Heap underflow." << std::endl;
            return NULL;
        }

        MaxBinomialHeap lo;
        Node<T> *temp;

        temp = findMax();
        auto it = treeRoots.begin();
        while (it != treeRoots.end())
        {
            if (*it == temp)
            {
                treeRoots.erase(it);
            }

            it++;
        }

        lo = removeMaxFromTreeReturnHeap(temp);
        this->unionHeap(lo);
        return temp;
    }

    void increaseKey(T prevKey, T newKey)
    {
        Node<T> *nodeToBeIncreased = NULL;
        bool found = false;
        for(auto it = treeRoots.begin(); it != treeRoots.end(); it++)
        {
            Node<T>* temp = *it;

            while(temp != NULL)
            {
                if(temp->getKey() == prevKey)
                {
                    nodeToBeIncreased = temp;
                    found = true;
                }

                Node<T>* sibling = temp->getSibling();
                while(sibling != NULL)
                {
                    if(sibling->getKey() == prevKey)
                    {
                        nodeToBeIncreased = sibling;
                        found = true;
                        break;
                    }
                    sibling = sibling->getSibling();
                }

                if(found)
                    break;
                temp = temp->getChild();
            }

            if(found)
                break;
        }

        if(found)
        {
            nodeToBeIncreased->setKey(newKey);

            Node<T> *temp = nodeToBeIncreased;
            Node<T> *parent = nodeToBeIncreased->getParent();

            while(parent && parent->getKey() < temp->getKey())
            {
                T tempKey = temp->getKey();
                temp->setKey(parent->getKey());
                parent->setKey(tempKey);

                temp = parent;
                parent = temp->getParent();
            }

            std::cout << "Increased " << prevKey << ". The updated value is " << newKey << ".\n";
        }
        else
        {
            std::cout << prevKey << " not found.\n";
        }

    }

    void print()
    {
        int i = 1;
        std::cout << "Printing Binomial Heap...\n";
        std::cout << "-------------------------\n";
        for(auto it = treeRoots.begin(); it != treeRoots.end(); it++)
        {
            std::cout << "Binomial Tree, B" << i << std::endl;
            int j = 0;
            Node<T>* temp = *it;
            while(temp != NULL)
            {
                std::cout << "Level " << j << " : " << temp->getKey();
                Node<T>* sibling = temp->getSibling();
                while(sibling != NULL)
                {
                    std::cout << " " << sibling->getKey();
                    sibling = sibling->getSibling();
                }
                std::cout << std::endl;
                temp = temp->getChild();
                j++;
            }

            i++;
        }
        std::cout << "-------------------------\n";
    }
};
