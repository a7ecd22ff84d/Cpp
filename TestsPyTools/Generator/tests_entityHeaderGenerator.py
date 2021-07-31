import unittest
import yaml
from PyTools.Generator.entityHeaderGenerator import EntityHeaderGenerator


class EntityHeaderGeneratorTests(unittest.TestCase):

    def test_create_header_with_one_field(self):
        file_definition = {"table_name": "single_field_table",
                           "fields": [{"name": "id", "type": "int"}]}

        output = '''
#ifndef CPP_SINGLEFIELDTABLE_H
#define CPP_SINGLEFIELDTABLE_H
class SingleFieldTable {
public:
    void setId(int id);
    int getId() const;

private:
    int id;
};
#endif'''

        generator = EntityHeaderGenerator(file_definition)
        result = generator.create()
        self.assertEqual(result, output)

    def test_create_header_with_namespace(self):
        file_definition = {"table_name": "single_field_table",
                           "fields": [{"name": "id", "type": "int"}]}

        output = '''
#ifndef CPP_SINGLEFIELDTABLE_H
#define CPP_SINGLEFIELDTABLE_H
namespace Entities{
class SingleFieldTable {
public:
    void setId(int id);
    int getId() const;

private:
    int id;
};
}
#endif'''

        generator = EntityHeaderGenerator(file_definition)
        result = generator.create(namespace='Entities')
        self.assertEqual(result, output)

    def test_create_header_with_multiple_fields(self):
        file_definition = {"table_name": "single_field_table",
                           "fields": [{"name": "id", "type": "int"},
                                      {"name": "double_field", "type": "double"}]}

        output = '''
#ifndef CPP_SINGLEFIELDTABLE_H
#define CPP_SINGLEFIELDTABLE_H
class SingleFieldTable {
public:
    void setId(int id);
    int getId() const;

    void setDoubleField(double doubleField);
    double getDoubleField() const;

private:
    int id;
    double doubleField;
};
#endif'''

        generator = EntityHeaderGenerator(file_definition)
        result = generator.create()
        self.assertEqual(result, output)

if __name__ == '__main__':
    unittest.main()
