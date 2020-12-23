#pragma once

#include <unordered_map>
#include <string>
#include <istream>

using namespace std;

namespace Ini {

using Section = unordered_map<string, string>;

class Document {
public:
  Section& AddSection(string name);
  const Section& GetSection(const string& name) const;
  size_t SectionCount() const;

private:
  unordered_map<string, Section> sections;
};

Document Load(istream& input);

}

