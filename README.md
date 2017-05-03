# generation-terrain

## На русском

Мой дипломный проект. Был защищен в июне 2016 года. Изначально код хранился в приватном репозитории bitbucket. Решил выложить в открытый доступ. Я очистил от лишних элементов, которые не нужно хранить в репозитории.

При написании работы я опирался на следующие статьи(включая материалы на которых основаны они):

https://habrahabr.ru/post/111538/

https://habrahabr.ru/post/142592/

по DirectX 11:

https://www.braynzarsoft.net/viewtutorial/q16390-braynzar-soft-directx-11-tutorials

http://ru.directx.wikia.com/wiki/DirectX_11_шаг_за_шагом

В интернете есть более удачные статьи нежели те которые я привел, к сожелению они мне попадались уже после сдачи работы.

Генерация карты имеет некоторые дефекты, например не генерируется карты больше 512, не было времени разобраться в причинах, по хорошему надо переписать, возможно с использованием более лучшего алгоритма. Часть моментов написаны для того, чтобы приложение не сломалось в неподходящий момент. 

Я не планирую поддержку или исправления на данный момент.

---
visualization написан на c++, остальное написано на c#. 
Чтобы скомпилировать проект “visualization” необходимо подключить библиотеку:
https://github.com/Microsoft/DirectXTK

## On English

It’s my graduation project. It was protected in June 2016. Code project was stored in a private bitbucket repository. I decided to lay out in the open access. I cleared of unnecessary items that do not need to be stored in the repository.

When writing the work, I relied on the following articles (including the materials on which they are based):

https://habrahabr.ru/post/111538/

https://habrahabr.ru/post/142592/

DirectX 11:

https://www.braynzarsoft.net/viewtutorial/q16390-braynzar-soft-directx-11-tutorials

http://ru.directx.wikia.com/wiki/DirectX_11_шаг_за_шагом

On the Internet there are better articles than those which I have given to yet they came across to me after the delivery of the project.

Generation of the card has some defects, for example, no more than 512 cards are generated, there was no time to understand the reasons, it is necessary to rewrite the good, perhaps using a better algorithm. Some of the moments are written so that the application does not break at the wrong time.

I do not plan to support or fix at this time.

---

“visualization” is written in c ++, the rest is written in c #.
To compile the "visualization" project, you need to connect the library:
https://github.com/Microsoft/DirectXTK
