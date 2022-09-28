#include <iostream>
#include "product.h"
#include "util.cpp"
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
Product(category, name, price, qty){
  size_ = size;
  brand_ = brand;
  //keywords_ = NULL; //might need to call keywords function here, not sure
}
  
  std::set<std::string> Clothing::keywords() const{

   set<string> result;
   set<string> name_search;
   set<string> brand_search;
   
  name_search = parseStringToWords(name_);
  brand_search = parseStringToWords(brand_);

  result = setUnion(name_search, brand_search);
  return result;

  }


  std::string Clothing::displayString() const{
    string priceString = std::to_string(price_);
    string qtyString = std::to_string(qty_);
    string result = "Name: " + name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + priceString + " " + qtyString + " left.";
    return result;
  }


  void Clothing::dump(std::ostream& os) {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
  }


