cmake_minimum_required(VERSION 3.16)

project(CppChaos)

add_custom_target(Doc ALL 
    make html
    WORKING_DIRECTORY ../Docs)
