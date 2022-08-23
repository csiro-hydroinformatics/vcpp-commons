
#include "include/mylibrary/my_class.h"
#include <string>
#include "cinterop/c_cpp_interop.hpp"
/*
will load
C:\local\include\cinterop\c_cpp_interop.hpp
if
<DependenciesType Condition="'$(DependenciesType)'==''">Stable</DependenciesType>
in
%UserProfile%\dev_settings.props
or e.g.
C:\src\github_jm\c-interop\include\cinterop\c_cpp_interop.hpp
if
<DependenciesType Condition="'$(DependenciesType)'==''">Source</DependenciesType>
in
%UserProfile%\dev_settings.props
*/

namespace mylibrary {

	char** dummy_example(std::vector<double> values)
	{
		using namespace cinterop::utils;
		auto converter = [](const double& d) {
			return to_ansi_string<std::string>(std::to_string(d));
		};
		int size;
		return vector_to_c_array<double, char*>(values, converter, &size);
	}

}