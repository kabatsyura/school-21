# Операционные системы UNIX/Linux (Базовый)
## Part 1. Установка ОС

Скачал и установил следующее ПО

- [VirtualBox]
- [Ubuntu Server 20.4 lts]

![Версия Ubuntu](images/task_1.png)

## Part 2. Создание пользователя

Создаем нового пользователя с определенной группой
```sh
sudo useradd -G adm <пользователь>
```
Ниже пример проверки, что такой пользователь существует в группе "adm"
![Проверка пользователя в группе](images/task_2_test_1.jpg)

Новый пользователь должен быть в выводе команды
```sh
cat /etc/passwd
```

![Проверка файла /etc/passwd](images/task_2.2.jpg)

Каждая  строка  представляет  одного  пользователя  и  состоит  из  семи  полей,  разделенных двоеточиями. Эти поля таковы.
- `Имя пользователя.`
- `Зашифрованный пароль пользователя.` В большинстве систем Linux пароль  в  действительности  не  хранится  в  файле  *passwd*,  а  помещается  в  файл  *shadow*  (см. подраздел 7.3.3). Формат файла *shadow* похож на формат файла *passwd*, однако  у обычных пользователей нет разрешения на чтение файла *shadow*. Второе поле  в файле *passwd* или *shadow* является зашифрованным паролем, он выглядит как  нечитаемый  набор  символов,  например  d1CVEWiB/oppc.  Пароли  в  системе  Unix  никогда не хранятся в виде простого текста.
Символ x во втором поле файла *passwd* говорит о том, что зашифрованный пароль  хранится в файле *shadow*. Звездочка (*) сообщает, что этот пользователь не может 
7.3. Файлы управления пользователями 179
совершать вход в систему, а если это поле пусто (то есть вы видите два двоеточия  подряд,  ::),  то  для  входа  в  систему  пароля  не  требуется.  Остерегайтесь  пустых  паролей. Никогда не следует регистрировать пользователя без пароля.
- `Идентификатор пользователя (UID)`, который представляет данного пользо­ вателя ядру. Можно создать две записи с одинаковым идентификатором поль­ зователя, но это будет сбивать с толку и вас, и ваше программное обеспечение.  Старайтесь использовать уникальные идентификаторы.
- `Идентификатор группы (GID)` представляет собой одну из нумерованных за­ писей в файле /etc/group. Группы задают права доступа к файлам и кое­что еще.  Данная группа называется также первичной группой пользователя.
- `Реальное имя пользователя` (часто называется полем GECOS). В этом поле вы  можете встретить запятые, которые отделяют номер комнаты и номер телефона.
- `Домашний каталог пользователя.`
- `Оболочка пользователя` (команда, которая запускается при работе пользовате­
ля в терминале).

![Как отражен пользователь в файле](images/task_2.3.jpg)

## Part 3. Настройка сети ОС

**Задать название машины вида user-1**

Первоначальные настройки ПК были следующими:
![Имя ПК после перезагрузки](images/task_3.2_user_1.jpg)

```sh
sudo vim /etc/hostname
```

После редактирования файла и перезагрузки системы, *hostname* будет отображаться следующим образом:

![Имя ПК после перезагрузки](images/task_3.1_user_1_after_restart.jpg)

**Установить временную зону, соответствующую вашему текущему местоположению.**

Первоначальный часовой пояс:
![Первоначальный часовой пояс](images/task_3.2_timezone_1.jpg)

```sh
sudo timedatectl set-timezone <нужный часовой пояс>
```

Как теперь отображается часовой пояс, после установки:
![Отредактированный часовой пояс](images/task_3.2_set_timezone.jpg)

**Вывести названия сетевых интерфейсов с помощью консольной команды.**

![Теория о lo](images/task_3.3_about_lo.jpg)
![вывод команды ip link show](images/task_3.3_lo.jpg)

**Используя консольную команду получить ip адрес устройства, на котором вы работаете, от DHCP сервера.**

Понятие о протоколе DHCP

