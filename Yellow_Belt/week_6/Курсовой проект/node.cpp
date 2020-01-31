#include "node.h"

//Базовый виртуальный класс Node
Node::Node():
    _type(TokenType::NONE),
    _comparison(Comparison::NONE)

{
}

Node::Node (TokenType tp, Comparison cmp):
    _type(tp),
    _comparison(cmp)
{
}

Comparison Node::GetComparison() const {
    return _comparison;
}


//Класс EmptyNode
EmptyNode::EmptyNode():
    Node()
{
}

bool EmptyNode::Evaluate(Date, string) const {
    return true;
}


//Класс DateComparisonNode
DateComparisonNode::DateComparisonNode():
    Node(TokenType::DATE, Comparison::NONE)
{
    _date = Date();
}

DateComparisonNode::DateComparisonNode(Comparison cmp, Date dt):
    _date(dt),
    Node(TokenType::DATE, cmp)
{
}

bool DateComparisonNode::Evaluate(Date date_for_compare, string event_for_compare) const {
    const Comparison cmp = GetComparison();
    switch(cmp) {
        case Comparison::Equal:
            return date_for_compare == _date;
        case Comparison::Greater:
            return date_for_compare > _date;
        case Comparison::GreaterOrEqual:
            return date_for_compare >= _date;
        case Comparison::Less:
            return date_for_compare < _date;
        case Comparison::LessOrEqual:
            return date_for_compare <= _date;
        case Comparison::NotEqual:
            return date_for_compare != _date;
        case Comparison::NONE:
        default:
            return false;

    }
}


//Класс EventComparisonNode
EventComparisonNode::EventComparisonNode():
    Node(TokenType::EVENT, Comparison::NONE),
    _event("")
{
}

EventComparisonNode::EventComparisonNode (Comparison cmp, string str):
    Node(TokenType::EVENT, cmp),
    _event(str)
{
}

bool EventComparisonNode::Evaluate(Date date_for_compare, string event_for_compare) const {
    const Comparison cmp = GetComparison();
    switch(cmp) {
        case Comparison::Less:
            return event_for_compare < _event;
        case Comparison::Equal:
            return event_for_compare == _event;
        case Comparison::Greater:
            return event_for_compare > _event;
        case Comparison::GreaterOrEqual:
            return event_for_compare >= _event;
        case Comparison::LessOrEqual:
            return event_for_compare <= _event;
        case Comparison::NotEqual:
            return event_for_compare != _event;
        default:
            return false;
    }
}


//Класс LogicalOperationNode
LogicalOperationNode::LogicalOperationNode(LogicalOperation lo, shared_ptr<Node> a, shared_ptr<Node> b):
    logicOperation(lo),
    leftForCompare(a),
    rightForCompare(b)
{
}

bool LogicalOperationNode::Evaluate(Date date_for_compare, string event_for_compare) const {
    switch (logicOperation){
        case LogicalOperation::And:
            return leftForCompare->Evaluate(date_for_compare, event_for_compare) &&
                   rightForCompare->Evaluate(date_for_compare, event_for_compare);
        case LogicalOperation::Or:
            return leftForCompare->Evaluate(date_for_compare, event_for_compare) ||
                   rightForCompare->Evaluate(date_for_compare, event_for_compare);
        default:
            return false;
    }
}
