Configuration and helpers for Visual C++ projects
=================================================

Visual C++ project property files and other material to rationalize path management to header files and libraries when compiling on Windows.

# Installing

copy one or more of the .props files in the config folder to a location of your choice. You should customize the props files. You probably do not need to change `standard_setup.props`. This latter file takes care to define some variables based on the build architecture (32 or 64 bits) and configuration (debug or release) so that each VC++ project files does not have duplicated gunk all over. 

Assuming you have copied vcpp_config.props to your user profile folder (aka %USERPROFILE%), you can now import it in your `.vcxproj` files:

```xml
  <ImportGroup Label="PropertySheets">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
   <Import Project="$(UserProfile)/vcpp_config.props" Condition="exists('$(UserProfile)/vcpp_config.props')" />
  </ImportGroup>
```

and use the the macro variables like so:

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

You would thus set up a folder structure like so:

```txt
c:\local
    include
        boost
        catch
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
    devlibs
        32
            mydevlib.dll
            mydevlib.lib
        64
            mydevlib.dll
```