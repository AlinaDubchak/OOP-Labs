# OOP-Labs

# Lab1

> Task 1

Віжтворити таке: вікно діалогу з повзуном горизонтального скролінгу (Horizontal scroll Bar) та дві 
кнопки: `[Так] і [Відміна]`. Рухаючи повзунок скролінгу користувач вводить число 
у діапазоні від 1 до 100. Після натискування кнопки `[Так]` вибране число буде 
відображатися у головному вікні. 

> Task 2

Два вікна діалогу. Спочатку з’являється перше, яке має дві кнопки: `[Далі >] і 
[Відміна]`. Якщо натиснути кнопку `[Далі >]`, то воно закриється і з’явиться друге 
длг вікно, яке має кнопки: `[< Назад], [Так] і [Відміна]`. Якщо натиснути кнопку 
`[<Назад]`, вікно закривається і перехід до першого вікна.

---

# Lab2,3

> Task 1

Створити графічний редактор. Для вибору типу об’єкта в графічному редакторі Lab2 повинно бути меню `"Об’єкти"` з 
чотирма підпунктами. Меню `"Об’єкти"` повинно бути праворуч меню `"Файл"` та ліворуч 
меню `"Довідка"`. Підпункти меню `"Об’єкти"` містять назви українською мовою 
геометричних форм – так, як наведено вище у порядку виконання роботи та методичних 
рекомендаціях. Геометричні форми згідно варіанту завдання.

> Варіант завдання

- статичний масив для Shape (5 mod 3 = 2) обсягом 105 
- "гумовий" слід (5 mod 4 = 1) – **суцільна лінія червоного кольору**
- Прямокутник:
  - ввід від центру до одного з кутів (5 mod 2 = 1) чорний контур з кольоровим заповненням (5 mod 5 = 1) 
  - колір заповнення - сірий (5 mod 6 = 5) 
- еліпс: 
  - ввід по двом протилежним кутам охоплюючого прямокутника (5 mod 2 = 1) 
  - чорний контур еліпсу з білим заповнення (5 mod 5 = 1) 
- позначка поточного типу об’єкту: 
  - в заголовку вікна (5 mod 2 = 1)

> Task 2

Для вибору типу об’єкту в графічному редакторі Lab3 повинно бути вікно `Toolbar` з 
кнопками відповідно типам об'єктів. Кнопки дублюють підпункти меню `"Об’єкти"`. 
Кнопки мають бути з підказками `(tooltips)`. Меню `"Об’єкти"` повинно бути праворуч 
меню `"Файл"` та ліворуч меню `"Довідка"`. Підпункти меню "Об’єкти" містять назви 
геометричних форм українською мовою. Геометричні форми згідно варіанту завдання.

> Варіант завдання

- статичний масив Shape *pcshape[N];
- "гумовий" слід суцільна лінія синього кольору для студентів, у яких (Ж mod 4 = 2)
- Прямокутник:
  - по двом протилежним кутам для студентів, у яких (Ж mod 2 = 0)
  - чорний контур з кольоровим заповненням для (Ж mod 5 = 1 або 2)
  - жовтий для (Ж mod 6 = 0)
- Еліпс:
  - від центру до одного з кутів охоплюючого прямокутника для (Ж mod 2 = 0)
  - чорний контур з білим заповненням для (Ж mod 5 = 1)
- Позначка поточного типу об’єкту, що вводиться:
  - в меню (метод OnInitMenuPopup) для студентів (Ж mod 2 = 0)

---

# Lab4

> Task 1

Запрограмувати `глобальний статичний об'єкт` класу MyEditor, геометричні форми з `пунктирною лінією 
синього кольору` викликом відповідної функції-члена класів Shape. Запрограмувати введення та відображення 
двох нових фігур – лінія з кружочками та каркас куба. Відповідні класи цих фігур запрограмувати саме `множинним успадкуванням`.
Для усіх шости типів форм зробити кнопки Toolbar з підказками.

> Варіант завждання
- глобальний статичний об'єкт класу MyEditor
- коло з синім заповненням
- прямокутник з білим заповненням

---

# Lab5

> Task 1

Запрограмувати вікно таблиці. Для його відкриття та закриття передбачити окремий пункт меню. Вікно таблиці повинно автоматично закриватися при виході з програми. Вікно таблиці – `немодальне вікно діалогу`. Таблиця повинна бути запрограмована як клас у окремому модулі. Інтерфейс модуля у вигляді оголошення класу таблиці. Запрограмувати запис файлу множини об’єктів, що вводяться.

> Варіант завдання

- Запрограмувати глобальний статичний об'єкт класу MyEditor у вигляді `Singleton Меєрса`.

> Додатковий функціонал

- користувач може виділити курсором рядок таблиці і відповідний об’єкт буде якось виділятися на зображенні у головному вікні.
- відповідний виділений об'єкт буде вилучений зі списку об'єктів

# Lab6

> Task 1

Головний проект – програма Lab6 має бути менеджером, який керує двома іншими 
програмами – Object2 та Object3. Програма Lab6 повинна автоматично, без участі 
користувача налагоджувати співпрацю та виконувати обмін повідомленнями з 
програмами Object2 та Object3

> Варіант завдання

- Lab6
  - Користувач вводить значення `n, Min, Max` у  діалоговому вікні. Програма викликає програми `Object2`, `Object3` і виконує обмін повідомленнями з ними для 
передавання, отримання інформації.
- Object2
  - Створює матрицю n×n цілих (int) чисел у діапазоні [Min – Max].  Показує числові значення у власному головному вікні. Записує дані в `Clipboard
Windows` у текстовому форматі
- Object3
  -  Зчитує дані з `Clipboard Windows`. Відображає значення детермінанту матриці у власному головному вікні
