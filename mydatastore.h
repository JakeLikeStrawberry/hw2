#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include "datastore.h"
#include "product.h"
#include "util.h"
#include "user.h"
#include "book.h"
#include "product_parser.h"

using namespace std;

class MyDataStore: public DataStore{

public:
  MyDataStore();
  ~MyDataStore();
  virtual void addProduct(Product* p);
  virtual void addUser(User* u);
  virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
  virtual void dump(std::ostream& ofile);
  //virtual void addUsername(User* u);
  void clear();

  virtual void addtoCart(string username, Product* p);
  virtual void viewCart(string username);
  virtual void buyCart(string username);
  
protected:

  map<string, User*> allUsers;
  map<string, vector<Product*>> userCart;
  map<string, set<Product*>> totalStore;
  set<Product*> allProducts;
  

};

#endif