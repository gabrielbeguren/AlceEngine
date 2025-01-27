#pragma once

#include <memory>

#include "../../../Libs/Libs.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Chrono/Chrono.hpp"
#include "../B2World/B2World.hpp"
#include "../Interface/Interface.hpp"

namespace alce
{
    typedef std::shared_ptr<List<GameObjectPtr>> GameObjectListPtr;

    class Scene : public Object
    {
    public:

        Scene(String name);

        void InitPhysics(Vector2 gravity);

        void AddGameObject(GameObjectPtr gameObject, String alias = false);

        List<GameObjectPtr> GetAllGameObjects();

        void AddCanvas(CanvasPtr canvasPtr, ComponentPtr camera);

        String GetName();

        void Pause(bool flag = true);

        bool IsPaused();

        void Clear();

        B2WorldPtr GetWorld();

        void DevelopmentMode(bool flag = true);

        void Shell(String command);

        void Save();

        bool persist = false;

        int gridMargin = 3;

        bool IsLoading()
        {
            return loading;
        }

        virtual void Init()
        {
            
        }

        virtual void Start()
        {
            
        }

        unsigned int GridScale = 5;

        unsigned int GridTextSize = 9;

        Color GridColor = sf::Color(100, 100, 255, 150);

        Color AxisYColor = sf::Color(50, 150, 255, 200);

        Color AxisXColor = sf::Color(255, 100, 100, 200);

    private:

        friend class KERNEL;
        friend class GameObject;
        
        B2WorldPtr world = nullptr;

        String name;
        Dictionary<int, GameObjectListPtr> sortingLayers;
        List<CanvasPtr> canvasList;
        List<Object*> cameras;
        bool paused = false;
        bool developmentMode = false;
        bool loading = false;

        Json json;

        void EventsManager(sf::Event& e);

        void Render();

        void Update();

        void SetCardinals(GameObjectPtr gameObject, Dictionary<String, Vector2Ptr> cardinals);

        void RenderGrid(sf::RenderWindow& window, const sf::View& view);

        void UpdateJson();

        void LoadFromJson()
        {
            json.FromFile("./Scenes/" + GetName().ToAnsiString() + ".json");

            for(auto& sl : sortingLayers)
            {
                for(auto& go : *sl.second.get())
                {
                    bool hasAlias = json.Has(go->alias);
                    bool hasId = json.Has(go->id);

                    if(hasAlias || hasId) 
                    {
                        go->transform.position.FromString(json.GetJson(hasAlias ? go->alias : go->id).GetJson("transform").Get("position"));
                    }
                }
            }
        }

        bool JsonFileExists()
        {
            File file("./Scenes/" + GetName().ToAnsiString() + ".json");
            return file.Exists();
        }

        std::string Trim(const std::string& str) 
        {
            size_t first = str.find_first_not_of(" \t\n\r");
            if (first == std::string::npos) return "";
            size_t last = str.find_last_not_of(" \t\n\r");
            return str.substr(first, last - first + 1);
        }

        std::string RemoveComments(const std::string& code) 
        {
            std::string result;
            size_t len = code.length();
            bool inMultilineComment = false;

            for (size_t i = 0; i < len; ++i) 
            {
                if (inMultilineComment) 
                {
                    // End of multiline comment
                    if (i + 1 < len && code[i] == '*' && code[i + 1] == '/') 
                    {
                        inMultilineComment = false;
                        ++i; // Skip '/'
                    }
                } 
                else 
                {
                    // Start of multiline comment
                    if (i + 1 < len && code[i] == '/' && code[i + 1] == '*') 
                    {
                        inMultilineComment = true;
                        ++i; // Skip '*'
                    }
                    // Start of inline comment (// or #)
                    else if ((i + 1 < len && code[i] == '/' && code[i + 1] == '/') || code[i] == '#') 
                    {
                        break; // Ignore the rest of the line
                    }
                    // Regular character
                    else 
                    {
                        result += code[i];
                    }
                }
            }

            return result;
        }

        // Function to split a command string into individual commands by ';'
        std::vector<std::string> SplitCommands(const std::string& cmd) 
        {
            std::string cleanedCmd = RemoveComments(cmd);
            std::vector<std::string> commands;
            std::stringstream ss(cleanedCmd);
            std::string token;
            while (std::getline(ss, token, ';')) 
            {
                token = Trim(token);
                if (!token.empty()) 
                {
                    commands.push_back(token);
                }
            }
            return commands;
        }

        void ProcessCommand(const std::string& command);
       
    };

    typedef std::shared_ptr<Scene> ScenePtr;
}