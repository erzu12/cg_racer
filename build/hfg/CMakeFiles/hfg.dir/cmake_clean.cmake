file(REMOVE_RECURSE
  "libhfg.a"
  "libhfg.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/hfg.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
