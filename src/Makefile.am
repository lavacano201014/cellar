bin_PROGRAMS = cellar
cellar_CPPFLAGS = $(BOOST_CPPFLAGS)
cellar_LDFLAGS = $(BOOST_LDFLAGS) $(BOOST_SYSTEM_LIB) $(BOOST_FILESYSTEM_LIB)
cellar_SOURCES = commands.cpp cellar.cpp fs.cpp bottles.cpp

# Generated files
nodist_cellar_SOURCES = version.cpp

CLEANFILES = version.cpp

version.cpp: 
	$(COG) -d -o version.cpp version.cpp.cog
