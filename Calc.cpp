#include <iostream>     //I/o入出力ストリーム
#include <string>       //文字列
#include <stack>        //LIFOスタック
#include <vector>       //可変長配列
#include <cstdlib>      //雑多な関数群　atoi専用
#include <stdexcept>    //標準例外クラス

using namespace std;

class Token {
    public:
        enum Type {
            NIL = 0,
            ADD = 1000,
            SUB,
            MULT,
            DIV,
            VALUE= 2222
        };

        void SetType(const Token::Type& op) { this->m_type = op; };
        Token::Type GetType(void) const { return (this->m_type); };

        void SetValue(const int v) { this->m_value = v; };
        int GetValue(void) const { return (this->m_value); };

        void Clear()
        {
            this->SetType(NIL);
            this->SetValue(0.0f);
        };

        Token() :
            m_type(NIL), m_value(0.0f)
        {
        }

    private:
        Token::Type m_type;
        int m_value;

};

vector<Token> Rex (const string& tmp)
{
    Token tk;
    vector<Token> ret;

    //文字解析など
    for ( int i = 0; i < tmp.length(); ++i) {
        if (tmp[i] == '+') {
            tk.Clear();
            tk.SetType(Token::ADD);
            ret.push_back(tk);
            continue;
        }
        if (tmp[i] == '-') {
            tk.Clear();
            tk.SetType(Token::SUB);
            ret.push_back(tk);
            continue;
        }
        else if (tmp[i] == '*') {
            tk.Clear();
            tk.SetType(Token::MULT);
            ret.push_back(tk);
            continue;
        }
        else if (tmp[i] == '/') {
            tk.Clear();
            tk.SetType(Token::DIV);
            ret.push_back(tk);
            continue;
        }

        //数値データの処理
        if (tmp[i] >= '0' && tmp[i] <= '9') {
            int j = i;

            for ( j = i; j < tmp.length(); ++j ) {
                if (tmp[j] >= '0' && tmp[j] <= '9') {
                    continue;
                }
                else {
                    break;
                }
            }

            char* nStr = new char[j-i + 2];
            for ( int k = 0; k < j-i; ++k) {
                nStr[k] = tmp[i+k];
            }
            nStr[j-i+1] = '\0';

            tk.Clear();
            tk.SetType(Token::VALUE);
            tk.SetValue(atoi(nStr));
            ret.push_back(tk);

            delete (nStr);
            nStr = 0;

            i = j - 1;
            continue;
        }
    }

    return (ret);
}

void Calc(const string& tmp)
{
    vector<Token> listRex;
    stack<Token> stackClac;

    //文字列分解
    listRex = Rex(tmp);

    stack<Token> stack0p;
    stack<Token> stackValue;

    for (auto itr = listRex.begin(); itr != listRex.end(); ++itr) {
        if (itr -> GetType() != Token::VALUE) {
            stack0p.push(*itr);
            continue;
        }
        else {
            stackValue.push(*itr);
            continue;
        }
    }

    while (!stack0p.empty()) {
        Token t = stack0p.top();
        stack0p.pop();

        if(t.GetType() == Token::ADD) {
            Token n1, n2;
            n1 = stackValue.top();
            stackValue.pop();
            n2 = stackValue.top();
            stackValue.pop();

            t.SetType(Token::VALUE);
            t.SetValue(n2.GetValue() + n1.GetValue());
            stackValue.push(t);
            continue;
        }
        else if (t.GetType() == Token::SUB) {
                        Token n1, n2;
            n1 = stackValue.top();
            stackValue.pop();
            n2 = stackValue.top();
            stackValue.pop();

            t.SetType(Token::VALUE);
            t.SetValue(n2.GetValue() + n1.GetValue());
            stackValue.push(t);
            continue;
        }
        else if (t.GetType() == Token::MULT) {
                        Token n1, n2;
            n1 = stackValue.top();
            stackValue.pop();
            n2 = stackValue.top();
            stackValue.pop();

            t.SetType(Token::VALUE);
            t.SetValue(n2.GetValue() + n1.GetValue());
            stackValue.push(t);
            continue;
        }
        else if (t.GetType() == Token::DIV) {
                        Token n1, n2;
            n1 = stackValue.top();
            stackValue.pop();
            n2 = stackValue.top();
            stackValue.pop();

            if (n1.GetValue() == 0 || n2.GetValue() == 0) {
                throw std::runtime_error("an 0 division occurred.");
            }

            t.SetType(Token::VALUE);
            t.SetValue(n2.GetValue() + n1.GetValue());
            stackValue.push(t);
            continue;
        }
    }

    if (!stackValue.empty()) {
        cout << "RESULT : " << stackValue.top().GetValue() << endl;
    }
    else {
        throw std::runtime_error("Inputed expr is unjust.");
    }

    return;
}

int main (int argc, char* argv[])
{
    string tmp;
    cout << "Calculation" << endl;
    cout << "Inputing a 'quit' or 'exit' will terminate." << endl;
    while(true) {
        tmp = "";
        cin >> tmp;
        if ( tmp == "quit" || tmp == "exit") {
            break;
        }

        try {
            Calc(tmp);
        }
        catch (const std::runtime_error& e) {
            cerr << e.what() << endl;
            break;
        }
        catch(...) {
            cerr << "Unexpected error." << endl;
            break;
        }
    }

    cout << "Quit." << endl;
    return (0);
}