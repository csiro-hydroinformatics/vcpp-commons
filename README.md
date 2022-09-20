Configuration and helpers for Visual C++ projects
=================================================

Visual C++ project property files and other material to rationalize path management to header files and libraries when compiling on Windows.

The property sheets address two use cases to develop a C++ codebase, and be able to switch between them fast:
* compile and link against stable releases of dependencies (header files and DLLs)
* compile and link against checked out sources of dependencies from multiple git repositories (e.g. co-evolution of your project and its dependencies)

# Assumed folder organisation

Linux has some level of file system conventions for managing header files and libraries. Not so for Windows, so we will mimick something similar. The property files herein assume the following folder structure:

```txt
c:\local
    include
        boost
        catch
        cinterop
            rcpp_interop.hpp
            c_cpp_interop.hpp
            etc.
        json
        moirai
        netcdf
        wila
        yaml-cpp
    libs
        32
            netcdf.dll
            netcdf.lib
        64
            netcdf.dll
            netcdf.lib
```

# Installing

Copy one or more of the .props files in the config folder to a location of your choice. You can customize some of the props filesl we will explain in a later section. 

Assuming you have copied vcpp_config.props to your user profile folder (aka %USERPROFILE%), you can now import it in your `.vcxproj` files:

```xml
  <ImportGroup Label="PropertySheets">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
   <Import Project="$(UserProfile)/vcpp_config.props" Condition="exists('$(UserProfile)/vcpp_config.props')" />
  </ImportGroup>
```

and use the the macro variables as shown:

```xml
  <PropertyGroup>
    <IncludePath>../include;$(LocalIncludePaths);$(IncludePath)</IncludePath>
    <ReferencePath>$(VisualLeakDetectorLibPath);$(LocalLibraryPaths);$(ReferencePath)</ReferencePath>
    <LibraryPath>$(VisualLeakDetectorLibPath);$(LocalLibraryPaths);$(LibraryPath)</LibraryPath>
  </PropertyGroup>
```

```xml
  <ItemDefinitionGroup>
    <Link>
      <AdditionalLibraryDirectories>$(LocalLibraryPaths);%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <AdditionalDependencies>netcdf.lib;%(AdditionalDependencies)</AdditionalDependencies>
      <!--AdditionalDependencies>vld.lib;%(AdditionalDependencies)</AdditionalDependencies-->
    </Link>
  </ItemDefinitionGroup>
```

# Tailoring to your context

The file meant to be loaded by project files is `vcpp_config.props`. It loads four other files, by default:
* dev_settings.props
* local_paths.props
* project_specific.props
* standard_setup.props

You probably do not need to change `standard_setup.props`. This latter file takes care to define some variables based on the build architecture (32 or 64 bits) and configuration (debug or release) so that each VC++ project files does not have multiple XML section all over. 

`local_paths.props` contains the specification of the location you decided to store your 'stable' versions of header files and DLLs. You may only need to customize the property `RootLocalPath`

`dev_settings.props` is the key to being able to switch between the two modes, compiling against dependencies' sources or against stable versions, by using a property called `DependenciesType`.

```xml
    <DependenciesType Condition="'$(DependenciesType)'==''">Stable</DependenciesType>
```

In the section for the case where DependenciesType is equal to 'Source' you want to define paths to the locations of the dependencies source codebases (and prefer '/' to '\' for folder separators - just an opinion...)

```xml
    <LocalIncludePaths>$(SfslSrcPath)/math/include;$(SfslSrcPath)/algorithm/include;$(CcppInteropSrcPath)/include;$(GitHubJm)/moirai/include;$(GitHubJm)/wila/include;$(CorporateSrcPath)/datatypes/include;$(CorporateSrcPath)/rpp-cpp/include;$(GitHubJm)/yaml-cpp/include;$(GitHubJm)/jsoncpp/include</LocalIncludePaths>
```

When you change the value of `DependenciesType` you probably need to unload/reload your project(s) or solution in Visual Studio for the new context to take effect.

# Sample

You can find a simple example project file under doc/example, compilable if you also check out the small repository for [C/C++ Interop](https://github.com/jmp75/c-interop)
