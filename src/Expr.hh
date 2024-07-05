
#pragma once

#include "Token.hh"
#include <memory>


struct Expr {
  virtual void f() = 0;
};


struct BinaryExpr : Expr {
  void f() override {}

  std::unique_ptr<Expr> left;
	std::unique_ptr<Token> op;
	std::unique_ptr<Expr> right;

  BinaryExpr(std::unique_ptr<Expr>&& left, std::unique_ptr<Token>&& op, std::unique_ptr<Expr>&& right) {
    this->left = std::move(left);
		this->op = std::move(op);
		this->right = std::move(right);
  }
};


struct GroupingExpr : Expr {
  void f() override {}

  std::unique_ptr<Expr> expression;

  GroupingExpr(std::unique_ptr<Expr>&& expression) {
    this->expression = std::move(expression);
  }
};


struct UnaryExpr : Expr {
  void f() override {}

  std::unique_ptr<Token> op;
	std::unique_ptr<Expr> right;

  UnaryExpr(std::unique_ptr<Token>&& op, std::unique_ptr<Expr>&& right) {
    this->op = std::move(op);
		this->right = std::move(right);
  }
};


struct FloatLitExpr : Expr {
  void f() override {}

  std::unique_ptr<float> value;

  FloatLitExpr(std::unique_ptr<float>&& value) {
    this->value = std::move(value);
  }
};


struct StringLitExpr : Expr {
  void f() override {}

  std::unique_ptr<std::string> value;

  StringLitExpr(std::unique_ptr<std::string>&& value) {
    this->value = std::move(value);
  }
};



