# calculator-ulanova-au  

**calculator-ulanova-au** – это консольное приложение на C для вычисления арифметических выражений с поддержкой работы с целыми и вещественными числами. Программа принимает выражение в качестве входных данных, анализирует его, обрабатывает операторы и выводит результат вычисления. Калькулятор *calculator-ulanova-au* представляет собой простое, но мощное консольное приложение, разработанное для вычисления арифметических выражений. Оно поддерживает как целочисленные, так и вещественные вычисления, что делает его универсальным инструментом для решения различных математических задач. Программа отличается высокой надежностью благодаря встроенной системе обработки ошибок, включая проверку на корректность ввода и обработку исключительных ситуаций, таких как деление на ноль или несбалансированные скобки. Простота использования и возможность работы в двух режимах делают этот калькулятор удобным как для учебных целей, так и для повседневных вычислений.

## Возможности  

- Поддержка базовых арифметических операторов: `+`, `-`, `*`, `/`, `(`, `)`.  
- Автоматический разбор выражений с учетом приоритетов операций.  
- Работа с пробелами в выражении – пробелы автоматически игнорируются.  
- Возможность работы в двух режимах: целочисленном и вещественном.  
- Безопасная обработка ошибок, включая недопустимые символы, деление на ноль и несбалансированные скобки.  

## Установка и запуск  

1. **Клонирование репозитория:**  
   ```sh
   git clone https://github.com/ainazikulanova/calculator-ulanova-au.git
   cd calculator-ulanova-au
   ```

2. **Компиляция проекта:**  
   ```sh
   make
   ```

3. **Запуск в целочисленном режиме:**  
   ```sh
   ./build/app.exe
   ```

4. **Запуск в режиме с плавающей запятой:**  
   ```sh
   ./build/app.exe --float
   ```

5. **Запуск тестов:**  
   - Юнит-тесты:  
     ```sh
     make run-unit-test
     ```  
   - Интеграционные тесты:  
     ```sh
     make run-integration-tests
     ```  

6. **Форматирование кода:**  
   Для форматирования кода используйте:  
   ```sh
   make format
   ```

7. **Примеры использования:**  
   ```sh
   echo "5/2=2" | ./build/app.exe
   echo "5/2=2.5" | ./build/app.exe --float
   ```

## Структура проекта  

- `src/main.c` – основной код калькулятора.  
- `tests/` – тесты для проверки работы приложения.  
- `.clang-format` – настройки форматирования кода.  
- `.gitignore` – список файлов, исключённых из Git.  
- `Makefile` – правила сборки проекта.  
- `README.md` – документация.  
- `pgp1.key`, `pgp2.key` – ключи PGP для подписи кода.  

## Принцип работы  

Программа считывает математическое выражение из входного потока и анализирует его. Она проверяет валидность символов, удаляет пробелы и определяет порядок выполнения операций. Затем выражение обрабатывается с учетом приоритетов, после чего вычисляется окончательный результат.  

Алгоритм поддерживает работу с вложенными скобками и разными приоритетами операций. В режиме `--float` все вычисления выполняются с плавающей точкой, а в стандартном режиме – в целых числах.  

## Обработка ошибок  

В программе предусмотрены проверки на:  
- Недопустимые символы в выражении.  
- Несбалансированные скобки.  
- Двойные операторы (например, `++`, `--`).  
- Деление на ноль.  
- Ошибки переполнения при вычислениях.  

При возникновении ошибки программа завершает работу с кодом выхода.

