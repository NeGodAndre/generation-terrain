# generation-terrain


Мой дипломный проект. Был защищен в июне 2016 года. Изначально код хранился на приватном репозитории bitbucket. Решил выложить в открытый доступ. Очистил от лишних элементов которые не нужны в репозитории.

---

visualization написан на c++, остальное написано на c#.
Для компиляции проекта “visualization” необходимо подключить библиотеку https://github.com/Microsoft/DirectXTK

---
Опирался в описании на следующие статьи(и те которые ссылаются эти):

https://habrahabr.ru/post/111538/

https://habrahabr.ru/post/142592/

по DirectX 11 

https://www.braynzarsoft.net/viewtutorial/q16390-braynzar-soft-directx-11-tutorials

http://ru.directx.wikia.com/wiki/DirectX_11_шаг_за_шагом

В интернете есть более удачные статьи нежели те которые я привел, к сожелению они мне попадались уже после сдачи.

Генерация карты имеет некоторые дефекты, например не генерируется карты больше 512, не было времени, по хорошему надо переписать, возможно с использованием более лучшего алгоритма. Многие моменты написаны так потому что нужно была заглушка чтоб не упала в неподходящий момент. Поддержку или исправление на данный момент не планирую.
