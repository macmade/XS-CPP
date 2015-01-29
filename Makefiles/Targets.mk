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
.PHONY: all             \
        clean           \
        os-x            \
        linux           \
        lib             \
        dylib           \
        ios-lib         \
        mac-framework   \
        i386            \
        x86-64          \
        armv7           \
        armv7s          \
        arm64

# Declaration for precious targets, to avoid cleaning of intermediate files
.PRECIOUS:  $(DIR_BUILD_TEMP_INTEL_32_OBJ)%$(EXT_O) \
            $(DIR_BUILD_TEMP_INTEL_64_OBJ)%$(EXT_O) \
            $(DIR_BUILD_TEMP_ARM_7_OBJ)%$(EXT_O)    \
            $(DIR_BUILD_TEMP_ARM_7S_OBJ)%$(EXT_O)   \
            $(DIR_BUILD_TEMP_ARM_64_OBJ)%$(EXT_O)

#-------------------------------------------------------------------------------
# Common targets
#-------------------------------------------------------------------------------

# Main Target
all: release debug
	
	@:
    
# Release build (parallel if available)
release:
	
ifeq ($(MAKE_4),true)
	@$(MAKE) -j 50 --output-sync _release
else
	@$(MAKE) _release
endif

# Debug build (parallel if available)
debug:
	
ifeq ($(MAKE_4),true)
	@$(MAKE) -j 50 --output-sync _debug DEBUG=1
else
	@$(MAKE) _debug DEBUG=1
endif

# Release build
_release: $(BUILD_TYPE)
	
	@:

# Debug build
_debug: $(BUILD_TYPE)
	
	@:
    
# Build for OS-X
os-x: lib dylib mac-framework ios-lib
	
	@:
	
# Build for Linux
linux: lib dylib
	
	@:

# Release test target
test: release
	
	@$(MAKE) -s _test

# Debug test target
test-debug: debug
	
	@$(MAKE) -s _test DEBUG=1

# Test target
_test:
	
	@:

# Cleans all build files
clean:
	
	@$(MAKE) _clean
	@$(MAKE) _clean DEBUG=1
	
# Clean target
_clean:
	
	@echo -e $(call PRINT,Cleaning,i386,Cleaning all intermediate files)
	@rm -rf $(DIR_BUILD_TEMP_INTEL_32_OBJ)*
	@rm -rf $(DIR_BUILD_TEMP_INTEL_32_BIN)*
	
	@echo -e $(call PRINT,Cleaning,x86-64,Cleaning all intermediate files)
	@rm -rf $(DIR_BUILD_TEMP_INTEL_64_OBJ)*
	@rm -rf $(DIR_BUILD_TEMP_INTEL_64_BIN)*
	
	@echo -e $(call PRINT,Cleaning,armv7,Cleaning all intermediate files)
	@rm -rf $(DIR_BUILD_TEMP_ARM_7_OBJ)*
	@rm -rf $(DIR_BUILD_TEMP_ARM_7_BIN)*
	
	@echo -e $(call PRINT,Cleaning,armv7s,Cleaning all intermediate files)
	@rm -rf $(DIR_BUILD_TEMP_ARM_7S_OBJ)*
	@rm -rf $(DIR_BUILD_TEMP_ARM_7S_BIN)*
	
	@echo -e $(call PRINT,Cleaning,arm64,Cleaning all intermediate files)
	@rm -rf $(DIR_BUILD_TEMP_ARM_64_OBJ)*
	@rm -rf $(DIR_BUILD_TEMP_ARM_64_BIN)*
	
	@echo -e $(call PRINT,Cleaning,i386,Cleaning all product files)
	@rm -rf $(DIR_BUILD_PRODUCTS_INTEL_32)*
	
	@echo -e $(call PRINT,Cleaning,x86-64,Cleaning all product files)
	@rm -rf $(DIR_BUILD_PRODUCTS_INTEL_64)*
	
	@echo -e $(call PRINT,Cleaning,armv7,Cleaning all product files)
	@rm -rf $(DIR_BUILD_PRODUCTS_ARM_7)*
	
	@echo -e $(call PRINT,Cleaning,armv7s,Cleaning all product files)
	@rm -rf $(DIR_BUILD_PRODUCTS_ARM_7S)*
	
	@echo -e $(call PRINT,Cleaning,arm64,Cleaning all product files)
	@rm -rf $(DIR_BUILD_PRODUCTS_ARM_64)*
	
	@echo -e $(call PRINT,Cleaning,universal,Cleaning all product files)
	@rm -rf $(DIR_BUILD_PRODUCTS_UNIVERSAL)*

# Builds a static library
lib: i386 x86-64
	
	@:

# Builds a static library
dylib: i386 x86-64
	
	@:

# Builds an iOS static library (OS-X builds only)
ios-lib: armv7 armv7s arm64
	
	@:
	
# Builds an Mac framework (OS-X builds only)
mac-framework: i386 x86-64
	
	@:

