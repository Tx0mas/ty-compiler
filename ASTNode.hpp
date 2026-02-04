#include<string>
#include<vector>
#include<memory>



struct Visitor;

struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual void accept(Visitor &visitor) = 0;
};


struct instructionNode
:ASTNode
{
    std::string val{};
    std::unique_ptr<ASTNode> node{};

    instructionNode(std::string v, std::unique_ptr<ASTNode> n)
    :val{v}, node{std::move(n)}
    {}

    instructionNode(std::string v)
    :val{v}, node{std::move(nullptr)}
    {}
    void accept(Visitor &visitor) override;
};

enum class varKind
{
    INT_KIND,
    STRING_KIND,
};

struct varNode
:ASTNode
{
    std::string val{};
    varKind kind{};
    std::unique_ptr<ASTNode> node{};

    varNode(std::string v,varKind k,  std::unique_ptr<ASTNode> n)
    :val{v},kind{k},node{std::move(n)}
    {}
    varNode(std::string v,varKind k)
    :val{v},kind{k},node{std::move(nullptr)}
    {}

    void accept(Visitor &visitor) override;
};

struct binaryOpNode
:ASTNode
{
    std::string val{};
    std::unique_ptr<ASTNode> left{};
    std::unique_ptr<ASTNode> right{};

    binaryOpNode(std::string v, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
    :val{v},left{std::move(l)},right{std::move(r)}
    {}
    void accept(Visitor &visitor) override;
};

enum class termKind
{
    INTEGER,
    STRING,
    VARIABLE,
};


struct termNode
:ASTNode
{
    std::string val{};
    termKind kind{};

    termNode(std::string v, termKind k )
    :val{v}, kind{k}
    {}
    void accept(Visitor &visitor) override;
};




