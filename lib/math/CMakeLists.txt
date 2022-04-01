add_library(${mathName} INTERFACE)

target_compile_features(${mathName} INTERFACE cxx_std_17)

target_include_directories(${mathName} INTERFACE ${headerDir})
