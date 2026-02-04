#include"parser.hpp"
#include<iostream>



struct Visitor
{
    virtual ~Visitor() = default;
    virtual void visit (termNode &node) = 0;
    virtual void visit (binaryOpNode &node) = 0;
    virtual void visit (varNode &node) = 0;
    virtual void visit (instructionNode &node) = 0;
};

struct PrintVisitor
:Visitor
{

    void visit (termNode &node) override
    {
        std::cout<<node.val;
    }
    void visit (binaryOpNode &node) override
    {
        std::cout<<"(";
        node.left->accept(*this);
        std::cout<<node.val;
        node.right->accept(*this);
        std::cout<<")";
    }
    void visit (varNode &node) override
    {
        std::cout<<node.val<<'\n';
        node.node->accept(*this);
    }
    void visit (instructionNode &node) override
    {
        if (node.val == "RETURN")
        {
            std::cout<<'\n'<<node.val<<'\n';
        }
        else 
        {
            std::cout<<'\n'<<node.val<<'\n';
            node.node->accept(*this);
        }
    }
};

void printStatements(std::vector<std::unique_ptr<ASTNode>> &statements)
{
    PrintVisitor printThis{};

    for (auto const &stats : statements)
    {
        stats->accept(printThis);
    }
}















void termNode::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void binaryOpNode::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void varNode::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void instructionNode::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

