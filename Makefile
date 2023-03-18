all: main

CBQ_OUT_DIR=cbq/target/release
LIB_CBQ=$(CBQ_OUT_DIR)/libcbq.a

.PHONY: $(LIB_CBQ)
$(LIB_CBQ):
	RUSTFLAGS=-Zsanitizer=thread cargo +nightly --offline build --release --manifest-path=cbq/Cargo.toml

main: cbq.h cbq.cpp $(LIB_CBQ)
	g++ -fsanitize="thread" -O3 main.cpp cbq.cpp -o main -L $(CBQ_OUT_DIR) -lcbq
