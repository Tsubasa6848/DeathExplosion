#include "Global.h"
#include "version.h"

using namespace Settings;

extern void loadConfig();

void PluginInit(){
    loadConfig();

    logger.info("DeathExplosion - 死亡自爆加载成功！");
    logger.info("当前版本 {}.{}.{}",PLUGIN_VERSION_MAJOR,PLUGIN_VERSION_MINOR,PLUGIN_VERSION_REVISION);
    logger.info("插件作者 Tsubasa6848");

    Event::PlayerDieEvent::subscribe([](const Event::PlayerDieEvent& event) {
        auto pl = event.mPlayer;
        auto pos = pl->getPos();
        auto dimid = pl->getDimensionId();
        Global<Level>->createExplosion(pos,dimid,pl,Radius,createFire,canBreak,2147483647.0);
        return true;
    });
}