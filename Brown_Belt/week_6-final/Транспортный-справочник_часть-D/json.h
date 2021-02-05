#pragma once

#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Json {

  class Node : std::variant<std::vector<Node>,
                            std::map<std::string, Node>,
                            double,
                            int,
                            bool,
                            std::string> {
  public:
    using variant::variant;

    const auto& AsArray() const {
      return std::get<std::vector<Node>>(*this);
    }
    const auto& AsMap() const {
      return std::get<std::map<std::string, Node>>(*this);
    }
    int DoubleAsInt() const {
      return static_cast<int>(this->AsDouble());
    }
    int AsInt() const {
        return std::get<int>(*this);
    }
    double AsDouble() const {
        return std::get<double>(*this);
    }
    const auto& AsString() const {
      return std::get<std::string>(*this);
    }
    const auto& AsBool() const{
        return std::get<bool>(*this);
    }

    bool HasMap() const {
        return std::holds_alternative<std::map<std::string, Node>>(*this);
    }
    bool HasVector() const {
        return std::holds_alternative<std::vector<Node>>(*this);
    }
    bool HasString() const {
        return std::holds_alternative<std::string>(*this);
    }
    bool HasDouble() const {
        return std::holds_alternative<double>(*this);
    }
    bool HasInt() const {
        return std::holds_alternative<int>(*this);
    }
  };

  class Document {
  public:
    explicit Document(Node root);

    const Node& GetRoot() const;

  private:
    Node root;
  };

  Node LoadNode(std::istream& input);
  Node LoadArray(std::istream& input);
  Node LoadNum(std::istream& input);
  Node LoadString(std::istream& input);
  Node LoadDict(std::istream& input);
  Node LoadBool(std::istream& input);
  Document Load(std::istream& input);

  void PrintNode(const Node& node, std::ostream& output=std::cout);
  void PrintNodeVector(const Node& node, std::ostream& output=std::cout);
  void PrintNodeMap(const Node& node, std::ostream& output=std::cout);
  void PrintNodeString(const Node& node, std::ostream& output=std::cout);
  void PrintNodeInt(const Node& node, std::ostream& output=std::cout);
  void PrintNodeDouble(const Node& node, std::ostream& output=std::cout);
}
