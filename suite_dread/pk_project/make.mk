#=======================================================================================#
# make.mk
#=======================================================================================#
#  Created on: Oct 3, 2015
#      Author: puch
#=======================================================================================#

cppinc+=-I $(rootdir)/$(incdir)
cpplib=-L
cppsrc=-c
cppobj=-o

arc=ar
arcflags=-qvc

obj=.o
cpp=.cpp
c__=.c
lib=.a


built_objs=$(patsubst $(src_dir)/%, $(objdir)/%$(obj), $(src_files))
built_libs=$(addprefix -l,$(lib_files))

all : $(lib_name) $(bin_name)
	

$(libdir)/lib%$(lib) : %_makefile.mk
	$(MAKE) -f  $^ -C $(dir $^ );

$(objdir)/%$(obj) : $(src_dir)/%$(cpp)
	$(gpp) $(cppflags) $(cppinc) $(cppsrc) $^ $(cppobj) $@; 

$(objdir)/%$(obj) : $(src_dir)/%$(c__)
	$(gpp) $(cppflags) $(cppinc) $(cppsrc) $^ $(cppobj) $@; 

$(lib_name) : $(built_objs)
	$(arc) $(arcflags) $(libdir)/lib$(lib_name)$(lib) $(built_objs) 

$(bin_name) : $(patsubst %, $(libdir)/lib%$(lib), $(lib_files)) $(built_objs)
	$(gpp) $(cppflags) $(cppinc) $(cppobj) $(bindir)/$@ $(built_objs) -L $(libdir) $(built_libs)
#=======================================================================================#
# make.mk
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#