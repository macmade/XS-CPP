#-------------------------------------------------------------------------------
# Copyright (c) 2015, Jean-David Gadina - www.xs-labs.com
# Distributed under the Boost Software License, Version 1.0.
# 
# Boost Software License - Version 1.0 - August 17th, 2003
# 
# Permission is hereby granted, free of charge, to any person or organization
# obtaining a copy of the software and accompanying documentation covered by
# this license (the "Software") to use, reproduce, display, distribute,
# execute, and transmit the Software, and to prepare derivative works of the
# Software, and to permit third-parties to whom the Software is furnished to
# do so, all subject to the following:
# 
# The copyright notices in the Software and this entire statement, including
# the above license grant, this restriction and the following disclaimer,
# must be included in all copies of the Software, in whole or in part, and
# all derivative works of the Software, unless such copies or derivative
# works are solely in the form of machine-executable object code generated by
# a source language processor.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
# SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
# FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Search paths
#-------------------------------------------------------------------------------

# Define the search paths for source files
vpath %$(EXT_C) $(DIR_SRC)
vpath %$(EXT_C) $(DIR_TESTS)

#-------------------------------------------------------------------------------
# Built-in targets
#-------------------------------------------------------------------------------

# Declaration for phony targets, to avoid problems with local files
.PHONY: all      \
        clean    \
        debug    \
        release  \
        products

# Declaration for precious targets, to avoid cleaning of intermediate files
.PRECIOUS: $(DIR_BUILD_TEMP)%$(PRODUCT)$(EXT_O) $(DIR_BUILD_TEMP)%$(EXT_C)$(EXT_O)

#-------------------------------------------------------------------------------
# Common targets
#-------------------------------------------------------------------------------

# Main Target
all: release debug
	
	@:
	
# Release build (parallel if available)
release:
	
ifeq ($(MAKE_4),true)
	@$(MAKE) -j 50 --output-sync products
else
	@$(MAKE) products
endif

# Debug build (parallel if available)
debug:
	
ifeq ($(MAKE_4),true)
	@$(MAKE) -j 50 --output-sync products DEBUG=1
else
	@$(MAKE) products DEBUG=1
endif

# Cleans all build files
clean: _ARCHS         = $(foreach _PRODUCT,$(PRODUCTS),$(subst $(firstword $(subst |, ,$(_PRODUCT))),,$(subst |, ,$(_PRODUCT))))
clean: _CLEAN_ARCHS   = $(foreach _ARCH,$(_ARCHS),$(addprefix _clean_,$(_ARCH)))
clean:
	
	@$(MAKE) $(_CLEAN_ARCHS)
	@$(MAKE) $(_CLEAN_ARCHS) DEBUG=1

# Cleans architecture specific files
_clean_%:
	
	@echo -e $(call PRINT,Cleaning,$*,Cleaning all intermediate files)
	@rm -rf $(DIR_BUILD_TEMP)$*
	
	@echo -e $(call PRINT,Cleaning,$*,Cleaning all product files)
	@rm -rf $(DIR_BUILD_PRODUCTS)$*

# Unit-tests
test:
	
	@:

#-------------------------------------------------------------------------------
# Targets with second expansion
#-------------------------------------------------------------------------------

.SECONDEXPANSION:

# Products target
products: _PRODUCTS       = $(foreach _PRODUCT,$(PRODUCTS),$(foreach _ARCH,$(subst $(firstword $(subst |, ,$(_PRODUCT))),,$(subst |, ,$(_PRODUCT))),$(_ARCH)/$(firstword $(subst |, ,$(_PRODUCT)))))
products: _PRODUCTS_BUILD = $(foreach _PRODUCT,$(_PRODUCTS),$(addprefix $(DIR_BUILD_PRODUCTS),$(_PRODUCT)))
products: $$(_PRODUCTS_BUILD)
	
	@:

