#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>
#include <set>
#include "product.h"

using namespace std;

class Book: public Product{

  public:
  Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
  virtual std::set<std::string> keywords() const;
  virtual std::string displayString() const;
  void dump(std::ostream& os) const;

  protected:
  std::set<std::string> keywords_;
  string isbn_;
  string author_;
};

#endif