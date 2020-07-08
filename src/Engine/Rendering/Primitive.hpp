/*
			This file is part of:
				TmingEngine
			https://github.com/xiaomingfun/TmingEngine

   Copyright 2018 - 2020 TmingEngine

   File creator: littleblue

   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef TmingEngine_Engine_Rending_Primitive_hpp_
#define TmingEngine_Engine_Rending_Primitive_hpp_

#include "Core/EngineDefs.h"
#include "Rendering/Model.hpp"
#include "Plantform/FileSystem/FileSystem.h"

namespace TmingEngine
{
	enum PrimitiveType
	{
		POINTS,
		LINES,
		TRIANGLES,
	};

	ENGINE_CLASS class Primitive
	{
	public:
		PrimitiveType  primitiveType;
		vector<Vertex> poins;

		Primitive()
		{
		}

		Primitive(PrimitiveType pt, vector<Vertex> manyPoints)
		{
			primitiveType = pt;
			poins = manyPoints;
		}
	};
} //namespace TmingEngine

#endif //TmingEngine_Engine_Rending_Primitive_hpp_