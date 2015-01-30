SOURCE_DIR = source
BRACKETS_DIR = $(SOURCE_DIR)/main
BRACKETS_EXE = brackets
BRACKETS_PATH = $(BRACKETS_DIR)/$(BRACKETS_EXE)
BIN_DIR = bin
DEBUG = -g

.PHONY: brackets

brackets:
	$(MAKE) -C $(SOURCE_DIR)
	mkdir -p $(BIN_DIR)
	cp $(BRACKETS_PATH) $(BIN_DIR)

clean:
	$(MAKE) -C $(SOURCE_DIR) clean
	rm -f $(BIN_DIR)/$(BRACKETS_EXE)

all: brackets