#-------------------------------------------------------------------------------
# Architecture specific targets
#-------------------------------------------------------------------------------

# Target: i386
i386: $(FILES_C_BUILD_INTEL_32)
	
	@echo -e $(call PRINT,Linking object files,i386,$(PRODUCT)$(EXT_O))
	@rm -rf $(DIR_BUILD_TEMP_ARM_64_OBJ)$(PRODUCT)$(EXT_O)
	@ld -r $(LD_FLAGS_INTEL_32) $(FILES_C_BUILD_INTEL_32) -o $(DIR_BUILD_TEMP_INTEL_32_OBJ)$(PRODUCT)$(EXT_O)

# Target: x86-64
x86-64: $(FILES_C_BUILD_INTEL_64)
	
	@echo -e $(call PRINT,Linking object files,x86-64,$(PRODUCT)$(EXT_O))
	@rm -rf $(DIR_BUILD_TEMP_ARM_64_OBJ)$(PRODUCT)$(EXT_O)
	@ld -r $(LD_FLAGS_INTEL_64) $(FILES_C_BUILD_INTEL_64) -o $(DIR_BUILD_TEMP_INTEL_64_OBJ)$(PRODUCT)$(EXT_O)

# Target: armv7
armv7: $(FILES_C_BUILD_ARM_7)
	
	@echo -e $(call PRINT,Linking object files,armv7,$(PRODUCT)$(EXT_O))
	@rm -rf $(DIR_BUILD_TEMP_ARM_64_OBJ)$(PRODUCT)$(EXT_O)
	@ld -r $(LD_FLAGS_ARM_7) $(FILES_C_BUILD_ARM_7) -o $(DIR_BUILD_TEMP_ARM_7_OBJ)$(PRODUCT)$(EXT_O)

# Target: armv7s
armv7s: $(FILES_C_BUILD_ARM_7S)
	
	@echo -e $(call PRINT,Linking object files,armv7s,$(PRODUCT)$(EXT_O))
	@rm -rf $(DIR_BUILD_TEMP_ARM_64_OBJ)$(PRODUCT)$(EXT_O)
	@ld -r $(LD_FLAGS_ARM_7S) $(FILES_C_BUILD_ARM_7S) -o $(DIR_BUILD_TEMP_ARM_7S_OBJ)$(PRODUCT)$(EXT_O)

# Target: arm64
arm64: $(FILES_C_BUILD_ARM_64)
	
	@echo -e $(call PRINT,Linking object files,arm64,$(PRODUCT)$(EXT_O))
	@rm -rf $(DIR_BUILD_TEMP_ARM_64_OBJ)$(PRODUCT)$(EXT_O)
	@ld -r $(LD_FLAGS_ARM_64) $(FILES_C_BUILD_ARM_64) -o $(DIR_BUILD_TEMP_ARM_64_OBJ)$(PRODUCT)$(EXT_O)

#-------------------------------------------------------------------------------
# Targets with second expansion
#-------------------------------------------------------------------------------

.SECONDEXPANSION:

# Target: i386 object file
$(DIR_BUILD_TEMP_INTEL_32_OBJ)%$(EXT_O): $$(shell mkdir -p $$(dir $$@)) %$(EXT_C)
	
	@echo -e $(call PRINT_FILE,"Compiling file",i386,$<)
	@$(_CC) $(CC_FLAGS_INTEL_32) -o $@ -c $<

# Target: x86_64 object file
$(DIR_BUILD_TEMP_INTEL_64_OBJ)%$(EXT_O): $$(shell mkdir -p $$(dir $$@)) %$(EXT_C)
	
	@echo -e $(call PRINT_FILE,"Compiling file",x86-64,$<)
	@$(_CC) $(CC_FLAGS_INTEL_64) -o $@ -c $<

# Target: armv7 object file
$(DIR_BUILD_TEMP_ARM_7_OBJ)%$(EXT_O): $$(shell mkdir -p $$(dir $$@)) %$(EXT_C)
	
	@echo -e $(call PRINT_FILE,"Compiling file",armv7,$<)
	@$(_CC) $(CC_FLAGS_ARM_7) -isysroot $(IOS_SDK_PATH) -o $@ -c $<

# Target: armv7s object file
$(DIR_BUILD_TEMP_ARM_7S_OBJ)%$(EXT_O): $$(shell mkdir -p $$(dir $$@)) %$(EXT_C)
	
	@echo -e $(call PRINT_FILE,"Compiling file",armv7s,$<)
	@$(_CC) $(CC_FLAGS_ARM_7S) -isysroot $(IOS_SDK_PATH) -o $@ -c $<

# Target: arm64 object file
$(DIR_BUILD_TEMP_ARM_64_OBJ)%$(EXT_O): $$(shell mkdir -p $$(dir $$@)) %$(EXT_C)
	
	@echo -e $(call PRINT_FILE,"Compiling file",arm64,$<)
	@$(_CC) $(CC_FLAGS_ARM_64) -isysroot $(IOS_SDK_PATH) -o $@ -c $<