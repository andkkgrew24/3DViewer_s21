BASE_FLAGS = -Werror -Wall -Wextra -std=c11
OS := $(shell uname -s)
UNIX_CHECK_F = `pkg-config --cflags --libs check` #-pthread -lcheck_pic -pthread -lrt -lm -lsubunit
MAC_CHECK_F = -lcheck -lm
CHECK_FLAGS = -lcheck
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
EXPLORER = open;

ifeq ($(OS), Linux)
 APP = cpp
 APPRN = 3DViewerV1
 CHECK_FLAGS=$(UNIX_CHECK_F)
 EXPLORER = xdg-open
 LEAK_CHECK =valgrind --leak-check=yes ./test
else ifeq ($(OS), Darwin)
 APP = cpp.app
 APPRN = 3DViewerV1.app
 CHECK_FLAGS=$(MAC_CHECK_F)
 EXPLORER = open
 LEAK_CHECK = CK_FORK=no leaks --atExit -- ./test
else
	@echo "Undetermined system \n"
endif

MAIN_SRCS =\
 s21_3D_Viewer.c\
 s21_affin_transforms.c\

MAIN_OBJS = $(MAIN_SRCS:.c=.o)

all: clean s21_3D_Viewer.a test gcov_report

s21_3D_Viewer.a: $(MAIN_OBJS) 
	ar rc $@ $(MAIN_OBJS)
	ranlib $@

test.c: tests.check
	checkmk clean_mode=1 $< > $@

test: test.c s21_3D_Viewer.a
	gcc $^ $(BASE_FLAGS) -o test $(CHECK_FLAGS)
	./test

gcov_report: test.c
	gcc $^ $(MAIN_SRCS) $(BASE_FLAGS) $(GCOV_FLAGS) -g -o $@.out $(CHECK_FLAGS)
	./$@.out
	gcov s21_*.gcda 
	lcov -t "cov" -o cov.info -c -d .
	genhtml -o gcov_report cov.info
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	$(EXPLORER) ./gcov_report/index.html

check:
	clang-format -style=Google -i *.c
	clang-format -style=Google -n *.c

leaks: test
	$(LEAK_CHECK)

install: 
	make clean
	mkdir -p build
	cd cpp && qmake && make && make clean && rm Makefile
	mv cpp/$(APP) build/$(APP)
	mv build/$(APP) build/$(APPRN)
	
uninstall:
	rm -rf build*

dvi:
	$(EXPLORER) ./docs/documentation.html

dist:
	rm -rf Archive_3D_Viewer_v1.0/
	mkdir Archive_3D_Viewer_v1.0/
	mkdir Archive_3D_Viewer_v1.0/src
	mv ./build/$(APPRN) Archive_3D_Viewer_v1.0/src/$(APPRN)
	tar cvzf Archive_3D_Viewer_v1.0.tgz Archive_3D_Viewer_v1.0/
	rm -rf Archive_3D_Viewer_v1.0/

clean:
	rm -f test
	rm -f test.c
	rm -rf gcov_report/
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov
	rm -f *.info
	rm -f *.o
	rm -f *.a
	rm -f *.txt
	rm -f *.out
	rm -rf Archive_3D_Viewer_v1.0 
	rm -rf *tgz
	rm -rf build

rebuild: clean all