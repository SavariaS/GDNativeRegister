#ifndef GDNATIVE_AUTOREGISTER_HPP
#define GDNATIVE_AUTOREGISTER_HPP

#include <Godot.hpp>
#include <vector>

#define REGISTER_CLASS(CLASS) static inline bool m_registered = gdnative_autoregister::register_class<CLASS>();

class gdnative_autoregister
{
    private:
        static std::vector<void(*)()>& m_register_funcs()
        {
            static std::vector<void(*)()> instance;
            return instance;
        }
    
    public:
        gdnative_autoregister() = delete;

        template<typename T>
        static inline bool register_class()
        {
            m_register_funcs().push_back([]{godot::register_class<T>();});
            return true;
        }

        static void register_classes()
        {
            for(auto func : m_register_funcs())
            {
                func();
            }
            m_register_funcs().clear();
        }
};

#endif