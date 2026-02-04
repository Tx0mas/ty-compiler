#include"tokenizer.hpp"
#include"ASTNode.hpp"




class Parser
{
private:
    std::vector<std::unique_ptr<ASTNode>> m_statements{};
    std::vector<Token> m_vecTokens{};
    size_t m_pos{};

public:
    Parser(std::vector<Token> &vec)
    : m_vecTokens{vec}
    {}


    tokenType peekToken(size_t optional = 0)
    {
        if (m_pos+optional<m_vecTokens.size())
        {
            return m_vecTokens.at(m_pos+optional).type;
        }
        return EOF_TOKEN;
    }

    std::string peekValToken(size_t optional = 0)
    {
        if (m_pos+optional<m_vecTokens.size())
        {
            return m_vecTokens.at(m_pos+optional).val;
        }
        return "EOF";
    }
    void consume(size_t optional = 1)
    {
        m_pos+=optional;
    }

    std::pair<double, double> getBindingPower(std::string op)
    {
        if (op == "+" || op == "-")
        {
            return {1,1.1};
        }
        else if (op == "*" || op == "/")
        {
            return {2,2.1};
        }
        else {
            return {0,0.1};
        }
    }





    std::unique_ptr<ASTNode> parseTerm()
    {
        if (peekToken() == NUM_TOKEN)
        {
            std::string val = peekValToken();
            consume();
            return std::make_unique<termNode> (val, termKind::INTEGER);
        }
        else if (peekToken() == STRING_TOKEN)
        {
            std::string val = peekValToken();
            consume();
            return std::make_unique<termNode> (val,termKind::STRING);
        }
        else if (peekToken() == IDENTIFIER_TOKEN)
        {
            std::string val = peekValToken();
            consume();
            return std::make_unique<termNode> (val,termKind::VARIABLE);
        }
        throw std::logic_error("error en parseTerm");
    }


    std::unique_ptr<ASTNode> parseExpression(double actualBp = 0)
    {
        auto nodo1 = parseTerm();

        while (true)
        {
            std::string operation = peekValToken();

            if (peekToken() == SEMICOLON_TOKEN || peekToken() == STRING_TOKEN || peekToken() == EQ_TOKEN 
                    || peekToken()==NEQ_TOKEN || peekToken()==RPAREN_TOKEN)
            {
                break;
            }
            std::pair<double,double> vecBp = getBindingPower(operation);

            if (actualBp>vecBp.first)
            {
                break;
            }

            consume();//op
            auto nodo2 = parseExpression(vecBp.second);
            nodo1 = std::make_unique<binaryOpNode>(operation, std::move(nodo1), std::move(nodo2));

        }
        return nodo1;

    }

    std::unique_ptr<ASTNode> parseVar()
    {
        auto tipo = peekToken();
        consume();
        if (peekToken() != IDENTIFIER_TOKEN) {throw std::logic_error("Su variable no tiene nombre.");}
        std::string nombre = peekValToken();
        consume();
        if (peekToken() == ASSIGN_TOKEN)
        {
            consume();
            if (tipo ==  STR_TYPE_TOKEN)
            {
                auto nodo = parseExpression();
                return std::make_unique<varNode> (nombre, varKind::STRING_KIND, std::move(nodo));
            }
            else if (tipo == INT_TYPE_TOKEN)
            {
                auto nodo = parseExpression();
                return std::make_unique<varNode> (nombre, varKind::INT_KIND, std::move(nodo));
            }
        }
        else if (peekToken() == SEMICOLON_TOKEN)
        {
            if (tipo ==  STR_TYPE_TOKEN)
            {
                return std::make_unique<varNode> (nombre, varKind::STRING_KIND);
            }
            else if (tipo == INT_TYPE_TOKEN)
            {
                return std::make_unique<varNode> (nombre, varKind::INT_KIND);
            }
        }
        else {throw std::logic_error("error en parseVar");}
    }

    std::unique_ptr<ASTNode> parseDeclaration()
    {
        consume();
        if (peekToken() == STR_TYPE_TOKEN || peekToken() == INT_TYPE_TOKEN)
        {
            auto nodo = parseVar();
            return std::make_unique<instructionNode> (instructions::DECLARATION, std::move(nodo));
        }
        throw std::logic_error("las variables declaradas deben llevar su tipo.");
    }

