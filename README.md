# GDNativeAutoregister

**GDNativeAutoregister** is a one header library to make registering GDNative classes easier and more modular. 

[SeleDreams](https://github.com/SeleDreams) came up with the concept and the core implementation. They also made their own [GDNative class factory](https://github.com/SeleDreams/gdnative_class_factory), which also generates `.gdns` files automatically.

## How to use
Make sure `GDNativeAutoregister.hpp` is accessible to your header files.

To register a class, call the `REGISTER_CLASS` macro inside the class definition. To register a tool class, call `REGISTER_TOOL` instead.
``` cpp
#include <Godot.hpp>
#include <Node.hpp>
#include <GDNativeAutoregister.hpp>

namespace godot 
{
    class ClassExample : public Node 
    {
        GODOT_CLASS(ClassExample, Node)
        REGISTER_CLASS(ClassExample)
        
        public:
            static void _register_methods();
        
            ClassExample();
            ~ClassExample();
    };
}
```

``` cpp
#include <Godot.hpp>
#include <Node.hpp>
#include <GDNativeAutoregister.hpp>

namespace godot
{
    class ToolExample : public Node
    {
        GODOT_CLASS(ToolExample, Node)
        REGISTER_TOOL(ToolExample)

        public:
            static void _register_methods();

            ClassExample();
            ~ClassExample();
    };
}
```

Call `gdnative_autoregister::register_classes` in `godot_native_script_init'.

``` cpp
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) 
{
    godot::Godot::nativescript_init(handle);
    gdnative_autoregister::register_classes();
}
```
