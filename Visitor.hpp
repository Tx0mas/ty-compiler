#include"parser.hpp"
#include<iostream>



struct Visitor
{
    virtual ~Visitor() = default;
    virtual void visit (termNode &node) = 0;
    virtual void visit (binaryOpNode &node) = 0;
    virtual void visit (varNode &node) = 0;
    virtual void visit (instructionNode &node) = 0;
    virtual void visit (ifNode &node) = 0;
    virtual void visit (conditionNode &node) = 0;
    virtual void visit (blockNode &node) = 0;
};


struct SemanticAnalysis
:Visitor
{
    std::unordered_map<std::string, varKind> mapVarsAndKind{};


    void visit (termNode &node) override
    {
        if (node.kind == termKind::VARIABLE && mapVarsAndKind.find(node.val)==mapVarsAndKind.end())
        {
            throw std::logic_error("La variable usada no fue declarada anteriormente");
        }
    }

    void visit (binaryOpNode &node) override
    {
        node.left->accept(*this);
        node.right->accept(*this);
    }

    void visit (varNode &node) override
    {
        if (mapVarsAndKind.find(node.val)!=mapVarsAndKind.end())
        {
            throw std::logic_error("El nombre de variable fue declarado anteriormente");
        }
        mapVarsAndKind[node.val]=node.kind;
        node.node->accept(*this);
    }

    void visit (instructionNode &node) override
    {
        if (node.val == instructions::RETURN) 
        {
        }
        else if (node.val == instructions::DECLARATION)
        {
            node.node->accept(*this);
        }
        else if (node.val == instructions::REASSIGN)
        {
            if (mapVarsAndKind.find(node.optional) == mapVarsAndKind.end())
            {
                throw std::logic_error("La variable no fue declarada anteriormente.");
            }
            node.node->accept(*this);
        }
        else 
        {
            node.node->accept(*this);
        }
    }
    
    void visit(ifNode &node) override
    {
    }
    void visit(conditionNode &node) override
    {
    }
    void visit(blockNode &node) override
    {
    }

    std::unordered_map<std::string, varKind> getMap()
    {
        return mapVarsAndKind;
    }

};



enum class Types
{
    STRING_TYPE,
    INTEGER_TYPE,
};

