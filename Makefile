include Rules.mk

#######################################
# list of source files
########################################
LIB_PSDP_SOURCES =                                  \
src/psdp.c

DEMO_SOURCES =                                      \
demo/main.c

#######################################
C_DEFS  = 

#######################################
# include and lib setup
#######################################
C_INCLUDES =                              \
-Isrc

LIBS = 
LIBDIR = 

#######################################
# for verbose output
#######################################
# Prettify output
V = 0
ifeq ($V, 0)
  Q = @
  P = > /dev/null
else
  Q =
  P =
endif

#######################################
# build directory and target setup
#######################################
BUILD_DIR = build
TARGET    = psdp_test

#######################################
# compile & link flags
#######################################
CFLAGS += -g $(C_DEFS) $(C_INCLUDES)

# Generate dependency information
CFLAGS += -MMD -MF .dep/$(*F).d

LDFLAGS +=  $(LIBDIR) $(LIBS)

#######################################
# build target
#######################################
all: $(BUILD_DIR)/$(TARGET)

#######################################
# target source setup
#######################################
TARGET_SOURCES := $(LIB_PSDP_SOURCES)
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(TARGET_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(TARGET_SOURCES)))

DEMO_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(DEMO_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(DEMO_SOURCES)))

#######################################
# C source build rule
#######################################
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo "[CC]         $(notdir $<)"
	$Q$(CC) -c $(CFLAGS) $< -o $@

#######################################
# main target
#######################################
$(BUILD_DIR)/$(TARGET): $(DEMO_OBJECTS) $(OBJECTS) Makefile
	@echo "[LD]         $@"
	$Q$(CC) $(DEMO_OBJECTS) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR):
	@echo "MKDIR          $(BUILD_DIR)"
	$Qmkdir $@

#######################################
# unit test target
#######################################
TEST_SRC=   \
unit_test/test.c

TEST_OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(TEST_SRC:.c=.o)))
vpath %.c $(sort $(dir $(TEST_SRC)))

.PHONY: unit_test
unit_test: $(BUILD_DIR)/$(TARGET)_unit_test
	@echo "unit_test taget built"
	@$(BUILD_DIR)/$(TARGET)_unit_test

$(BUILD_DIR)/$(TARGET)_unit_test: $(TEST_OBJS) $(OBJECTS) Makefile
	@echo "[LD]         $@"
	$Q$(CC) $(TEST_OBJS) $(OBJECTS) $(LDFLAGS) -o $@ -lcunit

#######################################
# clean up
#######################################
clean:
	@echo "[CLEAN]          $(TARGET) $(BUILD_DIR) .dep"
	$Q-rm -fR .dep $(BUILD_DIR)
	$Q-rm -f test/*.o unit_test/*.o

#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
