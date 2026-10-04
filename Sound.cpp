#include "Sound.h"
#include <string>


void Sound::playSound(std::string newPath) {
    
    std::filesystem::path path{ newPath };


    PlaySound(path.wstring().c_str(), NULL, SND_ASYNC);
}