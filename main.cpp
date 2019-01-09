#include <iostream>
#include <string>

using namespace std;

template <class T>
struct Node
{
  T data;
  Node<T> *left, *right;
  Node (const T& d, Node<T>* l, Node<T>* r): data(d), left(l), right(r) {}
};

template <class T>
class BTree
{
private:
  Node<T> *root;

  void insertHelper (const T& data,const char* trace,Node<T>*& curr)
  {
      if(curr == nullptr && trace[0] == 0)
      {
          curr = new Node<T>(data, nullptr, nullptr);
          return;
      }
      if(trace[0] == 'L')  insertHelper(data, trace + 1, curr->left);
      if(trace[0] == 'R')  insertHelper(data, trace + 1, curr->right);
  }
  void addHelp (Node<T>*& _root, const T& data)
  {
      if(_root != nullptr)
      {
          if(_root->data >= data) addHelp(_root->left, data);
          else addHelp(_root->right, data);
      }
      else
      {
          _root = new Node<T> (data);
      }
  }
  Node<T>* findMinRSubTree (Node<T>* crr)
  {
      while(crr->left != nullptr)
      {
          crr = crr->left;
      }
      return crr;
  }
  void removeNodeHelper (Node<T>*& _root, const T& _data)
  {
      if(_root == nullptr) return;
      else if(_root->data < _data) removeNodeHelper(root->right, _data);
      else if(_root->data > _data) removeNodeHelper(root->left, _data);
      else
      {
          if(_root->left == nullptr && _root->right == nullptr)
          {
              delete _root;
              _root = nullptr;
              return;
          }
          else if(_root->left == nullptr && _root->right != nullptr)
          {
              Node<T>* temp = _root;
              _root = _root->right;
              delete temp;
              return;
          }
          else if(_root->left != nullptr && _root->right == nullptr)
          {
              Node<T>* temp = _root;
              _root = _root-> left;
              delete temp;
              return;
          }
          T minInRight = findMinRSubTree(_root->right);
          swap(_root->data, minInRight->data);
          removeNodeHelper(_root->right, _data);
      }
  }
  Node<T>* copy (Node<T>*otherCurrent)
  {
      if(otherCurrent == nullptr)
      {
          return nullptr;
      }
      return new Node<T> (otherCurrent->data, copy(otherCurrent->left), copy(otherCurrent->right));
  }
  void deleteSubtree (Node<T> *currentRoot)
  {
      if(currentRoot == nullptr)
      {
          return;
      }
      deleteSubtree(currentRoot->left);
      deleteSubtree(currentRoot->right);
      delete currentRoot;
  }
  bool compareTrees (Node<T> *root1, Node<T> *root2)
  {
      if(root1 == nullptr || root2 == nullptr)
      {
          return root1 == root2;
      }
      return root1->data == root2->data && compareTrees(root1->left,root2->left) &&
                                           compareTrees(root1->right, root2->right);
  }
  bool member (Node<T>* root,const T& x)
  {
        if(root != nullptr && root->data == x) return true;
        else return false;

        return member(root->left,x)|| member(root->right,x);
  }
  T sum (Node<T>* root)
  {
      if(root == nullptr) return 0;
      return root->data + sum(root->left) + sum(root->right);
  }
  int countLeaves (Node<T>* root)
  {
      if(root->left == nullptr && root->right == nullptr) return 1;
      else return 0;

      return countLeaves(root->left) + countLeaves(root->right);
  }
  void printToHs (Node<T>* current, ostream& out)
  {
      if(current == nullptr)
      {
          out<<"Empty";
          return;
      }
      out<<"Node "<<current->data<<endl;
      printToHs(current->left, out);
      printToHs(current->right, out);
  }
  Node<T>* readFromHsHelper (istream& in)
  {
      string current;
      in>> current;

      if(current == "Empty")
      {
          return nullptr;
      }
      else if(current == "Node")
      {
          T rootdata;
          in>> rootdata;
          return new Node<T> (rootdata, readFromHsHelper(in), readFromHsHelper(in));
      }
  }
public:
  BTree ()
  {
      root = nullptr;
  }
  BTree (const BTree<T>& other)
  {
      root = copy(other);
  }

  BTree<T>& operator = (const BTree<T>& other)
  {
      if(this != &other)
      {
          deleteSubtree(this->root);
          this->root = copy(other.root);
      }
      return *this;
  }

  bool operator == (const BTree<T>& other)
  {
        return compareTrees(this->root, other.root);
  }
  bool member (const T& x)
  {
      return member(root, x);
  }
  T sum ()
  {
      return sum(root);
  }
  int countLeaves ()
  {
      return countLeaves(root);
  }

  void insert (const T& data,const char* trace)
  {
      insertHelper(data, trace, root);
  }
  void printToHs (ostream& out)
  {
        printToHs(root, out);
  }
  void readFromHs (istream& in)
  {
      if(root != nullptr)
      {
          deleteSubtree(root);
      }
      root = readFromHsHelper(in);
  }
  ~BTree ()
  {
      deleteSubtree(this->root);
  }



};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
