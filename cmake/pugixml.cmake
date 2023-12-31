include(FetchContent)

FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG        a0e064336317c9347a91224112af9933598714e9
    GIT_PROGRESS TRUE
) 
message("pugixml")
FetchContent_MakeAvailable(pugixml)
set_property(TARGET pugixml PROPERTY CXX_STANDARD 23)
