.PHONY: all clean test gcov_report cf val
.SILENT: all clean test gcov_report

# Объекты компиляции
LIB = # имя статической библиотеки, если компилим её
SRC = # все имена (без расширений) c-файлов
SRC_O = $(SRC:%=s21_%.o)

# Настройки компиляции
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -O2
CPOSTFLAGS = -lm -lpthread # эти флаги должны стоять последними
BUILD_DIR = build/

# Настройки компиляции тестов
TEST_POST_FLAGS = -lcheck -lpthread -lrt -lm
TEST_DIR = test/
TEST_SRC = test.c
TEST_TARGET = check.run

# Настройки проверки покрытия
GCOV_BUILD_DIR = gcov/
GCOV_REPORT_DIR = report/
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# Цель по умолчанию
all: TARGET = $(LIB)
all: clean $(TARGET)

# Сборка статической библиотеки .a из .o-файлов
# TODO Заменить lib.a на реальное название (не подставлять шаблон!)
lib.a: $(SRC_O)
	ar rcs $@ $^
	rm -f $(BUILD_DIR)*.o

# Тестирование
verb: DLVL := -DCK_LVL=CK_VERBOSE
test: DLVL := -DCK_LVL=CK_NORMAL
verb test: $(TEST_SRC) clean $(LIB)
	@$(CC) $(CFLAGS) $(DLVL) $(GCOV_FLAGS) -o $(TEST_TARGET) $< $(TEST_POST_FLAGS)
	@./$(TEST_TARGET)

# HTML-отчёт о покрытии тестами
#g: gcov_report
#	@lynx $(CGOV_REPORT_DIR)index.html

# Расчёт покрытия тестами
# gcov_report: CFLAGS := $(CFLAGS) $(GCOV_FLAGS)
# gcov_report: clean $(LIB) test
# 	gcovr -r . --filter "s21_*.*" --html --html-details -o $(GCOV_REPORT_DIR)index.html
#	$(MAKE) clean_o clean_gcov clean_compiled -s

# Проверка стиля (не нормализация, только проверка)
cf:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h

# Проверка на утечки
val:
	valgrind --leak-check=full # что проверяем?

# Запуск тестов в контейнере
#verter: CHECK_FLAGS = $(CHECK_FLAGS_VERTER)
#verter: clean
#	docker build -t verter:sp .
#	docker run -v $(shell pwd):/pro verter:sp make -C /pro CHECK_FLAGS="$(CHECK_FLAGS_VERTER)" test
#	docker container prune -f
#	$(MAKE) clean --no-print-directory

# Запуск тестов на Ubuntu
#ubuntu:
#	$(MAKE) test CHECK_FLAGS="$(CHECK_FLAGS_UBUNTU)"

# Компиляция (без линковки)
%.o: %.c %.h
	@$(CC) $(CFLAGS) -c $< -o $@

# Разные очистки

clean_o: CLEAN_DIR = $(BUILD_DIR)
clean_o: clean_dir

clean_gcov: CLEAN_DIR = $(GCOV_BUILD_DIR)
clean_gcov: clean_dir

clean_report: CLEAN_DIR = $(GCOV_REPORT_DIR)
clean_report: clean_dir

clean_dir:
	@cd $(CLEAN_DIR) && rm -f *

clean_compiled:
	@rm -f *.a *.run

clean: clean_o clean_gcov clean_report clean_compiled

# Для удобства, чтобы не было опечаток
clear: clean
