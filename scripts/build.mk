.RECIPEPREFIX = >

ifneq ($(VALID_CALL),1)
  $(error Call with `make` from root.)
endif

# CC setup
CPPFLAGS := -Isrc -MMD -MP
CXXFLAGS := -std=c++26 -Wall -Wextra -Werror -Wpedantic

ifeq ($(TYPE),native)
  CXXFLAGS += -march=native -O3 -flto=thin
endif

ifeq ($(DETECTED_OS),Windows_NT)
  LDFLAGS := -fuse-ld=lld -static-libgcc -static-libstdc++ -Wl,-Bstatic -lwinpthread -Wl,-Bdynamic
else
  LDFLAGS :=
endif

VERSION_FLAGS := \
  -DDI_VERSION=\"$(VERSION)\" \
  -DDI_GIT_COMMIT_HASH=\"$(GIT_COMMIT_HASH)\"

# Sources
LIB_SRC := \
  src/dude_incredible/chess/position.cpp \
  src/dude_incredible/uci/uci.cpp \
  src/dude_incredible/version.cpp
LIB_OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(LIB_SRC))

DEPS := $(LIB_OBJ:.o=.d) $(BUILD_DIR)/src/main.d

all: $(EXE)

# Sources
$(EXE): $(BUILD_DIR)/src/main.o $(LIB_OBJ)
> $(CXX) $^ -o $@ $(LDFLAGS) $(CXXFLAGS)

$(BUILD_DIR)/%.o: %.cpp
> @mkdir -p $(dir $@)
> $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/src/dude_incredible/version.o: .FORCE
> @mkdir -p $(dir $@)
> $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(VERSION_FLAGS) -c src/dude_incredible/version.cpp -o $@

# To force build targets
.PHONY: .FORCE
.FORCE:

-include $(DEPS)