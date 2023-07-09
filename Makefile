all:
	g++ PreProcess.cpp -o preprocess
	g++ Encoding.cpp -o encode
	g++ Decode.cpp -o decode
