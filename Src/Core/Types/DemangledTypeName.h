#ifndef __DEMANGLED_TYPE_NAME_H
#define __DEMANGLED_TYPE_NAME_H

#include <cxxabi.h>
#include <typeinfo> 
#include <string>

// http://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html

// nie działa z aliasami, informacja o aliasach znika w momencie kompilacji.
// Jest możliwe obejście tego problemu przez stringize/stringify macro,
// ale na razie nie chcę się w to zagłębiać
// https://stackoverflow.com/questions/49411422/return-alias-identificator-instead-of-type-in-typeidsome-type-name

// there was a memory leak in __cxa_demangle (or I did'n use it correctly :))
// according to this documentation I have to free output buffer manually.
// https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a01696.html
// It was written in the first link in this file...

namespace Core
{

template <typename T>
std::string getDemangledTypeName()
{
	int status;
	auto typeId = typeid(T).name();

	std::size_t sz = 100;
	char* buffer = static_cast<char*>(std::malloc(sz));	
	std::string realName = abi::__cxa_demangle(typeId, buffer, &sz, &status);
	std::free(buffer);

	return realName;
}

} // namespace Core

#endif // __DEMANGLED_TYPE_NAME_H
