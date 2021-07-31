from mako.template import Template


# TODO: move to separate file + tests
def snake_case_to_lower_camel_case(text: str) -> str:
    temp = text.split('_')
    res = temp[0] + ''.join(ele.title() for ele in temp[1:])
    return res


def snake_case_to_camel_case(text: str) -> str:
    lcc_text = snake_case_to_lower_camel_case(text)
    return lcc_text[0].upper() + lcc_text[1:]


# TODO:
#   support for date
#   support for optionals
#   relative patch when creating main include in source file
#   default field values
#   copy, move constructor
#   comparison operator

class EntityGenerator:
    def __init__(self, file_definition: dict):
        self.header_template = Template(filename='PyTools/Generator/Templates/EntityHeaderTemplate.txt')
        self.source_template = Template(filename='PyTools/Generator/Templates/EntitySourceTemplate.txt')
        self.type_conversion_dict = {
            'int': {'cpp_type': 'int', 'const_ref_set': False, 'header_file': None},
            'double': {'cpp_type': 'double', 'const_ref_set': False, 'header_file': None},
            'text': {'cpp_type': 'std::string', 'const_ref_set': True, 'header_file': 'string'},
        }

        self.class_name = snake_case_to_camel_case(file_definition['table_name'])
        self.fields = self._parse_fields(file_definition)

    def _parse_fields(self, file_definition: dict) -> list:
        result = []

        for field in file_definition['fields']:
            type_info = {'name': snake_case_to_lower_camel_case(field['name'])}
            type_info.update(self.type_conversion_dict[field['type']])
            result.append(type_info)

        return result

    def create_header(self, namespace: str = '') -> str:
        if not namespace:
            namespace = ''

        header_files = []
        for field in self.fields:
            if not field['header_file'] is None:
                header_files.append(field['header_file'])

        return self.header_template.render(
            class_name=self.class_name,
            namespace_name=namespace,
            header_files=header_files,
            fields=self.fields
        )

    def create_source(self, namespace: str = '') -> str:
        if not namespace:
            namespace = ''

        return self.source_template.render(
            header_file_path="{}.h".format(self.class_name),
            namespace_name=namespace,
            class_name=self.class_name,
            fields=self.fields
        )

