OPTS_SQLITE3 = `pkg-config --cflags --libs sqlite3`
OPTS_YAML-CPP = -L/usr/lib/x86_64-linux-gnu -lyaml-cpp -I/usr/include/yaml-cpp/ 
OPTS_FMT = `pkg-config --cflags --libs fmt`
ALL_OPTS = $(OPTS_FMT) $(OPTS_SQLITE3) ${OPTS_YAML-CPP}

INCLUDE = ./include
SRC = ./src
TESTS = ./tests
TESTS_BIN = ./tests_bin

CC = g++ -std=c++2a -g

# install 
BIN_PATH = /usr/local/bin
CFG_PATH = /etc/qkw-data
DATA = ./install-data
BUILD = ./build

MAN_PATH = /usr/share/man/man1
INSTALL-DATA = ./install-data



.PHONY: help
help:
	@echo "\n | HELP MENU"
	@echo "=================================================================="
	@echo "\"make build\" : to build qkw "
	@echo "\"make install\" : build, and install --qkw--"
	@echo "\"make clean\" : clean after installation"
	@echo "\"make run-tests\" : running all tests"

	@echo "  "
	@echo "Defaults: after installation"
	@echo "----------------------------"
	@echo "binary path: /usr/local/bin/qkw"
	@echo "config,database files: /etc/qkw-data/{userdata.db,qkw-config.yaml}"
	@echo "Please set environment variable \"QKW_CONFIG\" to qkw-config.yaml"
	@echo "=================================================================="


.PHONY: build
build : utils dir cmd _help qkw cli 
	@echo "--compiling--"
	$(CC) -o $(BUILD)/qkw -I$(INCLUDE) $(BUILD)/*.o $(ALL_OPTS)


.PHONY: install
install:
	cp $(BUILD)/qkw $(BIN_PATH)/
	mkdir -p $(CFG_PATH) >> /dev/null 
	mkdir -p $(MAN_PATH) >> /dev/null 
	cp $(INSTALL-DATA)/qkw.1.gz $(MAN_PATH)/
	cp $(INSTALL-DATA)/userdata.db $(CFG_PATH)/
	
	@echo "--------------------------------------------------------"
	@echo " Please set QKW_CONFIG to /etc/qkw-data/qkw-config.yaml"
	@echo "--------------------------------------------------------"




.PHONY: app
app : 
	$(CC) -o $(TESTS_BIN)/app_header_check -I$(INCLUDE) $(ALL_OPTS)  $(TESTS)/app_headers.cpp



.PHONY: test-utils
test-utils: utils
	$(CC) -o $(TESTS_BIN)/$@ $(TESTS)/tests_utils.cpp $(BUILD)/*.o $(ALL_OPTS) -I$(INCLUDE)


.PHONY: test-qkw
test-qkw: utils qkw
	$(CC) -o $(TESTS_BIN)/$@ $(TESTS)/tests_qkw.cpp $(BUILD)/*.o $(ALL_OPTS) -I$(INCLUDE)


.PHONY: test-dir
test-dir: utils qkw dir
	$(CC) -o $(TESTS_BIN)/$@ $(TESTS)/tests_dir.cpp $(BUILD)/*.o $(ALL_OPTS) -I$(INCLUDE)


.PHONY: test-cmd
test-cmd: utils qkw cmd

	$(CC) -o $(TESTS_BIN)/$@ $(TESTS)/tests_cmd.cpp $(BUILD)/*.o $(ALL_OPTS) -I$(INCLUDE)


.PHONY: run-tests
run-tests: test-qkw test-cmd test-dir test-utils


.PHONY: clean
clean:
	rm $(BUILD)/*.o



cmd : 
	$(CC) -o $(BUILD)/$@.o -I$(INCLUDE) $(ALL_OPTS) -c $(SRC)/$@.cpp

utils : 
	$(CC) -o $(BUILD)/$@.o -I$(INCLUDE) $(ALL_OPTS) -c $(SRC)/$@.cpp

qkw : 
	$(CC) -o $(BUILD)/$@.o -I$(INCLUDE) $(ALL_OPTS) -c $(SRC)/$@.cpp

dir : 
	$(CC) -o $(BUILD)/$@.o -I$(INCLUDE) $(ALL_OPTS) -c $(SRC)/$@.cpp

cli : 
	$(CC) -o $(BUILD)/$@.o -I$(INCLUDE) $(ALL_OPTS) -c $(SRC)/$@.cpp

_help : 
	$(CC) -o $(BUILD)/help.o -I$(INCLUDE) $(ALL_OPTS) -c $(SRC)/help.cpp


