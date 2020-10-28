# GLSLang-cmake
Modern CMake find module for GLSLang. Should work on any platform, but tested only on linux.

## How to use it?
Add this repo root directory into your cmake find path like this:

    LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
Then require it like this:

    find_package(GLSLang COMPONENTS GLSLang SPRIV)
You should already know a bit about CMake stuff, like `REQUIRED`, `QUIET` and similliar things. Only one thing that may be new for you is `COMPONENTS` dirictive. It's required and can be either `GLSLang`, `SPIRV` or both (like in example). It defines which libs will be searched and which targets will be defined.

Link to `GLSLang::GLSLang` or `GLSLang::SPIRV` depending on which libs you required and need.

As a sidenote, module don't define any vars: use targets to link to library and `if(TARGET GLSLang::COMPONENT)` to check is library available.