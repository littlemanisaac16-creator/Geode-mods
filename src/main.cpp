#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <random>

using namespace geode::prelude;

class $modify(PlayerObject) {
    void playerDestroyed(bool p0) {
        PlayerObject::playerDestroyed(p0);

        // 1. Locate the file in the mod's baked resources
        auto path = Mod::get()->getResourcesDir() / "messages.txt";
        std::ifstream file(path.string());
        std::vector<std::string> messages;
        std::string line;

        // 2. Read all 30 messages into a list
        if (file.is_open()) {
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    messages.push_back(line);
                }
            }
            file.close();
        }

        // 3. If we found messages, pick one and show it!
        if (!messages.empty()) {
            // Using a better random generator for C++
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, messages.size() - 1);
            
            std::string randomMsg = messages[dis(gen)];
            
            // Displays the message as a Geode notification
            Notification::create(randomMsg, NotificationIcon::None)->show();
        }
    }
};
