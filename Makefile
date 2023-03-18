all: main

CBQ_OUT_DIR=cbq/target/debug
LIB_CBQ=$(CBQ_OUT_DIR)/libcbq.a

.PHONY: $(LIB_CBQ)
$(LIB_CBQ):
	cargo --offline build --manifest-path=cbq/Cargo.toml

main: $(LIB_CBQ)
	g++ main.cpp -o main -L $(CBQ_OUT_DIR) -lcbq