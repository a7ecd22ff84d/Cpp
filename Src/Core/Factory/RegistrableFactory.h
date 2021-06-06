#ifndef __REGISTRABLE_FACTORY_H
#define __REGISTRABLE_FACTORY_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <type_traits>

#include "fmt/core.h"

namespace Factory
{
template<typename T>
class RegistrableFactory
{
	// function pointer does not work when lambda creator captures something
	// using CreatorFunc = std::unique_ptr<T> (*)();
	using CreatorFunc = std::function< std::unique_ptr<T>()>;

public:
	void registerType(std::string_view name, CreatorFunc creatorFunc)
	{
		if (isRegistered(name))
		{
			throw std::logic_error(
				fmt::format("Type '{0}' is already registered", name));
		}

		registeredTypes.insert(std::make_pair(name, creatorFunc));
	}

	template<typename U>
	void registerType(std::string_view name)
	{
		static_assert(std::is_base_of_v<T, U>, "Registered type does not match");

		registerType(
			name, []() -> std::unique_ptr<T> { return std::make_unique<U>(); });
	}

	std::unique_ptr<T> create(std::string_view name)
	{
		auto it = registeredTypes.find(name);

		if (it == registeredTypes.end())
		{
			throw std::logic_error(
				fmt::format("Type '{0}' is not registered", name));
		}

		return it->second();
	}

	std::vector<std::string_view> getRegisteredTypeNames() const
	{
		auto result = std::vector<std::string_view>();

		for (auto& item : registeredTypes)
			result.push_back(item.first);

		return result;
	}

private:
	bool isRegistered(std::string_view name) const
	{
		return registeredTypes.find(name) != registeredTypes.end();
	}

private:
	std::map<std::string_view, CreatorFunc> registeredTypes;
};

} // namespace Factory

#endif