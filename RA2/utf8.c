// utf8.c
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <locale.h>
#endif

void configurar_console_utf8(void) {
#ifdef _WIN32
    // Windows: muda code page do console para UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);  // também para entrada (opcional)
#else
    // Linux/macOS: define locale para UTF-8
    setlocale(LC_ALL, "pt_BR.UTF-8");
    // Fallback se pt_BR.UTF-8 não existir
    if (!setlocale(LC_ALL, "")) {
        setlocale(LC_ALL, "C.UTF-8");
    }
#endif
}