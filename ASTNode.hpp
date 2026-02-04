#include<string>
#include<vector>
#include<memory>



struct Visitor;

struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual void accept(Visitor &visitor) = 0;
    virtual std::string getVal() = 0;
};

enum class instructions
{
    REASSIGN,
    DECLARATION,
    PRINT,
    RETURN,
    EJECUTAR,

};

struct instructionNode
:ASTNode
{
    instructions val{};
    std::string optional{};
    std::unique_ptr<ASTNode> node{};


    instructionNode(instructions v, std::string o, std::unique_ptr<ASTNode> n)
    :val{v},optional{o}, node{std::move(n)}
    {}
    instructionNode(instructions v, std::unique_ptr<ASTNode> n)
    :val{v}, optional{"NULL"}, node{std::move(n)}
    {}
    instructionNode(instructions v)
    :val{v},optional{"NULL"}, node{std::move(nullptr)}
    {}
    void accept(Visitor &visitor) override;
    std::string getVal() override {return "'";}
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
    std::string getVal() override
    {
        return val;
    }
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

    std::string getVal() override
    {
        return val;
    }

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

    std::string getVal() override
    {
        return val;
    }
};

struct ifNode
:ASTNode
{
    std::unique_ptr<ASTNode> cond{};
    std::unique_ptr<ASTNode> block{};
    std::unique_ptr<ASTNode> pred{};

    ifNode(std::unique_ptr<ASTNode> c, std::unique_ptr<ASTNode> b, std::unique_ptr<ASTNode> p)
    :cond{std::move(c)},block{std::move(b)}, pred{std::move(p)}
    {}

    ifNode(std::unique_ptr<ASTNode> c, std::unique_ptr<ASTNode> b)
    :cond{std::move(c)},block{std::move(b)},pred{std::move(nullptr)}
    {}

    void accept(Visitor &visitor) override;
    std::string getVal() override {return "'";}

};

enum class conditionType
{
    EQ_COND,
    NEQ_COND,
    GREATER_THAN_CERO,

};

struct conditionNode
:ASTNode
{
    conditionType cond{};
    std::unique_ptr<ASTNode> left{};
    std::unique_ptr<ASTNode> right{};

    conditionNode(conditionType c, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
    :cond{c}, left{std::move(l)}, right{std::move(r)}
    {}

    conditionNode(conditionType c, std::unique_ptr<ASTNode> l)
    :cond{c}, left{std::move(l)}, right{std::move(nullptr)}
    {}

    void accept(Visitor &visitor) override;
    std::string getVal() override {return "'";}

};


struct blockNode
:ASTNode
{
    std::vector<std::unique_ptr<ASTNode>> statementsLocal{};

    blockNode(std::vector<std::unique_ptr<ASTNode>> stats)
    :statementsLocal{std::move(stats)}
    {}
    void accept(Visitor &visitor) override;
    std::string getVal() override {return "'";}
};




struct whileNode
:ASTNode
{
    std::unique_ptr<ASTNode> cond{};
    std::unique_ptr<ASTNode> block{};

    whileNode(std::unique_ptr<ASTNode> c, std::unique_ptr<ASTNode> b)
    :cond{std::move(c)},block{std::move(b)}
    {}

    void accept(Visitor &visitor) override;
    std::string getVal() override {return "'";}

};


