all:TinyWindow

TinyWindow: ./
	g++ -std=c++11 -DSO -w -g -fpermissive -o ./TinyWindowTest ./*.cpp -I./include -lGL -lX11 2> errors.txt


