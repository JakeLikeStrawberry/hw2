#include <iostream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
Product(category, name, price, qty){
  isbn_ = isbn;
  author_ = author;
  //keywords_ = NULL; //might need to call keywords function here, not sure
}

  std::set<std::string> Book::keywords() const{

   set<string> result;
   set<string> name_search;
   set<string> author_search;
   
  name_search = parseStringToWords(name_);
  author_search = parseStringToWords(author_);      //parses variables

  result = setUnion(name_search, author_search);
  result.insert(isbn_);     //directly inserts isbn
  
  //  set<string>::iterator itr;
   
  // for (itr = result.begin(); itr != result.end(); ++itr){
  //   cout << *itr << endl;
  // }

  return result;

  }


  std::string Book::displayString() const{
    string priceString = std::to_string(price_);
    string qtyString = std::to_string(qty_);
    string result = name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + priceString + " " + qtyString + " left.";
    return result;
  }


  void Book::dump(std::ostream& os) {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
  }


