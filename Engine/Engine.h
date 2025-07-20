#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "SFML/Graphics.hpp"

namespace GameEngine
{
    class Engine
    {
    public:
        static Engine* Instance();
        void Initialize();
        void Run();

        Engine();
        ~Engine() = default;

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
    };
}