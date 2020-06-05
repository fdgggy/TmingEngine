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

#include "Game.hpp"

namespace TmingEngine
{
	TmingEngine::Game::~Game()
	{
	}

	void TmingEngine::Game::Begin()
	{
		gameWidth = 1000;
		gameHeight = 1000;
		SoftRender();
	}

	void TmingEngine::Game::Update()
	{
		bool p_open = true;
		ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Game", &p_open))
		{
			ImGui::End();
			return;
		}
		ImTextureID my_tex_id = (void*)imageId;
		float my_tex_w = gameWidth;
		float my_tex_h = gameHeight;

		ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
		//----------------------------------------------------------------- -1 -1  Image reversal
		ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
		ImGui::End();
	}

	void TmingEngine::Game::End()
	{
	}

	void TmingEngine::Game::SoftRender()
	{
		glGenTextures(1, &imageId);

		glBindTexture(GL_TEXTURE_2D, imageId);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//// load image, create texture and generate mipmaps
		int width, height, nrChannels;

		TGAImage image(gameWidth, gameHeight, TGAImage::RGB);

		ImVec2 t0[3] = { ImVec2(0, 0),   ImVec2(350, 100),  ImVec2(250, 300) };
		ImVec2 t1[3] = { ImVec2(180, 50),  ImVec2(150, 1),   ImVec2(70, 180) };
		ImVec2 t2[3] = { ImVec2(180, 350), ImVec2(120, 260), ImVec2(130, 400) };
		triangle(t0[0], t0[1], t0[2], image, red);
		fillTriangle(t0[0], t0[1], t0[2], image, red);

		triangle(t1[0], t1[1], t1[2], image, blue);
		fillTriangle(t1[0], t1[1], t1[2], image, blue);

		triangle(t2[0], t2[1], t2[2], image, green);
		fillTriangle(t2[0], t2[1], t2[2], image, green);

		image.flip_horizontally();

		unsigned char* data = image.buffer();
		width = image.get_width();
		height = image.get_height();
		nrChannels = image.get_bytespp();

		if (data)
		{
			try
			{
				if (nrChannels == 4)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				}
				else if (nrChannels == 3)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				}
				else if (nrChannels == 1)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
				}
				else
				{
					int c = nrChannels;
				}

				glGenerateMipmap(GL_TEXTURE_2D);
			}
			catch (const std::exception&)
			{
			}
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		image.clear();
	}

	void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
		bool steep = false;
		if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
			std::swap(x0, y0);
			std::swap(x1, y1);
			steep = true;
		}
		if (x0 > x1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		int dx = x1 - x0;
		int dy = y1 - y0;
		int derror2 = std::abs(dy) * 2;
		int error2 = 0;
		int y = y0;
		for (int x = x0; x <= x1; x++) {
			if (steep) {
				image.set(y, x, color);
			}
			else {
				image.set(x, y, color);
			}
			error2 += derror2;
			if (error2 > dx) {
				y += (y1 > y0 ? 1 : -1);
				error2 -= dx * 2;
			}
		}
	}

	void line(ImVec2 x, ImVec2 y, TGAImage& image, TGAColor color)
	{
		line(x.x, x.y, y.x, y.y, image, color);
	}

	void triangle(ImVec2 t0, ImVec2 t1, ImVec2 t2, TGAImage& image, TGAColor color) {
		line(t0, t1, image, color);
		line(t1, t2, image, color);
		line(t2, t0, image, color);
	}

	void fillTriangle(ImVec2 t0, ImVec2 t1, ImVec2 t2, TGAImage& image, TGAColor color)
	{
		//根据 点的y坐标 从上到下排序
		if (t0.y < t1.y)
		{
			std::swap(t0, t1);
		}

		if (t0.y < t2.y)
		{
			std::swap(t0, t2);
		}

		if (t1.y < t2.y)
		{
			std::swap(t1, t2);
		}

		if (t1.y == t2.y)
		{
			fillUpTriangle(t0, t1, t2, image, color);
		}
		else if (t1.y == t0.y)
		{
			fillDownTriangle(t2, t1, t0, image, color);
		}
		else
		{
			//直线表达 两点式
			ImVec2 t4;
			t4.y = t1.y;
			t4.x = (t0.x - t2.x) / (t0.y - t2.y) * (t4.y - t2.y) + t2.x;

			fillUpTriangle(t0, t1, t4, image, color);

			fillDownTriangle(t2, t1, t4, image, color);
			line(t1, t4, image, white);
		}

		ImVec2* box = findTriangleBox(t0, t1, t2);
		auto b1 = box[0];
		auto b2 = box[1];
		;
	}

	void fillUpTriangle(ImVec2 t0, ImVec2 t1, ImVec2 t2, TGAImage& image, TGAColor color)
	{
		for (int i = 0; i < (t0.y - t1.y); i += 3)
		{
			ImVec2 p1, p2;
			p1.y = p2.y = t1.y + i;
			p1.x = (t0.x - t1.x) / (t0.y - t1.y) * (p1.y - t1.y) + t1.x;
			p2.x = (t0.x - t2.x) / (t0.y - t2.y) * (p2.y - t2.y) + t2.x;
			line(p1, p2, image, color);
		}
	}

	void fillDownTriangle(ImVec2 t0, ImVec2 t1, ImVec2 t2, TGAImage& image, TGAColor color)
	{
		for (int i = 0; i < (t1.y - t0.y); i++)
		{
			ImVec2 p1, p2;
			p1.y = p2.y = t1.y - i;
			p1.x = (t0.x - t1.x) / (t0.y - t1.y) * (p1.y - t1.y) + t1.x;
			p2.x = (t0.x - t2.x) / (t0.y - t2.y) * (p2.y - t2.y) + t2.x;
			line(p1, p2, image, color);
		}
	}

	ImVec2* findTriangleBox(ImVec2 t0, ImVec2 t1, ImVec2 t2)
	{
		ImVec2 minPoint, maxPoint;
		ImVec2 points[3], box[2];
		points[0] = t0;
		points[1] = t1;
		points[2] = t2;

		minPoint.x = points[0].x;
		minPoint.y = points[0].y;

		maxPoint.x = points[0].x;
		maxPoint.y = points[0].y;
		for (int i = 0; i < 3; i++)
		{
			if (minPoint.x > points[i].x)
			{
				minPoint.x = points[i].x;
			}
			if (minPoint.y > points[i].y)
			{
				minPoint.y = points[i].y;
			}

			if (maxPoint.x < points[i].x)
			{
				maxPoint.x = points[i].x;
			}
			if (maxPoint.y < points[i].y)
			{
				maxPoint.y = points[i].y;
			}
		}

		box[0] = minPoint;
		box[1] = maxPoint;

		return box;
	}
}