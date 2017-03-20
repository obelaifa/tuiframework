#include "Text.h"


Text::Text() {
}


Text::~Text() {
}


std::string & Text::operator()() {
    return this->str;
}


const std::string & Text::operator()() const {
    return this->str;
}


void Text::setText(const std::string & str) {
    this->str = str;
}


std::ostream & Text::serialize(std::ostream & os) const {
    os << this->str.size();
    if (this->str.size()) {
      os << " ";
      os.write(this->str.c_str(), this->str.size());
    }
    return os;
}


std::istream & Text::deSerialize(std::istream & is) {
    int size;
    is >> size;
    if (size) {
      char * text = new char[size + 1];
        // read the delimiter
      is.read(text, 1);
      is.read(text, size);
      text[size] = 0;
      this->str = text;
      delete []text;
    }
    return is;
}
