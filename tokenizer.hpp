#include<fstream>
#include<vector>
#include<unordered_map>



enum tokenType
{
    EOF_TOKEN,


    STRING_TOKEN,
    STR_TYPE_TOKEN,
    DECLARATION_TOKEN,
    INT_TYPE_TOKEN,
    IDENTIFIER_TOKEN,
    NUM_TOKEN,
    PRINT_TOKEN,
    RETURN_TOKEN,
    IF_TOKEN,
    ELIF_TOKEN,
    ELSE_TOKEN,
    WHILE_TOKEN,


    EQ_TOKEN,
    NEQ_TOKEN,


    ASSIGN_TOKEN,
    SEMICOLON_TOKEN,
    PLUS_TOKEN,
    MUL_TOKEN,
    DIV_TOKEN,
    MINUS_TOKEN,
    LPAREN_TOKEN,
    RPAREN_TOKEN,
    LBRACE_TOKEN,
    RBRACE_TOKEN,

};

struct Token
{
    tokenType type{};
    std::string val{};
};


class Tokenizer
{
private:
    std::ifstream m_file{};
    std::string m_line{};
    std::string m_palabra{};

    std::vector<Token> m_vectorTokens{};
    size_t m_pos{};
    std::unordered_map<std::string, tokenType> m_mapWords
    {
        {"dejar", DECLARATION_TOKEN},
        {"int", INT_TYPE_TOKEN},
        {"consola", PRINT_TOKEN},
        {"devuelva", RETURN_TOKEN},
        {"str", STR_TYPE_TOKEN},
        {"si", IF_TOKEN},
        {"ysi", ELIF_TOKEN},
        {"sino", ELSE_TOKEN},
        {"mientras", WHILE_TOKEN},


    };

    std::unordered_map<std::string, tokenType> m_mapDobleSimbols
    {
        {"==", EQ_TOKEN},
        {"!=", NEQ_TOKEN},


    };

    std::unordered_map<char, tokenType> m_mapSimbols
    {
        {'=', ASSIGN_TOKEN},
        {';', SEMICOLON_TOKEN},
        {'+', PLUS_TOKEN},
        {'*', MUL_TOKEN},
        {'/', DIV_TOKEN},
        {'-', MINUS_TOKEN},
        {'(', LPAREN_TOKEN},
        {')', RPAREN_TOKEN},
        {'}', RBRACE_TOKEN},
        {'{', LBRACE_TOKEN},

    };



public:
    Tokenizer(std::string locacion)
    {
        m_file.open(locacion);
        if (!m_file)
        {
            throw std::logic_error("La file no tiene nada o no se dio.");
        }
    }

    char getChar(size_t optional = 0)
    {
        if (m_pos+optional< m_line.length())
        {
            return m_line.at(m_pos+optional);
        }
        return '\0';
    }

    void consume()
    {
        m_palabra.push_back(getChar());
        m_pos+=1;
    }
    void next(size_t optional = 1)
    {
        m_pos+=optional;
    }

    //Booleanos

    bool isDobleSimbol()
    {
        char char1 = getChar();
        char char2 = getChar(1);

        std::string s{char1, char2};
            
        if (m_mapDobleSimbols.find(s) != m_mapDobleSimbols.end())
        {
            return true;
        }
        return false;
    }

    bool isSimbol()
    {
        char char1 = getChar();
            
        if (m_mapSimbols.find(char1) != m_mapSimbols.end())
        {
            return true;
        }
        return false;
    }


    //Booleanos


    //readings
    //readings

    Token readNumber()
    {
        m_palabra.clear();
        consume();
        while (std::isdigit(getChar()) && m_pos<m_line.length())
        {
            consume();
        }
        return Token{NUM_TOKEN, m_palabra};
    }

    Token readString()
    {
        m_palabra.clear();
        next();
        while (m_pos<m_line.length() && getChar()!='"')
        {
            consume();
        }
        next();
        return Token{STRING_TOKEN, m_palabra};
    }

    Token readWord()
    {
        m_palabra.clear();
        consume();
        while (std::isalpha(getChar()) && m_pos<m_line.length())
        {
            consume();
        }

        if (m_mapWords.find(m_palabra) != m_mapWords.end())
        {
            auto t = m_mapWords.find(m_palabra)->second;
            return Token{t, m_palabra};
        }
        return Token{IDENTIFIER_TOKEN, m_palabra};
    }


    Token readDobleSimbol()
    {
        char char1 = getChar();
        char char2 = getChar(1);
        next(2);
        std::string s{char1, char2};
            
        if (m_mapDobleSimbols.find(s) != m_mapDobleSimbols.end())
        {
            auto t = m_mapDobleSimbols.find(s)->second;
            return Token{t, s};
        }
        else {throw std::logic_error("esto no deberia pasar!");}
    }

    Token readSimbol()
    {
        char char1 = getChar();
        std::string s{char1};
        next();
        if (m_mapSimbols.find(char1) != m_mapSimbols.end())
        {
            auto t = m_mapSimbols.find(char1)->second;
            return Token{t, s};
        }
        else {throw std::logic_error("esto no deberia pasar!");}
    }




    void tokenize()
    {
        while (std::getline(m_file, m_line))
        {
            m_pos=0;
            while (m_pos<m_line.length())
            {
                if (std::isspace(getChar()))
                {
                    next();
                    continue;
                }
                else if (std::isdigit(getChar()))
                {
                    m_vectorTokens.push_back(readNumber());
                }
                else if (getChar() == '"')
                {
                    m_vectorTokens.push_back(readString());
                }
                else if (std::isalpha(getChar()))
                {
                    m_vectorTokens.push_back(readWord());
                }
                else if (isDobleSimbol())
                {
                    m_vectorTokens.push_back(readDobleSimbol());
                }
                else if (isSimbol())
                {
                    m_vectorTokens.push_back(readSimbol());
                }
                else 
                {
                    throw std::logic_error("en algo la cagaste");
                }
            }
        }
    }


    std::vector<Token> getTokens()
    {
        return m_vectorTokens;
    }

};
