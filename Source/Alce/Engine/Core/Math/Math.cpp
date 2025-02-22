#include "Math.hpp"
#include "../Kernel/Kernel.hpp"
#include <sstream>  
#include <stdexcept>

using namespace alce;

#pragma region Random

int RANDOM::Range(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	
	std::uniform_int_distribution<int> dis(min, max);

	return dis(gen);
}

float RANDOM::Range(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(min, max);

	return dis(gen);
}

#pragma endregion

#pragma region Vector2

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(sf::Vector2f v)
{
	x = v.x;
	y = v.y;
}

Vector2::Vector2(sf::Vector2i v)
{
	x = (float) v.x;
	y = (float) v.y;
}

Vector2::Vector2(sf::Vector2u v)
{
	x = (float) v.x;
	y = (float) v.y;
}

Vector2::Vector2(b2Vec2 v)
{
	x = v.x;
	y = v.y;
}

Vector2& Vector2::operator=(const Vector2& v) 
{
	x = v.x;
	y = v.y;

	return *this;
}

bool Vector2::operator!=(const Vector2& v)
{
	return !(x == v.x && y == v.y);
}

Vector2 Vector2::operator+(const Vector2& v)
{
	Vector2 z;

	z.x = x + v.x;
	z.y = y + v.y;

	return z;
}

Vector2 Vector2::operator+(const float& s)
{
	Vector2 z;

	z.x = x + s;
	z.y = y + s;

	return z;
}

Vector2 Vector2::operator-(const Vector2& v)
{
	Vector2 z;

	z.x = x - v.x;
	z.y = y - v.y;

	return z;
}

Vector2 Vector2::operator-(const float& s)
{
	Vector2 z;

	z.x = x - s;
	z.y = y - s;

	return z;
}

void Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
}

void Vector2::operator+=(const float& s)
{
	x += s;
	y += s;
}

void Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2::operator-=(const float& s)
{
	x -= s;
	y -= s;
}

void Vector2::operator*=(const float s)
{
	x *= s;
	y *= s;
}

Vector2 Vector2::operator*(const float s)
{
	Vector2 v;

	v.x = x * s;
	v.y = y * s;

	return v;
}

void Vector2::operator/=(const float s)
{
	x /= s;
	y /= s;
}

Vector2 Vector2::operator/(const float s)
{
	Vector2 v;

	v.x = x / s;
	v.y = y / s;

	return v;
}

float Vector2::operator*(const Vector2& v)
{
	return (x * v.x) + (y * v.y);
}

float Vector2::Magnitude()
{
	return std::sqrt((x * x) + (y * y));
}

Vector2 Vector2::Normalized()
{	
	Vector2 out;

	out.x = (x / std::sqrt((x * x) + (y * y)));
	out.y = (y / std::sqrt((x * x) + (y * y)));

	return out;
}

sf::Vector2f Vector2::ToVector2f()
{
	return sf::Vector2f(x, y);
}

sf::Vector2i Vector2::ToVector2i()
{
	return sf::Vector2i((int)x, (int)y);
}

sf::Vector2u Vector2::ToVector2u()
{
	return sf::Vector2u((unsigned int)x, (unsigned int)y);
}

b2Vec2 Vector2::Tob2Vec2()
{
	return b2Vec2(x, y);
}

Vector2 Vector2::ToMeters()
{
	return Vector2(x / PPM, y / PPM);
}

void Vector2::FromString(String _str)
{
	std::string str = _str.ToAnsiString();

    size_t start = str.find('(');
    size_t end = str.find(')');
    if (start == std::string::npos || end == std::string::npos || start >= end)
    {
        throw std::invalid_argument("Formato inválido");
    }

    std::string coordinates = str.substr(start + 1, end - start - 1);

    size_t comma = coordinates.find(',');

    if (comma == std::string::npos)
    {
        Debug.Warning("Invalid Format");
		return;
    }

    std::string xStr = coordinates.substr(0, comma);
    std::string yStr = coordinates.substr(comma + 1);

    this->x = std::stof(xStr);
    this->y = std::stof(yStr);    
}

String Vector2::ToString()
{
	String str = "(x, y)";

	return str.Replace("x", String(x)).Replace("y", String(y));
}

void Vector2::ConvertToMeters()
{
	x /= PPM;
	y /= PPM;
}

Vector2 Vector2::ToPixels()
{
    float pixelX = std::round(x * PPM);
    float pixelY = std::round(Alce.GetScreenResolution().y - y * PPM);

    return Vector2(pixelX, pixelY);
}

void Vector2::ConvertToPixels()
{
	x *= PPM;
	y = Alce.GetScreenResolution().y - y * PPM;
}

float Vector2::Distance(Vector2 other)
{
	float cx, cy, d;

	cx = (other.x - x) * (other.x - x);
	cy = (other.y - y) * (other.y - y);
	d = std::sqrt(cx + cy);

	return d;
}

void Vector2::SetRound()
{
	x = int(x);
	y = int(y);
}

Vector2 Vector2::GetRound()
{
	return Vector2(int(x), int(y));
}

