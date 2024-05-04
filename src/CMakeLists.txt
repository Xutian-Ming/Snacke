aux_source_directory(. SRC)

add_executable(snack ${SRC})

target_link_libraries(snack -leasyx)