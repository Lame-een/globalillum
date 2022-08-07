#pragma once
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <cassert>
#include <thread>
#include <mutex>
/*
Basic instrumentation profiler by Cherno
Forked by Lame

Usage:
    include this header file somewhere in your code (eg. precompiled header), and then use the:
        PROFILE_BEGIN_SESSION(std::string seesionName)
        PROFILE_END_SESSION()
        PROFILE_SCOPE(std::string scopeName)
        PROFILE_FUNCTION()
    macros while defining
        #define PROFILING 1
    before the header.

Example:
    void foo()
    {
        PROFILE_FUNCTION();
        //...
    }

    int main()
    {
        PROFILE_BEGIN_SESSION("foo", "C:\example\example\");

        foo();

        {
            PROFILE_SCOPE("scope");
            //...
        }

        PROFILE_END_SESSION();
    }

For multithreading purposes, define
    #define PROFILING_MULTITHREAD 1
*/

#if PROFILING
#define PROFILE_BEGIN_SESSION(sessionName) lameutil::Instrumentor::Get().BeginSession(sessionName)
#define PROFILE_END_SESSION() lameutil::Instrumentor::Get().EndSession()
#define PROFILE_SCOPE(scopeName) lameutil::InstrumentationTimer timer##__LINE__(scopeName)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else 
#define PROFILE_BEGIN_SESSION()
#define PROFILE_END_SESSION()
#define PROFILE_SCOPE(scopeName)
#define PROFILE_FUNCTION()
#endif

namespace lameutil
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        //uint32_t ThreadID;
        std::thread::id ThreadID;
    };

    class Instrumentor
    {
    private:
#ifdef PROFILING_MULTITHREAD
        std::mutex writeMutex;
#endif
        std::ofstream m_OutputStream;

        int m_ProfileCount;
        std::string m_Filepath;
        bool m_SessionStarted;

        Instrumentor()
            : m_ProfileCount{0}, m_Filepath{""}, m_SessionStarted{false}
        {
        }

    public:


        ~Instrumentor()
        {
            if(m_ProfileCount != 0)
            {
                EndSession();
            }
        }

        void SetFilepath(const std::string& path)
        {
            m_Filepath = path;
        }

        void BeginSession(const std::string& name = "session")
        {
            assert(!m_SessionStarted && "Unable to start multiple sessions in parallel.");
            m_SessionStarted = true;
            m_OutputStream.open(m_Filepath + name + ".session.json");
            WriteHeader();
        }

        void EndSession()
        {
            WriteFooter();
            m_OutputStream.close();
            m_ProfileCount = 0;
            m_SessionStarted = false;
        }

        void WriteProfile(const ProfileResult& result)
        {
#ifdef PROFILING_MULTITHREAD
            std::lock_guard<std::mutex> lock(writeMutex);
#endif
            if(m_ProfileCount++ > 0)
                m_OutputStream << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            m_OutputStream << "{";
            m_OutputStream << "\"cat\":\"function\",";
            m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            m_OutputStream << "\"name\":\"" << name << "\",";
            m_OutputStream << "\"ph\":\"X\",";
            m_OutputStream << "\"pid\":0,";
            m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            m_OutputStream << "\"ts\":" << result.Start;
            m_OutputStream << "}";

            //m_OutputStream.flush();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }
        };

    class InstrumentationTimer
    {
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
        Instrumentor* manager;
    public:
        InstrumentationTimer(const char* name)
            : m_Name(name), m_Stopped(false)
        {
            manager = &Instrumentor::Get();
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if(!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            //uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            std::thread::id threadID = std::this_thread::get_id();
            manager->WriteProfile({m_Name, start, end, threadID});

            m_Stopped = true;
        }
    };

    }