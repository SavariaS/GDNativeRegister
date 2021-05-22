# GDNativeAutoregister

**GDNativeAutoregister** is a one header library to make registering GDNative classes easier and more modular. 

[SeleDreams](https://github.com/SeleDreams) came up with the concept and the core implementation. They also made their own [GDNative class factory](https://github.com/SeleDreams/gdnative_class_factory).

## How to use
Make sure `GDNativeAutoregister.hpp` is accessible to your header files.

To register a class, call the `REGISTER_CLASS` macro inside the class declaration.
``` cpp
#include <Godot.hpp>
#include <Node.hpp>
#include <GDNativeAutoregister.hpp>

namespace godot 
{
    class GDExample : public Sprite 
    {
        GODOT_CLASS(GDExample, Sprite)
        REGISTER_CLASS(GDExample)
        
        public:
            static void _register_methods();
        
            GDExample();
            ~GDExample();
        };
}
```

Call `gdnative_autoregister::register_classes` in `godot_native_script_init` (defined in `gdlibrary.cpp` in the [GDNative C++ example](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html)).

``` cpp
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) 
{
    godot::Godot::nativescript_init(handle);
    gdnative_autoregister::register_classes();
}
```