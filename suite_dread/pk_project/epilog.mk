##======================================================================================#
 # make.mk
 #======================================================================================#
 #  Created on: Oct 3, 2015
 #      Author: puch
 ##=====================================================================================#

##======================================================================================#
 # EXPAND PACKAGE RULE
 ##=====================================================================================#
$(eval \
   $(call INFO_VERBOSE_template, \
      $($(_build_)_$(_curr_)_MAKE) \
   )\
)

include $($(_build_)_PROJECT_DIR)/$($(_build_)_MAK_DIR)/$(_build_)_make.mk
##======================================================================================#
 # make.mk
 ##=====================================================================================#
 # Changes Log
 #
 #
 ##=====================================================================================#