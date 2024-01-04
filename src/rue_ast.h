#ifndef RUE_AST_H
#define RUE_AST_H

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace Rue
{

class ExprAST
{
    void *type;

  public:
    virtual ~ExprAST() = default;
};

class NumLitExprAST : public ExprAST
{
    std::variant<double, int> val;

  public:
    NumLitExprAST(double val) : val(val)
    {
    }
};

class VarExprAST : public ExprAST
{
    std::string name;

  public:
    VarExprAST(std::string const &name) : name(name)
    {
    }
};

class BinExprAST : public ExprAST
{
    char op;
    std::unique_ptr<ExprAST> lhs, rhs;

  public:
    BinExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs)
        : op(op), lhs(std::move(lhs)), rhs(std::move(rhs))
    {
    }
};

class ExprTerminatorAST
{
  public:
    ExprTerminatorAST()
    {
    }
};

class CallExprAST : public ExprAST
{
    std::string callee;
    std::vector<std::unique_ptr<ExprAST>> args;

  public:
    CallExprAST(std::string const &callee, std::vector<std::unique_ptr<ExprAST>> args)
        : callee(callee), args(std::move(args))
    {
    }
};

class PrototypeAST
{
    std::string name;
    std::vector<std::string> args;

  public:
    PrototypeAST(std::string const &name, std::vector<std::string> args) : name(name), args(std::move(args))
    {
    }

    const std::string &getName() const
    {
        return name;
    }
};

class FunctionAST
{
    std::unique_ptr<PrototypeAST> proto;
    std::unique_ptr<ExprAST> body;

  public:
    FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body)
        : proto(std::move(proto)), body(std::move(body))
    {
    }
};

} // namespace Rue

#endif // RUE_AST_H
