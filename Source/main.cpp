// #include "Project/Scenes/Scenes.hpp"

// using namespace alce;

// int main()
// {
//     Alce.Window("Alce Engine Test", DisplayMode::Default);
//     Alce.stanby = true;

//     Debug.SetWaitTime(0);

//     //Alce.AddScene<Test1Scene::Test1>();
//     Alce.AddScene<SampleScene::Sample>();
    
//     Alce.SetCurrentScene("Sample");
//     Alce.GetCurrentScene()->Shell("system; /*hola que tal*/ window;");

    
//     //Alce.Run();

//     return 0;
// }

#include <iostream>
#include <tchar.h>
#include <windows.h>

void getArchitecture() {
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo); // Cambiado a GetNativeSystemInfo para obtener la arquitectura real

    if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        std::cout << "Arquitectura: x86_64 (64 bits)" << std::endl;
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
        std::cout << "Arquitectura: x86 (32 bits)" << std::endl;
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM)
        std::cout << "Arquitectura: ARM" << std::endl;
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64)
        std::cout << "Arquitectura: ARM64" << std::endl;
    else
        std::cout << "Arquitectura: Desconocida" << std::endl;
}

void getRAM() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    std::cout << "Memoria RAM total: " << (memInfo.ullTotalPhys / (1024 * 1024)) << " MB" << std::endl;
}

void getCPU() {
    HKEY hKey;
    TCHAR cpuName[256];
    DWORD size = sizeof(cpuName); // Asegurarse de que size es el tamaño en bytes

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueEx(hKey, _T("ProcessorNameString"), nullptr, nullptr, (LPBYTE)cpuName, &size) == ERROR_SUCCESS) {
            std::wcout << L"Procesador: " << cpuName << std::endl;
        } else {
            std::cout << "Error al leer el nombre del procesador" << std::endl;
        }
        RegCloseKey(hKey);
    } else {
        std::cout << "Error al acceder al registro del procesador" << std::endl;
    }
}

void getGPU() {
    DISPLAY_DEVICE displayDevice;
    displayDevice.cb = sizeof(DISPLAY_DEVICE);

    if (EnumDisplayDevices(nullptr, 0, &displayDevice, 0)) {
        std::wcout << L"Tarjeta gráfica: " << displayDevice.DeviceString << std::endl;
    } else {
        std::cout << "Tarjeta gráfica: No disponible" << std::endl;
    }
}

int main() {
    std::wcout << L"Información del sistema:\n------------------------" << std::endl;
    getArchitecture();
    getRAM();
    getCPU();
    getGPU();

    return 0;
}
