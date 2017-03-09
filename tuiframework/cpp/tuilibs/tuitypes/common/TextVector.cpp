#include "TextVector.h"


TextVector::TextVector() {
}


TextVector::~TextVector() {
}


std::vector<std::string> & TextVector::operator()() {
    return this->strVec;
}


const std::vector<std::string> & TextVector::operator()() const {
    return this->strVec;
}


void TextVector::setTextVector(const std::vector<std::string> & strVec) {
    this->strVec = strVec;
}


std::ostream & TextVector::serialize(std::ostream & os) const {
    os << this->strVec.size();
    if (this->strVec.size()) {
        std::vector<std::string>::const_iterator i = this->strVec.begin();
        std::vector<std::string>::const_iterator e = this->strVec.end();
        while (i != e) {
            os << " " << (*i).size();
            if ((*i).size()) {
                os << " ";
                os.write((*i).c_str(), (*i).size());
            }
            ++i;
        }
    }
    return os;
}


std::istream & TextVector::deSerialize(std::istream & is) {

    this->strVec.clear();
    int vecSize;
    is >> vecSize;

    for (int i = 0; i < vecSize; ++i) {
        int size;
        is >> size;
        if (size) {
          char * text = new char[size + 1];
            // read the delimiter
          is.read(text, 1);
          is.read(text, size);
          text[size] = 0;
          this->strVec.push_back(text);
          delete []text;
        } else  {
          strVec.push_back("");
        }
    }
}
