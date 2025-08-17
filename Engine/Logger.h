#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <atomic>
#include <filesystem>  // Добавлен заголовочный файл для filesystem

// Исправление макроса WIN32_LEAN_AND_MEAN
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

enum class LogLevel { TRACE, DEBUG, INFO, WARNING, ERRORR, CRITICAL };

// Вспомогательная функция для преобразования LogLevel в строку
inline std::string logLevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::TRACE: return "TRACE";
    case LogLevel::DEBUG: return "DEBUG";
    case LogLevel::INFO: return "INFO";
    case LogLevel::WARNING: return "WARN";
    case LogLevel::ERRORR: return "ERROR";
    case LogLevel::CRITICAL: return "CRITICAL";
    default: return "UNKNOWN";
    }
}

// Абстрактный sink с встроенной потокобезопасностью
class LogSink {
protected:
    std::mutex sinkMutex;
public:
    virtual void log(LogLevel level, const std::string& message) = 0;
    virtual ~LogSink() = default;
};

// Консольный sink
class ConsoleSink : public LogSink {
public:
    void log(LogLevel level, const std::string& message) override {
        std::lock_guard<std::mutex> lock(sinkMutex);
        std::cout << "[" << logLevelToString(level) << "] " << message << std::endl;
    }
};

// Файловый sink с ротацией
class FileSink : public LogSink {
    std::ofstream logFile;
    std::string filename;
    size_t maxSize;
    int maxFiles;

public:
    FileSink(const std::string& filename, size_t maxSizeMB = 10, int maxFiles = 5)
        : filename(filename), maxSize(maxSizeMB * 1024 * 1024), maxFiles(maxFiles) {
        rotateIfNeeded();
        logFile.open(filename, std::ios::app);
    }

    void log(LogLevel level, const std::string& message) override {
        std::lock_guard<std::mutex> lock(sinkMutex);
        if (logFile) {
            logFile << "[" << logLevelToString(level) << "] " << message << std::endl;
            rotateIfNeeded();
        }
    }

    void flush() {
        std::lock_guard<std::mutex> lock(sinkMutex);
        if (logFile) {
            logFile.flush();
        }
    }

    ~FileSink() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

private:
    void rotateIfNeeded() {
        if (logFile.tellp() > static_cast<std::streampos>(maxSize)) {
            logFile.close();
            for (int i = maxFiles - 1; i > 0; --i) {
                std::string oldName = filename + "." + std::to_string(i);
                std::string newName = filename + "." + std::to_string(i + 1);
                if (std::filesystem::exists(oldName)) {
                    std::filesystem::rename(oldName, newName);
                }
            }
            if (std::filesystem::exists(filename)) {
                std::filesystem::rename(filename, filename + ".1");
            }
            logFile.open(filename, std::ios::app);
        }
    }
};

// Потокобезопасный логгер
class Logger {
    std::vector<std::shared_ptr<LogSink>> sinks;
    mutable std::mutex sinksMutex;
    std::atomic<bool> initialized{ false };

public:
    void addSink(std::shared_ptr<LogSink> sink) {
        std::lock_guard<std::mutex> lock(sinksMutex);
        sinks.push_back(sink);
        if (!initialized) initialized = true;
    }

    void log(LogLevel level, const std::string& message) const {
        if (!initialized) return;

        std::vector<std::shared_ptr<LogSink>> sinksCopy;
        {
            std::lock_guard<std::mutex> lock(sinksMutex);
            sinksCopy = sinks;
        }

        for (const auto& sink : sinksCopy) {
            if (sink) {
                sink->log(level, message);
            }
        }
    }

    void flush() {
        std::lock_guard<std::mutex> lock(sinksMutex);
        for (auto& sink : sinks) {
            if (auto fileSink = std::dynamic_pointer_cast<FileSink>(sink)) {
                fileSink->flush();
            }
        }
    }
};

// Глобальный реестр логгеров
class LoggerRegistry {
    std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
    std::shared_ptr<Logger> defaultLogger;
    mutable std::mutex registryMutex;

    LoggerRegistry() = default;
    ~LoggerRegistry() = default;

public:
    static LoggerRegistry& instance() {
        static LoggerRegistry registry;
        return registry;
    }

    LoggerRegistry(const LoggerRegistry&) = delete;
    LoggerRegistry& operator=(const LoggerRegistry&) = delete;

    std::shared_ptr<Logger> getLogger(const std::string& name) {
        std::lock_guard<std::mutex> lock(registryMutex);

        if (auto it = loggers.find(name); it != loggers.end()) {
            return it->second;
        }

        auto newLogger = std::make_shared<Logger>();
        loggers[name] = newLogger;
        return newLogger;
    }

    void registerLogger(const std::string& name, std::shared_ptr<Logger> logger) {
        std::lock_guard<std::mutex> lock(registryMutex);
        loggers[name] = logger;
    }

    void setDefaultLogger(std::shared_ptr<Logger> logger) {
        std::lock_guard<std::mutex> lock(registryMutex);
        defaultLogger = logger;
    }

    void shutdown() {
        std::lock_guard<std::mutex> lock(registryMutex);
        for (auto& [name, logger] : loggers) {
            logger->flush();
        }
        loggers.clear();
        defaultLogger.reset();
    }
};

// Макросы для удобного использования
#define LOG_TRACE(message)   LoggerRegistry::instance().getLogger("global")->log(LogLevel::TRACE, message)
#define LOG_DEBUG(message)   LoggerRegistry::instance().getLogger("global")->log(LogLevel::DEBUG, message)
#define LOG_INFO(message)    LoggerRegistry::instance().getLogger("global")->log(LogLevel::INFO, message)
#define LOG_WARN(message)    LoggerRegistry::instance().getLogger("global")->log(LogLevel::WARNING, message)
#define LOG_ERROR(message)   LoggerRegistry::instance().getLogger("global")->log(LogLevel::ERRORR, message)
#define LOG_CRITICAL(message) LoggerRegistry::instance().getLogger("global")->log(LogLevel::CRITICAL, message)

// Инициализация логгера
inline void initLogger(const std::string& filename = "app.log") {
    auto globalLogger = std::make_shared<Logger>();
    globalLogger->addSink(std::make_shared<ConsoleSink>());
    globalLogger->addSink(std::make_shared<FileSink>(filename));

    LoggerRegistry::instance().registerLogger("global", globalLogger);
    LoggerRegistry::instance().setDefaultLogger(globalLogger);

    LOG_INFO("Logger initialized successfully");
}

// Очистка логгера
inline void shutdownLogger() {
    LOG_INFO("Shutting down logger...");
    LoggerRegistry::instance().shutdown();
}