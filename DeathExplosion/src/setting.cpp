#include <llapi/utils/FileHelper.h>
#include <Nlohmann/json.hpp>
#include "Global.h"

#define InitJson(key1,key2,val)                                \
if (json.find(key1) != json.end()) {                      \
    if (json.at(key1).find(key2) != json.at(key1).end()) {\
    const nlohmann::json& out2 = json.at(key1).at(key2);  \
         out2.get_to(val);}}                              \

namespace Settings {
    float Radius = 10.2;
    bool canBreak = true;
    bool createFire = true;
    nlohmann::json globaljson() {
        nlohmann::json json;
        json["Config"]["Radius"] = Radius;
        json["Config"]["CanBreak"] = canBreak;
        json["Config"]["CreateFire"] = createFire;
        return json;
    }

    void initjson(nlohmann::json json) {
        InitJson("Config", "Radius", Radius);
        InitJson("Config", "CanBreak", canBreak);
        InitJson("Config", "CreateFire", createFire);
    }

    void WriteDefaultConfig(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            logger.error("无法打开配置文件");
            return;
        }
        auto json = globaljson();
        file << json.dump(4);
        file.close();
    }

    void LoadConfigFromJson(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            logger.error("无法打开配置文件");
            return;
        }
        nlohmann::json json;
        file >> json;
        file.close();
        initjson(json);
        WriteDefaultConfig(fileName);
    }
    void reloadJson(const std::string& fileName) {
        std::ofstream file(fileName);
        if (file){
            file << globaljson().dump(4);
        }
        else{
            logger.error("配置文件异常！");
        }
        file.close();
    }
}