    std::unique_ptr<ASTNode> parsePrint()
    {
        consume();
        auto nodo = parseExpression();
        return std::make_unique<instructionNode> (instructions::PRINT, std::move(nodo));
    }

    std::unique_ptr<ASTNode> parseReturn()
    {
        consume();
        return std::make_unique<instructionNode> (instructions::RETURN);
    }
    std::unique_ptr<ASTNode> parseReassign()
    {
        std::string nombre = peekValToken();
        consume();
        if (peekToken()!=ASSIGN_TOKEN){throw std::logic_error("luego de un IDENTIFIER_TOKEN al principio va un assign");}
        consume();
        auto nodo = parseExpression();

        return std::make_unique<instructionNode> (instructions::REASSIGN,nombre, std::move(nodo));

    }





    std::unique_ptr<ASTNode> parseCondition()
    {
        auto nodo1 = parseExpression();
        if (peekToken() == RPAREN_TOKEN)
        {
            consume();
            return std::make_unique<conditionNode> (conditionType::GREATER_THAN_CERO, std::move(nodo1));
        }
        auto condicion = peekToken();
        consume();
        auto nodo2 = parseExpression(); 

        if (peekToken() != RPAREN_TOKEN){throw std::logic_error("algo fallo en parseCondition");}
        consume();

        if (condicion == EQ_TOKEN)
        {
            return std::make_unique<conditionNode> (conditionType::EQ_COND, std::move(nodo1),std::move(nodo2));
        }
        else if (condicion == NEQ_TOKEN)
        {
            return std::make_unique<conditionNode> (conditionType::NEQ_COND, std::move(nodo1),std::move(nodo2));
        }
        else {throw std::logic_error("algo fallo en parseCondition");}
    }

    std::unique_ptr<ASTNode> parseBlock()
    {
        if (peekToken()!=LBRACE_TOKEN){throw std::logic_error("error parseBlock");}
        consume();
        std::vector<std::unique_ptr<ASTNode>> stats{};

        while (peekToken() != RBRACE_TOKEN && m_pos<m_vecTokens.size())
        {
            if (peekToken() == SEMICOLON_TOKEN || peekToken() == EOF_TOKEN)
            {
                consume();
                continue;
            }
            stats.push_back(parseStatements());
        }

        if (peekToken()!=RBRACE_TOKEN){throw std::logic_error("error parseBlock");}
        consume();

        return std::make_unique<blockNode> (std::move(stats));
    }

    std::unique_ptr<ASTNode> parseIf()
    {
        if (peekToken() == ELSE_TOKEN)
        {
            consume();
            auto nodo = parseBlock();
            return std::make_unique<instructionNode> (instructions::EJECUTAR, std::move(nodo));
        }

        consume();
        if (peekToken() != LPAREN_TOKEN){throw std::logic_error("Luego de un if o elif va un (");}
        consume();
        auto cond = parseCondition();
        auto bloque = parseBlock();

        if (peekToken() == ELSE_TOKEN || peekToken() == ELIF_TOKEN)
        {
            auto predicado = parseIf();
            return std::make_unique<ifNode> (std::move(cond), std::move(bloque), std::move(predicado));
        }
        else 
        {
            return std::make_unique<ifNode> (std::move(cond), std::move(bloque));
        }


    }

    std::unique_ptr<ASTNode> parseStatements()
    {
        if (peekToken() == DECLARATION_TOKEN)
        {
            return parseDeclaration();
        }
        else if (peekToken() == PRINT_TOKEN)
        {
            return parsePrint();
        }
        else if (peekToken() == RETURN_TOKEN)
        {
            return parseReturn();
        }
        else if (peekToken() == IDENTIFIER_TOKEN)
        {
            return parseReassign();
        }
        else if (peekToken() == IF_TOKEN)
        {
            return parseIf();
        }
 
        else{ throw std::logic_error("error en parseStatements.");}
    }


    void globalParse()
    {
        while (m_pos<m_vecTokens.size())
        {
            if (peekToken() == SEMICOLON_TOKEN || peekToken() == EOF_TOKEN)
            {
                consume();
                continue;
            }
            m_statements.push_back(parseStatements());
        }
    }

    std::vector<std::unique_ptr<ASTNode>> getStatements()
    {
        return std::move(m_statements);
    }

};
