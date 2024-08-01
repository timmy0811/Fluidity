#pragma once

#include <memory>

#ifdef _WIN32
// Other defines
#else
#error 3DFLD only supports Windows!
#endif

#ifdef NO_ASSERTS
#define CAST_ASSERT(x, ...)
#define CAST_CORE_ASSERT(x, ...)
#else
#define FLUIDIFY_ASSERT(x, ...) {if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define FLUIDIFY_CORE_ASSERT(x, ...) {if(!(x)) { LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#endif

namespace FLD {
	template<typename T>
	using Unique = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}