String Vector2::operator~()
{
	return ToString();
}

#pragma endregion

#pragma region Math

float MATH::Sqrt(float x)
{
	return std::sqrt(x);
}

float MATH::Pow(float x, float exp)
{
	return std::pow(x, exp);
}

float MATH::Abs(float x)
{
	return std::fabs(x);
}

float MATH::Sin(float a)
{
	return std::sin(a);
}

float MATH::Cos(float a)
{
	return std::cos(a);
}

Vector2 MATH::Lerp(Vector2 start, Vector2 end, float t)
{
	Vector2 result;
	result.x = start.x + (end.x - start.x) * t;
	result.y = start.y + (end.y - start.y) * t;
	return result;
}


#pragma endregion

#pragma region Shape

Shape::Shape(ShapeType type)
{
	this->type = type;
}

ShapeType Shape::GetType()
{
	return type;
}

#pragma endregion

#pragma region RectShape

RectShape::RectShape() : Shape(ShapeType::rect)
{
	position = Vector2(0.0f, 0.0f);
	width = 0;
	height = 0;
}

RectShape::RectShape(float width, float height) : Shape(ShapeType::rect)
{
	this->width = width;
	this->height = height;
}

RectShape::RectShape(Vector2 bounds) : Shape(ShapeType::rect)
{
	width = bounds.x;
	height = bounds.y;
}

RectShape::RectShape(Vector2 position, float width, float height) : Shape(ShapeType::rect)
{
	this->position = position;
	this->width = width;
	this->height = height;
}

RectShape::RectShape(float x, float y, float width, float height) : Shape(ShapeType::rect)
{
	position.x = x;
	position.y = y;
	this->width = width;
	this->height = height;
}

RectShape::RectShape(sf::FloatRect fr) : Shape(ShapeType::rect)
{
	position.x = fr.left;
	position.y = fr.top;
	width = fr.width;
	height = fr.height;
}

RectShape::RectShape(sf::IntRect fr) : Shape(ShapeType::rect)
{
	position.x = (float)fr.left;
	position.y = (float)fr.top;
	width = (float)fr.width;
	height = (float)fr.height;
}

sf::FloatRect RectShape::ToFloatRect()
{
	return sf::FloatRect(position.x, position.y, width, height);
}

sf::IntRect RectShape::ToIntRect()
{
	return sf::IntRect(position.x, position.y, width, height);
}

Vector2 RectShape::GetBounds()
{
	return Vector2(width, height);
}

bool RectShape::InArea(Vector2 point)
{
    return point.x >= position.x && point.x <= (position.x + width) && point.y >= position.y && point.y <= (position.y + height);
}

String RectShape::ToString()
{
	return alce::FormatString("width: {}, height: {}, x: {}, y: {}", {width, height, position.x, position.y});
}

String RectShape::operator~()
{
	return ToString();
}

#pragma endregion

#pragma region PolygonShape

PolygonShape::PolygonShape(List<Vector2> vertexArray) : Shape(ShapeType::polygon)
{
	this->vertexArray = vertexArray;

	std::vector<b2Vec2> b2_vertex_vector;

	for (auto& v : ~vertexArray)
	{
		b2_vertex_vector.push_back(v.Tob2Vec2());
	}

	b2vertexArray = b2_vertex_vector.data();
}

int PolygonShape::GetVertexCount()
{
	return vertexArray.Length();
}

List<Vector2> PolygonShape::GetVertexList()
{
	return vertexArray;
}

b2Vec2* PolygonShape::GetB2VertexArray()
{
	return b2vertexArray;
}

bool PolygonShape::InArea(Vector2 point)
{
    int i, j;
    bool c = false;
    int n = vertexArray.Length();

    for (i = 0, j = n - 1; i < n; j = i++)
    {
        if (((vertexArray[i].y > point.y) != (vertexArray[j].y > point.y)) &&
            (point.x < (vertexArray[j].x - vertexArray[i].x) * (point.y - vertexArray[i].y) / (vertexArray[j].y - vertexArray[i].y) + vertexArray[i].x))
        {
            c = !c;
        }
    }

    return c;
}

float PolygonShape::GetAverageEdgeLength()
{
	float totalEdgeLength = 0.0f;
	int edgeCount = vertexArray.Length();

	for(int i = 0; i < edgeCount; i++)
	{
		int nextIndex = (i + 1) % edgeCount;
		Vector2 currentVertex = vertexArray[i];
		Vector2 nextVertex = vertexArray[nextIndex];

		float edgeLength = (nextVertex - currentVertex).Magnitude();

		totalEdgeLength += edgeLength;
	}

	return totalEdgeLength / edgeCount;
}

#pragma endregion

#pragma region CircleShape

CircleShape::CircleShape() : Shape(ShapeType::circle)
{
	radius = 1.0f;
}

CircleShape::CircleShape(float radius) : Shape(ShapeType::circle)
{
	this->radius = radius;
}

bool CircleShape::InArea(Vector2 point)
{
	return position.Distance(point) <= radius;
}

#pragma endregion