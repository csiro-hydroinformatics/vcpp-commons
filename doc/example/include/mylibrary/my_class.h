#pragma once

#include <vector>

#include "cinterop/c_cpp_interop.hpp"
/*
will load 
C:\local\include\cinterop\c_cpp_interop.hpp
if     
	<DependenciesType Condition="'$(DependenciesType)'==''">Stable</DependenciesType>
in 
%UserProfile%\dev_settings.props
or
C:\src\github_jm\rcpp-interop-commons\include\cinterop\c_cpp_interop.hpp
if
<DependenciesType Condition="'$(DependenciesType)'==''">Source</DependenciesType>
in
%UserProfile%\dev_settings.props
*/

namespace mylibrary {

	char** dummy_example(std::vector<double> values);
}