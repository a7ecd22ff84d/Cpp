import argparse
import os
import yaml

from PyTools.Generator.EntityGenerator import EntityGenerator


# TODO: move to separate file + tests
def snake_case_to_lower_camel_case(text: str) -> str:
    temp = text.split('_')
    res = temp[0] + ''.join(ele.title() for ele in temp[1:])
    return res


def snake_case_to_camel_case(text: str) -> str:
    lcc_text = snake_case_to_lower_camel_case(text)
    return lcc_text[0].upper() + lcc_text[1:]


def main():
    parser = argparse.ArgumentParser(description='Automatic file generation')
    parser.add_argument('source_file', type=str, help='Patch to entity definition file')
    parser.add_argument('output_dir', type=str, help='Directory for output files')
    parser.add_argument('include_dir', type=str, help='Root directory for include path')
    parser.add_argument('--namespace', dest='namespace', type=str, help='Entity namespace')

    generateEntity(parser.parse_args())


def generateEntity(args):
    with open(args.source_file) as file:
        table_definition = yaml.safe_load(file.read())

    generator = EntityGenerator(table_definition)

    output_file_name = snake_case_to_camel_case(table_definition['name'])
    warning = "// This file is auto generated and should not be modified.\n"

    with open('{}/{}.h'.format(args.output_dir, output_file_name), 'w') as header_file:
        header_file.write(warning)
        header_file.write(generator.create_header(args.namespace))

    with open('{}/{}.cpp'.format(args.output_dir, output_file_name), 'w') as source_file:
        source_file.write(warning)
        include_dir = os.path.relpath(args.output_dir, args.include_dir)
        source_file.write(generator.create_source(args.namespace, include_dir))


if __name__ == "__main__":
    main()
