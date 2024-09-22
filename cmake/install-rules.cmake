install(TARGETS CodeTask_exe DESTINATION ${INSTALL_PATH})

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
