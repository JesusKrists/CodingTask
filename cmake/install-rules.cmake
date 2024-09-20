install(
    TARGETS CodeTask_exe
    RUNTIME COMPONENT CodeTask_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
