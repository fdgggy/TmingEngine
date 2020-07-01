//The MIT License
//
//Copyright(c) 2016 - 2020 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//  Selection.cpp
//  Editor
//
//  Created by lillteblue on 2019/5/26.
//

#include "Selection.hpp"

namespace TmingEngine {
    
    Context * Selecttion:: activeContext = NULL;
    Transform * Selecttion:: activeTransform = NULL;
    string Selecttion::ProjectSelected = "";

    string Selecttion::GetActiveObjectName()
    {
        if(activeTransform!=NULL)
        {
              return activeTransform->GetGameObject()->GetGameObjectName();
        }else
        {
              return "Unselect any Object";
        }
      
    }

  
}