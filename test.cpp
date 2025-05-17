#include <windows.h>
#include <iostream>

// Função da thread secundária
DWORD WINAPI ThreadSecundaria(LPVOID lpParam) {
    std::cout << "Thread secundária iniciada. ID: " << GetCurrentThreadId() << std::endl;

    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread secundária executando: " << i + 1 << std::endl;
        Sleep(1000); // Dorme por 1 segundo
    }

    std::cout << "Thread secundária finalizada." << std::endl;
    return 0;
}

int main() {
    std::cout << "Thread principal iniciada. ID: " << GetCurrentThreadId() << std::endl;

    // Criando a thread secundária
    DWORD threadId;
    HANDLE hThread = CreateThread(
        NULL,              // Atributos padrão de segurança
        0,                 // Tamanho da pilha (0 usa o padrão)
        ThreadSecundaria,  // Função da thread
        NULL,              // Parâmetro da função (nenhum nesse caso)
        0,                 // Flags (0 inicia imediatamente)
        &threadId          // Retorna o ID da thread
    );

    if (hThread == NULL) {
        std::cerr << "Erro ao criar thread secundária. Código: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Thread secundária criada com sucesso. ID: " << threadId << std::endl;

    // A thread principal pode continuar fazendo outras coisas
    for (int i = 0; i < 3; ++i) {
        std::cout << "Thread principal executando: " << i + 1 << std::endl;
        Sleep(1000);
    }

    // Espera pela finalização da thread secundária
    WaitForSingleObject(hThread, INFINITE);

    // Fecha o handle da thread
    CloseHandle(hThread);

    std::cout << "Thread principal finalizada." << std::endl;
    return 0;
}