Когда вы настраиваете сетевой хост на автоматическое получение конфигурации из  сети, вы указываете ему, чтобы он использовал протокол DHCP (Dynamic Host  Configuration Protocol, протокол динамического конфигурирования хоста) для полу­ чения IP­адреса, маски подсети, шлюза по умолчанию и серверов DNS. Помимо того  что не приходится вводить эти параметры вручную, протокол DHCP обладает дру­ гими преимуществами для сетевого администратора, такими как предотвращение  конфликтов IP­адресов и минимизация последствий при изменении сети. Нечасто  можно встретить современную сеть, которая не использует протокол DHCP.
Чтобы хост получал свою конфигурацию с помощью протокола DHCP, он дол­ жен быть способен отправлять сообщения DHCP­серверу той сети, к которой он  подключен. Следовательно, каждая физическая сеть должна обладать собственным  DHCP­сервером, а в простой сети его роль обычно выполняет маршрутизатор.
Когда  компьютер  запрашивает  IP­адрес  у  сервера  DHCP,  на  самом  деле  он  просит  об  *аренде*  этого  адреса  на  некоторое  время.  Когда  аренда  заканчивается,  клиент может запросить обновление аренды.

![ip addr](images/task_3.4._DHCP.jpg)

**Определить и вывести на экран внешний ip-адрес шлюза (ip) и внутренний IP-адрес шлюза, он же ip-адрес по умолчанию (gw).**

Внутренний ip адрес
![ip внутренний](images/task_3.5_vnutrenniy_ip.jpg)

Внешний ip адрес. Пример, как видят тебя внешние сайты.
![ip внешний](images/task_3.5_vneshniy_ip.jpg)

**Задать статичные (заданные вручную, а не полученные от DHCP сервера) настройки ip, gw, dns (использовать публичный DNS серверы, например 1.1.1.1 или 8.8.8.8).**

![1](images/task_3.6.1_prepare.jpg)

![2](images/task_3.6.2.1.jpg)

![3](images/task_3.6.3.jpg)

![4](images/task_3.6.4.jpg)

## Part 4. Обновление ОС

Перед обновлением необходимо выполнить команду `apt-get update`, которая обновит информацию о пакетах, содержащихся в репозиториях, чтобы в процессе обновления получить самые последние версии пакетов.

Далее обновляем через `dist-upgrade`. Делает тоже самое, что `upgrade` плюс выполяет «умное» разрешения конфликтов версий пакетов. При конфликтах пакетов Ubuntu попытается обновите наиболее важные пакеты за счет менее важных. Поэтому команда `dist-upgrade` может установить дополнительные пакеты или удалить один из конфликтующих пакетов.

![update](images/task_4.1.jpg)
![Процесс](images/task_4.2_result.jpg)
![auturemove](images/task_4.3._remove.jpg)
![update-manager-core](images/task_4.4._update_manager.jpg)
![do-release-upgrade](images/task_4.5..jpg)
![upgrade](images/task_4.6.jpg)

## Part 5. Использование команды sudo

Sudo - это аналог выполнения какой-либо команды от имени администратора.

![upgrade](images/task_5.jpg)
![upgrade](images/task_5.2.jpg)

## Part 6. Установка и настройка службы времени

Данную задачу я проделал ранее. Проверка ниже:

![upgrade](images/task_6.jpg)

## Part 7. Установка и использование текстовых редакторов

**Установить текстовые редакторы VIM (+ любые два по желанию NANO, MCEDIT, JOE и т.д.)**

Используя каждый из трех выбранных редакторов, создайте файл test_X.txt, где X -- название редактора, в котором создан файл. Напишите в нём свой никнейм, закройте файл с сохранением изменений.

**NANO**

![Nano](images/task_7.1_nano_install.jpg)
![Nano](images/task_7.1.1._print.jpg)
![Nano](images/task_7.1.2_final.jpg)

**JOE**
![JOE](images/task_7.2_install.jpg)
![JOE](images/task_7.2.1_create.jpg)
![JOE](images/task_7.2.3_print.jpg)
![JOE](images/task_7.2.4_result.jpg)

**MCEDIT**
![MCEDIT](images/task_7.3_install.jpg)
![MCEDIT](images/task_7.3.2_print.jpg)
![MCEDIT](images/task_7.3.3._result.jpg)

Используя каждый из трех выбранных редакторов, откройте файл на редактирование, отредактируйте файл, заменив никнейм на строку "21 School 21", закройте файл без сохранения изменений.

**NANO**

![Nano](images/task_7.4.1_nano.jpg)

**JOE**
![JOE](images/task_7.4.2_joe.jpg)

**MCEDIT**
![MCEDIT](images/task_7.4.3_mcedit.jpg)

