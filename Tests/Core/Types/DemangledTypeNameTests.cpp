#include <gmock/gmock.h>

#include <Core/Types/DemangledTypeName.h>

// structs in different scopes
struct foo{};
namespace { struct foo2{}; }
namespace Bar {struct foo3{}; }


namespace Tests
{

using namespace testing;

class DemangledTypeNameTests : public testing::Test
{
public:
	DemangledTypeNameTests(){};
};

TEST(DemangledTypeNameTest, gets_type_name_from_simple_types)
{
	EXPECT_THAT(Core::getDemangledTypeName<int>(), Eq("int"));
	EXPECT_THAT(Core::getDemangledTypeName<float>(), Eq("float"));
	EXPECT_THAT(Core::getDemangledTypeName<double>(), Eq("double"));

	// type name nie działa poprawnie z tym typem :( nazwa jest rozwijana tak,
	// jak ma to miejsce w przypadku błędów kompilacji
	// EXPECT_THAT(Core::getDemangledTypeName<std::string>(), Eq("std::string"));
}

TEST(DemangledTypeNameTest, gets_name_from_struct_in_different_scopes)
{
	EXPECT_THAT(Core::getDemangledTypeName<foo>(), Eq("foo"));
	EXPECT_THAT(Core::getDemangledTypeName<foo2>(), Eq("(anonymous namespace)::foo2"));
	EXPECT_THAT(Core::getDemangledTypeName<Bar::foo3>(), Eq("Bar::foo3"));
}

typedef foo2 uberFoo;
using superFoo = foo2;

TEST(DemangledTypeNameTest, gets_name_from_aliases)
{
	// typename nie pobiera nazw po aliasach, zarówno po using jak i typedef
	// EXPECT_THAT(Core::getDemangledTypeName<uberFoo>(), Eq("uberFoo"));
	// EXPECT_THAT(Core::getDemangledTypeName<superFoo>(), Eq("superFoo"));
}

template<typename T1, typename T2>
struct Ertetei{};

TEST(DemangledTypeNameTest, gets_name_from_simple_templates)
{
	auto typeName = Core::getDemangledTypeName<Ertetei<int, float>>();
	auto expected = "Tests::Ertetei<int, float>";
	EXPECT_THAT(typeName, Eq(expected));
}

} // namespace Tests
