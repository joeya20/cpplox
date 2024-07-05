#include "Token.hh"
#include <memory>


struct Expr {
  virtual void f() = 0;
};


struct BinaryExpr : Expr {
  void f() override {}

  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;

  BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) :
    left(std::move(right)), op(op), right(std::move(right)) {};

};


struct UnaryExpr : Expr {
  void f() override {}

  std::unique_ptr<Token> op;
  std::unique_ptr<Expr> operand;

  UnaryExpr(Expr operand, Token op);
};
