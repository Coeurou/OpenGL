//
//  cbSingleton.h
//  OpenGL
//
//  Created by Guillaume Trollé on 20/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#ifndef OpenGL_cbSingleton_h
#define OpenGL_cbSingleton_h

#include <system_error>

namespace Invocat {
    
namespace Tools {
    
    template <typename T>
    class cbSingleton {
        
    public:
        static T& GetInstance()
        {
            if( !instance ) {
                if ( destroyed ) {
                    OnDeadReference();
                } else {
                    Create();
                }
            }
            return *instance;
        }
        
        static T* GetInstancePtr()
        {
            if( !instance ) {
                if ( destroyed ) {
                    OnDeadReference();
                } else {
                    Create();
                }
            }
            return instance;
        }
        
    protected:
        static T*           instance;
        static bool         destroyed;
        
        virtual ~cbSingleton()
        {
            destroyed = true;
            instance = 0;
        }
        cbSingleton& operator=( const cbSingleton& assign );
        
        static void OnDeadReference()
        {
            std::runtime_error( "Dead Reference detected" );
        }
        
        static void Create()
        {
            static T uniqueObj;
            instance = &uniqueObj;
        }
    };
    
    template <typename T>
    T* Invocat::Tools::cbSingleton<T>::instance = 0;
    template <typename T>
    bool Invocat::Tools::cbSingleton<T>::destroyed = false;
}
}

#endif
