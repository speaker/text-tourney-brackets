SOURCE_DIR = main
BRACKETS_DIR = $(SOURCE_DIR)
BRACKETS_EXE = $(BRACKETS_DIR)/brackets
BIN_DIR = bin

.PHONY: brackets

brackets:
	$(MAKE) -C $(SOURCE_DIR)
	cp $(BRACKETS_EXE) $(BIN_DIR)

clean:
	$(MAKE) -C $(SOURCE_DIR) clean
	
all: brackets