# Static library target
$(DIR_BUILD_PRODUCTS)%$(EXT_LIB): _ARCH  = $(firstword $(subst /, ,$*))
$(DIR_BUILD_PRODUCTS)%$(EXT_LIB): _FLAGS = $(AR_FLAGS_$(_ARCH))
$(DIR_BUILD_PRODUCTS)%$(EXT_LIB): $$(shell mkdir -p $$(dir $$@)) $(DIR_BUILD_TEMP)$$(_ARCH)/$(PRODUCT)$(EXT_O)
	
	@echo -e $(call PRINT,$(PRODUCT_LIB)$(EXT_LIB),$(_ARCH),Linking the $(_ARCH) binary)
	@$(AR) $(_FLAGS) $@ $<

# Dynamic library target
$(DIR_BUILD_PRODUCTS)%$(EXT_DYLIB): _ARCH  = $(firstword $(subst /, ,$*))
$(DIR_BUILD_PRODUCTS)%$(EXT_DYLIB): _FLAGS = $(CC_FLAGS_DYLIB_$(_ARCH)) $(CC_FLAGS_$(_ARCH))
$(DIR_BUILD_PRODUCTS)%$(EXT_DYLIB): $$(shell mkdir -p $$(dir $$@)) $(DIR_BUILD_TEMP)$$(_ARCH)/$(PRODUCT)$(EXT_O)
	
	@echo -e $(call PRINT,$(PRODUCT_LIB)$(EXT_DYLIB),$(_ARCH),Linking the $(_ARCH) binary)
	@$(CC) $(LIBS) $(_FLAGS) -o $@ $<

# Framework target
$(DIR_BUILD_PRODUCTS)%$(EXT_FRAMEWORK): _ARCH = $(firstword $(subst /, ,$*))
$(DIR_BUILD_PRODUCTS)%$(EXT_FRAMEWORK): $$(shell mkdir -p $$(dir $$@)) $(DIR_BUILD_TEMP)$$(_ARCH)/$(PRODUCT)$(EXT_O)
	
	@:

$(DIR_BUILD_TEMP)%$(PRODUCT)$(EXT_O): _ARCH        = $(subst /,,$*)
$(DIR_BUILD_TEMP)%$(PRODUCT)$(EXT_O): _FILES       = $(foreach _FILE,$(FILES),$(patsubst $(DIR_SRC)%,%,$(_FILE)))
$(DIR_BUILD_TEMP)%$(PRODUCT)$(EXT_O): _FILES_OBJ   = $(addprefix $*,$(patsubst %$(EXT_C),%$(EXT_C)$(EXT_O),$(_FILES)))
$(DIR_BUILD_TEMP)%$(PRODUCT)$(EXT_O): _FILES_BUILD = $(addprefix $(DIR_BUILD_TEMP),$(_FILES_OBJ))
$(DIR_BUILD_TEMP)%$(PRODUCT)$(EXT_O): _FLAGS       = $(LD_FLAGS_$(_ARCH))
$(DIR_BUILD_TEMP)%$(PRODUCT)$(EXT_O): $$(_FILES_BUILD)
	
	@echo -e $(call PRINT,Linking object files,$(_ARCH),$(PRODUCT)$(EXT_O))
	@ld -r $(_FLAGS) $(_FILES_BUILD) -o $@

$(DIR_BUILD_TEMP)%$(EXT_C)$(EXT_O): _ARCH      = $(firstword $(subst /, ,$(subst $(DIR_BUILD_TEMP),,$@)))
$(DIR_BUILD_TEMP)%$(EXT_C)$(EXT_O): _FILE      = $(subst $(_ARCH)/,,$*)$(EXT_C)
$(DIR_BUILD_TEMP)%$(EXT_C)$(EXT_O): _FLAGS     = $(CC_FLAGS_$(_ARCH))
$(DIR_BUILD_TEMP)%$(EXT_C)$(EXT_O): $$(_FILE)
	
	@echo -e $(call PRINT_FILE,"Compiling file",$(_ARCH),$(_FILE))
	@$(_CC) $(_FLAGS) -o $@ -c $(addprefix $(DIR_SRC),$(_FILE))
