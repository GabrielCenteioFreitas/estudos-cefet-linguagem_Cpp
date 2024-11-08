#include <iostream>

using namespace std;

int main() {
  int a, *p, **q;
  a = 30;
  p = &a;
  q = &p;
  cout << "a: " << a << endl;
  cout << "p: " << p << endl;
  cout << "q: " << q << endl;
  cout << "*p: " << *p << endl;
  cout << "*q: " << *q << endl;
  cout << "**q: " << **q << endl;
  cout << "&a: " << &a << endl;
  cout << "&p: " << &p << endl;
  cout << "&q: " << &q << endl;
  cout << "&*p: " << &*p << endl;
  cout << "*&p: " << *&p << endl;
  cout << "*(&p): " << *(&p) << endl;
  cout << "&(*p): " << &(*p) << endl;
}