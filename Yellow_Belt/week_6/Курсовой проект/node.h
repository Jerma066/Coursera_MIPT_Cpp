#ifndef __NODE_H
#define __NODE_H

#include "token.h"
#include "date.h"
#include <memory>

class Node{
public:
    Node();
    Node (TokenType, Comparison);

    virtual bool Evaluate(Date, string) const = 0;
    Comparison GetComparison() const;

private:
    TokenType _type;
    Comparison _comparison;
};


class EmptyNode : public Node{
public:
    EmptyNode();

    virtual bool Evaluate(Date, string) const override;
};


class DateComparisonNode: public Node{
public:
    DateComparisonNode();
    DateComparisonNode(Comparison , Date);

    virtual bool Evaluate(Date, string) const override;

private:
    Date _date;
};


class EventComparisonNode : public Node{
public:
    EventComparisonNode();
    EventComparisonNode(Comparison , string);

    virtual bool Evaluate(Date, string) const override;

private:
    string _event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation, shared_ptr<Node>, shared_ptr<Node>);

    virtual bool Evaluate(Date, string) const override;

private:
    LogicalOperation logicOperation;
    shared_ptr<Node> leftForCompare;
    shared_ptr<Node> rightForCompare;
};


#endif //__NODE_H
