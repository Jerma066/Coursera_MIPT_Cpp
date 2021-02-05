#include <variant>
#include "json.h"

using namespace std;

namespace Json {

  Document::Document(Node root) : root(move(root)) {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  Node LoadNode(istream& input);

  Node LoadArray(istream& input) {
    vector<Node> result;

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }
      result.push_back(LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadNum(istream& input) {
	bool is_negative = false;
	if (input.peek() == '-') {
		is_negative = true;
		input.get();
	}
	int int_part = 0;
	while (isdigit(input.peek())) {
		int_part *= 10;
		int_part += input.get() - '0';
	}
	if (input.peek() != '.') {
		return Node(int_part * (is_negative ? -1 : 1));
	}
	input.get();  // '.'
	double result = int_part;
	double frac_mult = 0.1;
	while (isdigit(input.peek())) {
		result += frac_mult * (input.get() - '0');
		frac_mult /= 10;
	}
	return Node(result * (is_negative ? -1 : 1));
   }

  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(move(line));
  }

  Node LoadDict(istream& input) {
    map<string, Node> result;

    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }

      string key = LoadString(input).AsString();
      input >> c;
      result.emplace(move(key), LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadBool(istream &input){
	bool result = (input.peek() == 't');
	while (islower(input.peek())) {
		input.get();
	}
	return Node(result);
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    } else if (isdigit(c)) {
      input.putback(c);
      return LoadNum(input);
    }
    else {
        input.putback(c);
        return LoadBool(input);
    }
  }

  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }



  void PrintNode(const Node& node, ostream& output){
      if(node.HasVector()){
          PrintNodeVector(node, output);
      }
      else if (node.HasMap()){
          PrintNodeMap(node, output);
      }
      else if (node.HasString()) {
          PrintNodeString(node, output);
      }
      else if (node.HasDouble()){
          PrintNodeDouble(node, output);
      }
      else if (node.HasInt()){
          PrintNodeInt(node, output);
      }
      else {
          throw invalid_argument("Node does not contain any value");
      }
  }

  void PrintNodeVector(const Node& node, std::ostream& output){
     std::vector<Node> vec_node = node.AsArray();
     std::string bracket = vec_node.empty() ? "[" : "[";
     output << bracket;
     bool is_first = true;
     for(const auto& el : vec_node){
		 if(!is_first) {
			output << ", ";
		 }
         PrintNode(el, output);
         is_first = false;
     }
     output << "]";
  }

  void PrintNodeMap(const Node& node, std::ostream& output){
      std::map<std::string, Node> map_node = node.AsMap();
      output << "{";
      bool is_first = true;
      for(const auto& el : map_node){
		  if(!is_first) {
			output << ",";
		  }
		  is_first = false;
          output << " \"" << el.first << "\": ";
          PrintNode(el.second, output);
      }
      output << "}";
  }

  void PrintNodeString(const Node& node, ostream& output){
      output << "\"" << node.AsString() << "\"";
  }

  void PrintNodeInt(const Node& node, ostream& output){
      output << node.AsInt();
  }

  void PrintNodeDouble(const Node& node, ostream& output){
      output << node.AsDouble();
  }
}
