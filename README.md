# 📐 ALQuadraticEquation

**Решай квадратные уравнения и строй их графики вместе с BAA GPT!**

![GitHub repo size](https://img.shields.io/github/repo-size/mathusha2023/quadratic_equation?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey?style=flat-square)

**ALQuadraticEquation (BAA GPT)** — это консольное приложение, которое умеет решать квадратные уравнения вида  
`ax² + bx + c = dx² + ex + f` и строить их графики прямо в терминале.  
Проект написан на C и распространяется с открытым исходным кодом.

---

## ✨ Возможности

- ➕ Решение квадратных уравнений общего вида (включая приведение подобных слагаемых)
- 📈 Построение графиков функций (если включено)
- 🗣️ Озвучивание результата (опционально)
- 🎨 Красивые ASCII-арты и цветной вывод
- 🧪 Встроенный режим тестирования
- ⚙️ Гибкая настройка через флаги запуска

---

## 📚 Документация

Подробная документация по проекту доступна по ссылке:  
[ALQuadraticEquation Documentation](https://mathusha2023.github.io/quadratic_equation/index.html)

Документация автоматически генерируется и разворачивается с помощью **GitHub Actions** при каждом обновлении репозитория.

---

## 🚀 Установка и запуск

### Требования

- Компилятор **clang++** (рекомендуется версия 10 или выше)
- `bash`

### Компиляция

```bash
./compile.sh
```
Скрипт compile.sh использует clang++ для сборки проекта.
После успешной компиляции появится исполняемый файл main.out.

### Запуск

```bash
./main.out
```
## 🧭 Использование

После запуска программа предложит ввести уравнение в формате:

```
ax^2 + bx + c = dx^2 + ex + f
```

Коэффициенты могут быть целыми или десятичными числами (например, `1.5`, `-2`).  
Степень нужно писать как `x^2`.

### Примеры корректного ввода

1. **Простое уравнение**  
   `x^2 - 3x + 2 = 0`

2. **С правой частью**  
   `2x^2 + 5x - 3 = x^2 - x + 1`

3. **Десятичные коэффициенты**  
   `0.5x^2 - 1.5x + 2 = 0`

4. **Некоторые коэффициенты равны нулю**  
   `2x + 1 = -x^2`

5. **Уравнение с отрицательными коэффициентами**  
   `-x^2 + 4x - 4 = -2x^2 + 8`

6. **Уравнение со степенями меньше 2**  
   `x^1 = x^2 - 5x^0 + 10`

---

## ⚙️ Флаги запуска

Вы можете настроить поведение программы, передав один или несколько флагов:

|   Флаг   | Описание |
|----------|----------|
| `--test` | Запуск встроенных тестов |
| `--disable-colors` | Отключить цветной вывод |
| `--disable-output-delay` | Убрать задержку при печати |
| `--disable-speech` | Отключить голосовое сопровождение |
| `--disable-graph` | Не строить график |
| `--disable-ascii-arts` | Убрать ASCII-арты и декоративные элементы |
| `--disable-all` | Отключить все дополнительные функции (эквивалентно `--disable-colors --disable-output-delay --disable-speech --disable-graph --disable-ascii-arts`) |

**Пример использования флагов:**

```bash
./main.out --disable-graph --disable-colors
```

---

## 📸 Скриншоты

![Старт программы](https://github.com/mathusha2023/quadratic_equation/blob/main/docs/screenshots/start.png?raw=true)

![Решение уравнений](https://github.com/mathusha2023/quadratic_equation/blob/main/docs/screenshots/equation.png?raw=true)

![Построенный график](https://github.com/mathusha2023/quadratic_equation/blob/main/docs/screenshots/graph.png?raw=true)

---

## 📞 Контакты

**Автор:** [@mathusha2023](https://t.me/mathusha2023)  
**Github:** [ссылка](https://github.com/mathusha2023)  
**Telegram:** [ссылка](https://t.me/mathusha2023)  
**VK:** [ссылка](https://vk.ru/mathusha2023)

---

## 📄 Лицензия

Этот проект распространяется под лицензией **MIT**. Подробности смотрите в файле [LICENSE](docs/LICENSE).

---

*Спасибо за использование ALQuadraticEquation!* 🚀