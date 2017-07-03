#pragma once

#include "public\defines.h"
#include "public\types.hpp"
#include <vector>

#if __cplusplus == 201703L
#include <variant>
#define JCON_VARIANT std::variant
#define JCON_VARIANT_GET std::get
#define JCON_VARIANT_INDEX(x) x.index()
#else
#include <boost/variant.hpp>
#define JCON_VARIANT boost::variant
#define JCON_VARIANT_GET boost::get
#define JCON_VARIANT_INDEX(x) x.which()
#endif // __cplusplus == 201703L

namespace JCON_NAMESPACE {

	typedef JCON_VARIANT<JCON_NAMESPACE::textType, JCON_NAMESPACE::fontType, JCON_NAMESPACE::colorType> component;
	typedef std::vector<JCON_NAMESPACE::component> componentList;

}