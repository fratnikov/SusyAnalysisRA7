#ifndef CHAMELEON_H
#define CHAMELEON_H


//---chameleon class

#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Chameleon {

  public:
Chameleon() {}
Chameleon(std::string const& value) {
  value_=value;
}


Chameleon(const char* c) {
  value_=c;
}

Chameleon(double d) {
  std::stringstream s;
  s<<d;
  value_=s.str();
}

Chameleon(Chameleon const& other) {
  value_=other.value_;
}

Chameleon& operator=(Chameleon const& other) {
  value_=other.value_;
  return *this;
}

Chameleon& operator=(double i) {
  std::stringstream s;
  s << i;
  value_ = s.str();
  return *this;
}

Chameleon& operator=(std::string const& s) {
  value_=s;
  return *this;
}

operator std::string() const {
  return value_;
}

operator double() const {
  return atof(value_.c_str());
}



private:
  std::string value_;
};



//---trim function
std::string trim(std::string const& source, char const* delims = " \t\r\n") {
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos)
    result.erase(++index);

  index = result.find_first_not_of(delims);
  if(index != std::string::npos)
    result.erase(0, index);
  else
    result.erase();
  return result;
}

//---trim function

//---class
class ConfigFile {
  std::map<std::string,Chameleon> content_;

public:
  ConfigFile(std::string const& configFile);

  Chameleon const& Value(std::string const& section, std::string const& entry) const;
  Chameleon const& Value(std::string const& section, std::string const& entry, double value);
  Chameleon const& Value(std::string const& section, std::string const& entry, std::string const& value);
};


ConfigFile::ConfigFile(std::string const& configFile) {
  std::ifstream file(configFile.c_str());

  std::string line;
  std::string name;
  std::string value;
  std::string inSection;
  int posEqual;
  while (std::getline(file,line)) {

    if (! line.length()) continue;

    if (line[0] == '#') continue;
    if (line[0] == ';') continue;

    if (line[0] == '[') {
      inSection=trim(line.substr(1,line.find(']')-1));
      continue;
    }

    posEqual=line.find('=');
    name  = trim(line.substr(0,posEqual));
    value = trim(line.substr(posEqual+1));

    content_[inSection+'/'+name]=Chameleon(value);
  }
}

Chameleon const& ConfigFile::Value(std::string const& section, std::string const& entry) const {

  std::map<std::string,Chameleon>::const_iterator ci = content_.find(section + '/' + entry);

  if (ci == content_.end()) throw "does not exist";

  return ci->second;
}

Chameleon const& ConfigFile::Value(std::string const& section, std::string const& entry, double value) {
  try {
    return Value(section, entry);
  } catch(const char *) {
    return content_.insert(std::make_pair(section+'/'+entry, Chameleon(value))).first->second;
  }
}

Chameleon const& ConfigFile::Value(std::string const& section, std::string const& entry, std::string const& value) {
  try {
    return Value(section, entry);
  } catch(const char *) {
    return content_.insert(std::make_pair(section+'/'+entry, Chameleon(value))).first->second;
  }
}


#endif
