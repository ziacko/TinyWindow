all:TinyWindow

TinyWindow: ./
	g++ -std=c++11 -DSO -w -g -fpermissive -o ./TinyWindowTest ./*.h ./*.cpp -I../dependencies/ -lGLU -lGL -lX11 -lXext 2> errors.txt


