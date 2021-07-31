import unittest
import yaml

from PyTools.Generator.EntityGenerator import EntityGenerator


class EntityGeneratorTests(unittest.TestCase):

    def test_create_entity_with_one_field(self):
        file_definition = {"table_name": "single_field_table",
                           "fields": [{"name": "id", "type": "int"}]}

        expected_header = '''
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

        expected_source = '''
#include <SingleFieldTable.h>

void SingleFieldTable::setId(int id) { this->id = id; }
int SingleFieldTable::getId() const { return id; }
'''

        generator = EntityGenerator(file_definition)
        self.assertEqual(generator.create_header(), expected_header)
        self.assertEqual(generator.create_source(), expected_source)

    def test_create_entity_with_namespace(self):
        file_definition = {"table_name": "single_field_table",
                           "fields": [{"name": "id", "type": "int"}]}

        expected_header = '''
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

        expected_source = '''
#include <SingleFieldTable.h>

namespace Entities{

void SingleFieldTable::setId(int id) { this->id = id; }
int SingleFieldTable::getId() const { return id; }

}
'''

        generator = EntityGenerator(file_definition)
        self.assertEqual(generator.create_header(namespace='Entities'), expected_header)
        self.assertEqual(generator.create_source(namespace='Entities'), expected_source)

    def test_create_entity_with_multiple_fields(self):
        file_definition = {"table_name": "single_field_table",
                           "fields": [{"name": "id", "type": "int"},
                                      {"name": "double_field", "type": "double"}]}

        expected_header = '''
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

        expected_source = '''
#include <SingleFieldTable.h>

void SingleFieldTable::setId(int id) { this->id = id; }
int SingleFieldTable::getId() const { return id; }

void SingleFieldTable::setDoubleField(double doubleField) { this->doubleField = doubleField; }
double SingleFieldTable::getDoubleField() const { return doubleField; }
'''

        generator = EntityGenerator(file_definition)
        self.assertEqual(generator.create_header(), expected_header)
        self.assertEqual(generator.create_source(), expected_source)

    def test_create_source_with_string_field(self):
        file_definition = {"table_name": "single_field_table",
                           "fields": [{"name": "textField", "type": "text", 'length': "20"}]}

        expected_header = '''
#ifndef CPP_SINGLEFIELDTABLE_H
#define CPP_SINGLEFIELDTABLE_H

#include <string>

class SingleFieldTable {
public:
    void setTextField(const std::string& textField);
    std::string getTextField() const;

private:
    std::string textField;
};
#endif'''

        expected_source = '''
#include <SingleFieldTable.h>

void SingleFieldTable::setTextField(const std::string& textField) { this->textField = textField; }
std::string SingleFieldTable::getTextField() const { return textField; }
'''

        generator = EntityGenerator(file_definition)
        self.assertEqual(generator.create_header(), expected_header)
        self.assertEqual(generator.create_source(), expected_source)


if __name__ == '__main__':
    unittest.main()
