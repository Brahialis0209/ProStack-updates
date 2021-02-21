# ProStack-updates
This is the repository for updates and some added changes to the ProStack directory.

## in Russian
Проблема: в текущей версии простака <br>
Есть пакеты которые устарели, и методы детектирования границ, такие как Canny  могут не работать (проверялось на Windows).<br>
Предлагается следющеее решение. Вам нужно скачать opencv(в данной версии используется версия 3.2) и собрать её (например с помощью cmake). Но перед сборкой вам нужно изменить файл ' ...opencv/samples/cpp/edge.cpp'  Правильный файл edge.cpp находится в папке src/Canny.<br>
Приложеный файл был изменён таким образом чтобы входные параметры указанные в сценарии обрабатывались корректно.
После сборки вам нужно переместить файл  '...opencvbuild/install/x64/mingw/samples/cpp/edge.exe '   и все dll файлы из '...opencv/build/install/x64/mingw/bin'  в папку bin установленной версии Prostack. А также переименовать  edge.exe на convert .exe для соотвествия коду сценария.
После данной процедуры алгоритм для блоков с Canny будет работать корректно.

## in English
Problem: in the current version of the simpleton (link will be below)
There are packages that are outdated and boundary detection methods such as Canny may not work (tested on Windows).<br>
The following solution is proposed. You need to download opencv (this version uses version 3.2) and build it (for example using cmake). But before building you need to change the file'... opencv/samples/cpp/edge.cpp' The correct edge.cpp file is located in the src/Canny folder. The attached file has been changed so that the input parameters specified in the script are processed correctly.<br>

After build, you need to move the file '...opencvbuild/install/x64/mingw/samples/cpp/edge.exe' and all dll files from '... opencv/build/install/x64/mingw/bin' to the folder bin of the installed version of Prostack. And also rename edge.exe to convert .exe to match the script code.
After this procedure, the algorithm for blocks with Canny will work correctly.