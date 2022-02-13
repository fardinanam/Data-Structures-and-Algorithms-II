template <typename T>
class Node
{
private:
    Node<T> *parent, *sibling, *child;
    T key;
    int degree;

public:
    Node(T key)
    {
        parent = NULL;
        sibling = NULL;
        child = NULL;
        this->key = key;
        degree = 0;
    }

    template <typename U>
    friend Node<U>* mergeTrees(Node<U> *n1, Node<U> *n2);

    void setParent(Node<T> *node)
    {
        this->parent = node;
    }

    void setSibling(Node<T> *node)
    {
        this->sibling = node;
    }

    void setChild(Node<T> *node)
    {
        this->child = node;
    }

    void setKey(T key)
    {
        this->key = key;
    }

    Node<T>* getParent()
    {
        return parent;
    }

    Node<T>* getSibling()
    {
        return sibling;
    }

    Node<T>* getChild()
    {
        return child;
    }

    T getKey()
    {
        return key;
    }

    int getDegree()
    {
        return degree;
    }

    ~Node()
    {
        delete parent;
        delete sibling;
        delete child;
    }
};

template <typename U>
Node<U>* mergeTrees(Node<U> *n1, Node<U> *n2)
{
    Node<U> *larger, *smaller;
    if(n1->key > n2->key)
    {
        larger = n1;
        smaller = n2;
    }
    else
    {
        larger = n2;
        smaller = n1;
    }

    smaller->parent = larger;
    smaller->sibling = larger->child;
    larger->child = smaller;
    larger->degree++;

    return larger;
}
