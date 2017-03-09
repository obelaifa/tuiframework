#ifndef _tuiframework_Text_h_
#define _tuiframework_Text_h_

#include <tuiframework/core/ISerializable.h>
#include <iostream>
#include <string>

class Text : public tuiframework::ISerializable {
public:
    Text();
    virtual ~Text();

    std::string & operator()();
    const std::string & operator()() const;

    void setText(const std::string & str);

    virtual std::ostream & serialize(std::ostream & os) const;
    virtual std::istream & deSerialize(std::istream & is);

protected:
    std::string str;
};


#endif
