LAB1(Создание нити):  
Напишите программу, которая создает нить. Используйте атрибуты по умолчанию. Родительская и вновь созданная нити должны распечатать десять строк текста.  

LAB2(Ожидание нити):  
Модифицируйте программу упр. 1 так, чтобы вывод родительской нити производился после завершения дочерней. Используйте pthread_join.  

LAB3(Параметры нити):  
Напишите программу, которая создает четыре нити, исполняющие одну и ту же функцию. Эта функция должна распечатать последовательность текстовых строк, переданных как параметр. Каждая из созданных нитей должна распечатать различные последовательности строк.  

LAB4(Принудительное завершение нити):  
Дочерняя нить должна распечатывать текст на экран. Через две секунды после создания дочерней нити, родительская нить должна прервать ее вызовом функции pthread_cancel. 

LAB5(Обработка завершения нити):  
Модифицируйте программу упр. 4 так, чтобы дочерняя нить перед завершением распечатывала сообщение об этом. Используйте pthread_cleanup_push.  

LAB6(Sleepsort):  
Реализуйте уникальный алгоритм сортировки sleepsort с асимптотикой O(N) (по процессорному времени).
На стандартный вход программы подается не более 100 строк различной длины. Вам необходимо вывести эти строки, отсортированные по длине. Строки одинаковой длины могут выводиться в произвольном порядке.

Для каждой входной строки, создайте нить и передайте ей эту строку в качестве параметра. Нить должна вызвать sleep(2) или usleep(2) с параметром, пропорциональным длине этой строки. Затем нить выводит строку в стандартный поток вывода и завершается. Не следует выбирать коэффициент пропорциональности слишком маленьким, вы рискуете получить некорректную сортировку.  

LAB8(Вычисление Пи):  
Напишите программу, которая вычисляет число Пи при помощи ряда Лейбница. Количество итераций может определяться во время компиляции. Для передачи частичных сумм ряда, подсчитанных потоками, используйте pthread_exit(3C)/pthread_join(3C).

Обратите внимание, что на 32разрядных платформах sizeof(double)>sizeof(void *), поэтому частичную сумму ряда нельзя преобразовывать к указателю, для нее надо выделять собственную память.  

LAB11(Синхронизированный вывод):  
Модифицируйте программу упр. 1 так, чтобы вывод родительской и дочерней нитей был синхронизован: сначала родительская нить выводила первую строку, затем дочерняя, затем родительская вторую строку и т.д. Используйте мутексы. Рекомендуется использовать мутексы типа PTHREAD_MUTEX_ERRORCHECK.

Явные и неявные передачи управления между нитями (sleep(3C)/usleep(3C), sched_yield(3RT)) и холостые циклы разрешается использовать только на этапе инициализации.  

LAB13(Синхронизированный вывод 2):  
Решите задачу 11 с использованием условной переменной и минимально необходимого количества мутексов.  

LAB14(Синхронизированный вывод 3):  
Решите задачу 11 с использованием двух семафоров-счетчиков.  

LAB24(Производственная линия):  
Разработайте имитатор производственной линии, изготавливающей винтики (widget). Винтик собирается из детали C и модуля, который, в свою очередь, состоит из деталей A и B. Для изготовления детали A требуется 1 секунда, В – две секунды, С – три секунды. Задержку изготовления деталей имитируйте при помощи sleep. Используйте семафоры-счетчики.  

LAB28(Псевдомногопоточный HTTP-клиент):  
Реализуйте простой HTTP-клиент. Он принимает один параметр командной строки – URL. Клиент делает запрос по указанному URL и выдает тело ответа на терминал как текст (т.е. если в ответе HTML, то распечатывает его исходный текст без форматирования). Вывод производится по мере того, как данные поступают из HTTP-соединения. Когда будет выведено более экрана (более 25 строк) данных, клиент должен продолжить прием данных, но должен остановить вывод и выдать приглашение Press space to scroll down.

При нажатии пользователем клиент должен вывести следующий экран данных. Для одновременного считывания данных с терминала и из сетевого соединения используйте системный вызов select.

Lab30(Многопоточный HTTP-клиент):  
Реализуйте задачу упр. 28, используя две нити, одну для считывания данных из сетевого соединения, другую для взаимодействия с пользователем.  







