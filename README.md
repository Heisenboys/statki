## Wymagania i kompilacja

### Wymagania systemowe
* **Kompilator C++:** zgodny ze standardem **C++17** (GCC >= 9.0, Clang >= 10.0 lub MSVC 2019+)
* **Biblioteka Qt:** wersja **Qt 6** (wymagany moduł `Widgets`)
* **Narzędzie do budowania:** **CMake** w wersji >= 3.16

---

### Kompilacja i uruchomienie (Terminal / CLI)

```bash
# 1. Konfiguracja projektu
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Wskazanie ścieżki do Qt (jeśli nie jest w PATH):
# cmake -B build -S . -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2019_64"

# 2. Kompilacja
cmake --build build --config Release

# 3. Uruchomienie aplikacji
./build/Battleship
# lub na Windowsie:
# ./build/Release/Battleship.exe
