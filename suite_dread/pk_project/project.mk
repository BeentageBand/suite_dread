##============================================================================#
 # project.mk
 #============================================================================#
 #  Created on: Dec 21, 2015
 #      Author: puch
 ##===========================================================================#

##============================================================================#
 # DEFINE TEMPLATES
 ##===========================================================================#
define INFO_VERBOSE_template
$1

ifeq "$(MAKE_DBG)" "1"
   $(info $1 )
endif

endef

##============================================================================#
 # DEFINE VARIABLES
 ##===========================================================================#
define USER_INCS

$(_build_)_PROJECT_INC_DIR+=$(shell find $($(_build_)_PROJECT_DIR) -path */pk_*_user 2>/dev/null)
$(_build_)_PROJECT_INC_DIR+=$(shell find $($(_build_)_PROJECT_DIR) -path */_inc 2>/dev/null)

endef 

define INCLUDE_MAKEFILE_template
_curr_:=$(word $(_i_), $($(_build_)_PACKAGE_NAME) )
_path_:=$(word $(_i_), $($(_build_)_PACKAGE_PATH) )

include $(word $(_i_), $($(_build_)_PACKAGE_FIND) )
endef

##============================================================================#
 # DEFINE RULES
 ##===========================================================================#

##
 # CALL BUILD : target rule, expands to all pk's inside this the project
 ##
define CALL_BUILD
.PHONY : $($(_build_)_PACKAGE_NAME)

$(_build_) : $($(_build_)_PACKAGE_NAME)
endef

##
 # PACKAGE BUILD : pk rule, search for binaries
 ##
define PACKAGE_BUILD

ifneq "$($(_build_)_$(_pk_)_bin_name)" ""
   $(_pk_) : $($(_build_)_BIN_DIR)/$($(_build_)_$(_pk_)_bin_name)
endif

endef
##============================================================================#
 # EXPAND VARIABLES
 ##===========================================================================#
$(_build_)_PROJECT_DIR?=$(realpath . )
$(_build_)_OUT_DIR=$($(_build_)_PROJECT_DIR)/out
$(_build_)_INC_DIR=$($(_build_)_OUT_DIR)/inc
$(_build_)_OBJ_DIR=$($(_build_)_OUT_DIR)/$(_build_)/obj
$(_build_)_LIB_DIR=$($(_build_)_OUT_DIR)/$(_build_)/lib
$(_build_)_BIN_DIR=$($(_build_)_OUT_DIR)/$(_build_)/bin
$(_build_)_PROJECT_INC_DIR+=$($(_build_)_INC_DIR)
MAKE_DBG?=
##
 #Generate all build modules
 ##
$(eval \
   $(call INFO_VERBOSE_template, \
     $(_build_)_PACKAGE_FIND=$(shell find $($(_build_)_PROJECT_DIR) -name *_makefile.mk) \
   ) \
)

##
 # BUILD_MODULE_PATH=.../pk_module_1/ .../pk_module_N/ ...
 ##
 
$(info ****************************************** SET MODULES ********************************)
 
$(eval \
   $(foreach _pk_, $($(_build_)_PACKAGE_FIND), \
      $(call INFO_VERBOSE_template, \
            $(_build_)_PACKAGE_PATH+=$(dir $(_pk_) ) \
      ) \
   ) \
)

##
 # BUILD_MODULE_PACK=pk_module_1 pk_module_N ...
 ##
$(foreach _pk_,$($(_build_)_PACKAGE_PATH), \
   $(eval \
      $(call INFO_VERBOSE_template, \
         $(_build_)_PACKAGE_NAME+=$(patsubst $(realpath $(_pk_)../)/%,%, $(realpath $(_pk_)) )\
      )\
   )\
)

##
 # BUILD_MODULE_USER_INC=pk_module_1/pk_module_1_user/*.h pk_module_N/pk_module_N_user/*.h ...
 ##
 
$(info ****************************************** MODULES INCS DIRS ********************************)

$(eval \
   $(call INFO_VERBOSE_template, $(USER_INCS) )\
)

##
 # BUILD_MODULE_MAKE=pk_module_1/Makefile*.mk pk_module_N/Makefile*.mk ...
 ##
$(info ****************************************** SUB-MAKE_RULES ********************************)

EXPORTABLE_PACKAGE_VARS:=\
lib_name  \
lib_libs  \
lib_objs  \
lib_incs  \
bin_name  \
bin_incs  \
bin_libs  \
bin_objs  \

_lprefix_=lib
_lib_ext_=.a
_obj_ext_=.o
_src_ext_=.cpp

##============================================================================#
 # EXPAND RULES
 ##===========================================================================#
$(foreach _i_,$(shell seq 1 $(words $($(_build_)_PACKAGE_NAME)) ), \
   $(eval \
      $(call INFO_VERBOSE_template, \
         $(INCLUDE_MAKEFILE_template) \
      )\
   ) \
)

##
 # CALL BUILD
 ##
 $(info ****************************************** CALL BUILD ********************************)

$(eval \
   $(call INFO_VERBOSE_template, \
      $(CALL_BUILD) \
   ) \
)

$(foreach _pk_, $($(_build_)_PACKAGE_NAME), \
   $(eval \
     $(call INFO_VERBOSE_template, $(PACKAGE_BUILD) )\
   )\
)

##
 # MAKE RULE CLEAN
 ## 
clean :
	$(RM) -r out/;

##
 # MAKE RULE FOR OUTPUT DIR
 ##
$($(_build_)_BIN_DIR) $($(_build_)_LIB_DIR) $($(_build_)_OBJ_DIR): $($(_build_)_OUT_DIR)/$(_build_)
	-mkdir $@

$($(_build_)_OUT_DIR)/$(_build_) $($(_build_)_INC_DIR): $($(_build_)_OUT_DIR)
	-mkdir $@

$($(_build_)_OUT_DIR):
	-mkdir $@
