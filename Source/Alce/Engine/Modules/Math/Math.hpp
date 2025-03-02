#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <random>
#include <limits>

#include "../../../Libs/Libs.hpp"

#define Random RANDOM::Instance()
#define Math MATH::Instance()

#define PPM 30.0F
#define DEG_PER_RAD 57.2957795F

namespace alce
{
	class RANDOM
	{
	public:

		static RANDOM& Instance()
		{
			static RANDOM random;
			return random;
		}

		int Range(int min, int max);

		float Range(float min, float max);

	private:

		RANDOM()
		{
			
		};

		RANDOM(RANDOM const&);

		void operator=(RANDOM const&);
	};

	#pragma region Vector2

	class Vector2
	{
	public:

		Vector2();

		Vector2(float x, float y);

		Vector2(sf::Vector2f v);

		Vector2(sf::Vector2i v);

		Vector2(sf::Vector2u v);

		Vector2(b2Vec2 v);

		Vector2& operator=(const Vector2& v);

		bool operator!=(const Vector2& v);

		Vector2 operator+(const Vector2& v);

		Vector2 operator+(const float& s);

		Vector2 operator-(const Vector2& v);

		Vector2 operator-(const float& s);

		void operator+=(const Vector2& v);

		void operator+=(const float& s);

		void operator-=(const Vector2& v);

		void operator-=(const float& s);

		void operator*=(const float s);

		Vector2 operator*(const float s);

		void operator/=(const float s);

		Vector2 operator/(const float s);

		float operator*(const Vector2& v);

		float Magnitude();

		Vector2 Normalized();

		sf::Vector2f ToVector2f();

		sf::Vector2i ToVector2i();

		sf::Vector2u ToVector2u();

		b2Vec2 Tob2Vec2();

		Vector2 ToMeters();

		String ToString();

		void FromString(String str);

		void ConvertToMeters();

		Vector2 ToPixels();

		void ConvertToPixels();

		float Distance(Vector2 other);

		void SetRound();

		Vector2 GetRound();

		String operator~();

		float x = 0;

		float y = 0;
	};

	typedef std::shared_ptr<Vector2> Vector2Ptr;

	#pragma endregion

	class MATH
	{
	public:

		static MATH& Instance()
		{
			static MATH math;
			return math;
		}

		const float PI = 3.1416f;

		float Sqrt(float x);

		float Pow(float x, float exp);

		float Abs(float x);

		float Sin(float a);

		float Cos(float a);

		Vector2 Lerp(Vector2 start, Vector2 end, float t);

		template<typename T>
		T Max(List<T> list)
		{
			T max = std::numeric_limits<T>::lowest();

			for(T num: ~list)
			{
				if(num > max)
				{
					max = num;
				}
			}

			return max;
		}

		template<typename T>
		T Min(List<T> list)
		{
			T min = std::numeric_limits<T>::max();

			for(T num: ~list)
			{
				if(num < min)
				{
					min = num;
				}
			}

			return min;
		}

	private:

		MATH()
		{

		};
	};

	#pragma region Shapes

	enum ShapeType
	{
		rect,
		circle,
		polygon,
		none
	};

	class Shape
	{
	public:

		Shape()
		{

		}

		Shape(ShapeType type);

		ShapeType GetType();

		Vector2 position = Vector2(0.0f, 0.0f);

	protected:

		ShapeType type = ShapeType::none;
	};

	typedef std::shared_ptr<Shape> ShapePtr;

	class PolygonShape : public Shape
	{
	public:

		PolygonShape(List<Vector2> vertexArray);

		int GetVertexCount();

		b2Vec2* GetB2VertexArray();

		List<Vector2> GetVertexList();

		bool InArea(Vector2 point);

		float GetAverageEdgeLength();

	private:

		List<Vector2> vertexArray;

		b2Vec2* b2vertexArray = nullptr;
	};

	typedef std::shared_ptr<PolygonShape> PolygonShapePtr;

	class CircleShape : public Shape
	{
	public:

		CircleShape();

		CircleShape(float radius);

		bool InArea(Vector2 point);
		
		float radius;
	};

	typedef std::shared_ptr<CircleShape> CircleShapePtr;

	class RectShape : public Shape
	{
	public:
		
		RectShape();

		RectShape(float width, float height);

		RectShape(Vector2 bounds);

		RectShape(Vector2 position, float width, float height);

		RectShape(float x, float y, float width, float height);

		RectShape(sf::FloatRect fr);

		RectShape(sf::IntRect fr);

		sf::FloatRect ToFloatRect();

		sf::IntRect ToIntRect();

		Vector2 GetBounds();

		bool InArea(Vector2 point);

		float width = 0.0f;

		float height = 0.0f;

		String ToString();

		String operator~();
	};

	typedef std::shared_ptr<RectShape> RectShapePtr;

	#pragma endregion
}