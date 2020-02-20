#include "read_obj.h"


#include <fstream>
#include <sstream>

#include <algorithm>


ObjParser::ObjParser(std::string filename):
	filename(filename)
{
}


ObjParser::~ObjParser()
{

}

int ObjParser::Parse()
{
    std::ifstream file(filename, std::ifstream::in);

    if (file.fail())
        return -1;

    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("v ", 0) == 0) {
            auto tokens = Split(line, ' ');

            float4 ver{0, 0, 0, 1};
            for (auto i = 1; i < tokens.size(); i++) {
                if (!tokens[i].empty()) {
                    float v = std::stof(tokens[i]);
                    ver[i - 1] = v;
                }
            }
            vertexes.push_back(ver);
        } else if (line.rfind("f ", 0) == 0) {
            auto tokens = Split(line, ' ');

            float4 first;
            auto ind0 = std::stoi(Split(tokens[1], '/')[0]);
            first = vertexes[vertexes.size() + ind0];

            float4 last;
            bool was = false;
            float4 curr;

            for (auto i = 2; i < tokens.size(); i++) {
                if (!tokens[i].empty()) {
                    auto ind = std::stoi(Split(tokens[i], '/')[0]);

                    curr = vertexes[vertexes.size() + ind];

                    if (was) {
                        faces.emplace_back<face>({
                                first, last, curr
                        });
                    }
                    last = curr;
                    was = true;
                }
            }

        }
    }

    return 0;
}

const std::vector<face>& ObjParser::GetFaces()
{
	return faces;
}

std::vector<std::string> ObjParser::Split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}


ReadObj::ReadObj(unsigned short width, unsigned short height, std::string obj_file) : LineDrawing(width, height) {
    parser = new ObjParser(obj_file);
}

ReadObj::~ReadObj() {
    delete parser;
}

void ReadObj::DrawTriangle(face const &f, color c) {
    auto x_center = width / 2;
    auto y_center = height / 2;
    auto radius = std::min(width, height) / 2;

    float4 vertices[3];

    for (int i = 0; i < 3; i++) {
        vertices[i] = float4{
                f.vertexes[i].x * radius + x_center,
                f.vertexes[i].y * radius + y_center,
                0,
                1
        };
    }

    DrawLine(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, color{255, 0, 0});
    DrawLine(vertices[0].x, vertices[0].y, vertices[2].x, vertices[2].y, color{0, 0, 255});
    DrawLine(vertices[2].x, vertices[2].y, vertices[1].x, vertices[1].y, color{0, 255, 0});
}

void ReadObj::DrawScene() {
    parser->Parse();
    auto faces = parser->GetFaces();

    for (auto const &f: faces) {
        DrawTriangle(f, color{255, 255, 255});
    }
}

