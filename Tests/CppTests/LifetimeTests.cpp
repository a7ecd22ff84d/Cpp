#include <string>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Testy mają na celu sprawdzenie, kiedy obiekty są kopiowane, przenoszone,
// niszczone itp.

namespace Tests
{
using namespace testing;

std::vector<std::string> operations;

class CC
{
public:
	CC(const std::string& name) : name(name)
	{
		operations.emplace_back("Constructor: " + name);
	}

	~CC()
	{
		operations.emplace_back("Destructor: " + name);
	}

	CC(const CC& other)
	{
		name = other.name;
		operations.emplace_back("Copy constructor: " + name);
	}

	CC(CC&& other)
	{
		name = other.name;
		other.name = "no_value";
		operations.emplace_back("Move constructor: " + name);
	}

	void operator=(const CC& other)
	{
		name = other.name;
		operations.emplace_back("Copy asignment: " + name);
	}

	void operator=(CC&& other)
	{
		name = other.name;
		other.name = "no_value";
		operations.emplace_back("Move asignment: " + name);
	}

	void useConstFunction() const
	{
		operations.emplace_back("UseConstFunction: " + name);
	}

	void useNonConstFunction() const
	{
		operations.emplace_back("UseNonConstFunction: " + name);
	}

private:
	std::string name;
};

//////////////////////////////////////////////////////////////////////////////

using Operation = void(void);

template<typename... Args>
void runTest(Operation op, Args... expectOperaions)
{
	operations.clear();
	op();
	EXPECT_THAT(operations, ElementsAre(std::forward<Args>(expectOperaions)...));
}

//////////////////////////////////////////////////////////////////////////////

TEST(LifetimeTests, create_variables)
{
	auto simpleCreate = []() { auto c1 = CC("first"); };
	runTest(simpleCreate, "Constructor: first", "Destructor: first");

	auto createReference = []() { const auto& c2 = CC("second"); };
	runTest(createReference, "Constructor: second", "Destructor: second");

	runTest(
		[]() {
			auto c1 = CC("first");
			auto c2 = c1;
		},
		"Constructor: first",
		"Copy constructor: first",
		"Destructor: first",
		"Destructor: first");

	runTest(
		[]() {
			auto c1 = CC("first");
			auto c2 = std::move(c1);
		},
		"Constructor: first",
		"Move constructor: first",
		"Destructor: first",
		"Destructor: no_value");

	runTest(
		[]() {
			auto c1 = CC("first");
			auto c2 = CC("second");
			c2 = std::move(c1);
		},
		"Constructor: first",
		"Constructor: second",
		"Move asignment: first",
		"Destructor: first",
		"Destructor: no_value");
}

TEST(LifetimeTests, push_vs_emplace)
{
	runTest(
		[]() {
			std::vector<CC> v;
			v.push_back(CC("first"));
		},
		"Constructor: first",
		"Move constructor: first",
		"Destructor: no_value",
		"Destructor: first");

	runTest(
		[]() {
			// heh, nie ma to jak się zorientować,
			// że cały czas źle używałem emplace back :D
			std::vector<CC> v;
			v.emplace_back("first");
		},
		"Constructor: first",
		"Destructor: first");
}

TEST(LifetimeTests, get_value_from_container)
{
	runTest(
		[]() {
			std::vector<CC> v;
			v.emplace_back("first");
			auto item = v[0];
		},
		"Constructor: first",
		"Copy constructor: first",
		"Destructor: first",
		"Destructor: first");

	runTest(
		[]() {
			std::vector<CC> v;
			v.emplace_back("first");
			const auto& item = v[0];
			item.useConstFunction();
		},
		"Constructor: first",
		"UseConstFunction: first",
		"Destructor: first");
}

TEST(LifetimeTests, get_non_const_container_from_container)
{
	runTest(
		[]() {
			std::vector<std::vector<CC>> v;
			v.emplace_back(std::vector<CC>());
			v[0].emplace_back("first");

			auto& col = v[0];
			col[0].useNonConstFunction();
		},
		"Constructor: first",
		"UseNonConstFunction: first",
		"Destructor: first");
}

} // namespace Tests