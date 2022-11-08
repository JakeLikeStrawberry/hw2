#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <string>
#include <iostream>
#include <set>

using namespace std;

class Clothing: public Product{

  public:
  Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
  virtual std::set<std::string> keywords() const;
  virtual std::string displayString() const;
  void dump(std::ostream& os) const;

  protected:
  std::set<std::string> keywords_;
  string size_;
  string brand_;

};
#endif