#ifndef _tuiframework_TextVector_h_
#define _tuiframework_TextVector_h_

#include <tuiframework/core/ISerializable.h>
#include <iostream>
#include <string>
#include <vector>

class TextVector : public tuiframework::ISerializable {
public:
    TextVector();
    virtual ~TextVector();

    std::vector<std::string> & operator()();
    const std::vector<std::string> & operator()() const;

    void setTextVector(const std::vector<std::string> & strVec);

    virtual std::ostream & serialize(std::ostream & os) const;
    virtual std::istream & deSerialize(std::istream & is);

protected:
    std::vector<std::string> strVec;
};


#endif
