find_program( MKPROP_EXECUTABLE mkprop DOC "The Qt Property Generator" )
if( NOT MKPROP_EXECUTABLE )
   message( SEND_ERROR "Failed to find the Qt Property Generator." )
endif( NOT MKPROP_EXECUTABLE )

# - Pass a list of files through the Qt Property Generator
#
# PROCESS( OUTVAR source1 ... sourceN )
#
#  OUTVAR  A list containing all the output souce file names, suitable
#          to be passed to add_executable or add_library.
#
# Example:
#  add_m4_sources( SRCS src/test1.cxx.m4 src/test2.cxx.m4 )
function(PROCESS OUTVAR)
   set( outfiles )
   foreach( f ${ARGN} )
     # first we might need to make the input file absolute
     get_filename_component( f "${f}" ABSOLUTE )
     file( RELATIVE_PATH rf "${CMAKE_CURRENT_SOURCE_DIR}" "${f}" )
     set(of "${CMAKE_CURRENT_BINARY_DIR}/${rf}")
     
     set(header_in  "${f}.h")
     set(header_out "${of}.h")
     set(source_in  "${f}.cpp")
     set(source_out "${of}.cpp")
     set(gen_f      "${of}.gen")
     set(moc_f      "${of}.moc")
     # create the output directory if it doesn't exist
     get_filename_component(in_dir "${f}" PATH)
     get_filename_component(out_dir "${of}" PATH)
     if( NOT IS_DIRECTORY "${out_dir}" )
         file( MAKE_DIRECTORY "${out_dir}" )
     endif( NOT IS_DIRECTORY "${out_dir}" )
     # now add the custom command to generate the output file
     add_custom_command(OUTPUT "${gen_f}" "${header_out}"
         COMMAND ${MKPROP_EXECUTABLE}
         ARGS "${header_in}" "${gen_f}" "${header_out}"
         DEPENDS "${heaer_in}"
         WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
       )
     add_custom_command(OUTPUT "${source_out}"
         COMMAND cp
         ARGS "${source_in}" "${source_out}"
         DEPENDS "${source_in}" "${header_out}"
       )
     message("Moc: ${header_out}, ${moc_f}")
     qt4_generate_moc(${header_out} ${moc_f})
     # append the output file to the list of outputs
     list( APPEND outfiles "${source_out}" "${header_out}")
   endforeach(f)
   #qt4_automoc(${outfiles})
   # set the output list in the calling scope
   set(${OUTVAR} ${${OUTVAR}} ${outfiles} PARENT_SCOPE )
endfunction( PROCESS )

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

# In this CMakeLists.txt we define which files
# are used to compile the application
set(weather-desktop_SRCS
   #/home/mspencer/Programs/weather-desktop/build/src/weather/location.cpp
   weather-desktop.cpp
   main.cpp
 )
 
process(weather-desktop_SRCS weather/location)

message("Files: ${weather-desktop_SRCS}")

# Run ui files through uic
# kde4_add_ui_files(weather-desktop_SRCS weather-desktop.ui)

# Set the name of the application
kde4_add_executable(weather-desktop ${weather-desktop_SRCS})

# Select which libraries we need to link to
target_link_libraries(weather-desktop ${KDE4_KDEUI_LIBS}  ${QT_QTDECLARATIVE_LIBRARY} qjson)

# Tell cmake to install the application binary
install(TARGETS weather-desktop ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES weather-desktopui.rc 
        DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop)

# Install the .desktop file
install(PROGRAMS weather-desktop.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR})

add_subdirectory(qml)