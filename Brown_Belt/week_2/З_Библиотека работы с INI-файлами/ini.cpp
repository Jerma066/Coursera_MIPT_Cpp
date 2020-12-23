#include "ini.h"

namespace Ini {

Document Load(istream& input) {
	Document result;

	Section* current_section = nullptr;
	
	string str;
	while(getline(input, str)){
		if(!str.empty()){
			if(str[0] == '['){
				current_section = &result.AddSection(
					str.substr(1, str.size() - 2)
				);
			}
			else{
				size_t pos = str.find('=');
				current_section->insert(
					{str.substr(0, pos), 
					 str.substr(pos + 1)}
				);
			}
		}
	}

	return result;
}

Section& Document::AddSection(string name) {
	return sections[name];
}

const Section& Document::GetSection(const string& name) const {
	return sections.at(name);
}

size_t Document::SectionCount() const {
	return sections.size();
}

}
