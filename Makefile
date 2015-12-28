CC = g++
MODULES= Config.o MapFile.o MapFileEntry.o TextFile.o Log.o AtomicBoolean.o AtomicCounter.o AtomicFloat.o AtomicULong.o Mutex.o ThreadPool.o ThreadWrapper.o ConditionVariable.o PrintStackTrace.o StackTrace.o
OBJECTS=
RCLOBJECTS= src/compat/pstdint.h src/file/config/Config.cpp src/file/config/Config.hpp src/file/config/ConfigEnv.h src/file/MapFile.cpp src/file/MapFile.hpp src/file/MapFileEntry.cpp src/file/MapFileEntry.hpp src/file/TextFile.cpp src/file/TextFile.hpp src/log/Log.hpp src/log/Log.cpp src/threading/AtomicBoolean.cpp src/threading/AtomicBoolean.hpp src/threading/AtomicCounter.cpp src/threading/AtomicCounter.hpp src/threading/AtomicFloat.cpp src/threading/AtomicFloat.hpp src/threading/AtomicULong.cpp src/threading/AtomicULong.hpp src/threading/Guard.hpp src/threading/LockedQueue.hpp src/threading/Mutex.cpp src/threading/Mutex.hpp src/threading/Queue.hpp src/threading/RWLock.hpp src/threading/Threading.h src/threading/ThreadPool.cpp src/threading/ThreadPool.hpp src/threading/ThreadStarter.hpp src/threading/ThreadWrapper.cpp src/threading/ThreadWrapper.hpp src/Array.hpp src/Common.h src/ConditionVariable.cpp src/ConditionVariable.hpp src/Errors.h src/PrintStackTrace.cpp src/PrintStackTrace.h src/Singleton.hpp src/StackTrace.cpp src/StackTrace.hpp
LDFLAGS = -Wl,-rpath,/usr/lib
LIBS = -L/usr/local/lib -lReadToueiConfig

all: MTLib.so

MTLib.so: $(MODULES)
	$(CC) -shared $(MODULES) -o MTLib.so

Config.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/file/config/Config.cpp -o Config.o

MapFile.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/file/MapFile.cpp -o MapFile.o

MapFileEntry.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/file/MapFileEntry.cpp -o MapFileEntry.o

TextFile.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/file/TextFile.cpp -o TextFile.o

Log.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/log/Log.cpp -o Log.o

AtomicBoolean.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/threading/AtomicBoolean.cpp -o AtomicBoolean.o

AtomicCounter.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/threading/AtomicCounter.cpp -o AtomicCounter.o

AtomicFloat.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/threading/AtomicFloat.cpp -o AtomicFloat.o

AtomicULong.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/threading/AtomicULong.cpp -o AtomicULong.o

Mutex.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/threading/Mutex.cpp -o Mutex.o

ThreadPool.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/threading/ThreadPool.cpp -o ThreadPool.o

ThreadWrapper.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/threading/ThreadWrapper.cpp -o ThreadWrapper.o

ConditionVariable.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/ConditionVariable.cpp -o ConditionVariable.o

PrintStackTrace.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/PrintStackTrace.cpp -o PrintStackTrace.o

StackTrace.o: $(RCLOBJECTS)
	$(CC) -fpic -c src/StackTrace.cpp -o StackTrace.o

install:
	cp MTLib.so /usr/local/lib

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o
	rm -f MTLib.so

.PHONY: all
.PHONY: count
.PHONY: clean
.PHONY: install
