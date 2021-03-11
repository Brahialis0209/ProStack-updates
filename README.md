# ProStack-updates
This is the repository for updates and some added changes to the ProStack directory.

## in Russian
Проблема: в текущей версии простака <br>
Есть пакеты которые устарели, и методы детектирования границ, такие как Canny  могут не работать (проверялось на Windows).<br>
Предлагается следущее решение. Вам нужно скачать и собрать opencv(в данной версии используется версия 3.4.12).<br>
Дале, скачать данный репозиторий, собрать (при разработке испоьзовался Visual Studio). Полученный .exe файл, все .dll файлы из opencv(например из opencv\build\x64\vc15\bin) а также .lib файл opencv_world3413d.lib <br>
(например из opencv\build\x64\vc15\lib) нужно закинуть в директорию ProStack.<br>
Весь код преставлен в файле main.cpp<br>
### Параметры для этой программы: <br>
opencv_2 -canny ksize sigma edgeThresh1 edgeThresh2 '..\opencv_2\lhbg.tif' '..\opencv_2\lhbg_out.tif'<br>
1. ksize - edge dimension for Gaussian blur.
2. sigma - parametr for Gaussian blur.
3. edgeThresh1, edgeThresh2 - first and second threshold for the hysteresis procedure. <br>
Example comand<br>
cd 'opencv_2\x64\Debug'<br>
opencv_2 -canny 3x3 1 0.03 0.1 '..\opencv_2\lhbg.tif' '..\opencv_2\lhbg_out.tif'<br>


## in English(fixed in future)
Problem: in the current version of the simpleton (link will be below)
There are packages that are outdated and boundary detection methods such as Canny may not work (tested on Windows).<br>
The following solution is proposed. You need to download opencv (this version uses version 3.2) and build it (for example using cmake). But before building you need to change the file'... opencv/samples/cpp/edge.cpp' The correct edge.cpp file is located in the src/Canny folder. The attached file has been changed so that the input parameters specified in the script are processed correctly.<br>

After build, you need to move the file '...opencvbuild/install/x64/mingw/samples/cpp/edge.exe' and all dll files from '... opencv/build/install/x64/mingw/bin' to the folder bin of the installed version of Prostack. And also rename edge.exe to convert .exe to match the script code.
After this procedure, the algorithm for blocks with Canny will work correctly.