struct Generation
:Visitor
{
    int ID_PRINT_NUM{1};
    int ID_PRINT_STRING{1};

    std::vector<Types> stackKind{};
    std::vector<std::string> stackDeclaration{};
    std::ofstream out{"./assembly.asm"};
    std::unordered_map<std::string, varKind> mapVars{};
    Generation(std::unordered_map<std::string,varKind> m)
    :mapVars{m}
    {
        out<<"section .text\n";
        out<<"     backN db 10\n";

        out<<"section .bss\n";
        out<<"     bufferString resb 64\n";
        out<<"     buffer resb 16\n";

        for (auto const var : mapVars)
        {
            if (var.second == varKind::STRING_KIND)
            {
                out<<"    "<<var.first<<" resb 64"<<'\n';
            }
            else 
            {
                out<<"    "<<var.first<<" resb 8"<<'\n';
            }
        }
        out<<"section .text\n";
        out<<"    global _start\n";
        out<<"_start:\n";
    }

    void visit (termNode &node) override
    {
        if (node.kind == termKind::INTEGER)
        {
            out<<"    mov rax, "<<std::stod(node.val)<<'\n';
            out<<"    push rax\n";
            stackKind.push_back(Types::INTEGER_TYPE);
        }
        else if (node.kind == termKind::STRING)
        {
            if (!stackDeclaration.back().empty())
            {
                std::string nombre = stackDeclaration.back();
                stackDeclaration.pop_back();
                size_t i{};
                while (i<node.val.length())
                {
                    out<<"    mov rax, "<<'"'<<node.val.substr(i,8)<<'"'<<'\n';
                    out<<"    mov qword ["<<nombre<<"+"<<i<<"]"<<", rax"<<'\n';
                    i+=8;
                }
                out<<"    mov byte["<<nombre<<"+"<<node.val.length()<<"],0\n";
                //no hace falta pushear el kind ya que es una declaracion.
            }
            else 
            {
                std::string nombre = "stringBuffer";
                size_t i{};
                while (i<node.val.length())
                {
                    out<<"    mov rax, "<<'"'<<node.val.substr(i,8)<<'"'<<'\n';
                    out<<"    mov qword ["<<nombre<<"+"<<i<<"]"<<", rax"<<'\n';
                    i+=8;
                }
                out<<"    mov byte["<<nombre<<"+"<<node.val.length()<<"],0\n";
                stackKind.push_back(Types::STRING_TYPE);
            }
        }
        else if (node.kind == termKind::VARIABLE)
        {
            auto tipo = mapVars.find(node.val)->second;
            if (tipo == varKind::INT_KIND)
            {
                out<<"    mov rax, ["<<node.val<<"]\n"; //chequeo posible error aca.
                out<<"    push rax\n";
                stackKind.push_back(Types::INTEGER_TYPE);
            }
            else if (tipo == varKind::STRING_KIND)
            {
                out<<"    mov rax, "<<node.val<<"\n"; //le paso la adress xq es de 64 bytes posiblemente
                out<<"    push rax\n";
                stackKind.push_back(Types::STRING_TYPE);
            }
        }
    }

    void visit (binaryOpNode &node) override
    {
        node.left->accept(*this);
        node.right->accept(*this);
        out<<"    pop rbx\n";
        out<<"    pop rax\n";

        if (node.val == "+")
        {
            out<<"    add rax, rbx\n";
            out<<"    push rax\n";
        }
        else if (node.val == "-")
        {
            out<<"    sub rax, rbx\n";
            out<<"    push rax\n";
        }
        else if (node.val == "*")
        {
            out<<"    mul rbx\n";
            out<<"    push rax\n";
        }
        else if (node.val == "/")
        {
            out<<"    mov rdx, 0\n";
            out<<"    div rbx\n";
            out<<"    push rax\n";
        }
        else {throw std::logic_error("error en binaryOpNode");}
    }

    void visit (varNode &node) override
    {
        auto tipo = mapVars.find(node.val)->second;
        if (tipo == varKind::INT_KIND)
        {
            node.node->accept(*this);
            out<<"    pop rax\n";
            out<<"    mov qword["<<node.val<<"], rax\n";
        }
        else if (tipo == varKind::STRING_KIND)
        {
            stackDeclaration.push_back(node.val);
            node.node->accept(*this);
        }
    }

    void visit (instructionNode &node) override  //agregar las otras instrucions
    {
        if (node.val == instructions::RETURN)
        {
            out<<"    mov rax, 60\n";
            out<<"    mov rdi, 0\n";
            out<<"    syscall\n";
        }
        else if (node.val == instructions::EJECUTAR)
        {
            node.node->accept(*this);
        }
        else if (node.val == instructions::DECLARATION)
        {
            node.node->accept(*this);
        }
        else if (node.val == instructions::REASSIGN)
        {
        }
        else if (node.val == instructions::PRINT)
        {
            node.node->accept(*this);
            auto tipo = stackKind.back();
            stackKind.pop_back();

            if (tipo == Types::INTEGER_TYPE)
            {
                int reservedId = ID_PRINT_NUM;
                ID_PRINT_NUM+=1;
                out<<"   pop rax\n";
                out<<"_printNumbers"<<reservedId<<":\n";

                out<<"   mov rbx, 0\n";
                out<<"   mov [buffer],rbx\n";
                out<<"   \n";
                out<<"   \n";
                out<<"   mov rcx, 8\n";
                out<<"   mov byte [buffer+rcx], 0\n";
                out<<"_printLoopNumbers"<<reservedId<<":\n";
                out<<"   mov rdx, 0\n";
                out<<"   mov rbx, 10\n";
                out<<"   div rbx\n";
                out<<"   mov rbx, rdx ;;aca posiblemente hay un error\n";
                out<<"   add rbx, 48\n";
                out<<"   dec rcx\n";
                out<<"   mov byte [buffer+rcx],bl\n";
                out<<"   cmp rax, 0\n";
                out<<"   je _done"<<reservedId<<"\n";
                out<<"   jmp _printLoopNumbers"<<reservedId<<"\n";
                out<<"_done"<<reservedId<<":\n";
                out<<"   mov rax, buffer\n";
                out<<"   add rax, rcx\n";
                out<<"   push rax\n";
                out<<"   \n";
                out<<"   mov rax, 8\n";
                out<<"   sub rax, rcx\n";
                out<<"   mov rbx, rax\n";
                out<<"   \n";
                out<<"   mov rax, 1\n";
                out<<"   mov rdi, 1\n";
                out<<"   pop rsi\n";
                out<<"   mov rdx, rbx\n";
                out<<"   syscall\n";
                out<<"   \n";
                out<<"   mov rax, 1\n";
                out<<"   mov rdi, 1\n";
                out<<"   mov rsi, backN\n";
                out<<"   mov rdx, 1\n";
                out<<"   syscall\n";


            }
            if (tipo == Types::STRING_TYPE)
            {
                int reservedIdString = ID_PRINT_STRING;
                ID_PRINT_STRING+=1;

                out<<"   mov rbx, 0\n";
                out<<"   mov rsi, [rsp]\n";
                out<<"_printString"<<reservedIdString<<":\n";
                out<<"   cmp byte [rsi+rbx], 0\n";
                out<<"   je _doneString"<<reservedIdString<<"\n";
                out<<"   inc rbx\n";
                out<<"   jmp _printString"<<reservedIdString<<"\n";
                out<<"_doneString"<<reservedIdString<<":\n";
                out<<"   mov rax, 1\n";
                out<<"   mov rdi, 1\n";
                out<<"   pop rsi\n";
                out<<"   mov rdx, rbx\n";
                out<<"   syscall\n";
                out<<"   \n";
                out<<"   mov rax, 1\n";
                out<<"   mov rdi, 1\n";
                out<<"   mov rsi, backN\n";
                out<<"   mov rdx, 1\n";
                out<<"   syscall\n";
            }

        }
        else 
        {
        }
    }

    void visit(ifNode &node) override
    {
    }
    void visit(conditionNode &node) override
    {
    }
    void visit(blockNode &node) override
    {
    }
};













void analyseAndGenerate(std::vector<std::unique_ptr<ASTNode>> &statements)
{
    SemanticAnalysis semanticAnalyseThis{};

    for (auto const &stats : statements)
    {
        stats->accept(semanticAnalyseThis);
    }
    auto m = semanticAnalyseThis.getMap();

    Generation generateThis{m};

    for (auto const &stats : statements)
    {
        stats->accept(generateThis);
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

void ifNode::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void conditionNode::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void blockNode::accept(Visitor &visitor)
{
    visitor.visit(*this);
}
