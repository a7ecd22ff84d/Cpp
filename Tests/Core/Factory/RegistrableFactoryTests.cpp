#include <memory>
#include <stdexcept>
#include <vector>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Core/Factory/RegistrableFactory.h"

namespace Tests
{
using namespace testing;

// clang-format off
struct IFoo
{
	virtual ~IFoo(){}
	virtual int getValue() const = 0;
};

struct FooImpl :public IFoo
{
	virtual int getValue() const final {return 1;};
};

struct ConstructibeFoo : public IFoo
{
	ConstructibeFoo(int value) : value(value){}
	virtual int getValue() const final {return value;};

private:
	int value;
};

// clang-format on

TEST(RegistrableFactoryTests, register_by_type_and_create)
{
	Factory::RegistrableFactory<IFoo> fooFactory;
	fooFactory.registerType<FooImpl>("fooImpl");

	auto item = fooFactory.create("fooImpl");
	ASSERT_THAT(item->getValue(), Eq(1));
}

TEST(RegistrableFactoryTests, register_by_creator_and_create)
{
	Factory::RegistrableFactory<IFoo> fooFactory;

	fooFactory.registerType("contructibleFoo", []() -> std::unique_ptr<IFoo> {
		return std::make_unique<ConstructibeFoo>(3);
	});

	auto item = fooFactory.create("contructibleFoo");
	ASSERT_THAT(item->getValue(), Eq(3));
}

TEST(RegistrableFactoryTests, throw_error_when_type_is_not_registered)
{
	Factory::RegistrableFactory<IFoo> fooFactory;

	try
	{
		auto item = fooFactory.create("nonExistingFoo");
		FAIL() << "Logic error expected";
	}
	catch (std::logic_error& e)
	{
		ASSERT_STREQ(e.what(), "Type 'nonExistingFoo' is not registered");
	}
}

TEST(RegistrableFactoryTests, throw_error_when_type_is_registered_for_the_second_time)
{
	Factory::RegistrableFactory<IFoo> fooFactory;
	fooFactory.registerType<FooImpl>("fooImpl");

	try
	{
		fooFactory.registerType<FooImpl>("fooImpl");
		FAIL() << "Logic error expected";
	}
	catch (std::logic_error& e)
	{
		ASSERT_STREQ(e.what(), "Type 'fooImpl' is already registered");
	}

	try
	{
		fooFactory.registerType("fooImpl", []() -> std::unique_ptr<IFoo> {
			return std::make_unique<FooImpl>();
		});

		FAIL() << "Logic error expected";
	}
	catch (std::logic_error& e)
	{
		ASSERT_STREQ(e.what(), "Type 'fooImpl' is already registered");
	}
}

// TEST(RegistrableFactoryTests, register_wrong_type)
// {
// 	Factory::RegistrableFactory<IFoo> fooFactory;
// 	fooFactory.registerType<int>("fooImpl");
// }

} // namespace Tests
