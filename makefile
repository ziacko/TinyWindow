all:TinyWindow

TinyWindow: ./
	g++ -std=c++11 -DSO -w -g -fpermissive -o ./TinyWindowTest ./*.h ./*.cpp -I../dependencies/ -lGL -lX11 2> errors.txt


