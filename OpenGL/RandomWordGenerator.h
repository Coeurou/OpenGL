//
//  RandomWordGenerator.h
//  OpenGL
//
//  Created by Guillaume Trollé on 10/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#ifndef __OpenGL__RandomWordGenerator__
#define __OpenGL__RandomWordGenerator__

#include <string>
#include <vector>
#include <map>

namespace Invocat {
    
namespace Tools {
    
    class RandomWordGenerator {
    
    public:
    
        RandomWordGenerator();
        RandomWordGenerator( std::string databaseFile );
    
        void Init();
        const std::string GenerateWord() const;
    
    private:
        std::vector<std::string> wordDatabase;
        std::map<std::string, unsigned int> transitions;
    
        std::vector<std::string> ReadFile( std::string data ) const;
        void ComputeTransitions();
        void UpdateTransitions( const std::string& prev, const std::string& next );
        const std::string BuildWord( const std::string state ) const;
};
    
}
    
}

#endif /* defined(__OpenGL__RandomWordGenerator__) */
