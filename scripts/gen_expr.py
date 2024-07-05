from argparse import ArgumentParser
from typing import Dict, Sequence
from pathlib import Path


EXPR_TMPL = """

#include "Token.hh"
#include <memory>


struct {base_name} {
  virtual void f() = 0;
};

{sub_types}

"""

TYPE_TMPL = """

struct {class_name} : {base_name} {{
  void f() override {{}}

  {fields}

  {class_name}() {{
    {inits}
  }}
}}

"""

TYPE_FIELD_TMPL = "std::unique_ptr<{field_type}> {field_name};"
INIT_TMPL = "std::unique_ptr<{field_type}> {field_name} = {field_name};"

def define_type(base_name, class_name, field_list):
  fields = "\n\t".join([
    TYPE_FIELD_TMPL.format(
      field_type=field.split()[0], field_name=field.split()[1]
    )
    for field in field_list
  ])
  inits = "\n\t\t".join([
    TYPE_FIELD_TMPL.format(
      field_type=field.split()[0], field_name=field.split()[1]
    )
    for field in field_list
  ])
  return TYPE_TMPL.format(
    class_name=class_name,
    base_name=base_name,
    fields=fields,
    inits=inits
  )


def define_ast(output_dir, base_name, types: Sequence[Dict]):
    filepath = Path(output_dir, base_name + ".hh")
    for k, v in types.items():
      sub_classes = "".join([define_type(sub_type, )])
    impl = EXPR_TMPL.format(
      base_name=base_name,
    )

    with open(filepath, 'w') as output_file:
      output_file.write(impl)


if __name__=="__main__":
  arg_parser = ArgumentParser(
    prog='Generate Expr.hh',
    description='Script to generate Expr.hh'
  )
  arg_parser.add_argument('-o', '--output', action='store', type=str)
  args = arg_parser.parse_args()
  output_dir = args.output

  define_ast(output_dir, "Expr", [
      "Binary   : Expr left, Token operator, Expr right",
      "Grouping : Expr expression",
      "Literal  : Object value",
      "Unary    : Token operator, Expr right"
  ])