Используя каждый из трех выбранных редакторов, отредактируйте файл ещё раз (по аналогии с предыдущим пунктом), а затем освойте функции поиска по содержимому файла (слово) и замены слова на любое другое.

**NANO**
![NANO](images/task_7.5.1.jpg)
![NANO](images/task_7.5.2_cat.jpg)
![NANO](images/task_7.5.2_result.jpg)
![NANO](images/task_7.5.2.jpg)

**JOE**
![JOE](images/task_7.5.3.jpg)
![JOE](images/task_7.5.3_result.jpg)
![JOE](images/task_7.5.3_cat.jpg)

**MCEDIT**
![MCEDIT](images/task_7.5.4_result.jpg)
![MCEDIT](images/task_7.5.4.jpg)

## Part 8. Установка и базовая настройка сервиса SSHD

**Установить службу SSHd.**

В моем случае, данный пакет уже был установлен.
![Install sshd](images/task_8.1_install.jpg)

**Добавить автостарт службы при загрузке системы.**
![autostart](images/task_8.2_autostart.jpg)

**Перенастроить службу SSHd на порт 2022.**
![reconfigure](images/task_8.3_how_it_was.jpg)

Чтобы отредактировать настройки службы, нужно зайти в следующий файл:
```sh
sudo vim /etc/ssh/sshd_config
```
![reconfigure](images/task_8.4_change_port.jpg)
![reconfigure](images/task_8.4_check.jpg)

**Используя команду ps, показать наличие процесса sshd. Для этого к команде нужно подобрать ключи.**
![final_sshd](images/task_8.5_final.jpg)

## Part 9. Установка и использование утилит top, htop

Для установки, используйте следующую команду.

```sh
sudo apt install top
```
Пример как работает программа.

![top](images/task_9.1_top.jpg)

- uptime = 1:28
- количество авторизованных пользователей = 1
- общую загрузку системы = 0.0
- общее количество процессов  = 93
- загрузку cpu = 0.0
- загрузку памяти = 148.2
- pid процесса занимающего больше всего памяти = 1393
- pid процесса, занимающего больше всего процессорного времени = 1

Для установки, используйте следующую команду.

```sh
sudo apt install htop
```
Пример как работает сортировка.

![htop](images/task_9.2_sort_CPU.jpg)
![htop](images/task_9.2_sort_PID.jpg)
![htop](images/task_9.2_sort_MEM.jpg)
![htop](images/task_9.2_sort_TIME.jpg)

Фильтр для процесса sshd.
![htop](images/task_9.3_filter_ssh.jpg)

C процессом syslog, найденным, используя поиск
![htop](images/task_9.4_search.jpg)

## Part 10. Использование утилиты fdisk

![fdisk](images/task_10.jpg)

## Part 11. Использование утилиты df

![df](images/task_11.1.jpg)
![df](images/task_11.2.jpg)

## Part 12. Использование утилиты du

Чтобы просто вывести список папок в определённом каталоге и занимаемое ими место, например, в /var выполните:

```sh
du <опция> <путь к папке>
```
![du](images/task_12_home.jpg)
![du](images/task_12.2_var.jpg)
![du](images/task_12.3_var_log_h.jpg)
![du](images/task_12.3_var_log.jpg)
![du](images/task_12.4_all.jpg)

## Part 13. Установка и использование утилиты ncdu

Установить утилиту ncdu.

![ncdu](images/task_13.1_install.jpg)
Вывести размер папок /home, /var, /var/log.
![ncdu](images/task_13.2.jpg)
![ncdu](images/task_13.3.jpg)
![ncdu](images/task_13.4.jpg)

## Part 14. Работа с системными журналами

![Журналы](images/task_14_dmesg.jpg)
![Журналы](images/task_14.1_auth.jpg)
![Журналы](images/task_14.1_syslog.jpg)

Перезапустить службу SSHd.
![Журналы](images/task_14.2_restart_sshd.jpg)


## Part 15. Использование планировщика заданий CRON

![CRON](images/task_15.1.jpg)
![CRON](images/task_15.2_edit.jpg)
![CRON](images/task_15.3_check.jpg)
![CRON](images/task_15.4_logs.jpg)
![CRON](images/task_15.5_erase.jpg)

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [VirtualBox]: <https://www.virtualbox.org/>
   [Ubuntu Server 20.4 lts]: <https://ubuntu.com/download/server>
