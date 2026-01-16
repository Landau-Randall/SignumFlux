include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES "*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    add_executable(${TEST_NAME}.out ${TEST_SOURCE})
    
    # 根据文件名判断是否需要链接SFML
    if(TEST_NAME STREQUAL "sigflx_sfml_test")
        # 这个测试需要SFML
        message(STATUS "Linking SFML for ${TEST_NAME}")
        
        # 查找SFML（如果还没找过）
        if(NOT TARGET SFML::System)
            set(SFML_STATIC_LIBRARIES ON)
            find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics audio)
        endif()
        
        # 先链接GTest
        target_link_libraries(${TEST_NAME}.out PRIVATE GTest::gtest GTest::gtest_main)
        
        # 再链接SFML（使用现代CMake目标）
        target_link_libraries(${TEST_NAME}.out PRIVATE
            SFML::Graphics
            SFML::Window
            SFML::System
            # SFML::Audio
        )
        
        # 或者直接链接静态库文件（如果现代目标不行）
        # target_link_libraries(${TEST_NAME}.out PRIVATE
        #     GTest::gtest
        #     GTest::gtest_main
        #     sfml-audio-s
        #     sfml-graphics-s
        #     sfml-window-s
        #     sfml-system-s
        # )
    else()
        # 其他测试只链接GTest
        target_link_libraries(${TEST_NAME}.out PRIVATE GTest::gtest GTest::gtest_main)
    endif()
    
    gtest_add_tests(TARGET ${TEST_NAME}.out)
endforeach()