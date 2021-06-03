#ifndef __REGISTRABLE_FACTORY_H
#define __REGISTRABLE_FACTORY_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <type_traits>

#include "Libraries/fmt-7.1.3/include/fmt/core.h"

namespace Factory
{
template<typename T>
class RegistrableFactory
{
	using CreatorFunc = std::unique_ptr<T> (*)();

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