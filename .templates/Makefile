.PHONY: all clean test gcov_report
.SILENT: all clean test gcov_report lib.a cf

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -O2
CPOSTFLAGS = -lm -lthread # эти флаги должны стоять последними

CHECK_FLAGS_VERTER = s21_string.a -DDEBUG -lcheck -lpthread -lrt -lm
CHECK_FLAGS_UBUNTU = $(CHECK_FLAGS_VERTER) -lsubunit
CHECK_FLAGS = $(CHECK_FLAGS_VERTER)

SRC = # все имена (без расширений) c-файлов
SRC_O = $(SRC:%=s21_%.o)

# Цель по умолчанию
all: clean lib.a 

# Сборка статической библиотеки .a из .o-файлов
lib.a: $(SRC_O)
	ar rcs $@ $^
	rm -f *.o

# Тестирование
verb: DLVL := -DCK_LVL=CK_VERBOSE
test: DLVL := -DCK_LVL=CK_NORMAL
verb test: CHECK_FLAGS=$(CHECK_FLAGS_UBUNTU)
verb test: test.c clean s21_string.a
	@$(CC) $(CFLAGS) $(DLVL) $(GCOV_FLAGS) -o check.run $< $(CHECK_FLAGS)
	@./check.run

# HTML-отчёт о покрытии тестами
g: gcov_report
	@lynx report/index.html

# Расчёт покрытия тестами
gcov_report: GCOV_FLAGS = -fprofile-arcs -ftest-coverage
gcov_report: DIR = report/
gcov_report: clean s21_string.a test
	gcovr -r . --filter "s21_*.*" --html --html-details -o $(DIR)index.html
	$(MAKE) clean_o clean_gcov clean_compiled -s

# Проверка стиля (не нормализация, только проверка)
cf:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h

# Запуск тестов в контейнере
verter: CHECK_FLAGS = $(CHECK_FLAGS_VERTER)
verter: clean
	docker build -t verter:sp .
	docker run -v $(shell pwd):/pro verter:sp make -C /pro CHECK_FLAGS="$(CHECK_FLAGS_VERTER)" test
	docker container prune -f
	$(MAKE) clean --no-print-directory

# Запуск тестов на Ubuntu
ubuntu:
	$(MAKE) test CHECK_FLAGS="$(CHECK_FLAGS_UBUNTU)"

# Компиляция (без линковки)
%.o: %.c %.h
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

# Разные очистки
clean_o:
	@rm -f *.o

clean_gcov:
	@rm -f *.gcov* gcov.* *.gcno *.gcda

clean_report:
	@cd report && rm -f *

clean_compiled:
	@rm -f *.a *.run

clean: clean_o clean_gcov clean_report clean_compiled

# Для удобства, чтобы не было опечаток
clear: clean
