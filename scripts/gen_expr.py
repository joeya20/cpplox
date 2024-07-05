from argparse import ArgumentParser
from typing import Dict
from pathlib import Path


EXPR_TMPL = """
#pragma once

#include "Token.hh"
#include <memory>


struct {base_name} {{
  virtual void f() = 0;
}};

{sub_exprs}

"""

SUB_EXPR_TMPL = """
struct {class_name}{base_name} : {base_name} {{
  void f() override {{}}

  {fields}

  {class_name}{base_name}({args}) {{
    {inits}
  }}
}};

"""
ARGS_TMPL = "std::unique_ptr<{field_type}>&& {field_name}"
TYPE_FIELD_TMPL = "std::unique_ptr<{field_type}> {field_name};"
INIT_TMPL = "this->{field_name} = std::move({field_name});"


def define_type(base_name, class_name, field_list):
  fields = "\n\t".join([
    TYPE_FIELD_TMPL.format(
      field_type=field.split()[0], field_name=field.split()[1]
    )
    for field in field_list
  ])
  inits = "\n\t\t".join([
    INIT_TMPL.format(
      field_type=field.split()[0], field_name=field.split()[1]
    )
    for field in field_list
  ])
  args = ", ".join([
    ARGS_TMPL.format(
      field_type=field.split()[0], field_name=field.split()[1]
    )
    for field in field_list
  ])
  return SUB_EXPR_TMPL.format(
    class_name=class_name,
    base_name=base_name,
    fields=fields,
    args=args,
    inits=inits
  )


def define_ast(output_dir, base_name, sub_exprs: Dict):
    filepath = Path(output_dir, base_name + ".hh")
    sub_exprs_str = ""
    for sub_expr_name, fields in sub_exprs.items():
      sub_exprs_str += "".join([define_type(base_name, sub_expr_name, fields)])
    impl = EXPR_TMPL.format(
      base_name=base_name,
      sub_exprs=sub_exprs_str
    )

    with open(filepath, 'w') as output_file:
      output_file.write(impl)


if __name__ == "__main__":
  arg_parser = ArgumentParser(
    prog='Generate Expr.hh',
    description='Script to generate Expr.hh'
  )
  arg_parser.add_argument('output_dir', action='store', type=str)
  args = arg_parser.parse_args()
  output_dir = args.output_dir

  define_ast(output_dir, "Expr", {
      "Binary":   ["Expr left", "Token op", "Expr right"],
      "Grouping": ["Expr expression"],
      "Unary":    ["Token op", "Expr right"],
      "FloatLit":  ["float value"],
      "StringLit":  ["std::string value"]
  })
