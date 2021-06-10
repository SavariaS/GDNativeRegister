#ifndef GDNATIVE_AUTOREGISTER_HPP
#define GDNATIVE_AUTOREGISTER_HPP

#include <Godot.hpp>
#include <Engine.hpp>
#include <vector>

#define REGISTER_CLASS(CLASS) static inline bool m_registered = GDNativeAutoregister::register_class<CLASS>();
#define REGISTER_TOOL(CLASS) static inline bool m_registered = GDNativeAutoregister::register_tool<CLASS>();

class GDNativeAutoregister
{
    private:
        static std::vector<void(*)()>& m_class_funcs()
        {
            static std::vector<void(*)()> instance;
            return instance;
        }

        static std::vector<void(*)()>& m_tool_funcs()
        {
            static std::vector<void(*)()> instance;
            return instance;
        }
    
    public:
        GDNativeAutoregister() = delete;

        template<typename T>
        static inline bool register_class()
        {
            m_class_funcs().push_back([]{godot::register_class<T>();});
            return true;
        }

        template<typename T>
        static inline bool register_tool()
        {
            m_tool_funcs().push_back([]{godot::register_tool_class<T>();});
            return true;
        }

        static void register_classes()
        {
            for(auto func : m_class_funcs())
            {
                func();
            }
            m_class_funcs().clear();

            for(auto func : m_tool_funcs())
            {
                func();
            }
            m_tool_funcs().clear();
        }
};

#endif
