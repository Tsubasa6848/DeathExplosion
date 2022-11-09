#include "setting.h"
#include "Global.h"
#include <llapi/LoggerAPI.h>

void loadConfig() {
    if (!std::filesystem::exists("plugins/DeathExplosion"))
        std::filesystem::create_directories("plugins/DeathExplosion");	
    if (std::filesystem::exists(ConfigFile)) {
        Settings::LoadConfigFromJson(ConfigFile);
    }
    else {
        logger.warn("配置文件不存在，已自动创建");
        Settings::WriteDefaultConfig(ConfigFile);
    }
}